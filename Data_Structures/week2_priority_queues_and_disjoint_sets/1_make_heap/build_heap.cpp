#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int number;
    cin >> number;
    data_.resize(number);
    for (int i = 0; i < number; ++i)
    {
        cin >> data_[i];
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    for (int i = (int) data_.size() / 2; i > 0; --i) {
        int idx = i - 1;
        shiftDown(idx);
    }
  }

  void shiftDown(int idx) {
      int minIndex = idx;
      int left_child = 2 * idx + 1;
      int right_child = 2 * idx + 2;

      if (left_child < data_.size() && data_[left_child] < data_[minIndex]) {
          minIndex = left_child;
      }
      if (right_child < data_.size() && data_[right_child] < data_[minIndex]) {
          minIndex = right_child;
      }
      if (idx != minIndex)
      {
          swap(data_[idx], data_[minIndex]);
          swaps_.push_back(make_pair(idx, minIndex));
          shiftDown(minIndex);
      }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
