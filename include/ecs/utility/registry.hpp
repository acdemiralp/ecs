#ifndef ECS_REGISTRY_HPP_
#define ECS_REGISTRY_HPP_

#include <tuple>
#include <type_traits>

#include <ecs/utility/resource.hpp>

namespace ecs
{
// Registry is a compile-time defined container of multiple vectors of different types.
template<typename... types>
class registry final
{
public:
  template<typename type>
  resource<type>& access()
  {
    return matching_resource<0, type, resources, resource_of_type<0, type>::value>::get(resources_);
  }

private:
  typedef std::tuple<resource<types>...> resources;

  template<int index, typename type>
  struct resource_of_type : std::is_same<type, typename std::tuple_element<index, resources>::type::value_type>
  {
    
  };
  template<int index, typename type, typename tuple, bool match = false>
  struct matching_resource
  {
    static resource<type>& get(tuple& value)
    {
      return matching_resource<index + 1, type, tuple, resource_of_type<index + 1, type>::value>::get(value);
    }
  };
  template<int index, typename type, typename tuple>
  struct matching_resource<index, type, tuple, true>
  {
    static resource<type>& get(tuple& value)
    {
      return std::get<index>(value);
    }
  };

  resources resources_;
};
}

#endif
