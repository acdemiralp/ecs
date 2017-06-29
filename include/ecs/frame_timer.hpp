#ifndef ECS_FRAME_TIMER_HPP_
#define ECS_FRAME_TIMER_HPP_

#include <chrono>

namespace ecs
{
// Frame timer keeps track of time and the delta between two consecutive calls to tick().
template<typename representation = double, typename precision = std::milli>
class frame_timer final
{
public:
  using clock      = std::chrono::high_resolution_clock;
  using duration   = std::chrono::duration<representation, precision>;
  using time_point = std::chrono::time_point<clock, duration>;

  void tick()
  {
    delta_time_ = clock::now() - time_;
    time_ += delta_time_;
  }

  duration   delta_time() const
  {
    return delta_time_;
  }
  time_point time      () const
  {
    return time_;
  }

private:
  duration   delta_time_;
  time_point time_      ;
};
}

#endif