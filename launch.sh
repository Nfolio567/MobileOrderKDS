echo "Delete build dir"
rm -rf build
echo "\nBuild:"
cmake -B build -G Ninja
cmake --build build
echo "\nRun:"
./build/kds -D