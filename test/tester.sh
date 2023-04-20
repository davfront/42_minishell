#!/bin/bash

# Minishell prompt string
MS_PS="^[[1;36mminishell>^[[0m "

# Get the directory containing this script
DIR="/mnt/FT/c3/minishell/test"

# Get the directory containing minishell
MS_DIR="/mnt/FT/c3/minishell"

# Move to minishell directory
cd $MS_DIR

# Initialize log file
log="$DIR/log.txt"
printf "" > "$log"

function test_commands() {

    # Get the commands file path from the function arguments
    test="$1"
    test_file="$DIR/tests/${test}.txt"
    echo ""
    echo -n "$test"| tr '[:lower:]' '[:upper:]'
    if [ ! -r "$test_file" ]; then
        echo ": no file found"
        return 1
    fi
    
    # Read the commands from the file
    commands=()
    while read -r cmd; do
    commands+=("$cmd")
    done < "$test_file"

    # Get the total number of commands
    total=${#commands[@]}
    printf " (%s tests)\n" "$total"
    
    # Initialize counters
    passed=0
    failed=0

    # Initialize command ID
    id=1

    # Initialize result string
    result="OK"

    # Loop over the list of commands
    for cmd in "${commands[@]}"; do

		# Capture output and exit code of minishell in file out1
		out1=$( "$MS_DIR/minishell" <<< "$cmd"$'\n'"exit" 2> "$DIR/err1" | cat -e )
		out1="${out1/${MS_PS}${cmd//\$/\\\$}\$$'\n'/}"  # remove command
		out1="${out1/${MS_PS}exit\$$'\n'exit\$/}" # remove exit
		echo -ne "$out1" > "$DIR/out1"
        sed -i 's/^minishell: //' "$DIR/err1"
		exit1=$?

        # Capture output and exit code of /bin/bash in file out2
        "/bin/bash" <<< "$cmd"$'\n'"exit" 2> "$DIR/err2" | cat -e > "$DIR/out2"
        sed -i 's/^\/bin\/bash: line 1: //' "$DIR/err2"
        sed -i "s/^\`.*//" "$DIR/err2" # remove command
        sed -i '/^$/d' "$DIR/err2" # remove empty lines
        exit2=$?

        # Compare the contents of files out1 and out2
        if cmp -s "$DIR/out1" "$DIR/out2" && [[ "$exit1" -eq "$exit2" ]] && cmp -s "$DIR/err1" "$DIR/err2"; then
            result="OK"
            passed=$((passed+1))
            printf "\033[32m%s.%s\033[0m " "$id" "$result"
        else
            result="KO"
            failed=$((failed+1))
            printf "\033[31m%s.%s\033[0m " "$id" "$result"

            
            printf "==============================================================\n" >> "$log"
            printf "%3s. [KO] %s\n" "$id" "$cmd" >> "$log"
            printf "==============================================================\n\n" >> "$log"

            if ! cmp -s "$DIR/out1" "$DIR/out2"; then
                printf "OUTPUT MISMATCH !!!\n\n" >> "$log"
                printf "minishell output:\n" >> "$log"
                cat "$DIR/out1" | cat -e >> "$log"
                printf "\n" >> "$log"
                printf "bash output:\n" >> "$log"
                cat "$DIR/out2" | cat -e >> "$log"
                printf "\n" >> "$log"
            fi

            if [[ "$exit1" -ne "$exit2" ]]; then
                printf "EXIT CODE MISMATCH !!!\n\n" >> "$log"
                printf "minishell exit code: %s\n" "$exit1" >> "$log"
                printf "bash exit code: %s\n" "$exit2" >> "$log"
                printf "\n" >> "$log"
            fi
            
            if ! cmp -s "$DIR/err1" "$DIR/err2"; then
                printf "STDERR MISMATCH !!!\n\n" >> "$log"
                printf "minishell stderr:\n" >> "$log"
                cat "$DIR/err1" >> "$log"
                printf "\n" >> "$log"
                printf "bash stderr:\n" >> "$log"
                cat "$DIR/err2" >> "$log"
                printf "\n" >> "$log"
            fi
        fi

		# Increment command ID
		id=$((id+1))
	done

	# Print breakline
	echo ""

	# Clean up temporary files
	rm $DIR/out1 $DIR/out2 $DIR/err1 $DIR/err2

	# Compute and print summary
	percentage=$(awk "BEGIN {printf \"%.0f\", $passed / $total * 100}")
	echo "Passed: $passed / $total ($percentage%)"
	
	# Print breakline
	echo -ne "\n"
}

# Test the commands using the test_commands function
test_commands syntax
test_commands echo