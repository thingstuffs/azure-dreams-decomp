#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_801741D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s8 unk_20;
} S_801741D0_0;   /* node in func_801741D0 */

typedef struct S_801741D0_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_801741D0_1;   /* sub in func_801741D0 */

typedef struct S_801741D0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_801741D0_2;   /* pos in func_801741D0 */

typedef struct S_801741D0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801741D0_3;   /* arg1 in func_801741D0 */



typedef struct {
    u32 words[3];
} Packed12 __attribute__((packed));

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern void *memcpy(void *, const void *, u32);
extern u8 D_80045340[9];
extern u8 D_80174180[9];
extern u8 D_80174D08[12];

void func_801741D0(s32 arg0, S_801741D0_3 *arg1, s32 arg2, s8 arg3, s32 arg4)
{
    s32 saved_arg4 = arg4;
    register s8 saved_arg3 ASM_REG("$20") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *node;
    S_801741D0_1 *sub;
    S_801741D0_2 *pos;
    u8 *bytes;

    node = func_8003FC64(0x212);
    if (node != NULL) {
        ((S_801741D0_0 *)node)->unk_10 = D_80174180;
        func_8004491C(node, D_80045340);

        sub = ((S_801741D0_0 *)node)->unk_0C;
        sub->unk_10 = 0x60;
        sub->unk_14 |= 0xC;

        pos = ((S_801741D0_0 *)node)->unk_08;
        pos->unk_02 = arg1->unk_02;
        pos->unk_06 = arg1->unk_06;
        pos->unk_0A = arg1->unk_0A - 0x28;

        sub = ((S_801741D0_0 *)node)->unk_0C;
        sub->unk_1E = 0x400;
        sub->unk_1C = 0x400;
        sub->unk_06 = 6;
        bytes = (u8 *)node + 0x20;
        ((S_801741D0_0 *)node)->unk_20 = 0x70;
        bytes[1] = 0x10;
        bytes[2] = 0x10;
        ASM_KEEP(saved_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sub->unk_0D = saved_arg3;
        sub->unk_0C = saved_arg4;
        sub->unk_0E = saved_arg4;
        sub->unk_1A = rand() & 0xFFF;

        memcpy((u8 *)node + 0x48, D_80174D08, 12);
        sub->unk_08 = (u8 *)node + 0x48;
    }
}

/* MECHANISM: The 40-byte frame holds arg1/node/sub in s2/s1/s0 and byte args in s4/s3.
   CDK 2.7.2-G0 gives the retail memcpy temp colors and unaligned 12-byte copy sequence.
   ASM_KEEP(saved_arg3) at its last use schedules the prologue saves as s2, s4, then s3. */
