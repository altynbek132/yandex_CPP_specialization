//
// Created by Addmin on 11.12.2020.
//

#include <sstream>
//#include "utilities.h"
#include "phone_number.h"

void ensure2(std::istream &input, char expected) {
    const char actual = input.peek();
    if (actual != expected) {
        input.setstate(std::ios::failbit);
        throw std::exception();
    }
    input.ignore(1);
}

void ensure2(std::istream &input) {
    if (!input) {
        throw std::exception();
    }
}




PhoneNumber::PhoneNumber(const string &international_number) {
    std::stringstream ss(international_number);
    try {
        ensure2(ss, '+');
        ensure2(getline(ss, country_code_, '-'));
        ensure2(ss);
        ensure2(getline(ss, city_code_, '-'));
        ensure2(ss);
        ensure2(getline(ss, local_number_));
    } catch (exception &ex) {
        stringstream error;
        error << "invalid format of international number: " << international_number;
        throw invalid_argument(error.str());
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    std::stringstream ss;
    ss << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
    return ss.str();
}
