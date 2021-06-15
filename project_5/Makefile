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
TESTLDFLAGS = -lgtest -lgtest_main -lpthread -lexpat

CSV_READER_OBJ = $(OBJDIR)/CSVReader.o
MAIN_OBJ = $(OBJDIR)/main.o
CSV_WRITER_OBJ = $(OBJDIR)/CSVWriter.o
CSV_TEST_OBJ = $(OBJDIR)/testrouter.o
TEST_SPEED_OBJ = $(OBJDIR)/speedtest.o
STRING_UTILS_OBJ = $(OBJDIR)/StringUtils.o
MAP_ROUTER_OBJ = $(OBJDIR)/MapRouter.o

all: directories lib/libcsv.a runTest

runTest: testbin/router
	testbin/router

testbin/router: $(MAP_ROUTER_OBJ) $(CSV_WRITER_OBJ) $(CSV_READER_OBJ) $(CSV_TEST_OBJ) obj/XMLReader.o obj/XMLWriter.o $(STRING_UTILS_OBJ) $(LIBDIR)/$(LIBCSV_NAME)
	$(CXX) $(MAP_ROUTER_OBJ) obj/XMLReader.o $(CSV_READER_OBJ) $(CSV_TEST_OBJ) $(LIBDIR)/$(LIBCSV_NAME) $(CXXFLAGS) $(TESTLDFLAGS) -o testbin/router


$(MAP_ROUTER_OBJ): $(SRCDIR)/MapRouter.cpp $(INCLUDEDIR)/MapRouter.h $(INCLUDEDIR)/XMLReader.h $(INCLUDEDIR)/CSVReader.h
	$(CXX) $(SRCDIR)/MapRouter.cpp -c $(CXXFLAGS) -o $(OBJDIR)/MapRouter.o

$(STRING_UTILS_OBJ): $(SRCDIR)/StringUtils.cpp $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/StringUtils.cpp -c $(CXXFLAGS) -o $(OBJDIR)/StringUtils.o

$(CSV_READER_OBJ): $(SRCDIR)/CSVReader.cpp $(INCLUDEDIR)/CSVReader.h
	$(CXX) $(SRCDIR)/CSVReader.cpp -c $(CXXFLAGS) -o $(CSV_READER_OBJ)

$(CSV_WRITER_OBJ): $(SRCDIR)/CSVWriter.cpp $(INCLUDEDIR)/CSVWriter.h $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/CSVWriter.cpp -c $(CXXFLAGS) -o $(CSV_WRITER_OBJ)

obj/XMLReader.o: $(SRCDIR)/XMLReader.cpp $(INCLUDEDIR)/XMLReader.h $(INCLUDEDIR)/StringUtils.h $(INCLUDEDIR)/XMLEntity.h
	$(CXX) $(SRCDIR)/XMLReader.cpp -c $(CXXFLAGS) -o $(OBJDIR)/XMLReader.o

obj/XMLWriter.o: $(SRCDIR)/XMLWriter.cpp $(INCLUDEDIR)/XMLWriter.h $(INCLUDEDIR)/XMLEntity.h $(INCLUDEDIR)/StringUtils.h
	$(CXX) $(SRCDIR)/XMLWriter.cpp -c $(CXXFLAGS) -o $(OBJDIR)/XMLWriter.o

$(CSV_TEST_OBJ): $(SRCDIR)/testrouter.cpp $(INCLUDEDIR)/MapRouter.h
	$(CXX) $(SRCDIR)/testrouter.cpp -c $(CXXFLAGS) -o $(CSV_TEST_OBJ)

$(TEST_SPEED_OBJ): $(SRCDIR)/speedtest.cpp $(INCLUDEDIR)/MapRouter.h $(INCLUDEDIR)/StringUtils.h $(INCLUDEDIR)/CSVWriter.h
	$(CXX) $(SRCDIR)/speedtest.cpp -c $(CXXFLAGS) -o $(CSV_TEST_OBJ)

$(MAIN_OBJ): $(SRCDIR)/main.cpp $(INCLUDEDIR)/CSVReader.h
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