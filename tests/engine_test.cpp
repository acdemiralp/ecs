#include "catch.hpp"

#include <ecs/core/engine.hpp>

TEST_CASE("Engine is tested.", "[engine]") {
  ecs::engine engine;

  // System tests.
  class system_1 : public ecs::system { };
  class system_2 : public ecs::system { };
  class system_3 : public ecs::system { };
  class system_4 : public ecs::system { };

  auto system_1_ref_1 = engine.add_system<system_1>();
  auto system_2_ref_1 = engine.add_system<system_2>();
  auto system_3_ref_1 = engine.add_system<system_3>();
  auto system_4_ref_1 = engine.add_system<system_4>();

  REQUIRE(system_1_ref_1->owner() == &engine);
  REQUIRE(system_2_ref_1->owner() == &engine);
  REQUIRE(system_3_ref_1->owner() == &engine);
  REQUIRE(system_4_ref_1->owner() == &engine);

  auto system_1_ref_2 = engine.get_system<system_1>();
  auto system_2_ref_2 = engine.get_system<system_2>();
  auto system_3_ref_2 = engine.get_system<system_3>();
  auto system_4_ref_2 = engine.get_system<system_4>();

  REQUIRE(system_1_ref_1 == system_1_ref_2);
  REQUIRE(system_2_ref_1 == system_2_ref_2);
  REQUIRE(system_3_ref_1 == system_3_ref_2);
  REQUIRE(system_4_ref_1 == system_4_ref_2);

  engine.remove_system<system_4>();
  
  auto system_1_ref_3 = engine.get_system<system_1>();
  auto system_2_ref_3 = engine.get_system<system_2>();
  auto system_3_ref_3 = engine.get_system<system_3>();
  auto system_4_ref_3 = engine.get_system<system_4>();

  REQUIRE(system_1_ref_1 == system_1_ref_3);
  REQUIRE(system_2_ref_1 == system_2_ref_3);
  REQUIRE(system_3_ref_1 == system_3_ref_3);
  REQUIRE(nullptr        == system_4_ref_3);

  // Scene tests.
  auto scene = engine.get_scene();

  REQUIRE(scene->owner() == &engine);

  auto entity_1_ref_1 = scene->add_entity();
  auto entity_2_ref_1 = scene->add_entity();
  auto entity_3_ref_1 = scene->add_entity();
  auto entity_4_ref_1 = scene->add_entity();

  REQUIRE(entity_1_ref_1->owner() == scene);
  REQUIRE(entity_2_ref_1->owner() == scene);
  REQUIRE(entity_3_ref_1->owner() == scene);
  REQUIRE(entity_4_ref_1->owner() == scene);

  auto entity_1_ref_2 = scene->get_entity(0);
  auto entity_2_ref_2 = scene->get_entity(1);
  auto entity_3_ref_2 = scene->get_entity(2);
  auto entity_4_ref_2 = scene->get_entity(3);
  
  REQUIRE(entity_1_ref_1 == entity_1_ref_2);
  REQUIRE(entity_2_ref_1 == entity_2_ref_2);
  REQUIRE(entity_3_ref_1 == entity_3_ref_2);
  REQUIRE(entity_4_ref_1 == entity_4_ref_2);

  scene->remove_entity(entity_4_ref_1);
  
  auto entity_1_ref_3 = scene->get_entity(0);
  auto entity_2_ref_3 = scene->get_entity(1);
  auto entity_3_ref_3 = scene->get_entity(2);
  auto entity_4_ref_3 = scene->get_entity(3);

  REQUIRE(entity_1_ref_1 == entity_1_ref_3);
  REQUIRE(entity_2_ref_1 == entity_2_ref_3);
  REQUIRE(entity_3_ref_1 == entity_3_ref_3);
  REQUIRE(nullptr        == entity_4_ref_3);

  // Entity tests.
  class component_1 : public ecs::component { };
  class component_2 : public ecs::component { };
  class component_3 : public ecs::component { };

  auto component_1_ref_1 = entity_1_ref_1->add_component<component_1>();
  auto component_2_ref_1 = entity_2_ref_2->add_component<component_2>();
  auto component_3_ref_1 = entity_3_ref_3->add_component<component_3>();
  
  REQUIRE(component_1_ref_1->owner() == entity_1_ref_1);
  REQUIRE(component_2_ref_1->owner() == entity_2_ref_2);
  REQUIRE(component_3_ref_1->owner() == entity_3_ref_3);

  auto component_1_ref_2 = entity_1_ref_1->get_component<component_1>();
  auto component_2_ref_2 = entity_2_ref_2->get_component<component_2>();
  auto component_3_ref_2 = entity_3_ref_3->get_component<component_3>();

  REQUIRE(component_1_ref_1 == component_1_ref_2);
  REQUIRE(component_2_ref_1 == component_2_ref_2);
  REQUIRE(component_3_ref_1 == component_3_ref_2);

  entity_1_ref_1->remove_component<component_1>();

  auto component_1_ref_3 = entity_1_ref_1->get_component<component_1>();

  REQUIRE(nullptr == component_1_ref_3);

  auto entities                        = scene->entities();
  auto entities_with_component_2       = scene->entities<component_2>();
  auto entities_with_component_3       = scene->entities<component_3>();
  auto entities_with_component_2_and_3 = scene->entities<component_2, component_3>();

  REQUIRE(entities_with_component_2      .size() == 1);
  REQUIRE(entities_with_component_3      .size() == 1);
  REQUIRE(entities_with_component_2_and_3.size() == 0);
}