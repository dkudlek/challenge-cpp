
[TOC]

# Dependencies

- installation of cmake/ gcc on linux 
- installation of cmake and a visual studio compiler on windows
- googletest with exported path
- Install [OpencppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage/releases)



## Setup and build googletest
```sh
git clone https://github.com/google/googletest.git -b v1.14.0
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build 
#IF WIN
cmake .. -DCMAKE_INSTALL_PREFIX=../install -Dgtest_force_shared_crt=1  # Set install folder to PROJECT_ROOT/install
#ELSE
cmake .. -DCMAKE_INSTALL_PREFIX=../install 
#ENDIF
cmake --build . --config Release --target install  # Build release and trigger install procedure
cd ..
```

# Build repo

Setup cmake_playground
```sh 
mkdir build          # Create a directory to hold the build output.
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install # Set install folder to PROJECT_ROOT/install
(cmake .. -DCMAKE_INSTALL_PREFIX=../install -DBUILD_SHARED_LIBS=ON) # Shared lib
cmake --build . --config Release --target install  # Build release and trigger install procedure
ctest -C Release --verbose
```

# Resources
- [CMake 3.27.6 Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)


# Code Coverage Windows 


# CI
- Running docker in docker (gitlab-runner with executor: docker)
