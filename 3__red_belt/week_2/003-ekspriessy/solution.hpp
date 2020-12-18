#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

//Q — количество запросов
//M — максимальное значение модуля координаты

class RouteManager {
 public:
  // logQ
  void AddRoute(int start, int finish) {
      reachable_lists_[start].push_back(finish);
      reachable_lists_[finish].push_back(start);
  }
  
  // logQ + Q
  int FindNearestFinish(int start, int finish) const {
      int result = abs(start - finish);
//      logQ
      if (reachable_lists_.count(start) < 1) {
          return result;
      }
      const vector<int> &reachable_stations =
          reachable_lists_.at(start);
      if (!reachable_stations.empty()) {
          result = min(
              result,
//              Q
              abs(finish - *min_element(
                  begin(reachable_stations), end(reachable_stations),
                  [finish](int lhs, int rhs) {
                    return abs(lhs - finish) < abs(rhs - finish);
                  }
              ))
          );
      }
      return result;
  }
 
 private:
  map<int, vector<int>> reachable_lists_;
};


int main() {
    RouteManager routes;
    
    int query_count;
    cin >> query_count;
    
//   (logQ + Q) * Q
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
    
    return 0;
}

// ================================================================================
// ================================================================================
// ================================================================================
// ================================================================================
// ================================================================================
// ================================================================================





#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <set>

using namespace std;

class RouteManager {
 public:
//  logQ
  void AddRoute(int start, int finish) {
      reachable_lists_[start].insert(finish);
      reachable_lists_[finish].insert(start);
  }
//  logQ
  int FindNearestFinish(int start, int finish) const {
      int result = abs(start - finish);
      if (reachable_lists_.count(start) < 1) {
          return result;
      }
      const set<int>& reachable_stations = reachable_lists_.at(start);
      const auto finish_pos = reachable_stations.lower_bound(finish);
      if (finish_pos != end(reachable_stations)) {
          result = min(result, abs(finish - *finish_pos));
      }
      if (finish_pos != begin(reachable_stations)) {
          result = min(result, abs(finish - *prev(finish_pos)));
      }
      return result;
  }
 private:
  map<int, set<int>> reachable_lists_;
};


int main() {
    RouteManager routes;
    
    int query_count;
    cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
    
    return 0;
}
