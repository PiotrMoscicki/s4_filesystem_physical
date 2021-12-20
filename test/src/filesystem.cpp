#include <catch2/catch_test_macros.hpp>

#include <fs_native/filesystem.hpp>

using namespace fs;
using namespace fs::native;
using namespace core::str;

//*************************************************************************************************
TEST_CASE( "Root is always the same", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.root() == fs.root() );
}

//*************************************************************************************************
TEST_CASE( "Root path is /", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.root().path() == StringId("/") );
}

//*************************************************************************************************
TEST_CASE( "Root has no name", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.root().name() == StringId("") );
}

//*************************************************************************************************
TEST_CASE( "Root has no ext", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.root().ext() == StringId("") );
}

//*************************************************************************************************
TEST_CASE( "Accessing parent of the root is invalid", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.parent(fs.root()).err() == IFilesystem::ErrParent::PATH_IS_ROOT );
}

//*************************************************************************************************
TEST_CASE( "Accessing root children count is always valid", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.children_count(fs.root()).is_ok() == true );
}

//*************************************************************************************************
TEST_CASE( "Root in not mounted filesystem has no children", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.children_count(fs.root()).ok() == 0 );
    REQUIRE( fs.child(fs.root(), 0).err() == IFilesystem::ErrChild::PATH_HAS_NO_CHILDREN );
}

//*************************************************************************************************
TEST_CASE( "Root is a directory", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.is_dir(fs.root()) );
}

//*************************************************************************************************
TEST_CASE( "Root is not a file", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.is_file(fs.root()) == false );
}

//*************************************************************************************************
TEST_CASE( "Can't add, remove, rename or move anything directly in root", "[fs::native::Filesystem]" ) {
    Filesystem fs;
    REQUIRE( fs.add(fs.root()).err() == IFilesystem::ErrAdd::CANT_ADD_CHILD_TO_ROOT );
    REQUIRE( fs.remove(fs.root()).err() == IFilesystem::ErrRemove::CANT_REMOVE_ROOT_CHILD );
    REQUIRE( fs.rename(fs.root()).err() == IFilesystem::ErrRename::CANT_RENAME_ROOT_CHILD );
    REQUIRE( fs.move(fs.root()).err() == IFilesystem::ErrMove::CANT_MOVE_ROOT_CHILD );
}

