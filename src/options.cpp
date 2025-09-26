//
// Created by kali on 9/25/25.
//

#include "../include/options.h"
#include <iostream>
#include <string>
#include <cstdlib>

#include "printout.h"

static void print_usage_and_exit() {
    std::cerr <<
        "Usage: printout [-c] [-w] <file>\n"
        "  -c    Print total number of lines after file contents\n"
        "  -w    Print total number of words after file contents\n";;
    std::exit(1);
}

Options parse_args(int argc, char* argv[]) {
    Options opts;

    if (argc < 2) {
        print_usage_and_exit();
    }

    int i = 1;
    // Parse flags
    while (i < argc && argv[i][0] == '-') {
        std::string flag = argv[i++];
        if (flag == "-c") {
            opts.count_lines = true;
        } else if (flag == "-w") {
            opts.count_words = true;
        } else if (flag == "--help" || flag == "-h") {
            print_usage_and_exit();
        } else {
            std::cerr << "Unknown flag: " << flag << "\n";
            print_usage_and_exit();
        }
    }

    // Expect exactly one file for now
    if (i >= argc) {
        std::cerr << "Missing filename\n";
        print_usage_and_exit();
    }

    opts.files.emplace_back(argv[i]);
    return opts;
}
