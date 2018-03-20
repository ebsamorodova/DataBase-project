#include <iostream>
#include <string>
#include "date.h"
#include "node.h"
#include "test_runner.h"

bool DateComparisonNode::Evaluate(const Date &d, const std::string &event) const {
    if (cmp == Comparison::Less) {
        return d < date;
    } else if (cmp == Comparison::LessOrEqual) {
        return d <= date;
    } else if (cmp == Comparison::Greater) {
        return d > date;
    } else if (cmp == Comparison::GreaterOrEqual) {
        return d >= date;
    } else if (cmp == Comparison::Equal) {
        return d == date;
    } else {
        return d != date;
    }
}

bool EventComparisonNode::Evaluate(const Date &d, const std::string &event) const {
    if (cmp == Comparison::Equal) {
        return (event == _event);
    } else if (cmp == Comparison::NotEqual){
        return (event != _event);
    } else if (cmp == Comparison::Less) {
        return (event < _event);
    } else if (cmp == Comparison::LessOrEqual) {
        return (event <= _event);
    } else if (cmp == Comparison::Greater) {
        return (event > _event);
    } else {
        return (event >= _event);
    }
}


bool LogicalOperationNode::Evaluate(const Date &d, const std::string &event) const {
    if (op == LogicalOperation::And) {
        return first->Evaluate(d, event) && second->Evaluate(d, event);
    } else if (op == LogicalOperation::Or) {
        return first->Evaluate(d, event) || second->Evaluate(d, event);
    } else {
        throw std::logic_error("Unexpected logical operation");
    }
}
