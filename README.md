# 🏧 Advanced C++ ATM Application

A robust, multi-threaded C++20 Banking & ATM Simulation System built with modular OOP architecture, thread-safe concurrent transactions, and persistent storage.

> **Team Lead:** Aung Mann | **Role:** System Architecture, Threading Logic & Team Coordination

---

## 🎯 Key Technical Highlights
- **Object-Oriented Architecture:** Designed using **SOLID principles** and patterns including **Factory** (account creation), **Singleton** (hardware interface), and **State** (ATM session management).
- **Concurrency & Safety:** Implemented `std::mutex` and `std::scoped_lock` to prevent race conditions during concurrent account operations and transaction logging.
- **Security & Data Handling:** Integrated SHA-256 PIN hashing and persistent account state storage via SQLite/JSON.
- **Engineering Quality:** Includes unit tests using **GoogleTest (gtest)** and automated memory leak checks via **Valgrind**.

## 🛠️ Tech Stack & Standards
- **Language:** C++20 (Modern C++ features: smart pointers, `std::optional`, `std::variant`)
- **Build System:** CMake (Cross-platform compilation)
- **Testing & Tools:** GoogleTest, Valgrind, Git/GitHub Actions (CI/CD)

## 👑 Leadership & Project Management
- **Architectural Ownership:** Designed the core domain layer and database interface schemas.
- **Workflow & Code Reviews:** Established Git Feature-Branch workflow, enforced code formatting via `.clang-format`, and reviewed 100% of pull requests.
