.PHONY: all clean

# ---------------- PROJECT ----------------
PROJECT_NAME := game
SRC_DIR := src
OBJ_DIR := obj

# ---------------- TOOLCHAIN ----------------
CXX := g++
RAYLIB_PATH := C:/raylib/raylib

INCLUDES := -I. -I$(RAYLIB_PATH)/src
LIBS := -L$(RAYLIB_PATH)/src -lraylib -lopengl32 -lgdi32 -lwinmm

CXXFLAGS := -std=c++17 -Wall -O0 -g -MMD -MP
LDFLAGS := -Wl,--subsystem,console

# ---------------- SOURCES ----------------
SRC := $(wildcard $(SRC_DIR)/*.cpp) \
       $(wildcard $(SRC_DIR)/*/*.cpp) \
       $(wildcard $(SRC_DIR)/*/*/*.cpp) \
       $(wildcard $(SRC_DIR)/*/*/*/*.cpp)

OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
DEPS := $(OBJS:.o=.d)

# ---------------- BUILD ----------------
all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(LDFLAGS)

# compile rule (robust mkdir for Windows)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@cmd /C "if not exist $(subst /,\,$(dir $@)) mkdir $(subst /,\,$(dir $@))"
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDES)

# dependency tracking
-include $(DEPS)

# ---------------- CLEAN ----------------
clean:
	@cmd /C "if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)"
	@cmd /C "if exist $(PROJECT_NAME).exe del /Q $(PROJECT_NAME).exe"