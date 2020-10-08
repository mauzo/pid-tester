# This is a BSD makefile. It will not work with GNU make.
# On non-BSD systems you may need to install and use bmake.
# Run 'make config' followed by 'make'.

.PATH: ${.CURDIR}/mk

.include "obj.mk"
.include "readconfig.mk"

.MAIN: all

PROG=	pid-tester

SRCS=	Graph.cc PIDTester.cc SampleSource.cc main.cc

OBJS=	${SRCS:R:S/$/.o/}

CLEAN+= ${PROG} ${OBJS}

${PROG}: ${OBJS}
	${CXX} ${LDFLAGS} -o ${.TARGET} ${OBJS} ${LIBS}

.cc.o:
	${CXX} ${CXXFLAGS} ${INCLUDES} -c -o ${.TARGET} ${.IMPSRC}

all: .PHONY ${PROG}

test: .PHONY ${PROG}
	./${PROG}

clean: .PHONY
	rm -f ${CLEAN}

cleandir: .PHONY
	cd ${.CURDIR} && rm -rf ${.OBJDIR}
