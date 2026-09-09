#include "common.h"

extern s32 func_8009CFE0(void *, void *);
extern void func_8008F134(void *arg0);
extern void func_80033D08(void *arg0);
extern s32 D_800814A0;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

/* On a successful object check, clear its linked byte and set object and global flags. */
void func_800BB508(void *object, void *context) {
    if (func_8009CFE0(object, context) != 0) {
        func_8008F134(object);
        if (FIELD(object, s8 **, 0x98) != 0) {
            *FIELD(object, s8 **, 0x98) = 0;
        }
        func_80033D08(object);
        FIELD(object, u16 *, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
