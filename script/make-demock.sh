#!/bin/bash
#
# make-demock.sh - Shell script to remove Mock-fragments in the C++ build-process.
# Author: Debinix Team (c). The MIT License.
# Date: 2022-09-07.
#

case $# in
  0) echo -n "Give the name of the file for 'democking': "
     read fname;;
  1) fname=$1
     ;;
  *) echo "Too many arguments were given, aborting. Please correct and retry."
     exit 1;;
esac

# Test if rpl is installed - command line tool that replace text strings in files
rpl --version >/dev/null 2>&1
if [ ! "$?" ]
then
  echo "Pre-requisite 'rpl' (https://github.com/rrthomas/rpl) is not installed."
  echo "Install the missing program with 'sudo apt install rpl' and retry."
  exit 1
fi

# Test if grep is installed
grep --version >/dev/null 2>&1
if [ ! "$?" ]
then
  echo "Pre-requsite 'grep' is not installed. Install the missing program and retry."
  exit 1
fi

echo "De-mocking '$fname' ..."

rpl -m --fixed-strings "Mock::" "" "$fname"
rpl -m --fixed-strings "#include <Mock.h>" "" "$fname"
rpl -m --fixed-strings "using namespace mock;" "" "$fname"

echo "Cleansing done!"
echo "Checking that all mock fragments are gone with grep ..."

if grep -n "Mock::" "$fname" ; then
  echo "Error: 'Mock::' was not cleansed in the file."
  exit 1
fi

if grep -n "#include <Mock.h>" "$fname" ; then
  echo "Error: '#include <Mock.h>' was not cleansed in the file."
  exit 1
fi

if grep -n "using namespace mock;" "$fname" ; then
  echo "Error: 'using namespace mock;' was not cleansed in the file."
  exit 1
fi

echo "All done and checked!"
# EOF
