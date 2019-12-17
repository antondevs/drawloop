#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import shutil

def prepareBuildDir(name):
    path = "build/" + name
    if os.path.exists(path):
        shutil.rmtree(path)
    os.makedirs(path)
    os.chdir(path)

def executeShell(command):
    print command
    stream = os.popen(command)
    output = stream.read()
    print output

def showMenu(title,options):
    for key, value in options.items():
        print str(key) + ". " + value
    result = int(input(title))

    if not options.has_key(result):
        print "ERROR: Unknown option"
        sys.exit()
    
    return result

androidSdkPath = "~/Library/Android/sdk"
platform = showMenu("Target:", { 1:"Windows", 2:"Linux", 3:"MacOS", 4:"iOS", 5:"Android", 6:"Only XCode project" })

if platform == 6:
    prepareBuildDir("xcode")
    executeShell("cmake ../.. -G Xcode")
    sys.exit()

buildType = showMenu("Build type:", { 1:"Release", 2:"Debug" })
buildConfig = "-DCMAKE_BUILD_TYPE=Release" if buildType == 1 else "-DCMAKE_BUILD_TYPE=Debug"

if platform == 1:
    print platform
elif platform == 2:
    print platform
elif platform == 3:
    prepareBuildDir("macos")
    executeShell("cmake ../.. {} && make".format(buildConfig))
elif platform == 4:
    prepareBuildDir("ios")
    executeShell("cmake ../.. -DCMAKE_TOOLCHAIN_FILE=../../toolchain/ios.toolchain.cmake -DPLATFORM=OS {} && make".format(buildConfig))
elif platform == 5:
    abiList = ["x86", "x86_64", "armeabi-v7a", "arm64-v8a"]
    ndkPath = androidSdkPath + "/ndk/20.1.5948944"
    currentDir = os.getcwd()
    for abi in abiList:
        os.chdir(currentDir)
        prepareBuildDir("android/" + abi)
        executeShell("cmake ../../.. -DCMAKE_TOOLCHAIN_FILE=" + ndkPath + "/build/cmake/android.toolchain.cmake -DANDROID_ABI=\"" + abi + "\" && make")
