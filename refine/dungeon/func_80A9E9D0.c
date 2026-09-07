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

/* Creates a tinted sprite at the source position with a height offset and random rotation. */
void func_801741D0(s32 unused_0, S_801741D0_3 *source_pos, s32 unused_2, s8 green, s32 red_blue)
{
    s32 saved_red_blue = red_blue;
    register s8 saved_green ASM_REG("$20") = green;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *node;
    S_801741D0_1 *sprite;
    S_801741D0_2 *position;
    u8 *node_params;

    node = func_8003FC64(0x212);
    if (node != NULL) {
        ((S_801741D0_0 *)node)->unk_10 = D_80174180;
        func_8004491C(node, D_80045340);

        sprite = ((S_801741D0_0 *)node)->unk_0C;
        sprite->unk_10 = 0x60;
        sprite->unk_14 |= 0xC;

        position = ((S_801741D0_0 *)node)->unk_08;
        position->unk_02 = source_pos->unk_02;
        position->unk_06 = source_pos->unk_06;
        position->unk_0A = source_pos->unk_0A - 0x28;

        sprite = ((S_801741D0_0 *)node)->unk_0C;
        sprite->unk_1E = 0x400;
        sprite->unk_1C = 0x400;
        sprite->unk_06 = 6;
        node_params = (u8 *)node + 0x20;
        ((S_801741D0_0 *)node)->unk_20 = 0x70;
        node_params[1] = 0x10;
        node_params[2] = 0x10;
        ASM_KEEP(saved_green);   /* MATCH pin: retail schedule: same instructions, different order without it */
        sprite->unk_0D = saved_green;
        sprite->unk_0C = saved_red_blue;
        sprite->unk_0E = saved_red_blue;
        sprite->unk_1A = rand() & 0xFFF;

        memcpy((u8 *)node + 0x48, D_80174D08, 12);
        sprite->unk_08 = (u8 *)node + 0x48;
    }
}

/* MECHANISM: The 40-byte frame holds source_pos/node/sprite in s2/s1/s0 and byte args in s4/s3.
   CDK 2.7.2-G0 gives the retail memcpy temp colors and unaligned 12-byte copy sequence.
   ASM_KEEP(saved_green) at its last use schedules the prologue saves as s2, s4, then s3. */
