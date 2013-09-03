# smullprop
The smullprop programs are C++ ports of a pair of propellor design programs written
in the mid 1990's by Ed Smull.  Their primary goal is to duplicate the exact
functionality of his original programs, while being usable on modern operating
systems such as GNU/Linux or Windows.

## Usage
To use these programs, you will have to either compile them yourself or download
precompiled versions from the Releases section on GitHub.  If you want to compile
them yourself, see the Compiling section below.

Once you have a runnable copy, launch it either by double-clicking on it (Windows) or
invoking it from the command line (GNU/Linux, OS X) as follows:

    $ ./helical
or

    $ ./nonhelical

Follow its prompts.  When it is done, it will ask to save the results somewhere.  You
can type an absolute path or just a file name; if you just give it a filename, it
will write it to the same folder it is in.

## Compiling
To compile the programs on Linux, you will need the development tools **g++** and
**make**.  Once you have them installed, simply running

    $ make

will build both programs.

On Windows, you can use any set of tools to compile the programs; I recommend the
excellent [Code::Blocks](http://www.codeblocks.org/), which will install a free, open
source compiler automatically.
