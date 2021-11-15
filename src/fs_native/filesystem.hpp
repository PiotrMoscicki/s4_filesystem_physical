#pragma once

#include "ifilesystem.hpp"

namespace fs::native {

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class Filesystem : public IFilesystem {
    public:

        Path root() const override;
        Res<Path, ErrParent> parent(const Path& path) const override;
        Res<size_t, ErrChildrenCount> children_count(const Path& path) const override;
        Res<Path, ErrChild> child(const Path& path, size_t idx) const override;

        bool is_dir(const Path& path) const override;
        bool is_file(const Path& path) const override;

        Res<Path, ErrAdd> add(const Path& parent, const std::string& relative_path) override;
        Res<void, ErrRemove> remove(const Path& path) override;
        Res<Path, ErrRename> rename(const Path& path, const std::string& new_name) override;
        Res<Path, ErrMove> move(const Path& path, const Path& new_parent) override;

        Res<rtti::Buffer, ErrRead> read(const Path& path) const override;
        Res<void, ErrWrite> write(const Path& path, const rtti::Buffer& buf) const override;

    }; // class IFilesystem

}