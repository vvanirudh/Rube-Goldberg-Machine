#!/bin/bash
rm -rf external/src/Box2D
cd external/src
tar -zxvf Box2D.tar.gz
cd ../../
#diff -wB external/src/Box2D/Box2D/Common/b2Timer.cpp newfiles/b2Timer.cpp | patch external/src/Box2D/Box2D/Common/b2Timer.cpp
#diff -wB external/src/Box2D/Box2D/Common/b2Timer.h newfiles/b2Timer.h | patch external/src/Box2D/Box2D/Common/b2Timer.h
cd external/src/Box2D
mkdir build296
cd build296
cmake -DCMAKE_BUILD_TYPE=Release ../
make
make install
cd ../../../../

