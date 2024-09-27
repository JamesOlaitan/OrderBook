#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <deque>
#include <format>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>


enum class OrderType {
    GTC,  // Good Till Cancel
    GFD,  // Good For Day
    FOK   // Fill Or Kill
};

enum class OrderSide {
    BUY,
    SELL
};

enum class OrderState {
    NEW,
    PARTIALLY_FILLED,
    FILLED,
    CANCELED
};

class Order {
public:
    // Constructors
    Order(int orderId, OrderType type, OrderSide side, int quantity, double price);

    // Accessors
    void setOrderId(int id);
    int getOrderId() const;
    OrderType getType() const;
    OrderSide getSide() const;
    int getQuantity() const;
    double getPrice() const;
    std::chrono::time_point<std::chrono::system_clock> getTimestamp() const;
    OrderState getState() const;
    int getRemainingQuantity() const;

    // Modifiers
    void setState(OrderState newState);
    void reduceQuantity(int amount);

    // Methods
    void cancel();
    bool isActive() const;

private:
    int orderId;
    OrderType type;
    OrderSide side;
    int quantity;
    double price;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    OrderState state;
    int remainingQuantity;
};

Order::Order(int orderId, OrderType type, OrderSide side, int quantity, double price)
    : orderId(orderId), type(type), side(side), quantity(quantity), price(price), state(OrderState::NEW), remainingQuantity(quantity) {
    timestamp = std::chrono::system_clock::now();
}

// Accessors
void Order::setOrderId(int id) {
    orderId = id;
}

int Order::getOrderId() const {
    return orderId;
}

OrderType Order::getType() const {
    return type;
}

OrderSide Order::getSide() const {
    return side;
}

int Order::getQuantity() const {
    return quantity;
}

double Order::getPrice() const {
    return price;
}

std::chrono::time_point<std::chrono::system_clock> Order::getTimestamp() const {
    return timestamp;
}

OrderState Order::getState() const {
    return state;
}

int Order::getRemainingQuantity() const {
    return remainingQuantity;
}

// Modifiers
void Order::setState(OrderState newState) {
    state = newState;
}

void Order::reduceQuantity(int amount) {
    if (amount <= remainingQuantity) {
        remainingQuantity -= amount;
        if (remainingQuantity == 0) {
            state = OrderState::FILLED;
        } else {
            state = OrderState::PARTIALLY_FILLED;
        }
    }
}

// Methods
void Order::cancel() {
    state = OrderState::CANCELED;
    remainingQuantity = 0;
}

bool Order::isActive() const {
    return state == OrderState::NEW || state == OrderState::PARTIALLY_FILLED;
}