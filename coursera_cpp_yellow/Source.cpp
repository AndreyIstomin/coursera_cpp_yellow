using namespace std;

#define WEEK_2
#define TASK_2

//#define TESTING_

#ifdef TESTING_
#include "Source.h"

#endif
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <numeric>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <string>


#ifdef WEEK_1
#ifdef TASK_1

int main() {
	int n{ 0 };
	int64_t av{ 0 };

	cin >> n;
	vector<int64_t> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
		//if (arr[i] >= 0) {
		//	pos_sum += arr[i];
		//}
		//else {
		//	neg_sum -= arr[i];
		//}
		av += arr[i];
	}
	av /= int(arr.size());

	std::vector<int> res;

	for (size_t i = 0; i < arr.size(); ++i) {
		if (arr[i] > av) {
			res.push_back(i);
		}
	}

	cout << res.size() << endl;
	for (int item : res) {
		cout << item << " ";
	}

}

#elif defined TASK_2

int main() {
	uint64_t sum{ 0 };
	int num{ 0 }, R{ 0 }, w{ 0 }, h{ 0 }, d{ 0 };

	cin >> num >> R;
	for (int i = 0; i < num; ++i) {
		cin >> w >> h >> d;
		sum += static_cast<uint64_t>(w) * static_cast<uint64_t>(h) * d;

	}
	cout << sum * R;
}

#elif defined TASK_3

auto to_tuple(const Region & item) {
	return tie(item.std_name, item.parent_std_name, item.names, item.population);
}

bool operator <(const Region & lhs, const Region & rhs)
{
	return to_tuple(lhs) < to_tuple(rhs);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {

	map<Region, int> counter;
	int result = 0;
	for (const auto & item : regions) {
		result = max(result, ++counter[item]);
	}

	return result;
}

#ifdef TESTING_
int main() {
	cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		},
		}) << endl;

	cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Toulouse",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			31
		},
		}) << endl;

	return 0;
}
#endif

#elif defined TASK_4

class TeamTasks {
public:
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return m_data.at(person);
	}

	void AddNewTask(const string& person) {
		m_data[person][TaskStatus::NEW] += 1;
	}

	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {

		if (m_data.count(person) == 0) {
			return make_tuple(TasksInfo(), TasksInfo());
		}

		TasksInfo changed, unchanged;
		TasksInfo & personData{ m_data[person] };
		int need_to_update{ task_count };

		for (auto & item : personData) {

			if (item.first < TaskStatus::DONE && need_to_update > 0) {
				int diff = min(item.second, need_to_update);
				item.second -= diff;
				changed[m_updateMap[int(item.first)]] = diff;
				need_to_update -= diff;
			}

			if (item.second > 0 && item.first != TaskStatus::DONE) {
				unchanged[item.first] = item.second;
			}

			//if (need_to_update <= 0) {
			//	break;
			//}
		}

		for (const auto & item : changed) {
			personData[item.first] += item.second;
		}

		for (auto it = personData.begin(); it != personData.end();) {
			if (it->second == 0) {
				it = personData.erase(it);
			}
			else {
				++it;
			}
		}

		return tie(changed, unchanged);
	}

private:

	std::map<string, TasksInfo> m_data;
	const std::array<TaskStatus, 4> m_updateMap = { TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE, TaskStatus::DONE };

};

#ifdef TESTING_
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

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
#endif

#elif defined TASK_5

template <typename T> T Sqr(const T &);
template <typename T> vector<T> Sqr(const vector<T> & v);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value> & m);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second> p);

template <typename T>
T Sqr(const T & value) {
	return value * value;
}

template <typename T>
vector<T> Sqr(const vector<T> & v) {
	vector<T> res;
	res.reserve(v.size());
	for (const auto & item : v) {
		res.push_back(Sqr(item));
	}
	return res;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value> & m) {
	map<Key, Value> res;
	for (const auto & item : m) {
		res[item.first] = Sqr(item.second);
	}
	return res;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second> p) {
	return make_pair(Sqr(p.first), Sqr(p.second));
}

#ifdef TESTING_

int main() {
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}

#endif

#elif defined TASK_6


template< typename Key ,typename Value>
Value & GetRefStrict(map<Key, Value> & m, Key k) {

	auto it = m.find(k);

	if (it != m.end()) {
		return it->second;
	}
	else {
		throw runtime_error("unknown key");
	}
}

#ifdef TESTING_
int main() {

	map<int, string>	m = { {0, "value"} };
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl;
	return 0;
}
#endif 

#endif
#elif defined WEEK_2
#ifdef TASK_1

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string operationCode;
	is >> operationCode;
	if (operationCode == "NEW_BUS") {

		q.type = QueryType::NewBus;
		is >> q.bus;
		int stopCount{ 0 };
		is >> stopCount;
		q.stops.resize(stopCount);
		for (string& stop : q.stops) {
			is >> stop;
		}
	}
	else if (operationCode == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (operationCode == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (operationCode == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	else {
		throw(runtime_error("Unknown operation code: " + operationCode));
	}
	return is;
}

struct BusesForStopResponse {
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.buses.empty()) {
		os << "No stop" << endl;
	}
	else {
		for (const string& bus : r.buses) {
			os << bus << " ";
		}
		os << endl;
	}

	return os;
}

struct StopsForBusResponse {
	string bus;
	vector<pair<string, vector<string>>> stop_interchange;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.stop_interchange.empty()) {
		os << "No bus" << endl;
	}
	else {
		for (auto & pair : r.stop_interchange) {
			os << "Stop " << pair.first << ": ";
			if (pair.second.size() == 1) {
				os << "no interchange" << endl;
			}
			else {
				for (const string& other_bus : pair.second) {
					if (other_bus != r.bus) {
						os << other_bus << " ";
					}
				}
				os << endl;
			}
		}
	}
	return os;
}

struct AllBusesResponse {
	std::map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stops.empty()) {
		os << "No buses" << endl;
	}
	else {
		for (const auto& pair : r.buses_to_stops) {
			os << "Bus " << pair.first << ": ";
			for (const string& stop : pair.second) {
				os << stop << " ";
			}
			os << endl;
		}
	}
	return os;
}

class BusManager {

	map<string, vector<string>> buses_to_stops;
	map<string, vector<string>> stops_to_buses;

public:
	void AddBus(const string& bus, const vector<string>& stops) {
		buses_to_stops[bus] = std::move(stops);
		for (const string & stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}

	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		if (stops_to_buses.count(stop)) {
			return { stops_to_buses.at(stop) };
		}
		return {};
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse r;
		r.bus = bus;
		if (buses_to_stops.count(bus)) {
			for (const string & stop : buses_to_stops.at(bus)) {
				r.stop_interchange.emplace_back(stop, stops_to_buses.at(stop));
			}
		}
		return r;
	}

	AllBusesResponse GetAllBuses() const {
		return { buses_to_stops };
	}
};

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}
#elif defined TASK_2
// HERE ....
#endif 
#endif