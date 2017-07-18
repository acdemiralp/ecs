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
  auto& entities    = registry_instance.access<ecs::entity>();
  auto& meshes      = registry_instance.access<mesh>       ();
  auto& materials   = registry_instance.access<material>   ();
  auto& colliders   = registry_instance.access<collider>   ();
  auto& rigidbodies = registry_instance.access<rigidbody>  ();
  entities   .add();
  entities   .add();
  entities   .add();
  entities   .add();
  entities   .add();
  meshes     .add();
  meshes     .add();
  meshes     .add();
  meshes     .add();
  materials  .add();
  materials  .add();
  materials  .add();
  colliders  .add();
  colliders  .add();
  rigidbodies.add();

  ecs::resource<float> resource;
  auto handle  = resource.add(1);
  auto handle2 = resource.add(2);
  auto handle3 = resource.add(3);
  auto handle4 = resource.add(4);
  handle2.remove();
  auto handle22 = handle2.get();
  for(auto& res : resource)
    std::cout << res.second << std::endl;

  engine.start();
}