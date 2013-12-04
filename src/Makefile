TARGET = genalg
OBJS = ${TARGET}.o
CXXFLAGS = -g -Wall -Wextra
LDFLAGS = # Libaries to be linked
.PHONY:clean

# CXX is already defined and depends on the object being made
${TARGET}:${OBJS}
	${CXX} -o ${TARGET} ${OBJS} ${LDFLAGS}

${TARGET}.o:${TARGET}.h

# This rule must be called explicitly
clean:
	rm -f *.o ${TARGET}.exe core*
