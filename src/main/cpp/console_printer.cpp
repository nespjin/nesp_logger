// Copyright (c) 2023-2023. NESP Technology.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
// on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
// for the specific language governing permissions and limitations under the License.

//
// Created by jinzhaolu on 2023/2/11.
//
#include <iostream>
#include "../include/nesp_logger.h"
#include "../include/console_printer.h"

using namespace NespLogger;

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m\033[0m"
#define BLACK   "\033[0m\033[30m"      /* Black */
#define RED     "\033[0m\033[31m"      /* Red */
#define GREEN   "\033[0m\033[32m"      /* Green */
#define YELLOW  "\033[0m\033[33m"      /* Yellow */
#define BLUE    "\033[0m\033[34m"      /* Blue */
#define MAGENTA "\033[0m\033[35m"      /* Magenta */
#define CYAN    "\033[0m\033[36m"      /* Cyan */
#define WHITE   "\033[0m\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

void ConsolePrinter::print(Logger::LogRecord logRecord) {
    const Logger::LogRecord record = logRecord;
    string color;
    if (record.level == Logger::Level::INFO || record.level == Logger::Level::DEBUG) {
        color = RESET;
    } else if (record.level == Logger::Level::WARN) {
        color = YELLOW;
    } else if (record.level == Logger::Level::ERROR) {
        color = RED;
    } else if (record.level == Logger::Level::FATAL) {
        color = BOLDRED;
    }
    cout << color << record.messageFormatted << endl;
}

ConsolePrinter::~ConsolePrinter() = default;
