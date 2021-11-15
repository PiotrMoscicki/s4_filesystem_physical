#include "filesystem.hpp"

using namespace fs;
using namespace fs::native;

//*************************************************************************************************
Res<void, ErrMount> Filesystem::mount(std::filesystem::path mount_point, std::string name) {
    // const size_t idx = std::distance(m_names.begin()
    //     , m_names.insert(std::upper_bound( m_names.begin(), m_names.end(), name ), std::move(name)));
    // m_mount_points.insert(idx, std::move(mount_point));

    return Ok();
}

//*************************************************************************************************
Res<void, ErrUnmount> Filesystem::unmount(const std::string& name) {
    return {};
}

//*************************************************************************************************
Path Filesystem::root() const {
    return Path("/");
}