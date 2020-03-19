CC = g++
CFLAGS = -O2 -Wall -Wextra -g 
OBJS = main.o test.o noun_extractor.o document_element.o bow_vectorizer.o tfidf_vectorizer.o text_file_reader.o vector_utility.o document_analyzer.o cosine_similarity_calculator.o vectorizer.o bm25_vectorizer.o text_file_writer.o documents_pair.o dictionary_editor.o
PROGRAM = docana
MCFLAGS = `mecab-config --cflags` `mecab-config --libs` 

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(MCFLAGS)-o $(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)
