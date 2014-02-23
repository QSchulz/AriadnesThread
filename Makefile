# Differents types of files 
.SUFFIXES:.o.cpp


#---------------------------------
# INITIALISATION OF VARIABLES
#---------------------------------

# Compiler
CCC = g++

# Path where files are store
INCLUDES= -I/usr/openwin/include

# Compilation's options
CCFLAGS=  ${INCLUDES} -c

# Source files
FILES= main.cpp vertex.cpp stronglyconnectedcomponents.cpp level.cpp

#-----------
# TARGETS
#-----------

all:  $(FILES:.cpp=.o)
	$(CCC) -o project $(FILES:.cpp=.o)
	@echo "\n/!\\ When launching the executable, please give in argument the file with the matrix in it ! /!\\"
clean:
	/bin/rm $(FILES:.cpp=.o) project *~

#-------------------
# DEPENDANCE RULES 
#-------------------

main.o:main.cpp vertex.hpp stronglyconnectedcomponents.hpp level.hpp
vertex.o:vertex.cpp vertex.hpp
stronglyconnectedcomponents.o:stronglyconnectedcomponents.hpp stronglyconnectedcomponents.cpp
level.o:level.cpp level.hpp

#---------------------------------
# IMPLICITES RULES OF COMPILATION
#---------------------------------

.cpp.o:; ${CCC} ${CCFLAGS} $*.cpp

