use nesp_logger::{
    level::Level,
    log_manager::{self, LogManager},
    nesp_logger::ILogger,
};

#[test]
fn test_log_manager() {
    let log_manager_arc = LogManager::shared();
    let mut log_manager = log_manager_arc.lock().unwrap();
    let log = log_manager.get_logger("test_class".to_string());
    log.log(
        None,
        Level::Debug,
        12,
        "main-thread".to_string(),
        "TestClass".to_string(),
        "test_method".to_string(),
        1,
        "This is a test message".to_string(),
        "".to_string(),
    );
}
