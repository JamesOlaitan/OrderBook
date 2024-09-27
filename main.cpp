// /main.cpp
#include <iostream>
#include "Order.cpp"

int main() {
    // Create an order
    Order order1(1, OrderType::GTC, OrderSide::BUY, 100, 50.0);

    // Display order details
    std::cout << "Order ID: " << order1.getOrderId() << std::endl;
    std::cout << "Order Type: " << (order1.getType() == OrderType::GTC ? "GTC" : "") << std::endl;
    std::cout << "Order Side: " << (order1.getSide() == OrderSide::BUY ? "BUY" : "SELL") << std::endl;
    std::cout << "Quantity: " << order1.getQuantity() << std::endl;
    std::cout << "Price: " << order1.getPrice() << std::endl;
    std::cout << "Order State: " << (order1.getState() == OrderState::NEW ? "NEW" : "") << std::endl;
    std::cout << "Remaining Quantity: " << order1.getRemainingQuantity() << std::endl;

    // Simulate filling part of the order
    order1.reduceQuantity(40);
    std::cout << "\nAfter filling 40 units:" << std::endl;
    std::cout << "Order State: " << (order1.getState() == OrderState::PARTIALLY_FILLED ? "PARTIALLY FILLED" : "") << std::endl;
    std::cout << "Remaining Quantity: " << order1.getRemainingQuantity() << std::endl;

    // Cancel the order
    order1.cancel();
    std::cout << "\nAfter cancellation:" << std::endl;
    std::cout << "Order State: " << (order1.getState() == OrderState::CANCELED ? "CANCELED" : "") << std::endl;
    std::cout << "Is Active: " << (order1.isActive() ? "Yes" : "No") << std::endl;

    return 0;
}