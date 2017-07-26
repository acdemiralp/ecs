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

    void update() override
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

  class mesh      : public ecs::component {};
  class material  : public ecs::component {};
  class collider  : public ecs::component {};
  class rigidbody : public ecs::component {};

  typedef ecs::registry<ecs::entity, mesh, material, collider, rigidbody> registry;

  ecs::registry<ecs::entity, mesh, material, collider, rigidbody> registry_instance;
  registry_instance.resize(4096);
  const auto& entities    = registry_instance.access<ecs::entity>();
  const auto& meshes      = registry_instance.access<mesh>       ();
  const auto& materials   = registry_instance.access<material>   ();
  const auto& colliders   = registry_instance.access<collider>   ();
  const auto& rigidbodies = registry_instance.access<rigidbody>  ();
  entities   [0];
  entities   [0];
  entities   [0];
  entities   [0];
  entities   [0];
  meshes     [0];
  meshes     [0];
  meshes     [0];
  meshes     [0];
  materials  [0];
  materials  [0];
  materials  [0];
  colliders  [0];
  colliders  [0];
  rigidbodies[0];

  engine.start();
}