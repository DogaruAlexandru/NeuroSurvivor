#pragma once

#include "i_function.h"
#include <pybind11/embed.h>
#include <pybind11/eval.h>
#include <pybind11/pytypes.h>
#include <string>

namespace py = pybind11;
class PythonFunction : public IFunction
{
public:
  PythonFunction(std::string definition);

  ~PythonFunction() override;

  std::string getIdentifier() override { return identifier; }
  std::string getDefinition() override { return definition; }
  void execute() override { py::exec(identifier + "()"); }

private:
  std::string identifier;
  std::string definition;
};
