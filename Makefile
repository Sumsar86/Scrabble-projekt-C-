SRCDIR := src
INCDIR := include\project
LIBDIR := include\libs
BUILDDIR := build
EXE := $(BUILDDIR)/kodu6.exe

CXX := g++
# CXXFLAGS := -std=c++2a -Wall -Werror -Wpedantic -g -I$(INCDIR)
CXXFLAGS := -std=c++2a -I$(INCDIR) -I$(LIBDIR)

SRC_FILES := $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRCDIR)/%.cpp,$(LIBDIR)/%.o,$(SRC_FILES))

$(LIBDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXE): $(OBJ_FILES) | $(BUILDDIR)
	$(CXX) $(OBJ_FILES) -o $@

$(BUILDDIR):
	mkdir -p $(TESTDIR)

run: $(EXE)
	./$(EXE)
