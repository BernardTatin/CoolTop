#!/bin/sh

script=$(basename $0)
dohelp() {
  cat <<DOHELP
$0 [-h|--help]: this text
$0 <preprocessor>: the prprocessor to use
    cpp, clang-cpp, ...
DOHELP
  exit 0
}

cpp=$(which $1)
[ -z "${cpp}" ] \
  && echo "Cannot find ${1}" \
  && dohelp

tmpfile=/tmp/pipo.c
cat > ${tmpfile} << PIPO
int main(int argn, char **argv) {
  return 0
}
PIPO

${cpp} -std=c11 -dM < ${tmpfile}
