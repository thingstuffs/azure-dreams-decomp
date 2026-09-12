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
    s16 compare;
    s32 result;

    value = D_800DD8E7[index];
    if (D_800E3D7C[0]->inner->flag != 0) {
        compare = value;
        if (compare == 0x32) {
            result = 0x33;
            func_800A93F8(value);
            return result;
        } else if (compare == 0x39) {
            result = 0x3A;
            func_800A93F8(value);
            return result;
        } else if (compare == 0x40) {
            result = 0x42;
            func_800A93F8(value);
            return result;
        }
    }
    return value;
}
