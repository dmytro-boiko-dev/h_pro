#include "../lib/gate.h"
#include <iostream>

int main() {

    Gate gate;

    std::cout << "Initial gate opening: " << gate.getOpening() << "%\n";

    // test
    gate.open(30);
    gate.close(80);

    if (gate.isClosed()) {
        std::cout << "Gate is fully closed.\n";
    } else {
        std::cout << "Gate is currently at " << gate.getOpening() << "% open.\n";
    }

    gate.open(101);
    gate.close(100);
    gate.open(99);

    std::cout << "Gate is currently at " << gate.getOpening() << "% open.\n";

    gate.open(1);

    // Final count of operations
    std::cout << "Total operations: " << gate.getCount() << "\n";

    return 0;
}

