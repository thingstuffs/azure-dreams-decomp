#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

typedef struct EffectBase {
    u8 pad0[8];
    s32 field8;
    u8 padC[8];
    u16 field14;
    u8 pad16[0x1C];
    s16 field32;
    s16 field34;
} EffectBase;

typedef struct Effect {
    u8 pad0[0x20];
    EffectBase base;
} Effect;

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern s32 D_800D68F4[];
extern s32 D_800D707C[];
extern s16 D_800E2468[];

void func_80D659DC(void *arg0, u32 arg1, s32 arg2) {
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_a2;
    void *temp_s0;
    EffectBase *temp_s0_2;
    Effect *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        temp_s0_2 = &temp_v0->base;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800D707C;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 2) = (u16)
            M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 6) = (u16)
            M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16)
            (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) - 0x58);
        temp_s0 = (void *)D_800E2468 + ((arg1 >> 7) & 0x1C);
        temp_a0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0, u16 *, 2) = (u16)
            (M2C_FIELD(temp_a0, u16 *, 2) +
             (M2C_FIELD(temp_s0, s16 *, 0) * 0x12));
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0_2, u16 *, 6) = (u16)
            (M2C_FIELD(temp_a0_2, u16 *, 6) +
             (M2C_FIELD(temp_s0, s16 *, 2) * 0x12));
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x10) = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        temp_a1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a1, s32 *, 0xC) = (s32)
            (M2C_FIELD(temp_a1, s32 *, 0xC) +
             (M2C_FIELD(temp_s0, s16 *, 0) * 0x1C0000));
        {
            s32 temp_v1 = M2C_FIELD(temp_s0, s16 *, 2);

            temp_a2 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_a2, s32 *, 0x10) = (s32)
                (M2C_FIELD(temp_a2, s32 *, 0x10) +
                 (temp_v1 * 0x1C0000));
            temp_s0_2->field14 = arg1;
            temp_s0_2->field32 = 0xC;
            temp_s0_2->field34 = 0xC;
            func_8004491C(temp_v0, &D_800D68F4, temp_a2);
            M2C_FIELD(temp_v0, s32 *, 0x20) = arg2;
            temp_s0_2->field8 = arg2;
        }
    }
}
