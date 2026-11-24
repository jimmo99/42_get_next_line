*This project has been created as part of the 42 curriculum by ssaavedr.*

# get_next_line

## Description

**get_next_line** is a C function that reads and returns a single line from a file descriptor (`fd`) each time it is called. The project introduces **static variables** in C, dynamic heap memory management (`malloc` / `free`), and low-level file I/O using the `read()` system call.

When called repeatedly inside a loop, `get_next_line()` retrieves the entire content of a file or standard input (`stdin`) line by line until reaching End Of File (`EOF`). Every returned line ends with the newline character `\n`, except when the end of the file is reached and the file does not end with `\n`.

### Project structure

.
├── README.md
├── get_next_line.h        # Function prototypes, BUFFER_SIZE macro and required includes
├── get_next_line.c        # Main logic: read loop, line extraction and stash update
└── get_next_line_utils.c  # Helper string functions (ft_strlen, ft_strchr, ft_strjoin, ft_substr)


## Instructions

### Compilation

The project does not require a `Makefile` and is compiled directly with `cc` using `-Wall -Wextra -Werror`. You can specify the read buffer size at compile time using `-D BUFFER_SIZE=n` (if omitted, `BUFFER_SIZE` defaults to `42` as defined in `get_next_line.h`):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl
To test edge cases (very small or very large reads), recompile with different buffer sizes:

Bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c -o gnl
Usage
Include "get_next_line.h" in your source file, open a file descriptor with open(), and call get_next_line(fd) in a loop until it returns NULL. Remember to free() each returned line to prevent memory leaks:

C
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
You can also test reading from standard input (stdin) by passing file descriptor 0 (get_next_line(0)).

Algorithm and data structure
Overall approach
Because read() reads fixed chunks of BUFFER_SIZE bytes rather than stopping at line breaks, a single call often reads past the \n into the next line. To preserve unread characters across function calls without using forbidden global variables, get_next_line() uses a single static char *stash pointer:

Input validation: If fd < 0 or BUFFER_SIZE <= 0, return NULL immediately.

Read into stash (read_to_stash): Allocate a heap buffer of BUFFER_SIZE + 1 bytes and loop read(fd, buffer, BUFFER_SIZE) until ft_strchr(stash, '\n') finds a newline or read() returns 0 (EOF). Each chunk is appended to stash via ft_strjoin(), which frees the previous stash block on every iteration to prevent leaks.

Extract line (extract_line): Scan stash up to the first \n (included) or \0 and allocate the exact substring to return using ft_substr().

Update stash (update_stash): Slice everything after the \n into a new heap string for the next call, free the old stash, and update the static pointer. If no \n remains (EOF), stash is freed and set to NULL.

Data structures
No complex custom structures are used. The state relies solely on:

static char *stash: Stored in the .bss data segment (automatically initialized to NULL) and pointing to a dynamically allocated null-terminated string on the heap.

Heap-allocated buffer: Allocated dynamically (malloc(BUFFER_SIZE + 1)) instead of on the stack so that extreme values like -D BUFFER_SIZE=10000000 do not cause a stack overflow.

Resources
References
man 2 read – system call behaviour, return values (bytes_read, 0 on EOF, -1 on error).

man 2 open / man 2 close – file descriptor management for testing.

man 3 malloc / man 3 free – dynamic heap memory allocation and deallocation.

42 Network Urduliz – Peer-to-peer learning.

Use of AI
In line with the project's AI guidelines, the core logic and implementation were developed by me through peer-to-peer learning. AI was used as a study aid to review edge cases, verify Norminette constraints, and structure this README.md. I have reviewed all parts of the project and can explain every line of code.
