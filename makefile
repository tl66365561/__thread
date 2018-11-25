


all:multithread 
multithread:multithread.c
	gcc $^ -o $@ -pthread

.phone:clean
clean:
	rm -i multithread
