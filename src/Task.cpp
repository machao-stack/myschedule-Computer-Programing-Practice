#include "Task.hpp"

int Task::nectId = 1;

Task::Task(const std::string& name,std::time_t startTime,Priority priority,Category category):
	id(nextId++),name(name),startTime(startTime),priority(priority),category(category),remindTime(startTime){
}

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
