#!/bin/bash

# Checks that assignment files exist in repo and that code compiles without warnings or errors

readonly ERROR="\e[31;1mERROR:\x1b[0m"
readonly WARNING="\e[33;1mWARNING:\x1b[0m"
readonly SUCCESS="\e[92msuccess!\x1b[0m"
readonly EXE=encrypt
readonly SOURCE=encrypt.c
readonly REPO_FILES=("*akefile" "$SOURCE" "input_encryption.txt" \
    "mapping_encryption.csv" "test_encryption.sh" "output_encryption.txt" \
    "input_decryption.txt" "mapping_decryption.csv" "test_decryption.sh" \
    "output_decryption.txt")

# Check for README
if [ ! -f README ] && [ ! -f ReadMe ] && [ ! -f README.md ] && [ ! -f ReadMe.md ]
then
    echo -e $ERROR "Could not find README (or any acceptable variations of it)"
    exit 2
fi

# Check for makefile and make
if [ ! -f makefile ] && [ ! -f Makefile ]
then
    echo -e $ERROR "Could not find makefile. Exiting script"
    exit 1
fi
  
# Check for encrypt.c
if [ ! -f encrypt.c ]
then
    echo -e $ERROR "Could not find $SOURCE. Exiting script"
    exit 2
fi

# Check existence of every file...
for file in ${REPO_FILES[@]}
do
    if [ ! -f $file ]
    then
        echo -e $ERROR "Could not find $file. Exiting script"
        exit 2
    fi
done

echo ""


# Try to make (-B will force make)
make_error=false
output="$(make -B 2>&1)"
make_result=$?

if grep "warning:" <<<"${output}"; then
    echo -e $ERROR "Your program compiles with warnings. Please fix before submitting."
    make_error=true
fi

if [ $make_result -ne 0 ]
then
    echo -e $ERROR "make failed. Your program does not compile correctly."
    make_error=true
fi

# Check that executable exists
if [ ! -f $EXE ]
then
    echo -e $ERROR "Could not find $EXE in order to run it (either your program did not compile or you have a different executable name in your Makefile)"
    make_error=true
fi

if [ "$make_error" = false ]
then 
    echo -e "make ..." $SUCCESS
else
    exit 2
fi

echo ""

# Check make clean
clean_error=false
make clean
if [ $? -ne 0 ]
then
    echo -e $ERROR "make clean failed"
    clean_error=true
fi

if [ -f $EXE ]
then
    echo -e $ERROR "make clean should remove $EXE"
    clean_error=true
fi

if [ "$clean_error" = false ]
then
    echo -e "make clean ..." $SUCCESS
else
    exit 2
fi
echo ""

