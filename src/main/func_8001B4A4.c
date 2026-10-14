#include "common.h"

s32 func_800484A4(s32, s32 *);

extern s32 D_8008DAB4;

/* Updates the object's indirect value and sets the object and global 0x8000 flags. */
void func_8001B4A4(void *object) {

    if (object != 0) {
        **(s32 ***)(object + 0x20) = func_800484A4(*(s32 *)(object + 0x24) + 6, *(s32 *)(object + 0x20));
        {
            u16 of = *(u16 *)(object + 0x1E);
            s32 gf = D_8008DAB4;

            *(u16 *)(object + 0x1E) = of | 0x8000;
            D_8008DAB4 = gf | 0x8000;
        }
    }
}
