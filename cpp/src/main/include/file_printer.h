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
// Time: Create 2023/2/11 下午10:41
// Description:
//

#ifndef NESP_LOGGER_FILE_PRINTER_H
#define NESP_LOGGER_FILE_PRINTER_H

#include "nesp_logger.h"

namespace NespLogger {
    class FilePrinter final : public Logger::Printer {

    public:
        class CompressNameFormat {
            /**
             * Returns the name for compressed file.
             *
             * @param fileName the name of origin file.
             * @param num the number of current log file.
             **/
            virtual string format(string fileName, int num) = 0;

        public:
            virtual ~CompressNameFormat() = default;
        };

    private:
        string dirPath;

        /** The name of the log file to write, default log */
        string fileName;

        CompressNameFormat *compressNameFormat;

        /** The max size for per log file, default 100M */
        unsigned long maxPerFileSize;

        /** The max log file count, default 5 */
        unsigned int maxFileCount;

        bool _isAsync;

    public:
        explicit FilePrinter(const string &dirPath);

        void setFileName(const string &name);

        string getFileName();

        void setMaxPerFileSize(ulong size);

        ulong getMaxPerFileSize();

        void setMaxFileCount(uint count);

        uint getMaxFileCount();

        void setAsync(bool async);

        bool isAsync();

        void print(Logger::LogRecord logRecord) override;

        ~FilePrinter() override;
    };
}

#endif //NESP_LOGGER_FILE_PRINTER_H
