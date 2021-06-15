CXX = g++
CURDIR = $(shell pwd)
INCLUDEDIR = ./include
LIBDIR = ./lib
OBJDIR = ./obj
SRCDIR = ./src
TESTDIR = ./testbin
LIBCSVDIR = libcsv-3.0.3
LIBCSV_NAME = libcsv.a

INCLUDE = -I $(INCLUDEDIR)
CXXFLAGS = -std=c++14 $(INCLUDE)
TESTLDFLAGS = -lgtest -lgtest_main -lpthread

CSV_READER_OBJ = $(OBJDIR)/CSVReader.o
CSV_MAIN_OBJ = $(OBJDIR)/main.o
CSV_WRITER_OBJ = $(OBJDIR)/CSVWriter.o
CSV_TEST_OBJ = $(OBJDIR)/testcsv.o
STRING_UTILS_OBJ = $(OBJDIR)/StringUtils.o
CSV_TEST_NAME = testcsv

all: directories lib/libcsv.a runTest

runTest: testbin/testcsv
	testbin/testcsv

bin/Tool:  $(CSV_READER_OBJ)
	$(CXX) $(CSV_READER_OBJ) -o bin/Tool

testbin/testcsv: $(CSV_WRITER_OBJ) $(CSV_READER_OBJ) $(CSV_TEST_OBJ) $(STRING_UTILS_OBJ) $(LIBDIR)/$(LIBCSV_NAME)
	$(CXX) $(CSV_WRITER_OBJ) $(CSV_READER_OBJ) $(CSV_TEST_OBJ) $(LIBDIR)/$(LIBCSV_NAME) $(CXXFLAGS) $(TESTLDFLAGS) -o testbin/testcsv

obj/StringUtils.o: $(SRCDIR)/StringUtils.cpp $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/StringUtils.cpp -c $(CXXFLAGS) -o $(OBJDIR)/StringUtils.o

$(CSV_READER_OBJ): $(SRCDIR)/CSVReader.cpp $(INCLUDEDIR)/CSVReader.h
	$(CXX) $(SRCDIR)/CSVReader.cpp -c $(CXXFLAGS) -o $(CSV_READER_OBJ)

$(CSV_WRITER_OBJ): $(SRCDIR)/CSVWriter.cpp $(INCLUDEDIR)/CSVWriter.h $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/CSVWriter.cpp -c $(CXXFLAGS) -o $(CSV_WRITER_OBJ)

obj/XMLReader.o: $(SRCDIR)/XMLReader.cpp $(INCLUDEDIR)/XMLReader.h $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/XMLReader.cpp -c $(CXXFLAGS) -o $(OBJDIR)/XMLReader.o

obj/XMLWriter.o: $(SRCDIR)/XMLWriter.cpp $(INCLUDEDIR)/XMLWriter.h $(INCLUDEDIR)/XMLEntity.h $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/XMLWriter.cpp -c $(CXXFLAGS) -o $(OBJDIR)/XMLWriter.o

$(CSV_TEST_OBJ): $(SRCDIR)/testcsv.cpp $(INCLUDEDIR)/CSVReader.h $(INCLUDEDIR)/CSVWriter.h
	$(CXX) $(SRCDIR)/testcsv.cpp -c $(CXXFLAGS) -o $(CSV_TEST_OBJ)



$(CSV_MAIN_OBJ): $(SRCDIR)/main.cpp $(INCLUDEDIR)/CSVReader.h
	$(CXX) $(CXXFLAGS) $(SRCDIR)/main.cpp -c -o $(OBJDIR)/main.o 

$(LIBCSVDIR)/Makefile: $(LIBCSVDIR)/configure
	cd $(LIBCSVDIR); ./configure --prefix=$(CURDIR); cd ..

$(LIBCSVDIR)/libcsv.la: $(LIBCSVDIR)/Makefile
	cd $(LIBCSVDIR); make; cd ..

$(LIBDIR)/libcsv.a: $(LIBCSVDIR)/libcsv.la
	cd $(LIBCSVDIR); make install; cd ..

directories: obj/ bin/ testbin/

obj/:
	mkdir obj/

bin/:
	mkdir bin/

testbin/:
	mkdir testbin/

clean:
	rm -f $(LIBDIR)/*
	rm -f $(INCLUDEDIR)/csv.h
	cd $(LIBCSVDIR); make clean; cd ..
	rm -f $(LIBCSVDIR)/Makefile