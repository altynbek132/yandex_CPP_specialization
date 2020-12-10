// #include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <iomanip>
#include <fstream>

#include <numeric>

using namespace std;

void txt() {
    const char *maslo = std::getenv("maslo");
    if (!maslo) {
        return;
    }
    
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// ==================================

class Date {
 public:
  Date() : year(0), month(0), day(0) {}
  Date(int year_, int month_, int day_) : year(0), month(0), day(0) {
      if (month_ < 1 || month_ > 12) {
          stringstream error;
          error << "Month value is invalid: " << month_;
          throw logic_error(error.str());
      }
      if (day_ < 1 || day_ > 31) {
          stringstream error;
          error << "Day value is invalid: " << day_;
          throw logic_error(error.str());
      }
      year = year_;
      month = month_;
      day = day_;
  }
  int GetYear() const {
      return year;
  }
  int GetMonth() const {
      return month;
  }
  int GetDay() const {
      return day;
  }
 
 private:
  int year, month, day;
};

void ensure(istream &input, char expected) {
    const char actual = input.peek();
    if (actual != expected) {
        input.setstate(ios::failbit);
        throw exception();
    }
    input.ignore(1);
}
void ensure(istream &input) {
    if (!input) {
        throw exception();
    }
}

istream &operator>>(istream &input_, Date &date) {
    string input_string;
    input_ >> input_string;
    stringstream input(input_string);
    
    int year, month, day;
    try {
        ensure(input >> year);
        ensure(input, '-');
        ensure(input >> month);
        ensure(input, '-');
        ensure(input >> day);
        if (!input.eof()) {
            throw exception();
        }
    } catch (exception &ex) {
        stringstream error;
        error << "Wrong date format: " << input_string;
        throw runtime_error(error.str());
    }
    date = Date(year, month, day);
    
    return input_;
}

ostream &operator<<(ostream &output, const Date &date) {
    output << setfill('0');
    output << setw(4) << date.GetYear()
           << "-" << setw(2) << date.GetMonth()
           << "-" << setw(2) << date.GetDay();
    return output;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
        tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

class Database {
 public:
  void AddEvent(const Date &date, const string &event) {
      Date_to_events[date].insert(event);
  }
  bool DeleteEvent(const Date &date, const string &event) {
      if (Date_to_events.count(date) == 0
          || Date_to_events[date].count(event) == 0) {
          return false;
      }
      Date_to_events[date].erase(event);
      return true;
  }
  int DeleteDate(const Date &date) {
      if (Date_to_events.count(date) == 0) {
          return 0;
      }
      const auto count = Date_to_events[date].size();
      Date_to_events.erase(date);
      return count;
  }
  set<string> Find(const Date &date) const {
      if (Date_to_events.count(date)) {
          return Date_to_events.at(date);
      }
      return {};
  }
  void Print() const {
      for (auto &[date, events] :Date_to_events) {
          for (auto &event : events) {
              std::cout << date << " " << event << std::endl;
          }
      }
  }
  
  void Clear() {
      Date_to_events.clear();
  }
 
 private:
  map<Date, set<string>> Date_to_events;
};

int run() {
    txt();
    Database db;
    
    string command;
    bool safe_mode = true;
    while (getline(cin, command)) {
        stringstream command_stream(command);
        string operation_code;
        command_stream >> operation_code;

//        ====================
        if (operation_code == "Clear") {
            db.Clear();
            std::cout << std::endl;
            std::cout << "Cleared" << std::endl;
            continue;
        }
        if (operation_code == "//") {
            string comment;
            getline(command_stream, comment);
            std::cout << "//" << comment << std::endl;
            continue;
        }
//        ====================
        
        if (operation_code.empty()) {
            continue;
        }
        if (operation_code == "Add") {
            Date date;
            string event;
            command_stream >> date >> event;
            db.AddEvent(date, event);
        } else if (operation_code == "Del") {
            Date date;
            string event;
            command_stream >> date;
            
            if (command_stream.eof()) {
                const int deleted_count = db.DeleteDate(date);
                std::cout << "Deleted " << deleted_count << " events" << std::endl;
            } else {
                command_stream >> event;
                const bool success = db.DeleteEvent(date, event);
                if (success) {
                    std::cout << "Deleted successfully" << std::endl;
                } else {
                    std::cout << "Event not found" << std::endl;
                }
            }
        } else if (operation_code == "Find") {
            Date date;
            command_stream >> date;
            const set<string> events = db.Find(date);
            for (const auto &event : events) {
                std::cout << event << std::endl;
            }
        } else if (operation_code == "Print") {
            db.Print();
        } else {
            std::cout << "Unknown command: " << operation_code << std::endl;
        }
    }
    return 0;
}

int main() {
    try {
        return run();
    } catch (exception &ex) {
        std::cout << ex.what() << std::endl;
        exit(1);
    }
}

// ==================================
