cmake_minimum_required(VERSION 3.28)

project(stm32
        VERSION 1.0.0
        DESCRIPTION ""
        HOMEPAGE_URL "https://github.com/dimitri-ef/STM32_custom_bootloader"
        LANGUAGES ASM C)

# Common
file(GLOB COMMON_SRCS   ${CMAKE_SOURCE_DIR}/common/src/*.c)
set(COMMON_INCS         ${CMAKE_SOURCE_DIR}/common/inc)
set(STARTUP             ${CMAKE_SOURCE_DIR}/common/startup_stm32f411xe.S)
set(LINKER_SCRIPT_NAME  STM32F411XX_FLASH.ld)
set(LINKER_SCRIPT_PATH  ${CMAKE_SOURCE_DIR}/common/${LINKER_SCRIPT_NAME})

# Bootloader
set(BOOTLOADER_FLASH_START  0x08000000)
set(BOOTLOADER_FLASH_SIZE   32K)
set(BOOTLOADER_PROJECT_NAME bootloader)

add_subdirectory(${BOOTLOADER_PROJECT_NAME})

# Application
set(APPLICATION_FLASH_START     0x08008000)
set(APPLICATION_FLASH_SIZE      480K)
set(APPLICATION_PROJECT_NAME    application)

add_subdirectory(${APPLICATION_PROJECT_NAME})

# target to flash bootloader and application
add_custom_target(flash
    DEPENDS flash_${BOOTLOADER_PROJECT_NAME} flash_${APPLICATION_PROJECT_NAME}
    COMMENT "Flashing complete firmware (bootloader + application)"
    VERBATIM
)