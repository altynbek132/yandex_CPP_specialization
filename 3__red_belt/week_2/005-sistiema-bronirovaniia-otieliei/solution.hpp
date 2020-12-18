#include <cstdint>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

/*
Q — количество запросов
T — максимальное значение модуля времени (то есть −T ⩽ time ⩽ T)
L — максимальная длина строки с названием отеля
С — максимальное значение client_id
R — максимальное количество комнат, бронируемых за один запрос
W — размер временно́го окна (в данном случае равный 86400)
 */

/*
Действительно, сложность решения складывается из трёх частей:

1. Поиск названия отеля по словарю hotels_ на каждый запрос: O(QL logQ).
2. Суммарное время работы всех вызовов метода Book: O(Q logQ).
3. Суммарное время работы всех вызовов метода RemoveOldBookings.
    Поскольку каждое добавленное событие может быть удалено не более 1 раза,
    получаем не более Q вызовов метода PopBooking, то есть O(Q logQ).

Итого, путём поглощения получаем итоговую оценку O(QL logQ).
    Величины T, C, R и W в оценке сложности не участвуют:
    T, R и C определяют лишь необходимую размерность типов,
    а W влияет лишь на количество удалений: чем больше W, тем меньше в конечном счёте будет вызовов PopBooking.
 */

class HotelManager {
 public:
  
  void Book(int64_t time, const string &hotel_name, int client_id, int room_count) {
      current_time_ = time;
      //  sum? O(Q  L logQ) search in map
      hotels_[hotel_name].Book({time, client_id, room_count});
  }
  
  //  O(L * logQ)
  int ComputeClientCount(const string &hotel_name) {
      return hotels_[hotel_name].ComputeClientCount(current_time_);
  }
  
  //  O(L * logQ)
  int ComputeRoomCount(const string &hotel_name) {
      return hotels_[hotel_name].ComputeRoomCount(current_time_);
  }
 
 private:
  struct Booking {
    int64_t time;
    int client_id;
    int room_count;
  };
  
  class HotelInfo {
   public:
    //  O(logQ)
    // sum O(Q logQ)
    void Book(const Booking &booking) {
        last_bookings_.push(booking);
        room_count_ += booking.room_count;
        ++client_booking_counts_[booking.client_id];
    }
  
    //  amortized O(logQ)
    int ComputeClientCount(int64_t current_time) {
        RemoveOldBookings(current_time);
        return client_booking_counts_.size();
    }
  
    //  amortized O(logQ)
    int ComputeRoomCount(int64_t current_time) {
        RemoveOldBookings(current_time);
        return room_count_;
    }
   
   private:
    static const int TIME_WINDOW_SIZE = 86400;
    queue<Booking> last_bookings_;
    int room_count_ = 0;
    map<int, int> client_booking_counts_;
    
    //  O(logQ)
    void PopBooking() {
        const Booking &booking = last_bookings_.front();
        room_count_ -= booking.room_count;
        //  O(logQ)
        const auto client_stat_it = client_booking_counts_.find(booking.client_id);
        if (--client_stat_it->second == 0) {
            client_booking_counts_.erase(client_stat_it);
        }
        last_bookings_.pop();
    }
    
    // amortized O(logQ)
    // sum O(Q logQ)
    void RemoveOldBookings(int64_t current_time) {
        while (!last_bookings_.empty() && last_bookings_.front().time <= current_time - TIME_WINDOW_SIZE) {
            PopBooking();
        }
    }
  };
  
  int64_t current_time_ = 0;
  map<string, HotelInfo> hotels_;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    HotelManager manager;
    
    int query_count;
    cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        
        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            int client_id, room_count;
            cin >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else {
            string hotel_name;
            cin >> hotel_name;
            if (query_type == "CLIENTS") {
                cout << manager.ComputeClientCount(hotel_name) << "\n";
            } else if (query_type == "ROOMS") {
                cout << manager.ComputeRoomCount(hotel_name) << "\n";
            }
        }
    }
    
    return 0;
}
