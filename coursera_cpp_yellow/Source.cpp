using namespace std;
#include <iostream>
#include <vector>
#include <numeric>

#define WEEK_1
#define TASK_2

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

	for (size_t i = 0; i < arr.size(); ++ i) {
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

#endif
#endif