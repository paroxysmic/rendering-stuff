OBJDIR := obj
LIBDIR := lib
DBGOBJDIR := dbg-obj
LIBFILES := $(wildcard $(LIBDIR)/*.cpp)
OBJFILES := $(patsubst $(LIBDIR)/%.cpp,$(OBJDIR)/%.o,$(LIBFILES))
DBGOBJFILES := $(patsubst $(LIBDIR)/%.cpp,$(DBGOBJDIR)/%-dbg.o,$(LIBFILES))
rast: $(OBJFILES) src/basicrasterizer.cpp
	g++ -c src/basicrasterizer.cpp -Iinclude -O3 -o obj/rast.o
	g++ $(OBJFILES) obj/rast.o -O3 -o rast
dbg: $(DBGOBJFILES) src/basicrasterizer.cpp
	g++ -c src/basicrasterizer.cpp -Iinclude -O0 -g -o dbg-obj/rast-dbg.o
	g++ $(DBGOBJFILES) dbg-obj/rast-dbg.o -O0 -g -o rast-dbg
test: $(OBJFILES) src/test.cpp
	g++ -c src/test.cpp -Iinclude -O0 -g -o obj/test.o
	g++ $(OBJFILES) obj/test.o -O0 -g -o test
$(OBJDIR)/%.o: $(LIBDIR)/%.cpp
	g++ -c $< -Iinclude -O3 -o $@
$(DBGOBJDIR)/%-dbg.o: $(LIBDIR)/%.cpp
	g++ -c -g  $< -Iinclude -O0 -o $@
.PHONY: clean print
clean:
	@rm -f $(DBGOBJFILES) $(OBJFILES) dbg-obj/rast-dbg.o obj/rast.o
	@echo CLEAN $(DBGOBJFILES) dbg-obj/rast-dbg.o
	@echo CLEAN $(OBJFILES) obj/rast.o 