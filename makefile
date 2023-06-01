CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: st_pipeline

st_pipeline: partA.o partB.o partC.o st_pipeline.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

partA.o: partA.c partA.h
	$(CC) $(CFLAGS) -c $< -o $@

partB.o: partB.c partB.h
	$(CC) $(CFLAGS) -c $< -o $@

partC.o: partC.c partC.h
	$(CC) $(CFLAGS) -c $< -o $@

st_pipeline.o: st_pipeline.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o st_pipeline
