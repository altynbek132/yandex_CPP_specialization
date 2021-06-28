#include <bits/stdc++.h>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO

// Перечислимый тип для статуса задачи
#ifdef MASLO
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};
#endif

ostream& operator<<(ostream& out, const TaskStatus& status) {
    switch (status) {
        case TaskStatus::NEW: {
            out << "\"NEW\"";
            break;
        }
        case TaskStatus::IN_PROGRESS: {
            out << "\"IN_PROGRESS\"";
            break;
        }
        case TaskStatus::TESTING: {
            out << "\"TESTING\"";
            break;
        }
        case TaskStatus::DONE: {
            out << "\"DONE\"";
            break;
        }
        default: {
            throw runtime_error("chotam?");
        }
    }
    return out;
}

TaskStatus operator+(const TaskStatus& status, const int step) {
    auto new_status = static_cast<TaskStatus>(static_cast<int>(status) + step);
    return new_status;
}

#ifdef MASLO
// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

#endif  // MASLO

ostream& operator<<(ostream& out, const tuple<TasksInfo, TasksInfo>& t) {
    const auto& [a, b] = t;
    std::cout << a << b << std::endl;
}

class TeamTasks {
   public:
    // Получить статистику по статусам задач конкретного разработчика
    [[nodiscard]] const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return person_to_task.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) { person_to_task[person][TaskStatus::NEW]++; }

    void AddNewTask(const string& person, int count) { person_to_task[person][TaskStatus::NEW] += count; }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        auto& tasks = person_to_task[person];
        TasksInfo updated_tasks, untouched_tasks;
        for (auto status = TaskStatus::NEW; status != TaskStatus::DONE; status = status + 1) {
            const int update_count = min(task_count, tasks[status]);
            updated_tasks[status + 1] = update_count;
            task_count -= update_count;
        }
        for (auto status = TaskStatus::NEW; status != TaskStatus::DONE; status = status + 1) {
            untouched_tasks[status] = tasks[status] - updated_tasks[status + 1];
            tasks[status] += updated_tasks[status] - updated_tasks[status + 1];
        }
        tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

        RemoveZeros(updated_tasks);
        RemoveZeros(untouched_tasks);
        RemoveZeros(tasks);
        return {updated_tasks, untouched_tasks};
    }

   private:
    map<string, TasksInfo> person_to_task;

    static void RemoveZeros(TasksInfo& tasks) {
        vector<TaskStatus> zero_count_statuses;
        for (const auto& [status, count] : tasks) {
            if (count == 0) {
                zero_count_statuses.push_back(status);
            }
        }
        for (const auto& status : zero_count_statuses) {
            tasks.erase(status);
        }
    }
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"
         << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
         << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
         << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

#ifdef MASLO
int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
#endif  // MASLO

#ifndef MASLO
int main() {
    TeamTasks TT;
    string line;
    while (getline(cin, line)) {
        stringstream input_command(line);
        string operation_command;
        input_command >> operation_command;

        string name;
        input_command >> name;
        if (operation_command == "AddNewTasks") {
            int count;
            input_command >> count;
            TT.AddNewTask(name, count);
        } else if (operation_command == "PerformPersonTasks") {
            int count;
            input_command >> count;
            cout << TT.PerformPersonTasks(name, count) << endl;
        } else if (operation_command == "GetPersonTasksInfo") {
            cout << TT.GetPersonTasksInfo(name) << endl;
        }
    }

    return 0;
}
#endif  // MASLO
