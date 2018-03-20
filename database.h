#pragma once

#include <algorithm>
#include <functional>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include "date.h"

class Database {
private:
    std::map<std::string, std::pair<std::vector<std::string>, std::set<std::string> > > data;
public:
    void Add(const Date &date, const std::string &event);
    int DeleteDate(const Date& date);

    std::vector<std::pair<std::string, std::string> > FindIf(const std::function<bool(const Date&, const std::string&)> &predicate) const;

    int RemoveIf(const std::function<bool(const Date&, const std::string&)> &predicate);

    std::pair<std::string, std::string> Last(const Date &d) const;

    void Print(std::ostream& out) const;
};

std::ostream& operator << (std::ostream &out, const std::pair<std::string, std::string> &p);
