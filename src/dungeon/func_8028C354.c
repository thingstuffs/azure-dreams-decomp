#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8001F354_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_8001F354_0;   /* temp_v0 in func_8001F354 */

typedef struct S_8001F354_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8001F354_1;   /* temp_a0 in func_8001F354 */



extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80044BB0[3];
extern s32 D_800A5AF0[3];

void func_8001F354(s16 arg0, s16 arg1, s32 arg2, s32 arg3)
{
    register s16 final_arg0 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 held_arg3 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u16 flags;
    S_8001F354_1 *temp_a0;
    void *temp_v0;
    s16 *temp_v1;
    s16 *temp_v1_2;

    held_arg3 = arg3;
    ASM_KEEP_NV(held_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_v0 = func_8003FC64(2);
    if (temp_v0 != NULL) {
        final_arg0 = arg0;
        ASM_KEEP(final_arg0);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ((S_8001F354_0 *)temp_v0)->unk_10 = (s32)D_800A5AF0;
        func_8004491C(temp_v0, D_80044BB0);
        temp_v1 = (s16 *)((S_8001F354_0 *)temp_v0)->unk_08;
        temp_v1[1] = arg0 + 0x280;
        temp_v1[3] = arg1;
        temp_v1[5] = 1;
        temp_a0 = ((S_8001F354_0 *)temp_v0)->unk_0C;
        temp_a0->unk_1C = 0x2000;
        temp_a0->unk_1E = 0x1000;
        temp_a0->unk_08 = held_arg3;
        if ((arg2 << 0x10) != 0) {
            temp_a0->unk_0C = 0x202080;
        } else {
            temp_a0->unk_0C = 0x808080;
        }
        flags = temp_a0->unk_14;
        temp_a0->unk_10 = 0x20;
        temp_v1_2 = (s16 *)(temp_v0 + 0x20);
        temp_a0->unk_14 = flags | 0xC;
        temp_v1_2[3] = 0x18;
        temp_v1_2[4] = final_arg0;
    }
}
