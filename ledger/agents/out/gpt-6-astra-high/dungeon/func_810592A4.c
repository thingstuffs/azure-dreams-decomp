#include "common.h"


typedef void (*EntityCallback)(void *, void *, void *, void *);

extern void func_80042984();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern void func_800A56E0();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80170F68;
extern EntityCallback D_80174018[];


typedef struct S_80170AA4_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xD];
    s16 unk_12;
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80170AA4_0;   /* arg2 in func_80170AA4 */

typedef struct S_80170AA4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170AA4_1;   /* entity in func_80170AA4 */

typedef struct S_80170AA4_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170AA4_2;   /* arg1 in func_80170AA4 */

/* Updates entity callbacks, directional animation, movement, and ground contact. */
void func_80170AA4(void *entity_input, void *motion_input, void *part_input)
{
    register void *actor ASM_REG("$17") = entity_input;   /* MATCH pin: retail register colouring depends on it */
    S_80170AA4_2 *motion = motion_input;
    void *part = part_input;
    register void *entity ASM_REG("$18") = actor;   /* MATCH pin: load-bearing for the whole function shape */
    s16 state_direction;
    register s32 direction_index ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *call_entity ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call_motion ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *call_part ASM_REG("$6");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_self;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 previous_state ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 floor_height ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    EntityCallback callback;
    s32 view_angle;
    s16 ground_height;
    s16 base_height;
    s32 previous_direction;
    s32 entity_flags;
    s32 current_state;
    s32 wobble;
    s32 wobble_base;
    u16 part_flags;
    u16 new_part_flags;
    u8 direction_flag;

    if (D_80083462 & 0x2000) {
        callback = (*(EntityCallback *)((u8 *)actor + 0x8C));
        if (callback == (EntityCallback)&D_80170F68) {
            void *self;
            self = entity_input;
            ASM_KEEP(self);   /* MATCH pin: retail register colouring depends on it */
            callback(self, motion_input, part_input, self);
            goto done;
        }
        (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        goto done;
    }

    ASM_KEEP(actor);   /* MATCH pin: keeps a statement from moving across a call/branch */
    call_entity = actor;
    call_motion = motion;
    call_part = part;
    previous_state = (*(u8 *)((u8 *)actor + 0x6D));
    call_self = actor;
    state_direction = (s8)previous_state;
    if (func_800A9E70(call_entity, call_motion, call_part, call_self) != 0) {
        return;
    }

    {
        EntityCallback update_callback;
        update_callback = (*(EntityCallback *)((u8 *)actor + 0x8C));
        if (update_callback != 0) {
            update_callback(actor, motion, part, actor);
        }
    }
    D_80174018[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, part, actor);

    previous_state = (s32)state_direction << 16;
    current_state = (*(s8 *)((u8 *)actor + 0x6D));
    previous_state >>= 16;
    if (previous_state != current_state) {
        func_800AA36C(actor, motion, part, actor);
    }

    if ((*(u16 *)((u8 *)actor + 0x98)) & 0x8000) {
        wobble = (*(u16 *)((u8 *)actor + 0xAC)) + 1;
        (*(s16 *)((u8 *)actor + 0xAC)) = wobble;
        if (((s16)wobble >> 2) >= 2) {
            (*(s16 *)((u8 *)actor + 0xAC)) = -8;
            func_800A56E0(0x60B);
        }
        wobble = (*(u16 *)((u8 *)actor + 0xAC));
        wobble_base = (*(u16 *)((u8 *)actor + 0xA6));
        wobble = (s16)wobble >> 2;
        if (wobble < 0) {
            wobble = -wobble;
        }
        wobble_base += wobble;
        ((S_80170AA4_0 *)part)->unk_12 = wobble_base;
    } else if (((*(s32 *)((u8 *)actor + 0x14)) & 7) != (*(s16 *)((u8 *)actor + 0xAA))) {
        func_80042984(actor);
        (*(s16 *)((u8 *)actor + 0xAA)) = (*(u16 *)((u8 *)actor + 0x14)) & 7;
    }

    part_flags = ((S_80170AA4_0 *)part)->unk_14.n;
    if (!(part_flags & 0x8000)) {
        view_angle = D_80083228 + ((S_80170AA4_1 *)entity)->unk_2A + 0x100;
        state_direction = (view_angle >> 9) & 7;
        previous_direction = (*(s16 *)((u8 *)actor + 0x94));
        direction_index = (u16)state_direction;
        if (previous_direction != state_direction) {
            if (((S_80170AA4_0 *)part)->unk_2C != 0) {
                func_80047738(part,
                              ((S_80170AA4_0 *)part)->unk_2C[state_direction],
                              ((S_80170AA4_0 *)part)->unk_04);
            }
            (*(s16 *)((u8 *)actor + 0x94)) = state_direction;
        }

        direction_flag = D_8006CCF8[direction_index];
        ASM_KEEP(direction_index);   /* MATCH pin: load-bearing for the whole function shape */
        if (direction_flag != 0) {
            ((S_80170AA4_0 *)part)->unk_14.n |= 1;
        } else {
            ((S_80170AA4_0 *)part)->unk_14.n &= 0xFFFE;
        }
        if (!(((S_80170AA4_1 *)entity)->unk_1C & 0x20)) {
            if (!(((S_80170AA4_0 *)part)->unk_14.v & 0x40)) {
                func_800478B8(part);
                goto after_part_flags;
            }
        } else {
            ((S_80170AA4_0 *)part)->unk_14.v |= 0x7000;
        }
after_part_flags:
        func_800A020C(((S_80170AA4_1 *)entity)->unk_1C, (u8 *)part + 0xC);
        goto motion;
    }

    if (part_flags & 0x800) {
        new_part_flags = part_flags & 0x8FFF;
    } else {
        new_part_flags = part_flags | 0x7000;
    }
    ((S_80170AA4_0 *)part)->unk_14.n = new_part_flags;

motion:
    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)actor + 0x98)) & 8) {
        (*(s8 *)((u8 *)actor + 0x9D)) = 0;
        goto accumulate;
    }

    motion->unk_14 += (*(s8 *)((u8 *)actor + 0x9D)) * 0x14000;
    (*(s8 *)((u8 *)actor + 0x9D)) = (u8)(*(s8 *)((u8 *)actor + 0x9D)) + 1;
accumulate:
    (*(s32 *)((u8 *)actor + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)actor + 0x98)) & 4)) {
        ground_height = func_800BCB04(motion->unk_00.at02.v,
                               motion->unk_04.at02.v,
                               (s16)(((S_80170AA4_1 *)entity)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            base_height = (s16)((S_80170AA4_1 *)entity)->unk_88;
            if ((*(s16 *)((u8 *)actor + 0x92)) + base_height < ground_height) {
                ((S_80170AA4_1 *)entity)->unk_1C &= 0xF7FFFFFF;
                goto flags_test;
            }
            if (ground_height >= base_height) {
                (*(s32 *)((u8 *)actor + 0x90)) = 0;
                motion->unk_14 = 0;
                ((S_80170AA4_1 *)entity)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)actor + 0x9D)) = 0;
                goto flags_test;
            }

            motion->unk_14 = 0;
            ((S_80170AA4_1 *)entity)->unk_1C |= 0x08000000;
            (*(s8 *)((u8 *)actor + 0x9D)) = 0;
            (*(s16 *)((u8 *)actor + 0x92)) = ground_height - ((S_80170AA4_1 *)entity)->unk_88;

flags_test:
            entity_flags = ((S_80170AA4_1 *)entity)->unk_1C;
            if (entity_flags & 0x40000000) {
                ((S_80170AA4_1 *)entity)->unk_1C = entity_flags & 0xBFFFFFFF;
                floor_height = func_800BCB04(
                    (((S_80170AA4_0 *)part)->unk_24 << 6) | 0x20,
                    (((S_80170AA4_0 *)part)->unk_25 << 6) | 0x20,
                    (s16)(((S_80170AA4_1 *)entity)->unk_88 - 0x20));
                (*(s16 *)((u8 *)actor + 0x92)) +=
                    ((S_80170AA4_1 *)entity)->unk_88 - floor_height;
                ((S_80170AA4_1 *)entity)->unk_88 = floor_height;
                goto finish;
            }
            goto finish;
        }
    }

    ((S_80170AA4_1 *)entity)->unk_1C &= 0xF7FFFFFF;

finish:
    motion->unk_0A =
        ((S_80170AA4_1 *)entity)->unk_88 + (*(u16 *)((u8 *)actor + 0x92));
    ((S_80170AA4_0 *)part)->unk_14.n |= 0x40;

done:
    return;
}
