#!/bin/bash

NDK=~/Library/Android/sdk/ndk/20.0.5594570

options=("XCode lib project" "iOS Debug" "iOS Release" "Android Debug" "Android Release" "Quit")

width=20
cols=3

for ((i=0;i<${#options[@]};i++)); do 
  string="$(($i+1))) ${options[$i]}"
  printf "%s" "$string"
  printf "%$(($width-${#string}))s" " "
  [[ $(((i+1)%$cols)) -eq 0 ]] && echo
done

echo
read -p '#? ' opt
case $opt in
1)
    echo "${options[$opt-1]}"
    rm -dr build/xcode
    mkdir build/xcode
    cd build/xcode
    cmake ../../ -G Xcode -DCMAKE_TOOLCHAIN_FILE=../../toolchain/ios.toolchain.cmake -DPLATFORM=OS -DCMAKE_BUILD_TYPE=Debug
    make
    cd ..
    ;;
2)
    echo "${options[$opt-1]}"
    rm -dr build/ios
    mkdir build/ios
    cd build/ios
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=../../toolchain/ios.toolchain.cmake -DPLATFORM=OS -DCMAKE_BUILD_TYPE=Debug
    make
    cd ..
    ;;
3)
    echo "${options[$opt-1]}"
    rm -dr build/ios
    mkdir build/ios
    cd build/ios
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=../../toolchain/ios.toolchain.cmake -DPLATFORM=OS -DCMAKE_BUILD_TYPE=Release
    make
    cd ..
    ;;
4)
    echo "${options[$opt-1]}"
    rm -dr build/android
    mkdir build/android
	mkdir build/android/x86
	mkdir build/android/x86_64
	mkdir build/android/armeabi-v7a
	mkdir build/android/arm64-v8a
    cd build/android
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DANDROID_NDK=$NDK -DANDROID_ABI="x86"
    make
	mv libdrawloop.a ./x86
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DANDROID_NDK=$NDK -DANDROID_ABI="x86_64"
    make
	mv libdrawloop.a ./x86_64
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DANDROID_NDK=$NDK -DANDROID_ABI="armeabi-v7a"
    make
	mv libdrawloop.a ./armeabi-v7a
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DANDROID_NDK=$NDK -DANDROID_ABI="arm64-v8a"
    make
	mv libdrawloop.a ./arm64-v8a
    cd ..
    ;;
5)
    echo "${options[$opt-1]}"
    rm -dr build/android
    mkdir build/android
	mkdir build/android/x86
	mkdir build/android/x86_64
	mkdir build/android/armeabi-v7a
	mkdir build/android/arm64-v8a
    cd build/android
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_NDK=$NDK -DANDROID_ABI="x86"
    make
	mv libdrawloop.a ./x86
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_NDK=$NDK -DANDROID_ABI="x86_64"
    make
	mv libdrawloop.a ./x86_64
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_NDK=$NDK -DANDROID_ABI="armeabi-v7a"
    make
	mv libdrawloop.a ./armeabi-v7a
    cmake ../../ -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_NDK=$NDK -DANDROID_ABI="arm64-v8a"
    make
	mv libdrawloop.a ./arm64-v8a
    cd ..
    ;;
6)
  echo "Quit..."
  ;;
esac



