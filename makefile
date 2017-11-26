CXX=g++

IDIR=include
SDIR=src
ODIR=obj
LDIR=lib

CFLAGS=$(shell pkg-config --cflags curlpp) -I$(IDIR)
LDFLAGS=$(shell pkg-config --libs curlpp)

_DEPS=device.h router.h trafficmeter.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJS=device.o router.o trafficmeter.o
OBJS=$(patsubst %,$(ODIR)/%,$(_OBJS))

LIBNAME=netgear

all: $(LDIR)/lib$(LIBNAME).so

$(LDIR)/lib$(LIBNAME).so: $(OBJS)
	@mkdir -p $(LDIR)
	$(CXX) -shared $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(LDIR)/lib$(LIBNAME).so

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -fPIC -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm $(ODIR)/*.o
