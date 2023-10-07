#include <find_unique_interval.h>

#include <chrono>
#include <fstream>  // std::ifstream
#include <iomanip>
#include <iostream>  // ?
#include <sstream>   // std::stringstream
#include <string>    // std::string

#include "argparse.hpp"  // ArgumentParser

namespace fui = find_unique_interval;
namespace sc = std::chrono;

std::string toTime(sc::microseconds duration) {
    auto durationSeconds = sc::duration_cast<sc::seconds>(duration);
    auto hours = (durationSeconds.count() / 60) % 60;
    auto minutes = durationSeconds.count() / 60;
    auto micros = duration.count() % 1000000;
    std::stringstream message;
    message << std::setw(2) << std::setfill('0') << hours << ":";
    message << std::setw(2) << std::setfill('0') << minutes << ":";
    message << std::setw(2) << std::setfill('0') << durationSeconds.count() << ".";
    message << std::setw(6) << std::setfill('0') << micros;
    return message.str();
}

int main(int argc, const char** argv) {
    // CLI
    ArgumentParser parser;
    parser.addArgument("--file", 1);
    parser.addArgument("--naive");
    parser.addArgument("--dynamic");
    parser.parse(argc, argv);
    const auto filename = parser.retrieve<std::string>("file");
    const bool runNaive = parser.exists("naive");
    const bool runDynamic = parser.exists("dynamic");
    // Read from file
    std::vector<fui::Interval> testSet;
    std::ifstream input(filename);
    for (std::string line; getline(input, line);) {
        const auto pos = line.find(",");
        const auto first = line.substr(0, pos);
        const auto second = line.substr(pos + 1);
        try {
            const int32_t low = std::stoi(first);
            const int32_t high = std::stoi(second);
            testSet.push_back(fui::Interval(low, high));
        } catch (std::invalid_argument const& ex) {
        } catch (std::out_of_range const& ex) {
        }
    }

    // Run algos
    if (runNaive) {
        auto start = sc::high_resolution_clock::now();
        auto res = fui::hasSingleInterval(testSet, fui::findNaive);
        auto stop = sc::high_resolution_clock::now();
        auto delta = sc::duration_cast<sc::microseconds>(stop - start);
        if (res) {
            std::cout << "Found with naive!" << std::endl;
            std::cout << "[" << res->low() << " " << res->high() << "]" << std::endl;
        } else {
            std::cout << "Not Found with naive!" << std::endl;
        }
        std::cout << "Took " << toTime(delta) << " || " << delta.count() << " us" << std::endl;
    }
    if (runDynamic) {
        auto start = sc::high_resolution_clock::now();
        auto res = fui::hasSingleInterval(testSet, fui::findDynamic);
        auto stop = sc::high_resolution_clock::now();
        auto delta = sc::duration_cast<sc::microseconds>(stop - start);
        if (res) {
            std::cout << "Found with dynamic!" << std::endl;
            std::cout << "[" << res->low() << " " << res->high() << "]" << std::endl;
        } else {
            std::cout << "Not Found with dynamic!" << std::endl;
        }
        std::cout << "Took " << toTime(delta) << " || " << delta.count() << " us" << std::endl;
    }
    return EXIT_SUCCESS;
}
