#include "catch.hpp"

#include <ecs/all.hpp>

TEST_CASE("Engine is tested", "[engine]") {
  class renderer final : public ecs::system
  {
  public:
    explicit renderer(const std::string parameter) : parameter_(parameter)
    {
      
    }

  private:
    std::string parameter_;
  };
  class physics  final : public ecs::system
  {
  public:
    explicit physics(const std::string parameter) : parameter_(parameter)
    {

    }

    void tick() override
    {
      engine_->stop();
    }

  private:
    std::string parameter_;
  };

  ecs::engine engine;

  auto renderer_ptr   = engine.add_system<renderer>("Test Renderer");
  auto physics_ptr    = engine.add_system<physics> ("Test Physics" );
  auto renderer_ptr_2 = engine.get_system<renderer>();
  auto physics_ptr_2  = engine.get_system<physics> ();
  REQUIRE(renderer_ptr == renderer_ptr_2);
  REQUIRE(physics_ptr  == physics_ptr_2 );

  engine.remove_system<renderer>();
  auto renderer_ptr_3 = engine.get_system<renderer>();
  auto physics_ptr_3  = engine.get_system<physics> ();
  REQUIRE(renderer_ptr_3 == nullptr      );
  REQUIRE(physics_ptr    == physics_ptr_3);

  engine.start();
}