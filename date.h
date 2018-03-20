#pragma once
#include <string>

bool IsCorrectMonth(const int &month);

bool IsCorrectDay(const int &day);

class Date {
private:
    int year;
    int month;
    int day;
    std::string str_date;
public:

    Date(const std::string &date);

    Date(int x, int y, int z);

    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
    std::string Str() const {
        return str_date;
    }
};

enum class LogicalOperation {
    And,
    Or,
    Not,
};

std::ostream& operator << (std::ostream& out, const Date &d);

Date ParseDate(std::istream& is);


bool operator < (const Date& lhs, const Date& rhs);
bool operator <= (const Date &lhs, const Date& rhs);
bool operator > (const Date &lhs, const Date& rhs);
bool operator >= (const Date &lhs, const Date& rhs);
bool operator == (const Date &lhs, const Date& rhs);
bool operator != (const Date &lhs, const Date& rhs);
