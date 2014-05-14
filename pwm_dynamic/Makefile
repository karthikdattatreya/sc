export SYSTEMC_HOME=/softwares/systemc/systemc-2.3.0
export SYSTEMC_AMS=/softwares/systemc/systemc-ams

EXTRACFLAGS = -DDEBUG_SYSTEMC
EXTRA_LIBS =
MODULE = run
SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

## Variable that points to SystemC,Systemc-ams and TUV_AMS  installation path
SYSTEMC = $(SYSTEMC_HOME)
SYSTEMCAMS=$(SYSTEMC_AMS)

## edit this to gccsparcOS5 for solaris
TARGET_ARCH = macosx64

CC     = g++  
OPT    = -O0
DEBUG  = -g

SYSDIR = -I $(SYSTEMC)/include
          
INCDIR = -I. -I.. $(SYSDIR) -I$(SYSTEMCAMS)/include -I$(TUV_LIB)/include
LIBDIR = -L. -L.. -L$(SYSTEMC)/lib-$(TARGET_ARCH) -L$(SYSTEMCAMS)/lib-$(TARGET_ARCH)

##using -m32 option for 32 bit compilation,i use this for linking with 32bit systemc ovp processor models

## Build with maximum gcc warning level
CFLAGS = -Wall -Wno-deprecated -Wno-return-type -Wno-char-subscripts $(DEBUG) $(OPT) $(EXTRACFLAGS)
LIBS   =  -lstdc++ -lpthread -lm $(EXTRA_LIBS) -lsystemc -lsystemc-ams 

EXE    = $(MODULE).exe

.PHONY: clean 

all: $(EXE)

$(EXE): $(OBJS) $(SYSTEMC)/lib-$(TARGET_ARCH)/libsystemc.a 
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS) $(LIBS) 2>&1 | c++filt

## based on http://www.paulandlesley.org/gmake/autodep.html
%.o : %.cpp
	$(CC) $(CFLAGS) $(INCDIR) -c -MMD -o $@ $<
	cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d


clean:
	-rm -f $(OBJS) *~ $(EXE) *.vcd *.wif *.isdb *.dmp *.P *.log *.dat

-include $(SRCS:.cpp=.P)
