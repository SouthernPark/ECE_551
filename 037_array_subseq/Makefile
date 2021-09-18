var=-std=gnu99 -Wall -Werror -pedantic

test:maxSeq.o test-subseq.o
	gcc -o test $(var) maxSeq.o test-subseq.o

maxSeq.o:maxSeq.c
	gcc -c  $(var) maxSeq.c

test-subseq.o:test-subseq.c
	gcc -c  $(var) test-subseq.c


