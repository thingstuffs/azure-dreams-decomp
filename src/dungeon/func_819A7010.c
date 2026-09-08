#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024810_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80024810_2;   /* temp_v1 in func_80024810 */

typedef struct S_80024810_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024810_3;   /* ((S_80024810_2 *)temp_v1)->unk_08 in func_80024810 */


typedef struct S_80024810_0_pre {
    u16 unk_00;
} S_80024810_0_pre;   /* the 0x2 bytes before arg0 in func_80024810, addressed as arg0[-1] */

typedef struct S_80024810_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x1A];
    u16 unk_24;
    u16 unk_26;
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x4];
    s32 unk_34;
    u8 pad_38[0x4];
    s16 unk_3C;
    u16 unk_3E;
} S_80024810_0;   /* arg0 in func_80024810 */

typedef struct S_80024810_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_80024810_1;   /* temp_a0 in func_80024810 */


/* micro-lane E 2026-08-14: true base 0x80024810 (delta 0x7E65D800) */
extern s16 D_80083780[];
extern s32 D_80082E80[];
extern s32 D_800814A0[3];
s32 func_8003DE58();       /* extern */
s32 rand();                                /* extern */

/* Update the effect's jittered points between endpoints and advance its animation. */
void func_80024810(void *effect) {
    u16 coord_delta[3];
    s32 phase;
    s32 point_index;

    S_80024810_1 *owner;
    S_80024810_2 *target;

    owner = ((S_80024810_0 *)effect)->unk_00;
    target = (void *) (((S_80024810_0 *)effect)->unk_34 - 0x20);
    owner->unk_52 = (u16) (owner->unk_52 | 0x8000);
    ((S_80024810_0 *)effect)->unk_24 = (u16) ((S_80024810_3 *)(target->unk_08))->unk_02;
    ((S_80024810_0 *)effect)->unk_26 = (u16) ((S_80024810_3 *)(target->unk_08))->unk_06;
    ((S_80024810_0 *)effect)->unk_28 = (s16) (((S_80024810_3 *)(target->unk_08))->unk_0A - 0x20);
    ((S_80024810_0 *)effect)->unk_04 = (u16) D_80083780[1];
    ((S_80024810_0 *)effect)->unk_06 = (u16) D_80083780[3];
    ((S_80024810_0 *)effect)->unk_08 = (u16) D_80083780[5];
    if (func_8003DE58(D_80082E80[2], D_80082E80, coord_delta, 0) != 0) {
        ((S_80024810_0 *)effect)->unk_04 = (u16) (((S_80024810_0 *)effect)->unk_04 + coord_delta[0]);
        ((S_80024810_0 *)effect)->unk_06 = (u16) (((S_80024810_0 *)effect)->unk_06 + coord_delta[1]);
        ((S_80024810_0 *)effect)->unk_08 = (u16) (((S_80024810_0 *)effect)->unk_08 + coord_delta[2]);
    }
    coord_delta[0] = (u16) ((s32) ((s16) ((S_80024810_0 *)effect)->unk_24 - (s16) ((S_80024810_0 *)effect)->unk_04) >> 2);
    point_index = 1;
    coord_delta[1] = (u16) ((s32) ((s16) ((S_80024810_0 *)effect)->unk_26 - (s16) ((S_80024810_0 *)effect)->unk_06) >> 2);
    coord_delta[2] = (u16) ((s32) (((S_80024810_0 *)effect)->unk_28 - (s16) ((S_80024810_0 *)effect)->unk_08) >> 2);
    do {
        (*(s16 *)((u8 *)effect + (point_index * 8) + 4)) = (s16) ((((S_80024810_0 *)effect)->unk_04 + ((s16) coord_delta[0] * point_index) + (rand() & 0x3F)) - 0x20);
        (*(s16 *)((u8 *)effect + (point_index * 8) + 6)) = (s16) ((((S_80024810_0 *)effect)->unk_06 + ((s16) coord_delta[1] * point_index) + (rand() & 0x3F)) - 0x20);
        (*(s16 *)((u8 *)effect + (point_index * 8) + 8)) = (s16) ((((S_80024810_0 *)effect)->unk_08 + ((s16) coord_delta[2] * point_index)) - (rand() & 0x3F));
        point_index += 1;
    } while (point_index < 4);
    ((S_80024810_0 *)effect)->unk_2C = (s16) (((((S_80024810_0 *)effect)->unk_3E & 3) << 5) + 0x80);
    ((S_80024810_0 *)effect)->unk_2E = (s16) (((s32) (((S_80024810_0 *)effect)->unk_3E << 0x10) >> 0x12) << 5);
    phase = ((S_80024810_0 *)effect)->unk_3C;
    switch (phase) {
    case 0:
        ((S_80024810_0 *)effect)->unk_24 = (u16) (((S_80024810_0 *)effect)->unk_04 + ((s32) ((s16) ((S_80024810_0 *)effect)->unk_24 - (s16) ((S_80024810_0 *)effect)->unk_04) >> 1));
        ((S_80024810_0 *)effect)->unk_26 = (u16) (((S_80024810_0 *)effect)->unk_06 + ((s32) ((s16) ((S_80024810_0 *)effect)->unk_26 - (s16) ((S_80024810_0 *)effect)->unk_06) >> 1));
        ((S_80024810_0 *)effect)->unk_28 = (s16) (((S_80024810_0 *)effect)->unk_08 + ((s32) (((S_80024810_0 *)effect)->unk_28 - (s16) ((S_80024810_0 *)effect)->unk_08) >> 1));
        ((S_80024810_0 *)effect)->unk_3C = (s16) ((u16) ((S_80024810_0 *)effect)->unk_3C + 1);
        /* fallthrough */
    case 1:
        if ((s16) ((S_80024810_0 *)effect)->unk_3E >= 6) {
            ((S_80024810_0 *)effect)->unk_3E = 2U;
            ((S_80024810_0 *)effect)->unk_3C = (s16) ((u16) ((S_80024810_0 *)effect)->unk_3C + 1);
        }
        break;
    case 2:
        if ((s16) ((S_80024810_0 *)effect)->unk_3E >= 8) {
            ((S_80024810_0_pre *)effect)[-1].unk_00 = (u16) (((S_80024810_0_pre *)effect)[-1].unk_00 | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
        break;
    }
    ((S_80024810_0 *)effect)->unk_3E = (u16) (((S_80024810_0 *)effect)->unk_3E + 1);
}
