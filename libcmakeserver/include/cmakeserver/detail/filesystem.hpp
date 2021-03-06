#pragma once
#if __has_include(<filesystem>)
#include <filesystem>
namespace cmakeserver {
	namespace fs = std::filesystem;
}
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace cmakeserver {
	namespace fs = std::experimental::filesystem;
}
#else
#error "<filesystem> header not found"
#endif
