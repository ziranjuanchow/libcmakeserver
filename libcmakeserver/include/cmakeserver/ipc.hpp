#pragma once
#if defined(WIN32)
#include "win32/ipc.hpp"
#elif defined(__linux__)
#include "linux/ipc.hpp"
#endif
#include <boost/process/child.hpp>
#include <string_view>

namespace cmakeserver {
	boost::process::child spawn_cmake_server(std::string_view pipe);
	fs::path make_temporary_filename();
}    // namespace cmakeserver
