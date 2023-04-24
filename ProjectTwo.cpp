//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Robert Lulashi
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Project Two Parse through a CSV File to help an academic advising team
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// Definition of structure course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Function to split string to list of strings on the basis of the given delimiter
vector<string> splitString(string str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}



vector<Course> LoadDataStructure(string filename) {
    ifstream fin("ABCU_Advising_Program_Input.csv", ios::in); // Use the provided filename parameter
    vector<Course> courses;
    string line;

    // Read each line of the CSV file
    while (getline(fin, line)) {
        Course course;
        istringstream ss(line);

        // Read each comma-separated value from the line and store it in the course structure
        getline(ss, course.courseNumber, ',');
        getline(ss, course.name, ',');

        string prerequisitesString;
        getline(ss, prerequisitesString, ',');
        course.prerequisites = splitString(prerequisitesString, ';');

        courses.push_back(course);
    }

    fin.close();
    return courses;
}

// Printing course information of given course in proper format
void printCourse(Course course) {
    string courseNumber = course.courseNumber;
    string name = course.name;
    vector<string> prerequisites = course.prerequisites;

    cout << "Course Number: " << courseNumber << endl;
    cout << "Course Name: " << name << endl;
    cout << "Prerequisites: ";


    //Using iterator to iterate through prerequisites vector
    for (int i = 0; i < prerequisites.size(); i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << prerequisites[i];
    }
    cout << endl << endl;
}
void bubbleSort(vector<Course>& courses) {
    int n = courses.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                swap(courses[j], courses[j + 1]);
            }
        }
    }
}

// Printing course information of all courses in proper format, sorted by course number
void printCourseList(vector<Course> courses) {
    int n = courses.size();
    bubbleSort(courses); // Sort the courses vector by course number using bubble sort
    // Traversing list of courses to print all courses information
    for (int i = 0; i < static_cast<int>(courses.size()); i++) {
        cout << "Course Number: " << courses[i].courseNumber << endl;
        cout << "Course Name: " << courses[i].name << endl;
        cout << "Prerequisites: ";

        vector<string> prerequisites = courses[i].prerequisites;
        int j = 0;
        while (j < static_cast<int>(prerequisites.size())) {
            cout << prerequisites[j] << " ";
            j++;
        }
        cout << endl << endl;
    }
}
//search the course for the user entered course number
void searchCourse(vector<Course> courses) {
    int n = courses.size();
    string courseNumber;
    int found = 0;
    cout << "Enter course number: ";
    cin >> courseNumber;
    for (int i = 0; i < n; i++) {
        if (courses[i].courseNumber == courseNumber) {
            found = 1;
            cout << courses[i].courseNumber << ", " << courses[i].name << endl;
            cout << "Prerequisites: ";
            vector<string> prerequisites = courses[i].prerequisites;
            for (int j = 0; j < prerequisites.size(); j++) {
                if (j > 0) {
                    cout << ", ";
                }
                cout << prerequisites[j];
            }
            cout << endl;
            break;
        }
    }
    if (!found) {
        cout << "Course with given course number not found\n";
    }
}




int main() {
    vector<Course> courses;
    bool isLoaded = false;

    //Printing menu
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course\n";
    cout << "9. Exit\n";
    int ch;

    //loop will break once user enter 9
    do {
        //Prompt user to enter choice
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            courses = LoadDataStructure("ABCU_Advising_Program_Input.csv");
            isLoaded = true;
            cout << "Data loaded successfully." << endl;
            break;
        case 2:
            if (isLoaded) {
                printCourseList(courses);
            }
            else {
                cout << "Data has not been loaded yet. Please select option 1 to load data first." << endl;
            }
            break;
        case 3:
            if (isLoaded) {
                searchCourse(courses);
            }
            else {
                cout << "Data has not been loaded yet. Please select option 1 to load data first." << endl;
            }
            break;
        case 9:
            cout << "Thank you for using our course planner!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid choice." << endl;
            break;
        }
    } while (ch != 9);

    return 0;
}