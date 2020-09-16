export ZERPHYR_TOOLCHAIN_VARIANT=cross-compile
export CROSS_COMPILE=/usr/bin/arm-none-eabi-

mkdir build
pushd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -GNinja ..
popd
