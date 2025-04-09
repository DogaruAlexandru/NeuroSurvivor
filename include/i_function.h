#pragma once
#include <string>

class IFunction
{
public:
  virtual ~IFunction() = default;
  virtual std::string getIdentifier() = 0;
  virtual std::string getDefinition() = 0;
  virtual void execute() = 0;
};
