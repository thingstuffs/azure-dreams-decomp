#include "common.h"

#ifdef NON_MATCHING
#define ASM_TAILSLOT_PIN(value) ((void)0)
#else
#endif

typedef struct Inner {
    u8 pad[1];
    u8 flag;
} Inner;

typedef struct DungeonState {
    u8 pad[0x4C];
    Inner *inner;
} DungeonState;

extern u8 D_800DD8E7[];
extern DungeonState *D_800E3D7C[];
extern void func_800A93F8(s32 value);

s32 func_800A9390(s16 index) {
    s32 value;
    s32 compare;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    value = D_800DD8E7[index];
    if (D_800E3D7C[0]->inner->flag != 0) {
        compare = value;
        ASM_KEEP(compare);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (compare == 0x32) {
            result = 0x33;
            ASM_TAILSLOT_PIN(result);
            func_800A93F8(value);
            return result;
        } else if (compare == 0x39) {
            result = 0x3A;
            ASM_TAILSLOT_PIN(result);
            func_800A93F8(value);
            return result;
        } else if (compare == 0x40) {
            result = 0x42;
            ASM_TAILSLOT_PIN(result);
            func_800A93F8(value);
            return result;
        }
    }
    return value;
}
