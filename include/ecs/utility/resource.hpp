#ifndef ECS_RESOURCE_HPP_
#define ECS_RESOURCE_HPP_

#include <vector>

#include <boost/pool/object_pool.hpp>

namespace ecs
{
template <typename type>
class resource
{
public:
  explicit resource(std::size_t next_size = 1024) : object_pool_(next_size)
  {
    
  }
  resource(const resource&  that)            = default;
  resource(      resource&& temp)            = default;
 ~resource()                                 = default;

  resource& operator=(const resource&  that) = default;
  resource& operator=(      resource&& temp) = default;

  template<typename... constructor_arguments>
  type* add(constructor_arguments&&... arguments)
  {
    object_pool_.construct()
  }

protected:
  boost::object_pool<type> object_pool_;
  std::vector<type*>       object_ptrs_;
};
}

#endif
