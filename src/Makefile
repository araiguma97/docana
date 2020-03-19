CC = g++
CFLAGS = -O2 -Wall -Wextra -g 
OBJS = main.o DocanaTest.o NounExtractor.o DocumentElement.o BowVectorizer.o TfidfVectorizer.o TextFileReader.o VectorizerUtility.o DocumentAnalyzer.o CosSimCalculator.o AbstractVectorizer.o Bm25Vectorizer.o CorpusLoader.o TextFileWriter.o DocumentsPair.o
PROGRAM = docana
MCFLAGS = `mecab-config --cflags` `mecab-config --libs` 

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(MCFLAGS)-o $(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)
