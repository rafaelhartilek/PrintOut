//
// Created by kali on 9/25/25.
//

#include "../include/printout.h"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

printout::printout(Options opts) : opts_(std::move(opts)) {}

int printout::run_single_file(const std::string& path) {

    std::ifstream in(path);

    if (!in.is_open()) {
        std::cerr << "Error opening file: " << path << "\n";
        return 1;
    }
    reset_state_();
    int rc = process_stream_(in, std::cout);
    finalize_(std::cout);
    return rc;
}

int printout::process_stream_(std::istream& in, std::ostream& out) {
    std::string line;
    while (std::getline(in, line)) {
        out << line << "\n";
        ++line_count_; // count each line as we output it
        if (opts_.count_words) {
            word_count_ += count_words_in_line_(line);
        }
    }
    return 0;
}

void printout::finalize_(std::ostream& out) {
    if (opts_.count_lines) out << "Total lines: " << line_count_ << "\n";
    if (opts_.count_words) out << "Total words: " << word_count_ << "\n";
}

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


void printout::reset_state_() {
    line_count_ = 0;
    word_count_ = 0;
}