#ifndef ECS_COMPONENT_CHECK_HPP_
#define ECS_COMPONENT_CHECK_HPP_

#include <ecs/core/entity.hpp>

namespace ecs
{
template <typename... components>
struct component_check
{
  
};
template <>
struct component_check<>
{
  static bool check(entity* entity)
  {
    return true;
  }
};
template <typename head, typename... tail>
struct component_check<head, tail...> 
{
  static bool check(entity* entity) 
  {
    return entity->get_component<head>() && component_check<tail...>::check(entity);
  }
};
}

#endif
