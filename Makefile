###########################################################
#
# Simple Makefile for Operating Systems Project 2
# osp2
#
###########################################################
.SUFFIXES: .h .c .cpp .o

CPP = g++
CCOPTS =
CPPOPTS =
LEX = flex
RM = /bin/rm
RMOPTS = -f

all: osp2a osp2b osp2c

###
osp2a: osp2a.o
	$(CPP) $(CPPOPTS) osp2a.o -o osp2a

osp2b: osp2b.o
	$(CPP) $(CPPOPTS) osp2b.o -o osp2b

osp2c: osp2c.o
	$(CPP) $(CPPOPTS) osp2c.o -o osp2c

osp2a.o: osp2a.cpp
	 $(CPP) $(CPPOPTS) -c osp2a.cpp

osp2b.o: osp2b.cpp
	 $(CPP) $(CPPOPTS) -c osp2b.cpp

osp2c.o: osp2c.cpp
	 $(CPP) $(CPPOPTS) -c osp2c.cpp

clean:
	$(RM) $(RMOPTS) *.o *~ core osp2a osp2b osp2c
