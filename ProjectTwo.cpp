//============================================================================
// Name        : Project Two
// Author      : Stephen Chryn
// Version     : 1.0
// Copyright   : ISC Copyright � 2024 Stephen Chryn
// Description : Develop code using algorithms and data structures to solve
//                 basic programming problems
//============================================================================

#include <algorithm> // for std::sort
#include <fstream>
#include <iostream>
#include <limits> // for std::numeric_limits
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Struct to hold the information about each course
struct Course {
  std::string courseId;
  std::string title;
  std::string prereq1;
  std::string prereq2;

  // Function to print the course details
  void print() const {
    std::cout << "Course ID: " << courseId << "\nTitle: " << title;
    if (!prereq1.empty())
      std::cout << "\nPrerequisite 1: " << prereq1;
    if (!prereq2.empty())
      std::cout << "\nPrerequisite 2: " << prereq2;
    std::cout << std::endl;
  }
};

// Function to read the course data from a file and load it into a map
std::map<std::string, Course> loadCourseData(const std::string &filename) {
  std::map<std::string, Course> courses;
  std::ifstream file(filename);
  std::string line;

  // Check if the file was successfully opened
  if (!file) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return courses;
  }

  // Read each line from the file
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string courseId, title, prereq1, prereq2;

    // Parse the line into course fields
    std::getline(ss, courseId, ',');
    std::getline(ss, title, ',');
    std::getline(ss, prereq1, ',');
    std::getline(ss, prereq2, ',');

    // Trim any whitespace from parsed fields
    courseId.erase(courseId.find_last_not_of(" \n\r\t") + 1);
    title.erase(title.find_last_not_of(" \n\r\t") + 1);
    prereq1.erase(prereq1.find_last_not_of(" \n\r\t") + 1);
    prereq2.erase(prereq2.find_last_not_of(" \n\r\t") + 1);

    // Create a Course struct and add it to the map
    Course course{courseId, title, prereq1, prereq2};
    courses[courseId] = course;
  }

  file.close();
  return courses;
}

// Function to print all courses in alphanumeric order
void printAllCourses(const std::map<std::string, Course> &courses) {
  std::vector<std::string> courseIds;

  // Collect all course IDs
  for (const auto &pair : courses) {
    courseIds.push_back(pair.first);
  }

  // Sort the course IDs alphanumerically using the standard sort method
  std::sort(courseIds.begin(), courseIds.end());

  // Print the sorted course list with course titles
  for (const auto &id : courseIds) {
    std::cout << id << " - " << courses.at(id).title << std::endl;
  }
}

// Function to print details of a specific course, including prerequisites
void printCourseDetails(const std::map<std::string, Course> &courses) {
  std::string courseId;
  std::cout << "Enter the course ID: ";
  std::cin >> courseId;

  // Search for the course in the map
  auto it = courses.find(courseId);
  if (it != courses.end()) {
    // Print the course title
    std::cout << "Course Title: " << it->second.title << std::endl;

    // Print the first prerequisite if it exists and is valid
    if (!it->second.prereq1.empty()) {
      auto prereq1It = courses.find(it->second.prereq1);
      if (prereq1It != courses.end()) {
        std::cout << "Prerequisite 1: " << prereq1It->second.courseId << " - "
                  << prereq1It->second.title << std::endl;
      } else {
        std::cout << "Prerequisite 1: " << it->second.prereq1
                  << " (Course not found)" << std::endl;
      }
    }

    // Print the second prerequisite if it exists and is valid
    if (!it->second.prereq2.empty()) {
      auto prereq2It = courses.find(it->second.prereq2);
      if (prereq2It != courses.end()) {
        std::cout << "Prerequisite 2: " << prereq2It->second.courseId << " - "
                  << prereq2It->second.title << std::endl;
      } else {
        std::cout << "Prerequisite 2: " << it->second.prereq2
                  << " (Course not found)" << std::endl;
      }
    }

  } else {
    std::cout << "Error: Course ID '" << courseId << "' not found."
              << std::endl;
  }
}

// Function to clear the input stream in case of an error
void clearInputStream() {
  std::cin.clear(); // Clear the error flag on the stream
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Main function with a menu system for user interaction
int main() {
  std::map<std::string, Course> courses; // Map to hold the courses
  int option; // Variable to store user menu selection

  do {
    // Display the menu options
    std::cout << "\nMenu Options:\n";
    std::cout << "1. Load the file data into the data structure\n";
    std::cout << "2. Print an alphanumeric list of all the courses in the "
                 "Computer Science and Math departments\n";
    std::cout << "3. Print the course title and the prerequisites for any "
                 "individual course\n";
    std::cout << "9. Exit the program\n";
    std::cout << "Enter your choice: ";
    std::cin >> option;

    // Handle input errors and clear the stream
    if (std::cin.fail()) {
      std::cout << "Error: Invalid input. Please enter a valid number."
                << std::endl;
      clearInputStream();
      continue; // Restart the loop after clearing input
    }

    clearInputStream();

    // Handle menu options based on user input
    switch (option) {
    case 1: {
      std::string filename;
      std::cout << "Enter the filename containing course data: ";
      std::getline(
          std::cin,
          filename); // Use std::getline to allow spaces in the filename
      courses = loadCourseData(filename); // Load the course data from the file
      std::cout << "Data loaded successfully." << std::endl;
      break;
    }
    case 2:
      if (courses.empty()) {
        std::cout << "Error: No data loaded. Please load data first."
                  << std::endl;
      } else {
        printAllCourses(courses); // Print all courses in alphanumeric order
      }
      break;
    case 3:
      if (courses.empty()) {
        std::cout << "Error: No data loaded. Please load data first."
                  << std::endl;
      } else {
        printCourseDetails(courses); // Print details of a specific course
      }
      break;
    case 9:
      std::cout << "Exiting program." << std::endl;
      break;
    default:
      std::cout << "Error: Invalid option. Please try again." << std::endl;
      break;
    }
  } while (option != 9); // Continue until the user chooses to exit

  return 0;
}
