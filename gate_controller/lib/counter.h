#pragma once

class Counter {
public:
    Counter();

    void increment();

    int getCount() const;

private:
    int count;
};