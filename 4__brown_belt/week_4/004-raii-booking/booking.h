#ifndef YANDEXCPLUSPLUS_4_BROWN_4_WEEK_4_TASK_BOOKING_H_
#define YANDEXCPLUSPLUS_4_BROWN_4_WEEK_4_TASK_BOOKING_H_

#include <bits/stdc++.h>

using namespace std;

namespace RAII {

template <typename Provider>
class Booking {
   public:
    using BookingId = typename Provider::BookingId;

   public:
    Booking(Provider* provider, const BookingId& booking_id)
        : provider_ptr_(provider), booking_id_(booking_id) {}

    ~Booking() {
        if (!provider_ptr_) {
            return;
        }
        provider_ptr_->CancelOrComplete(*this);
    }

    Booking(const Booking&) = delete;
    Booking& operator=(const Booking&) = delete;

    Booking(Booking&& other) { MoveFrom(move(other)); };
    Booking& operator=(Booking&& other) {
        MoveFrom(move(other));
        return *this;
    };

    const BookingId& GetId() const { return booking_id_; }

   private:
    Provider* provider_ptr_;
    BookingId booking_id_;

    void MoveFrom(Booking&& other) {
        swap(provider_ptr_, other.provider_ptr_);
        swap(booking_id_, other.booking_id_);
        other.provider_ptr_ = nullptr;
    }
};

}  // namespace RAII

#endif  // YANDEXCPLUSPLUS_4_BROWN_4_WEEK_4_TASK_BOOKING_H_
