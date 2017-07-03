#ifndef ECS_REGISTRY_HPP_
#define ECS_REGISTRY_HPP_

#include <tuple>
#include <type_traits>
#include <vector>

namespace ecs
{
// Registry is a compile-time defined container of multiple vectors of different types.
template<typename... types>
class registry final
{
public:
  template<typename type>
  std::vector<type>& access()
  {
    return matching_vector<0, type, resource_vectors, vector_of_type<0, type>::value>::get(resource_vectors_);
  }

private:
  typedef std::tuple<std::vector<types>...> resource_vectors;

  template<int index, typename type>
  struct vector_of_type : std::is_same<type, typename std::tuple_element<index, resource_vectors>::type::value_type>
  {
    
  };
  template<int index, typename type, typename tuple, bool match = false>
  struct matching_vector
  {
    static std::vector<type>& get(tuple& value)
    {
      return matching_vector<index + 1, type, tuple, vector_of_type<index + 1, type>::value>::get(value);
    }
  };
  template<int index, typename type, typename tuple>
  struct matching_vector<index, type, tuple, true>
  {
    static std::vector<type>& get(tuple& value)
    {
      return std::get<index>(value);
    }
  };

  resource_vectors resource_vectors_;
};
}

#endif
