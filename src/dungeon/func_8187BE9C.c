#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"

typedef struct S_8187BE9C_0_pre {
    u16 unk_00;
} S_8187BE9C_0_pre;   /* the 0x2 bytes before arg0 in func_8002569C, addressed as arg0[-1] */

typedef struct S_8187BE9C_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x30];
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 pad_39[0x9];
    s16 unk_42;
    u8 pad_44[0x8];
    u8 unk_4C;
} S_8187BE9C_0;   /* arg0 in func_8002569C */

typedef struct S_8187BE9C_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_8187BE9C_1;   /* arg2 in func_8002569C */


extern s16 D_8002694C[5];

/* Advance the effect fade, scale primitive colors, and flag completion. */
void func_8002569C(void *effect, s32 unused, S_8187BE9C_1 *primitive)
{
    s16 phase;

    D_8002694C[0] = 1;
    ((S_8187BE9C_0 *)effect)->unk_02.s--;

    phase = ((S_8187BE9C_0 *)effect)->unk_42;
    switch (phase) {
    case 0:
        ((S_8187BE9C_0 *)effect)->unk_42 = 1;
        ((S_8187BE9C_0 *)effect)->unk_4C += 24;
        break;
    case 1:
        ((S_8187BE9C_0 *)effect)->unk_42 = 0;
        ((S_8187BE9C_0 *)effect)->unk_4C -= 24;
        break;
    }

    primitive->unk_0C =
        ((S_8187BE9C_0 *)effect)->unk_36 * ((S_8187BE9C_0 *)effect)->unk_02.u /
        ((S_8187BE9C_0 *)effect)->unk_04;
    primitive->unk_0D =
        ((S_8187BE9C_0 *)effect)->unk_37 * ((S_8187BE9C_0 *)effect)->unk_02.u /
        ((S_8187BE9C_0 *)effect)->unk_04;
    primitive->unk_0E =
        ((S_8187BE9C_0 *)effect)->unk_38 * ((S_8187BE9C_0 *)effect)->unk_02.u /
        ((S_8187BE9C_0 *)effect)->unk_04;

    if (((S_8187BE9C_0 *)effect)->unk_02.u <= 0) {
        ((S_8187BE9C_0_pre *)effect)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }

    if (primitive->unk_14 & 0x8000) {
        ((S_8187BE9C_0_pre *)effect)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
