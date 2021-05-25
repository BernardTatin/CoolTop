#!/bin/sh

# // ======================================================================
# build.sh
# Created by Bernard on 25/04/2021
# // ======================================================================
# /*
# MIT License
#
# Copyright (c) 2021 Bernard Tatin
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#  */

build_dir=build
case $(uname) in
    NetBSD)
        export LDFLAGS=""
        export CFLAGS=""
        export MAKE=make
        export CC=clang
        ;;
    Linux)
        export LDFLAGS=
        export CFLAGS=
        export MAKE=make
        export CC=gcc
        ;;
    *)
        echo "Unkown OS!"
        exit 1
        ;;
esac

export CFLAGS="$CFLAGS -Wall -pedantic"

dohelp() {
    cat <<DOHELP
build.sh [-h|--help]: this text
build.sh --clean: clear the build directory and
                    run a new cMAKE
build.sh --all: build all the targets
build.sh <target> ...: build the targets

You can also use:
build.sh --clean --all
bild.sh --clean target target ...
DOHELP
    exit 0
}

[ $# -eq 0 ] && dohelp

while [ $# -ne 0 ]
do
    case $1 in
        -h|--help)
            dohelp
            ;;
        --clean)
            [ -d ${build_dir} ] && rm -rf ${build_dir}
            mkdir -p build
            (cd ${build_dir};
             cmake ..)
            ;;
        --all)
            (cd ${build_dir};
             ${MAKE})
            ;;
        *)
            (cd ${build_dir};
             ${MAKE} $1)
            ;;
    esac
    shift
done

