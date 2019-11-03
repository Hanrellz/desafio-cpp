CPP      = g++
RM       = rm -f
CPPFLAGS = -Wall -Wextra -pedantic -I. -O2 -std=c++11 -g
LDFLAGS  = -lpthread -lzmqpp -lzmq -lsodium -lPocoUtil -lPocoFoundation
SOURCES  = $(wildcard publish/*.cc) \
           $(wildcard subscribe/*.cc)
TARGETS  = $(SOURCES:%.cc=%)

all:${TARGETS}

clean:
  ${RM} *.obj *~* ${TARGETS}

${TARGETS}:
  ${CPP} ${CPPFLAGS} -o $@ ${@:%=%.cc} ${LDFLAGS}
