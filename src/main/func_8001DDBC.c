#include "common.h"

typedef struct {
    s32 v;
    s32 pad[2];
} D_8008DAB4_View; /* real D_8008DAB4 is >8B so hi/lo addressing is used */

void func_8001DDBC(void *arg0) {
    if (arg0 != 0) {
        u16 *p = (u16 *)((u8 *)arg0 + 0x1E);
        u16 v0 = *p;
        s32 v1;
        {
            extern s32 D_8008DAB4;
            v1 = D_8008DAB4;
        }
        v0 |= 0x8000;
        v1 |= 0x8000;
        *p = v0;
        {
            extern D_8008DAB4_View D_8008DAB4;
            D_8008DAB4.v = v1;
        }
    }
}
