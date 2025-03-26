#include <iostream> 
#include <string> 
#include <algorithm> 

using namespace std; 

int MAX_STUDENTS = 5; 

struct Student { 
    int studentID; 
    string firstName; 
    string lastName; 
    string course; 
    float gpa; 
}; 

Student students[5]; 
int studentCount = 0; 

void displayMenu() { 
    cout << "\nMenu:\n"; 
    cout << "1. Add Student\n"; 
    cout << "2. Edit Student\n"; 
    cout << "3. Delete Student\n"; 
    cout << "4. Search Student\n"; 
    cout << "5. Display Students\n"; 
    cout << "6. Exit Program\n"; 
    cout << "Enter your choice: "; 
} 

bool isValidStudentID(int id) { 
    return id >= 100000000 && id <= 999999999; 
} 

bool isValidGPA(float gpa) { 
    return gpa >= 0.0; 
} 

int findStudentByID(int id) { 
    for (int i = 0; i < studentCount; i++) { 
        if (students[i].studentID == id) { 
            return i; 
        } 
    } 
    return -1; 
} 

void addStudent() { 
    if (studentCount >= MAX_STUDENTS) { 
        cout << "Student list is full.\n"; 
        return; 
    } 

    Student newStudent; 
    cout << "Enter Student ID (9-digit positive number): "; 
    cin >> newStudent.studentID; 

    if (cin.fail() || !isValidStudentID(newStudent.studentID)) { 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Error: Invalid Student ID. Must be a 9-digit positive number.\n"; 
        return; 
    } 

    if (findStudentByID(newStudent.studentID) != -1) { 
        cout << "Error: Duplicate Student ID.\n"; 
        return; 
    } 

    cout << "Enter First Name: "; 
    cin >> newStudent.firstName; 
    cout << "Enter Last Name: "; 
    cin >> newStudent.lastName; 
    cout << "Enter Course: "; 
    cin >> newStudent.course; 

    cout << "Enter Previous Semestral GPA: "; 
    cin >> newStudent.gpa; 

    if (cin.fail() || !isValidGPA(newStudent.gpa)) { 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Error: Invalid GPA. Must be a positive number.\n"; 
        return; 
    } 

    students[studentCount] = newStudent; 
    studentCount++; 
    cout << "Student added successfully.\n"; 
} 

void editStudent() { 
    int id; 
    cout << "Enter Student ID to edit: "; 
    cin >> id; 

    if (cin.fail() || !isValidStudentID(id)) { 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Error: Invalid Student ID.\n"; 
        return; 
    } 

    int index = findStudentByID(id); 
    if (index == -1) { 
        cout << "Student not found.\n"; 
        return; 
    } 

    cout << "Enter New First Name: "; 
    cin >> students[index].firstName; 
    cout << "Enter New Last Name: "; 
    cin >> students[index].lastName; 
    cout << "Enter New Course: "; 
    cin >> students[index].course; 

    cout << "Enter New GPA (must be positive): "; 
    cin >> students[index].gpa; 

    if (cin.fail() || !isValidGPA(students[index].gpa)) { 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Error: Invalid GPA. Must be a positive number.\n"; 
        return; 
    } 

    cout << "Student updated successfully.\n"; 
} 

void deleteStudent() { 
    int id; 
    cout << "Enter Student ID to delete: "; 
    cin >> id; 

    if (cin.fail() || !isValidStudentID(id)) { 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Error: Invalid Student ID.\n"; 
        return; 
    } 

    int index = findStudentByID(id); 
    if (index == -1) { 
        cout << "Student not found.\n"; 
        return; 
    } 

    for (int i = index; i < studentCount - 1; i++) { 
        students[i] = students[i + 1]; 
    } 

    studentCount--; 
    cout << "Student deleted successfully.\n"; 
} 

void searchStudent() { 
    int id; 
    cout << "Enter Student ID to search: "; 
    cin >> id; 

    if (cin.fail() || !isValidStudentID(id)) { 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Error: Invalid Student ID.\n"; 
        return; 
    } 

    int index = findStudentByID(id); 
    if (index == -1) { 
        cout << "Student not found.\n"; 
        return; 
    } 

    cout << "\nStudent Details:\n"; 
    cout << "ID: " << students[index].studentID << "\n"; 
    cout << "Name: " << students[index].firstName << " " << students[index].lastName << "\n"; 
    cout << "Course: " << students[index].course << "\n"; 
    cout << "GPA: " << students[index].gpa << "\n"; 
} 

void displayStudents() { 
    if (studentCount == 0) { 
        cout << "No students to display.\n"; 
        return; 
    } 

    sort(students, students + studentCount, [](const Student &a, const Student &b) { 
        return a.lastName < b.lastName; 
    }); 

    cout << "\nStudent Records (Sorted by Last Name):\n"; 
    for (int i = 0; i < studentCount; i++) { 
        cout << "ID: " << students[i].studentID  
             << ", Name: " << students[i].firstName << " " << students[i].lastName 
             << ", Course: " << students[i].course 
             << ", GPA: " << students[i].gpa << "\n"; 
    } 
} 

int main() { 
    int choice; 
    do { 
        displayMenu(); 
        cin >> choice; 

        if (cin.fail() || choice < 1 || choice > 6) { 
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            cout << "Invalid input. Please enter a number between 1 and 6.\n"; 
            continue; 
        } 

        switch (choice) { 
            case 1: addStudent(); break; 
            case 2: editStudent(); break; 
            case 3: deleteStudent(); break; 
            case 4: searchStudent(); break; 
            case 5: displayStudents(); break; 
            case 6: cout << "Exiting program...\n"; break; 
            default: cout << "Invalid choice. Please try again.\n"; 
        } 
    } while (choice != 6); 

    return 0; 
}