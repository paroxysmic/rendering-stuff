SRCDIR := src
OBJDIR := obj
DEBUGOBJDIR := dbg-obj
COMPILER := g++
SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES))
rast: $(OBJFILES)
	$(COMPILER) -c src/basicrasterizer.cpp -Iinclude -O3 -o obj/rast.o
	$(COMPILER) $(OBJFILES) obj/rast.o -O3 -o rast
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(COMPILER) -c $< -Iinclude -O3 -o $@
.PHONY: clean

clean:
	@echo CLEAN $(OBJFILES)
	@rm -f $(OBJFILES)