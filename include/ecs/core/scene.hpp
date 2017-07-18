#ifndef ECS_SCENE_HPP_
#define ECS_SCENE_HPP_

#include <ecs/utility/resource.hpp>

namespace ecs
{
class scene final
{
public:
  template<typename... argument_types>
  resource<entity>::handle add_entity   (argument_types&&...             arguments)
  {
    return entities_.add(arguments...);
  }
  void                     remove_entity(const resource<entity>::handle& handle   )
  {
    entities_.remove(handle);
  }

private:
  resource<ecs::entity> entities_;
};
}

#endif
