#include "Task.hpp"

int Task::nextId = 1;

Task::Task(const std::string& name,std::time_t startTime,Priority priority,Category category):
	id(nextId++),name(name),startTime(startTime),priority(priority),category(category),remindTime(startTime),reminded(false){}

int Task::getId() const{
	return id;
}

std::string Task::getName() const{
	return name;
}

std::time_t Task::getStartTime() const {
	return startTime;
}

Priority Task::getPriority() const {
	return priority;
}

Category Task::getCategory() const {
	return category;
}

std::time_t Task::getRemindTime() const {
	return remindTime;
}

std::string Task::toFileString() const {
	return std::to_string(id) + ","+ name + "," +std::to_string(startTime) + "," +
		std::to_string(static_cast<int>(priority)) + "," + 
		std::to_string(static_cast<int>(category)) + "," +
		std::to_string(remindTime);
}

Task Task::fromFileString(const std::string& line){
	Task task;
	size_t pos = 0;
	size_t next = 0;

	next = line.find(',',pos);
	task.id = std::stoi(line.substr(pos,next - pos));

	pos = next + 1;
	next = line.find(',',pos);
	task.name = line.substr(pos,next - pos);

	pos = next + 1;
	next = line.find(',', pos);
	task.startTime = std::stol(line.substr(pos,next - pos));

	pos = next + 1;
	next = line.find(',', pos);
	task.priority = static_cast<Priority>(std::stoi(line.substr(pos,next - pos)));

	pos = next + 1;
	next = line.find(',',pos);
	task.category = static_cast<Category>(std::stoi(line.substr(pos,next - pos)));

	pos = next + 1;
	next = line.find(',', pos);
	task.remindTime = std::stol(line.substr(pos,next - pos));

	if (task.id >= Task::nextId) {
			Task::nextId = task.id + 1;
			}

			return task;
			}

bool Task::isReminded() const {
	return reminded;
}

void Task::setReminded(bool r){
	reminded = r;
}
