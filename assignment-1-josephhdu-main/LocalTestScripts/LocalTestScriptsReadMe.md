Test Scripts for Students for CMPUT 201 Assignment #1
=====================================================

This folder contains scripts that you may find helpful when locally testing your
solution during development.

We created these scripts to help you ensure that you adhere to the assignment requirements
and to save you from cases where you get a 0 on the assignment due to simple mistakes that can
easily be avoided.
!!!!!
HOWEVER, in the end, it is your responsibility to fully test your assignment and to make sure
it completely adheres to the assignment requirements. When in doubt, ask on the forum. 
It is also your responsibility to make sure your files are up to date on Github. 
!!!!!

Please note that (a variation of) these scripts automatically run whenever you push to GitHub and you can view those automated running results when you go to the commits page of your repo. We are providing them separately in this folder so you can run them locally on your machine. 


Getting started
---------------
Please do not change the location of the scripts.
The script will assume that the assignment files (e.g., encrypt.c) are in
the main folder, one level up from this folder.

The scripts are designed to work on the lab computers and likely any other Linux
machine. PLEASE RUN THEM ON THE LAB COMPUTERS. We are not responsible for any wrong results or errors received when those scripts are run on a different machine.

Finally, when submitting your assignment, is is your own responsibility, without relying
on the script, that your submission is valid. This might mean cloning your repo
into another directory and making sure the files are present and up-to-date,
or going to your repo on github.com and checking that the last pushed commit matches
the last commit on your local machine, which can be checked with git log.


Contents
--------
This folder contains three bash scripts:
 - check_and_test.sh: runs the two scripts below
 - check_general_requirements.sh : ensures that all assignment files are present
 - test_program.sh               : tests the validity of your solution with the sample test cases we provided in the sampletests/ folder in the repo. CAUTION: we will test your solution with additional test cases. This is just meant to show you how we will test your code. Passing these two tests DOES NOT GUARANTEE A FULL MARK for the assignment.

check_and_test.sh
-----------------
Run this script to do a full local check on your code.

First, make sure that the script is executable. Then run it from inside the main folder of your repo as follows:

./LocalTestScripts/check_and_test.sh

check_general_requirements.sh
-----------------------------

The script checks that:
 - All the needed files (a readme, encrypt.c, test cases, ...) are present
   in the directory.
 - make and make clean work as expected. 
 - The assignment files have been added to git. The script will output warnings
   if the code has changed but has not been committed, or a commit hasn't been pushed.


test_program.sh
---------------

The script checks that:
 - Calling encrypt with invalid arguments works as expected. That is, the exit
   code of the program is 7, and the error message appears on stderr (as opposed
   stdout)
 - That YOUR encryption and decryption test cases work.
 - That your program passes the test cases described in the assignment
   specification.


Automating additional test cases
--------------------------------
It's advised to test your solution on more than just a couple of test cases.
So, feel free to extend test_program.sh or make your own test script to run
all of your tests.

A word of caution: be VERY careful which flags you provide diff. The flags
in test_program.sh are what will be used when marking your assignment. Our diff ignores trailing
spaces at the end of a line. However, some
flags will make the comparison even more lenient so you should stick ONLY to what we use in our scripts.

We use:
 - diff -Z [file1] [file2] for encryption/decryption test cases. This means that
   your file must match exactly, apart from trailing spaces/newlines
 - diff -b -B -Z [file1] [file2] for testing error messages.
   Look at man diff for details.

You can use test_program.sh as a guide. Below is an explanation on what some
lines are doing.

  output=$(./encrypt -o 10 -t 32 -q abc 2>&1 > /dev/null)
This line will run [./encrypt -o 10 -t 32 -1 abc] and save ONLY stderr to
the variable output.

  diff <(./test_encryption.sh) output_encryption.txt
Since diff expects two files, we use a technique called "process substitution"
to compare the output of ONLY stdout when running ./test_encryption.sh,
with the contents of output_encryption.txt

  echo $?
Echoes the return value of the last command (you probably want ./encrypt). Note 
that running echo itself will have some exit code, so you shouldn't expect the
value of $? to persist over several lines in the script.

Questions and bug reports
-------------------------
Please post these in the Assignment #1 forum. Any information is probably
relevant for other students as well as for us.


Thanks for reading!
