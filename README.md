# get-next-line

*This project has been created as part of the 42 curriculum by aabi-mou.*

## Description

This project implements a function in C that reads a line from a file descriptor. Repeated calls to this function allow reading the text file pointed to by the file descriptor, one line at a time.

The function returns the line including the terminating newline character (if present), or `NULL` when the end of file is reached or an error occurs. It uses a static variable to preserve leftover data between function calls, enabling efficient line-by-line reading with configurable buffer sizes.

## Instructions

### Installation

```bash
git clone https://github.com/abimoussagnes/get-next-line.git
cd get-next-line
```

### Compilation

Compile with your source files and define `BUFFER_SIZE`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c get_next_line_test.c -o program
```

### Testing

The project includes a test program in `get_next_line_test.c` that demonstrates basic usage. To run your own tests:

1. **Modify the test file** (optional):
   - Edit `get_next_line_test.c` to test different scenarios
   - Change the input file path or buffer size as needed

2. **Compile and run**:
   ```bash
   cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c get_next_line_test.c -o gnl_test
   ./gnl_test
   ```

3. **Test with valgrind** (optional, for memory leak detection):
   ```bash
   valgrind --leak-check=yes ./gnl_test
   ```

## Explanation

### Main Function

```c
char *get_next_line(int fd);
```

The core function that reads and returns the next line from the file descriptor. It manages leftover data in a static variable and handles end-of-file scenarios gracefully.

**Parameters:**
- `fd`: File descriptor to read from

**Returns:**
- Pointer to the line read (including `\n` if present)
- `NULL` on EOF or error

### Helper Functions

#### `read_until_newline`
```c
char *read_until_newline(int fd, char *stash)
```
Reads data in chunks of `BUFFER_SIZE` from the file descriptor until a newline character is encountered or EOF is reached. Accumulates data in the stash and handles read errors by returning `NULL`.

#### `extract_line`
```c
char *extract_line(char *stash)
```
Extracts and returns a complete line from the stash (up to and including the newline character). Returns `NULL` if the stash is empty.

#### `update_stash`
```c
char *update_stash(char *stash)
```
Removes the line that was just extracted from the stash and preserves any remaining data for the next call. Frees the old stash and returns the updated version.

### Utility Functions (in get_next_line_utils.c)

- `ft_strlen`: Calculate string length
- `ft_strchr`: Locate character in string
- `ft_strjoin`: Concatenate two strings
- `ft_strdup`: Duplicate a string
- `ft_substr`: Extract substring

## Resources

- [Linux Manual Pages - read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux Manual Pages - open(2)](https://man7.org/linux/man-pages/man2/open.2.html)
- [Static Variables in C](https://en.cppreference.com/w/c/language/storage_duration)