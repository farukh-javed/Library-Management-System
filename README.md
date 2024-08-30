# 📚 Library Management System

A simple console-based Library Management System built in C++ to help manage books and users in a library setting.

## ✨ Features

- **🔒 Librarian Login:**
  - Secure login with a predefined username and password.
  - Add new books to the library collection.
  - Update and delete existing books.
  - Display all available books.
  - View and manage all issued books.

- **👥 User Login:**
  - Secure login using a valid university ID.
  - Search for books and issue them.
  - Return books to the library.
  - View books currently issued to them.

## 📂 Project Structure

- **`main.cpp`**: The main source file containing all functionalities for the system.

## 🏷️ Key Classes

- **`Node`**: Represents each book in the system using a binary search tree structure.
- **`Student`**: Represents user information including name, ID, and issued books.
- **`LibraryManagement`**: Core class handling all library operations like book management and user transactions.

## 🚀 How to Run

### Prerequisites

- A C++ compiler (e.g., GCC, Clang).

### Steps to Run

1. **Compile the program**:
   ```bash
   g++ main.cpp -o library_management_system
   ```

2. **Execute the program**:
   ```bash
   ./library_management_system
   ```

### 📝 Usage Instructions

- **Librarian**:
  - Username: `admin`
  - Password: `123`
- **Users**:
  - Enter a valid university ID (e.g., 201, 202, ...).

## 📁 File Operations

- **`books.txt`**: Stores details about all books in the library.
- **`issued_books.txt`**: Tracks the books that have been issued to users.

> ⚠️ Ensure that both `books.txt` and `issued_books.txt` files are in the same directory as the executable for the application to function correctly.

## 🤝 Contribution Guidelines

We welcome contributions to enhance this project! Please fork this repository and create a pull request with your improvements.

## 📄 License

GNU v3 License. See LICENSE for details.
