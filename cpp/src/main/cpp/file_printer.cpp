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

#include "../include/file_printer.h"

#include <sys/stat.h>

#include <fstream>
#include <iostream>

//
// Team: NESP Technology
// Author: JinZhaolu Email:1756404649@qq.com
// Version: 1.0
// Time: Create 2023/2/11 下午10:43
// Description:
//

#define TAG "FilePrinter"

using namespace std;

namespace nesp {
namespace logger {
class DefaultCompressNameFormat : public FilePrinter::CompressNameFormat {
  string Format(string file_name, int num) override {
    return file_name + "-" + to_string(num) + ".gz";
  }

  ~DefaultCompressNameFormat() override = default;
};
}  // namespace logger
}  // namespace nesp

nesp::logger::FilePrinter::FilePrinter(const string &dirPath) {
  this->dir_path_ = dirPath;
  this->file_name_ = "log";
  this->compress_name_format_ = new DefaultCompressNameFormat();
  this->max_per_file_size_ = 1024 * 1024 * 100L;  // 100M
  this->max_file_count_ = 5;
  this->is_async_ = false;
}

void nesp::logger::FilePrinter::set_file_name(const string &name) {
  this->file_name_ = name;
}

string nesp::logger::FilePrinter::file_name() { return file_name_; }

void nesp::logger::FilePrinter::set_max_per_file_size(ulong size) {
  this->max_per_file_size_ = size;
}

ulong nesp::logger::FilePrinter::max_per_file_size() {
  return max_per_file_size_;
}

void nesp::logger::FilePrinter::set_max_file_count(uint count) {
  this->max_file_count_ = count;
}

uint nesp::logger::FilePrinter::max_file_count() { return max_file_count_; }

void nesp::logger::FilePrinter::set_async(bool async) {
  this->is_async_ = async;
}

bool nesp::logger::FilePrinter::async() { return this->is_async_; }

string &Trim(string &str) {
  if (str.empty()) {
    return str;
  }

  str.erase(0, str.find_first_not_of(' '));
  str.erase(str.find_last_not_of(' '), 1);

  return str;
}

bool isDir(const string &dir_path) {
  struct stat buffer {};
  return (stat(dir_path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

void DoPrint(const string &dir_path, nesp::logger::Logger::LogRecord record);

void nesp::logger::FilePrinter::Print(
    nesp::logger::Logger::LogRecord log_record) {
  if (Trim(dir_path_).empty()) {
    cout << TAG << " print: The dir path must not be empty";
    return;
  }

  ifstream dir(dir_path_);

  // TODO: replace mkdir with mkdirs
  if (!dir.good() && ::mkdir(dir_path_.c_str(), 0777) != 0) {
    cout << TAG << " print: mkdir log dir(" << dir_path_ << ") failed";
    return;
  }

  if (!isDir(dir_path_)) {
    cout << TAG << " print: dirPath is not a directory";
    return;
  }

  // TODO: implements async
  DoPrint(dir_path_, log_record);
}

void DoPrint(const string &dir_path, nesp::logger::Logger::LogRecord record) {}

nesp::logger::FilePrinter::~FilePrinter() {
  delete this->compress_name_format_;
}
