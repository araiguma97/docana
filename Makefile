CC = g++
CFLAGS = -O2 -Wall -g
OBJS = main.o DocanaTest.o NounExtractor.o DocumentElement.o BowVectorizer.o TfidfVectorizer.o TextFileReader.o VectorizerUtility.o DocumentAnalyzer.o CosSimCalculator.o DocumentSimilarity.o AbstractVectorizer.o Bm25Vectorizer.o
PROGRAM = docana
MCFLAGS = `mecab-config --cflags` `mecab-config --libs` 

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(MCFLAGS)-o $(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)
