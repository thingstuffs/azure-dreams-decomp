#include "common.h"

/* Returns 1 if the NUL-terminated string contains a byte other than
 * space (0x20) or newline (0x0A) before its terminator, else 0. */
extern int string_has_non_whitespace(char *a0);

/* Pool allocator: matched (gcc 2.8.1, src/code7.c) as
 * `void create_callback_pair_default(int a0,int a1,int a2,int a3)` (forwards (0,0,a0,a3) to
 * create_callback_pair_payload). Declared here via a K&R (unspecified-args) prototype so the
 * call sets ONLY $a0=0x100 (matching the target, which never touches
 * a1-a3), and its real return value ($v0, forwarded from the inner call
 * despite the other TU's `void` signature) is captured here as a pointer. */
extern void *create_callback_pair_default();

/* Parses/tokenizes string a1 into buffer a0, using a2 as an auxiliary
 * argument (still unmatched, INCLUDE_ASM'd in code.c). */
extern void build_positioned_text_glyphs(void *a0, char *a1, int a2);

/* Parses nonblank text into a new 0x100-byte buffer, returning NULL if blank or allocation fails. */
void *alloc_parsed_string(char *text, int parse_arg)
{
    void *buffer = 0;

    if (string_has_non_whitespace(text) != 0) {
        buffer = create_callback_pair_default(0x100);
        if (buffer != 0)
            build_positioned_text_glyphs(buffer, text, parse_arg);
    }

    return buffer;
}
