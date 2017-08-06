#ifndef ECS_SCENE_HPP_
#define ECS_SCENE_HPP_

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>

#include <ecs/core/entity.hpp>

namespace ecs
{
class engine;

class scene
{
public:
  scene()                   = default;
  scene(const scene&  that)
  {
    owner_ = that.owner_;
    for (auto& entity : that.entities_)
      add_entity(*entity);
  }
  scene(      scene&& temp) = default;
  virtual ~scene()          = default;

  scene& operator=(const scene&  that)
  {
    owner_ = that.owner_;
    for (auto& entity : that.entities_)
      add_entity(*entity);
    return *this;
  }
  scene& operator=(      scene&& temp) = default;

  const engine* owner() const
  {
    return owner_;
  }

  template<typename... entity_arguments>
  entity* add_entity   (entity_arguments&&... arguments)
  {
    auto entity = std::make_unique<ecs::entity>(arguments...);
    entity->owner_ = this;
    entities_.push_back(std::move(entity));
    return entities_.back().get();
  }
  entity* get_entity   (std::size_t           index    ) const
  {
    return index < entities_.size() ? entities_[index].get() : nullptr;
  }
  void    remove_entity(entity*               entity   )
  {
    entities_.erase(std::remove_if(
      entities_.begin(), 
      entities_.end  (),
      [&entity](const std::unique_ptr<ecs::entity>& iteratee)
      {
        return iteratee.get() == entity;
      }), 
      entities_.end  ());
  }

  std::vector<entity*> entities() const
  {
    std::vector<entity*> entities(entities_.size());
    std::transform(
      entities_.begin(), 
      entities_.end  (), 
      entities .begin(),
      [] (const std::unique_ptr<entity>& iteratee)
      {
        return iteratee.get();
      });
    return entities;
  }

protected:
  friend engine;

  const engine*                        owner_   = nullptr;
  std::vector<std::unique_ptr<entity>> entities_;
};
}

#endif
