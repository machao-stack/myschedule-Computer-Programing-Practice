#include<iostream>
#include<string>
#include<ctime>
#include"Task.hpp"
#include<vector>
#include<fstream>

void saveTasks(const std::vector<Task>& tasks, const std::string& filename){
	std::ofstream file(filename);
	if(!file.is_open()){
		std::cerr << "Error: Cannot open file for saving."<<std::endl;
		return;
	}
	for(const auto& task : tasks){
		file << task.toFileString() << std::endl;
	}
	file.close();
}

std::vector<Task> loadTasks(const std::string& filename){
	std::vector<Task> tasks;
	std::ifstream file(filename);
	if(!file.is_open()){
		return tasks;
	}
	std::string line;
	while (std::getline(file,line)){
		if (!line.empty()){
			tasks.push_back(Task::fromFileString(line));
		}
	}
	file.close();
	return tasks;
}

int main(int argc,char* argv[])
{
	std::vector<Task> tasks;
	tasks = loadTasks("tasks.txt");
	std::cout << "Loaded " << tasks.size() << "tasks from file." << std::endl;

	if(argc < 2)
	{
		std::cout<<"Usage: myschedule <command>"<<std::endl;
		return 0;
	}

	std::string cmd = argv[1];

	if (cmd == "addtask"){
	if (argc < 4){
		std::cout << "Usage: myschedule addtask <name> <time>"<< std::endl;
		return 0;
	}

	std::string name = argv[2];
	std::time_t startTime = std::time(nullptr);

	Task task(name,startTime);
	tasks.push_back(task);
	std::cout << "Task added! ID: " << task.getId() << std::endl;
	saveTasks(tasks,"tasks.txt");
	}

	else if (cmd == "showtask"){
	if(tasks.empty()){
		std::cout << "No tasks found." <<std::endl;
	}
	else{
		std::cout << "All tasks:" << std::endl;
		for (size_t i=0; i < tasks.size();i++){
			std::cout << "ID: " << tasks[i].getId()
				<< ",Name: " << tasks[i].getName() << std::endl;
		}
	}
	}

	else if (cmd == "deltask"){
		std::cout << "deltask command - not implemented yet"<<std::endl;
	}

	else{
		std::cout<< "Unkown command. Use: addtask, showtask, deltask"<<std::endl;
	}

	return 0;
}
