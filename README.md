# Project-4-Bank-System-With-Extension

## 🏦 C++ Bank Management System

### 📖 Overview

This project is a **console-based Bank Management System** written in **C++**.
It allows users to manage bank client records using file handling, vectors, and structured data.
All client data is stored persistently in a text file (`Clients.txt`), with fields separated by the custom delimiter `#//#`.

### ⚙️ Core Features

* **View all clients** — Displays client data in a formatted table.
* **Add new clients** — Adds new client records after checking for duplicate account numbers.
* **Update client info** — Edits existing records and saves updates to file.
* **Delete clients** — Marks clients for deletion and rewrites file without them.
* **Find specific clients** — Searches by account number and displays details.
* **Transactions** — Includes deposit, withdrawal, and total balance summary.
* **Persistent storage** — Data is stored in a `.txt` file for future runs.

### 🧩 Technical Details

* **Language:** C++
* **Concepts used:**

  * File handling (`fstream`)
  * Vectors and loops
  * String parsing (`#//#` delimiter)
  * Structs and enums
  * Input validation
  * Menu-driven design (`switch`, `enum`)

### 🗂️ File Format

Each client record is stored in `Clients.txt` as:

```
AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance
```

**Example:**

```
A101#//#1234#//#Abu Khalid#//#0911223344#//#2500.75
```

### 🖥️ How It Works

1. On startup, the program loads all clients from `Clients.txt`.
2. Users navigate through menus to perform operations.
3. Updates are immediately written back to the file for persistence.
4. The system supports full CRUD functionality and simple transactions.

### 🧠 Learning Focus

This project demonstrates strong understanding of:

* File I/O (read/write/append)
* Vector operations and data manipulation
* String processing and parsing
* Modular programming with functions
* Struct-based record systems
* Console-based UI with formatted output (`iomanip`)

### 🚀 Future Improvements

* Add authentication (Admin Login)
* Support for CSV or JSON data storage
* Improved error handling and validation
* GUI integration using Qt or SFML
