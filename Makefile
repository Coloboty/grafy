#
#  To sa opcje dla kompilacji
#
CPPFLAGS= -c -g -Iinc -Wall -pedantic
EXEC= grafy
LISTA= inc/lista.h inc/lista.hpp
GMACIERZ= inc/grafy_macierz.h inc/grafy_macierz.hpp
GLISTA= inc/grafy_lista.h inc/grafy_lista.hpp
KRUSKAL= inc/kruskal.h inc/kruskal.hpp
PRIM= inc/prim.h inc/prim.hpp
INNE= inc/porownywacz.h inc/grafy_klasy.h inc/funkcje_pomocnicze.hpp inc/testy.h


${EXEC}: obj/main.o obj/testy.o
	g++ -Wall -pedantic -o ${EXEC} obj/main.o obj/testy.o

obj/main.o: src/main.cpp 
	g++ ${CPPFLAGS} -Wall -pedantic -o obj/main.o src/main.cpp

obj/testy.o: src/testy.cpp ${LISTA} ${GMACIERZ} ${GLISTA} ${KRUSKAL} ${PRIM} ${INNE}
	g++ ${CPPFLAGS} -Wall -pedantic -o obj/testy.o src/testy.cpp
clean:
	rm -f obj/*.o ${EXEC}

run: ${EXEC}
	./${EXEC}
