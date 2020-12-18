#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "utilities.h"
#include "tests.h"

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================
#ifdef MASLO

void SendSms(const string &number, const string &message);
void SendEmail(const string &email, const string &message);

#endif

class INotifier {
 public:
  virtual void Notify(const string &message) = 0;
};

class SmsNotifier : public INotifier {
 public:
  SmsNotifier(const string &phone_number) : phone_number(phone_number) {}
  
  void Notify(const string &message) override {
      SendSms(phone_number, message);
  }
 
 private:
  const string phone_number;
};

class EmailNotifier : public INotifier {
 public:
  EmailNotifier(const string &email_address) : email_address(email_address) {}
  
  void Notify(const string &message) override {
      SendEmail(email_address, message);
  }
 
 private:
  const string email_address;
};

//int main() {
//
//    return 0;
//}
#ifdef MASLO

#include <iostream>
#include <string>

using namespace std;

void SendSms(const string &number, const string &message) {
    cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string &email, const string &message) {
    cout << "Send '" << message << "' to e-mail " << email << endl;
}

/*
 Реализуйте здесь классы INotifier, SmsNotifier, EmailNotifier
 */

void Notify(INotifier &notifier, const string &message) {
    notifier.Notify(message);
}


int main() {
    SmsNotifier sms{"+7-495-777-77-77"};
    EmailNotifier email{"na-derevnyu@dedushke.ru"};
    
    Notify(sms, "I have White belt in C++");
    Notify(email, "And want a Yellow one");
    return 0;
}

#endif


// ==========================================
