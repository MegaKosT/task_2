#include <iostream>
#include "hash_table.h"
#include <gtest/gtest.h>


class HashTableTest : public testing::Test {
protected:
    void SetUp() override {
        t1.insert("Valery Simka", { .age = 21, .weight = 60 });
        t1.insert("David Divanov", { .age = 23, .weight = 75 });
        t2.insert("Harry Pattern", { .age = 28, .weight = 70 });
        t2.insert("Obi One", { .age = 28, .weight = 70 });
        t2.insert("Thomas Anderson", { .age = 19, .weight = 58 });
    }
    HashTable t0, t2, t3;
};
TEST_F(HashTableTest, SwapWorks) {
    t1.swap(t2);
    EXPECT_EQ(t1.size(), 3);
    EXPECT_EQ(t2.size(), 2);
    EXPECT_EQ(t2["David Divanov"].weight, 75);
}
TEST_F(HashTableTest, EraseWorks) {
    bool r = t2.erase("Obi One");
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, EmptyWorks) {
    bool r = t1.empty();
    EXPECT_EQ(r, false);
    r = t0.empty();
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, ContainsWorks) {
    bool r = t1.contains("Valery Simka");
    EXPECT_EQ(r, true);
    r = t1.contains("David Divanov");
    EXPECT_EQ(r, false);
}
TEST_F(HashTableTest, AtWorks) {
    Value& s = t1.at("Valery Simka");
    EXPECT_EQ(s.weight, 60);
    ASSERT_ANY_THROW(t1.at("try_to_break_my_table"));
}
TEST_F(HashTableTest, OperatorsWork) {
    bool r1 = t1 == t2;
    EXPECT_EQ(r1, false);
    bool r2 = t1 != t2;
    EXPECT_EQ(r2, true);
    unsigned int r3 = t2["Obi One"].weight;
    EXPECT_EQ(r3, 70);
    t1 = t2;
    r1 = t1 == t2;
    EXPECT_EQ(r1, true);
}
TEST_F(HashTableTest, CopyConstructWorks) {
    HashTable t3 = t1;
    EXPECT_EQ(t3.size(), 2);
    bool r0 = t3.contains("Valery Simka");
    EXPECT_EQ(r0, true);
    bool r2 = t3.contains("Thomas Anderson");
    EXPECT_EQ(r2, false);

}
TEST_F(HashTableTest, MoveConstructWorks) {
    HashTable t4 = std::move(t2);

    bool r0 = t4.contains("Harry Pattern");
    bool r1 = t4.contains("Obi One");
    bool r2 = t4.contains("Thomas Anderson");
    bool r3 = t2.empty();
    EXPECT_EQ(r0, true);
    EXPECT_EQ(r1, true);
    EXPECT_EQ(r2, true);
    EXPECT_EQ(r3, true);
}
