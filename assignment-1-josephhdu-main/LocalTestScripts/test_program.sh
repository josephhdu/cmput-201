#!/bin/bash

readonly ERROR="\e[31;1mERROR:\x1b[0m"
readonly SUCCESS="\e[92mTest passed!\x1b[0m"

readonly ERROR_USAGE_MSG="Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>"



# First, check that there are no warnings or errors (although you should run check_general_requirements.sh before this
make clean
output="$(make -B 2>&1)"
make_result=$?

if grep "warning:" <<<"${output}"; then
    echo -e $ERROR "Your program compiles with warnings. Please fix before trying to run this script."
    exit 2
fi

if [ $make_result -ne 0 ]
then
    echo -e $ERROR "make failed. Your program has compilation errors. Please fix before trying to run this script"
    exit 2
fi

# Check that executable exists and is executable
if [ ! -x encrypt ]
then
    echo -e $ERROR "encrypt could not be found or is not executable (maybe check the name of the executable in your Makefile)"
    exit 1
fi

# Testing incorrect arguments
echo -e "Testing incorrect arguments..."
output=$(./encrypt -o 10 -t 32 -q abc 2>&1 > /dev/null)
return_val=$?
# Check that return value of above argument is indeed 8
if [ $return_val -ne 7 ]
then
    echo -e $ERROR "Expected return value of 7 but received $return_val"
    exit 2
fi
# Verify correct error message
diff -Z -b -B -q <(echo $ERROR_USAGE_MSG) <(echo $output) > /dev/null
diff_exit=$?
if [ $diff_exit -ne 0 ]
then
    echo -e $ERROR "Incorrect error message"
    echo "Program output:"
    echo $output
    exit 2
fi
if [ $return_val -eq 7 ] && [ $diff_exit -eq 0 ]
then
    echo -e $SUCCESS
fi

echo ""

# Test student scripts
echo "Testing student-provided encryption script..."
if [ ! -f mapping_encryption.csv ] || [ ! -f input_encryption.txt ] || \
    [ ! -f output_encryption.txt ] || [ ! -x test_encryption.sh ]
then
    echo -e $ERROR "Files needed for student-provided encryption test case missing or script not executable"
    exit 2
else
    diff -Z -q <(./test_encryption.sh) output_encryption.txt
    if [ $? -ne 0 ]
    then
        echo -e $ERROR "test failed. The output of your program is different that the expected output you provide"
        exit 2
    else
        echo -e $SUCCESS
    fi
fi

echo ""

echo "Testing student-provided decryption script..."
if [ ! -f mapping_decryption.csv ] || [ ! -f input_decryption.txt ] || \
    [ ! -f output_decryption.txt ] || [ ! -x test_decryption.sh ]
then
    echo -e $ERROR "Files needed for student-provided decryption test case missing or script not executable"
    exit 2
else
    diff -Z -q <(./test_decryption.sh) output_decryption.txt
    if [ $? -ne 0 ]
    then
        echo -e $ERROR "test failed"
        exit 2
    else
        echo -e $SUCCESS
    fi
fi

echo ""

# Test sample cases provided with assignment description
echo "Testing sample cases provided with assignment description..."

echo "Test case 1 running as... ./encrypt -t sampletests/mapping_encryption.csv -i sampletests/input_encryption.txt -m 1"
output=$(./encrypt -t sampletests/mapping_encryption.csv -i sampletests/input_encryption.txt -m 1)
return_val=$?
if [ $return_val -ne 0 ]
then
    echo -e $ERROR "Your program returned with a non-0 value, suggesting that it failed on this test case"
    exit 2
else
    diff -Z <(echo "$output") sampletests/output_encryption.txt
    if [ $? != 0 ]
    then
        echo -e $ERROR "test failed"
        exit 2
    else
        echo -e $SUCCESS
    fi
fi

echo ""

echo "Test case 2 running as... ./encrypt -t sampletests/mapping_decryption.csv -i sampletests/input_decryption.txt -m 2"
output=$(./encrypt -t sampletests/mapping_decryption.csv -i sampletests/input_decryption.txt -m 2)
return_val=$?
if [ $return_val != 0 ]
then
    echo -e $ERROR "Your program returned with a non 0 value, suggesting that it failed on this test case"
else
    diff -Z <(echo "$output") sampletests/output_decryption.txt
    if [ $? -ne 0 ]
    then
        echo -e $ERROR "test failed"
        exit 2
    else
        echo -e $SUCCESS
    fi
fi

