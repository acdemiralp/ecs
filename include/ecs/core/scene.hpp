#ifndef ECS_SCENE_HPP_
#define ECS_SCENE_HPP_

#include <ecs/utility/registry.hpp>

namespace ecs
{
class scene final
{
public:
  template<typename... argument_types>
  entity* add_entity(argument_types&&... arguments)
  {
    return nullptr;
  }
  entity* get_entity   (const std::size_t& index)
  {
    return nullptr;
  }
  void    remove_entity(const std::size_t& index)
  {
    
  }

  void    serialize    (const std::string& filepath)
  {
    
  }
  void    deserialize  (const std::string& filepath)
  {
    
  }

private:
  registry<ecs::entity> entity_registry_;
};
}

#endif
