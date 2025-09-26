//
// Created by Rafael Hartilek on 9/25/25.
//

#ifndef PRINTOUT_PRINTOUT_H
#define PRINTOUT_PRINTOUT_H

#include "options.h"
#include <cstddef>
#include <iosfwd>
#include <string>

class printout {
public:
    explicit printout(Options opts);

    // Run for exactly one file (single-file for now)
    int run_single_file(const std::string& path);

private:
    // Core pipeline: read text lines from in, write to out
    int process_stream_(std::istream& in, std::ostream& out);

    // Post-processing after the stream is consumed (e.g., totals)
    void finalize_(std::ostream& out);

    // Reset per-run state
    void reset_state_();

    std::size_t count_words_in_line_(const std::string& line);

    // Per-run state
    std::size_t line_count_ = 0;
    std::size_t word_count_ = 0;

    // Options captured at construction
    Options opts_;
};


#endif //PRINTOUT_PRINTOUT_H