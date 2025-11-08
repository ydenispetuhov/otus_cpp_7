mkdir build
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
chmod +x otus_cpp_7
cpack --config CPackConfig.cmake
make package_source