use std::{cell::RefCell, rc::Rc, task::Context};

use nesp_logger::{
    log_manager::LogManager,
    nesp_logger::ILogger,
    printer::{console_printer::ConsolePrinter, printer::Printer},
};

#[test]
fn test_log_manager() {
    // let mut i:i64 = 99999999999999999;

    let printer: Rc<RefCell<dyn Printer>> = Rc::new(RefCell::new(ConsolePrinter::new()));

    let mut i: i64 = 2;
    while i > 0 {
        let log_manager_arc = LogManager::shared();
        let mut log_manager = log_manager_arc.lock().unwrap();
        let logger = log_manager.get_logger("test_class".to_string());

        if i == 2 {
            log_manager.get_config().borrow_mut().add_printer(printer.clone());
        }

        if i < 2 {
            log_manager
                .get_config()
                .borrow_mut()
                .remove_printer(&printer);
        }

        drop(log_manager);

        logger.info(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            12,
            "This is info message".to_string(),
            "".to_string(),
        );
        logger.debug(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            13,
            "This is debug message".to_string(),
            "".to_string(),
        );
        logger.warn(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            14,
            "This is warn message".to_string(),
            "".to_string(),
        );
        logger.error(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            15,
            "This is error message".to_string(),
            "".to_string(),
        );
        logger.fatal(
            None,
            1,
            "main-thread".to_string(),
            "test".to_string(),
            "main".to_string(),
            16,
            "This is fatal message".to_string(),
            "".to_string(),
        );
        println!();

        i -= 1;
    }
}
