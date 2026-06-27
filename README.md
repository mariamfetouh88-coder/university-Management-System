# University Management System (Algorithms-Based)

A comprehensive C++ console application that combines **Object-Oriented Programming (OOP)** with **Advanced Data Structures and Algorithms (Level 3)** to solve real-world campus infrastructure and academic problems.

---

## 🚀 Key Features & Algorithms Used

Instead of building a traditional management system, this project integrates advanced graph algorithms to simulate an intelligent campus network:

| Feature | Description | Algorithm / Data Structure | Time Complexity |
| :--- | :--- | :--- | :--- |
| **Campus Navigation** | Finds the shortest path and distance between campus buildings. | **Dijkstra's Algorithm** (with Priority Queue) | O(E \log V) |
| **Network Optimization** | Designs the most cost-effective layout for laying campus internet/electricity cables without cycles. | **Kruskal's MST** & **DSU** (Manual Sorting) | O(E \log E)  |
| **Academic Path Planner** | Generates a recommended order for students to register for courses based on prerequisites. | **Topological Sort** (using DFS) | O(V + E) |
| **Core University Core** | Manages basic university entities like Students, Professors, and Courses. | **OOP Concepts** (Inheritance, Encapsulation) | Across all classes |

---

## 🛠️ System Architecture

The project is built using standard C++ with a clean OOP structure:
* `Person` (Base Class) ➔ `Student` & `Professor` (Derived Classes)
* `Course` ➔ Manages course codes, names, and prerequisites.
* `CampusNetwork` ➔ Handles the graph matrix, Dijkstra, and Kruskal's MST.
* `CourseManager` ➔ Handles the Topological Sorting for academic registration.

---

## 💻 How to Run the Project

1. Copy the entire C++ source code into your favorite IDE (Visual Studio, Code::Blocks, or VS Code).
2. Make sure you are using a standard C++ compiler (C++11 or higher).
3. Run the application. A dynamic console menu will appear to guide you through all features with pre-loaded demo data!

---
*Created with passion by Maryam Fattouh as a milestone for completing Level 3 Problem Solving track.* 🦾🚀