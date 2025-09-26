//
// Created by Rafael Hartilek on 9/25/25.
//

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>

struct Options {
    bool count_lines = false;          // -c : print total lines after content
    bool count_words = false;          // -w : print total words after count
    std::vector<std::string> files;    // for now, expect exactly one
};

// Parse CLI Options (prints usage/errors to stderr and exits on failure)
Options parse_args(int argc, char* argv[]);

#endif // OPTIONS_H
