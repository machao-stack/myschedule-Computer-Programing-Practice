#ifndef TASK_HPP
#define TASK_HPP


#include<string>
#include<ctime>

enum class Priority{
        HIGH,
        MEDIUM,
        LOW,
};

enum class Category{
        STUDY,
        ENTERTAINMENT,
        LIFE
};

class Task {
        private:
                int id;
                std::string name;
                std::time_t startTime;
                Priority priority;
                Category category;
                std::time_t remindTime;

        public:
                Task(const std::string& name,std::time_t startTime,
                                Priority priority = Priority::MEDIUM,
                                Category category = Category::LIFE);
                int getId() const;
                std::string getName() const;
                std::time_t getStartTime() const;
                Priority getPriority() const;
                Category getCategory() const;
                std::time_t getRemindTime() const;
};

#endif

