#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void appendTownMovieListNode();        /* extern */
extern u8 D_8006AE7C[];
extern u8 D_800717D0[];

/* Passes D_8006AE7C and the shared D_800717D0 context to appendTownMovieListNode. */
void func_8003B2F8(void) {
    appendTownMovieListNode(&D_800717D0, &D_8006AE7C);
}
