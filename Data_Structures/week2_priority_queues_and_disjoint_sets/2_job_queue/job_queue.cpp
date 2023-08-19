#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  vector<int> _workers;
  vector<long long> _end_time;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
    _workers = vector<int>(num_workers_);
    _end_time = vector<long long>(num_workers_);
    for (size_t i = 0; i < num_workers_; i++)
    {
        _end_time[0] = 0;
        _workers[i] = i;
    }
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      assigned_workers_[i] = _workers[0];
      start_times_[i] = _end_time[0];
      _end_time[0] += duration;
      shiftDown(0);
    }
  }

  void shiftDown(int idx) {
      int minIndex = idx;
      int left_child = 2 * idx + 1;
      int right_child = 2 * idx + 2;

      if (left_child < num_workers_ && (_end_time[left_child] < _end_time[minIndex] || (_end_time[left_child] == _end_time[minIndex] && _workers[left_child] < _workers[minIndex]))) {
          minIndex = left_child;
      }
      if (right_child < num_workers_ && (_end_time[right_child] < _end_time[minIndex] || (_end_time[right_child] == _end_time[minIndex] && _workers[right_child] < _workers[minIndex]))) {
          minIndex = right_child;
      }
      if (idx != minIndex)
      {
          std::swap(_end_time[idx], _end_time[minIndex]);
          std::swap(_workers[idx], _workers[minIndex]);
          shiftDown(minIndex);
      }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
