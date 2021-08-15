#!/bin/bash

name=libphoton

flags=(
    -std=c99
    -Wall
    -Wextra
    -O2
)

inc=(
    -I.
    -Iinclude/
)

lib=(
    -Llib/
    -lfract
)

fail_op() {
    echo "Run with -d to build dynamically, or -s to build statically."
    exit
}

fail_os() {
    echo "OS is not supported yet..."
    exit
}

mac_dlib() {
    gcc ${flags[*]} ${inc[*]} ${lib[*]} -dynamiclib src/*.c -o $name.dylib
    install_name_tool -id @executable_path/$name.dylib $name.dylib 
}

linux_dlib() {
    gcc -shared ${flags[*]} ${inc[*]} ${lib[*]} -lm -fPIC src/*.c -o $name.so 
}

build() {
    mkdir lib/
    pushd fract/
    ./build.sh -s
    popd
    mv fract/libfract.a lib/libfract.a
}

clean() {
    rm -r lib/
}

dlib() {
    if echo "$OSTYPE" | grep -q "darwin"; then
        mac_dlib
    elif echo "$OSTYPE" | grep -q "linux"; then
        linux_dlib
    else
        fails_os
    fi
}

slib() {
    gcc ${flags[*]} ${inc[*]} -c src/*.c
    ar -crv $name.a *.o
    rm *.o
}

if [[ $# < 1 ]]; then 
    fail_op
elif [[ "$1" == "-d" ]]; then
    dlib
elif [[ "$1" == "-s" ]]; then
    slib
elif [[ "$1" == "-build" ]]; then
    build
elif [[ "$1" == "-clean" ]]; then
    clean
else
    fail_op
fi 
