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

/* Advance the countdown and update entry and completion flags when it expires. */
void func_800C4E00(void *state)
{
    s32 countdown;
    s32 entry_index;
    register u32 addr_or_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    if (D_80083462 & 0x10) {
        countdown = ((S_800C4E00_0 *)state)->unk_08 - 1;
        ((S_800C4E00_0 *)state)->unk_08 = countdown;
        if ((countdown << 0x10) <= 0) {
            if (((S_800C4E00_0 *)state)->unk_0A == 1) {
                func_800997FC(&D_800E18C8);
                entry_index = ((S_800C4E00_0 *)state)->unk_0C;
                addr_or_flags = entry_index << 2;
                addr_or_flags += entry_index;
                addr_or_flags <<= 2;
                addr_or_flags += (u32)D_800E2970;
                ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                ((S_800C4E00_1 *)((void *)addr_or_flags))->unk_0C =
                    ((S_800C4E00_1 *)((void *)addr_or_flags))->unk_0C & 0xFFFD;
            }
            addr_or_flags = ((S_800C4E00_0_pre *)state)[-1].unk_00;
            addr_or_flags |= 0x8000;
            ((S_800C4E00_0_pre *)state)[-1].unk_00 = addr_or_flags;
            addr_or_flags = D_800814A0;
            addr_or_flags |= 0x8000;
            D_800814A0 = addr_or_flags;
        }
    }
}
