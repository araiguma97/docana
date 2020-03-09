#vim:set noexpandtab :

PROGRAM = docana
OBJS = main.o DocanaTest.o NounExtractor.o DocumentElement.o BowVectorizer.o TfidfVectorizer.o TextFileReader.o

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
