#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <limits>
using namespace std;

void Display1();
void Display2();
void Display3();
void Display4();
void Display5();

tm incrementDays(const tm& original, int days) {
    tm copy = original;
    copy.tm_mday += days;
    mktime(&copy); 
    return copy;
}

int main()
{
    int choice;
    do {	
    cout << "\n\n\nSpaced Repetitions \n\n";
    cout << " 1. Add revision \n";
    cout << " 2. Check to revise today \n";
    cout << " 3. Print each line of revisions \n";
    cout << " 4. Add/Check Solution \n";
    cout << " 5. Remove a task \n";
    cout << " 6. Exit Program \n";
    cout << "\nYour choice: ";
    cin >> choice; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch (choice)
    {
        case 1:
        	system("cls");
            Display1();
            break;
        case 2:
        	system("cls");
            Display2();
            break;
        case 3:
        	system("cls");
            Display3();
            break;
        case 4:
        	system("cls");
            Display4();
            break;    
        case 5:
        	system("cls");
            Display5();
            break;  
        case 6: 
			system("cls");
			cout << "Exiting program... \n";
			return 0;   
        default:
        	system("cls");
            cout << "Invalid Choice: \n";
            break;            
    }
} while (choice!=6);
return 0;
}


void Display1()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    tm* now_tm = localtime(&now_time);

    string task;
    cout << "Enter your task: ";
    getline(cin, task);

    string filename = "tasks.txt";

    ofstream outfile(filename, ios::app); 
    if (outfile.is_open()) {
        char buffer[80];
        
        strftime(buffer, sizeof(buffer), "%d-%m-%Y-%H:%M:%S", now_tm);
        outfile << buffer << " - " << task << endl;

        for (int i = 1; i <= 16; i += 3) { 
            tm incrementedDate = incrementDays(*now_tm, i);
            strftime(buffer, sizeof(buffer), "%d-%m-%Y-%H:%M:%S", &incrementedDate);
            outfile << buffer << " - " << task << endl;
        }

        outfile.close();
        cout << "Task saved to " << filename << endl;
    } else {
        cerr << "Unable to open file " << filename << endl;
    }
}

void Display2()
{
    string filename = "tasks.txt";
    ifstream infile(filename);

    if (!infile.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    vector<pair<int, string>> lines;
    string line;

    while (getline(infile, line)) {
        int day = stoi(line.substr(0, 2)); 
        if (day!= -1) {
            lines.push_back(make_pair(day, line));
        }
    }

    infile.close();

    if (lines.empty()) {
        cout << "No valid dates found in the file." << endl;
        return;
    }

    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_time);
    int currentDay = now_tm->tm_mday;

    bool tasksFound = false;
    for (const auto& task : lines) {
        if (task.first == currentDay) {
            cout << "To revise today: " << task.second << endl;
            tasksFound = true;
        }
    }

    if (!tasksFound) {
        cout << "No tasks to revise today." << endl;
    }
}


void Display3()
{

    string filename = "tasks.txt";
	
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
}

void Display4() {
    int option;
    do {
        system("cls");
        cout << "1. Add a solution\n";
        cout << "2. View a solution\n";
        cout << "3. Delete a solution\n";
        cout << "4. Back to main menu\n";
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");

        if (option == 1) {
            
            ifstream tasksFile("tasks.txt");
            if (!tasksFile.is_open()) {
                cerr << "Unable to open file tasks.txt" << endl;
                system("pause");
                continue;
            }

            map<string, int> taskMap;
            string line;
            while (getline(tasksFile, line)) {
                size_t pos = line.find(" - ");
                if (pos != string::npos) {
                    string task = line.substr(pos + 3);
                    taskMap[task]++;
                }
            }
            tasksFile.close();

            if (taskMap.empty()) {
                cout << "No tasks found." << endl;
                system("pause");
                continue;
            }

            int taskIndex = 1;
            vector<string> taskList;
            cout << "List of tasks:\n";
            for (const auto& task : taskMap) {
                cout << taskIndex << ". " << task.first << " (x" << task.second << ")" << endl;
                taskList.push_back(task.first);
                taskIndex++;
            }

            cout << "Select a task by number: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice <= 0 || choice > taskList.size()) {
                cout << "Invalid selection." << endl;
                system("pause");
                continue;
            }

            string selectedTask = taskList[choice - 1];

            cout << "Enter the solution for the task: ";
            string solution;
            getline(cin, solution);

            ofstream outfile("sols.txt", ios::app);
            if (outfile.is_open()) {
                ifstream infile("sols.txt");
                int count = 0;
                while (getline(infile, line)) {
                    size_t pos = line.find(" - Solution:");
                    if (pos != string::npos && line.substr(0, pos) == selectedTask) {
                        count++;
                    }
                }
                infile.close();

                outfile << selectedTask << " (" << count + 1 << ") - Solution: " << solution << endl;
                outfile.close();
                cout << "Solution saved to sols.txt" << endl;
            } else {
                cerr << "Unable to open file sols.txt" << endl;
            }
            system("pause");
            system("cls");

        } else if (option == 2) {
            
            ifstream infile("sols.txt");
            if (!infile.is_open()) {
                cerr << "Unable to open file sols.txt" << endl;
                system("pause");
                continue;
            }

            map<string, int> solutionMap;
            string line;
            while (getline(infile, line)) {
                size_t pos = line.find(" - Solution:");
                if (pos != string::npos) {
                    string task = line.substr(0, pos);
                    solutionMap[task]++;
                }
            }
            infile.close();

            if (solutionMap.empty()) {
                cout << "No solutions found." << endl;
                system("pause");
                continue;
            }

            int taskIndex = 1;
            vector<string> taskList;
            cout << "List of tasks with solutions:\n";
            for (const auto& task : solutionMap) {
                cout << taskIndex << ". " << task.first << " (x" << task.second << ")" << endl;
                taskList.push_back(task.first);
                taskIndex++;
            }

            cout << "Select a task by number: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice <= 0 || choice > taskList.size()) {
                cout << "Invalid selection." << endl;
                system("pause");
                continue;
            }

            string selectedTask = taskList[choice - 1];

            ifstream infile2("sols.txt");
            if (!infile2.is_open()) {
                cerr << "Unable to open file sols.txt" << endl;
                system("pause");
                continue;
            }

            cout << "Solutions for " << selectedTask << ":\n";
            while (getline(infile2, line)) {
                size_t pos = line.find(" - Solution:");
                if (pos != string::npos) {
                    string taskInFile = line.substr(0, pos);

                    if (taskInFile == selectedTask) {
                        // Display the full solution line
                        cout << line << endl;
                    }
                }
            }
            infile2.close();

            system("pause");
            system("cls");

        } else if (option == 3) {
            
            ifstream infile("sols.txt");
            if (!infile.is_open()) {
                cerr << "Unable to open file sols.txt" << endl;
                system("pause");
                continue;
            }

            vector<string> solutions;
            string line;
            while (getline(infile, line)) {
                solutions.push_back(line);
            }
            infile.close();

            if (solutions.empty()) {
                cout << "No solutions found." << endl;
                system("pause");
                continue;
            }

            cout << "List of solutions:\n";
            for (size_t i = 0; i < solutions.size(); ++i) {
                cout << i + 1 << ". " << solutions[i] << endl;
            }

            cout << "Select a solution to delete by number: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice <= 0 || choice > solutions.size()) {
                cout << "Invalid selection." << endl;
                system("pause");
                continue;
            }

            solutions.erase(solutions.begin() + choice - 1);

            ofstream outfile("sols.txt");
            if (!outfile.is_open()) {
                cerr << "Unable to open file sols.txt" << endl;
                system("pause");
                continue;
            }

            for (const auto& sol : solutions) {
                outfile << sol << endl;
            }
            outfile.close();

            cout << "Solution deleted successfully." << endl;
            system("pause");
            system("cls");

        } else if (option != 4) {
            
            cout << "Invalid option." << endl;
            system("pause");
            system("cls");
        }
    } while (option != 4);
}


void Display5() {
    string taskToRemove;
    cout << "Enter the name of the task to remove: ";
    getline(cin, taskToRemove);

    string filename = "tasks.txt";
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    vector<string> tasks;
    string line;
    while (getline(infile, line)) {
        if (line.find(taskToRemove) == string::npos) {
            tasks.push_back(line);
        }
    }
    infile.close();

    if (tasks.empty()) {
        cout << "No tasks found with the name '" << taskToRemove << "'.\n";
        return;
    }

    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const auto& task : tasks) {
            outfile << task << endl;
        }
        outfile.close();
        cout << "All instances of task '" << taskToRemove << "' have been removed.\n";
    } else {
        cerr << "Unable to open file " << filename << endl;
    }
}


