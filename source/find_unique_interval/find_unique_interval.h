/// MIT License
///
/// Copyright (c) 2023 David Kudlek
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to
/// deal in the Software without restriction, including without limitation the
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
/// sell copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.

#ifndef ___FIND_UNIQUE_INTERVAL_H___
#define ___FIND_UNIQUE_INTERVAL_H___

#include <cstdint>     // int32_t
#include <functional>  // std::function
#include <memory>      // std::shared_ptr
#include <vector>      // std::vector

namespace find_unique_interval {

/// @brief A class which describes an interval with a lower and upper bound. It's a closed interval which means that
/// it includes both values.
class Interval {
public:
    /// @brief Creates an interval
    /// @param low lower bound of the interval (included)
    /// @param high upper bound of the interval (included)
    /// @throws std::invalid_argument if lower > upper
    Interval(const int32_t low, const int32_t high);
    Interval(const Interval& interval);
    Interval(Interval&& interval);
    Interval operator=(Interval&& interval);
    bool overlap(const Interval& rhs) const;
    int32_t low() const;
    int32_t high() const;

private:
    /// lower bound of the interval inclusive
    int32_t mLow = 0;
    /// upper bound of the interval inclusive
    int32_t mHigh = 0;

    void setLow();
};

typedef std::function<std::shared_ptr<Interval>(const std::vector<Interval>&)> findInterval;

/// Naive approach with: O(N * N)
///
/// Compare each intervale with all other intervals.
/// Early exit when we find one interval that doesn't overlap with an other interval from the
/// list.
std::shared_ptr<Interval> findNaive(const std::vector<Interval>& intervals);

/// Dynamic approach with: O(N*log(N)) + O(N) ~ O(N*log(N))
/// (1) Sort the array: O(N log N)
/// (2) Touch each element and compare to a memorized interval: O(N)
///
/// Memoization technique: We use one interval to memorize all the intervals we've seen. When a
/// interval overlaps with it then we grow this interval. This means for each element, we only
/// need to compare against this interval. If it doesn't overlap then we create a new interval.
/// If this is the last element or the next element does not overlap then we found an interval
/// that doesn't overlap with any other interval.
/// Early exit when we find one interval that doesn't overlap with an other interval from the
/// list.
std::shared_ptr<Interval> findDynamic(const std::vector<Interval>& intervals);

/// @brief Returns the first interval that does not overlap with any other
/// @param intervals list of all intervals
/// @return null or the first interval with matches the condition
std::shared_ptr<Interval> hasSingleInterval(const std::vector<Interval>& intervals, const findInterval& fun);
}  // namespace find_unique_interval

#endif