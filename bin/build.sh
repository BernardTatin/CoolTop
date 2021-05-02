#!/bin/sh

build_dir=build
case $(uname) in
    NetBSD)
        export LDFLAGS=""
        export CFLAGS=""
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

