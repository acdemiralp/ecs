#ifndef ECS_COMPONENT_HPP_
#define ECS_COMPONENT_HPP_

namespace ecs
{
class component
{
public:
  component()                       = default;
  component(const component&  that) = default;
  component(      component&& temp) = default;
  virtual ~component()              = default;

  component& operator=(const component&  that) = default;
  component& operator=(      component&& temp) = default;

protected:

};
}

#endif
