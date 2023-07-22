// Copyright (c) 2023-2023. NESP Technology.
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
// Created by jinzhaolu on 2023/2/11.
//

#include "default_message_format.h"

#include <ctime>
#include <iostream>

string nesp::logger::DefaultMessageFormat::Format(Logger::LogRecord record) {
  char current_time_chars[255];
  std::time_t current_time = record.time;
  std::strftime(current_time_chars, sizeof current_time_chars,
                "%Y-%m-%d %H:%M:%S", std::localtime(&current_time));

  std::stringstream current_time_string;
  current_time_string << current_time_chars;

  std::stringstream ret;
  ret << current_time_string.str();
  ret << "\t";
  ret << LoggerUtil::level_name(record.level);
  ret << "\t";
  ret << record.pid;
  ret << "\t";
  ret << "[";
  ret << record.thread_name;
  ret << "]";
  ret << "\t";
  ret << record.log_name;
  ret << "\t";
  ret << record.class_name;
  if (!record.class_name.empty() && !record.method_name.empty()) {
    ret << ".";
  }
  ret << record.method_name;
  ret << " ";
  ret << record.line_number;
  ret << ":";
  ret << record.message;

  return ret.str();
}

nesp::logger::DefaultMessageFormat::~DefaultMessageFormat() = default;
