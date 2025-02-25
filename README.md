# Edge Impulse Example: Standalone Example Using CMake

This builds and runs an exported impulse locally on your machine. See the documentation at [Running your impulse locally](https://docs.edgeimpulse.com/docs/running-your-impulse-locally). This project demonstrates how to use CMake to generate a GNU Make build system for a local C++ SDK project.

## Basic Steps

Download and unzip your Edge Impulse C++ library into the *lib/* directory. Run the following commands from this directory:

```
mkdir build
cd build
cmake ..
```
 
**Note:** for Windows with MinGW, you will want to call `cmake .. -G "MinGW Makefiles"` instead.

Build the project (the `-j` flag can be used to speed up build time by using multiple threads):

```
make -j
```

Next, go into your *Edge Impulse project > Model testing* and click to *Show classification* for one of your test samples. Copy the *Raw features* and paste them into a new text file in the build directory: *build/features.txt*

Run the application and give it the location of the *features.txt* file as an argument:

```
./app features.txt
```

**Note:** for Windows, this command will likely be `app.exe features.txt`

 ## License

 [BSD 3-Clause Clear License](./LICENSE)