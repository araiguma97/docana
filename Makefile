#vim:set noexpandtab :

PROGRAM = nounex
OBJS = main.o test.o NounExtractor.o

CC = gcc
CFLAGS = -Wall -O2 -g

.SUFFIXES: .cpp .o

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) `mecab-config --cflags` $^ `mecab-config --libs`

.cpp.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)
