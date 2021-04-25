#!/bin/sh

build_dir=build
case $(uname) in
    NetBSD)
        libglfw3=$(pkg-config --libs glfw3)
        libGL="-L/usr/X11R7/lib -Wl,-R/usr/X11R7/lib -lGL"
        libGLU="-L/usr/X11R7/lib -Wl,-R/usr/X11R7/lib -lGLU -Wl,-R/usr/X11R7/lib -lGL"
        libGLEW="-L/usr/X11R7/lib -Wl,-R/usr/X11R7/lib -lGLEW -Wl,-R/usr/X11R7/lib -lGLU -Wl,-R/usr/X11R7/lib -lGL"

        export LDFLAGS="$libGL -lm $libGLU $libGLEW $libglfw3"
        export CFLAGS="-I/usr/X11R7/include -I/usr/pkg/include"
        export MAKE=gmake
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

CFLAGS="${CFLAGS} -Wall -pedantic -I../../Nuklear"

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

