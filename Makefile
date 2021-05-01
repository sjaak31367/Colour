# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS =


# Source and build-output locations
src_dir = ./src
build_dir = ./build
output_exec = ./a.out
$(shell mkdir -p $(build_dir))

# Source and object files
src_files = $(wildcard $(src_dir)/*.cpp)
obj_files = $(addprefix $(build_dir)/,$(notdir $(src_files:.cpp=.o)))


# Recipes
.PHONY: default
default: run

.PHONY: build
build: $(obj_files)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(output_exec) $(obj_files)

$(build_dir)/%.o: $(src_dir)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(build_dir)
	rm $(output_exec)

.PHONY: run
run:
ifeq (,$(wildcard $(output_exec)))
	$(info [!] Executable doesn't exist! Compiling it now.)
	@$(MAKE) build
endif
	$(output_exec)
