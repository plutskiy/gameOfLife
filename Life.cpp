#include "Life.h"

Life::Life(size_t wighth, size_t height) : widwght_(wighth), height_(height) {
    if (wighth < 3 and height < 3) {
        throw LifeExeption("Wrong size!");
    }

    cell_states_.resize(widwght_ * height_);
}

size_t Life::getWidwght() const {
    return widwght_;
}

size_t Life::getHeight() const {
    return height_;
}

std::vector<bool> Life::getCellStates() const {
    return cell_states_;
}


bool Life::getCellState(int x, int y) const {
    if (x == widwght_) x = 0;
    if (y == height_) y = 0;
    if (x == -1) x += widwght_;
    if (y == -1) y += height_;


    if (!IsValid(x, y)) {
        throw LifeExeption("Invalid index x = " + std::to_string(x) + " or y = " + std::to_string(y));
    }
    return cell_states_[x * widwght_ + y];
}


bool Life::IsValid(size_t x, size_t y) const {
    return x >= 0 and y >= 0 and x < widwght_ and y < height_;

}

void Life::setStateValue_(size_t x, size_t y, bool state) {
    cell_states_[x * widwght_ + y] = state;
}

bool Life::setAliveCell(size_t x, size_t y) {
    if (!IsValid(x, y)) {
        throw LifeExeption("Invalid index x = " + std::to_string(x) + " or y = " + std::to_string(y));
    }
    setStateValue_(x, y, true);
}

bool Life::setDeadCell(size_t x, size_t y) {
    if (!IsValid(x, y)) {
        throw LifeExeption("Invalid index x = " + std::to_string(x) + " or y = " + std::to_string(y));
    }
    setStateValue_(x, y, false);
}


std::ostream &operator<<(std::ostream &os, Life &life) {
    for (size_t x = 0; x < life.getWidwght(); ++x) {
        for (size_t y = 0; y < life.getHeight(); ++y) {
            if (life.getCellState(x, y)) os << "* ";
            if (!life.getCellState(x, y)) os << ". ";
        }
        os << "\n";
    }
    return os;
}

size_t Life::check_live_neighbours(size_t x, size_t y) {
    if (!IsValid(x, y)) {
        throw LifeExeption("Invalid index x = " + std::to_string(x) + " or y = " + std::to_string(y));
    }
    size_t count = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i == 0 and j == 0) continue;
            if (getCellState(x + i, y + j)) {
                ++count;
            }
        }
    }
    return count;
}

void Life::update_game() {
    Life other_life(getWidwght(), getHeight());

    for (size_t x = 0; x < getWidwght(); ++x) {
        for (size_t y = 0; y < getHeight(); ++y) {
            size_t alive_neighbours = check_live_neighbours(x, y);
            if (alive_neighbours == 3) {
                other_life.setAliveCell(x, y);
                continue;
            }

            if (getCellState(x, y)) {
                if (alive_neighbours < 2 or alive_neighbours > 3) {
                    other_life.setDeadCell(x, y);
                } else if (alive_neighbours == 2) {
                    other_life.setAliveCell(x, y);
                }
            }
        }
    }
    std::swap(*this, other_life);
}




