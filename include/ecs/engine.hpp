#ifndef ECS_ENGINE_HPP_
#define ECS_ENGINE_HPP_

#include <memory>
#include <vector>

#include <ecs/frame_timer.hpp>
#include <ecs/system.hpp>

namespace ecs
{
// Engine owns, initializes, ticks, terminates the systems. 
class engine
{
public:
  engine()                    = default;
  engine(const engine&  that) = delete ;
  engine(      engine&& temp) = default;
  virtual ~engine()           = default;

  engine& operator=(const engine&  that) = delete ;
  engine& operator=(      engine&& temp) = default;
  
  template<typename system_type, typename... arguments_type>
  system_type* add_system   (arguments_type&&... arguments)
  {
    systems_.emplace_back(std::make_unique<system_type>(arguments...));
    auto& system = systems_.back();
    system->engine_ = this;
    return static_cast<system_type*>(system.get());
  }
  template<typename system_type>
  system_type* get_system   () const
  {
    auto system = std::find_if(systems_.begin(), systems_.end(), system_match_pred<system_type>);
    return system != systems_.end() ? static_cast<system_type*>(system->get()) : nullptr;
  }
  template<typename system_type>
  void         remove_system()
  {
    systems_.erase(std::remove_if(systems_.begin(), systems_.end(), system_match_pred<system_type>), systems_.end());
  }

  void start()
  {
    is_running_ = true;
    
    for(auto& system : systems_)
      system->initialize();

    frame_timer_.tick();
    while(is_running_)
    {
      frame_timer_.tick();
      for (auto& system : systems_)
        system->tick();
    }
    
    for (auto& system : systems_)
      system->terminate();
  }
  void stop ()
  {
    is_running_ = false;
  }

protected:
  template<typename system_type>
  static bool system_match_pred(const std::unique_ptr<system>& iteratee) 
  {
    return typeid(system_type) == typeid(*iteratee.get());
  }

  std::vector<std::unique_ptr<system>> systems_    ;
  frame_timer<>                        frame_timer_;
  bool                                 is_running_ = false;
};
}

#endif
