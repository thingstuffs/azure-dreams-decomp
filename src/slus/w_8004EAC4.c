#include "common.h"

/* Writes a 2-char code into a slot at arg0+arg2*2 via strncpy(arg1,2), first calling func_8004E9EC(arg0,arg2) to check/prepare the slot; null-terminates the slot if that call signaled it was needed. Returns pointer to the slot. */
extern s32 func_8004E9EC(u8 *arg0, s32 arg1);
extern char *strncpy(char *dest, const char *src, u32 n);

char *func_8004EAC4(u8 *arg0, char *arg1, s32 arg2) {
    s32 flag;
    char *dest;

    flag = func_8004E9EC(arg0, arg2);
    dest = (char *)(arg0 + arg2 * 2);
    strncpy(dest, arg1, 2);
    if (flag != 0) {
        dest[2] = 0;
    }
    return dest;
}
