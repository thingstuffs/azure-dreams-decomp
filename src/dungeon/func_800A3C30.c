#include "common.h"

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

s32 func_800A9390(s16 index) {
    s32 compare;

    index = D_800DD8E7[index];
    if (D_800E3D7C[0]->inner->flag != 0) {
        compare = index;
        if (compare == 0x32) {
            return 0x33;
        }
        if (compare == 0x39) {
            return 0x3A;
        }
        if (compare == 0x40) {
            return 0x42;
        }
    }
    return index;
}
