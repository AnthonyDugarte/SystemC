# This makefile requires two environment variables to be set in your shell
#
# SYSTEMC_HOME = global route to systemc installation folder
# LD_LIBRARY_PATH = (subfolder of $SYSTEMC_HOME containing) libsystemc.a
#
# you can define these variables the file ~/.bashrc
# i.e put the following lines at the end of ~/.bashrc
#
# export SYSTEMC_HOME=/usr/local/systemc-2.3.2
# export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64
INCLUDES = -I./modules

SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)


CC = g++-6
EXECUTABLE = main.exe
CVERSION = -std=c++14

SYSTEMC = -I$$SYSTEMC_HOME/include -L$$LD_LIBRARY_PATH -lsystemc -lc -lm


all:$(EXECUTABLE)
$(EXECUTABLE):$(OBJECTS)
	$(CC) $(INCLUDES) $(SYSTEMC) $(CVERSION) $^ -o $@
.cpp.o: $(SOURCES)
	$(CC) $(INCLUDES) $(SYSTEMC) $(CVERSION) -c $^ -o $@
clean:
	$(RM) $(EXECUTABLE) *.o $(SOURCES_PATH)/*.o *.out
