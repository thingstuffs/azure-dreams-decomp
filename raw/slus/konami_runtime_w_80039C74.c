#include "common.h"

#include "common.h"

typedef struct Func80039C74State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
} Func80039C74State;

extern s32 func_80033B2C(s32 arg0);

void func_80039C74(Func80039C74State *arg0) {
    u8 *initial = arg0->read_ptr;
    s32 value = initial[0] + (initial[1] << 8);

    arg0->read_ptr = initial + 2;
    if (func_80033B2C((s16)value) == 0) {
        u8 *ptr = arg0->read_ptr;

        arg0->read_ptr = (u8 *)(ptr[0] + (ptr[1] << 8) +
                                (ptr[2] << 16) + (ptr[3] << 24));
    } else {
        arg0->read_ptr += 4;
    }
}
