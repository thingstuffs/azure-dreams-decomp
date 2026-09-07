#include "common.h"

typedef void (*S_80083C68)(void);

extern S_80083C68 D_80083C68[];

/* Walks the null-terminated array of function pointers D_80083C68, invoking
   each entry in turn until a null (0) terminator entry is reached. */
void func_800411AC(void) {
    S_80083C68 *p = D_80083C68;

    if (*p != 0) {
        do {
            (*p)();
            p++;
        } while (*p != 0);
    }
}
