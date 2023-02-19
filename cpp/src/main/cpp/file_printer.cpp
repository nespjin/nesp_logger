// Copyright (c) 2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
// on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
// for the specific language governing permissions and limitations under the License.

#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include "../include/file_printer.h"

//
// Team: NESP Technology
// Author: JinZhaolu Email:1756404649@qq.com
// Version: 1.0
// Time: Create 2023/2/11 下午10:43
// Description:
//

#define TAG "FilePrinter"

using namespace std;

namespace NespLogger {
    class DefaultCompressNameFormat : public FilePrinter::CompressNameFormat {
        string format(string fileName, int num) override {
            return fileName + "-" + to_string(num) + ".gz";
        }

        ~DefaultCompressNameFormat() override = default;
    };
}

NespLogger::FilePrinter::FilePrinter(const string &dirPath) {
    this->dirPath = dirPath;
    this->fileName = "log";
    this->compressNameFormat = new DefaultCompressNameFormat();
    this->maxPerFileSize = 1024 * 1024 * 100L; // 100M
    this->maxFileCount = 5;
    this->_isAsync = false;
}

void NespLogger::FilePrinter::setFileName(const string &name) {
    this->fileName = name;
}

string NespLogger::FilePrinter::getFileName() {
    return fileName;
}

void NespLogger::FilePrinter::setMaxPerFileSize(ulong size) {
    this->maxPerFileSize = size;
}

ulong NespLogger::FilePrinter::getMaxPerFileSize() {
    return maxPerFileSize;
}

void NespLogger::FilePrinter::setMaxFileCount(uint count) {
    this->maxFileCount = count;
}

uint NespLogger::FilePrinter::getMaxFileCount() {
    return maxFileCount;
}

void NespLogger::FilePrinter::setAsync(bool async) {
    this->_isAsync = async;
}

bool NespLogger::FilePrinter::isAsync() {
    return this->_isAsync;
}

string &trim(string &str) {
    if (str.empty()) {
        return str;
    }

    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' '), 1);

    return str;
}

bool isDir(const string &dirPath) {
    struct stat buffer{};
    return (stat(dirPath.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

void doPrint(const string &dirPath, NespLogger::Logger::LogRecord record);

void NespLogger::FilePrinter::print(NespLogger::Logger::LogRecord logRecord) {
    if (trim(dirPath).empty()) {
        cout << TAG << " print: The dirPath must not be empty";
        return;
    }

    ifstream dir(dirPath);

    // TODO: replace mkdir with mkdirs
    if (!dir.good() && ::mkdir(dirPath.c_str(), 0777) != 0) {
        cout << TAG << " print: mkdir log dir(" << dirPath << ") failed";
        return;
    }

    if (!isDir(dirPath)) {
        cout << TAG << " print: dirPath is not a directory";
        return;
    }

    // TODO: implements async
    doPrint(dirPath, logRecord);
}

void doPrint(const string &dirPath, NespLogger::Logger::LogRecord record) {

}

NespLogger::FilePrinter::~FilePrinter() {
    delete this->compressNameFormat;
}
