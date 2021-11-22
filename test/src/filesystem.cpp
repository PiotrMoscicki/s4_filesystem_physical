#include <catch2/catch_test_macros.hpp>

#include <fs_native/filesystem.hpp>

using namespace fs::native;

//*************************************************************************************************
TEST_CASE( "Accessing root children count is always valid", "[fs_native]" ) {
    Filesystem fs;
    REQUIRE( fs.children_count(fs.root()).is_ok() == true );
}

//*************************************************************************************************
TEST_CASE( "Not mounted filesystem has no directories", "[fs_native]" ) {
    Filesystem fs;
    REQUIRE( fs.children_count(fs.root()).ok() == 0 );
}
