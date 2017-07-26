#ifndef ECS_SCENE_HPP_
#define ECS_SCENE_HPP_

#include <vector>

#include <ecs/core/entity.hpp>

namespace ecs
{
class scene
{
public:
  scene()                   = default;
  scene(const scene&  that) = default;
  scene(      scene&& temp) = default;
  virtual ~scene()          = default;

  scene& operator=(const scene&  that) = default;
  scene& operator=(      scene&& temp) = default;

protected:
  std::vector<entity> entities_;
  
};
}

#endif
