TARGET = genalg
OBJS = genalg.o
CXXFLAGS = -g -Wall
LDFLAGS = # Libaries to be linked
.PHONY:clean

# CXX is already defined and depends on the object being made
${TARGET}:${OBJS}
	${CXX} -o ${TARGET} ${OBJS} ${LDFLAGS}

genalg.o:genalg.h

# This rule must be called explicitly
clean:
	rm -f *.o ${TARGET}.exe core*
