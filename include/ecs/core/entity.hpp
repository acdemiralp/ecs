#ifndef ECS_ENTITY_HPP_
#define ECS_ENTITY_HPP_

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>

#include <ecs/core/component.hpp>

namespace ecs
{
class scene;

class entity
{
public:
  entity()                    = default;
  entity(const entity&  that)
  {
    owner_ = that.owner_;
    for (auto& component : that.components_)
      copy_component(*component);
  }
  entity(      entity&& temp) = default;
 ~entity()                    = default;

  entity& operator=(const entity&  that)
  {
    owner_ = that.owner_;
    for (auto& component : that.components_)
      copy_component(*component);
    return *this;
  }
  entity& operator=(      entity&& temp) = default;

  const scene* owner() const
  {
    return owner_;
  }

  template <typename component_type, typename... component_arguments>
  component_type* add_component   (component_arguments&&... arguments)
  {
    static_assert(std::is_base_of<component, component_type>::value, "The type does not inherit from component.");
    auto component = std::make_unique<component_type>(arguments...);
    component->owner_ = this;
    components_.push_back(std::move(component));
    return static_cast<component_type*>(components_.back().get());
  }
  template <typename component_type>
  component_type* copy_component  (const component_type& component)
  {
    return add_component<component_type>(component);
  }
  template <typename component_type>
  component_type* get_component   () const
  {
    static_assert(std::is_base_of<component, component_type>::value, "The type does not inherit from component.");
    auto   iterator = std::find_if(components_.begin(), components_.end(), component_match_predicate<component_type>);
    return iterator != components_.end() ? static_cast<component_type*>(iterator->get()) : nullptr;
  }
  template <typename component_type>
  void            remove_component()
  {
    static_assert(std::is_base_of<component, component_type>::value, "The type does not inherit from component.");
    components_.erase(std::remove_if(components_.begin(), components_.end(), component_match_predicate<component_type>), components_.end());
  }

private:
  friend scene;

  template<typename component_type>
  static bool component_match_predicate(const std::unique_ptr<component>& iteratee)
  {
    return typeid(component_type) == typeid(*iteratee.get());
  }

  const scene*                            owner_     = nullptr;
  std::vector<std::unique_ptr<component>> components_;
};
}

#endif
