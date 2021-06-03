#include <bits/stdc++.h>
#include <ostream>
#include "profile.h"
#include "test_runner.h"

using namespace std;

#ifdef MASLO

prerun maslo(true, false, false);

#endif  // MASLO
/*
Q 10^5
time — −10^18 до 10^18 и не убывает от события к событию
hotel_name — строка
client_id — 10^9
room_count — 1000



IMPLEMENTATION:
class bookmanager
map hotel to stack of bookings
store and refresh room counts
map client to booking count

 * */

using Time = int64_t;
using Client_id = uint32_t;
using Room_count = uint16_t;
const int time_interval = 86400;

struct Booking {
    Time time;
    Client_id client_id;
    Room_count room_count;
#ifdef MASLO

    friend ostream& operator<<(ostream& os, const Booking& booking) {
        os << "time: " << booking.time << " client_id: " << booking.client_id
           << " room_count: " << booking.room_count;
        return os;
    }

#endif  // MASLO
};

class Hotel {
   public:
    void book(Booking booking) {
        room_count_ += booking.room_count;
        client_to_book_count[booking.client_id]++;
        bookings.push_back(booking);
    }
    size_t clients() { return client_to_book_count.size(); }
    size_t rooms() { return room_count_; }
    void popTill(Time time) {
        while (true) {
            if (bookings.empty())
                break;
            auto& booking = bookings.front();
            if (booking.time > time)
                break;
            room_count_ -= booking.room_count;
            auto it = client_to_book_count.find(booking.client_id);
            if (--it->second == 0)
                client_to_book_count.erase(it);
            bookings.pop_front();
        }
    }

#ifdef MASLO

    friend ostream& operator<<(ostream& os, const Hotel& hotel) {
        os << "room_count_: " << hotel.room_count_ << " client_to_book_count: " << hotel.client_to_book_count
           << " bookings: " << hotel.bookings;
        return os;
    }

#endif  // MASLO

   private:
    size_t room_count_ = 0;
    unordered_map<Client_id, size_t> client_to_book_count;
    deque<Booking> bookings;
};

class BookManager {
   public:
    BookManager() {}
    BookManager(BookManager&&) = default;
    BookManager(const BookManager&) = default;
    BookManager& operator=(BookManager&&) = default;
    BookManager& operator=(const BookManager&) = default;
    ~BookManager() {}

    void book(const string& hotel_name, Time time, Client_id client_id, Room_count room_count) {
        last_time = time;
        hotel_to_books[hotel_name].popTill(last_time - time_interval);
        hotel_to_books[hotel_name].book({time, client_id, room_count});
    }
    size_t clients(const string& hotel_name) {
        hotel_to_books[hotel_name].popTill(last_time - time_interval);
        return hotel_to_books[hotel_name].clients();
    }
    size_t rooms(const string& hotel_name) {
        hotel_to_books[hotel_name].popTill(last_time - time_interval);
        return hotel_to_books[hotel_name].rooms();
    }

#ifdef MASLO

    friend ostream& operator<<(ostream& os, const BookManager& manager) {
        os << "hotel_to_books: " << manager.hotel_to_books;
        return os;
    }

#endif  // MASLO

   private:
    Time last_time;
    unordered_map<string, Hotel> hotel_to_books;
};

int main(int argc, const char** argv) {
#ifndef MASLO
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif  // MASLO

    BookManager bm;

    size_t Q;
    cin >> Q;
    cin.ignore(1);
    while (Q-- > 0) {
        string query;
        getline(cin, query);
        stringstream ss(query);
        string op;
        ss >> op;

        if (op == "BOOK") {
            string hotel_name;
            Time time;
            Client_id client_id;
            Room_count room_count;
            ss >> time >> hotel_name >> client_id >> room_count;
            bm.book(hotel_name, time, client_id, room_count);
        } else if (op == "CLIENTS") {
            string hotel_name;
            ss >> hotel_name;
            cout << bm.clients(hotel_name) << std::endl;
        } else if (op == "ROOMS") {
            string hotel_name;
            ss >> hotel_name;
            cout << bm.rooms(hotel_name) << std::endl;
        }

#ifdef MASLO1
        std::cout << "========start" << std::endl;
        cout << bm << endl;
        std::cout << "========end" << std::endl;
#endif  // MASLO
    }
    return 0;
}
