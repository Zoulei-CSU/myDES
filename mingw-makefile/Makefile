MAKEFILE      = Makefile

####### Compiler, tools and options
CC            = gcc
CXX           = g++
DEFINES       = -DUNICODE -D_UNICODE
CFLAGS        = -fno-keep-inline-dllexport -O3 -Wextra -Wall -W $(DEFINES)
CXXFLAGS      = -fno-keep-inline-dllexport -O3 -march=native -funroll-loops -std=gnu++11 -Wextra -Wall -W -fexceptions -mthreads $(DEFINES)
INCPATH       = -I.. -I.
LINKER      =        g++
LFLAGS        =        -Wl,-s -static -Wl,-subsystem,console -static -mthreads
LIBS        =         
COPY          = copy /y
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
DEL_FILE      = del
DEL_DIR       = rmdir
MOVE          = move
MKDIR         = mkdir

####### Files

SOURCES       = ..\main.cpp \
		..\des.cpp 
OBJECTS       = main.o \
		des.o

DESTDIR_TARGET = myDes.exe

####### Build rules

first: all
all: Makefile  $(DESTDIR_TARGET)

$(DESTDIR_TARGET):  $(OBJECTS) 
	$(LINKER) $(LFLAGS) -o $(DESTDIR_TARGET) $(OBJECTS)  $(LIBS)

clean:  
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(DESTDIR_TARGET)

####### Compile

main.o: ../main.cpp ../progress.hpp \
		../timer.hpp \
		../des.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ..\main.cpp

des.o: ../des.cpp ../des.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o des.o ..\des.cpp
