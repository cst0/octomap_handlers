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
        std::cout << "didn't get output file, writing to stdout" << std::endl;
        output_stream.open("stdout", std::fstream::in);  // TODO-- stdout isn't gonna be accessed like this.
    } else {
        output_stream.open(outputfile, std::fstream::out);
        if (!output_stream.is_open()) {
            std::cerr << "Failed to open output file, closing." << std::endl;
            return -1;
        }
    }

    output_stream << "x,y,z,size";
    for (octomap::OcTree::leaf_iterator iter = octree.begin_leafs(); iter != octree.end_leafs(); ++iter) {
        std::string output_string = "";
        output_string += std::to_string(iter.getX()) + ",";
        output_string += std::to_string(iter.getY()) + ",";
        output_string += std::to_string(iter.getZ()) + ",";
        output_string += std::to_string(iter.getSize()) + "\n";
        output_stream << output_string;
    }
    std::cout << "I think I'm all done here." << std::endl;

    return 0;
}
