
# set -e
# set -x

basepath=$(cd `dirname $0`/; pwd)

BUILD_DIR=${basepath}/build

#NINJA_EXE=/d/gao_tianlin/Android/AndroidSDK/cmake/3.10.2.4988404/bin/ninja.exe
#CMAKE=/d/gao_tianlin/Android/AndroidSDK/cmake/3.10.2.4988404/bin/cmake
#set CXX=D:/gao_tianlin/Android/AndroidSDK/ndk/21.1.6352462/toolchains/llvm/prebuilt/windows-x86_64/lib/gcc/arm-linux-androideabi/4.9.x

rm -rf ${BUILD_DIR}
mkdir  ${BUILD_DIR}

cd ${BUILD_DIR} 

cmake \
-DCMAKE_CXX_FLAGS="-std=c++1z" \
..

make

./src/main