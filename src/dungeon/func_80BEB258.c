#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(s32, s32, s32);

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80171014[];
extern u8 D_8017420C[];
extern Callback D_8017426C[];


typedef struct S_80170A58_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A58_0;   /* arg1 in func_80170A58 */


typedef struct S_80170A58_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170A58_2;   /* state in func_80170A58 */

/* Update entity callbacks, movement, sprite facing, and ground-relative height. */
void func_80170A58(void *entity, S_80170A58_0 *motion, void *sprite)
{
    S_80170A58_2 *state = entity;
    s16 previous_state;
    s32 view_dir;
    u8 dir_index;
    s16 height_offset;
    u16 height_bits;
    s32 hover_limit;
    s16 ground_delta;
    s32 ground_height;
    u16 part_flags;
    s32 entity_flags;
    Callback gated_callback;
    Callback update_callback;

    if (D_80083462 & 0x2000) {
        gated_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (gated_callback == (Callback)D_80171014) {
            gated_callback(entity, motion, sprite, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    previous_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (func_800A9E70(entity, motion, sprite, entity) != 0) {
        return;
    }

    update_callback = (*(Callback *)((u8 *)entity + 0x8C));
    if (update_callback != 0) {
        update_callback(entity, motion, sprite, entity);
    }
    D_8017426C[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    if (previous_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        func_800AA36C(entity, motion, sprite, entity);
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if (!((*(s32 *)((u8 *)entity + 0x1C)) & 0x40000) && !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D)) = (*(u8 *)((u8 *)entity + 0x9D)) + 1;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    part_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
    if (!(part_flags & 0x8000)) {
        view_dir = ((D_80083228 + state->unk_2A + 0x100) >> 9) & 7;
        dir_index = view_dir;
        if ((*(s16 *)((u8 *)entity + 0x94)) != dir_index) {
            func_80047738(sprite, ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8[dir_index],
                          ((Rec_D_80082E80 *)sprite)->unk_04.as_s8);
            (*(s16 *)((u8 *)entity + 0x94)) = view_dir;
        }
        if (D_8006CCF8[dir_index] != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 1;
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFFFE;
        }
        func_800A020C(state->unk_1C, (u8 *)sprite + 0xC);
        if (!(state->unk_1C & 0x20)) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                func_800478B8(sprite);
            }
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x7000;
            state->unk_1C &= 0xFFFBFFFF;
        }

        entity_flags = state->unk_1C;
        entity_flags &= 0xF7FFFFFF;
        state->unk_1C = entity_flags;
        entity_flags &= 0x40000;
        if (entity_flags != 0) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == D_8017420C) {
                    u16 bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                    (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick + 1;
                    (*(s32 *)((u8 *)entity + 0xA0)) += func_800644B8((s16)bob_tick * 0xAA) << 5;
                }
            }
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                func_800BCB04(motion->unk_00.at02.v, motion->unk_04.at02.v,
                              (s16)(state->unk_88 - 0x20));
                hover_limit = -0x20;
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_offset > hover_limit) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits - 8;
                } else if (height_offset < -0x28) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits + 8;
                }
            }
        } else {
            s32 bob_offset = (*(s32 *)((u8 *)entity + 0xA0));
            (*(u16 *)((u8 *)entity + 0x9E)) = 0;
            (*(s32 *)((u8 *)entity + 0xA0)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) -= bob_offset;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_delta = func_800BCB04(motion->unk_00.at02.v, motion->unk_04.at02.v,
                                      (s16)(state->unk_88 - 0x20)) -
                        state->unk_88;
                if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->unk_14 = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        }
    } else {
        if (!(part_flags & 0x800)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = part_flags | 0x7000;
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = part_flags & 0x8FFF;
        }

        entity_flags = state->unk_1C;
        entity_flags &= 0xF7FFFFFF;
        state->unk_1C = entity_flags;
        entity_flags &= 0x40000;
        if (entity_flags == 0) {
            s32 bob_offset = (*(s32 *)((u8 *)entity + 0xA0));
            (*(u16 *)((u8 *)entity + 0x9E)) = 0;
            (*(s32 *)((u8 *)entity + 0xA0)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) -= bob_offset;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_delta = func_800BCB04(motion->unk_00.at02.v, motion->unk_04.at02.v,
                                      (s16)(state->unk_88 - 0x20)) -
                        state->unk_88;
                if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->unk_14 = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        } else {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == D_8017420C) {
                    u16 bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                    (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick + 1;
                    (*(s32 *)((u8 *)entity + 0xA0)) += func_800644B8((s16)bob_tick * 0xAA) << 5;
                }
            }
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                func_800BCB04(motion->unk_00.at02.v, motion->unk_04.at02.v,
                              (s16)(state->unk_88 - 0x20));
                hover_limit = -0x20;
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_offset > hover_limit) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits - 8;
                } else if (height_offset < -0x28) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits + 8;
                }
            }
        }
    }

    entity_flags = state->unk_1C;
    if (entity_flags & 0x40000000) {
        state->unk_1C = entity_flags & 0xBFFFFFFF;
        ground_height = func_800BCB04((((Rec_D_80082E80 *)sprite)->unk_24 << 6) | 0x20,
                               (((Rec_D_80082E80 *)sprite)->unk_25 << 6) | 0x20,
                               (s16)(state->unk_88 - 0x20));
        if ((s16)ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (*(u16 *)((u8 *)entity + 0x92)) + (state->unk_88 - ground_height);
            state->unk_88 = ground_height;
        }
    }

    motion->unk_0A = state->unk_88 + (*(u16 *)((u8 *)entity + 0x92)) -
                            (*(u16 *)((u8 *)entity + 0xA2));
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x40;
}
