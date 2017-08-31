SRCDIR := src
OBJDIR := obj
MAIN := $(SRCDIR)/Main.cpp
SRCS := $(filter-out $(MAIN) $(SRCDIR)/Gem5Wrapper.cpp, $(wildcard $(SRCDIR)/*.cpp))
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))


# Ramulator currently supports g++ 5.1+ or clang++ 3.4+.  It will NOT work with
#   g++ 4.x due to an internal compiler error when processing lambda functions.
CXX := clang++
# CXX := g++-5
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
<\t>CXXFLAGS := -O3 -std=c++11 -g -Wall -I/Users/tarekjost/Downloads/DRAMPower-master/src -I/Users/tarekjost/Desktop/xerces-c-3.1.4/src -L/Users/tarekjost/Downloads/DRAMPower-master/src
<\t>LDFLAGS := -lboost_program_options -ldrampowerxml -ldrampower 
endif
ifeq ($(UNAME_S), Darwin)
 CXXFLAGS := -O0 -std=c++11 -g -Wall -I/usr/local/Cellar/boost/1.64.0_1/include -I/Users/tarekjost/Desktop/xerces-c-3.1.4/src
 LDFLAGS := -L/usr/local/Cellar/boost/1.64.0_1/lib -L/usr/local/Cellar/xerces-c/3.1.4/lib -L/Users/tarekjost/Downloads/DRAMPower-master/src -lboost_program_options -lxerces-c -ldrampowerxml -ldrampower
endif

.PHONY: all clean depend

all: depend ramulator

clean:
	rm -f ramulator
	rm -rf $(OBJDIR)

depend: $(OBJDIR)/.depend


$(OBJDIR)/.depend: $(SRCS)
	@mkdir -p $(OBJDIR)
	@rm -f $(OBJDIR)/.depend
	@$(foreach SRC, $(SRCS), $(CXX) $(CXXFLAGS) -DRAMULATOR -MM -MT $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC)) $(SRC) >> $(OBJDIR)/.depend ;)

ifneq ($(MAKECMDGOALS),clean)
-include $(OBJDIR)/.depend
endif


ramulator: $(MAIN) $(OBJS) $(SRCDIR)/*.h | depend
	$(CXX) $(CXXFLAGS) -DRAMULATOR -g -o $@ $(MAIN) $(INC) $(OBJS) $(LIB) $(LDFLAGS)

ramulator_debug: $(MAIN) $(OBJS) $(SRCDIR)/*.h | depend
	$(CXX) $(CXXFLAGS) -DRAMULATOR -g -o $@ $(MAIN) $(INC) $(OBJS) $(LIB) $(LDFLAGS)

$(OBJS): | $(OBJDIR)

$(OBJDIR): 
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -DRAMULATOR -g -c -o $@ $(INC) $(LIB) $(LDFLAGS) $<
