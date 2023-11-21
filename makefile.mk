

all: compile link

compile: Q1.cpp Q1DBM.cpp Q2DB.cpp Q2DBM.cpp Q3.cpp Q4.cpp
    g++ -c Q1.cpp 
	g++ -c Q1DBM.cpp 
	g++ -c Q2DB.cpp 
	g++ -c Q2DBM.cpp 
	g++ -c Q3.cpp
	g++ -c  Q4.cpp
	

link: 
	g++ -o Q1 Q1.o
	g++ -o Q1DBM Q1DBM.o
	g++ -o Q2DB Q2DB.o
	g++ -o Q3 Q3.o
	g++ -o Q4 Q4.o
	

run:
	./Q1
	./Q1DBM
	./Q2DB
	./Q2DBM
	./Q3
	./Q4

clean: 
	rm -f Q1.o
	rm -f Q1DBM.o
	rm -f Q2DB.o
	rm -f Q2DBM.o
	rm -f Q3.o
	rm -f Q4.o

n_debug: Q1.cpp Q1DBM.cpp Q2DB.cpp Q2DBM.cpp Q3.cpp Q4.cpp

