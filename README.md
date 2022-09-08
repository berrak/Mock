[![GitHub license](https://img.shields.io/github/license/berrak/Mock.svg?logo=gnu&logoColor=ffffff)](https://github.com/berrak/My_Macros/blob/master/LICENSE)
[![GitHub version](https://img.shields.io/github/release/berrak/Mock.svg?logo=github&logoColor=ffffff)](https://github.com/berrak/My_Macros/releases/latest)
[![GitHub issues](https://img.shields.io/github/issues/berrak/Mock.svg?logo=github&logoColor=ffffff)](https://github.com/berrak/Mock/issues)
[![Documentation](https://img.shields.io/badge/documentation-doxygen-green.svg)](https://berrak.github.io/Mock/classmock_1_1Mock.html)

# Arduino library Mock
Replace Arduino methods with `mocked` versions and let you develop code without the hardware. The mocked functions return immediately or return zero. Run parallel hardware and system development for greater efficiency. Arduino's command line tool, such as [arduino-cli](https://github.com/arduino/arduino-cli), frees you from Arduino IDE for tests and uploads.

## Why try Mock?

- Develop software independently of any related parallel hardware project.
- Use any development environment or your favorite editor with `arduino-cli` and library `Mock`.
- Use existing well-known tools for debugging.
- Reach set time goals faster in any Arduino microcontroller project.  

The purpose of this library is to be a practical eye-opener on mocked object usage, at least for some early phases of the project development cycle.

## Usage

Add the `include path` to the `Mock` source directory for the IDE. For example, in the Eclipse IDE, open.
`Project->Properties->C++ General->Paths and Symbols->Includes->Languages: Gnu C++, Include Directories: /home/bekr/Arduino/libraries/Mock/src`.

At the beginning of the `main.cpp` file, add.
```cpp
#include <Mock.h>
using namespace mock;
```
Pre-pend all Arduino's calls with '`Mock::`', like this.

```cpp
int value = Mock::analogRead(analog_read_pin);
```
The mocked functions return immediately or return zero. To remove all mocking fragments, use either search/replace in the IDE, or run the `demock` shell script on the file to erase all added `mock` -fragments.


## Examples

In Arduino IDE scroll down the long list below `File->Examples` and find `Mock`. An example run of the example may look like the following screen output. Note that a majority of the mocked methods return zero or return immediately. The `map()`-call is an exception and is defined as in Arduino. 
```
Mock::millis(): 0
Mock::analogRead(): 0
Mock::digitalRead(): 0
Mock::analogWrite(): NOP
Mock::analogRead(): 0
The map() return value should be ~2500: 2474
10 x Mock::digitalWrite() - LED_BUILTIN will not blink
```

## Documentation (GitHub Pages - Doxygen)

[Library documentation](https://berrak.github.io/Mock/classmock_1_1Mock.html).

## How to Install

Click on the green `Library Manager` badge above for instructions,
or use the alternative manual installation procedure.

1. Navigate to the [Releases page](https://github.com/berrak/Mock/releases).
1. Download the latest released ZIP-archive in `~/Arduino/libraries`.
1. Unzip the archive.
1. Rename the new directory. Remove *version-code*, or *master* in the name like this for `Mock`.
1. Restart Arduino IDE.
1. In Arduino IDE scroll down the long list below `Sketch->Include Library` and find `Mock`.

## Ensure any mock-fragments are removed in the build process

Now we will create a command script called `make-demock.sh`. Open an editor and copy the script content below. The `script` folder includes the code as well.

```bash
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
  echo "Pre-requisite 'grep' is not installed. Install the missing program and retry."
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
```

Move this file to the `~/.local/bin` folder, and make it executable:
```
$ mv make-demock.sh ~/.local/bin
$ chmod u+x ~/.local/bin/make-demock.sh
```
Run it with the file name, as the argument, like so.
```
make-demock.sh sketch.ino
make-demock.sh other.cpp
make-demock.sh other.h
```

## Planned Improvements/Changes

For planned changes, improvements, and known bugs, please visit the [Github issues tracker](https://github.com/berrak/Mock/issues). Unfortunately, they're not yet 100% coverage of Arduino methods, but only the most common. Testing more on other architectures and boards than Arduino Uno is also on the list of upcoming activities.

## Other related libraries

`FabioBatSilva` et al. and their library [ArduinoFake](https://github.com/FabioBatSilva/ArduinoFake) focus on validating methods in the project test phase.
