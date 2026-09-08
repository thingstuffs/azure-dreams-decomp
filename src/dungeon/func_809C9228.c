#include "common.h"


typedef void (*EntityCallback)(void *, void *, void *, void *);

extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern u8 D_8006CCF8[];
extern u16 D_80083462;
extern s16 D_80083228;
extern u8 D_80170E54;
extern EntityCallback D_80173CEC[];


typedef struct S_80170A28_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    union { u16 n; volatile u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80170A28_0;   /* arg2 in func_80170A28 */

typedef struct S_80170A28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_80170A28_1;   /* entity in func_80170A28 */

typedef struct S_80170A28_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A28_2;   /* arg1 in func_80170A28 */

/* Run entity callbacks and update facing, motion, and ground contact. */
void func_80170A28(void *entity_input, void *motion_input, void *part_input)
{
    register void *entity ASM_REG("$18") = entity_input;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_80170A28_2 *motion = motion_input;
    void *part = part_input;
    register void *entity_base ASM_REG("$17") = entity;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 state_or_direction;
    register s32 direction_index ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *call_entity ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *call_motion ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *call_part ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_self;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 previous_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 unused_tail;
    register s32 floor_height ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    EntityCallback callback;
    s32 rounded_angle;
    s16 ground_height;
    s16 base_height;
    s32 previous_direction;
    s32 entity_flags;
    s32 current_state;
    u16 part_flags;
    u16 new_part_flags;
    u8 direction_flag;

    if (D_80083462 & 0x2000) {
        callback = (*(EntityCallback *)((u8 *)entity + 0x8C));
        if (callback == (EntityCallback)&D_80170E54) {
            {
                void *self;
                self = entity_input;
                ASM_KEEP(self);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                callback(self, motion_input, part_input, self);
            }
            goto done;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        goto done;
    }

    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    call_entity = entity;
    call_motion = motion;
    call_part = part;
    previous_state = (*(u8 *)((u8 *)entity + 0x6D));
    call_self = entity;
    state_or_direction = (s8)previous_state;
    if (func_800A9E70(call_entity, call_motion, call_part, call_self) != 0) {
        return;
    }

    {
        EntityCallback update_callback;
        update_callback = (*(EntityCallback *)((u8 *)entity + 0x8C));
        if (update_callback != 0) {
            update_callback(entity, motion, part, entity);
        }
    }
    D_80173CEC[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, part, entity);

    previous_state = (s32)state_or_direction << 16;
    current_state = (*(s8 *)((u8 *)entity + 0x6D));
    previous_state >>= 16;
    if (previous_state != current_state) {
        func_800AA36C(entity, motion, part, entity);
    }

    part_flags = ((S_80170A28_0 *)part)->unk_14.n;
    if (!(part_flags & 0x8000)) {
        rounded_angle = D_80083228 + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        state_or_direction = (rounded_angle >> 9) & 7;
        previous_direction = (*(s16 *)((u8 *)entity + 0x94));
        direction_index = (u16)state_or_direction;
        if (previous_direction != state_or_direction) {
            if (((S_80170A28_0 *)part)->unk_2C != 0) {
                func_80047738(part,
                              ((S_80170A28_0 *)part)->unk_2C[state_or_direction],
                              ((S_80170A28_0 *)part)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = state_or_direction;
        }

        direction_flag = D_8006CCF8[direction_index];
        ASM_KEEP(direction_index);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (direction_flag != 0) {
            ((S_80170A28_0 *)part)->unk_14.n |= 1;
        } else {
            ((S_80170A28_0 *)part)->unk_14.n &= 0xFFFE;
        }
        if (!(((S_80170A28_1 *)entity_base)->unk_1C & 0x20)) {
            if (!(((S_80170A28_0 *)part)->unk_14.v & 0x40)) {
                func_800478B8(part);
                goto after_part_flags;
            }
        } else {
            ((S_80170A28_0 *)part)->unk_14.v |= 0x7000;
        }
after_part_flags:
        func_800A020C(((S_80170A28_1 *)entity_base)->unk_1C, (u8 *)part + 0xC);
        goto motion;
    }

    if (part_flags & 0x800) {
        new_part_flags = part_flags & 0x8FFF;
    } else {
        new_part_flags = part_flags | 0x7000;
    }
    ((S_80170A28_0 *)part)->unk_14.n = new_part_flags;

motion:
    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(s8 *)((u8 *)entity + 0x9D)) = 0;
        goto accumulate;
    }

    motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
    (*(s8 *)((u8 *)entity + 0x9D)) = (u8)(*(s8 *)((u8 *)entity + 0x9D)) + 1;
accumulate:
    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        ground_height = func_800BCB04(motion->unk_00.at02.v,
                               motion->unk_04.at02.v,
                               (s16)(((S_80170A28_1 *)entity_base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            base_height = (s16)((S_80170A28_1 *)entity_base)->unk_88;
            if ((*(s16 *)((u8 *)entity + 0x92)) + base_height < ground_height) {
                ((S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
                goto flags_test;
            }
            if (ground_height >= base_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
                motion->unk_14 = 0;
                ((S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
                goto flags_test;
            }

            motion->unk_14 = 0;
            ((S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
            (*(s8 *)((u8 *)entity + 0x9D)) = 0;
            (*(s16 *)((u8 *)entity + 0x92)) = ground_height - ((S_80170A28_1 *)entity_base)->unk_88;

flags_test:
            entity_flags = ((S_80170A28_1 *)entity_base)->unk_1C;
            if (entity_flags & 0x40000000) {
                ((S_80170A28_1 *)entity_base)->unk_1C = entity_flags & 0xBFFFFFFF;
                floor_height = func_800BCB04(
                    (((S_80170A28_0 *)part)->unk_24 << 6) | 0x20,
                    (((S_80170A28_0 *)part)->unk_25 << 6) | 0x20,
                    (s16)(((S_80170A28_1 *)entity_base)->unk_88 - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    ((S_80170A28_1 *)entity_base)->unk_88 - floor_height;
                ((S_80170A28_1 *)entity_base)->unk_88 = floor_height;
                goto finish;
            }
            goto finish;
        }
    }

    ((S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;

finish:
    motion->unk_0A =
        ((S_80170A28_1 *)entity_base)->unk_88 + (*(u16 *)((u8 *)entity + 0x92));
    ((S_80170A28_0 *)part)->unk_14.n |= 0x40;

done:
    return;
}
