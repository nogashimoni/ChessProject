#!/bin/bash

bin="chessprog"
diff="diff -iad"   # Diff command, or what ever
valgrind="valgrind --leak-check=full "
valgrind_flag="1"

# An array, do not have to declare it, but is supposedly faster
declare -a file_base=("./tests/testCmdSetup")

# Loop the array
for file in "${file_base[@]}"; do
    # Padd file_base with suffixes
    file_in="$file.in"             # The in file
    file_out_val="$file.outp"       # The out file to check against
    file_out_tst="$file.outp.tst"   # The outfile from test application

    # Validate infile exists (do the same for out validate file)
    if [ ! -f "$file_in" ]; then
        printf "In file %s is missing\n" "$file_in"
        continue;
    fi
    if [ ! -f "$file_out_val" ]; then
        printf "Validation file %s is missing\n" "$file_out_val"
        continue;
    fi

    printf "Testing input file: %s\n" "$file_in"
    
    echo "./$bin" "$file_in"  "$file_out_tst"
    
    # Run application, redirect in file to app, and output to out file
    "./$bin" < "$file_in" > "$file_out_tst"

    # Execute diff
    $diff "$file_out_tst" "$file_out_val"


    # Check exit code from previous command (ie diff)
    # We need to add this to a variable else we can't print it
    # as it will be changed by the if [
    # Iff not 0 then the files differ (at least with diff)
    e_code=$?
    if [ $e_code != 0 ]; then
            printf "\n== DIFF TEST FAILED ==\n \n : %d\n" "$e_code"
    else
            printf "\n== DIFF TEST IS OK! ===\n \n"
    fi

    # Pause by prompt
    read -p "Enter a to abort, anything else to continue: " input_data
    # Iff input is "a" then abort
    [ "$input_data" == "a" ] && break
    
    if [ $valgrind_flag == 1  ]; then
    	"valgrind" "./$bin" < $file_in
    fi
done

# Clean exit with status 0
exit 0