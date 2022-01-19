# Tool macros
CC = gcc
CXX = g++

# Settings
TARGET_NAME = my-motion
BUILD_PATH = ./build

# Location of main (can be C, but must use C++ compiler)
APP_SRC = main.c

# Search path for header files
CFLAGS += -Ilib/

# C compiler flags
CFLAGS += -Wall						# Include all warnings
CFLAGS += -g						# Generate GDB debugger information
CFLAGS += -Wno-strict-aliasing		# Disable warnings about strict aliasing
CFLAGS += -Os						# Optimize for size
CFLAGS += -DNDEBUG					# Disable assert() macro
CFLAGS += -DEI_CLASSIFIER_ENABLE_DETECTION_POSTPROCESS_OP	# Add TFLite_Detection_PostProcess operation

# C++ compiler flags
CXXFLAGS += -std=c++14				# Use C++14 standard

# Linker flags
LDFLAGS += -lm 						# Link to math.h
LDFLAGS += -lstdc++					# Link to stdc++.h

# Include C source code for required libraries
CSOURCES = 	$(wildcard lib/edge-impulse-sdk/CMSIS/DSP/Source/TransformFunctions/*.c) \
			$(wildcard lib/edge-impulse-sdk/CMSIS/DSP/Source/CommonTables/*.c) \
			$(wildcard lib/edge-impulse-sdk/CMSIS/DSP/Source/BasicMathFunctions/*.c) \
			$(wildcard lib/edge-impulse-sdk/CMSIS/DSP/Source/ComplexMathFunctions/*.c) \
			$(wildcard lib/edge-impulse-sdk/CMSIS/DSP/Source/FastMathFunctions/*.c) \
			$(wildcard lib/edge-impulse-sdk/CMSIS/DSP/Source/SupportFunctions/*.c) \
			$(wildcard lib/edge-impulse-sdk/CMSIS/DSP/Source/MatrixFunctions/*.c) \
			$(wildcard lib/edge-impulse-sdk/CMSIS/DSP/Source/StatisticsFunctions/*.c)

# Include C++ source code for required libraries
CXXSOURCES = 	$(wildcard lib/tflite-model/*.cpp) \
				$(wildcard lib/edge-impulse-sdk/dsp/kissfft/*.cpp) \
				$(wildcard lib/edge-impulse-sdk/dsp/dct/*.cpp) \
				$(wildcard lib/edge-impulse-sdk/dsp/memory.cpp) \
				$(wildcard lib/edge-impulse-sdk/porting/posix/*.c*) \
				$(wildcard lib/edge-impulse-sdk/porting/mingw32/*.c*)
CCSOURCES =

# Use TensorFlow Lite for Microcontrollers (TFLM)
CFLAGS += -DTF_LITE_DISABLE_X86_NEON=1
CSOURCES += lib/edge-impulse-sdk/tensorflow/lite/c/common.c
CCSOURCES +=	$(wildcard lib/edge-impulse-sdk/tensorflow/lite/kernels/*.cc) \
				$(wildcard lib/edge-impulse-sdk/tensorflow/lite/kernels/internal/*.cc) \
				$(wildcard lib/edge-impulse-sdk/tensorflow/lite/micro/kernels/*.cc) \
				$(wildcard lib/edge-impulse-sdk/tensorflow/lite/micro/*.cc) \
				$(wildcard lib/edge-impulse-sdk/tensorflow/lite/micro/memory_planner/*.cc) \
				$(wildcard lib/edge-impulse-sdk/tensorflow/lite/core/api/*.cc)

# Generate names for the output object files (*.o)
COBJECTS := $(patsubst %.c,%.o,$(CSOURCES))
CXXOBJECTS := $(patsubst %.cpp,%.o,$(CXXSOURCES))
CCOBJECTS := $(patsubst %.cc,%.o,$(CCSOURCES))
APP_OBJ := $(addsuffix .o, $(basename $(APP_SRC)))

# Default rule
.PHONY: all
all: $(TARGET_NAME)

# Compile library source code into object files
$(COBJECTS) : %.o : %.c
$(CXXOBJECTS) : %.o : %.cpp
$(CCOBJECTS) : %.o : %.cc
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
%.o: %.cc
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ -o $@
%.o: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ -o $@

# Compile main application into object file
$(APP_OBJ): $(APP_SRC)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $^ -o $@

# Build target (must use C++ compiler)
.PHONY: $(TARGET_NAME)
$(TARGET_NAME): $(APP_OBJ) $(COBJECTS) $(CXXOBJECTS) $(CCOBJECTS)
	mkdir -p $(BUILD_PATH)
	$(CXX) $(APP_OBJ) $(COBJECTS) $(CXXOBJECTS) $(CCOBJECTS) -o $(BUILD_PATH)/$(TARGET_NAME) $(LDFLAGS)

# Remove compiled object files
.PHONY: clean
clean:
	rm -f $(COBJECTS)
	rm -f $(CCOBJECTS)
	rm -f $(CXXOBJECTS)
	rm -r $(BUILD_PATH)