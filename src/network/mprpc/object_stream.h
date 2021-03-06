// Copyright (c)2008-2011, Preferred Infrastructure Inc.
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
// 
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
// 
//     * Neither the name of Preferred Infrastructure nor the names of other
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef INCLUDE_GUARD_PFI_NETWORK_MPRPC_OBJECT_STREAM_H_
#define INCLUDE_GUARD_PFI_NETWORK_MPRPC_OBJECT_STREAM_H_

#include <memory>

#include <msgpack.hpp>

namespace pfi {
namespace network {
namespace mprpc {


class object_stream {
public:
	object_stream(int iofd);
	object_stream(const std::string& host, uint16_t port);
	~object_stream();

        int read(msgpack::object* obj, std::auto_ptr<msgpack::zone>* zone,
		 double timeout_sec);

	template <typename T>
	int write(const T& v, double timeout_sec);

        int write(const void* data, size_t size, double timeout_sec);

private:
	msgpack::unpacker unpacker;
	int iofd;
};

template <typename T>
int object_stream::write(const T& v, double timeout_sec)
{
	msgpack::sbuffer sbuf;
	msgpack::pack(sbuf, v);
	return write(sbuf.data(), sbuf.size(), timeout_sec);
}


}  // namespace mprpc
}  // namespace network
}  // namespace pfi

#endif // #ifndef INCLUDE_GUARD_PFI_NETWORK_MPRPC_OBJECT_STREAM_H_
