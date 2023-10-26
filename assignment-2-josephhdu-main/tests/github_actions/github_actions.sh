#!/usr/bin/env bash

# Define global vars
readonly ERROR="\e[31;1mERROR:\x1b[0m"
readonly SUCCESS="\e[92mTest passed!\x1b[0m"
readonly ERROR_USAGE_MSG="Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]"

#╔─────────────────────────────────────────────────────────────────────────────╗
#│ Chεck licεηsε fδr sτμdεητ ηαmε                                              |
#╚─────────────────────────────────────────────────────────────────────────────╝
if ! [[ -r License.md ]]; then
  echo -e "$ERROR Missing License.md at project root!"
  echo "Refusing to test without a signed license"
  exit 2
elif grep -q 'student name' License.md; then
  echo -e "$ERROR Missing student name in License.md at project root!"
  echo "Refusing to test without a signed license"
  exit 2
fi

#╔─────────────────────────────────────────────────────────────────────────────╗
#│ Chεck τhατ αll filεs αrε ρrεsεητ                                            |
#╚─────────────────────────────────────────────────────────────────────────────╝
declare -ar required_files=(\
  Makefile
  README.md
  src/wordSearch2D.c
  src/puzzle2D.c
  src/puzzle2D.h
  tests/local/puzzle.txt
  tests/local/wordlist.txt
  tests/local/expected_solution.txt
  tests/local/sample_test.sh
  tests/sample_tests/student_1_sols.txt
  tests/sample_tests/student_1_table.txt
  tests/sample_tests/student_1_wordlist.txt
  tests/sample_tests/student_2_sols.txt
  tests/sample_tests/student_2_table.txt
  tests/sample_tests/student_2_wordlist.txt
)

declare has_all_required_files=true

for f in "${required_files[@]}"; do
  if ! [[ -f "$f" ]]; then
    echo -e "$ERROR Missing file \`$f\` in your submission"
    has_all_required_files=false
  elif ! [[ -s "$f" ]]; then
    echo -e "$ERROR \`$f\` is empty"
    has_all_required_files=false
  fi
done

if [[ "$has_all_required_files" == false ]]; then
  exit 2
fi

#╔─────────────────────────────────────────────────────────────────────────────╗
#│ Λssεrτ Mαkεfilε hαs αll τhε cδrrεcτ flαgs                                   |
#╚─────────────────────────────────────────────────────────────────────────────╝
declare -ar gcc_args=(\
  '\-Wall'
  '\-Wextra'
  '\-Werror'
  '\-std=c99'
)
declare has_all_args=true

for arg in "${gcc_args[@]}"; do
  if ! grep -q "$arg" Makefile; then
    echo -e "$ERROR gcc command in makefile is missing argument \`$arg\`"
    has_all_args=false
  fi
done

if [[ "$has_all_args" == false ]]; then
  exit 2
fi

#╔─────────────────────────────────────────────────────────────────────────────╗
#│ Bμild ρrδgrαm ωiτh ηδ ωαrηiηgs                                              |
#╚─────────────────────────────────────────────────────────────────────────────╝
declare -r TFILE="$(mktemp)"
make clean

if ! make -B 2>&1 >"$TFILE"; then
  echo "exitcode: $?"
  echo -e "$ERROR \`make\` failed. Your program has compilation errors"
  exit 2
elif grep -Eq "(warning|error):" "$TFILE"; then
  echo -e "$ERROR Your program compiles with warning or errors"
  exit 2
fi

# Check that executable exists and is executable
if ! [[ -x wordSearch2D ]]; then
  echo -e "$ERROR Makefile failed to create wordSearch2D"
  exit 2
fi

#╔─────────────────────────────────────────────────────────────────────────────╗
#│ Tεsτ ρrδgrαm ωiτh iηcδrrεcτ αrgμmεητs                                       |
#╚─────────────────────────────────────────────────────────────────────────────╝
echo "Running program with wrong arguments..."

output="$(./wordSearch2D -o puzzle.txt 2>&1 >/dev/null)"
return_val=$?

if [[ $return_val -ne 6 ]]; then
  echo -e "$ERROR Program when run with wrong arguments returned exit-code $return_val instead of 6"
  exit 2
fi

if ! diff -Z -b -B -q <(echo "$ERROR_USAGE_MSG") <(echo "$output") > /dev/null; then
  echo -e "$ERROR Incorrect error message when program is run with wrong arguments"
  echo "Program output was:"
  echo "$output"
  echo "Expected output:"
  echo "$ERROR_USAGE_MSG"
  exit 2
fi

echo -e "$SUCCESS\n"

#╔─────────────────────────────────────────────────────────────────────────────╗
#│ Rμη sτμdεητ τεsτ cαsεs                                                      |
#╚─────────────────────────────────────────────────────────────────────────────╝
readonly local_path="./tests/local"
echo "Testing your own test case..."

declare has_all_tests=true

declare -ra local_test_files=(\
  puzzle.txt
  wordlist.txt
  expected_solution.txt
  sample_test.sh
)

for f in "${local_test_files[@]}"; do
  p="${local_path}/${f}"

  if [[ ! -f "$p" ]]; then
    echo -e "$ERROR Missing file $p for student-provided test case"
    has_all_tests=false
  fi
done

if [[ "$has_all_tests" == false ]]; then
  exit 2
fi

if ! bash "${local_path}/sample_test.sh"; then
  echo -e "$ERROR \`${local_path}/sample_test.sh\` exited with a non-zero error code"
  exit 2
fi


if ! diff -Z -q output.txt "${local_path}/expected_solution.txt"; then
  echo -e "$ERROR test failed"
  exit 2
else
  echo -e "$SUCCESS"
fi

echo ""

#╔─────────────────────────────────────────────────────────────────────────────╗
#│ Rμη ρrδνidεd τεsτ cαsε 1                                                    |
#╚─────────────────────────────────────────────────────────────────────────────╝
readonly provided_path=tests/sample_tests

echo "Sample test case 1"
echo "RUNNING AS: ./wordSearch2D -p ${provided_path}/student_1_table.txt -l 4 -w ${provided_path}/student_1_wordlist.txt -o output1.txt"

./wordSearch2D -p "${provided_path}/student_1_table.txt" -l 4 -w "${provided_path}/student_1_wordlist.txt" -o output1.txt

if ! diff -Z -q output1.txt "${provided_path}/student_1_sols.txt"; then
  echo -e "$ERROR test failed"
  exit 2
else
  echo -e "$SUCCESS"
fi

echo ""

#╔─────────────────────────────────────────────────────────────────────────────╗
#│ Rμη ρrδνidεd τεsτ cαsε 2                                                    |
#╚─────────────────────────────────────────────────────────────────────────────╝
echo "Sample test case 2"
echo "RUNNING AS: ./wordSearch2D -p ${provided_path}/student_2_table.txt -l 6 -w ${provided_path}/student_2_wordlist.txt -o output2.txt"

./wordSearch2D -p "${provided_path}/student_2_table.txt" -l 6 -w "${provided_path}/student_2_wordlist.txt" -o output2.txt

if ! diff -Z -q output2.txt "${provided_path}/student_2_sols.txt"; then
  echo -e "$ERROR test failed"
  exit 2
else
  echo -e "$SUCCESS"
fi
