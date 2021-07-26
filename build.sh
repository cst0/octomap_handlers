#!/bin/bash

# making sure there's a build dir
mkdir build 2>/dev/null

# heading over there
cd build

# handle makin' stuff: first cmake, then make (if successful)
cmake ../
make

cd -
