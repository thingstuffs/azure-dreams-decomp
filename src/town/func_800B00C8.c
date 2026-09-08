#include "common.h"

extern s32 func_8004A618(u8 *);
extern s32 func_8004A638(u8 *);
extern void func_800AD894(void) __attribute__((noreturn));

s32 func_800AD828(u8 *arg0, s32 arg1) {
    register s32 acc ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *orig ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *p;

    orig = arg0;
    acc = 0;
    if (arg0[1] != 0) {
        p = orig + 1;
        do {
            if (p[2] & 0x20) {
                if (arg1 == 0) {
                    acc += func_8004A638(arg0);
                    ASM_TAILSLOT_PIN(acc);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                    func_800AD894();
                }
                acc += func_8004A618(arg0);
            }
            p += 4;
            arg0 += 4;
        } while (*p != 0);
    }
    return acc;
}
