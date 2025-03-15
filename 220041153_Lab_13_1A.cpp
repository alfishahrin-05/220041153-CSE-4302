#include <iostream>
#include <map>
#include <set>
#include <fstream>
using namespace std;

class Person 
{
    protected:
        int id;
        string name;
    public:
        Person(int i, string n) : id(i), name(n) {}
        Person() : id(0), name("") {}
        int getId() const 
        { 
            return id; 
        }
        string getName() const 
        { 
            return name; 
        }
        void setId(int i) 
        { 
            id = i; 
        }
        void setName(string n) 
        { 
            name = n;
        } 
};

class Course {
    private:
        string code, name;
        set<int> studentIDs;
        int instructorID;
    public:
        Course(string c, string n) : code(c), name(n), instructorID(-1) {}
        Course():code(""), name(""), instructorID(-1) {}
        string getCode() const 
        { 
            return code; 
        }
        string getName() const 
        { 
            return name;
        }
        int getInstructorID() const 
        { 
            return instructorID; 
        }
        set<int> getStudentIDs() const 
        { 
            return studentIDs; 
        }
        void setCode(string c) 
        { 
            code = c; 
        }
        void setName(string n) 
        { 
            name = n; 
        }
        void setInstructorID(int id) 
        { 
            instructorID = id; 
        }
        void addStudent(int id) 
        { 
            studentIDs.insert(id); 
        }
};
class Student:public Person 
{
    private:
        set<string> coursesEnrolled;
    public:
        Student(int i, string n) : Person(i, n) {}
        Student() : Person() {}
        set<string> getCoursesEnrolled() const 
        { 
            return coursesEnrolled; 
        }
        void enrollCourse(string course) 
        { 
            coursesEnrolled.insert(course); 
        }
};

class Instructor:public Person {
    private:
        set<string>coursesTeaching;
    public:
        Instructor(int i, string n) : Person(i, n) {}
        Instructor() : Person() {}
        set<string> getCoursesTeaching() const 
        { 
            return coursesTeaching; 
        }
        void assignCourse(string course) 
        { 
            coursesTeaching.insert(course); 
        }
};

map<string, Course> courses;
map<int, Student> students;
map<int, Instructor> instructors;

void addCourse() 
{
    string code, name;
    cout << "Enter course code: ";
    cin >> code;
    cin.ignore();
    cout << "Enter course name: ";
    getline(cin, name);
    courses[code] = Course(code, name);
    cout << "Course added successfully!\n";
}

void enrollStudent() {
    int id;
    string courseCode,name;
    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter course code: ";
    cin >> courseCode;
    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, name);
    if (courses.find(courseCode) == courses.end()) 
    {
        cout << "Course has not been found!\n";
        return;
    }
    students[id].setId(id);
    students[id].setName(name);
    students[id].enrollCourse(courseCode);
    courses[courseCode].addStudent(id);
    cout << "Student has been enrolled successfully!\n";
}

void assignInstructor() {
    int id;
    string courseCode, name;
    cout << "Enter instructor ID: ";
    cin >> id;
    cout << "Enter course code: ";
    cin >> courseCode;
    cin.ignore();
    cout << "Enter instructor name: ";
    getline(cin, name);
    if (courses.find(courseCode) == courses.end()) {
        cout << "Course not found!\n";
        return;
    }
    instructors[id].setId(id);
    instructors[id].setName(name);
    instructors[id].assignCourse(courseCode);
    courses[courseCode].setInstructorID(id);
    cout << "Instructor assigned successfully!\n";
}
void displayData() {
    cout << "Courses:\n";
    for (auto &c : courses) {
        cout << "Code: " << c.second.getCode() << ", Name: " << c.second.getName() << "\n";
        cout << "Instructor ID: " << c.second.getInstructorID() << "\n";
        cout << "Enrolled Students: ";
        for (int id : c.second.getStudentIDs()) cout << id << " ";
        cout << "\n";
    }
    
    cout << "Students:\n";
    for (auto &s : students) {
        cout << "Name: " << s.second.getName() << ", ID: " << s.second.getId() << "\nCourses Enrolled: ";
        for (auto &c : s.second.getCoursesEnrolled()) cout << c << " ";
        cout << "\n";
    }
    
    cout << "Instructors:\n";
    for (auto &i : instructors) {
        cout << "Name: " << i.second.getName() << ", ID: " << i.second.getId() << "\nCourses Teaching: ";
        for (auto &c : i.second.getCoursesTeaching()) cout << c << " ";
        cout << "\n";
    }
}
void saveData() {
    ofstream file("data.txt");
    for (auto &c : courses) {
        file << "C " << c.second.getCode() << " " << c.second.getName() << " " << c.second.getInstructorID() << " ";
        for (int id : c.second.getStudentIDs()) file << id << " ";
        file << "\n";
    }
    for (auto &s : students) {
        file << "S " << s.second.getId() << " " << s.second.getName() << " ";
        for (auto &c : s.second.getCoursesEnrolled()) file << c << " ";
        file << "\n";
    }
    for (auto &i : instructors) {
        file << "I " << i.second.getId() << " " << i.second.getName() << " ";
        for (auto &c : i.second.getCoursesTeaching()) file << c << " ";
        file << "\n";
    }
    file.close();
    cout << "Data saved successfully!\n";
}
void loadData() {
    ifstream file("data.txt");
    if (!file) return;
    
    courses.clear();
    students.clear();
    instructors.clear();
    
    string type;
    while (file >> type) {
        if (type == "C") {
            string code, name;
            int instructorID, studentID;
            file >> code >> name >> instructorID;
            courses[code] = Course(code, name);
            courses[code].setInstructorID(instructorID);
            while (file.peek() != '\n' && file >> studentID) //new line encounter na hoa porjonto read korte thake
                courses[code].addStudent(studentID);
        } 
        else if (type == "S") {
            int id;
            string name, courseCode;
            file >> id >> name;
            students[id] = Student(id, name);
            while (file.peek() != '\n' && file >> courseCode)
                students[id].enrollCourse(courseCode);
        } 
        else if (type == "I") {
            int id;
            string name, courseCode;
            file >> id >> name;
            instructors[id] = Instructor(id, name);
            while (file.peek() != '\n' && file >> courseCode)
                instructors[id].assignCourse(courseCode);
        }
    }
    file.close();
    cout << "Data loaded successfully!\n";
}
int main() 
{
    int choice;
    while (true) {
        cout << "\n1. Add Course\n2. Enroll Student\n3. Assign Instructor\n4. Display Data\n5. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) 
        {
            case 1: addCourse(); break;
            case 2: enrollStudent(); break;
            case 3: assignInstructor(); break;
            case 4: displayData(); break;
            case 5: saveData(); break;
            case 6: loadData(); break;
            case 7: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}