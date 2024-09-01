cmake_minimum_required(VERSION 3.7)

message(STATUS "CMAKE_BUILD_TYPE = " ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_STANDARD 11)
message(STATUS "Starting build")
message(STATUS "USERNAME: " $ENV{USER})
set(CMAKE_VERBOSE_MAKEFILE ON)
project(voodooboard)
set(PROJECT_NAME voodooboard)
# specify the cross compiler
SET(CMAKE_C_COMPILER_WORKS 1)
SET(CMAKE_C_COMPILER arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(AS arm-none-eabi-as)
set(AR arm-none-eabi-ar)
set(OBJCOPY arm-none-eabi-objcopy)
set(OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

set(FreeRTOSSources
        ${PROJECT_SOURCE_DIR}/FreeRTOS-Kernel/portable/GCC/ARM_CM3/port.c
        ${PROJECT_SOURCE_DIR}/FreeRTOS-Kernel/queue.c
        ${PROJECT_SOURCE_DIR}/FreeRTOS-Kernel/list.c
        ${PROJECT_SOURCE_DIR}/FreeRTOS-Kernel/timers.c
        ${PROJECT_SOURCE_DIR}/FreeRTOS-Kernel/tasks.c
        ${PROJECT_SOURCE_DIR}/FreeRTOS-Kernel/portable/MemMang/heap_4.c
        )

set(PeripheralSources
        ${PROJECT_SOURCE_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
        ${PROJECT_SOURCE_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
        ${PROJECT_SOURCE_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
        ${PROJECT_SOURCE_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
        ${PROJECT_SOURCE_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
        ${PROJECT_SOURCE_DIR}/Libraries/CMSIS/Device/ST/STM32F10x/Source/Templates/system_stm32f10x.c
        )

set(Sources
        main.c
        Libraries/modbuslib/modbus.c
        adc.c
        globals.c
        i2c.c
        serial.c
        spi_flash.c
        stm32f10x_it.c
        stm32f10x_vector.c
        ${FreeRTOSSources}
        ${PeripheralSources}
        )
add_executable(${PROJECT_NAME}.elf ${Sources})

set(LINKER_SCRIPT stm32f103md2.ld)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
#set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/${LINKER_SCRIPT}")
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -mno-thumb-interwork -mfpu=vfp -msoft-float -mfix-cortex-m3-ldrd -nostdlib -Wl,-Map,output.map")

target_include_directories(${PROJECT_NAME}.elf PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}.elf PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/modbuslib)
target_include_directories(${PROJECT_NAME}.elf PUBLIC ${PROJECT_SOURCE_DIR}/FreeRTOS-Kernel/include)
target_include_directories(${PROJECT_NAME}.elf PUBLIC ${PROJECT_SOURCE_DIR}/FreeRTOS-Kernel/portable/GCC/ARM_CM3)
target_include_directories(${PROJECT_NAME}.elf PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/STM32F10x_StdPeriph_Driver/inc)
target_include_directories(${PROJECT_NAME}.elf PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/CMSIS/Device/ST/STM32F10x/Include)
target_include_directories(${PROJECT_NAME}.elf PUBLIC ${PROJECT_SOURCE_DIR}/Libraries/CMSIS/Include)

target_link_options(${PROJECT_NAME}.elf
                PUBLIC "SHELL:-T ${PROJECT_SOURCE_DIR}/${LINKER_SCRIPT} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map -Wl,-gc-sections"
                )

add_definitions(-DSTM32F10X_MD)
add_definitions(-DDEBUG)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
#        COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
#        )

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}"
        COMMAND ${CMAKE_SOURCE_DIR}/usage.sh ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map
        )
add_custom_target(BOOTLOADER_USAGE
        ${CMAKE_SOURCE_DIR}/usage.sh ${PROJECT_BINARY_DIR}/bootloader.map)