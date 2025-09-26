//
// Created by Rafael Hartilek on 9/25/25.
//

#include "../include/printout.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

// Constructor that copies contents of opts to private version of it
printout::printout(Options opts) : opts_(std::move(opts)) {}

// Handles opening up the specified file, parsing for processing and returning status
int printout::run_single_file(const std::string& path) {

    std::ifstream in(path);

    if (!in.is_open()) {
        std::cerr << "Error opening file: " << path << "\n";
        return 1;
    }

    // Sets counters to pre-run state (all 0`s)
    reset_state_();

    // Return code, indicates if processing ran as expected, or trows an error
    int rc = process_stream_(in, std::cout);
    finalize_(std::cout);
    return rc;
}

// Main processing pipeline for printing out contents and updating counters
int printout::process_stream_(std::istream& in, std::ostream& out) {
    std::string line;
    while (std::getline(in, line)) {
        out << line << "\n";
        ++line_count_;
        if (opts_.count_words) {
            word_count_ += count_words_in_line_(line);
        }
    }
    return 0;
}

// Prints out the counters, as specified by the flags
void printout::finalize_(std::ostream& out) {
    if (opts_.count_lines) out << "Total lines: " << line_count_ << "\n";
    if (opts_.count_words) out << "Total words: " << word_count_ << "\n";
}

// Handles counting the ammount of words line by line. Sums up to the total at the end
std::size_t printout::count_words_in_line_(const std::string &line) {
    int count = 0;
    bool in_word = false;

    for (char ch : line) {
        if (isspace(static_cast<unsigned char>(ch))) {
            in_word = false;
        } else {
            if (!in_word) {
                ++count;
                in_word = true;
            }
        }
    }
    return count;
}

// Set counter to 0
void printout::reset_state_() {
    line_count_ = 0;
    word_count_ = 0;
}