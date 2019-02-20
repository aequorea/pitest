## pitest
Pointerized insertion sort test.

Here is the source code for the pointer benchmark discussed [here](https://zyenz.blogspot.com/2019/02/fast-pointers.html).

If you want to try the benchmark program yourself run the python script bench.py or on a mac run macbench.py. It compiles the program, collects some information about your environment and displays it along with the benchmark result.

You'll need to install gcc on your system. On linux it may already be there. Or on debian descendents use:

    sudo apt-get install build-essential
    
On a mac you can install the [homebrew](https://brew.sh/) package and install gcc. After installing homebrew:

    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

The incantation goes something like this:

    brew update
    brew upgrade
    brew install gcc

At the moment, to use gcc you have to type gcc-8 instead of gcc. Apple links gcc to clang.

It may be possible to install homebrew on the linux subsystem of a Windows machine too. So you may be able to try things out there as well. I haven't tested this though.
