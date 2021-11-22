#include "filesystem.hpp"

using namespace core::util;
using namespace fs;
using namespace fs::native;

//*************************************************************************************************
Res<void, Filesystem::ErrMount> Filesystem::mount(std::filesystem::path mount_point
    , std::string name)
{
    StringId name_id = StringId(name);
    const auto it = m_mount_points_names.insert(std::upper_bound(
        m_mount_points_names.begin(), m_mount_points_names.end(), name_id), name_id);

    const std::size_t idx = std::distance(m_mount_points_names.begin(), it);
    m_mount_points.insert(m_mount_points.begin() + idx, mount_point);

    return Ok();
}

//*************************************************************************************************
Res<void, Filesystem::ErrUnmount> Filesystem::unmount(const std::string& /*name*/) {
    return Ok();
}

//*************************************************************************************************
Path Filesystem::root() const {
    return Path(StringId("/"));
}

//*************************************************************************************************
Res<Path, IFilesystem::ErrParent> Filesystem::parent(const Path& /*path*/) const {
    return Err(ErrParent::UNDEFINED);
}

//*************************************************************************************************
Res<size_t, IFilesystem::ErrChildrenCount> Filesystem::children_count(const Path& path) const {
    if (path == root())
        return Ok(m_mount_points.size());
    else
        return Err(ErrChildrenCount::UNDEFINED);
}

//*************************************************************************************************
Res<Path, IFilesystem::ErrChild> Filesystem::child(const Path& /*path*/, size_t /*idx*/) const {
    return Err(ErrChild::UNDEFINED);
}

//*************************************************************************************************
bool Filesystem::is_dir(const Path& /*path*/) const {
    return false;
}

//*************************************************************************************************
bool Filesystem::is_file(const Path& /*path*/) const {
    return false;
}

//*************************************************************************************************
Res<Path, IFilesystem::ErrAdd> Filesystem::add(const Path& /*parent*/
    , const std::string& /*relative_path*/) 
{
    return Err(ErrAdd::UNDEFINED);
}

//*************************************************************************************************
Res<void, IFilesystem::ErrRemove> Filesystem::remove(const Path& /*path*/) {
    return Err(ErrRemove::UNDEFINED);
}

//*************************************************************************************************
Res<Path, IFilesystem::ErrRename> Filesystem::rename(const Path& /*path*/
    , const std::string& /*new_name*/) 
{
    return Err(ErrRename::UNDEFINED);
}

//*************************************************************************************************
Res<Path, IFilesystem::ErrMove> Filesystem::move(const Path& /*path*/
    , const Path& /*new_parent*/) 
{
    return Err(ErrMove::UNDEFINED);
}

//*************************************************************************************************
Res<rtti::Buffer, IFilesystem::ErrRead> Filesystem::read(const Path& /*path*/) const {
    return Err(ErrRead::UNDEFINED);
}

//*************************************************************************************************
Res<void, IFilesystem::ErrWrite> Filesystem::write(const Path& /*path*/
    , const rtti::Buffer& /*buf*/) const 
{
    return Err(ErrWrite::UNDEFINED);
}