#include "gate.h"
#include <iostream>

Gate::Gate(int initial_opening) : current_opening(initial_opening), counter() {}

void Gate::open(int percentage) {
    if (percentage < 0 || percentage > 100) {
//        std::cerr << "Error: Open percentage must be between 0 and 100.\n";
        std::cout << "Error: Open percentage must be between 0 and 100.\n";
        return;
    }
    int new_opening = current_opening + percentage;
    current_opening = (new_opening > 100) ? 100 : new_opening;

    counter.increment();

    std::cout << "Gate opened to " << current_opening << "%.\n";
}

void Gate::close(int percentage) {
    if (percentage < 0 || percentage > 100) {
//        std::cerr << "Error: Close percentage must be between 0 and 100.\n";
        std::cout << "Error: Close percentage must be between 0 and 100.\n";
        return;
    }
    int new_opening = current_opening - percentage;
    current_opening = (new_opening < 0) ? 0 : new_opening;

    counter.increment();

    std::cout << "Gate closed to " << current_opening << "%.\n";
}

bool Gate::isClosed() const {
    return current_opening == 0;
}

int Gate::getOpening() const {
    return current_opening;
}

int Gate::getCount() const {
    return counter.getCount(); // Return the count from the operation counter
}
