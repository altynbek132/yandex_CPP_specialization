// #include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <iomanip>
#include <fstream>

#include <numeric>
//#include <limits>

#include <type_traits>


using namespace std;

const char *maslo = std::getenv("maslo");

template<typename Collection>
string Join(const Collection &col, char sep) {
    stringstream ss;
    bool first = true;
    for (const auto &i : col) {
        if (!first) {
            ss << sep;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}

template<typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p) {
    return out << '(' << p.first << ',' << p.second << ')';
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    return out << '[' << Join(v, ',') << ']';
}

template<typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m) {
    return out << '{' << Join(m, ',') << '}';
}

// tuple printing
template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream &, const std::tuple<T...> &) {}

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream &os, const std::tuple<T...> &tup) {
    if (n != 0) {
        os << ", ";
    }
    os << std::get<n>(tup);
    print_tuple<n + 1>(os, tup);
}

template<typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
    os << "[";
    print_tuple<0>(os, tup);
    return os << "]";
}

void txt() {
    if (!maslo) {
        return;
    }
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

void ensure(istream &input, char expected) {
    const char actual = input.peek();
    if (actual != expected) {
        input.setstate(ios::failbit);
        throw exception();
    }
    input.ignore(1);
}

void ensure(istream &input) {
    if (!input) {
        throw exception();
    }
}

void ensure(bool state) {
    if (!state) {
        throw exception();
    }
}

stringstream stream_line(istream &input) {
    string line;
    while (line.empty() && !input.eof()) {
        getline(input, line);
    }
    stringstream input_stream(line);
    return input_stream;
}

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

void io_files(ifstream &in, const string &input, ofstream &out, const string &output) {
    in = ifstream(input);
    out = ofstream(output);
}

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

// ==================================

// Перечислимый тип для статуса задачи
#ifdef MASLO
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};
#endif

ostream &operator<<(ostream &out, const TaskStatus &status) {
    switch (status) {
        case TaskStatus::NEW : {
            out << "\"NEW\"";
            break;
        }
        case TaskStatus::IN_PROGRESS : {
            out << "\"IN_PROGRESS\"";
            break;
        }
        case TaskStatus::TESTING : {
            out << "\"TESTING\"";
            break;
        }
        case TaskStatus::DONE : {
            out << "\"DONE\"";
            break;
        }
        default: {
            break;
        }
    }
    return out;
}

TaskStatus operator+(const TaskStatus &status, const int step) {
    auto new_status = static_cast<TaskStatus>(static_cast<int>(status) + step);
    return new_status;
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса

#ifdef MASLO
using TasksInfo = map<TaskStatus, int>;
#endif

//ostream &operator<<(ostream &out, const tuple<TasksInfo, TasksInfo> &t) {
//    const auto&[a, b]  = t;
//    std::cout << a << b << std::endl;
//}

class TeamTasks {
 public:
  // Получить статистику по статусам задач конкретного разработчика
  [[nodiscard]] const TasksInfo &GetPersonTasksInfo(const string &person) const {
      return person_to_task.at(person);
  }
  
  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string &person) {
      person_to_task[person][TaskStatus::NEW]++;
  }
  
  void AddNewTask(const string &person, int count) {
      person_to_task[person][TaskStatus::NEW] += count;
  }
  
  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count) {
      auto &tasks = person_to_task[person];
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
  
  static void RemoveZeros(TasksInfo &tasks) {
      vector<TaskStatus> zero_count_statuses;
      for (const auto &[status, count] : tasks) {
          if (count == 0) {
              zero_count_statuses.push_back(status);
          }
      }
      for (const auto &status : zero_count_statuses) {
          tasks.erase(status);
      }
  }
};

// ==================================
// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int run() {
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
    
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    
    return 0;
}

int main() {
    txt();
    ifstream in;
    ofstream out;
    io_files(in, "input.txt", out, "output.txt");
    // ================================================================

//    run();
//    std::cout << std::endl;
    
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
