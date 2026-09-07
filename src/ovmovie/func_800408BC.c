#include "common.h"

typedef struct {
    u8 pad00[0x10];
    u16 unk10;
    u16 unk12;
    u8 pad14[0x0C];
    s32 unk20;
    u16 unk24;
    u16 unk26;
    u8 pad28[0x04];
    s32 unk2C;
} MovieEntity;

void func_800408BC(MovieEntity *arg0) {
    volatile s32 sp0;
    s32 idx;
    u16 *p;
    s32 stride;

    sp0 = 0x800000;
    if (arg0->unk2C == 0) {
        do {
            sp0 = sp0 - 1;
            if (0 == sp0) {
                arg0->unk2C = 1;
                idx = arg0->unk20 == 0;
                arg0->unk20 = idx;
                p = (u16 *) ((s32) arg0 + (idx * 8) + 0x10);
                stride = 8;
                arg0->unk24 = *p;
                arg0->unk26 = *(u16 *) ((s32) arg0 + (arg0->unk20 * stride) + 0x12);
            }
        } while (arg0->unk2C == 0);
    }
    arg0->unk2C = 0;
}
