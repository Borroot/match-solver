NAME=     match
CFLAGS=   -Wall -Wextra -Werror -pedantic

all: $(NAME)

$(NAME): $(NAME).cpp
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(NAME)

.PHONY: all clean
