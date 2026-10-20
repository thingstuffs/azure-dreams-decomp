#include "modules/dungeon_ovl_19c6800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

typedef struct S_func_819A6800_1 {
    void *unk_00;
    void *unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;
    u8 pad_0C[0x44];
    union { s16 s; u16 u; } unk_50;
    union { s16 s; u16 u; } unk_52;
} S_func_819A6800_1;

typedef struct S_func_819A6800_2 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x0C];
    void *unk_20;
    u8 unk_24;
    u8 unk_25;
} S_func_819A6800_2;

typedef struct S_func_819A6800_3 {
    u8 pad_00[0x60];
    union { void *p; u32 u; } unk_60;
    u8 pad_64[0x0E];
    u8 unk_72;
    u8 unk_73;
} S_func_819A6800_3;

typedef struct S_func_819A6800_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x7A];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    u32 unk_F4;
    u8 pad_F8[0x0A];
    u8 unk_102;
} S_func_819A6800_4;

typedef struct S_func_819A6800_5 {
    union {
        u32 u;
        s32 s;
        struct { u8 pad_00[2]; u16 unk_02; } h;
    } unk_00;
    union {
        u32 u;
        s32 s;
        struct { u8 pad_04[2]; u16 unk_06; } h;
    } unk_04;
    union {
        u32 u;
        s32 s;
        struct { u8 pad_08[2]; u16 unk_0A; } h;
    } unk_08;
} S_func_819A6800_5;

typedef struct S_func_819A6800_6 {
    u16 unk_00;
} S_func_819A6800_6;

typedef struct S_func_819A6800_7 {
    u8 pad_00[0x0C];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x1E];
    u16 unk_30;
    u16 unk_32;
    u32 unk_34;
    u32 unk_38;
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
    u16 unk_42;
    u8 pad_44[8];
    u16 unk_4C;
} S_func_819A6800_7;

typedef struct S_func_819A6800_9 {
    u8 pad_00[4];
    u32 unk_04;
} S_func_819A6800_9;

extern u8 D_800814A8[16];
struct S_800244BC_2;
void func_800244BC(void *, struct S_800244BC_2 *, s32);
void update_jittered_effect_points(void *);
s32 update_segment(void *);
extern u8 D_800DEE38[];
extern u32 D_800814A0[];

#define GLOBAL_OBJECT (*(void **)D_800814A8)

extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s32 func_80053EF0(s32);
extern u16 func_80066460(s32, s32, s32, s32);
extern u16 func_8006649C(s32, s32);
extern void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, void *, s32);

void func_80024020(void *sequence, void *out_position);

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */

void (*const dungeon_19c6800_entry)(void *, void *) = func_80024020;

#define SELF ((S_func_819A6800_1 *)sequence)

/* Runs a timed object creation sequence with visual effects and final cleanup. */
void func_80024020(void *sequence, void *out_position)
{
    S_func_819A6800_3 *owner = SELF->unk_00;
    S_func_819A6800_2 *record = ((S_func_819A6800_2 *)((u8 *)owner - 0x20))->unk_0C;
    S_func_819A6800_2 *owner_object = (S_func_819A6800_2 *)((u8 *)owner - 0x20);
    u16 timer;
    s32 state;
    S_func_819A6800_2 *new_object;
    S_func_819A6800_4 *counter_object;
    s16 position_offset[3];
    S_func_819A6800_7 *effect_data;
    SpriteFrameState *sprite;
    u8 *global_slot;
    S_func_819A6800_4 *global_object;
    S_func_819A6800_4 *reloaded_object;

    timer = SELF->unk_50.u - 1;
    state = SELF->unk_0A.s;
    SELF->unk_50.u = timer;
    switch (state) {
    case 0:
        global_slot = (u8 *)&D_800814A0[2];
        global_object = *(void **)global_slot;
        global_object->unk_102 = 1;
        reloaded_object = *(void * *)global_slot;
        reloaded_object->unk_F4 = 0;

        ((S_func_819A6800_5 *)(out_position))->unk_00.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_00.u;
        ((S_func_819A6800_5 *)(out_position))->unk_04.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_04.u;
        ((S_func_819A6800_5 *)(out_position))->unk_08.u = ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_08.u;

        new_object = scan_monster_along_heading(reloaded_object,
                                   D_80082E80.tileX,
                                   D_80082E80.tileY,
                                   reloaded_object->unk_2A,
                                   7);
        owner->unk_60.p = new_object;
        if (new_object == 0) {
            owner->unk_72 = record->unk_24;
            owner->unk_73 = record->unk_25;
        } else {
            sprite = ((S_func_819A6800_2 *)((u8 *)new_object - 0x20))->unk_0C;
            owner->unk_72 = sprite->unk_24;
            owner->unk_73 = sprite->unk_25;
        }

        SELF->unk_0A.u++;
    case 1:
        if ((((S_func_819A6800_6 *)(SELF->unk_04))->unk_00 & 0x80) == 0) {
            return;
        }

        counter_object = GLOBAL_OBJECT;
        SELF->unk_50.u = 10;
        counter_object->unk_A6--;
        counter_object->unk_A8 = SELF->unk_08;
        new_object = allocate_list_node(0x312, ((u8 *)(&D_80083498)));
        record = new_object;
        if (record != 0) {
            if (resolve_record_orientation_or_fallback(((S_func_819A6800_2 *)(owner_object->unk_0C))->unk_08,
                              owner_object->unk_0C, position_offset, 0) == 0) {
                position_offset[2] = 0;
                position_offset[1] = 0;
                position_offset[0] = 0;
            }
            record->unk_10 = func_800244BC;
            register_node(record, project_sprite_chain);
            sprite = record->unk_0C;

            ((S_func_819A6800_5 *)(record->unk_08))->unk_00.s =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_00.s + ((s32)position_offset[0] << 16);
            ((S_func_819A6800_5 *)(record->unk_08))->unk_04.s =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_04.s + ((s32)position_offset[1] << 16);
            ((S_func_819A6800_5 *)(record->unk_08))->unk_08.s =
                ((S_func_819A6800_5 *)(owner_object->unk_08))->unk_08.s + ((s32)position_offset[2] << 16);

            effect_data = (S_func_819A6800_7 *)((u8 *)record + 0x20);
            effect_data->unk_0C = ((S_func_819A6800_5 *)(record->unk_08))->unk_00.h.unk_02;
            effect_data->unk_0E = ((S_func_819A6800_5 *)(record->unk_08))->unk_04.h.unk_06;
            effect_data->unk_10 = ((S_func_819A6800_5 *)(record->unk_08))->unk_08.h.unk_0A;

            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->tpage_abr = 0x20;
            sprite->flags |= 0x0C;
            sprite->unk_00 = D_800DEE38;
            sprite->source = ((S_func_819A6800_9 *)(D_800DEE38))->unk_04;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->color.word = 0x00606060;
            record->unk_20 = SELF;
            effect_data->unk_4C = 0;
        }
        SELF->unk_0A.u++;
        return;

    case 2:
        if ((s16)SELF->unk_50.u > 0) {
            return;
        }
        {
            s32 mode = func_80053EF0(4);
            if (mode != 2) {
                mode = 0x300;
            } else {
                mode = 0x4300;
            }
            play_sound_if_enabled(mode);
        }
        {
            u16 next_state = SELF->unk_0A.u;
            u16 timer;
            timer = 10;
            SELF->unk_50.u = timer;
            SELF->unk_0A.u = next_state + 1;
        }
        return;

    case 3:
    {
        s16 timer_left = SELF->unk_50.s;
        if (timer_left == 7) {
            if (owner->unk_60.p != 0) {
                record = allocate_list_node(0x302, ((u8 *)(&D_80083498)));
                if (record != 0) {
                    S_func_819A6800_7 *effect_data = (S_func_819A6800_7 *)((u8 *)record + 0x20);
                    u32 target_object;
                    record->unk_10 = update_jittered_effect_points;
                    register_node(record, update_segment);
                    target_object = owner->unk_60.u;
                    effect_data->unk_3C = 0;
                    effect_data->unk_3E = 0;
                    effect_data->unk_32 = 0x1F;
                    effect_data->unk_30 = 0x1F;
                    effect_data->unk_34 = target_object;
                    effect_data->unk_40 = func_80066460(0, 1, 0x2C0, 0x100);
                    effect_data->unk_42 = func_8006649C(0x60, 0x1F8);
                    effect_data->unk_38 = 0x00404040;
                    record->unk_20 = SELF;
                }
            }
        }
    }
        if (SELF->unk_50.s == 4) {
            apply_attack_power_and_element_effects(owner->unk_60.p,
                          10,
                          SELF->unk_09,
                          12,
                          ((S_func_819A6800_4 *)(GLOBAL_OBJECT))->unk_2A,
                          owner,
                          2);
        }
        if ((D_80082E80.unk_014 & 0x8000) == 0 &&
            SELF->unk_50.s >= 0) {
            return;
        }
        {
            u16 next_state5 = SELF->unk_0A.u;
            u16 cleanup_delay;
            cleanup_delay = 20;
            SELF->unk_50.u = cleanup_delay;
            SELF->unk_0A.u = next_state5 + 1;
        }
        return;

    case 4:
        if ((s16)SELF->unk_50.u > 0) {
            return;
        }
        SELF->unk_0A.u++;
        return;

    case 5:
    {
        s16 signed_flags = SELF->unk_52.s;
        u16 flags = SELF->unk_52.u;
        if ((signed_flags & 0x8000) != 0) {
            SELF->unk_52.u = flags & 0x7FFF;
            return;
        }
    }
        {
            g_dungeon_status.unk_0C = 0;
            g_dungeon_status.unk_0A--;
        }
        ((S_func_819A6800_6 *)((u8 *)SELF - 2))->unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;

        return;
    }
}

#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"

typedef struct S_800244BC_0_pre {
    u16 unk_00;
} S_800244BC_0_pre;   /* the 0x2 bytes before arg0 in func_800244BC, addressed as arg0[-1] */

typedef struct S_800244BC_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_800244BC_0;   /* arg0 in func_800244BC */

typedef struct S_800244BC_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_800244BC_1;

typedef struct S_800244BC_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800244BC_2;   /* arg1 in func_800244BC */

typedef struct S_800244BC_3 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800244BC_3;

typedef struct S_800244BC_4 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u8 pad_2A[0x6];
    s16 unk_30;
    s16 unk_32;
    u8 pad_34[0x4];
    s32 unk_38;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
} S_800244BC_4;

typedef struct {
    u8 pad[0xC];
    u32 word0;
    u32 word1;
} CopySource __attribute__((packed));

typedef struct {
    u8 pad[0x24];
    u32 word0;
    u32 word1;
} CopyDestination __attribute__((packed));

/* cfail-repair: tf7-phase1-cache-v3 */
s32 resolve_record_orientation_or_fallback();       /* extern */
s32 func_800644B8(s32, s16 *); /* extern */
extern u16 func_80066460(s32, s32, s32, s32); /* extern */
s32 rand();                                /* extern */
void update_randomized_intermediate_points(void *);

/* Move toward the target while spawning effects, then mark the sequence complete. */
void func_800244BC(void *object, S_800244BC_2 *position, s32 context) {
    s16 target_pos[3];
    s16 phase;
    s32 effects_left;
    S_800244BC_4 *effect_data;
    void *effect;
    S_800244BC_1 *owner;

    owner = ((S_800244BC_0 *)object)->unk_00;
    ((S_800244BC_0 *)object)->unk_48 = (u16) (((S_800244BC_0 *)object)->unk_48 - 1);
    owner->unk_52 = (u16) (owner->unk_52 | 0x8000);
    phase = ((S_800244BC_0 *)object)->unk_4C;
    switch (phase) {
    case 0:
        ((S_800244BC_0 *)object)->unk_48 = 0xAU;
        ((S_800244BC_0 *)object)->unk_4C = (s16) ((u16) ((S_800244BC_0 *)object)->unk_4C + 1);
                        /* fall through */
    case 1:
        if (resolve_record_orientation_or_fallback(D_80082E80.unk_008, ((s32 *)(&D_80082E80)), target_pos, 0) != 0) {
            func_800478B8(context);
            position->unk_00.at00.v = (s32) (position->unk_00.at00.v + (((target_pos[0] + D_80083780.x.w.i)
                - position->unk_00.at02.v) << 0xE));
            position->unk_04.at00.v = (s32) (position->unk_04.at00.v + (((target_pos[1] + D_80083780.y.w.i)
                - position->unk_04.at02.v) << 0xE));
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v + (((target_pos[2] + D_80083780.z.w.i)
                - position->unk_08.at02.v) << 0xE));
            effects_left = 0;
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v
                - (func_800644B8(((s16) ((S_800244BC_0 *)object)->unk_48 << 0xB) / 10, ((s16 *)(&D_80083780))) << 9));
            do {
                effect = allocate_list_node(0x302, ((u8 *)(&D_80083498)));
                effect_data = effect + 0x20;
                if (effect != 0) {
                    ((S_800244BC_3 *)effect)->unk_10 = update_randomized_intermediate_points;
                    effect_data->unk_3C = 0;
                    effect_data->unk_3E = (s16) ((rand() & 3) + 2);
                    effect_data->unk_32 = 0x1F;
                    effect_data->unk_30 = 0x1F;
                    effect_data->unk_40 = func_80066460(0, 1, 0x2C0, 0x100);
                    effect_data->unk_38 = 0x404040;
                    memcpy((u8 *) effect + 0x24, (u8 *) object + 0xC, 8);
                    effect_data->unk_24 = (u16) position->unk_00.at02.v;
                    effect_data->unk_26 = (u16) position->unk_04.at02.v;
                    effect_data->unk_28 = (u16) position->unk_08.at02.v;
                    ((S_800244BC_3 *)effect)->unk_20 = (void *) ((S_800244BC_0 *)object)->unk_00;
                }
                effects_left -= 1;
            } while (effects_left >= 0);
        }
        if ((s16) ((S_800244BC_0 *)object)->unk_48 <= 0) {
            ((S_800244BC_0 *)object)->unk_48 = 8U;
            ((S_800244BC_0 *)object)->unk_4C = (s16) ((u16) ((S_800244BC_0 *)object)->unk_4C + 1);
        }
        break;
    case 2:
        if (resolve_record_orientation_or_fallback(D_80082E80.unk_008, ((s32 *)(&D_80082E80)), target_pos, 0) != 0) {
            func_800478B8(context);
            position->unk_00.at00.v = (s32) (position->unk_00.at00.v + (((target_pos[0] + D_80083780.x.w.i)
                - position->unk_00.at02.v) << 0xF));
            position->unk_04.at00.v = (s32) (position->unk_04.at00.v + (((target_pos[1] + D_80083780.y.w.i)
                - position->unk_04.at02.v) << 0xF));
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v + (((target_pos[2] + D_80083780.z.w.i)
                - position->unk_08.at02.v) << 0xF));
        }
        if ((s16) ((S_800244BC_0 *)object)->unk_48 <= 0) {
            ((S_800244BC_0_pre *)object)[-1].unk_00 = (u16) (((S_800244BC_0_pre *)object)[-1].unk_00 | 0x8000);
            object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
        }
        break;
    }
}

#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80024810_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80024810_2;

typedef struct S_80024810_0_pre {
    u16 unk_00;
} S_80024810_0_pre;   /* the 0x2 bytes before arg0 in update_jittered_effect_points, addressed as arg0[-1] */

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
} S_80024810_0;   /* arg0 in update_jittered_effect_points */

typedef struct S_80024810_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_80024810_1;

/* micro-lane E 2026-08-14: true base 0x80024810 (delta 0x7E65D800) */
s32 resolve_record_orientation_or_fallback();       /* extern */
s32 rand();                                /* extern */

/* Update the effect's jittered points between endpoints and advance its animation. */
void update_jittered_effect_points(void *effect) {
    u16 coord_delta[3];
    s32 phase;
    s32 point_index;

    S_80024810_1 *owner;
    S_80024810_2 *target;

    owner = ((S_80024810_0 *)effect)->unk_00;
    target = (void *) (((S_80024810_0 *)effect)->unk_34 - 0x20);
    owner->unk_52 = (u16) (owner->unk_52 | 0x8000);
    ((S_80024810_0 *)effect)->unk_24 = (u16) ((MovingPosition *)(target->unk_08))->unk_02;
    ((S_80024810_0 *)effect)->unk_26 = (u16) ((MovingPosition *)(target->unk_08))->unk_06;
    ((S_80024810_0 *)effect)->unk_28 = (s16) (((MovingPosition *)(target->unk_08))->unk_0A - 0x20);
    ((S_80024810_0 *)effect)->unk_04 = (u16) D_80083780.x.w.i;
    ((S_80024810_0 *)effect)->unk_06 = (u16) D_80083780.y.w.i;
    ((S_80024810_0 *)effect)->unk_08 = (u16) D_80083780.z.w.i;
    if (resolve_record_orientation_or_fallback(D_80082E80.unk_008, ((s32 *)(&D_80082E80)), coord_delta, 0) != 0) {
        ((S_80024810_0 *)effect)->unk_04 = (u16) (((S_80024810_0 *)effect)->unk_04 + coord_delta[0]);
        ((S_80024810_0 *)effect)->unk_06 = (u16) (((S_80024810_0 *)effect)->unk_06 + coord_delta[1]);
        ((S_80024810_0 *)effect)->unk_08 = (u16) (((S_80024810_0 *)effect)->unk_08 + coord_delta[2]);
    }
    coord_delta[0] = (u16) ((s32) ((s16) ((S_80024810_0 *)effect)->unk_24 - (s16) ((S_80024810_0 *)effect)->unk_04)
        >> 2);
    point_index = 1;
    coord_delta[1] = (u16) ((s32) ((s16) ((S_80024810_0 *)effect)->unk_26 - (s16) ((S_80024810_0 *)effect)->unk_06)
        >> 2);
    coord_delta[2] = (u16) ((s32) (((S_80024810_0 *)effect)->unk_28 - (s16) ((S_80024810_0 *)effect)->unk_08) >> 2);
    do {
        (*(s16 *)((u8 *)effect + (point_index * 8) + 4)) = (s16) ((((S_80024810_0 *)effect)->unk_04
            + ((s16) coord_delta[0] * point_index) + (rand() & 0x3F)) - 0x20);
        (*(s16 *)((u8 *)effect + (point_index * 8) + 6)) = (s16) ((((S_80024810_0 *)effect)->unk_06
            + ((s16) coord_delta[1] * point_index) + (rand() & 0x3F)) - 0x20);
        (*(s16 *)((u8 *)effect + (point_index * 8) + 8)) = (s16) ((((S_80024810_0 *)effect)->unk_08
            + ((s16) coord_delta[2] * point_index)) - (rand() & 0x3F));
        point_index += 1;
    } while (point_index < 4);
    ((S_80024810_0 *)effect)->unk_2C = (s16) (((((S_80024810_0 *)effect)->unk_3E & 3) << 5) + 0x80);
    ((S_80024810_0 *)effect)->unk_2E = (s16) (((s32) (((S_80024810_0 *)effect)->unk_3E << 0x10) >> 0x12) << 5);
    phase = ((S_80024810_0 *)effect)->unk_3C;
    switch (phase) {
    case 0:
        ((S_80024810_0 *)effect)->unk_24 = (u16) (((S_80024810_0 *)effect)->unk_04
            + ((s32) ((s16) ((S_80024810_0 *)effect)->unk_24 - (s16) ((S_80024810_0 *)effect)->unk_04) >> 1));
        ((S_80024810_0 *)effect)->unk_26 = (u16) (((S_80024810_0 *)effect)->unk_06
            + ((s32) ((s16) ((S_80024810_0 *)effect)->unk_26 - (s16) ((S_80024810_0 *)effect)->unk_06) >> 1));
        ((S_80024810_0 *)effect)->unk_28 = (s16) (((S_80024810_0 *)effect)->unk_08
            + ((s32) (((S_80024810_0 *)effect)->unk_28 - (s16) ((S_80024810_0 *)effect)->unk_08) >> 1));
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
            object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
        }
        break;
    }
    ((S_80024810_0 *)effect)->unk_3E = (u16) (((S_80024810_0 *)effect)->unk_3E + 1);
}

#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/game_work.h"
int abs(int);
s32 func_80065420();
s32 func_80066640(void *, s32);
s32 func_800666F4(void *);
void transform_rotated_vertices();
typedef struct
{
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
}
E_SVEC;
typedef struct
{
    u16 x;
    u16 y;
}
E_DVEC;
typedef struct
{
    void *p0;
    void *p1;
    s16 f08;
    s16 f0A;
    u16 f0C;
    s16 f0E;
    s16 f10;
    s16 f12;
    s16 f14;
    s16 f16;
    s16 f18;
    s16 f1A;
    s32 f1C;
}
E_PRIM;
/* Emit each chain node's four trail quads into the display list, depth-sorted into the OT. */
s32 update_segment(void *node)
{
    E_SVEC scratch;
    s32 otz[6];
    E_DVEC sxy[6];
    E_PRIM prim;
    s32 p;
    s32 i;
    s32 mid_otz;
    s32 slot_offset;
    GameWork *base;
    void *poly;
    void *parent;
    void *obj;
    int dy;
    u8 colour_a;
    u8 colour_b;
    u8 colour_c;
    u8 colour_d;
    base = &g_game_work;
    do {
        obj = node;
        i = 4;
        do {
            otz[i] = (s32) (func_80065420(((u8 *) obj) + ((i * 8) + 4), &sxy[i], &p, &p) - 8);
            i -= 1;
        }
        while (i >= 0);
        scratch.x = *((u16 *) (((s8 *) obj) + 4));
        scratch.y = *((u16 *) (((s8 *) obj) + 6));
        scratch.z = (u16) ((*((u16 *) (((s8 *) obj) + 8))) + 0x30);
        func_80065420(&scratch, &sxy[5], &p, &p);
        scratch.x = 0;
        scratch.z = 0;
        prim.p1 = &scratch;
        prim.p0 = &scratch;
        prim.f0A = 0;
        prim.f08 = 0;
        prim.f14 = 0;
        prim.f12 = 0;
        prim.f10 = 0;
        prim.f1A = 0;
        prim.f18 = 1;
        dy = (s16) sxy[0].y;
        dy = dy - ((s16) sxy[5].y);
        scratch.y = (u16) abs((s32) dy);
        prim.f0C = *((u16 *) (((s8 *) base) + 0xC8));
        transform_rotated_vertices(&prim, (s16) sxy[5].y);
        for (i = 0; i < 4; i++) {
            poly = *((void **) (((s8 *) (*((void **) (((s8 *) base) + 0)))) + 0x8D0));
            *((void **) (((s8 *) (*((void **) (((s8 *) base) + 0)))) + 0x8D0)) = (void *) (((u8 *) poly) + 0x28);
            *((s32 *) (((s8 *) poly) + 4)) = *((s32 *) (((s8 *) obj) + 0x38));
            func_800666F4(poly);
            func_80066640(poly, 1);
            *((u16 *) (((s8 *) poly) + 0x16)) = (u16) (*((u16 *) (((s8 *) obj) + 0x40)));
            *((u16 *) (((s8 *) poly) + 0xE)) = (u16) (*((u16 *) (((s8 *) obj) + 0x42)));
            *((s16 *) (((s8 *) poly) + 8)) = (s16) (sxy[i].x - scratch.x);
            *((s16 *) (((s8 *) poly) + 0x10)) = (s16) (sxy[i + 1].x - scratch.x);
            *((s16 *) (((s8 *) poly) + 0x18)) = (s16) (sxy[i].x + scratch.x);
            *((s16 *) (((s8 *) poly) + 0x20)) = (s16) (sxy[i + 1].x + scratch.x);
            *((s16 *) (((s8 *) poly) + 0xA)) = (s16) (sxy[i].y - scratch.y);
            *((s16 *) (((s8 *) poly) + 0x1A)) = (s16) (sxy[i].y + scratch.y);
            *((s16 *) (((s8 *) poly) + 0x12)) = (s16) (sxy[i + 1].y - scratch.y);
            *((s16 *) (((s8 *) poly) + 0x22)) = (s16) (sxy[i + 1].y + scratch.y);
            colour_a = *((u8 *) (((s8 *) obj) + 0x2C));
            *((u8 *) (((s8 *) poly) + 0x1C)) = colour_a;
            *((u8 *) (((s8 *) poly) + 0xC)) = colour_a;
            colour_b = (u8) (colour_a + (*((u8 *) (((s8 *) obj) + 0x30))));
            *((u8 *) (((s8 *) poly) + 0x24)) = colour_b;
            *((u8 *) (((s8 *) poly) + 0x14)) = colour_b;
            colour_c = *((u8 *) (((s8 *) obj) + 0x2E));
            *((u8 *) (((s8 *) poly) + 0x25)) = colour_c;
            *((u8 *) (((s8 *) poly) + 0x1D)) = colour_c;
            colour_d = (u8) (colour_c + (*((u8 *) (((s8 *) obj) + 0x32))));
            *((u8 *) (((s8 *) poly) + 0x15)) = colour_d;
            *((u8 *) (((s8 *) poly) + 0xD)) = colour_d;
            mid_otz = (s32) ((otz[i] + otz[i + 1]) >> 1);
            p = mid_otz;
            if (((u32) mid_otz) < 0x1E0U) {
                u32 low_mask = 0xFFFFFF;
                u32 high_mask = 0xFF000000;
                slot_offset = mid_otz * 4;
                *((s32 *) (((s8 *) poly) + 0)) = (s32) (((*((s32 *) (((s8 *) poly) + 0))) & high_mask)
                    | ((*((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (*((void **) (((s8 *) base) + 0))))))
                    + 0xB0))) & low_mask));
                *((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (*((void **) (((s8 *) base) + 0)))))) + 0xB0)) =
                    (s32) (((*((s32 *) (((s8 *) (((u8 *) slot_offset) + ((u32) (*((void **) (((s8 *) base) + 0))))))
                    + 0xB0))) & high_mask) | (((s32) poly) & low_mask));
            }
        }

        parent = *((void **) (((s8 *) node) + (-8)));
        if (parent == 0) {
            break;
        }
        node = (void *) (((u8 *) parent) + 0x20);
    }
    while (1);
    return 0;
}

#include "modules/dungeon_ovl_19c6800.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_819A764C_0_pre {
    u16 unk_00;
} S_819A764C_0_pre;   /* the 0x2 bytes before self in func_819A764C, addressed as self[-1] */

typedef struct S_819A764C_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
    u8 pad_0A[0x1A];
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    u8 pad_2A[0x2];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[0x8];
    s32 unk_38;
    union { s16 s; u16 u; } unk_3C;   /* accessed as both */
    u16 unk_3E;
    u8 pad_40[0x2];
    s16 unk_42;
} S_819A764C_0;   /* self in func_819A764C */

typedef struct S_819A764C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_819A764C_1;   /* inner in func_819A764C */

typedef struct S_819A764C_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
} S_819A764C_2;   /* dst in func_819A764C */

s32 update_segment(void *);
extern u16 func_8006649C(s32, s32);
extern s32 func_80069EF8(void);

/* Update randomized intermediate points and advance the effect state. */
void update_randomized_intermediate_points(void *self)
{
    s16 point_step[3];
    s32 state;
    s32 point_index;
    void *object_base;
    S_819A764C_1 *linked_object;
    void *message;

    linked_object = ((S_819A764C_0 *)self)->unk_00;
    linked_object->unk_52 |= 0x8000;

    point_step[0] = (((S_819A764C_0 *)self)->unk_24 - ((S_819A764C_0 *)self)->unk_04.s) >> 2;
    point_step[1] = (((S_819A764C_0 *)self)->unk_26 - ((S_819A764C_0 *)self)->unk_06.s) >> 2;
    point_step[2] = (((S_819A764C_0 *)self)->unk_28 - ((S_819A764C_0 *)self)->unk_08.s) >> 2;
    point_index = 1;

    do {
        ((S_819A764C_2 *)((u8 *)self + point_index * 8))->unk_04 = ((S_819A764C_0 *)self)->unk_04.u + point_step[0] * point_index
        + (func_80069EF8() & 0x3F) - 0x20;
        ((S_819A764C_2 *)((u8 *)self + point_index * 8))->unk_06 = ((S_819A764C_0 *)self)->unk_06.u + point_step[1] * point_index
        + (func_80069EF8() & 0x3F) - 0x20;
        ((S_819A764C_2 *)((u8 *)self + point_index * 8))->unk_08 = ((S_819A764C_0 *)self)->unk_08.u + point_step[2] * point_index
        - (func_80069EF8() & 0x3F);
        point_index++;
    } while (point_index < 4);

    ((S_819A764C_0 *)self)->unk_2C = ((((S_819A764C_0 *)self)->unk_3E & 3) << 5) + 0x80;
    state = ((S_819A764C_0 *)self)->unk_3C.s;
    ((S_819A764C_0 *)self)->unk_2E = ((s16)((S_819A764C_0 *)self)->unk_3E >> 2) << 5;

    switch (state) {
    case 0:
        object_base = self - 0x20;
        message = update_segment;

        register_node(object_base, message);
    case 1:
        ((S_819A764C_0 *)self)->unk_3E = (func_80069EF8() & 3) + 2;
        ((S_819A764C_0 *)self)->unk_38 += 0xFFF7F7F8;
        ((S_819A764C_0 *)self)->unk_42 = func_8006649C((func_80069EF8() & 0xF) << 4, 0x1F8);
        ((S_819A764C_0 *)self)->unk_3C.u++;
        return;
    case 2:
        ((S_819A764C_0_pre *)self)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
        break;
    }
}
