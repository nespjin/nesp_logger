// Copyright (c) 2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
// on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
// for the specific language governing permissions and limitations under the License.

//
// Team: NESP Technology
// Author: JinZhaolu Email:1756404649@qq.com
// Version: 1.0
// Time: Create 2023/2/12 下午12:02
// Description:
//

#include "gzip_util.h"

#define GZIP_ENCODING 16

long NespLogger::GzipUtil::compress(const char *src, uint srcLen, char *dest, uint destLen) {
    z_stream stream;
    int err;
    int windowBits = 15;

    if (src == nullptr || srcLen <= 0) return -1;

    stream.zalloc = (alloc_func) nullptr;
    stream.zfree = (free_func) nullptr;

    if (deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
        /*windowBits |*/ GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
        return -1;
    }

    stream.next_in = (Bytef *) src;
    stream.avail_in = srcLen;
    stream.next_out = (Bytef *) dest;
    stream.avail_out = destLen;

    while (stream.avail_in != 0 && stream.total_out < destLen) {
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

    return (long) stream.total_out;
}

long NespLogger::GzipUtil::uncompress(const char *src, uint srcLen, char *dest, uint destLen) {
    z_stream stream;
    stream.zalloc = nullptr;
    stream.zfree = nullptr;
    stream.opaque = nullptr;

    stream.avail_in = srcLen;
    stream.avail_out = destLen;
    stream.next_in = (Bytef *) src;
    stream.next_out = (Bytef *) dest;

    int err;
    ulong ret;

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
    return (long) ret;
}
