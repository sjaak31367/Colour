# source: https://stackanswers.net/questions/how-to-make-makefile-recompile-when-a-header-file-is-changed
# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = 


# Source and build-output locations
SRC_DIR = ./src
BUILD_DIR = ./build
OUTPUT_EXEC = ./a.out
$(shell mkdir -p $(BUILD_DIR))

# Source and object files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(SOURCES))

#$(info $$SOURCES = [$(SOURCES)])
#$(info $$OBJECTS = [$(OBJECTS)])
#$(info $$DEPENDS = [$(DEPENDS)])


# Recipes
.PHONY: all
all: run

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm $(OUTPUT_EXEC)

.PHONY: build
build: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(OUTPUT_EXEC) $^

-include $(DEPENDS)

$(BUILD_DIR)/%.o: src/%.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

.PHONY: run
run:
ifeq (,$(wildcard $(OUTPUT_EXEC)))
	$(info [!] Executable doesn't exist! Compiling it now.)
	@$(MAKE) build
endif
	$(OUTPUT_EXEC)
