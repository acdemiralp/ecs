#ifndef ECS_NAMED_HPP_
#define ECS_NAMED_HPP_

#include <string>

namespace ecs
{
// Aspect representing the named nature of the deriving type.
class named
{
public:
  explicit named(const std::string& name = "") : name_(name) { }

  const std::string& name    () const                  { return name_; }
  void               set_name(const std::string& name) { name_ = name; }

protected:
  std::string name_;
};
}

#endif
