#ifndef ECS_SYSTEM_HPP_
#define ECS_SYSTEM_HPP_

namespace ecs
{
class engine;

class system
{
public:
  system()                    = default;
  system(const system&  that) = default;
  system(      system&& temp) = default;
  virtual ~system()           = default;

  system& operator=(const system&  that) = default;
  system& operator=(      system&& temp) = default;

  const engine* owner() const
  {
    return owner_;
  }

protected:
  friend engine;

  virtual void initialize() { }
  virtual void update    () { }
  virtual void terminate () { }

  const engine* owner_;
};
}

#endif
