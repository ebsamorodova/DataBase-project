#include <iostream>
#include <stdexcept>
#include "date.h"

bool IsCorrectMonth(const int &month) {
    return month >= 1 && month <= 12;
}

bool IsCorrectDay(const int &day) {
    return day >= 1 && day <= 31;
}

std::ostream& operator << (std::ostream& out, const Date &d) {
    out << d.Str();
    return out;
}

std::string IsCorrectDate(const int d, const int m) {
    if (!IsCorrectMonth(m)) {
        return "Month value is invalid: " + std::to_string(m);
    }
    if (!IsCorrectDay(d)) {
        return "Day value is invalid: " + std::to_string(d);
    }
    return "OK";
}

bool IsCorrectFormat(const std::string &s) {
    int first_dash = -1, second_dash = -1;
    size_t i = 0;
    while (i < s.size()) {
        if (!(('0' <= s[i] && s[i] <= '9') || s[i] == '-'))
            return false;
        if (s[i] == '-') {
            if (first_dash < 0) {
                first_dash = i;
            } else if (second_dash < 0) {
                second_dash = i;
            } else {
                return false;
            }
        }
        ++i;
    }
    if (first_dash < 0 || second_dash < 0) {
        return false;
    } else {
        return (first_dash != 0 && (second_dash + 1) != s.size() && (second_dash - first_dash > 1));
    }
}

Date::Date(int x, int y, int z) {
    std::string year_ = "";
    int n = 1000;
    while (x < n) {
        year_ += "0";
        n /= 10;
    }
    year_ += std::to_string(x);
    std::string month_ = ((y < 10) ? "0" : "") + std::to_string(y);
    std::string day_ = ((z < 10) ? "0" : "") + std::to_string(z);

    str_date = year_ + "-" + month_ + "-" + day_;
    year = x;
    month = y;
    day = z;
}

Date::Date(const std::string &date) {
    std::string cp = date;
    if (!IsCorrectFormat(cp)) {
        throw std::runtime_error("Wrong date format: " + date);
    }
    int y = 0;
    size_t i = 0;
    while (cp[i] != '-') {
        y = y * 10 + (cp[i] - '0');
        i++;
    }
    int _year = y;
    i++;
    y = 0;
    while (cp[i] != '-') {
        y = y * 10 + (cp[i] - '0');
        i++;
    }
    int _month = y;
    i++;
    y = 0;
    while (i != cp.size()) {
        y = y * 10 + (cp[i] - '0');
        i++;
    }
    int _day = y;
    std::string res = IsCorrectDate(_day, _month);
    if (res != "OK") {
        throw std::runtime_error(res);
    }
    str_date = "";
    int x = 1000;
    while (_year < x) {
        str_date += "0";
        x /= 10;
    }
    if (x != 0)
        str_date += std::to_string(_year);
    str_date += "-";
    if (_month < 10) {
        str_date += "0";
    }
    str_date += std::to_string(_month) + "-";
    if (_day < 10) {
        str_date += "0";
    }
    str_date += std::to_string(_day);
    year = _year;
    month = _month;
    day = _day;
}

bool operator == (const Date &lhs, const Date &rhs) {
    return (lhs.GetDay() == rhs.GetDay() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetYear() == rhs.GetYear());
}

bool operator != (const Date &lhs, const Date &rhs) {
    return (!(lhs == rhs));
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    }
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() < rhs.GetMonth()) {
            return true;
        } else if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        } else {
            return false;
        }
    }
    return false;
}

Date ParseDate(std::istream& is) {
    std::string d;
    is >> d;
    return Date(d);
}

bool operator <= (const Date &lhs, const Date &rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator > (const Date &lhs, const Date &rhs) {
    return (!(lhs <= rhs));
}

bool operator >= (const Date &lhs, const Date &rhs) {
    return (!(lhs < rhs));
}
