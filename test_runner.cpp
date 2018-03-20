#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "test_runner.h"

using namespace std;

void Assert(bool b, const std::string& hint) {
  AssertEqual(b, true, hint);
}
