#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

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

void func_801741D0(s32 arg0, void *arg1, s32 arg2, s8 arg3, s32 arg4)
{
    register s32 saved_arg4 ASM_REG("$19") = arg4;
    register s8 saved_arg3 ASM_REG("$20") = arg3;
    void *node;
    void *sub;
    void *pos;
    u8 *bytes;

    node = func_8003FC64(0x212);
    if (node != NULL) {
        FIELD(node, void *, 0x10) = D_80174180;
        func_8004491C(node, D_80045340);

        sub = FIELD(node, void *, 0xC);
        FIELD(sub, s16, 0x10) = 0x60;
        FIELD(sub, u16, 0x14) |= 0xC;

        pos = FIELD(node, void *, 8);
        FIELD(pos, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(pos, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(pos, s16, 0xA) = FIELD(arg1, u16, 0xA) - 0x28;

        sub = FIELD(node, void *, 0xC);
        FIELD(sub, s16, 0x1E) = 0x400;
        FIELD(sub, s16, 0x1C) = 0x400;
        FIELD(sub, s16, 6) = 6;
        bytes = (u8 *)node + 0x20;
        FIELD(node, s8, 0x20) = 0x70;
        bytes[1] = 0x10;
        bytes[2] = 0x10;
        ASM_KEEP(saved_arg3);
        FIELD(sub, s8, 0xD) = saved_arg3;
        FIELD(sub, s8, 0xC) = saved_arg4;
        FIELD(sub, s8, 0xE) = saved_arg4;
        FIELD(sub, s16, 0x1A) = rand() & 0xFFF;

        memcpy((u8 *)node + 0x48, D_80174D08, 12);
        FIELD(sub, void *, 8) = (u8 *)node + 0x48;
    }
}

/* MECHANISM: The 40-byte frame holds arg1/node/sub in s2/s1/s0 and byte args in s4/s3.
   CDK 2.7.2-G0 gives the retail memcpy temp colors and unaligned 12-byte copy sequence.
   ASM_KEEP(saved_arg3) at its last use schedules the prologue saves as s2, s4, then s3. */
