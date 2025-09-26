#include "options.h"
#include "printout.h"

int main(int argc, char* argv[]) {
    Options opts = parse_args(argc, argv);
    printout app(opts);
    return app.run_single_file(opts.files[0]);
}

