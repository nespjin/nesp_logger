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
// Created by jinzhaolu on 23-1-31.
//

#include "default_log_config.h"
#include "default_message_format.h"

using namespace NespLogger;

DefaultLogConfig::DefaultLogConfig() {
    format = new DefaultMessageFormat();
    filter = nullptr;
    _isEnable = true;
}

Logger::Format *DefaultLogConfig::getFormat() {
    return format;
}

Logger::Level DefaultLogConfig::getLevel() {
    return Logger::DEBUG;
}

void DefaultLogConfig::setFilter(Logger::Filter *filter) {
    this->filter = filter;
}

Logger::Filter *DefaultLogConfig::getFilter() {
    return filter;
}

bool DefaultLogConfig::isEnable() {
    return _isEnable;
}

void DefaultLogConfig::setEnable(bool isEnable) {
    this->_isEnable = isEnable;
}

void DefaultLogConfig::addPrinter(Logger::Printer *printer) {
    printers.insert(printer);
}

void DefaultLogConfig::removePrinter(Logger::Printer *printer) {
    printers.erase(printer);
}

set<Logger::Printer *> DefaultLogConfig::getPrinters() {
    return printers;
}

DefaultLogConfig::~DefaultLogConfig() {
    printers.clear();
    delete format;
    delete filter;
}
