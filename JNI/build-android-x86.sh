CurrentDir=$0
CurrentDir="$( cd "$( dirname $CurrentDir  )" && pwd  )"
echo "CurrentDir=$CurrentDir"

mkdir -p $CurrentDir/../_build/android_x86
cd $CurrentDir/../_build/android_x86
NDK_ROOT=/Users/yangsen/Library/Android/sdk/ndk-bundle
cmake \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_TOOLCHAIN_FILE=$NDK_ROOT/build/cmake/android.toolchain.cmake \
-DANDROID_ABI="x86" \
-DANDROID_TOOLCHAIN_NAME=llvm \
-DANDROID_NDK=$NDK_ROOT $CurrentDir/../ 
make
cp -f $CurrentDir/../_build/android_x86/lib/libmupdf.so /Users/yangsen/gitlab/android_docinshelf/app/src/main/jniLibs/x86/libmupdf.so
