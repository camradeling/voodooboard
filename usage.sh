#!/bin/bash
#set -x
MAP_FILE=${1}
RAM_START=$(cat ${MAP_FILE} | grep -w "RAM " | awk '{print $2}')
RAM_LENGTH=$(cat ${MAP_FILE} | grep -w "RAM " | awk '{print $3}')
RAM_END=$(cat ${MAP_FILE} | grep "_RAMEND" | awk '{print $1}')
RAM_USED=$((${RAM_END}-${RAM_START}))
RAM_LEFT=$((${RAM_LENGTH}-${RAM_USED}))
printf "RAM used: 0x%x, RAM left: 0x%x\n" ${RAM_USED} ${RAM_LEFT}

CCMRAM_START=$(cat ${MAP_FILE} | grep -w "CCMRAM " | awk '{print $2}')
CCMRAM_LENGTH=$(cat ${MAP_FILE} | grep -w "CCMRAM " | awk '{print $3}')
CCMRAM_END=${CCMRAM_START} #if CCMRAM is not used this var wont get into the map file
CCMRAM_END_CHECK=$(cat ${MAP_FILE} | grep "CCMRAMEND" | awk '{print $1}')
[ ! -z ${CCMRAM_END_CHECK} ] && CCMRAM_END=${CCMRAM_END_CHECK}
CCMRAM_USED=$((${CCMRAM_END}-${CCMRAM_START}))
CCMRAM_LEFT=$((${CCMRAM_LENGTH}-${CCMRAM_USED}))
printf "CCMRAM used: 0x%x, CCMRAM left: 0x%x\n" ${CCMRAM_USED} ${CCMRAM_LEFT}


FLASH_START=$(cat ${MAP_FILE} | grep "FLASH " | awk '{print $2}')
FLASH_LENGTH=$(cat ${MAP_FILE} | grep "FLASH " | awk '{print $3}')
FLASH_END=$(cat ${MAP_FILE} | grep "FLASHEND " | awk '{print $1}')
INITDATA_END=$(cat ${MAP_FILE} | grep -w "_INITDATAEND " | awk '{print $1}')
INITDATA_LENGTH=$((${INITDATA_END}-${RAM_START}))
#CCMINITDATA_END=$(cat ${MAP_FILE} | grep -w "_CCMINITDATAEND " | awk '{print $1}')
#CCMINITDATA_LENGTH=$((${CCMINITDATA_END}-${CCMRAM_START}))
FLASH_USED=$((${FLASH_END}-${FLASH_START}+${INITDATA_LENGTH}))
FLASH_LEFT=$((${FLASH_LENGTH}-${FLASH_USED}))
printf "FLASH used: 0x%x, FLASH left: 0x%x\n" ${FLASH_USED} ${FLASH_LEFT}