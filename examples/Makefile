# Variables: specifying the compiler and flags (warnings, debugging)
CC = gcc
CFLAGS = -Wall -Wextra -g

# List of executable files we want to generate
TARGETS = step1_basic step2_refactor step3_oracle step4_history step5_contract

# Main target: build all examples
# Simply type 'make' in the terminal
all: $(TARGETS)

# Rule for building each step
# % is a pattern that matches the file name (e.g., step1_basic)
# $< refers to the source file (.c)
# $@ refers to the output (the executable file)
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Special target to clean the project of binary files
# Type 'make clean' to remove all compiled programs
clean:
	rm -f $(TARGETS)

# Phony targets (to prevent make from confusing these with actual filenames)
.PHONY: all clean
