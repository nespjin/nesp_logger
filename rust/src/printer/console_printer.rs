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

use crate::level;
use crate::level::Level;
use crate::log_record::LogRecord;
use crate::printer::printer::Printer;

const RESET: &'static str = "\033[0m\033[0m";
const BLACK: &'static str = "\033[0m\033[30m"; /* Black */
const RED: &'static str = "\033[0m\033[31m"; /* Red */
const GREEN: &'static str = "\033[0m\033[32m"; /* Green */
const YELLOW: &'static str = "\033[0m\033[33m"; /* Yellow */
const BLUE: &'static str = "\033[0m\033[34m"; /* Blue */
const MAGENTA: &'static str = "\033[0m\033[35m"; /* Magenta */
const CYAN: &'static str = "\033[0m\033[36m"; /* Cyan */
const WHITE: &'static str = "\033[0m\033[37m"; /* White */
const BOLD_BLACK: &'static str = "\033[1m\033[30m"; /* Bold Black */
const BOLD_RED: &'static str = "\033[1m\033[31m"; /* Bold Red */
const BOLD_GREEN: &'static str = "\033[1m\033[32m"; /* Bold Green */
const BOLD_YELLOW: &'static str = "\033[1m\033[33m"; /* Bold Yellow */
const BOLD_BLUE: &'static str = "\033[1m\033[34m"; /* Bold Blue */
const BOLD_MAGENTA: &'static str = "\033[1m\033[35m"; /* Bold Magenta */
const BOLD_CYAN: &'static str = "\033[1m\033[36m"; /* Bold Cyan */
const BOLD_WHITE: &'static str = "\033[1m\033[37m"; /* Bold White */

pub struct ConsolePrinter;

impl ConsolePrinter {
    pub fn new() -> ConsolePrinter {
        ConsolePrinter {}
    }
}

impl Printer for ConsolePrinter {
    fn print(&self, record: LogRecord) {
        let level = record.level;
        let mut color: &str = RESET;

        match level {
            Level::Debug => {
                color = RESET;
            }
            Level::Info => {
                color = RESET;
            }
            Level::Warn => {
                color = YELLOW;
            }
            Level::Error => {
                color = RED;
            }
            Level::Fatal => {
                color = BOLD_RED;
            }
        }

        println!("{}", color.to_string() + &*record.message_formatted);
    }
}
