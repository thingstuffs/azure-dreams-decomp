#include "common.h"
#include "m2c_compat.h"

struct S_81984D4C_local {
    /* 0x00 */ char pad0[0x94];
    /* 0x94 */ u16 unk94;                           /* inferred */
    /* 0x96 */ u16 unk96;                           /* inferred */
    /* 0x98 */ s16 unk98;                           /* inferred */
    /* 0x9A */ char pad9A[0xA];                     /* maybe part of unk98[6]? */
    /* 0xA4 */ s16 unkA4;                           /* inferred */
    /* 0xA6 */ s16 unkA6;                           /* inferred */
    /* 0xA8 */ s16 unkA8;                           /* inferred */
    /* 0xAA */ char padAA[0xA];                     /* maybe part of unkA8[6]? */
    /* 0xB4 */ void (*callback)();
    /* 0xB8 */ void *field_B8;
    /* 0xBC */ char padBC[0x1C];                    /* maybe part of field_B8[8]? */
    /* 0xD8 */ void *ptr;
};                                                  /* size = 0xDC */

extern u8 D_80026BE4[16];
extern u8 D_800E3D20[16];


typedef struct S_81984D4C_0 {
    u8 pad_00[0x94];
    u16 unk_94;
    u16 unk_96;
    union { u16 u; s16 s; } unk_98;   /* accessed as both */
    u8 pad_9A[0xA];
    union { u16 u; s16 s; } unk_A4;   /* accessed as both */
    union { u16 u; s16 s; } unk_A6;   /* accessed as both */
    union { u16 u; s16 s; } unk_A8;   /* accessed as both */
} S_81984D4C_0;   /* state in func_81984D4C */

typedef struct S_81984D4C_1 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_81984D4C_1;   /* timer in func_81984D4C */

typedef struct S_81984D4C_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81984D4C_2;   /* temp_v1 in func_81984D4C */

typedef struct S_81984D4C_3 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} S_81984D4C_3;   /* flag in func_81984D4C */

typedef struct S_81984D4C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_81984D4C_4;   /* (*(void **)((u8 *)arg0 + 0xC)) in func_81984D4C */

void func_81984D4C(void *arg0) {
    s16 temp_a0;
    s16 temp_v0;
    S_81984D4C_2 *temp_v1;
    u8 *state;
    u8 *timer;
    u8 *flag;

    temp_a0 = (*(s16 *)((u8 *)arg0 + 0x24));
    state = (u8 *)&D_80083178;
    if (temp_a0 > 0) {
        ((S_81984D4C_0 *)state)->unk_98.u = (u16) ((S_81984D4C_0 *)state)->unk_98.u + ((s32) ((*(s16 *)((u8 *)arg0 + 0x26)) - ((S_81984D4C_0 *)state)->unk_98.s) / temp_a0);
    }
    temp_v0 = (u16) (*(s16 *)((u8 *)arg0 + 0x24)) - 1;
    (*(s16 *)((u8 *)arg0 + 0x24)) = temp_v0;
    if (temp_v0 < -0x80) {
        (*(s16 *)((u8 *)arg0 + 0x24)) = -0x80;
    }
    timer = D_800E3D20;
    if (((S_81984D4C_1 *)timer)->unk_00.u != 0) {
        ((S_81984D4C_1 *)timer)->unk_00.s = (s8) (((S_81984D4C_1 *)timer)->unk_00.u - 1);
    }
    temp_v1 = (*(void * volatile *)((u8 *)arg0 + 0xC));
    (*(u16 *)((u8 *)arg0 + 4)) = (u16) ((S_81984D4C_4 *)((*(void **)((u8 *)arg0 + 0xC))))->unk_02;
    (*(u16 *)((u8 *)arg0 + 6)) = (u16) temp_v1->unk_06;
    (*(u16 *)((u8 *)arg0 + 8)) = (u16) temp_v1->unk_0A;
    ((S_81984D4C_0 *)state)->unk_A4.u = (u16) ((S_81984D4C_0 *)state)->unk_A4.u + ((s32) ((s16) (*(u16 *)((u8 *)arg0 + 4)) - ((S_81984D4C_0 *)state)->unk_A4.s) >> 2);
    ((S_81984D4C_0 *)state)->unk_A6.u = (u16) ((S_81984D4C_0 *)state)->unk_A6.u + ((s32) ((s16) (*(u16 *)((u8 *)arg0 + 6)) - ((S_81984D4C_0 *)state)->unk_A6.s) >> 2);
    flag = D_80026BE4;
    if (((S_81984D4C_3 *)flag)->unk_00.u != 0) {
        ((S_81984D4C_0 *)state)->unk_A8.u = (u16) ((S_81984D4C_0 *)state)->unk_A8.u + ((s32) ((s16) (*(u16 *)((u8 *)arg0 + 8)) - ((S_81984D4C_0 *)state)->unk_A8.s) >> 2);
    }
    ((S_81984D4C_3 *)flag)->unk_00.s = (s8) (((S_81984D4C_0 *)state)->unk_A8.s != (s16) (*(u16 *)((u8 *)arg0 + 8)));
    ((S_81984D4C_0 *)state)->unk_94 = (u16) ((s32) (((S_81984D4C_0 *)state)->unk_94 << 0x10) >> 0x12);
    ((S_81984D4C_0 *)state)->unk_96 = (u16) ((s32) (((S_81984D4C_0 *)state)->unk_96 << 0x10) >> 0x12);
}

/* MECHANISM: Frameless leaf; arg0 stays in a1 and D_80083178 in a2 across the CFG.
   A volatile cached read of arg0+0xC prevents CSE with the direct first-use load,
   producing retail's paired lw v0/v1 and keeping v1 live for offsets 6/0xA. */
