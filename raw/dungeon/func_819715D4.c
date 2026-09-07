#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Sprite Sprite;
typedef struct Object Object;

struct Sprite {
    u8 pad0[12];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    u16 flags10;
    s16 angle;
    u16 flags14;
    u8 pad16[6];
    s16 scale_x;
    s16 scale_y;
};

struct Object {
    u8 pad0[8];
    u16 *dst;
    Sprite *sprite;
    u8 *callback;
    u8 pad14[0x44];
    s16 unk58;
    s16 unk5A;
};

M2C_UNK func_8003DB94();
Object *func_8003FC64();
M2C_UNK func_8004491C();
s32 rand();
extern u8 D_80024AB4[];
extern u8 D_80045340[];
extern u8 D_800DECF8[];

void func_819715D4(u16 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_v0_2;
    Sprite *temp_a0;
    Sprite *temp_a0_2;
    u16 *temp_s0;
    register Object *temp_v0 ASM_REG("$17");
    u8 *temp_v1;

    temp_v0 = func_8003FC64(0x212);
#ifdef NON_MATCHING
    ASM_KEEP(temp_v0);
#endif
    if (temp_v0 != NULL) {
        temp_v1 = (u8 *)temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0x38) = 0x14;
        M2C_FIELD(temp_v1, s16 *, 0x3A) = 0x14;
        temp_v0->callback = D_80024AB4;
        func_8004491C(temp_v0, D_80045340);
        temp_a0 = temp_v0->sprite;
        temp_a0->flags10 = 0x20;
        M2C_FIELD(temp_a0, s16 *, 6) = 0;
        temp_a0->flags14 |= 0xC;
        temp_s0 = temp_v0->dst;
        temp_s0[1] = arg3;
        temp_s0[3] = (u16)arg4;
        temp_s0[5] = (u16)arg5;
        ASM_KEEP(temp_s0);
        {
            register s32 x ASM_REG("$2");
            register s32 offset ASM_REG("$3") = arg0[62];
            ASM_KEEP(offset);
            x = arg3;
            ASM_KEEP(x);
            x += offset;
            temp_s0[1] = (u16)x;
        }
        {
            register s32 y ASM_REG("$2");
            register s32 offset ASM_REG("$3") = arg0[63];
            ASM_KEEP(offset);
            y = arg4;
            ASM_KEEP(y);
            y += offset;
            temp_s0[3] = (u16)y;
        }
        {
            register s32 z ASM_REG("$2");
            register s32 offset ASM_REG("$3") = arg0[64];
            ASM_KEEP(offset);
            z = arg5;
            ASM_KEEP(z);
            z += offset;
            temp_s0[5] = (u16)z;
        }
        temp_v0_2 = rand(temp_a0);
        {
            s32 value = temp_s0[1];
            value -= 7;
            value += temp_v0_2 & 0xF;
            temp_s0[1] = (u16)value;
        }
        temp_v0_2 = rand();
        {
            s32 value = temp_s0[3];
            value -= 7;
            value += temp_v0_2 & 0xF;
            temp_s0[3] = (u16)value;
        }
        temp_v0_2 = rand();
        M2C_FIELD(temp_s0, s32 *, 0x14) = 0x20000;
        {
            s32 value = temp_s0[5];
            value -= 7;
            value += temp_v0_2 & 0xF;
            temp_s0[5] = (u16)value;
        }
        temp_a0_2 = temp_v0->sprite;
        temp_a0_2->scale_y = 0x1000;
        temp_a0_2->scale_x = 0x1000;
        temp_a0_2->b = 0x80;
        temp_a0_2->g = 0x80;
        temp_a0_2->r = 0x80;
        temp_a0_2->angle = 0x7DCE;
        temp_a0_2->flags14 |= 0x100;
        func_8003DB94(temp_a0_2, D_800DECF8, 0);
    }
}

/* MECHANISM: A guarded s1 object-result pin makes arg0 fall naturally into s2,
   closing the 0x30 frame/save contract; byte-scaled +0x20 and scoped v0/v1 accumulators fill load delays.
   Split random-result accumulations keep each -7 as addiu, removing the shared-register +1-word drift. */
