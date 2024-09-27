// /OrderBook
#include "Order.cpp"

class OrderBook {
public:
    // Constructors
    OrderBook();

    // Order Management
    int addOrder(const Order& order);
    bool cancelOrder(int orderId);

    // Market Data Retrieval
    double getBestBidPrice() const;
    double getBestAskPrice() const;
    std::vector<std::pair<double, int>> getBidLevels(int depth = 5) const;
    std::vector<std::pair<double, int>> getAskLevels(int depth = 5) const;

    // Matching Engine
    void matchOrders();

private:
    // Buy orders: Key = Price, Value = Orders at that price
    std::map<double, std::deque<Order>> buyOrders;

    // Sell orders: Key = Price, Value = Orders at that price
    std::map<double, std::deque<Order>> sellOrders;

    int nextOrderId;

    // Helper Functions
    void addOrderToBook(const Order& order);
};


// Constructors
OrderBook::OrderBook() : nextOrderId(1) {}

// Order Management
int OrderBook::addOrder(const Order& order) {
    Order newOrder = order;
    newOrder.setOrderId(nextOrderId++);
    addOrderToBook(newOrder);
    // Matching logic can be called here
    // matchOrders();
    return newOrder.getOrderId();
}

bool OrderBook::cancelOrder(int orderId) {
    // Implement cancellation logic
    // Search both buy and sell orders for the orderId
    // Remove if found and return true
    // Return false if not found
    return false;
}

// Market Data Retrieval
double OrderBook::getBestBidPrice() const {
    if (buyOrders.empty()) {
        return 0.0; // No bids available
    }
    // Reverse iterator to get the highest price
    auto it = buyOrders.rbegin();
    return it->first;
}

double OrderBook::getBestAskPrice() const {
    if (sellOrders.empty()) {
        return 0.0; // No asks available
    }
    // Iterator to get the lowest price
    auto it = sellOrders.begin();
    return it->first;
}

std::vector<std::pair<double, int>> OrderBook::getBidLevels(int depth) const {
    std::vector<std::pair<double, int>> levels;
    for (auto it = buyOrders.rbegin(); it != buyOrders.rend() && depth > 0; ++it, --depth) {
        double price = it->first;
        int quantity = 0;
        for (const auto& order : it->second) {
            quantity += order.getRemainingQuantity();
        }
        levels.emplace_back(price, quantity);
    }
    return levels;
}

std::vector<std::pair<double, int>> OrderBook::getAskLevels(int depth) const {
    std::vector<std::pair<double, int>> levels;
    for (auto it = sellOrders.begin(); it != sellOrders.end() && depth > 0; ++it, --depth) {
        double price = it->first;
        int quantity = 0;
        for (const auto& order : it->second) {
            quantity += order.getRemainingQuantity();
        }
        levels.emplace_back(price, quantity);
    }
    return levels;
}

// Matching Engine
void OrderBook::matchOrders() {
    // Implement matching logic here
}

// Private Helper Functions
void OrderBook::addOrderToBook(const Order& order) {
    if (order.getSide() == OrderSide::BUY) {
        buyOrders[order.getPrice()].push_back(order);
    } else {
        sellOrders[order.getPrice()].push_back(order);
    }
}