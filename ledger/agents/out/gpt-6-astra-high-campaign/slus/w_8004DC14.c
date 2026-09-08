#include "common.h"

/* Already-matched callees (reuse their real signature where it doesn't
   conflict with how THIS call site uses the return value / passes args). */
extern void *func_8004B404(s32 a0, s32 a1, s32 a2, s32 a3); /* code7.c's own
    decl is `void func_8004B404(...)`, but its body ends in a tail call to the
    still-unmatched func_8004B364, whose return value passes through in $v0;
    this caller relies on that passthrough, so it's declared returning a
    pointer here. Argument shape (4 ints) is identical. */
extern s32 func_8004B4DC(void *a0);
extern void func_8004B1A4(void *a0);

/* Not yet matched elsewhere -- inventing a prototype that matches this call
   site's register setup only (a0=obj, a1=format string, a2=arg value). */
extern s32 func_8004DA74(void *a0, char *a1, s32 a2);

extern int puts(const char *s);

/* Allocates a 0x100-byte note buffer, decodes text, and frees the buffer if decoding produces no entries. */
void *allocObject100(char *text, s32 initial_octave, s32 alloc_arg2, s32 alloc_arg3)
{
    void *entries;

    entries = func_8004B404(0x100, initial_octave, alloc_arg2, alloc_arg3);
    if (entries != 0) {
        if (func_8004DA74(entries, text, initial_octave) != 0) {
            if (func_8004B4DC(entries) < 0x16) {
                return entries;
            }
            puts(text);
            return entries;
        }
        func_8004B1A4(entries);
        entries = 0;
    }

    return entries;
}
