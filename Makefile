CXX		= g++
CXXFLAGS= -Wall -Isrc
LDFLAGS	= -lSDL2 -lSDL2main -lSDL2_image
INCLUDE	= -Isrc
TARGET	= VikingShmup

SRCDIR	= src
OBJDIR	= obj
BINDIR	= bin

SRC			:= $(wildcard $(SRCDIR)/*.cpp)
OBJ			:= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
SRC_SUBDIR	:= $(wildcard $(SRCDIR)/*/*.cpp)
OBJ_SUBDIR	:= $(SRC_SUBDIR:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJ) $(OBJ_SUBDIR)
	$(CXX) -o $@ $(OBJ) $(OBJ_SUBDIR) $(LDFLAGS)

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_SUBDIR): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

setup:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)/display
	@mkdir -p $(OBJDIR)/elements
	@mkdir -p $(OBJDIR)/events
	@mkdir -p $(OBJDIR)/time
	@mkdir -p $(OBJDIR)/world

clean:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(OBJ_SUBDIR)/*.o
	rm -f $(BINDIR)/$(TARGET)

