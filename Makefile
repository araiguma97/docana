#vim:set noexpandtab :

PROGRAM = docana
OBJS = main.o test.o NounExtractor.o DocumentElement.o BowVectorizer.o TfidfVectorizer.o

CC = g++
CFLAGS = -Wall -O2 -g

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) `mecab-config --cflags` $^ `mecab-config --libs`

%.o: %.h

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)
