#ifndef TASK_H
#define TASK_H

#include <string>
#include<queue>
using namespace std;

void main_menu(); //main menu

//define Task class
class Task{
public:
	string taskname;
	string duration;
	bool iscompleted;

	//constructor
	Task(string name, string due, bool comp);

	//getter
	string getTaskname();
	string getDueDate();
	bool getCompletionStatus();

	//setter
	void setCompletionStatus(bool completed);
};


//define TaskManager class
class TaskManager {
private:
	queue<Task> task_queue; //queue

public:
	void addData(); //add the task detail
	void process_next(queue<Task>& task_queue); //process to next task
	void displayAll(queue<Task> q); //display all the task
	void writeQueueToFile(queue<Task>& task_queue, string filename); //save the data into file
	void readQueueFromFile(queue<Task>& task_queue, string filename); //read the data from file
};

void task_menu(); //task menu

#endif //TASK_H