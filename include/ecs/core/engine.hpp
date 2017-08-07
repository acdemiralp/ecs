#ifndef ECS_ENGINE_HPP_
#define ECS_ENGINE_HPP_

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>

#include <ecs/core/scene.hpp>
#include <ecs/core/system.hpp>
#include <ecs/utility/frame_timer.hpp>

namespace ecs
{
// Engine owns, initializes, updates, terminates the systems over a scene and tracks the time between two updates.
class engine final
{
public:
  engine() : scene_(std::make_unique<scene>())
  {
    scene_->owner_ = this;
  }
  engine(const engine&  that) = delete ;
  engine(      engine&& temp) = default;
 ~engine()                    = default;

  engine& operator=(const engine&  that) = delete ;
  engine& operator=(      engine&& temp) = default;
  
  void   set_scene(std::unique_ptr<scene> scene)
  {
    scene_ = std::move(scene);
    scene_->owner_ = this;
  }
  scene* get_scene() const
  {
    return scene_.get();
  }

  template<typename system_type, typename... arguments_type>
  system_type* add_system   (arguments_type&&... arguments)
  {
    static_assert(std::is_base_of<system, system_type>::value, "The type does not inherit from system.");
    auto system = std::make_unique<system_type>(arguments...);
    system->owner_ = this;
    systems_.push_back(std::move(system));
    return static_cast<system_type*>(systems_.back().get());
  }
  template<typename system_type>
  system_type* get_system   () const
  {
    static_assert(std::is_base_of<system, system_type>::value, "The type does not inherit from system.");
    auto   system = std::find_if(systems_.begin(), systems_.end(), system_match_predicate<system_type>);
    return system != systems_.end() ? static_cast<system_type*>(system->get()) : nullptr;
  }
  template<typename system_type>
  void         remove_system()
  {
    static_assert(std::is_base_of<system, system_type>::value, "The type does not inherit from system.");
    systems_.erase(std::remove_if(systems_.begin(), systems_.end(), system_match_predicate<system_type>), systems_.end());
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
        system->update();
    }
    
    for (auto& system : systems_)
      system->terminate();
  }
  void stop ()
  {
    is_running_ = false;
  }

private:
  template<typename system_type>
  static bool system_match_predicate(const std::unique_ptr<system>& iteratee) 
  {
    return typeid(system_type) == typeid(*iteratee.get());
  }

  std::unique_ptr<scene>               scene_      ;
  std::vector<std::unique_ptr<system>> systems_    ;
  frame_timer<double, std::milli>      frame_timer_;
  bool                                 is_running_ = false;
};
}

#endif
