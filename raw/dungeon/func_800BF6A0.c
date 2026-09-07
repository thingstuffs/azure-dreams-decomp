#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800997FC(void *);
extern s32 D_800814A0;
extern u16 D_80083462;
extern s32 D_800E18C8;
extern s8 D_800E2970[];

void func_800C4E00(void *arg0)
{
    s32 temp_v0;
    register s32 index ASM_REG("$4");
    register u32 offset ASM_REG("$2");

    if (D_80083462 & 0x10) {
        temp_v0 = FIELD(arg0, u16, 8) - 1;
        FIELD(arg0, u16, 8) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            if (FIELD(arg0, s16, 0xA) == 1) {
                func_800997FC(&D_800E18C8);
                index = FIELD(arg0, s16, 0xC);
                offset = index << 2;
                offset += index;
                offset <<= 2;
                offset += (u32)D_800E2970;
                ASM_KEEP(index);
                ASM_KEEP(offset);
                FIELD((void *)offset, u16, 0xC) =
                    FIELD((void *)offset, u16, 0xC) & 0xFFFD;
            }
            offset = FIELD(arg0, u16, -2);
            offset |= 0x8000;
            FIELD(arg0, u16, -2) = offset;
            offset = D_800814A0;
            offset |= 0x8000;
            ASM_KEEP(offset);
            D_800814A0 = offset;
        }
    }
}

/* MECHANISM: A signed countdown removes the u16 re-extension, and direct global RMWs keep 45 words.
   Guarded $a0 index and $v0 scaled-address/tail reuse reproduce retail's runtime roles.
   With that structure fixed, the late orientation closes exactly at 2.7.2-cdk-G0. */
