BUILD_DIR := build

default: clox

# Remove all build outputs and intermediate files.
clean:
	@ rm -rf $(BUILD_DIR)

# Compile a debug build of clox.
debug:
	@ $(MAKE) -f util/c.make NAME=cloxd MODE=debug SOURCE_DIR=c


# Compile the C interpreter.
clox:
	@ $(MAKE) -f util/c.make NAME=clox MODE=release SOURCE_DIR=c
	@ cp $(BUILD_DIR)/clox clox # For convenience, copy the interpreter to the top level.

cpplox:
	@ $(MAKE) -f util/c.make NAME=cpplox MODE=debug CPP=true SOURCE_DIR=c

.PHONY: clean clox debug default
