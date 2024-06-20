

CPP = g++
BISON = bison
FLEX = flex
TGT = coi
SCAN = $(TGT).l
PARSE = $(TGT).y

OBJ = scan.o parse.tab.o main.o support.o ast.o options.o

CFLAGS = -g -fpermissive

HEADERS = common-headers.hh ast.hh 

$(TGT): $(OBJ)
	$(CPP) --std=c++0x  $(OBJ) -o $(TGT) -lfl -ly

scan.o: scan.c $(HEADERS)
	$(CPP) --std=c++0x  $(CFLAGS) -c $<

parse.tab.o:parse.tab.c $(HEADERS)
	$(CPP) --std=c++0x  $(CFLAGS) -c  $<

%.o: %.cc $(HEADERS)
	$(CPP) --std=c++0x  $(CFLAGS) -c $<

scan.c : $(SCAN) parse.tab.h
	$(FLEX) -l --yylineno -o scan.c $(SCAN)

parse.tab.c parse.tab.h : $(PARSE)
	$(BISON) -b parse -dv  $(PARSE)

clean :
	rm -f *.o *.output
	rm -f $(TGT) 
	rm -rf parse.tab.c parse.tab.h scan.c 
	rm -f a.out
