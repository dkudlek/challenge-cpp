#include <find_unique_interval.h>
#include <gtest/gtest.h>

#include <iostream>

namespace fui = find_unique_interval;

struct IntervalTest {
    std::string name;
    fui::Interval first;
    fui::Interval second;
    bool result;
};

TEST(find_unique_interval_interval, overlap) {
    std::vector<IntervalTest> tests = {
        {"0", fui::Interval(0, 4), fui::Interval(3, 5), true},  {"1", fui::Interval(0, 3), fui::Interval(3, 5), true},
        {"2", fui::Interval(3, 5), fui::Interval(4, 5), true},  {"3", fui::Interval(0, 4), fui::Interval(0, 4), true},
        {"4", fui::Interval(3, 5), fui::Interval(6, 7), false}, {"5", fui::Interval(4, 5), fui::Interval(6, 7), false}};

    for (auto i : tests) {
        EXPECT_EQ(i.first.overlap(i.second), i.result);
    }
}

struct AlogTest {
    std::string name;
    std::vector<fui::Interval> testVec;
    std::shared_ptr<fui::Interval> result;
};

std::shared_ptr<fui::Interval> newInterval(int32_t x, int32_t y) {
    return std::shared_ptr<fui::Interval>(new fui::Interval(fui::Interval(x, y)));
}

const std::vector<AlogTest> testSet = {
    {"empty", {}, nullptr},
    {"one", {fui::Interval(0, 3)}, newInterval(0, 3)},
    {"unmatched first",
     {fui::Interval(0, 3), fui::Interval(4, 6), fui::Interval(5, 7), fui::Interval(7, 10)},
     newInterval(0, 3)},
    {"unmatched last",
     {fui::Interval(4, 6), fui::Interval(5, 7), fui::Interval(7, 10), fui::Interval(25, 50)},
     newInterval(25, 50)},
    {"unmatched middle",
     {fui::Interval(3, 5), fui::Interval(4, 6), fui::Interval(7, 9), fui::Interval(10, 30), fui::Interval(10, 20)},
     newInterval(7, 9)},
    {"matched", {fui::Interval(1, 3), fui::Interval(2, 4), fui::Interval(3, 5), fui::Interval(4, 6)}, nullptr}};

TEST(find_unique_interval_algo, naive) {
    for (auto i : testSet) {
        auto result = fui::hasSingleInterval(i.testVec, &fui::findNaive);
        if (i.result == nullptr) {
            EXPECT_TRUE(i.result == result) << "test: " << i.name;
        } else {
            ASSERT_TRUE(i.result != nullptr) << "test: " << i.name;
            EXPECT_EQ(i.result->high(), result->high()) << "test: " << i.name;
            EXPECT_EQ(i.result->low(), result->low()) << "test: " << i.name;
        }
    }
}

TEST(find_unique_interval_algo, dynamic) {
    for (auto i : testSet) {
        auto result = fui::hasSingleInterval(i.testVec, &fui::findDynamic);
        if (i.result == nullptr) {
            EXPECT_TRUE(i.result == result) << "test: " << i.name;
        } else {
            ASSERT_TRUE(i.result != nullptr) << "test: " << i.name;
            EXPECT_EQ(i.result->high(), result->high()) << "test: " << i.name;
            EXPECT_EQ(i.result->low(), result->low()) << "test: " << i.name;
        }
    }
}