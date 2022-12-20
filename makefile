CC := g++
ALLDIRS := .
VPATH := $(ALLDIRS)
INCL := $(addprefix -I , $(ALLDIRS))
CL := $(addsuffix /*.cpp, $(ALLDIRS))

all: prog

prog: $(notdir $(patsubst %.cpp, %.o, $(wildcard $(CL))))
	$(CC) -o CAD.exe $^ -lgdi32
	
%.o: %.cpp
	$(CC) -c -MMD $(INCL) $<
	
include $(wildcard *.d)