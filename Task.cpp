#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include "Task.h" //header file

using namespace std;

//constructor
Task::Task(string tname, string due, bool comp) : taskname(tname), duration(due), iscompleted(comp){}

string Task::getTaskname() {
	return taskname;
}

string Task::getDueDate() {
	return duration;
}

bool Task::getCompletionStatus() {
	return iscompleted;
}

void Task::setCompletionStatus(bool completed) {
	iscompleted = completed;
}

//add the task data 
void TaskManager::addData() {
	readQueueFromFile(task_queue, "task.txt");
	queue<Task> task_queue;
	string name, due;
	bool comp = false;
	cout << "Enter the task:";
	cin >> name;
	cout << "Enter the duration(in days):";
	cin >> due;
	Task task(name, due, comp);
	task_queue.push(task);
	writeQueueToFile(task_queue, "task.txt");
}

//process to next task
void TaskManager::process_next(queue<Task>& task_queue) {
	readQueueFromFile(task_queue, "task.txt"); //read the data from file to queue
	while (!task_queue.empty()) {
		Task task = task_queue.front();
		task.setCompletionStatus(true);
		task_queue.pop();
		cout << "Processing task: " << task.getTaskname() << std::endl;

		ofstream outFile("task.txt");
		while (!task_queue.empty()) {
			Task task = task_queue.front();
			outFile << task.getTaskname() << "," << task.getDueDate() << "," << task.getCompletionStatus()<< std::endl;
			task_queue.pop();	
		}

		outFile.close();
	}
}

//display all the task by recursion
void TaskManager::displayAll(queue<Task> q) {
	while (!q.empty()) {
		Task task = q.front();
		q.pop();
		cout << "Task name: " << task.taskname << ", Duration(in days): " << task.duration << endl;
	}
}


//save the task detail from queue to file
void TaskManager::writeQueueToFile(queue<Task>& task_queue, string filename) {
	ofstream outputFile(filename, ios_base::app);
	if (outputFile.is_open()) {
		Task task = task_queue.back();
		outputFile << task.getTaskname() << "," << task.getDueDate() << "," << task.getCompletionStatus() << "\n";
		cout << "Task is successfully added."  << "\n";
	}
	else {
		cout << "Unable to open file " << filename << "\n";
	}
}

//load the task data from file to queue 
void TaskManager::readQueueFromFile(queue<Task>& q, string filename) {
	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		cerr << "Error opening file " << filename << endl;
		return;
	}

	string line;
	while (getline(inputFile, line)) {
		string desc, dueDate;
		bool completed;

		// Read the description
		size_t pos1 = 0, pos2 = line.find(',');
		desc = line.substr(pos1, pos2 - pos1);

		// Read the due date
		pos1 = pos2 + 1;
		pos2 = line.find(',', pos1);
		dueDate = line.substr(pos1, pos2 - pos1);

		// Read the completed flag
		pos1 = pos2 + 1;
		pos2 = line.size();
		completed = line.substr(pos1, pos2 - pos1) == "true";

		Task task(desc, dueDate, completed);
		q.push(task);
	}
}

//task menu
void task_menu() {
	system("cls");
	int ch;
	char choice;
	queue<Task> task_queue; //define queue
	TaskManager man;
	
		cout << "TASK MANAGEMENT" << endl;
		cout << "----------------------------" << endl;
		cout << "1. Add a task" << endl;
		cout << "2. Process to the next task" << endl;
		cout << "3. Display all the task" << endl;
		cout << "4. Back to main menu" << endl << endl;
		
		cout << "Select one option:";
		cin >> ch;
		
		switch (ch) {
		case 1:
			system("cls");
			man.addData(); //add the task
			cout << "Back to menu(Y/N)";
			cin >> choice;
			switch (choice) {
			case 'Y':
				task_menu(); //back to task menu
				break;
			case 'N':
				break;
			}
			break;
		case 2:
			system("cls");
			man.process_next(task_queue); //process to next task
			cout << "Back to menu(Y/N)";
			cin >> choice;
			switch (choice) {
			case 'Y':
				task_menu(); //back to task menu
				break;
			case 'N':
				break;
			}
			break;
		case 3:
			system("cls");
			man.readQueueFromFile(task_queue, "task.txt");
			cout << "All Tasks:" << endl;
			man.displayAll(task_queue); //display all the task
			cout << "Back to menu(Y/N)";
			cin >> choice;
			switch (choice) {
			case 'Y':
				task_menu(); //back to task menu
				break;
			case 'N':
				break;
			}
			break;
		case 4:
			main_menu(); //back to main menu
			break;
			break;
		default:
			cout << "Please select valid option" << endl;
			break;
		}
}