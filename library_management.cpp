#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class Node
{
public:
	string key;
	Node* left;
	Node* right;

	Node(string item)
	{
		key = item;
		left = nullptr;
		right = nullptr;
	}
};

class Student
{
public:
	string name;
	int id_no;
	string field;
	string book1, book2;
	int book_no, issuedbook;

	Student()
	{
		id_no = 0;
		book_no = 0;
		issuedbook = 0;
		name = "";
		field = "";
		book1 = "";
		book2 = "";
	}

	Student(string name, int id_no, string field)
	{
		this->name = name;
		this->id_no = id_no;
		this->field = field;
		book1 = "";
		book2 = "";
		book_no = 0;
		issuedbook = 0;
	}

	Student(const Student& std)
	{
		name = std.name;
		id_no = std.id_no;
		field = std.field;
		book1 = std.book1;
		book2 = std.book2;
		book_no = std.book_no;
		issuedbook = std.issuedbook;
	}

	Student& operator=(const Student& std)
	{
		if (this != &std)
		{
			name = std.name;
			id_no = std.id_no;
			field = std.field;
			book1 = std.book1;
			book2 = std.book2;
			book_no = std.book_no;
			issuedbook = std.issuedbook;
		}
		return *this;
	}

	void display()
	{
		for (int i = 0; i < 10; i++)
		{
			cout << "\nName of Student: " << name << endl;
			cout << "Id of Student: " << id_no << endl;
			cout << "field of Student: " << field << endl;
		}
	}
};

class LibraryManagement
{
	Node* root;
	Student *students;

public:
	LibraryManagement(Student *std)
	{
		root = nullptr;
		students = std;
	}

	void customSwap(Student& a, Student& b)
	{
		Student temp = a;
		a = b;
		b = temp;
	}

	bool authenticateLibrarian(string username, string password)
	{
		return (username == "admin" && password == "123");
	}

	void librarianLogin(ifstream &reader)
	{
		string username, password;

		cout << "Enter librarian username: ";
		cin >> username;
		cout << "Enter librarian password: ";
		cin >> password;

		if (authenticateLibrarian(username, password))
		{
			cout << "Librarian login successful!" << endl;
			librarianMenu(reader);
		}
		else
		{
			cout << "Librarian login failed. Access denied." << endl;
		}
	}

	void librarianMenu(ifstream &reader)
	{
		int choice;
		do
		{
			cout << "\nLibrarian Menu:" << endl;
			cout << "1. Add Book\n2. Update Book\n3. Delete Book\n4. Display Books\n5. Logout" << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			if (choice == 1)
			{
				addBook(reader);
			}
			else if (choice == 2)
			{
				updateBook(reader);
			}
			else if (choice == 3)
			{
				deleteBook(reader);
			}
			else if (choice == 4)
			{
				displayBooks();
			}
			else if (choice == 5)
			{
				cout << "Logging out..." << endl;
			}
			else
			{
				cout << "Invalid choice. Try again." << endl;
			}
		} while (choice != 5);
	}

	void userLogin(ofstream &hist, ofstream &issue_book)
	{
		int userId;
		cout << "Enter your university ID (integer value): ";
		cin >> userId;

		if (userId == 201 || userId == 202 || userId == 203 || userId == 204 || userId == 205 || userId == 206 || userId == 207 || userId == 208 || userId == 209 || userId == 210)
		{
			userMenu(userId, hist, issue_book);
		}
		else
		{
			cout << "Invalid university ID. Access denied." << endl;
		}
	}

	void userMenu(int userId, ofstream &hist, ofstream &issue_book)
	{
		int choice;
		do
		{
			cout << "\nUser Menu for ID " << userId << ":" << endl;
			cout << "1. Issue Book\n2. Return Book\n3. View Issued Books\n4. Logout" << endl;
			cout << "Enter your choice: ";
			cin >> choice;

			if (choice == 1)
			{
				issueBook(userId, hist, issue_book);
			}
			else if (choice == 2)
			{
				returnBook(userId, hist, issue_book);
			}
			else if (choice == 3)
			{
				viewIssuedBooks(userId, issue_book);
			}
			else if (choice == 4)
			{
				cout << "Logging out...." << endl;
			}
			else
			{
				cout << "Invalid choice. Try again." << endl;
			}
		} while (choice != 4);
	}

	bool bookAvailability(string bookName)
	{
		Node* current = root;
		while (current != nullptr)
		{
			if (bookName == current->key)
			{
				return true;
			}
			else if (bookName < current->key)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		return false;
	}

	void bookIssued(int userId, string bookName, ofstream &hist, ofstream &issue_book)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (students[i].id_no == userId)
			{
				if (students[i].book_no == 0)
				{
					students[i].book1 = bookName;
					students[i].book_no = 1;
					students[i].issuedbook++;
					cout << "Book marked as issued to user with ID " << userId << ": " << bookName << endl;
					hist << "Student Name:   " << students[i].name << endl;
					hist << "Student ID  :   " << students[i].id_no << endl;
					hist << "Issued Book :   " << bookName << endl;
					issue_book << students[i].id_no <<" "<<bookName << endl;
					return;
				}
				else if (students[i].book_no == 1)
				{
					students[i].book2 = bookName;
					students[i].book_no = 2;
					students[i].issuedbook++;
					cout << "Book marked as issued to user with ID " << userId << ": " << bookName << endl;
					hist << "Student Name:   " << students[i].name << endl;
					hist << "Student ID  :   " << students[i].id_no << endl;
					hist << "Issued Book :   " << bookName << endl;
					issue_book << students[i].id_no << " " << bookName << endl;
					return;
				}
				else
				{
					cout << "User has already issued the maximum number of books." << endl;
					return;
				}
			}
		}
		cout << "User not found with ID: " << userId << endl;
	}

	bool bookIsIssuedToUser(int userId, string bookName, ofstream &issue_book)
	{
		string book_name[10];
		int k = 0, id[10] = { 0 };
		bool flag = false;

		issue_book.close();
		ifstream reading("issued_books.txt");

		while (!(reading.eof()))
		{
			reading >> id[k];
			reading.ignore();
			getline(reading, book_name[k]);
			k++;
		}

		reading.close();
		issue_book.open("issued_books.txt", ios::app);

		for (int i = 0; i < k; i++)
		{
			if (id[i] == userId && book_name[i] == bookName)
			{
				flag = true;
				break;
			}
			else
			{
				flag = false;
			}
		}

		if (flag == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void markBookAsReturned(int userId, string bookName, ofstream &hist, ofstream &issue_book)
	{
		string book_name[10];
		int i = 0, id[10] = { 0 };
	

		issue_book.close();
		ifstream reading("issued_books.txt");

		while (!(reading.eof()))
		{
			reading >> id[i];
			reading.ignore();
			getline(reading, book_name[i]);
			i++;
		}

		reading.close();
		issue_book.open("issued_books.txt");

		int j = 0;
		while (j<i)
		{
			if (bookName != book_name[j])
			{
				issue_book << id[j] << " " << book_name[j] << endl;
			}
			j++;
		}

		issue_book.close();
		issue_book.open("issued_books.txt", ios::app);

		for (int i = 0; i < 10; i++)
		{
			if (students[i].id_no == userId)
			{
				tm ltm = {};

				if (bookName == students[i].book1)
				{
					students[i].book1 = "";
					students[i].book_no = 0;
					students[i].issuedbook--;
					cout << "Book marked as returned by user with ID " << userId << ": " << bookName << endl;
					hist << "Student Name:   " << students[i].name << endl;
					hist << "Student ID  :   " << students[i].id_no << endl;
					hist << "Returned Book :   " << bookName << endl;
					hist << "Returned Date :   " << ltm.tm_mday << "/" << ltm.tm_mon + 1 << "/" << 1900 + ltm.tm_year << " "
						<< ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << endl << endl;
					return;
				}
				else if (bookName == students[i].book2)
				{
					students[i].book2 = "";
					students[i].book_no = 1;
					students[i].issuedbook--;
					cout << "Book marked as returned by user with ID " << userId << ": " << bookName << endl;
					hist << "Student Name:   " << students[i].name << endl;
					hist << "Student ID  :   " << students[i].id_no << endl;
					hist << "Returned Book :   " << bookName << endl;
					hist << "Returned Date :   " << ltm.tm_mday << "/" << ltm.tm_mon + 1 << "/" << 1900 + ltm.tm_year << " "
						<< ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << endl << endl;
					return;
				}
				else
				{
					cout << "Book marked as returned by user with ID " << userId << ": " << bookName << endl;
					hist << "Student Name:   " << students[i].name << endl;
					hist << "Student ID  :   " << students[i].id_no << endl;
					hist << "Returned Book :   " << bookName << endl;
					hist << "Returned Date :   " << ltm.tm_mday << "/" << ltm.tm_mon + 1 << "/" << 1900 + ltm.tm_year << " "
						<< ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << endl << endl;
					return;
				}
			}
		}
	}

	void displayIssuedBooks(int userId, ofstream &issue_book)
	{
		string book_name[10];
		int k = 0, id[10] = { 0 };
		bool flag = false;

		issue_book.close();
		ifstream reading("issued_books.txt");

		while (!(reading.eof()))
		{
			reading >> id[k];
			reading.ignore();
			getline(reading, book_name[k]);
			k++;
		}

		reading.close();
		issue_book.open("issued_books.txt", ios::app);
		
		for (int i = 0; i < k; i++)
		{
			if (id[i] == userId)
			{
				cout << "Book Name: " << book_name[i] << endl;
				flag = true;
			}
		}

		if (flag == false)
		{
			cout << "\nNo books issued by user with ID " << userId << "." << endl;
		}
	}

	void issueBook(int userId, ofstream &hist, ofstream &issue_book)
	{
		string bookName;
		cout << "Enter the name of the book to issue: ";
		cin.ignore();
		getline(cin, bookName);

		if (bookAvailability(bookName))
		{
			time_t now = time(0);
			tm* ltm = localtime(&now);  // Capture the returned pointer

			if (ltm != nullptr)
			{
				cout << "Book issued on: " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << 1900 + ltm->tm_year << " "
					<< ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;

				bookIssued(userId, bookName, hist, issue_book);

				hist << "Issued Date :   " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << 1900 + ltm->tm_year << " "
					<< ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl << endl;
			}
			else
			{
				cout << "Error getting local time." << endl;
			}
		}
		else
		{
			cout << "Book not available for issuance." << endl;
		}
	}

	void returnBook(int userId, ofstream &hist, ofstream &issue_book)
	{
		string bookName;
		cout << "Enter the name of the book to return: ";
		cin.ignore();
		getline(cin, bookName);

		if (bookIsIssuedToUser(userId, bookName, issue_book))
		{
			markBookAsReturned(userId, bookName, hist,issue_book);
			cout << "Book successfully returned." << endl;
		}
		else
		{
			cout << "You have not issued this book or the book is not valid for return." << endl;
		}
	}

	void viewIssuedBooks(int userId, ofstream &issue_book)
	{
		cout << "Books issued by user with ID " << userId << ":" << endl << endl;
		displayIssuedBooks(userId,issue_book);
	}

	void addBook(ifstream &reader)
	{
		string bookName;
		cout << "Enter book name to add: ";
		cin.ignore();
		getline(cin, bookName);

		reader.close();
		ofstream writer("books.txt", ios::app);
		writer << endl;
		writer << bookName;
		writer.close();
		reader.open("books.txt");

		insert(bookName);

		cout << "Book added successfully!" << endl;
	}

	void updateBook(ifstream &reader)
	{
		string oldBook, newBook;
		cout << "Enter the name of the book to update: ";
		cin.ignore();
		getline(cin, oldBook);

		cout << "Enter the new name of the book: ";
		getline(cin, newBook);

		update(oldBook, newBook);
		insert_books(reader);
		cout << "Book successfully updated." << endl;
	}

	void deleteBook(ifstream &reader)
	{
		string bookName;
		cout << "Enter the name of the book to delete: ";
		cin.ignore();
		getline(cin, bookName);

		deleteKey(bookName);
		insert_books(reader);
		cout << "Book successfully deleted." << endl;
	}

	void insert_booksRec(Node* node, ofstream &writer, int i)
	{
		if (node == nullptr)
			return;

		insert_booksRec(node->left, writer, i + 1);

		if (i == 0)
		{
			writer << node->key;
		}
		else
		{
			writer << endl;
			writer << node->key;
		}

		insert_booksRec(node->right, writer,i+1);
	}

	void insert_books(ifstream &reader)
	{
		int i = 0;
		reader.close();
		ofstream writer("books.txt");
		insert_booksRec(root, writer,i);
		writer.close();
		reader.open("books.txt");
	}

	void Selectionsort(Student arr[], int n)
	{
		for (int i = 0; i < n - 1; i++)
		{
			int min_idx = i;
			for (int j = i + 1; j < n; j++)
			if (arr[j].id_no < arr[min_idx].id_no)
				min_idx = j;

			customSwap(arr[min_idx], arr[i]);
		}
	}

	void displayBooks()
	{
		cout << "\nList of Books:" << endl;
		printInorder();
	}


	void insert(string key)
	{
		root = insertRec(root, key);
	}

	Node* insertRec(Node* root, string key)
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return root;
		}

		if (key < root->key)
			root->left = insertRec(root->left, key);
		else if (key > root->key)
			root->right = insertRec(root->right, key);
		else
			cout << "Error: Book with the same name already exists." << endl;

		return root;
	}

	void update(string key, string key1)
	{
		deleteKey(key);
		insert(key1);
	}

	bool containsNode(string value)
	{
		return containsNodeRecursive(root, value);
	}

	bool containsNodeRecursive(Node* current, string key)
	{
		if (current == nullptr)
			return false;

		if (key == current->key)
			return true;

		if (key < current->key)
		{
			containsNodeRecursive(current->left, key);
		}
		else
		{
			containsNodeRecursive(current->right, key);
		}
	}

	void printTree()
	{
		printTreeRec(root, 0, 0);
	}

	void printTreeRec(Node* t, int space, int level)
	{
		if (t == nullptr)
			return;

		space += 5;

		printTreeRec(t->right, space, level + 1);

		for (int i = 0; i < space; i++)
			cout << " ";
		cout << "[" << t->key << "]" << endl;

		printTreeRec(t->left, space, level + 1);
	}

	void deleteKey(string key)
	{
		root = deleteRec(root, key);
	}

	Node* deleteRec(Node* root, string key)
	{
		if (root == nullptr)
			return root;

		if (key < root->key)
			root->left = deleteRec(root->left, key);
		else if (key > root->key)
			root->right = deleteRec(root->right, key);
		else
		{
			if (root->left == nullptr)
				return root->right;
			else if (root->right == nullptr)
				return root->left;

			root->key = minValue(root->right);

			root->right = deleteRec(root->right, root->key);
		}

		return root;
	}

	string minValue(Node* root)
	{
		string minv = root->key;
		while (root->left != nullptr)
		{
			minv = root->left->key;
			root = root->left;
		}
		return minv;
	}

	void printInorderRec(Node* node)
	{
		if (node == nullptr)
			return;

		printInorderRec(node->left);

		cout << node->key << "        ";

		printInorderRec(node->right);
	}

	void printInorder()
	{
		printInorderRec(root);
	}
};

int main()
{
	Student *students = new Student[10];

	string fname, lname, field, books;
	int id = 0, i = 0;

	ifstream book("books.txt");
	ifstream student("students.txt");
	ofstream hist("history.txt", ios::app);
	ofstream issue_book("issued_books.txt", ios::app);

	if (!(book.is_open() || student.is_open() || hist.is_open() || issue_book.is_open()))
	{
		cout << "\nFiles Not Found" << endl;
	}
	else
	{
		while (i<10)
		{
			student >> fname;
			student >> lname;
			student >> id;
			student >> field;

			students[i].name = fname + " " + lname;
			students[i].id_no = id;
			students[i].field = field;
			i++;
		}

		LibraryManagement tree(students);

		while (!(book.eof()))
		{
			getline(book, books);
			tree.insert(books);
		}

		bool option = false;

		while (!option)
		{
			cout << "\n....................................." << endl;
			cout << "1. Librarian Login." << endl;
			cout << "2. User Login." << endl;
			cout << "3. Exit." << endl;
			cout << "\n....................................." << endl;

			cout << "\nEnter Your choice:" << endl;
			int ch1;
			cin >> ch1;

			if (ch1 == 1)
			{
				tree.librarianLogin(book);
			}
			else if (ch1 == 2)
			{
				tree.userLogin(hist, issue_book);
			}
			else if (ch1 == 3)
			{
				option = true;
			}
			else
			{
				cout << "Invalid choice. Try again." << endl;
			}
		}
	}

	hist.close();
	book.close();
	student.close();

	delete[] students;
	system("pause");
	return 0;
}
