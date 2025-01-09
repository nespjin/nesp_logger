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
 *
 */

use crate::format::format::Format;
use crate::log_manager::LogManager;
use crate::log_record::LogRecord;
use chrono::{FixedOffset, TimeZone, Utc};

#[derive(Debug, Clone, Copy)]
pub struct DefaultMessageFormat {}

impl DefaultMessageFormat {
    pub fn new() -> DefaultMessageFormat {
        return DefaultMessageFormat {};
    }
}

impl Format for DefaultMessageFormat {
    fn format(&self, record: &LogRecord) -> String {
        let log_manager_mutex = LogManager::shared();
        let log_manager = log_manager_mutex.lock().unwrap();
        let config = log_manager.get_config();
        drop(log_manager);

        let current_utc_time = Utc.timestamp_millis_opt(record.time).unwrap();
        let current_time = match config.borrow().time_zone {
            Some(time_zone) => current_utc_time.with_timezone(&time_zone),
            None => current_utc_time.with_timezone(&FixedOffset::east_opt(0).unwrap()),
        };

        let current_time_str = current_time.format("%Y-%m-%d %H:%M:%S").to_string();

        let middle_of_class_method_name =
            if !record.class_name.is_empty() && !record.class_name.is_empty() {
                "."
            } else {
                ""
            };

        return format!(
            "{}\t{:?}\t{}\t[{}]\t{}\t{}{} {}:{}",
            current_time_str,
            record.level,
            record.pid,
            record.thread_name,
            record.log_name,
            record.class_name,
            middle_of_class_method_name.to_string() + &*record.method_name,
            record.line_number,
            record.message
        );
    }
}
