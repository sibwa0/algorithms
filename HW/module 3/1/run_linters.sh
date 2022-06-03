set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cppcheck"
check_log "cppcheck *.c utils --enable=all --inconclusive --error-exitcode=1 -I utils --suppress=missingIncludeSystem" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy utils/*.c utils/*.h -warnings-as-errors=* -extra-arg=-std=c99 --filter=-warnings-as-errors -- -Iutils" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=c utils/* utils/*" "Can't open for reading"

print_header "SUCCESS"