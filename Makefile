CPP :=cpp
CFLAGS := -Wall
all: projectGame
projectGame: projectGame.o
clean:
	rm -f *.o projectGame
%.o : %.c
	$(CPP) $(CFLAGS) -c -o $@ $^
