#
#  To sa opcje dla kompilacji
#
CPPFLAGS= -c -g -Iinc -Wall -pedantic
EXEC= grafy
LISTA= inc/lista.h inc/lista.hpp
GMACIERZ= inc/grafy_macierz.h inc/grafy_macierz.hpp
GLISTA= inc/grafy_lista.h inc/grafy_lista.hpp
KRUSKAL= inc/kruskal.h inc/kruskal.hpp
KOLEJKA= inc/kolejka.h inc/kolejka.hpp
# __start__: uklad_rownan
	# ./uklad_rownan


${EXEC}: obj/main.o
	g++ -Wall -pedantic -o ${EXEC} obj/main.o

obj/main.o: src/main.cpp ${LISTA} ${GMACIERZ} ${GLISTA} ${KRUSKAL} ${KOLEJKA}
	g++ ${CPPFLAGS} -Wall -pedantic -o obj/main.o src/main.cpp


clean:
	rm -f obj/*.o ${EXEC}

run: ${EXEC}
	./${EXEC}
