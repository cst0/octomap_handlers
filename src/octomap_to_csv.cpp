#include "octomap/OcTree.h"
#include "unistd.h"
#include <cstdio>
#include <iostream>
#include <istream>

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
        output_stream.open("stdout", std::fstream::in);  // TODO-- stdout isn't gonna be accessed like this.
    } else {
        output_stream.open(outputfile, std::fstream::out);
        if (!output_stream.is_open()) {
            std::cerr << "Failed to open output file, closing." << std::endl;
            return -1;
        }
    }

    std::cout << "x,y,z,size" << std::endl;
    for (octomap::OcTree::leaf_iterator iter = octree.begin_leafs(); iter != octree.end_leafs(); ++iter) {
        std::cout << std::to_string(iter.getX())    + ",";
        std::cout << std::to_string(iter.getY())    + ",";
        std::cout << std::to_string(iter.getZ())    + ",";
        std::cout << std::to_string(iter.getSize()) + "\n";
    }

    return 0;
}
