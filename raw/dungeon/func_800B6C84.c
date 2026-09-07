#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 D_80083160[];
extern s32 func_80045310(void *);
extern void func_800BC4D4(void *, void *, s16, s32);
extern s16 func_800BCB04(u16, u16, s16);

s32 func_800BC3E4(void *arg0) {
    void *node = arg0;
    s32 *state = D_80083160;
    volatile u16 *scratch = (volatile u16 *)0x1F800000;
    register void *previous ASM_REG("$4");

    scratch[0x80] = -((u16 *)state)[0x62];
    scratch[0x81] = -((u16 *)state)[0x63];
    scratch[0x82] = ((u16 *)state)[0x5C];

    for (;;) {
        void *object = FIELD(node, void *, 0);
        void *primitive = FIELD(object, void *, 0xC);

        if (!(FIELD(primitive, u16, 0x14) & 0x8000)) {
            void *coord = FIELD(object, void *, 8);
            s16 depth = func_800BCB04(FIELD(coord, u16, 2), FIELD(coord, u16, 6), FIELD(coord, s16, 0xA));
            func_800BC4D4(coord, primitive, depth, 0);
            if (func_80045310(FIELD(FIELD(state, void *, 0), void *, 0x8D0)) != 0) {
                break;
            }
        }
        previous = FIELD(node, void *, -8);
        node = (u8 *)previous + 0x20;
        if (previous == 0) {
            break;
        }
    }
    return 0;
}
