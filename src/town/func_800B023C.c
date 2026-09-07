#include "common.h"

typedef struct {
    s8 pad00[4];
    s32 unk04;
    s8 pad08[0x10];
    s32 unk18;
    s8 pad1C[4];
    u8 *unk20;
} UnkStruct800B023C;

extern s32 func_800AD968(void);
extern s32 func_800AD914(u8 *arg0);
extern s32 func_800ADA08(void);

s32 func_800AD99C(UnkStruct800B023C *arg0) {
    s32 temp_s0;

    if (arg0->unk18 == 0) {
        if ((u32) (arg0->unk20[(arg0->unk04 * 4) + 1] - 0x17) < 2U) {
            return 1;
        }
        temp_s0 = func_800AD968();
        temp_s0 += func_800AD914(arg0->unk20);
        __asm__ __volatile__("" ::: "memory");
        func_800ADA08();
        return temp_s0 < 20;
    }
    return 1;
}
