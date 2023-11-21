#!/bin/bash

# Create folder
mkdir OOPD_Assignment_4

# Change to the folder
cd OOPD_Assignment_4

# Create CPP files
touch Q1.cpp  Q1DBM.cpp Q2DB.cpp Q2DBM.cpp Q3.cpp Q4.cpp

# Create header files
touch Q1DB.h CSV3Db.h

# Create Makefile
cat <<EOL > Makefile
CXX=g++
CXXFLAGS=-std=c++11

all: Q1 Q1DBM Q2DB Q2DBM  Q3 Q4

Q1: Q1.cpp Q1DB.h
	\$(CXX) \$(CXXFLAGS) Q1.cpp -o Q1

Q2: Q2DB.cpp 
	\$(CXX) \$(CXXFLAGS) Q2Db.cpp -o Q2DB

Q3: Q3.cpp
	\$(CXX) \$(CXXFLAGS) Q3.cpp -o Q3

Q4: Q4.cpp
	\$(CXX) \$(CXXFLAGS) Q4.cpp -o Q4

clean:
	rm -f Q1 Q2 Q3 Q4
EOL

# Provide execute permissions to the Makefile
chmod +x Makefile
