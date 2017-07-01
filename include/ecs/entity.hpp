#ifndef ECS_ENTITY_HPP_
#define ECS_ENTITY_HPP_

#include <boost/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <ecs/named.hpp>

namespace ecs
{
class entity final : public named
{
public:
  using named::named;

  entity()                    = default;
  entity(const entity&  that) = default;
  entity(      entity&& temp) = default;
 ~entity()                    = default;

  entity& operator=(const entity&  that) = default;
  entity& operator=(      entity&& temp) = default;

protected:
  std::size_t             id_            ;
  boost::dynamic_bitset<> component_mask_;
};
}

#endif
