BINARY = bckuper
SRCDIR = src
DOCDIR=doc
DOX=Doxyfile

CXX = g++
CXXFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11

OBJECTS =\
		$(SRCDIR)/backup.o\
		$(SRCDIR)/parser.o\
		$(SRCDIR)/recovery.o\
		$(SRCDIR)/btar.o\
		$(SRCDIR)/search.o\
		$(SRCDIR)/main.o

all: compile doc

compile: $(BINARY)

run: $(BINARY)
	./$(BINARY)

clean:
	rm -Rf $(BINARY) $(OBJECTS) $(DOCDIR)

doc: 
	doxygen $(DOX) 2> /dev/null

$(BINARY): $(OBJECTS)
	$(CXX) -o $(BINARY) $(OBJECTS)

$(SRCDIR)/backup.o: $(SRCDIR)/backup.cpp $(SRCDIR)/backup.h $(SRCDIR)/search.h $(SRCDIR)/btar.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/btar.o: $(SRCDIR)/btar.cpp $(SRCDIR)/btar.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/parser.o: $(SRCDIR)/parser.cpp $(SRCDIR)/parser.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/recovery.o: $(SRCDIR)/recovery.cpp $(SRCDIR)/recovery.h $(SRCDIR)/search.h $(SRCDIR)/btar.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/search.o: $(SRCDIR)/search.cpp $(SRCDIR)/search.h $(SRCDIR)/btar.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(SRCDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/parser.h $(SRCDIR)/backup.h $(SRCDIR)/search.h $(SRCDIR)/btar.h $(SRCDIR)/recovery.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

