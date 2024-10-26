#include "counter.h"

Counter::Counter() : count(0) {}

void Counter::increment() {
    ++count;
}

int Counter::getCount() const {
    return count;
}