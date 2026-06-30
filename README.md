*This project has been created as part of the 42 curriculum by mpinto-l*

## get_next_line()

## Description

At 42 we need a function that reads a file one line at a time, without reading the whole file into memory at once. `get_next_line` does that: each call returns the next line from a file descriptor, including the terminating `\n`, until there's nothing left to read.

### Algorithm and Data Structure

`get_next_line` keeps a `static` variable between calls to hold whatever was read but not yet returned. On each call, it reads the file in chunks of `BUFFER_SIZE` bytes, joining each chunk onto that leftover with `ft_strjoin`, until a `\n` shows up or the file ends.

Once there's a `\n` (or EOF), `extract_line` cuts out everything up to and including it — that's the line returned to the caller. `update_rest` then saves whatever comes after the `\n` back into the static variable, ready for the next call.

Reading in small chunks instead of the whole file means a single `read` can land in the middle of a line, or even span several lines — the static variable is what keeps that from getting lost between calls.

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

`BUFFER_SIZE` can be replaced with any value.

### Makefile rules

| Rule | Description |
|------|-------------|
| `make` | Compiles the program |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the binary |
| `make re` | Runs `fclean` + `make` |

## Functions

| Function | File | Description |
|----------|------|-------------|
| `get_next_line` | [get_next_line.c](get_next_line.c) | Main function. Returns the next line from a file descriptor |
| `read_file` | [get_next_line.c](get_next_line.c) | Reads up to `BUFFER_SIZE` bytes from the file descriptor |
| `extract_line` | [get_next_line.c](get_next_line.c) | Cuts out the line up to and including the `\n` |
| `update_rest` | [get_next_line.c](get_next_line.c) | Saves whatever comes after the `\n` for the next call |
| `ft_strlen` | [get_next_line_utils.c](get_next_line_utils.c) | Returns the length of a string |
| `ft_strchr` | [get_next_line_utils.c](get_next_line_utils.c) | Locates a character in a string |
| `ft_strjoin` | [get_next_line_utils.c](get_next_line_utils.c) | Concatenates two strings into a new one |

## main.c

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int	fd;
	char	*line;
	int	count;

	count = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR opening file :( ");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		printf("[%d]:%s\n", count, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}
```

## Resources

- [Handling a File by its Descriptor in C](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
- [Local, Global and Static Variables in C](https://www.codequoi.com/en/local-global-static-variables-in-c/)
- ["Everything is a file" in UNIX](https://www.youtube.com/watch?v=dDwXnB6XeiA)
- [GNL-GOD](https://github.com/PLEB42/gnl-god)

### AI Usage

Claude was used to review the code and answer questions during development — specifically to debug issues and clarify concepts around static variables and memory management.
