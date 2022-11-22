# Makefile for building a single configuration of the C interpreter.
# It expects variables to be passed in for:
#
# MODE		"debug" or "release"
# NAME		Name of the output executable (and object file directory).
# SOURCE_DIR	Directory where source files and headers are found.

ifeq ($(CPP),true)
	# Ideally, we'd add -pedantic-errors, but the use of designated initializers
	# means clox relies on some GCC/Clang extensions to compile as C++.
	CFLAGS := -std=c++11
	C_LANG := -x c++
else
	CFLAGS := -std=c99
endif

CFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter

CFLAGS_FUZZER := $(CFLAGS) -g -fsanitize=address,fuzzer
SOURCE_FUZZER:= $(SOURCE_DIR)/fuzz_vm.cc

# Mode configuration.
ifeq ($(MODE),debug)
	CFLAGS += -O0 -DDEBUG -g -fsanitize=address,fuzzer-no-link -fsanitize-address-use-after-scope
	BUILD_DIR := build/debug
else
	CFLAGS += -O3 -flto
	BUILD_DIR := build/release
endif

# Files.
HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(addprefix $(BUILD_DIR)/$(NAME)/, $(notdir $(SOURCES:.c=.o)))

# Targets ---

default: build/$(NAME) build/$(NAME).a build/$(NAME)-fuzzer

# Link as a library
build/$(NAME).a: $(OBJECTS)
	@ printf "%8s %-40s %s\n" ar rcs $@
	@ mkdir -p build
	@ ar rcs $@ $^

# Link the interpreter.
build/$(NAME): $(OBJECTS)
	@ printf "%8s %-40s %s\n" $(CC) $@ "$(CFLAGS)"
	@ mkdir -p build
	@ $(CC) $(CFLAGS) $^ -o $@

build/$(NAME)-fuzzer: $(SOURCE_FUZZER) build/$(NAME).a
	@ printf "%8s %-40s %s\n" $(CC) $@ "$(CFLAGS_FUZZER)"
	@ mkdir -p build
	@ $(CC) $(CFLAGS_FUZZER) $(SOURCE_FUZZER) build/$(NAME).a -o $@

# Compile object files.
$(BUILD_DIR)/$(NAME)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
	@ printf "%8s %-40s %s\n" $(CC) $< "$(CFLAGS)"
	@ mkdir -p $(BUILD_DIR)/$(NAME)
	@ $(CC) -c $(C_LANG) $(CFLAGS) -o $@ $<

.PHONY: default
