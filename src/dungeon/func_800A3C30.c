#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

typedef struct Inner {
    u8 pad[1];
    u8 flag;
} Inner;

extern u8 D_800DD8E7[];

s32 func_800A9390(s16 index) {
    s32 compare;

    index = D_800DD8E7[index];
    if (((Inner *)D_800E3D7C->unk_4C)->flag != 0) {
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
