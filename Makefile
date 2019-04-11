#
#  To sa opcje dla kompilacji
#
CPPFLAGS= -c -g -Iinc -Wall -pedantic
EXEC= grafy
# __start__: uklad_rownan
	# ./uklad_rownan


${EXEC}: obj/main.o obj/lista.o
	g++ -Wall -pedantic -o ${EXEC} obj/main.o obj/lista.o

obj/main.o: src/main.cpp
	g++ ${CPPFLAGS} -Wall -pedantic -o obj/main.o src/main.cpp

obj/lista.o: src/lista.cpp inc/lista.h
	g++ ${CPPFLAGS} -Wall -pedantic -o obj/lista.o src/lista.cpp


clean:
	rm -f obj/*.o ${EXEC}

run: ${EXEC}
	./${EXEC}
