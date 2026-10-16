#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void appendTownMovieListNode();        /* extern */
extern u8 D_8006AE4C[];
extern u8 D_800717D0[];

/* Passes D_8006AE4C and the shared D_800717D0 context to appendTownMovieListNode. */
void func_8003B238(void) {
    appendTownMovieListNode(&D_800717D0, &D_8006AE4C);
}
