#pragma once

#include <iostream>
#include <vector>

class LifeExeption : public std::runtime_error {
public:
    explicit LifeExeption(const std::string &message) : std::runtime_error(message) {
    }
};

class Life {
public:
    explicit Life(size_t widwght, size_t height);

    size_t getWidwght() const;

    size_t getHeight() const;

    std::vector<bool> getCellStates() const;

    bool getCellState(int x, int y) const;

    bool IsValid(size_t x, size_t y) const;

    void setAliveCell(size_t x, size_t y);

    void setDeadCell(size_t x, size_t y);

    friend std::ostream &operator<<(std::ostream &os, Life &life);

    size_t check_live_neighbours(size_t x, size_t y);

    void update_game();

    void fill();

    std::ostream &operator<<(std::ostream &os, Life &life);

private:
    void setStateValue_(size_t x, size_t y, bool state);

    size_t widwght_ = 0;
    size_t height_ = 0;
    std::vector<bool> cell_states_;
};


