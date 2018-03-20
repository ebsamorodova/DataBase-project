#pragma once

#include <memory>
#include <string>
#include <stdexcept>
#include "date.h"

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

struct Node {
    Node() {}
    virtual bool Evaluate(const Date &date, const std::string &event)  const = 0;
};

struct EmptyNode : Node {
    EmptyNode() {}

    bool Evaluate(const Date &d, const std::string &event) const { return true; }
};

struct DateComparisonNode : public Node {
    Comparison cmp;
    Date date;
    DateComparisonNode(const Comparison &cmp_, const Date &date_) : cmp(cmp_), date(date_) {}

    bool Evaluate(const Date &d, const std::string &event) const;
};

struct EventComparisonNode : public Node {
    Comparison cmp;
    const std::string _event;
    EventComparisonNode(const Comparison &cmp_, const std::string &event_) : cmp(cmp_), _event(event_) {}

    bool Evaluate(const Date &d, const std::string &event) const;
};

struct LogicalOperationNode : public Node {
    LogicalOperation op;
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> second;

    LogicalOperationNode(const LogicalOperation &op_, const std::shared_ptr<Node> first_, const std::shared_ptr<Node> second_) :  op(op_), first(first_), second(second_) {}

    bool Evaluate(const Date &d, const std::string &event) const;
};
