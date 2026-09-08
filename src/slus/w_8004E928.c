#include "common.h"

/* Returns 1 if the NUL-terminated string contains a byte other than
 * space (0x20) or newline (0x0A) before its terminator, else 0. */
extern int func_8004E8D8(char *a0);

/* Pool allocator: matched (gcc 2.8.1, src/code7.c) as
 * `void func_8004B404(int a0,int a1,int a2,int a3)` (forwards (0,0,a0,a3) to
 * func_8004B364). Declared here via a K&R (unspecified-args) prototype so the
 * call sets ONLY $a0=0x100 (matching the target, which never touches
 * a1-a3), and its real return value ($v0, forwarded from the inner call
 * despite the other TU's `void` signature) is captured here as a pointer. */
extern void *func_8004B404();

/* Parses/tokenizes string a1 into buffer a0, using a2 as an auxiliary
 * argument (still unmatched, INCLUDE_ASM'd in code.c). */
extern void func_8004E298(void *a0, char *a1, int a2);

/* Parses nonblank text into a new 0x100-byte buffer, returning NULL if blank or allocation fails. */
void *allocParsedString(char *text, int parse_arg)
{
    void *buffer = 0;

    if (func_8004E8D8(text) != 0) {
        buffer = func_8004B404(0x100);
        if (buffer != 0)
            func_8004E298(buffer, text, parse_arg);
    }

    return buffer;
}
