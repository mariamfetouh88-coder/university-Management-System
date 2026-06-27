#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include<algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

class Person {
private:
    int id;
    string name;
    string email;
public:
    Person(int id, string name, string email) {
        this->id = id;
        this->name = name;
        this->email = email;
    }


    int getId() { return id; }

    virtual void printDetails() {
        cout << " Person Information " << endl;
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
    }
};

class student : public Person {
private:
    double gpa;
    int level;
    vector<string> registered_courses;
public:
    student(int id, string name, string email, double gpa, int level) : Person(id, name, email) {
        this->gpa = gpa;
        this->level = level;
    }


    void registerCourse(string course_code) {
        registered_courses.push_back(course_code);
    }

    void printDetails() {
        Person::printDetails();
        cout << "GPA: " << gpa << endl;
        cout << "LEVEL: " << level << endl;
        cout << "Registered Courses: ";
        if (registered_courses.empty()) {
            cout << "No courses registered yet." << endl;
        }
        else {
            cout << endl;
            for (int i = 0; i < registered_courses.size(); i++) {
                cout << " - " << registered_courses[i] << endl;
            }
        }
    }
};

class Professor : public Person {
private:
    double salary;
    string department;
public:
    Professor(int id, string name, string email, double salary, string department) : Person(id, name, email) {
        this->salary = salary;
        this->department = department;
    }
    void printDetails() {
        Person::printDetails();
        cout << "Salary: " << salary << endl;
        cout << "Department: " << department << endl;
    }
};

class Course {
private:
    string course_code;
    string course_title;
    vector<string> prerequisites;
public:
    Course(string course_code, string course_title, vector<string> prerequisites) {
        this->course_code = course_code;
        this->course_title = course_title;

        this->prerequisites = prerequisites;
    }


    string getCourseCode() { return course_code; }
    vector<string> getPrerequisites() { return prerequisites; }
};

class CampusNetwork {

private:
    static const int MAX_BUILDINGS = 10;
    vector<Edge> edgeList;
    int adj[10][10];
public:
    CampusNetwork() {
        for (int i = 0; i < MAX_BUILDINGS; i++) {
            for (int j = 0; j < MAX_BUILDINGS; j++) {
                if (i == j) {
                    adj[i][j] = 0;
                }
                else {
                    adj[i][j] = 1e9;
                }
            }
        }
    }
    void addEdge(int u, int v, int w) {
        adj[u][v] = w;
        adj[v][u] = w;
        edgeList.push_back({ u, v, w });
    }
    void shortestPathPriorityQueue(int src, int dest) {
        int dist[MAX_BUILDINGS];
        for (int i = 0; i < MAX_BUILDINGS; i++) dist[i] = 1e9;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[src] = 0;
        pq.push({ 0, src });
        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            if (d > dist[u]) continue;
            for (int v = 0; v < MAX_BUILDINGS; v++) {
                if (adj[u][v] != 1e9) {
                    if (dist[u] + adj[u][v] < dist[v]) {
                        dist[v] = dist[u] + adj[u][v];
                        pq.push({ dist[v], v });
                    }
                }
            }
        }
        if (dist[dest] == 1e9) {
            cout << "No path exists between building " << src << " and building " << dest << endl;
        }
        else {
            cout << "Shortest distance (Using PQ) from building " << src << " to " << dest << " is: " << dist[dest] << " meters." << endl;
        }
    }
    int get(int x, int parent[]) {
        if (x == parent[x])return x;
        return parent[x] = get(parent[x], parent);
    }
    void optimizeCampusNetwork() {
        int parent[MAX_BUILDINGS];
        for (int i = 0; i < MAX_BUILDINGS; i++) {
            parent[i] = i;
        }
        for (int i = 0; i < edgeList.size(); i++) {
            for (int j = i + 1; j < edgeList.size(); j++) {
                if (edgeList[j].w < edgeList[i].w) {
                    Edge temp = edgeList[i];
                    edgeList[i] = edgeList[j];
                    edgeList[j] = temp;
                }
            }
        }

        int total_cost = 0;
        vector<Edge> mst_edges;

        cout << "\n--- Optimizing Campus Network (MST - Kruskal) ---" << endl;


        for (int i = 0; i < edgeList.size(); i++) {
            int u = edgeList[i].u;
            int v = edgeList[i].v;
            int w = edgeList[i].w;

            int root_u = get(u, parent);
            int root_v = get(v, parent);


            if (root_u != root_v) {
                parent[root_u] = root_v;
                total_cost += w;
                mst_edges.push_back(edgeList[i]);
            }
        }


        cout << "\n--- Optimizing Campus Network (MST - Kruskal) ---" << endl;
        cout << "Optimal Cables to Install:" << endl;
        for (int i = 0; i < mst_edges.size(); i++) {
            cout << "   Connect Building " << mst_edges[i].u
                << " with Building " << mst_edges[i].v
                << "  Distance: " << mst_edges[i].w << " meters." << endl;
        }
        cout << "\n Total Minimum Cable Length Required: " << total_cost << " meters." << endl;

    }
};

class CourseManager {

private:
    vector<Course> all_courses;
public:
    void addCourse(Course c) {
        all_courses.push_back(c);
    }
    void DFS(string current_course, vector<string>& order, vector<string>& visited) {
        visited.push_back(current_course);
        for (int i = 0; i < all_courses.size(); i++) {
            if (all_courses[i].getCourseCode() == current_course) {
                vector<string> pre = all_courses[i].getPrerequisites();


                for (int j = 0; j < pre.size(); j++) {

                    bool is_visited = false;
                    for (int k = 0; k < visited.size(); k++) {
                        if (visited[k] == pre[j]) is_visited = true;
                    }
                    if (!is_visited) {
                        DFS(pre[j], order, visited);
                    }
                }
            }
        }

        order.push_back(current_course);
    }
    void printAcademicPath() {
        vector<string> order;
        vector<string> visited;


        for (int i = 0; i < all_courses.size(); i++) {
            string c_code = all_courses[i].getCourseCode();
            bool is_visited = false;
            for (int k = 0; k < visited.size(); k++) {
                if (visited[k] == c_code) is_visited = true;
            }

            if (!is_visited) {
                DFS(c_code, order, visited);
            }
        }


        cout << "\n--- Recommended Academic Path (Topological Sort) ---" << endl;
        for (int i = 0; i < order.size(); i++) {
            cout << "  Step [" << i + 1 << "] ➔ " << order[i] << endl;
        }

    }

};

class UniversityManager {
private:
    vector<student> students;
    vector<Professor> professors;

public:
    void addStudent(student s) {
        students.push_back(s);
    }

    void addProfessor(Professor p) {
        professors.push_back(p);
    }


    void displayStudentDetails(int id) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                students[i].printDetails();
                return;
            }
        }
        cout << "Student with ID " << id << " not found." << endl;
    }
};



int main() {
    UniversityManager uni;
    CampusNetwork campus;
    CourseManager tracker;


    student s1(101, "Maryam Fattouh", "maryam@computers.edu", 4.0, 1);
    s1.registerCourse("CS101");
    s1.registerCourse("MA101");
    uni.addStudent(s1);

    Professor p1(201, "Dr. Ahmed", "ahmed@computers.edu", 15000, "Computer Science");
    uni.addProfessor(p1);


    campus.addEdge(0, 1, 50);
    campus.addEdge(0, 2, 150);
    campus.addEdge(1, 3, 30);
    campus.addEdge(2, 3, 20);
    campus.addEdge(3, 4, 60);


    vector<string> no_pre;
    tracker.addCourse(Course("CS101", "Intro to Programming", no_pre));

    vector<string> cs102_pre;
    cs102_pre.push_back("CS101");
    tracker.addCourse(Course("CS102", "OOP", cs102_pre));

    vector<string> ds_pre;
    ds_pre.push_back("CS102");
    tracker.addCourse(Course("CS201", "Data Structures", ds_pre));

    int choice;
    do {

        cout << "\n\n==================================================" << endl;
        cout << "       UNIVERSITY MANAGEMENT SYSTEM (LEVEL 3)     " << endl;
        cout << "==================================================" << endl;
        cout << " [1] Display Student Details" << endl;
        cout << " [2] Find Shortest Path Between Buildings (Dijkstra)" << endl;
        cout << " [3] Optimize Campus Cable Network (Kruskal MST)" << endl;
        cout << " [4] View Recommended Academic Path (Topological Sort)" << endl;
        cout << " [5] Exit" << endl;
        cout << "==================================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            int id;
            cout << " Enter Student ID (Try 101): ";
            cin >> id;
            cout << "\n--------------------------------------------------" << endl;
            uni.displayStudentDetails(id);
            cout << "--------------------------------------------------" << endl;
        }
        else if (choice == 2) {
            int src, dest;
            cout << " Enter Source Building (0 to 4): ";
            cin >> src;
            cout << " Enter Destination Building (0 to 4): ";
            cin >> dest;
            cout << "\n--------------------------------------------------" << endl;
            campus.shortestPathPriorityQueue(src, dest);
            cout << "--------------------------------------------------" << endl;
        }
        else if (choice == 3) {
            campus.optimizeCampusNetwork();
        }
        else if (choice == 4) {
            tracker.printAcademicPath();
        }
        else if (choice == 5) {
            cout << "\n>>> Exiting System. Goodbye, Maryam! <<<" << endl;
        }
        else {
            cout << " Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}