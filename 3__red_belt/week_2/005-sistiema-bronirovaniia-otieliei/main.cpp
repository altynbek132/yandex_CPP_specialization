#include <bits/stdc++.h>

using namespace std;

// 2^7 = 128
// 2^15 = 3e4
// 2^31 = 2e9
// 2^63 = 9e18

#ifdef MASLO

#include "tests.h"

void txt() {
    freopen("input.txt", "r", stdin);
    return;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("output.txt", "w", stdout);
}

struct Prerun {
  Prerun() {
      txt();
      TestAll();
  }
};

Prerun maslo;
#endif
// ==========================================
#include <iostream>
#include <cstdint>
#include <map>
#include <queue>

//----------------------------------------------------------------------------------------------------
struct Booking {
  int64_t time;
  int client_id;
  int room_count;
};

//----------------------------------------------------------------------------------------------------
class Hotel {
 public:
  void Book(const Booking &booking);
  
  int GetClients(const int64_t &current_time);
  
  int GetRooms(const int64_t &current_time);
 
 private:
  static const int SECONDS_IN_DAYS = 86400;
  
  std::queue<Booking> booking_history;
  int room_count = 0;
  std::map<int, int> client_booking_counts;
  
  void pop_booking();
  
  void remove_old_books(const int64_t &current_time);
};

void Hotel::Book(const Booking &booking) {
    booking_history.push(booking);
    room_count += booking.room_count;
    ++client_booking_counts[booking.client_id];
}

int Hotel::GetClients(const int64_t &current_time) {
    remove_old_books(current_time);
    return client_booking_counts.size();
}

int Hotel::GetRooms(const int64_t &current_time) {
    remove_old_books(current_time);
    return room_count;
}

void Hotel::pop_booking() {
    const Booking &booking = booking_history.front();
    room_count -= booking.room_count;
    const auto client_stat_it = client_booking_counts.find(booking.client_id);
    
    if (--client_stat_it->second == 0) {
        client_booking_counts.erase(client_stat_it);
    }
    booking_history.pop();
}

void Hotel::remove_old_books(const int64_t &current_time) {
    while (!booking_history.empty() && booking_history.front().time <= current_time - SECONDS_IN_DAYS) {
        pop_booking();
    }
}

//----------------------------------------------------------------------------------------------------
class BookingManager {
 public:
  void Book(const int64_t &time, const std::string &hotel_name, int client_id, short int room_count);
  
  int GetClients(const std::string &hotel_name);
  
  int GetRooms(const std::string &hotel_name);
 
 private:
  int64_t current_time = 0;
  std::map<std::string, Hotel> hotels;
};

void BookingManager::Book(const int64_t &time, const string &hotel_name, int client_id, short room_count) {
    current_time = time;
    hotels[hotel_name].Book({time, client_id, room_count});
}

int BookingManager::GetClients(const string &hotel_name) {
    return hotels[hotel_name].GetClients(current_time);
}

int BookingManager::GetRooms(const string &hotel_name) {
    return hotels[hotel_name].GetRooms(current_time);
}

//----------------------------------------------------------------------------------------------------
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    BookingManager manager;
    
    int query_count;
    std::cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        std::string query_type;
        std::cin >> query_type;
        
        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            uint64_t client_id;
            uint16_t room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            
            manager.Book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            std::string hotel_name;
            std::cin >> hotel_name;
            
            std::cout << manager.GetClients(hotel_name) << "\n";
        } else if (query_type == "ROOMS") {
            std::string hotel_name;
            std::cin >> hotel_name;
            
            std::cout << manager.GetRooms(hotel_name) << "\n";
        }
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------
