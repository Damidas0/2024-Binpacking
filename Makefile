# Définition des variables
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11
SRC_DIR := src
BUILD_DIR := build
TARGET := myprogram

# Liste de tous les fichiers source
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Liste de tous les fichiers objets
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Règle de compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle de construction du programme
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Règle de nettoyage
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Règle par défaut
all: $(TARGET)

# Phony targets
.PHONY: all clean
