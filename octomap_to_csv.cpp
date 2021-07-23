#include "octomap/OcTree.h"
#include "unistd.h"
#include <cstdio>
#include <iostream>

int main(int argc, char *argv[])
{

    int c;
    char *inputfile = NULL;
    char *outputfile = NULL;

    while ((c = getopt (argc, argv, "i:o:")) != -1) {
        switch (c) {
            case 'i':
                inputfile = optarg;
                break;
            case 'o':
                outputfile = optarg;
                break;
        }
    }

    if (inputfile == NULL) {
        std::cerr << "Didn't get input file-- not sure what to do here!" << std::endl;
        return -1;
    }
    octomap::OcTree octree = octomap::OcTree(inputfile);

    std::fstream output_stream;
    if (outputfile == NULL) {
        std::cout << "didn't get output file, writing to stdout" << std::endl;
        output_stream.open("stdout", std::fstream::in);  // TODO-- stdout isn't gonna be accessed like this.
    } else {
        output_stream.open(outputfile, std::fstream::out);
        if (!output_stream.is_open()) {
            std::cerr << "Failed to open output file, closing." << std::endl;
            return -1;
        }
    }



    return 0;
}
