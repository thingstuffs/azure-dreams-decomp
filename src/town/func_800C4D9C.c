#include "common.h"

extern s32 func_80033B2C(s32 arg0);
extern void func_80033AA8(s32 arg0);
extern void func_80033AE8(s32 arg0);
extern s16 D_800D4770[];

void func_800C24FC(void) {
    s16 *current;
    register s16 *value ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    current = D_800D4770;
    if (*current != -1) {
        s32 sentinel = -1;
        value = current + 1;
        do {
            if (func_80033B2C(*current) != 0) {
                current += 2;
                func_80033AA8(*value);
            } else {
                current += 2;
                func_80033AE8(*value);
            }
        } while (value += 2, *current != sentinel);
    }
}
