#include "common.h"

typedef struct S_800C4E00_0_pre {
    u16 unk_00;
} S_800C4E00_0_pre;   /* the 0x2 bytes before arg0 in func_800C4E00, addressed as arg0[-1] */

typedef struct S_800C4E00_0 {
    u8 pad_00[0x8];
    u16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_800C4E00_0;   /* arg0 in func_800C4E00 */

typedef struct S_800C4E00_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_800C4E00_1;   /* (void *)offset in func_800C4E00 */



extern void func_800997FC(void *);
extern s32 D_800814A0;
extern u16 D_80083462;
extern s32 D_800E18C8;
extern s8 D_800E2970[];

void func_800C4E00(void *arg0)
{
    s32 temp_v0;
    s32 index;
    register u32 offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    if (D_80083462 & 0x10) {
        temp_v0 = ((S_800C4E00_0 *)arg0)->unk_08 - 1;
        ((S_800C4E00_0 *)arg0)->unk_08 = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            if (((S_800C4E00_0 *)arg0)->unk_0A == 1) {
                func_800997FC(&D_800E18C8);
                index = ((S_800C4E00_0 *)arg0)->unk_0C;
                offset = index << 2;
                offset += index;
                offset <<= 2;
                offset += (u32)D_800E2970;
                ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                ((S_800C4E00_1 *)((void *)offset))->unk_0C =
                    ((S_800C4E00_1 *)((void *)offset))->unk_0C & 0xFFFD;
            }
            offset = ((S_800C4E00_0_pre *)arg0)[-1].unk_00;
            offset |= 0x8000;
            ((S_800C4E00_0_pre *)arg0)[-1].unk_00 = offset;
            offset = D_800814A0;
            offset |= 0x8000;
            D_800814A0 = offset;
        }
    }
}

/* MECHANISM: A signed countdown removes the u16 re-extension, and direct global RMWs keep 45 words.
   Guarded $a0 index and $v0 scaled-address/tail reuse reproduce retail's runtime roles.
   With that structure fixed, the late orientation closes exactly at 2.7.2-cdk-G0. */
