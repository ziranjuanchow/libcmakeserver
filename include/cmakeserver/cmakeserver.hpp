#pragma once
#include "cmake_protocol.hpp"
#include "coroutines.hpp"
#include "use_boost_future.hpp"
#include <boost/asio.hpp>

namespace cmakeserver {
	template <typename AsyncReadStream, typename Allocator>
	auto async_read_line(AsyncReadStream &s, boost::asio::basic_streambuf<Allocator> &b) {
		return boost::asio::async_read_until(s, b, protocol::epilogue, use_boost_future);
	}

	template <typename AsyncWriteStream, typename ConstBufferSequence>
	auto async_write(AsyncWriteStream &s, ConstBufferSequence const &buffers) -> boost::future<std::size_t> {
		return boost::asio::async_write(s, buffers, use_boost_future);
	}

	template <typename AsyncReadStream, typename Allocator>
	auto async_cmake_recv(AsyncReadStream &s, boost::asio::basic_streambuf<Allocator> &b)
	    -> boost::future<std::string> {
		[[maybe_unused]] auto const line_len = co_await async_read_line(s, b);
		auto const str = std::string((std::istreambuf_iterator<char>(&b)), std::istreambuf_iterator<char>());
		co_return str;
	}

	template <typename AsyncWriteStream>
	auto async_cmake_send(AsyncWriteStream &s, std::string const &str) -> boost::future<bool> {
		auto transmitted = co_await async_write(s, boost::asio::buffer(protocol::prologue));
		transmitted += co_await async_write(s, boost::asio::buffer(str));
		transmitted += co_await async_write(s, boost::asio::buffer(protocol::epilogue));
		co_return transmitted == (protocol::prologue.size() + str.size() + protocol::epilogue.size());
	}
}    // namespace cmakeserver