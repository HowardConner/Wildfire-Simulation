.PHONY: clean run

# Default target
all: run

# Target to run the project
run:
	@mkdir -p build
	@cd build && cmake .. && cmake --build . --target run_all

# Target to clean the project
clean:
	@cd build && cmake --build . --target clean_all
