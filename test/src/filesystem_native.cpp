#include <catch2/catch_test_macros.hpp>

//*************************************************************************************************
TEST_CASE( "Ref, Id, Path conversions", "[assets]" ) {
    // assets::Ref<EntityPrefabAsset> ref;
    // assets::Id<EntityPrefabAsset> id;
    // assets::Path<EntityPrefabAsset> path;

    // REQUIRE( ref.is_id() == true );
    // REQUIRE( ref.is_path() == false );
    // REQUIRE( ref.id().is_nil() == true );
    // id = ref.id();
    // REQUIRE( id.id().is_nil() == true );

    // ref = assets::Path<EntityPrefabAsset>(VALID_PATH);
    // REQUIRE( ref.is_id() == false );
    // REQUIRE( ref.is_path() == true );
    // REQUIRE( ref.path() == VALID_PATH );
    // path = ref.path();
    // REQUIRE( path.path() == VALID_PATH );

    // ref = assets::Id<EntityPrefabAsset>(VALID_ID);
    // REQUIRE( ref.is_id() == true );
    // REQUIRE( ref.is_path() == false );
    // REQUIRE( ref.id() == VALID_ID );
    // id = ref.id();
    // REQUIRE( id.id() == VALID_ID );

    // path = INVALID_PATH;
    // ref = path;
    // REQUIRE( ref.is_id() == false );
    // REQUIRE( ref.is_path() == true );
    // REQUIRE( ref.path() == INVALID_PATH );

    // id = INVALID_ID;
    // ref = id;
    // REQUIRE( ref.is_id() == true );
    // REQUIRE( ref.is_path() == false );
    // REQUIRE( ref.id() == INVALID_ID );
}
