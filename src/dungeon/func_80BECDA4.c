#include "common.h"

typedef struct S_801725A4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801725A4_0;   /* owner in func_801725A4 */

typedef struct S_801725A4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_801725A4_1;   /* object in func_801725A4 */

typedef struct S_801725A4_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801725A4_2;   /* actor in func_801725A4 */

typedef struct S_801725A4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801725A4_3;   /* motion in func_801725A4 */

typedef struct S_801725A4_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801725A4_4;   /* status in func_801725A4 */

extern s32 func_8003F270(void);
extern void func_80047784(void *, u8, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800BB044(void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[28];
extern u8 D_80171014[];
extern u8 D_8017420C[];

/* Advances an object action through spawning, actor synchronization, and cleanup. */
void func_801725A4(void *owner_arg, void *motion_arg, void *actor_arg, void *object_arg)
{
    static void *const dispatch_labels[] = {
        &&L_tail_b0, &&L_tail_b8, &&L_tail_c0, &&L_after_jt
    };
    register void *owner ASM_REG("$21") = owner_arg;
    register void *motion ASM_REG("$19") = motion_arg;
    register void *actor ASM_REG("$18") = actor_arg;
    register void *object ASM_REG("$16") = object_arg;
    register s32 is_special;
    u8 *action_data;
    register s32 x ASM_REG("$2");
    s32 y;
    s32 kind;
    u32 kind_index;
    void *spawn;
    u8 *action_entry;
    register u8 *record ASM_REG("$3");
    u8 *action_table;
    u32 action_id;
    void **dispatch_table;
    s32 state;
    state = ((S_801725A4_0 *)owner)->unk_9B;
    ASM_KEEP_NV(motion);
    ASM_KEEP_NV(actor);
    ASM_KEEP_NV(object);
    is_special = 0;
    if (state == 1) {
        goto L_state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto L_state0;
        }
        return;
    }
    if (state == 2) {
        goto L_state2;
    }
    return;

L_state0:
    if (((S_801725A4_1 *)object)->unk_1C & 0x2000) {
        kind_index = (((S_801725A4_1 *)object)->unk_46 & 0x3FFF) - 1;
        if (kind_index >= 7U) {
            goto L_after_jt;
        }
        dispatch_table = (void **)D_80170838;
        (void)dispatch_labels;
        goto *dispatch_table[kind_index];

L_tail_b0:
        is_special = 1;
        goto L_kind3;
L_tail_b8:
        is_special = 1;
        goto L_kind2;
L_tail_c0:
        is_special = 1;
        goto L_kind1;
    }

    kind = ((S_801725A4_1 *)object)->unk_46 & 0x3FFF;
    if (kind == 2) {
        goto L_kind2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto L_kind1;
        }
        action_data = 0;
        goto L_selected;
    }
    if (kind == 3) {
L_kind3:
        action_data = (u8 *)object + 0xE;
        goto L_selected;
    }
    action_data = 0;
    goto L_selected;
L_kind2:
    action_data = (u8 *)object + 0xB;
    goto L_selected;
L_kind1:
    action_data = (u8 *)object + 8;
    goto L_selected;

L_after_jt:
    action_data = 0;
L_selected:
    if (*action_data != 0) {
        ((S_801725A4_0 *)owner)->unk_98 &= 0xFF7F;
        ASM_KEEP(owner);
        x = is_special;
        if (x) {
            spawn = D_800814A8;
            ((S_801725A4_1 *)object)->unk_60 = spawn;
            goto L_record;
        }

        action_table = D_8006DE24;
        action_id = *action_data;
        action_entry = action_table + (action_id * 20);
        if (action_entry[0x12] == 2) {
            spawn = ((S_801725A4_1 *)object)->unk_60;
            if (spawn == 0) {
                goto L_spawn_ready;
            }
L_record:
            record = *(u8 **)((u8 *)spawn - 0x14);
            ((S_801725A4_1 *)object)->unk_72.s = record[0x24];
            ((S_801725A4_1 *)object)->unk_73.s = record[0x25];
            goto L_spawn_ready;
        }

        spawn = func_800A05A4(
            object,
            ((S_801725A4_2 *)actor)->unk_24,
            ((S_801725A4_2 *)actor)->unk_25,
            ((S_801725A4_1 *)object)->unk_2A,
            0x10);
        ((S_801725A4_1 *)object)->unk_60 = spawn;

        x = ((S_801725A4_1 *)object)->unk_72.u;
        y = ((S_801725A4_1 *)object)->unk_73.u;
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        ((S_801725A4_1 *)object)->unk_72.s = x;
        ((S_801725A4_1 *)object)->unk_73.s = y;

L_spawn_ready:
        if (func_800A94A0(object, action_data, is_special,
                          (u16 *)((u8 *)owner + 0x98)) == 0) {
            return;
        }
        func_800BB044(object);
        ((S_801725A4_0 *)owner)->unk_9B++;
        return;
    }

    ((S_801725A4_3 *)motion)->unk_14 = 0;
    ((S_801725A4_3 *)motion)->unk_10 = 0;
    ((S_801725A4_3 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((S_801725A4_2 *)actor)->unk_24, ((S_801725A4_2 *)actor)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(object);
    ((S_801725A4_1 *)object)->unk_6D--;
    ((S_801725A4_0 *)owner)->unk_8C = D_80171014;
    ((S_801725A4_1 *)object)->unk_73.s = 0;
    ((S_801725A4_1 *)object)->unk_72.s = 0;
    ((S_801725A4_1 *)object)->unk_46 &= 0x7FFF;
    return;

L_state1:
    if (func_8003F270() != 0) {
        ((S_801725A4_2 *)actor)->unk_14 |= 0x0800;
        return;
    }
    ((S_801725A4_2 *)actor)->unk_14 &= 0xF7FF;
    ((S_801725A4_0 *)owner)->unk_9B++;

L_state2:
    if (((S_801725A4_2 *)actor)->unk_04 == 4) {
        if (((S_801725A4_2 *)actor)->unk_14 & 0x1000) {
            goto L_state2_ready;
        }
    }
    if ((((S_801725A4_2 *)actor)->unk_14 & 0xE000) == 0) {
        return;
    }

L_state2_ready:
    ((S_801725A4_0 *)owner)->unk_98 |= 0x80;
    if ((((S_801725A4_2 *)actor)->unk_14 & 0xE000) == 0) {
        return;
    }

    ((S_801725A4_3 *)motion)->unk_14 = 0;
    ((S_801725A4_3 *)motion)->unk_10 = 0;
    ((S_801725A4_3 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((S_801725A4_2 *)actor)->unk_24, ((S_801725A4_2 *)actor)->unk_25);

    {
        u8 *direction_table = D_8017420C;
        if (((S_801725A4_2 *)actor)->unk_2C != direction_table) {
            (*(u8 * *)((u8 *)actor + 0x2C)) = direction_table;
            func_80047784(
                actor,
                direction_table[((D_80083228 + ((S_801725A4_1 *)object)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
    }

    {
        u8 *status = (u8 *)&D_80083460;
        if (((S_801725A4_4 *)status)->unk_0C != 0) {
            return;
        }
        ((S_801725A4_4 *)status)->unk_0A--;
    }
    ((S_801725A4_0 *)owner)->unk_8C = D_80171014;
    func_800A4ACC(object);
    ((S_801725A4_1 *)object)->unk_73.s = 0;
    ((S_801725A4_1 *)object)->unk_72.s = 0;
    ((S_801725A4_1 *)object)->unk_6D--;
    ((S_801725A4_1 *)object)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
}
