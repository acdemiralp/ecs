#ifndef ECS_ENTITY_HPP_
#define ECS_ENTITY_HPP_

#include <memory>
#include <vector>

#include <ecs/named.hpp>

namespace ecs
{
class entity : public named
{
public:
  using named::named;

  entity()                    = default;
  entity(const entity&  that) = default;
  entity(      entity&& temp) = default;
  virtual ~entity()           = default;

  entity& operator=(const entity&  that) = default;
  entity& operator=(      entity&& temp) = default;

  template<typename component_type, typename... arguments_type>
  component_type*                 add_component   (arguments_type&&... arguments)
  {
    
  }
  template<typename component_type>
  component_type*                 get_component   (std::size_t index = 0)
  {
    
  }
  template<typename component_type>
  std::unique_ptr<component_type> remove_component(std::size_t index = 0)
  {
    
  }

protected:
  std::vector<std::unique_ptr<component>> components_;
};
}

#endif
