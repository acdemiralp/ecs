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

  virtual void initialize () {}
  virtual void tick       () {}
  virtual void terminate  () {}

protected:
  friend engine;
  engine* engine_;
};
}

#endif
