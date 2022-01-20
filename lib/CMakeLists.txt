cmake_minimum_required(VERSION 3.13.1)

# list(FIND ${BUILDSYSTEM_TARGETS} "app" HAS_APP)
# if( HAS_APP EQUAL -1 )
#     message( FATAL_ERROR, "Please create a target named 'app' before adding this file" )
# endif()


set(MODEL_FOLDER .)

include(${MODEL_FOLDER}/edge-impulse-sdk/cmake/utils.cmake)

RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk" "*.cpp")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk" "*.cc")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk" "*.s")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions" "*.c")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/CMSIS/DSP/Source/CommonTables" "*.c")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/CMSIS/DSP/Source/BasicMathFunctions" "*.c")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/CMSIS/DSP/Source/ComplexMathFunctions" "*.c")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/CMSIS/DSP/Source/FastMathFunctions" "*.c")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/CMSIS/DSP/Source/SupportFunctions" "*.c")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/CMSIS/DSP/Source/MatrixFunctions" "*.c")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/CMSIS/DSP/Source/StatisticsFunctions" "*.c")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "${MODEL_FOLDER}/tflite-model" "*.cpp")
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/porting/posix" "*.c*") 
RECURSIVE_FIND_FILE_APPEND(EI_SOURCE_FILES "edge-impulse-sdk/porting/mingw32" "*.c*")
LIST(APPEND EI_SOURCE_FILES "edge-impulse-sdk/tensorflow/lite/c/common.c")

target_include_directories(app PRIVATE
    ${MODEL_FOLDER}
)

# add all sources to the project
target_sources(app PRIVATE ${EI_SOURCE_FILES})

target_compile_definitions(app PUBLIC TF_LITE_DISABLE_X86_NEON=1)
