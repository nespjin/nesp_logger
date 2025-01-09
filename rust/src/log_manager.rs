/*
 *
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

use std::cell::RefCell;
use std::collections::HashMap;
use std::rc::Rc;
use std::sync::{Arc, Mutex};

use crate::config::config::Config;
use crate::nesp_logger::Logger;
use crate::printer::console_printer::ConsolePrinter;

pub struct LogManager {
    logger_cache: HashMap<String, Logger>,
    config: Rc<RefCell<Config>>,
}

impl LogManager {
    pub fn shared() -> Arc<Mutex<LogManager>> {
        static mut INSTANCE: Option<Arc<Mutex<LogManager>>> = None;
        unsafe {
            INSTANCE
                .get_or_insert_with(|| {
                    let manager: LogManager = LogManager {
                        logger_cache: HashMap::new(),
                        config: Rc::new(RefCell::new(Config::new_default())),
                    };
                    manager.init();
                    Arc::new(Mutex::new(manager))
                })
                .clone()
        }
    }

    fn init(&self) {
        self.config
            .borrow_mut()
            .add_printer(Rc::new(RefCell::new(ConsolePrinter::new())));
    }

    pub fn get_logger(&mut self, name: String) -> Logger {
        let name_local = name.clone();
        let old_value = self.logger_cache.get(&name_local);
        if old_value.is_none() {
            self.logger_cache
                .insert(name, Logger::new(name_local.clone()));
        }
        let ret = Some(self.logger_cache.get(&name_local).unwrap().clone());
        return ret.unwrap();
    }

    pub fn get_config(&self) -> Rc<RefCell<Config>> {
        return self.config.clone();
    }
}
