

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<string> vs;
#define Func first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i, a, b) for (int i = a; i <= b; i++)

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

// Prerun maslo for cin&cout to txt; and tests are at beginning of file
// open
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

#include "query.h"
#include "bus_manager.h"
#include "responses.h"


// Не меняя тела функции main, реализуйте функции и классы выше

#ifdef MASLO
#include "utilities.h"
#include "tests.h"

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif


int main() {
    int query_count;
    Query q;
    
    cin >> query_count;
    
    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:cout << bm.GetAllBuses() << endl;
                break;
        }
    }
    
    return 0;
}
