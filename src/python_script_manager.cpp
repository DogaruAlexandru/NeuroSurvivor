#include "game.h"
#include <memory>
#include <python_function.h>
#include <python_script_manager.h>

PYBIND11_EMBEDDED_MODULE(game_api, m)
{
  py::class_<Entity>(m, "Entity")
      .def(py::init<double, double, double, double, double, double, double,
                    double, double>())
      .def("is_alive", &Entity::isAlive)
      .def("get_health", &Entity::getHealth)
      .def("get_max_health", &Entity::getMaxHealth)
      .def("set_health", &Entity::setHealth)
      .def("set_max_health", &Entity::setMaxHealth);

  py::class_<GameAPI>(m, "GameAPI")
      .def(py::init([](py::capsule game_capsule)
                    { return new GameAPI(static_cast<Game *>(game_capsule.get_pointer())); }))
      .def("get_player", &GameAPI::getPlayer,
           py::return_value_policy::reference);
}

PythonScriptManager::PythonScriptManager(Game *game) : game(game)
{
  py::capsule game_capsule(static_cast<void *>(game), "game_pointer");
  py::module_ gameModule = py::module_::import("game_api");

  py::dict global_namespace = py::globals();
  global_namespace["game"] = gameModule.attr("GameAPI")(game_capsule);
}

std::shared_ptr<IFunction>
PythonScriptManager::addFunction(std::string definition)
{
  return std::make_shared<PythonFunction>(definition);
}
