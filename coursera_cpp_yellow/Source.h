#pragma once

#include <map>

using namespace std;

// TASK_3
enum class Lang {
	DE, FR, IT
};


struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

//TASK_4
// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

