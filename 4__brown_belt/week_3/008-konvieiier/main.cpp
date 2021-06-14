#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "test_runner.h"

using namespace std;

struct Email {
    Email() = default;
    Email(string from, string to, string body)
        : from(std::move(from)), to(std::move(to)), body(std::move(body)) {}
    string from;
    string to;
    string body;
};

class Worker {
   public:
    virtual ~Worker() = default;
    virtual void Process(unique_ptr<Email> email) = 0;
    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

   protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const {
        if (!next_) {
            return;
        }
        next_->Process(move(email));
    }

   public:
    void SetNext(unique_ptr<Worker> next) { next_ = move(next); }

   private:
    unique_ptr<Worker> next_;
};

class Reader : public Worker {
   public:
    Reader(istream& is) : is(is) {}
    void Run() override {
        while (is) {
            auto email = make_unique<Email>();
            if (!getline(is, email->from)) {
                break;
            }
            if (!getline(is, email->to)) {
                break;
            }
            if (!getline(is, email->body)) {
                break;
            }
            PassOn(move(email));
        }
    }
    void Process(unique_ptr<Email> email) override { throw logic_error("chotam?"); }

   private:
    istream& is;
};

class Filter : public Worker {
   public:
    using Function = function<bool(const Email&)>;
    Filter(Function f) : f(std::move(f)) {}
    void Process(unique_ptr<Email> email) override {
        if (f(*email)) {
            PassOn(move(email));
        }
    }

   private:
    Function f;
};

class Copier : public Worker {
   public:
    Copier(string to) : to(move(to)) {}
    void Process(unique_ptr<Email> email) override {
        if (email->to == to) {
            PassOn(move(email));
            return;
        }
        auto copy_email = make_unique<Email>(email->from, to, email->body);
        PassOn(move(email));
        PassOn(move(copy_email));
    }

   private:
    string to;
};

class Sender : public Worker {
   public:
    Sender(ostream& os) : os(os) {}
    void Process(unique_ptr<Email> email) override {
        os << email->from << '\n';
        os << email->to << '\n';
        os << email->body << '\n';
        PassOn(move(email));
    }

   private:
    ostream& os;
};

// реализуйте класс
class PipelineBuilder {
   public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream& in) { workers.push_back(make_unique<Reader>(in)); }

    // добавляет новый обработчик Filter
    PipelineBuilder& FilterBy(Filter::Function filter) {
        workers.push_back(make_unique<Filter>(move(filter)));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder& CopyTo(string recipient) {
        workers.push_back(make_unique<Copier>(move(recipient)));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder& Send(ostream& out) {
        workers.push_back(make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build() {
        for (size_t i = workers.size() - 1; i > 0; --i) {
            workers[i - 1]->SetNext(move(workers[i]));
        }
        return move(workers[0]);
    }

   private:
    vector<unique_ptr<Worker>> workers;
};

void TestSanity() {
    string input =
        ("erich@example.com\n"
         "richard@example.com\n"
         "Hello there\n"

         "erich@example.com\n"
         "ralph@example.com\n"
         "Are you sure you pressed the right button?\n"

         "ralph@example.com\n"
         "erich@example.com\n"
         "I do not make mistakes of that kind\n");
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email& email) { return email.from == "erich@example.com"; });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput =
        ("erich@example.com\n"
         "richard@example.com\n"
         "Hello there\n"

         "erich@example.com\n"
         "ralph@example.com\n"
         "Are you sure you pressed the right button?\n"

         "erich@example.com\n"
         "richard@example.com\n"
         "Are you sure you pressed the right button?\n");

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
