#include "python_function.h"
#include <random>
#include <sstream>

std::string generateRandomString(size_t length = 8) {
  static const char charset[] = "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "0123456789";
  static std::mt19937 rng(std::random_device{}());
  static std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

  std::string result;
  for (size_t i = 0; i < length; ++i) {
    result += charset[dist(rng)];
  }
  return result;
}

std::string generateUniqueIdentifier(const std::string &prefix,
                                     size_t length = 8) {
  std::string id;
  while (true) {
    id = prefix + generateRandomString(length);
    std::string check_expr = "\"" + id + "\" in globals()";
    bool exists = py::eval(check_expr, py::globals()).cast<bool>();
    if (!exists)
      break;
  }
  return id;
}

std::vector<std::string> splitLines(const std::string &input) {
  std::vector<std::string> lines;
  std::istringstream stream(input);
  std::string line;
  while (std::getline(stream, line)) {
    lines.push_back(line);
  }
  return lines;
}

PythonFunction::PythonFunction(std::string definition)
    : definition(definition) {
  identifier = generateUniqueIdentifier("py_func_");

  std::string function_code = "def " + identifier + "():\n";
  for (const std::string &line : splitLines(definition)) {
    function_code += "    " + line + "\n";
  }

  py::exec(function_code);
}

PythonFunction::~PythonFunction() {
  std::string delete_code = "del " + identifier;
  py::exec(delete_code);
}
