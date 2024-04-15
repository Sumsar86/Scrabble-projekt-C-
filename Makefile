SRCDIR := src
INCDIR := include\project
TESTDIR := tests
LIBDIR := lib
EXE := $(TESTDIR)/kodu6.exe

CXX := g++
# CXXFLAGS := -std=c++2a -Wall -Werror -Wpedantic -g -I$(INCDIR)
CXXFLAGS := -std=c++2a -I$(INCDIR)

SRC_FILES := $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRCDIR)/%.cpp,$(LIBDIR)/%.o,$(SRC_FILES))

$(LIBDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXE): $(OBJ_FILES) | $(TESTDIR)
	$(CXX) $(OBJ_FILES) -o $@

$(TESTDIR):
	mkdir -p $(TESTDIR)

run: $(EXE)
	./$(EXE)
