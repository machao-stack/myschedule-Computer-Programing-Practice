#include<iostream>
#include<string>
#include<ctime>
#include"Task.hpp"
#include<vector>
#include<fstream>
#include<thread>
#include<chrono>

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

void reminderLoop(std::vector<Task>& tasks){
	while(true) {
		std::this_thread::sleep_for(std::chrono::seconds(10));

		std::time_t now = std::time(nullptr);

		for(auto& task : tasks){
			if(!task.isReminded() && task.getStartTime() <= now) {
				std::cout << "\n[REMINDER] Task \"" << task.getName()
					<<"\" (ID: " << task.getId() << ") is due!" << std::endl;
				task.setReminded(true);
			}
		}
	}
}

int main(int argc,char* argv[])
{
	std::string username = "admin";
	std::string passwordHash = std::to_string(std::hash<std::string>{}("123456"));

	std::string inputUser, inputPass;
	std::cout << "Username:";
	std::cin>>inputUser;
	std::cout<< "Password:";
	std::cin >> inputPass;

	if (inputUser != username || std::to_string(std::hash<std::string>{}(inputPass))!= passwordHash){
		std::cout << "Login failed." << std::endl;
		return 0;
	}

	std::cout << "Login successful."<<std::endl;

	std::vector<Task> tasks;

	tasks = loadTasks("tasks.txt");
	std::cout << "Loaded " << tasks.size() << "tasks from file." << std::endl;
	std::thread reminderThread(reminderLoop, std::ref(tasks));
        reminderThread.detach();


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
	if (argc < 3){
		std::cout << "Usage: myschedule deltask <id>" <<std::endl;
		return 0;
	}

	int id = std::stoi(argv[2]);
	bool found = false;

	for(size_t i = 0; i<tasks.size(); i++){
		if (tasks[i].getId() == id){
			tasks.erase(tasks.begin() + i);
			found = true;
			std::cout << "Task "<<id<<" deleted."<<std::endl;
			break;
		}
	}

	if (!found) {
		std::cout << "Task" << id << "not found." << std::endl;
	}else{
		saveTasks(tasks,"tasks.txt");
	}
	}

	else if (cmd == "run"){
		std::cout << "Enter interactive mode.Type 'exit' to quit." << std::endl;
		std::string input;
		while (true){
			std::cout << ">";
			std::getline(std::cin,input);
			if (input == "exit" || input == "quit") {
				break;
			}
if (input == "showtask") {
	//showtask;
	if (tasks.empty()) {
		std:: cout << "No tasks found." << std::endl;
	}else{
		std::cout << "All tasks:" << std::endl;
		for(size_t i = 0;i < tasks.size(); i++){
			std::cout << "ID: " <<tasks[i].getId()
				<< ",Name: " <<tasks[i].getName() << std::endl;
		}
	}
}

else if (input.rfind("addtask",0) == 0) {
	//addtask
	std::string name = input.substr(8);
	Task task(name, std::time(nullptr));
	tasks.push_back(task);
	saveTasks(tasks,"tasks.txt");
	std::cout<< "Task added! ID: "<< task.getId() << std::endl;
}

else if (input.rfind("deltask",0) == 0) {
	//deltask
	int id = std::stoi(input.substr(8));
	bool found = false;
	for (size_t i = 0;i < tasks.size();i++){
		if (tasks[i].getId() == id){
			tasks.erase(tasks.begin() + i);
			found = true;
			std::cout<< "Task " << id << "deleted." << std::endl;
			break;
		}
		}
	if(!found) {
		std::cout << "Task " << id << " not found." << std::endl;
	}else{
		saveTasks(tasks,"tasks.txt");
	}
}

else {
	std::cout << "Unknown command. Use: addtask,showtask,deltask,exit" << std::endl;
}
		}
	}

	else{
		std::cout<< "Unkown command. Use: addtask, showtask, deltask"<<std::endl;
	}

	return 0;
}
