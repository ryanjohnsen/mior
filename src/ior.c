#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>  // atoi
#include <getopt.h>

#include "ior.h"

const char *short_opts = "a:b:Cehst:";

/* option struct:
struct option {
    const char *name; // long option name
    int has_arg;     // whether the option takes an argument (no_argument, required_argument, optional_argument)
    int *flag;       // if non-NULL, set *flag to val when option found
    int val;         // value to return or to set *flag to
};
*/
static struct option long_opts[] = {
    {"api", required_argument, NULL, 'a'},
    {"blockSize", required_argument, NULL, 'b'},
    {"reorderTasksConstant", no_argument, NULL, 'C'},
    {"fsync", no_argument, NULL, 'e'},
    {"help", no_argument, NULL, 'h'},
    {"segmentCount", required_argument, NULL, 's'},
    {"transferSize", required_argument, NULL, 't'},
    {NULL, 0, NULL, 0} // End of options
};

struct ior_options {
    char *api;
    int blockSize;
    int reorderTasksConstant;
    int fsync;
    int segmentCount;
    int transferSize;
};

// const char *usage_long = "Usage: ior [options]\n"
//                           "Options:\n"
//                           "  -a, --api <api>                Specify the API to use\n"
//                           "  -b, --blockSize <size>         Specify the block size\n"
//                           "  -C, --reorderTasksConstant     Reorder tasks constant\n"
//                           "  -e, --fsync                   Enable fsync\n"
//                           "  -h, --help                    Show this help message\n"
//                           "  -s, --segmentCount <count>    Specify the segment count\n"
//                           "  -t, --transferSize <size>     Specify the transfer size\n";
// const char *version = "IOR version 1.0\n";

// Error handling
void err_msg(const char *msg)
{
    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Print the error message with rank
    fprintf(stderr, "ERROR (rank %d): %s\n", rank, msg);
}

// Set to default values
int init_ior_options(struct ior_options *options)
{
    if (!options) {
        fprintf(stderr, "ERROR: ior_options struct is NULL\n");
        return -1;
    }
    options->api = "POSIX";
    options->blockSize = 1048576; // 1 MB
    options->reorderTasksConstant = 0;
    options->fsync = 0;
    options->segmentCount = 1;
    options->transferSize = 262144; // 256 KB

    return 0;
}

int parse_args(int argc, char **argv, struct ior_options *options)
{
    // print argv
    // for (int i = 0; i < argc; i++) {
    //     fprintf(stdout, "argv[%d]: %s\n", i, argv[i]);
    // }
    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
        switch (opt) {
            case 'a':
                options->api = optarg;
                break;
            case 'b':
                options->blockSize = atoi(optarg);
                break;
            case 'C':
                options->reorderTasksConstant = 1;
                break;
            case 'e':
                options->fsync = 1;
                break;
            case 'h':
                // TODO: print usage message, also this should fail out in main()
                fprintf(stdout, "Usage: ior [options]\n");
                return 0;
            case 's':
                options->segmentCount = atoi(optarg);
                break;
            case 't':
                options->transferSize = atoi(optarg);
                break;
            default:
                fprintf(stderr, "ERROR: Unknown option\n");
                return -1;
        }
    }
    return 0;
}

int validate_options(struct ior_options *options)
{
    if (options->blockSize <= 0) {
        err_msg("Block size must be greater than 0");
        return -1;
    }
    if (options->segmentCount <= 0) {
        err_msg("Segment count must be greater than 0");
        return -1;
    }
    if (options->transferSize <= 0) {
        err_msg("Transfer size must be greater than 0");
        return -1;
    }
    return 0;
}

int print_header(struct ior_options *options)
{
    return 0; // TODO: Implement header printing
}

int run_ior_tests(struct ior_options *options)
{
    return 0; // TODO: Implement IOR tests
}

int print_results(struct ior_options *options)
{
    return 0; // TODO: Implement results printing
}

int print_footer(struct ior_options *options)
{
    return 0; // TODO: Implement footer printing
}

int main(int argc, char **argv) 
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Initialize the IOR options
    struct ior_options options;
    int ret = init_ior_options(&options);
    if (ret != 0) {
        fprintf(stderr, "ERROR: Failed to initialize IOR options\n");
        goto fail;
    }

    // Parse command line arguments
    ret = parse_args(argc, argv, &options);
    if (ret != 0) {
        fprintf(stderr, "ERROR: Failed to parse command line arguments\n");
        goto fail;
    }

    // TODO: Validate options
    ret = validate_options(&options);
    if (ret != 0) {
        fprintf(stderr, "ERROR: Invalid options\n");
        goto fail;
    }

    // TODO: Print header
    ret = print_header(&options);
    if (ret != 0) {
        fprintf(stderr, "ERROR: Failed to print header\n");
        goto fail;
    }

    // TODO: Run the IOR tests
    ret = run_ior_tests(&options);
    if (ret != 0) {
        fprintf(stderr, "ERROR: Failed to run IOR tests\n");
        goto fail;
    }

    // TODO: Print results
    ret = print_results(&options);
    if (ret != 0) {
        fprintf(stderr, "ERROR: Failed to print results\n");
        goto fail;
    }

    // TODO: Print footer
    ret = print_footer(&options);
    if (ret != 0) {
        fprintf(stderr, "ERROR: Failed to print footer\n");
        goto fail;
    }

fail:
    // Finalize the MPI environment.
    MPI_Finalize();

    // TODO: Free variables and do other cleanup
}