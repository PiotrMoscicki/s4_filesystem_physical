#pragma once

#include <string>
#include <sstream>
#include <variant>
#include <optional>

#include <rtti/rtti.hpp>

namespace fs {

    enum class ErrParent {
        INVALID_PATH
    };

    enum class ErrChildrenCount {
        UNDEFINED
    };
    
    enum class ErrChild {
        UNDEFINED
    };
    
    enum class ErrAdd {
        UNDEFINED
    };
    
    enum class ErrRemove {
        UNDEFINED
    };
    
    enum class ErrRename {
        UNDEFINED
    };
    
    enum class ErrMove {
        UNDEFINED
    };
    
    enum class ErrRead {
        UNDEFINED
    };
    
    enum class ErrWrite {
        UNDEFINED
    };
    
    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    template <typename OK = void>
	class Ok final
	{
	public:
		Ok() = delete;
		Ok(Ok&) = delete;
		constexpr Ok(Ok&&) = default;
		Ok& operator=(Ok&) = delete;
		Ok& operator=(Ok&&) = delete;

		explicit constexpr Ok(OK val) : m_value(std::move(val)) {}

		constexpr OK&& get() && { return std::move(m_value); }

	private:
		OK m_value;
	};

    //*********************************************************************************************
	template <>
	class Ok<void> final
	{
	public:
		constexpr Ok() = default;
		Ok(Ok&) = delete;
		constexpr Ok(Ok&&) = default;
		Ok& operator=(Ok&) = delete;
		Ok& operator=(Ok&&) = delete;
	};

	Ok()->Ok<void>;

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
	template <typename ERR>
	class Err final
	{
	public:
		Err() = delete;
		Err(Err&) = delete;
		constexpr Err(Err&&) = default;
		Err& operator=(Err&) = delete;
		Err& operator=(Err&&) = delete;

		explicit constexpr Err(ERR val) : m_value(std::move(val)) {}

		constexpr ERR&& get() && { return std::move(m_value); }

	private:
		ERR m_value;
	};

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    template <typename OK, typename ERR>
	class Res final
	{
	public:
		Res() = delete;
		constexpr Res(Res&) = default;
		constexpr Res(Res&&) = default;
		constexpr Res& operator=(Res&) = default;
		constexpr Res& operator=(Res&&) = default;
		constexpr Res(Ok<OK> ok) : m_value(std::move(ok).get()) {}
		constexpr Res(Err<ERR> err) : m_value(std::move(err).get()) {}

		constexpr bool is_ok() const { return m_value.index() == 0; }
		constexpr bool is_err() const { return m_value.index() == 1; }

		constexpr OK& ok() & { return std::get<OK>(m_value); }
		constexpr const OK& ok() const & { return std::get<OK>(m_value); }
		constexpr OK&& ok() && { return std::get<OK>(std::move(m_value)); }

		constexpr ERR& err() & { return std::get<ERR>(m_value); }
		constexpr const ERR& err() const & { return std::get<ERR>(m_value); }
		constexpr ERR&& err() && { return std::get<ERR>(std::move(m_value)); }

	private:
		std::variant<OK, ERR> m_value;
	};

    //*********************************************************************************************
	template <typename ERR>
	class Res<void, ERR> final
	{
	public:
		constexpr Res() = delete;
		constexpr Res(Res&) = default;
		constexpr Res(Res&&) = default;
		constexpr Res& operator=(Res&) = default;
		constexpr Res& operator=(Res&&) = default;
		constexpr Res(Ok<void> ok) {}
		constexpr Res(Err<ERR> err) : m_value(std::move(err).get()) {}

		constexpr bool is_ok() const { return !is_err(); }
		constexpr bool is_err() const { return m_value.has_value(); }
        
		constexpr ERR& err() & { return m_value.value(); }
		constexpr const ERR& err() const & { return m_value.value(); }
		constexpr ERR&& err() && { return std::move(m_value).value(); }

	private:
		std::optional<ERR> m_value;
	};

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class Path {
    public:
        inline static char NAME_SEPARATOR = '/';
        inline static char EXT_SEPARATOR = '.';

        Path() = default;
        Path(std::string path) : m_path(std::move(path)) { extract_name_and_ext(); }

        const std::string& path() const { return m_path; } 
        const std::string& name() const { return m_name; }
        const std::string& ext() const { return m_ext; }

    private:
        void extract_name_and_ext() {
            std::istringstream stream(m_path);
            std::string last_path_elem;
            while (getline(stream, last_path_elem, NAME_SEPARATOR)) {}
            stream = std::istringstream(last_path_elem);
            getline(stream, m_name, EXT_SEPARATOR);
            getline(stream, m_ext);
        }

        std::string m_path;
        std::string m_name;
        std::string m_ext;

    }; // class Path

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class IFilesystem {
    public:
        virtual Path root() const = 0;
        virtual Res<Path, ErrParent> parent(const Path& path) const = 0;
        virtual Res<size_t, ErrChildrenCount> children_count(const Path& path) const = 0;
        virtual Res<Path, ErrChild> child(const Path& path, size_t idx) const = 0;

        virtual bool is_dir(const Path& path) const = 0;
        virtual bool is_file(const Path& path) const = 0;

        virtual Res<Path, ErrAdd> add(const Path& parent, const std::string& relative_path) = 0;
        virtual Res<void, ErrRemove> remove(const Path& path) = 0;
        virtual Res<Path, ErrRename> rename(const Path& path, const std::string& new_name) = 0;
        virtual Res<Path, ErrMove> move(const Path& path, const Path& new_parent) = 0;

        virtual Res<rtti::Buffer, ErrRead> read(const Path& path) const = 0;
        virtual Res<void, ErrWrite> write(const Path& path, const rtti::Buffer& buf) const = 0;

    }; // class IFilesystem

} // namespace fs