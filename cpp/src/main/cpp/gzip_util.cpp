// Copyright (c) 2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may
// obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

//
// Team: NESP Technology
// Author: JinZhaolu Email:1756404649@qq.com
// Version: 1.0
// Time: Create 2023/2/12 下午12:02
// Description:
//

#include "gzip_util.h"

#define GZIP_ENCODING 16

long nesp::logger::GzipUtil::Compress(const char *src, uint32_t src_len,
                                      char *dest, uint32_t dest_len) {
  z_stream stream;
  uint32_t err;
  uint32_t window_bits = 15;

  if (src == nullptr || src_len <= 0) return -1;

  stream.zalloc = (alloc_func) nullptr;
  stream.zfree = (free_func) nullptr;

  if (deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                   /*windowBits |*/ GZIP_ENCODING, 8,
                   Z_DEFAULT_STRATEGY) != Z_OK) {
    return -1;
  }

  stream.next_in = (Bytef *)src;
  stream.avail_in = src_len;
  stream.next_out = (Bytef *)dest;
  stream.avail_out = dest_len;

  while (stream.avail_in != 0 && stream.total_out < dest_len) {
    if (deflate(&stream, Z_NO_FLUSH) != Z_OK) {
      return -1;
    }
  }

  while (true) {
    if ((err = deflate(&stream, Z_FINISH)) == Z_STREAM_END) {
      break;
    }
    if (err != Z_OK) {
      return -1;
    }
  }

  if (deflateEnd(&stream) != Z_OK) {
    return -1;
  }

  return (long)stream.total_out;
}

uint32_t nesp::logger::GzipUtil::Uncompress(const char *src, uint32_t src_len,
                                        char *dest, uint32_t dest_len) {
  z_stream stream;
  stream.zalloc = nullptr;
  stream.zfree = nullptr;
  stream.opaque = nullptr;

  stream.avail_in = src_len;
  stream.avail_out = dest_len;
  stream.next_in = (Bytef *)src;
  stream.next_out = (Bytef *)dest;

  uint32_t err;
  uint64_t ret;

  err = inflateInit2(&stream, MAX_WBITS + 16);
  if (err == Z_OK) {
    err = inflate(&stream, Z_FINISH);
    if (err == Z_STREAM_END) {
      ret = stream.total_out;
    } else {
      inflateEnd(&stream);
      return err;
    }
  } else {
    inflateEnd(&stream);
    return err;
  }
  inflateEnd(&stream);
  return (long)ret;
}
