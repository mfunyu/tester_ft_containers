#!/bin/bash

# --------------------------------- color def -------------------------------- #
THICK="\033[1m"
CYAN="\033[1;36m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[m"
PROMPT="${CYAN}$>${RESET}"
INFO=$CYAN
ERROR="${THICK}[ ${RED}ERROR${RESET} ${THICK}]"
OK="${THICK}[ ${GREEN}OK${RESET} ${THICK}]"
EOL="\n${RESET}"

# --------------------------------- settings --------------------------------- #
logfile="result.log"
stdfile="std.log"
option=""

# ------------------------------ setup arguments ----------------------------- #
if [ $# == 0 ]; then
	:
elif [ $1 == "vector" ]; then
	option="vector"
elif [ $1 == "map" ]; then
	option="map"
elif [ $1 == "stack" ]; then
	option="stack"
elif [ $1 == "set" ]; then
	option="set"
fi

# ------------------------------- check tester ------------------------------- #
stdoption="std"
if [ "$option" != "" ]; then
	stdoption="${option}-std"
fi
printf "${INFO}Checking for Tester Validity ...${EOL}"
printf "${PROMPT} make -s ${stdoption} ${EOL}"
make -s ${stdoption} > /dev/null

printf "${PROMPT} ./std_test > $stdfile${EOL}"
./std_test > $stdfile
if [ $? == 1 ] ; then
	cat $stdfile
	printf "\n"
	printf "${ERROR} : Tester does not return 100%% for STD${EOL}"
	exit
fi
printf "${OK} : Tester returns 100%% for STD${EOL}"

printf "\n"

# --------------------------------- run test --------------------------------- #
test_name=$option
if [ "$option" == "" ]; then
	option="ft"
	test_name="run"
fi
printf "${INFO}Runnning Tester ...${EOL}"
printf "${PROMPT} make -s ${option} ${EOL}"
make ${option} > /dev/null

./${test_name}_test 2>> $logfile
printf "See ./$logfile for more details ...${EOL}"


rm $stdfile
