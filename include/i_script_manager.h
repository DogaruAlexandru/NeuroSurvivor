#pragma once
#include <i_function.h>
#include <memory>

class IScriptManager
{
public:
  virtual ~IScriptManager() = default;
  virtual std::shared_ptr<IFunction> addFunction(std::string definition) = 0;
};
