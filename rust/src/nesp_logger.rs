/*
 * Copyright (c) 2023. NESP Technology.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 * for the specific language governing permissions and limitations under the License.
 */

use chrono::Utc;

use crate::{
    config::config::Config, filter::Filter, format::format::Format, level::Level,
    log_manager::LogManager, log_record::LogRecord, printer::printer::Printer,
};

pub trait ILogger {
    fn log(
        &self,
        printer: Option<Box<dyn Printer>>,
        level: Level,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    );
}

#[derive(Debug, Clone)]
pub struct Logger {
    name: String,
}

impl Logger {
    pub(crate) fn new(name: String) -> Logger {
        return Logger { name };
    }
}

impl ILogger for Logger {
    fn log(
        &self,
        printer: Option<Box<dyn Printer>>,
        level: Level,
        pid: u32,
        thread_name: String,
        class_name: String,
        method_name: String,
        line_number: u32,
        message: String,
        exception: String,
    ) {
        // let log_manager_arc =  LogManager::shared();
        // let mut log_manager = log_manager_arc.lock().unwrap();
        // log_manager.

        let config = Config::new_default();
        let filter = config.filter;

        if !config.enabled {
            return;
        }

        if level.index() < config.level.index() {
            return;
        }

        let mut message_formatted: String = "".to_string();

        let mut record = LogRecord {
            time: Utc::now().timestamp_millis(),
            pid,
            thread_name,
            log_name: self.name.to_string(),
            class_name,
            method_name,
            line_number,
            level,
            message,
            message_formatted,
            exp: exception,
        };

        let format = config.format;
        if format.is_some() {
            message_formatted = format.unwrap().format(&record);
            record.message_formatted = message_formatted;
        }

        if filter.is_some() {
            if !filter.unwrap().enabled(record) {
                return;
            }
        }

        let printers = config.get_printers();

    }
}
