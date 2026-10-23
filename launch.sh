echo "Delete build dir"
rm -rf build
echo "\nBuild:"
cmake -B build -G Ninja
cmake --build build
echo "\nRun:"
QT_FATAL_WARNINGS=1 ./build/kds $1