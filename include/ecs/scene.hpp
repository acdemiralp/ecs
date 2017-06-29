#ifndef ECS_SCENE_HPP_
#define ECS_SCENE_HPP_

#include <boost/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>

namespace ecs
{
// Scene owns and keeps track of the components of entities.
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
  std::vector<std::pair<entity, boost::dynamic_bitset<>>> entities_;
};
}

#endif
