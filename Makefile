SRCDIR=./src

CXX=clang++
CXX_FLAGS=-O2 -Wall -g
BIN=brainfxxk

.PHONY:	all build clean

all: build

build: ${SRCDIR}/driver.cpp ${SRCDIR}/virtualmachine.cpp ${SRCDIR}/transformer.cpp
	${CXX} ${CXX_FLAGS} -o ${BIN} ${SRCDIR}/driver.cpp ${SRCDIR}/virtualmachine.cpp ${SRCDIR}/transformer.cpp

clean:
	@rm ${BIN}

