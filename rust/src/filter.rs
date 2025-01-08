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

use crate::{level::Level, log_record::LogRecord};

pub trait Filter {
    fn enabled(&self, record: &LogRecord) -> bool;
}

pub struct ReleaseFilter;

impl Filter for ReleaseFilter {
    fn enabled(&self, record: &LogRecord) -> bool {
        return matches!(record.level, Level::Debug);
    }
}
