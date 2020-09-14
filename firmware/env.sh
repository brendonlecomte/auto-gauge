export ZERPHYR_TOOLCHAIN_VARIANT=cross-compile
export CROSS_COMPILE=/usr/bin/arm-none-eabi-

mkdir build
pushd build
cmake -DBOARD=adafruit_trinket_m0 -GNinja ..
popd
