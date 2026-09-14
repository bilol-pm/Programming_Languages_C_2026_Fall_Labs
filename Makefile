# Makefile for Lab 1–5
# Builds only the sources that currently exist in src/, so unreleased labs
# don't break `make all`.
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
LDFLAGS = -lm
BUILD_DIR = bin
SRC_DIR = src

# Binary names per lab (binary name == source name, except "formats")
LAB1_BINS = hello calculator formats
LAB2_BINS = lab2_1 lab2_2 lab2_3
LAB3_BINS = lab3_task1 lab3_task2 lab3_task3
LAB4_BINS = week4_1_dynamic_array week4_2_struct_student week4_3_struct_database
LAB5_BINS = week5_task1_file_io week5_task2_struct_save_load week5_task3_student_management_system

# Map binary name -> source basename
src_of = $(if $(filter formats,$1),format_specifiers,$1)

# Keep only binaries whose source file exists
available = $(foreach b,$1,$(if $(wildcard $(SRC_DIR)/$(call src_of,$b).c),$(BUILD_DIR)/$b))

LAB1 = $(call available,$(LAB1_BINS))
LAB2 = $(call available,$(LAB2_BINS))
LAB3 = $(call available,$(LAB3_BINS))
LAB4 = $(call available,$(LAB4_BINS))
LAB5 = $(call available,$(LAB5_BINS))
PROGRAMS = $(LAB1) $(LAB2) $(LAB3) $(LAB4) $(LAB5)

.PHONY: all lab1 lab2 lab3 lab4 lab5 run-lab1 run-lab2 run-lab3 run-lab4 run-lab5 run-all debug help clean

all: $(PROGRAMS)

lab1: $(LAB1)
lab2: $(LAB2)
lab3: $(LAB3)
lab4: $(LAB4)
lab5: $(LAB5)

# Explicit rule for the one binary whose name differs from its source
$(BUILD_DIR)/formats: $(SRC_DIR)/format_specifiers.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Generic rule: bin/NAME from src/NAME.c
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# -----------------------

hello: $(BUILD_DIR)/hello
calculator: $(BUILD_DIR)/calculator
formats: $(BUILD_DIR)/formats

run-hello:
	./$(BUILD_DIR)/hello

run-calculator:
	./$(BUILD_DIR)/calculator

run-formats:
	./$(BUILD_DIR)/formats
# Run targets (run whatever was built, in order)
# -----------------------
run-lab1: lab1
	@for p in $(LAB1); do echo "== $$p =="; ./$$p; done

run-lab2: lab2
	@for p in $(LAB2); do echo "== $$p =="; ./$$p; done

run-lab3: lab3
	@for p in $(LAB3); do echo "== $$p =="; ./$$p; done

run-lab4: lab4
	@for p in $(LAB4); do echo "== $$p =="; ./$$p; done

run-lab5: lab5
	@for p in $(LAB5); do echo "== $$p =="; ./$$p; done

run-all: all
	@for p in $(PROGRAMS); do echo "== $$p =="; ./$$p; done

# -----------------------
# Debug build
# -----------------------
debug:
	$(MAKE) clean
	$(MAKE) CFLAGS="-std=c11 -Wall -Wextra -Wpedantic -g" all

# -----------------------
# Help
# -----------------------
help:
	@echo "Available make targets:"
	@echo "  make all          - Build all labs whose sources exist"
	@echo "  make labN         - Build specific lab (e.g., lab3)"
	@echo "  make run-labN     - Run all programs for a lab (1–5)"
	@echo "  make run-all      - Run all labs in sequence"
	@echo "  make debug        - Rebuild all with debugging (-g)"
	@echo "  make clean        - Remove build artifacts"
	@echo ""
	@echo "Currently buildable: $(notdir $(PROGRAMS))"

# -----------------------
# Cleanup
# -----------------------
clean:
	rm -rf $(BUILD_DIR)
