#include "common.h"

typedef struct S_8008D470_0_pre {
    u16 unk_00;
} S_8008D470_0_pre;   /* the 0x2 bytes before arg0 in func_8008D470, addressed as arg0[-1] */

typedef struct S_8008D470_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    s32 unk_9C;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    union { u16 s; s16 u; } unk_A4;   /* accessed as both */
    u8 pad_A6[0x2];
    union { u16 s; s16 u; } unk_A8;   /* accessed as both */
    s16 unk_AA;
    s16 unk_AC;
    s16 unk_AE;
    u8 pad_B0[0x4];
    union { s16 s; u16 u; } unk_B4;   /* accessed as both */
} S_8008D470_0;   /* arg0 in func_8008D470 */

typedef struct S_8008D470_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    u32 unk_1C;
    u8 pad_20[0x104];
    void * unk_124;
} S_8008D470_1;   /* target in func_8008D470 */

typedef struct S_8008D470_2 {
    u8 pad_00[0x124];
    void * unk_124;
} S_8008D470_2;   /* D_800E3D7C[0] in func_8008D470 */

typedef struct S_8008D470_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
} S_8008D470_3;   /* arg2 in func_8008D470 */

typedef struct S_8008D470_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8008D470_4;   /* arg1 in func_8008D470 */

typedef struct S_8008D470_5 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x7C];
    void * unk_9C;
} S_8008D470_5;   /* entity in func_8008D470 */

typedef struct S_8008D470_6 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8008D470_6;   /* ((S_8008D470_0 *)arg0)->unk_8C in func_8008D470 */

typedef struct S_8008D470_7 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8008D470_7;   /* ((S_8008D470_1 *)target)->unk_124 in func_8008D470 */



extern void *D_800E3D7C[];
extern u32 D_800814A0[];
extern s32 D_800814A8[];
extern u8 D_80081484[];

extern s32 func_8003DE58();
extern s32 func_800644B8();
extern s32 func_800A8E74();

/* Move the effect toward its target, pulse its brightness, and handle expiration. */
void func_8008D470(void *effect, S_8008D470_4 *position, S_8008D470_3 *visual) {
    s16 offsets[3];
    s16 state;
    s32 expiry_mode;
    s16 brightness;
    s32 current_x;
    s32 current_y;
    s32 current_z;
    register s32 update_result;
    s32 spawn_handle;
    register s32 position_updated ASM_REG("$19"); /* MATCH: shared-tail liveness otherwise swaps position_updated and visual registers. */
    u16 steps_left;
    u8 intensity;
    S_8008D470_1 *target;
    S_8008D470_5 *entity;

    state = ((S_8008D470_0 *)effect)->unk_A2.s;
    position_updated = 0;
    if (state != 0) {
        if (state != 1) {
            goto update_light;
        }
    } else {
        ((S_8008D470_0 *)effect)->unk_A4.s = 6;
        ((S_8008D470_0 *)effect)->unk_A2.s = ((S_8008D470_0 *)effect)->unk_A2.u + 1;
    }

    target = ((S_8008D470_0 *)effect)->unk_90;
    if (func_8003DE58(target->unk_08, target, offsets, 0) != 0 &&
        ((S_8008D470_2 *)(D_800E3D7C[0]))->unk_124 != 0) {
        visual->unk_1C = 0x1000;
        steps_left = ((S_8008D470_0 *)effect)->unk_A4.s - 1;
        ((S_8008D470_0 *)effect)->unk_A4.s = steps_left;
        if ((s16)steps_left > 0) {
            current_x = position->unk_00.at00.v;
            position->unk_00.at00.v = current_x +
                (((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_00.at00.v +
                 (offsets[0] << 16) - current_x) / (s16)steps_left;

            current_y = position->unk_04.at00.v;
            position->unk_04.at00.v = current_y +
                (((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_04.at00.v +
                 (offsets[1] << 16) - current_y) / ((S_8008D470_0 *)effect)->unk_A4.u;

            current_z = position->unk_08.at00.v;
            position->unk_08.at00.v = current_z +
                (((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_08.at00.v +
                 (offsets[2] << 16) - (((S_8008D470_0 *)effect)->unk_A4.u << 21) - current_z) /
                ((S_8008D470_0 *)effect)->unk_A4.u;
        } else {
            ((S_8008D470_0 *)effect)->unk_A4.s = 0;
            position->unk_00.at02.v = ((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_00.at02.v + (u16)offsets[0];
            position->unk_04.at02.v = ((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_04.at02.v + (u16)offsets[1];
            position->unk_08.at02.v = ((S_8008D470_6 *)(((S_8008D470_0 *)effect)->unk_8C))->unk_08.at02.v + (u16)offsets[2];
        }
        if (((S_8008D470_0 *)effect)->unk_AA == 0) {
            ((S_8008D470_0 *)effect)->unk_AA = 1;
            position_updated = 1;
        } else {
            position_updated = 1;
        }
    } else {
        state = ((S_8008D470_0 *)effect)->unk_AA;
        if (state != 0) {
            goto nonzero_state;
        }
        visual->unk_1C = 0;
        goto update_light;
nonzero_state:
        if (state == 1) {
            if (((S_8008D470_0 *)effect)->unk_AE == 0) {
                ((S_8008D470_0_pre *)effect)[-1].unk_00 |= 0x8000;
                D_800814A0[0] |= 0x8000;
            }
        }
    }

update_light:
    if (((S_8008D470_0 *)effect)->unk_AE != 0) {
        brightness = (func_800644B8(((S_8008D470_0 *)effect)->unk_B4.s << 8) >> 6) + 0x80;
        intensity = visual->unk_0C;
        intensity += (brightness - intensity) >> 2;
        visual->unk_0C = intensity;
        visual->unk_0D = intensity;
        visual->unk_0E = intensity;
    }

    ((S_8008D470_0 *)effect)->unk_B4.u++;
    ((S_8008D470_0 *)effect)->unk_A8.s--;
    if (((S_8008D470_0 *)effect)->unk_A8.u <= 0) {
        expiry_mode = ((S_8008D470_0 *)effect)->unk_AC;
        ((S_8008D470_0 *)effect)->unk_A8.s = 0;
        if (expiry_mode == 1) {
            spawn_handle = func_800A8E74(effect, position, visual, D_800814A8[0], ((S_8008D470_0 *)effect)->unk_9C, -1);
            if (spawn_handle != 0) {
                entity = (void *)(spawn_handle + 0x20);
                target = D_800E3D7C[0];
                target->unk_124 = entity;
                entity->unk_9C = D_80081484;
                entity->unk_1C |= 0x80000;
                ((S_8008D470_7 *)(target->unk_124))->unk_60 = target;
                target->unk_1C |= 0x100000;
                goto set_flag;
            }
        } else {
            if (expiry_mode == 2) {
                goto set_flag;
            }
            if (expiry_mode != 0) {
                return;
            }
            update_result = position_updated;
            ASM_KEEP(update_result); /* MATCH: materialize the retail v0 copy before testing position_updated. */
            if (update_result != 0) {
                return;
            }
set_flag:
            ((S_8008D470_0_pre *)effect)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
}
