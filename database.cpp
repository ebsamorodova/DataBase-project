#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "database.h"
#include "test_runner.h"

using namespace std;

void Database::Add(const Date &date, const std::string& event) {
    std::string s = date.Str();
    auto &vec = data[s];
    if (vec.second.find(event) == vec.second.end()) {
        vec.first.push_back(event);
        vec.second.insert(event);
    }
}

std::vector<pair<std::string, std::string> > Database::FindIf(const std::function<bool(const Date&, const std::string&)> &predicate) const {
    std::vector<pair<std::string, std::string>> ans;
    for(auto &date : data) {
        for (auto &event : date.second.first) {
            if (predicate(date.first, event)) {
                ans.push_back(make_pair(date.first, event));
            }
        }
    }
    return ans;
}

int Database::RemoveIf(const std::function<bool(const Date&, const std::string&)> &predicate) {
    int removed = 0;
    for(auto &date : data) {
        vector<std::string> events;
        std::set<std::string> st;
        for (auto &event : date.second.first) {
            if (!predicate(date.first, event)) {
                events.push_back(event);
                st.insert(event);
            } else {
                removed++;
            }
        }
        date.second = {events, st};
    }

    map<std::string, pair<vector<std::string>, std::set<std::string>>> new_data;
    for (auto &date : data) {
        if (!date.second.first.empty()) {
            new_data[date.first] = date.second;
        }
    }
    data = new_data;

    return removed;
}

pair<std::string, std::string> Database::Last(const Date &d) const {
    auto it = data.upper_bound(d.Str());
    if (it == data.begin()) {
        throw std::invalid_argument("no events");
    } else {
        --it;
        return {it->first, (it->second).first.back()};
    }
}

void Database::Print(ostream& out) const {
    for (auto const &date : data) {
        for (auto &event : date.second.first) {
            out << date.first << " " << event << "\n";
        }
    }
}

std::ostream& operator << (std::ostream &out, const std::pair<std::string, std::string> &p) {
    out << p.first << " " << p.second;
    return out;
}
