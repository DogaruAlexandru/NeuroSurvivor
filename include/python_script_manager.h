#pragma once

#include <game_api.h>
#include <i_script_manager.h>
#include <memory>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

namespace py = pybind11;
class PythonScriptManager : public IScriptManager
{
public:
  PythonScriptManager(Game *game);
  ~PythonScriptManager() override = default;

  std::shared_ptr<IFunction> addFunction(std::string definition) override;

private:
  Game *game;
  py::scoped_interpreter interpreter;
};
