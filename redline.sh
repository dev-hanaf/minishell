#!/bin/sh


cd 

HOME=$(pwd)
SOURCE_CODE_DIR="readline_source_code"

echo "we are in " $HOME

echo "making the library directory..."
mkdir readline

$(GIT_SSL_NO_VERIFY=true git clone https://git.savannah.gnu.org/git/readline.git $SOURCE_CODE_DIR)

echo "changing the directory to the source code"
cd $SOURCE_CODE_DIR

echo "configuring the source code"
./configure --prefix="$HOME/readline"

echo "making the library"
make everything

echo "installing the library"
make install