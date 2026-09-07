#include "common.h"
typedef s32 M2C_UNK;

typedef struct S_81977E0C_0_pre {
    u16 unk_00;
} S_81977E0C_0_pre;   /* the 0x2 bytes before arg0 in func_81977E0C, addressed as arg0[-1] */

typedef struct S_81977E0C_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} S_81977E0C_0;   /* arg0 in func_81977E0C */

typedef struct S_81977E0C_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81977E0C_1;   /* arg2 in func_81977E0C */

typedef struct S_81977E0C_2 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_81977E0C_2;   /* arg1 in func_81977E0C */

typedef struct S_81977E0C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_81977E0C_3;   /* D_80026208 in func_81977E0C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_8002579C(void) __attribute__((noreturn));
extern void func_800478B8(void *);
s32 func_800644B8();
s32 func_80064584();
s32 rand();
extern s32 *D_80026208;
extern s32 D_800814A0;

/* Expand and fade a spiraling effect while updating its position. */
void func_81977E0C(void *effect, void *position, void *sprite) {
    u16 height_offset;
    u16 age;
    u16 scale;
    u8 brightness;

    age = ((S_81977E0C_0 *)effect)->unk_04 + 1;
    ((S_81977E0C_0 *)effect)->unk_04 = age;
    if ((s16) age >= 0xA) {
        brightness = ((S_81977E0C_1 *)sprite)->unk_0E - 0x10;
        ((S_81977E0C_1 *)sprite)->unk_0E = brightness;
        ((S_81977E0C_1 *)sprite)->unk_0D = brightness;
        ((S_81977E0C_1 *)sprite)->unk_0C = brightness;
    }
    ((S_81977E0C_0 *)effect)->unk_08 = (u16) (((S_81977E0C_0 *)effect)->unk_08 + 0x100);
    ((S_81977E0C_0 *)effect)->unk_06 = (u16) (((S_81977E0C_0 *)effect)->unk_06 + 1);
    height_offset = (u16) (((S_81977E0C_0 *)effect)->unk_0A - 8) - (rand() % 9);
    ((S_81977E0C_0 *)effect)->unk_0A = height_offset;
    if ((u16) ((S_81977E0C_1 *)sprite)->unk_1C < 0x400U) {
        scale = ((S_81977E0C_1 *)sprite)->unk_1E + 0x40;
        ((S_81977E0C_1 *)sprite)->unk_1E = scale;
        ((S_81977E0C_1 *)sprite)->unk_1C = scale;
    }
    func_800478B8(sprite);
    if (((S_81977E0C_1 *)sprite)->unk_14 & 0x6000) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_81977E0C_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
        func_8002579C();
        return;
    }
    ((S_81977E0C_2 *)position)->unk_00 = (s32) (*D_80026208 + (((func_800644B8((s16) ((S_81977E0C_0 *)effect)->unk_08) >> 4) * (s16) ((S_81977E0C_0 *)effect)->unk_06) << 8));
    ((S_81977E0C_2 *)position)->unk_04 = (s32) (D_80026208[1] + (((func_80064584((s16) ((S_81977E0C_0 *)effect)->unk_08) >> 4) * (s16) ((S_81977E0C_0 *)effect)->unk_06) << 8));
    ((S_81977E0C_2 *)position)->unk_0A = (s16) (((S_81977E0C_3 *)D_80026208)->unk_0A + ((S_81977E0C_0 *)effect)->unk_0A);
}
