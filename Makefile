.PHONY: all clean

# ---------------- PROJECT ----------------
PROJECT_NAME := game
SRC_DIR := src
OBJ_DIR := obj

# ---------------- TOOLCHAIN ----------------
CXX := g++
RAYLIB_PATH := C:/raylib/raylib

INCLUDES := -I. -I$(RAYLIB_PATH)/src
LIBS := -L$(RAYLIB_PATH)/src -lraylib -lopengl32 -lgdi32 -lwinmm -mconsole

CXXFLAGS := -std=c++17 -Wall -O0 -g -MMD -MP

# ---------------- SOURCES ----------------
# recursive wildcard (safe Windows make version)
SRC := $(wildcard $(SRC_DIR)/*.cpp) \
       $(wildcard $(SRC_DIR)/*/*.cpp) \
       $(wildcard $(SRC_DIR)/*/*/*.cpp) \
       $(wildcard $(SRC_DIR)/*/*/*/*.cpp)

OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
DEPS := $(OBJS:.o=.d)

# ---------------- BUILD ----------------
all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

# compile rule (FIXED for Windows cmd safety)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDES)

# include dependency tracking
-include $(DEPS)

# ---------------- CLEAN ----------------
clean:
	@if exist "$(OBJ_DIR)" rmdir /S /Q "$(OBJ_DIR)"
	@if exist "$(PROJECT_NAME).exe" del /Q "$(PROJECT_NAME).exe"