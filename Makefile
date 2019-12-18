NAME=     match
CFLAGS=   -Wall -Wextra -Werror -pedantic -O3

all: $(NAME)

$(NAME): $(NAME).cpp
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(NAME)

.PHONY: all clean
