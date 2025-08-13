cmake_minimum_required(VERSION 3.28)

project(${APPLICATION_PROJECT_NAME}
        VERSION 1.0.0
        DESCRIPTION "Custom STM32F411 Bootloader"
        HOMEPAGE_URL "https://github.com/dimitri-ef/STM32_custom_bootloader"
        LANGUAGES ASM C)

file(GLOB SRCS "src/*.c")
set(INCS "inc/")

add_executable(${PROJECT_NAME}
    ${STARTUP}
    ${COMMON_SRCS}
    ${SRCS}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    STM32F411xE
    USER_VECT_TAB_ADDRESS
    VECT_TAB_OFFSET=0x00008000U
)

set(FLASH_START ${APPLICATION_FLASH_START})
set(FLASH_SIZE ${APPLICATION_FLASH_SIZE})

configure_file(
    "${LINKER_SCRIPT_PATH}.in"
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${LINKER_SCRIPT_NAME}"
    @ONLY
)

target_link_options(${PROJECT_NAME} PRIVATE 
    -T${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${LINKER_SCRIPT_NAME}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${COMMON_INCS}
    ${INCS}
)

add_custom_target(${PROJECT_NAME}_formats ALL
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    DEPENDS ${PROJECT_NAME}
    COMMENT "Convert ${PROJECT_NAME}.elf in ${PROJECT_NAME}.bin"
    VERBATIM
)

add_custom_target(flash_${PROJECT_NAME}
    COMMAND st-flash write ${PROJECT_NAME}.bin ${APPLICATION_FLASH_START}
    DEPENDS ${PROJECT_NAME}_formats
    COMMENT "Flash the bootloader"
    VERBATIM
)