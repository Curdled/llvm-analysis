#!/bin/bash


mkdir build-clang2
cd build-clang2
cmake -G "Ninja" -DLLVM_ENABLE_PROJECTS="clang" -DCMAKE_BUILD_TYPE=Debug -DLLVM_TARGETS_TO_BUILD="X86" -DLLVM_ENABLE_RTTI=ON  ../llvm

