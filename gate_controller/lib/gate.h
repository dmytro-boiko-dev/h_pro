#pragma once

#include "counter.h"

class Gate {
public:
    Gate(int initial_opening = 50);

    void open(int percentage);

    void close(int percentage);

    bool isClosed() const;

    int getOpening() const;

    int getCount() const;

private:
    int current_opening;

    Counter counter;
};
