#include <iostream>
#include "gtest/gtest.h"
#include "Life.h"


TEST(TestsOfLife, Default) {
    Life a(3, 3);
    ASSERT_NO_THROW(Life(4, 5));
    ASSERT_EQ(a.getCellStates().size(), 9);
    ASSERT_THROW(Life(2, 2), LifeExeption);
}

TEST(SETTERS, Alive) {
    Life a(10, 10);
    Life b(3, 6);
    Life c(1000, 5);
    a.setAliveCell(0, 0);
    b.setAliveCell(2, 2);
    c.setAliveCell(999, 4);
    ASSERT_EQ(a.getCallState(0, 0), true);
    ASSERT_EQ(a.getCallState(0, 2), false);

    ASSERT_EQ(b.getCallState(0, 2), false);
    ASSERT_EQ(b.getCallState(2, 2), true);

    ASSERT_EQ(c.getCallState(999, 4), true);
    ASSERT_EQ(c.getCallState(0, 4), false);
}

TEST(SETTERS, Dead) {
    Life a(10, 10);
    Life b(3, 6);
    Life c(1000, 5);
    a.setAliveCell(0, 0);
    b.setAliveCell(2, 2);
    c.setAliveCell(999, 4);

    a.setDeadCell(0, 0);
    b.setDeadCell(2, 2);
    c.setDeadCell(999, 4);
    ASSERT_EQ(a.getCallState(0, 0), false);
    ASSERT_EQ(a.getCallState(0, 2), false);
    ASSERT_EQ(b.getCallState(0, 2), false);
    ASSERT_EQ(b.getCallState(2, 2), false);
    ASSERT_EQ(c.getCallState(999, 4), false);
    ASSERT_EQ(c.getCallState(0, 4), false);
}

TEST(SETTERS, AliveWithExeptions) {
    Life a(10, 10);
    Life b(3, 6);
    Life c(1000, 5);
    a.setAliveCell(1, 0);
    b.setAliveCell(2, 2);
    c.setAliveCell(999, 4);


    ASSERT_THROW(a.setAliveCell(-2, 20), LifeExeption);
    ASSERT_THROW(b.setAliveCell(-2, 20), LifeExeption);
    ASSERT_THROW(c.setAliveCell(-2, 20), LifeExeption);

    ASSERT_THROW(a.setAliveCell(20, -20), LifeExeption);
    ASSERT_THROW(b.setAliveCell(20, -20), LifeExeption);
    ASSERT_THROW(c.setAliveCell(20, -20), LifeExeption);

    ASSERT_THROW(a.setAliveCell(100000, 100000), LifeExeption);
    ASSERT_THROW(b.setAliveCell(10000000, 1000000), LifeExeption);
    ASSERT_THROW(c.setAliveCell(10000, 100000), LifeExeption);
}

TEST(SETTERS, DeadWithExeptions) {
    Life a(10, 10);
    Life b(3, 6);
    Life c(1000, 5);
    a.setAliveCell(0, 0);
    b.setAliveCell(2, 2);
    c.setAliveCell(999, 4);

    a.setDeadCell(0, 0);
    b.setDeadCell(2, 2);
    c.setDeadCell(999, 4);

    ASSERT_THROW(a.setDeadCell(-2, 20), LifeExeption);
    ASSERT_THROW(b.setDeadCell(-2, 20), LifeExeption);
    ASSERT_THROW(c.setDeadCell(-2, 20), LifeExeption);

    ASSERT_THROW(a.setDeadCell(20, -20), LifeExeption);
    ASSERT_THROW(b.setDeadCell(20, -20), LifeExeption);
    ASSERT_THROW(c.setDeadCell(20, -20), LifeExeption);

    ASSERT_THROW(a.setDeadCell(100000, 100000), LifeExeption);
    ASSERT_THROW(b.setDeadCell(10000000, 1000000), LifeExeption);
    ASSERT_THROW(c.setDeadCell(10000, 100000), LifeExeption);
}

TEST(GETTERS, widwght) {
    Life a(10, 10);
    Life b(3, 6);
    Life c(1000, 5);
    ASSERT_EQ(a.getWidwght(), 10);
    ASSERT_EQ(b.getWidwght(), 3);
    ASSERT_EQ(c.getWidwght(), 1000);
}

TEST(GETTERS, height) {
    Life a(10, 10);
    Life b(3, 6);
    Life c(1000, 5);
    ASSERT_EQ(a.getHeight(), 10);
    ASSERT_EQ(b.getHeight(), 6);
    ASSERT_EQ(c.getHeight(), 5);
}

TEST(GETTERS, call_cells) {
    Life a(10, 10);
    Life b(3, 6);
    Life c(1000, 5);
    ASSERT_EQ(typeid(a.getCellStates()), typeid(std::vector<bool>));
    ASSERT_EQ(typeid(b.getCellStates()), typeid(std::vector<bool>));
    ASSERT_EQ(typeid(c.getCellStates()), typeid(std::vector<bool>));
}

TEST(GETTERS, call_cell) {
    Life a(10, 10);
    Life b(3, 6);
    Life c(1000, 5);
    a.setAliveCell(0, 0);
    a.setAliveCell(9,9);
    ASSERT_EQ(a.getCallState(0, 0), true);
    ASSERT_EQ(a.getCallState(-1,-1), true);
    ASSERT_EQ(a.getCallState(10,10), true);
}


TEST(GETTERS, call_cell_exeption){
    Life a(10,10);
    ASSERT_THROW(a.getCallState(-10,10), LifeExeption);
    ASSERT_THROW(a.getCallState(10,-10), LifeExeption);
    ASSERT_THROW(a.getCallState(100,10), LifeExeption);
    ASSERT_THROW(a.getCallState(10,100), LifeExeption);
}

TEST(GETTERS, check_live_neighbours){
    Life a(10,10);
    a.setAliveCell(5,5);
    a.setAliveCell(4,5);
    a.setAliveCell(6,7);
    ASSERT_EQ(a.check_live_neighbours(6,6) , 3);
}