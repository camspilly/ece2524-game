CXXFLAGS = -Wall -Wextra

all: projectGame

.PHONY: clean
clean:
	rm -rf *.o projectGame *.dSYM
