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

#include "find_unique_interval.h"

#include <algorithm>
#include <stdexcept>  // std::invalid_argument
#include <string>     // std::to_string

namespace fui = find_unique_interval;

auto sortFn = [](const fui::Interval& a, const fui::Interval& b) -> bool {
    if (a.low() < b.low()) {
        return true;
    } else if (a.low() == b.low() && a.high() <= b.high()) {
        return true;
    }
    return false;
};

fui::Interval::Interval(const int32_t low, const int32_t high) : mLow(low), mHigh(high) {
    if (mLow > mHigh) {
        throw std::invalid_argument("low must be smaller or equal to high! But low is '" + std::to_string(mLow) +
                                    "' and high is " + std::to_string(mHigh) + "'");
    }
}

fui::Interval::Interval(const Interval& interval) : mLow(interval.low()), mHigh(interval.high()) {}

fui::Interval::Interval(Interval&& interval) : mLow(interval.low()), mHigh(interval.high()) {}

fui::Interval fui::Interval::operator=(fui::Interval&& interval) {
    mHigh = interval.mHigh;
    mLow = interval.mLow;
    return *this;
}

int32_t fui::Interval::low() const { return mLow; }

int32_t fui::Interval::high() const { return mHigh; }

bool fui::Interval::overlap(const Interval& rhs) const {
    if (rhs.low() <= high() && rhs.high() >= low()) {
        return true;
    }
    return false;
}

std::shared_ptr<fui::Interval> fui::findNaive(const std::vector<Interval>& intervals) {
    for (auto i = 0; i < intervals.size(); ++i) {
        auto hasOverlap = false;
        if (i == intervals.size() - 1) {
            // last interval
        }
        for (auto j = 0; j < intervals.size(); j++) {
            if (i == j) {
                // identity, false positive
                continue;
            } else if (intervals[i].overlap(intervals[j])) {
                hasOverlap = true;
                break;
            }
        }
        if (!hasOverlap) {
            return std::unique_ptr<Interval>(new Interval(intervals[i]));
        }
    }
    return std::shared_ptr<fui::Interval>();
}

std::shared_ptr<fui::Interval> fui::findDynamic(const std::vector<Interval>& intervals) {
    auto intv_copy = intervals;
    // Sort list (and copy)
    std::sort(intv_copy.begin(), intv_copy.end(), sortFn);
    // Initialize other helper variables
    auto span = Interval(0, 0);
    auto found = false;
    auto idxMax = intv_copy.size() - 1;
    for (auto i = 0; i < intv_copy.size(); ++i) {
        const auto candidate = intv_copy[i];
        // Update buffer and skip first check
        if (i == 0) {
            span = Interval(candidate);
            found = true;
            continue;
        }
        auto hasOverlap = span.overlap(candidate);
        if (hasOverlap) {
            if (candidate.high() > span.high()) {
                span = Interval(span.low(), candidate.high());
            }
            found = false;
        } else {
            if (i == 1) {
                // First is single
                return std::shared_ptr<fui::Interval>(new Interval(span));
            } else if (i == idxMax) {
                // Last is single
                return std::shared_ptr<fui::Interval>(new Interval(candidate));
            } else if (found) {
                // Middle is single
                //
                // The last interval did't overlap with the temporary interval and the current
                // interval also doesn't overlap with the last one. The last one does not have
                // an overlap with any other interval.
                return std::shared_ptr<fui::Interval>(new Interval(span));
            }
            span = Interval(candidate.low(), candidate.high());
            found = true;
        }
    }
    return std::shared_ptr<fui::Interval>();
}

std::shared_ptr<fui::Interval> fui::hasSingleInterval(const std::vector<fui::Interval>& intervals,
                                                      const findInterval& fun) {
    if (intervals.size() == 0) {
        return std::shared_ptr<fui::Interval>();
    } else if (intervals.size() == 1) {
        return std::shared_ptr<Interval>(new Interval(intervals[0]));
    }
    return fun(intervals);
}