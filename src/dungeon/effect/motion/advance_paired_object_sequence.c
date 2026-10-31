#include "shared/audio_commands.h"
#include "shared/dungeon_actor_callbacks.h"
#include "dungeon/actor.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80083160.h"
#include "shared/object_links.h"
#include "engine/graphics.h"

typedef struct S_800253C0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 v; s16 n; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x10];
    void * unk_AC;
    void * unk_B0;
} S_800253C0_0;   /* arg0 in advance_paired_object_sequence */

typedef struct S_800253C0_1 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_800253C0_1;   /* arg3 in advance_paired_object_sequence */

typedef struct S_800253C0_3 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_800253C0_3;   /* fa0 in advance_paired_object_sequence */

typedef struct S_800253C0_4 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_4;   /* record in advance_paired_object_sequence */

typedef struct S_800253C0_5_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800253C0_5_pre;   /* the 0x18 bytes before object in advance_paired_object_sequence, addressed as object[-1] */

typedef struct S_800253C0_5 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    union { u16 n; s16 n2; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
    u16 unk_8A;
} S_800253C0_5;   /* object in advance_paired_object_sequence */

typedef struct S_800253C0_8 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800253C0_8;   /* arg2 in advance_paired_object_sequence */

typedef struct S_800253C0_9 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_800253C0_9;   /* prim in advance_paired_object_sequence */

typedef struct S_800253C0_10 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_800253C0_10;   /* arg1 in advance_paired_object_sequence */

typedef struct S_800253C0_11 {
    u32 unk_00;
} S_800253C0_11;   /* amounts in advance_paired_object_sequence */

typedef struct S_800253C0_12 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_12;   /* record2 in advance_paired_object_sequence */

typedef struct S_800253C0_14_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800253C0_14_pre;   /* the 0x18 bytes before other in advance_paired_object_sequence, addressed as other[-1] */

typedef struct S_800253C0_15 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    u32 unk_0C;
    u8 pad_10[0xB8];
    s16 unk_C8;
} S_800253C0_15;   /* tb in advance_paired_object_sequence */

   /* the 0x14 bytes before object2 in advance_paired_object_sequence, addressed as object2[-1] */

typedef struct S_800253C0_17 {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { u32 v; } at00p;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    union { u16 u; s16 s; } unk_12;   /* accessed as both */
    union { s16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800253C0_17;   /* child in advance_paired_object_sequence */

typedef struct S_800253C0_18 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800253C0_18;   /* (void *)((i << 2) + (s32)arg0) in advance_paired_object_sequence */


extern void *cd_cue_base[];
extern u8 D_800DD148[];
extern u8 D_800DD150[];
extern u8 D_80025000[];
extern u8 D_80025024[];
extern u8 D_80025028[];
extern u8 D_80025068[];
extern u8 D_800287F0[];

extern void sound_set_cd_cue_parameters(void *, void *, void *, s32);
extern s32 read_stream_cue_start_offset(void);
extern void Control_CD(s32,void *, s32);

extern void play_sound_if_enabled(s32);
extern void *create_and_link_six_offset_objects(s16, s16, s16, void *);
extern void *create_six_offset_effects(void *, void *, void *, void *);
#include "dungeon/effect/screen.h"
#include "dungeon/actor/object.h"
#include "engine/scene.h"

extern void process_adjacent_objects_with_gray_nodes(void *, void *);
extern void *get_unused_text_buffer(void);
extern void *write_text_byte_and_advance(s8 value, s8 *dest);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern u8 *clear_byte_and_advance(u8 *byte_ptr);
extern void * write_status_prefix_bytes(void *);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void *create_linked_objects(void *, void *, s32, s16);
extern void *create_positioned_graphic_object(s16 x, s16 y, s16 z, s16 graphic_index, s32 state_value);
extern void *merge_creature_abilities_and_state(void *, void *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void * build_status_effect_name_list(void *, void *);
extern void *create_four_groups_of_angular_effects(s16, s16, s16, s32);


/* Advance the paired-object sequence, animating both objects and displaying the result. */
void advance_paired_object_sequence(void *sequence, void *position, void *actor, void *owner)
{
    void *message_id;
    GameWork *scene = &g_game_work;
    u8 *anim_entry;
    u8 state;
    u32 result_flags;
    void *object_slot;
    u8 brightness;
    s16 timer;
    s32 delta;
    GameWork *move_scene;
    s16 *table_x;
    s16 *table_y;

    state = ((S_800253C0_0 *)sequence)->unk_9B.n;
    switch (state) {
        s32 coord_delta;
        s32 slot_value;
        u8 * page_cursor;
        void *object_m;
        S_800253C0_17 *child;
        void *message_text;
        s32 object_index_m;
        s32 old_x;
        S_800253C0_9 *prim_m;
        s32 table_index_m;
    case 0:
        if (((S_800253C0_0 *)sequence)->unk_AC == 0 || ((S_800253C0_0 *)sequence)->unk_B0 == 0) {
            ((S_800253C0_0 *)sequence)->unk_9B.n = 13;
            return;
        }
        {
            void *sound_data = *&cd_cue_base[0];
            sound_set_cd_cue_parameters(0, sound_data, 0, 0x1000530);
        }
        {
            s32 cd_value = read_stream_cue_start_offset();
            Control_CD(21, cd_value, 0);
        }
        state = ((S_800253C0_0 *)sequence)->unk_9B.n;
        ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
        return;

    case 1:
    {
        s32 index;
        GameWork *turn_scene;
        u16 old_angle;

        turn_scene = &g_game_work;
        old_angle = ((S_800253C0_1 *)owner)->unk_2A.u;
        index = ((turn_scene->view.camera_rotation.parts.viewAngle +
            ((S_800253C0_1 *)owner)->unk_2A.s + 0x100) >> 9) & 7;
        if (index == 2) {
            ((S_800253C0_3 *)actor)->unk_2C = D_800DD148;
            anim_entry = D_800DD148 + ((((turn_scene->view.camera_rotation.parts.viewAngle +
                ((S_800253C0_1 *)owner)->unk_2A.s) + 0x100) >> 9) & 7);
            set_sprite_animation_frame(actor, *anim_entry, 0, 1);
            ((S_800253C0_0 *)sequence)->unk_9B.n = ((S_800253C0_0 *)sequence)->unk_9B.n + 1;
            return;
        }
        ((S_800253C0_1 *)owner)->unk_2A.s = old_angle + 0x200;
        return;
    }

    case 2:
    {

        object_index_m = 0;
        slot_value = 0x20000000;
        message_text = sequence;

        do {
            object_m = ((S_800253C0_4 *)message_text)->unk_AC;
            if ((((S_800253C0_5 *)object_m)->unk_14 & slot_value) != 0) {
                begin_actor_flagged_action(object_m, ((S_800253C0_5_pre *)object_m)[-1].unk_00,
                    ((S_800253C0_5_pre *)object_m)[-1].unk_04, object_m);
            }
            object_index_m++;
            message_text += 4;
        } while (object_index_m < 2);
    }
        state = ((S_800253C0_0 *)sequence)->unk_9B.n;
        ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
        return;

    case 3:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        {

            u32 mask;
            void *child_slot;
            object_index_m = 0;
            mask = 0x100000;
            child_slot = sequence;
            do {
                u16 angle;
                object_m = ((S_800253C0_4 *)child_slot)->unk_AC;
                child_slot = (u8 *)child_slot + 4;
                object_index_m++;
                ((S_800253C0_5 *)object_m)->unk_14 |= mask;
                angle = ((S_800253C0_5 *)object_m)->unk_2A.n;
                ((S_800253C0_5 *)object_m)->unk_8A = angle;
            } while (object_index_m < 2);
        }

        ((S_800253C0_0 *)sequence)->unk_9B.n++;
        ((S_800253C0_0 *)sequence)->unk_96.v = 32;
case 4:
        brightness = scene->view.tint.parts.tint_r;
        timer = ((S_800253C0_0 *)sequence)->unk_96.n;
        delta = (32 - brightness) / timer;
        brightness = brightness + delta;
        message_text = (u8 *)scene + 0xA8;
        object_index_m = 0;
        object_slot = sequence;
        move_scene = &g_game_work;
        table_x = (s16 *)((s8 *)dir_step_x);
        table_y = (s16 *)((s8 *)dir_step_y);
        scene->view.tint.parts.tint_r = brightness;
        ((u8 *)message_text)[1] = brightness;
        ((u8 *)message_text)[2] = brightness;
        do {
            s32 step_delta;
            s32 frames_left;
            s32 coord;
            s32 coord_y;
            s32 previous_x;
            s32 old_y;

            table_index_m = (object_index_m << 11) - move_scene->view.camera_rotation.parts.viewAngle;
            object_m = ((S_800253C0_4 *)object_slot)->unk_AC;
            table_index_m += 0x100;
            table_index_m >>= 8;
            table_index_m &= 0xE;
            coord = (s32)((S_800253C0_8 *)actor)->unk_24 + table_x[table_index_m >> 1];
            frames_left = ((S_800253C0_0 *)sequence)->unk_96.n;
            coord = coord << 6;
            prim_m = ((S_800253C0_5_pre *)object_m)[-1].unk_00;
            previous_x = prim_m->unk_02.s - 0x20;
            coord = coord - previous_x;
            prim_m->unk_02.u = prim_m->unk_02.u + coord / frames_left;
            coord_y = (s32)((S_800253C0_8 *)actor)->unk_25;
            {
                coord_y = coord_y + table_y[table_index_m >> 1];
            }
            coord_y = coord_y << 6;
            old_y = prim_m->unk_06.s - 0x20;
            coord_y = coord_y - old_y;
            prim_m->unk_06.u = prim_m->unk_06.u +
                coord_y / ((S_800253C0_0 *)sequence)->unk_96.n;
            {
                s32 old_z = prim_m->unk_0A.s;
                s32 z_delta = ((S_800253C0_10 *)position)->unk_0A.s - old_z;
                prim_m->unk_0A.u = prim_m->unk_0A.u +
                    z_delta / ((S_800253C0_0 *)sequence)->unk_96.n;
            }

            {
                s32 angle = move_scene->view.camera_rotation.parts.viewAngle + ((S_800253C0_5 *)object_m)->unk_2A.n2;
                u16 old_angle = ((S_800253C0_5 *)object_m)->unk_2A.n;
                if ((((angle + 0x100) >> 9) & 7) != 2) {
                    ((S_800253C0_5 *)object_m)->unk_2A.n = old_angle + 0x200;
                }
            }
            object_index_m++;
            object_slot = (u8 *)object_slot + 4;
        } while (object_index_m < 2);
        timer = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
        ((S_800253C0_0 *)sequence)->unk_96.n = timer;
        if (timer > 0) {
            return;
        }
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        {
            GameWork *snap_scene;
            s16 *snap_x;
            s16 *snap_y;
            void *final_slot;
            ((S_800253C0_11 *)(u8 *)message_text)->unk_00 = 0x2C202020;
            object_index_m = 0;
            snap_scene = &g_game_work;
            snap_x = (s16 *)((s8 *)dir_step_x);
            snap_y = (s16 *)((s8 *)dir_step_y);
            final_slot = sequence;
            do {
                s32 table_index = (object_index_m << 11) - snap_scene->view.camera_rotation.parts.viewAngle;
                s32 x;
                s32 y;
                table_index += 0x100;
                table_index >>= 8;
                object_m = ((S_800253C0_12 *)final_slot)->unk_AC;
                table_index &= 0xE;
                x = (s32)((S_800253C0_8 *)actor)->unk_24 + snap_x[table_index >> 1];
                prim_m = ((S_800253C0_5_pre *)object_m)[-1].unk_00;
                prim_m->unk_02.s = (x << 6) + 0x20;
                y = (s32)((S_800253C0_8 *)actor)->unk_25 + snap_y[table_index >> 1];
                prim_m->unk_06.s = (y << 6) + 0x20;
                prim_m->unk_0A.u = ((S_800253C0_10 *)position)->unk_0A.u;
                final_slot = (u8 *)final_slot + 4;
                object_index_m++;
            } while (object_index_m < 2);
            {
                coord_delta = 16;
                state = ((S_800253C0_0 *)sequence)->unk_9B.v;
                ((S_800253C0_0 *)sequence)->unk_96.n = coord_delta;
            }
        }
        ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
        return;

    case 5:
    {
        s16 ticks = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
        ((S_800253C0_0 *)sequence)->unk_96.n = ticks;
        if (ticks > 0) {
            return;
        }
        create_and_link_six_offset_objects(((S_800253C0_10 *)position)->unk_02, ((S_800253C0_10 *)position)->unk_06,
            ((S_800253C0_10 *)position)->unk_0A.s, actor);
        {
            coord_delta = 32;
            state = ((S_800253C0_0 *)sequence)->unk_9B.v;
            ((S_800253C0_0 *)sequence)->unk_96.n = coord_delta;
        }
        ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
        return;
    }

    case 6:
    {
        s16 ticks = ((S_800253C0_0 *)sequence)->unk_96.n - 1;

        ((S_800253C0_0 *)sequence)->unk_96.n = ticks;
        if (ticks > 0) {
            return;
        }
        object_index_m = 0;
        page_cursor = sequence;
        do {
            void *call_position = position;
            void *call_actor = actor;
            object_m = ((S_800253C0_4 *)(void *)page_cursor)->unk_AC;
            create_six_offset_effects(call_position, ((S_800253C0_5_pre *)object_m)[-1].unk_00, object_m, call_actor);
            page_cursor += 4;
            object_index_m++;
        } while (object_index_m < 2);
        {
            GpuRectBuffer texture_rect;
            ((S_800253C0_0 *)sequence)->unk_9B.n++;
            ((S_800253C0_0 *)sequence)->unk_96.n = 60;
            texture_rect.halves[0] = 0x340;
            texture_rect.halves[1] = 0x180;
            texture_rect.halves[3] = 0x40;
            texture_rect.halves[2] = 0x40;
            draw_textured_ellipse(D_800287F0, &texture_rect.rect, 1, 0);
        }
        return;
    }

    case 7:
        process_adjacent_objects_with_gray_nodes(((S_800253C0_0 *)sequence)->unk_AC, ((S_800253C0_0 *)sequence)->unk_B0);
        {
            s16 ticks = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            ((S_800253C0_0 *)sequence)->unk_96.n = ticks;
            if (ticks > 0) {
                return;
            }
            {
                coord_delta = 8;
                state = ((S_800253C0_0 *)sequence)->unk_9B.n;
                ((S_800253C0_0 *)sequence)->unk_96.n = coord_delta;
            }
            ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
            return;
        }

    case 8:
        process_adjacent_objects_with_gray_nodes(((S_800253C0_0 *)sequence)->unk_AC, ((S_800253C0_0 *)sequence)->unk_B0);
        {
            s16 ticks = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
            ((S_800253C0_0 *)sequence)->unk_96.n = ticks;
            if (ticks > 0) {
                return;
            }
        }
        if (has_enough_available_runtime_nodes(13) == 0) {
            return;
        }
        {
            long work = (long)&g_game_work;
            long step_x = (long)dir_step_x;
            long step_y = (long)dir_step_y;
            message_id = get_unused_text_buffer();
            message_text = write_text_byte_and_advance(8, message_id);
            message_text = append_entity_display_text(((S_800253C0_0 *)sequence)->unk_AC, message_text);
            message_text = expand_text_control_codes(D_80025000, message_text);
            message_text = append_entity_display_text(((S_800253C0_0 *)sequence)->unk_B0, message_text);
            message_text = expand_text_control_codes(D_80025024, message_text);
            {
                object_m =
                    select_object_by_flags_and_keys(((S_800253C0_0 *)sequence)->unk_AC,
                    ((S_800253C0_0 *)sequence)->unk_B0,
                    &result_flags);
                ((S_800253C0_1 *)owner)->unk_60 = object_m;
                if (object_m != 0) {
                    void *other;
                    S_800253C0_4 *child_slot;
                    object_index_m = 0;
                    do {
                        child_slot = (S_800253C0_4 *)((u8 *)sequence + object_index_m * sizeof(void *));
                        slot_value = (s16)object_index_m;
                        other = child_slot->unk_AC;
                        create_linked_objects(((S_800253C0_14_pre *)other)[-1].unk_00, other,
                            slot_value, object_m == other);
                        if (object_m == child_slot->unk_AC) {
                            s32 angle;
                            s32 index;
                            s32 x;
                            s32 y;
                            angle = ((S_800253C0_15 *)work)->unk_C8;
                            angle = -angle;
                            index = ((angle + 0x500) >> 8) & 0xE;
                            x = ((S_800253C0_8 *)actor)->unk_24 + *(s16 *)(index + step_x);
                            y = ((S_800253C0_8 *)actor)->unk_25 + *(s16 *)(index + step_y);
                            create_positioned_graphic_object((s16)((x << 6) + 0x20),
                                (s16)((y << 6) + 0x20),
                                ((S_800253C0_1 *)owner)->unk_88, slot_value, object_m);
                        }
                        object_index_m++;
                    } while (object_index_m < 2);
                    {

                        register s32 sprite_x;
                        register s32 sprite_flags;
                        void *final_slot;
                        object_index_m = 0;
                        sprite_x = 32;
                        sprite_flags = 12;
                        final_slot = sequence;
                        do {

                            u16 child_y;
                            object_m = ((S_800253C0_12 *)final_slot)->unk_AC;
                            other = ((SpriteLinkPrefixView *)object_m)[-1].sprite;
                            child_y = ((S_800253C0_17 *)other)->unk_12.u;
                            ((S_800253C0_17 *)other)->unk_10 = sprite_x;
                            ((S_800253C0_17 *)other)->unk_14.s = sprite_flags;
                            ((S_800253C0_17 *)other)->unk_12.s = child_y - 128;
                            final_slot = (u8 *)final_slot + 4;
                            object_index_m++;
                        } while (object_index_m < 2);
                    }
                    ((S_800253C0_0 *)sequence)->unk_96.n = 38;
                    ((S_800253C0_0 *)sequence)->unk_9B.n++;
                } else {
                    message_text = write_text_byte_and_advance(10, message_text);
                    message_text = expand_text_control_codes(D_80025028, message_text);
                    ((S_800253C0_0 *)sequence)->unk_96.n = 32;
                    ((S_800253C0_0 *)sequence)->unk_9B.n += 2;
                }
            }
            clear_byte_and_advance(message_text);
            display_text_with_fullwidth_adjustment(message_id);
            return;
        }

    case 9:
        process_adjacent_objects_with_gray_nodes(((S_800253C0_0 *)sequence)->unk_AC, ((S_800253C0_0 *)sequence)->unk_B0);
        {
            void *child_slot = sequence;
            object_index_m = 0;
            do {

                u32 red;
                u32 green;
                u32 blue;
                object_m = ((S_800253C0_4 *)child_slot)->unk_AC;
                child = ((S_800253C0_5_pre *)object_m)[-1].unk_04;
                red = child->unk_0C.at00.v;
                green = child->unk_0C.at01.v;
                child->unk_0C.at00.v = red - (red >> 1);
                child->unk_0C.at01.v = green - (green >> 1);
                blue = child->unk_0C.at02.v;
                child->unk_0C.at02.v = blue - (blue >> 1);
                if (child->unk_0C.at00.v < 5) {
                    child->unk_0C.at02.v = 0;
                    child->unk_0C.at01.v = 0;
                    child->unk_0C.at00.v = 0;
                }
                object_index_m++;
                child_slot = (u8 *)child_slot + 4;
            } while (object_index_m < 2);
            {
                s16 ticks = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
                ((S_800253C0_0 *)sequence)->unk_96.n = ticks;
                if (ticks > 0) {
                    return;
                }
            }
        }
        {
            object_m = ((S_800253C0_1 *)owner)->unk_60;
            if (object_m != 0) {
                void **first_slot;
                void **text_slot;
                void **removed_slot;

                message_id = get_unused_text_buffer();
                first_slot = (void **)((u8 *)sequence + 0xAC);
                text_slot = first_slot;
                if (*first_slot != object_m) {
                    text_slot = (void **)((u8 *)sequence + 0xB0);
                }
                message_text = message_id;
                message_text = append_entity_display_text(*text_slot, message_text);
                message_text = expand_text_control_codes(D_80025068, message_text);
                text_slot = first_slot;
                if (*first_slot == object_m) {
                    text_slot = (void **)((u8 *)sequence + 0xB0);
                }
                message_text = append_entity_display_text(*text_slot, message_text);
                message_text = expand_text_control_codes(D_80025024, message_text);
                message_text = write_status_prefix_bytes(message_text);
                message_text = clear_byte_and_advance(message_text);
                message_text = write_text_byte_and_advance(17, message_text);
                display_text_with_fullwidth_adjustment(message_id);
                object_m = merge_creature_abilities_and_state(((S_800253C0_0 *)sequence)->unk_AC,
                    ((S_800253C0_0 *)sequence)->unk_B0, 0);
                removed_slot = first_slot;
                if (*first_slot == object_m) {
                    removed_slot = (void **)((u8 *)sequence + 0xB0);
                }
                *removed_slot = 0;
                message_id = get_unused_text_buffer();
                message_text = build_status_effect_name_list(object_m, message_id);
                message_text = clear_byte_and_advance(message_text);
                display_text_with_fullwidth_adjustment(message_id);
            }
        }
        {
            GameWork *restore_scene;
            s16 *row_x;
            object_index_m = 0;
            restore_scene = &g_game_work;
            row_x = (s16 *)((s8 *)dir_step_x);
loop_7:
            {
                object_m =
                    ((S_800253C0_18 *)((void *)((object_index_m << 2) + (long)sequence)))->unk_AC;
                if (object_m != 0) {
                    s32 index;
                    u8 *y_table;
                    s32 effect_size;
                    s32 x;
                    s32 y;
                    s32 z;
                    prim_m = ((S_800253C0_5_pre *)object_m)[-1].unk_00;
                    child = ((S_800253C0_5_pre *)object_m)[-1].unk_04;
                    child->unk_0C.at00p.v = 0x808080;
                    child->unk_10 = 0;
                    child->unk_12.u &= 0x3F;
                    child->unk_14.u &= 0xFFF3;
                    index = (((-restore_scene->view.camera_rotation.parts.viewAngle + 0x500) >> 8) & 0xE);
                    x = ((S_800253C0_8 *)actor)->unk_24 + row_x[index >> 1];
                    prim_m->unk_02.s = (x << 6) + 0x20;
                    effect_size = 16;
                    y_table = (u8 *)((s8 *)dir_step_y);
                    y = ((S_800253C0_8 *)actor)->unk_25 + *(s16 *)((s32)(index + (s32)y_table));
                    prim_m->unk_06.s = (y << 6) + 0x20;
                    z = ((S_800253C0_10 *)position)->unk_0A.u;
                    prim_m->unk_0A.u = z;
                    create_four_groups_of_angular_effects(prim_m->unk_02.s, prim_m->unk_06.s,
                        (s16)(z - 0x20), effect_size);
                }
                object_index_m++;
            }
            if (object_index_m < 2)
                goto loop_7;
            {
                coord_delta = 64;
                state = ((S_800253C0_0 *)sequence)->unk_9B.v;
                ((S_800253C0_0 *)sequence)->unk_96.n = coord_delta;
            }
            ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
            return;
        }

    case 10:
    {
        s16 ticks = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
        ((S_800253C0_0 *)sequence)->unk_96.n = ticks;
        if (ticks > 0) {
            return;
        }
        {
            coord_delta = 32;
            state = ((S_800253C0_0 *)sequence)->unk_9B.v;
            ((S_800253C0_0 *)sequence)->unk_96.n = coord_delta;
        }
        ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
        return;
    }

    case 11:
    {
        void *child_slot;
        s32 target_level;
        register void *final_slot;
        s16 ticks;
        s32 step;
        s32 shade;
        s32 old_coord;
        s32 step_delta;
        s32 x;
        s32 current_angle;
        u16 old_angle;
        u32 saved_angle;
        register u32 clear_flags;

        step = (128 - scene->view.tint.parts.tint_r) / ((S_800253C0_0 *)sequence)->unk_96.n;
        page_cursor = ((u8 *)scene + 0xA8);
        object_index_m = 0;
        child_slot = sequence;
        shade = scene->view.tint.parts.tint_r + step;
        scene->view.tint.parts.tint_r = shade;
        (page_cursor)[2] = shade;
        (page_cursor)[1] = shade;
        do {
            object_m = ((S_800253C0_4 *)child_slot)->unk_AC;
            if (object_m != 0) {
                child = ((S_800253C0_5_pre *)object_m)[-1].unk_04;
                prim_m = ((S_800253C0_5_pre *)object_m)[-1].unk_00;
                {
                    s32 coord;
                    coord = (s32)child->unk_24;
                    coord = coord << 6;
                    old_x = prim_m->unk_02.s - 0x20;
                    coord = coord - old_x;
                    prim_m->unk_02.u = prim_m->unk_02.u +
                        coord / ((S_800253C0_0 *)sequence)->unk_96.n;
                }
                {
                    s32 y;
                    s32 old_y;
                    y = (s32)child->unk_25;
                    y = y << 6;
                    old_y = prim_m->unk_06.s - 0x20;
                    y = y - old_y;
                    prim_m->unk_06.u = prim_m->unk_06.u +
                        y / ((S_800253C0_0 *)sequence)->unk_96.n;
                }
                {
                    s32 old_z = prim_m->unk_0A.s;
                    s32 z_delta = ((S_800253C0_5 *)object_m)->unk_88.s - old_z;
                    prim_m->unk_0A.u = prim_m->unk_0A.u +
                        z_delta / ((S_800253C0_0 *)sequence)->unk_96.n;
                }
                saved_angle = ((S_800253C0_5 *)object_m)->unk_8A;
                ((S_800253C0_5 *)object_m)->unk_2A.n =
                    ((S_800253C0_5 *)object_m)->unk_2A.n & 0xFFF;
                saved_angle = saved_angle & 0xFFF;
                ((S_800253C0_5 *)object_m)->unk_8A = saved_angle;
                current_angle = ((S_800253C0_5 *)object_m)->unk_2A.n2;
                old_angle = ((S_800253C0_5 *)object_m)->unk_2A.n;
                if (current_angle != (s16)saved_angle) {
                    ((S_800253C0_5 *)object_m)->unk_2A.n = old_angle + 0x200;
                }
            }
            object_index_m++;
            child_slot = (u8 *)child_slot + 4;
        } while (object_index_m < 2);
        ticks = ((S_800253C0_0 *)sequence)->unk_96.n - 1;
        ((S_800253C0_0 *)sequence)->unk_96.n = ticks;
        if (ticks > 0) {
            return;
        }
        ((S_800253C0_11 *)page_cursor)->unk_00 = 0x2C808080;
        object_index_m = 0;
        clear_flags = 0xFFEFFFFF;
        final_slot = sequence;
        do {
            object_m = ((S_800253C0_12 *)final_slot)->unk_AC;
            if (object_m != 0) {
                child = ((S_800253C0_5_pre *)object_m)[-1].unk_04;
                x = child->unk_24;
                prim_m = ((S_800253C0_5_pre *)object_m)[-1].unk_00;
                prim_m->unk_02.s = (x << 6) + 0x20;
                prim_m->unk_06.s = ((s32)child->unk_25 << 6) + 0x20;
                prim_m->unk_0A.u = ((S_800253C0_5 *)object_m)->unk_88.u;
                ((S_800253C0_5 *)object_m)->unk_14 &= clear_flags;
            }
            object_index_m++;
            final_slot = (u8 *)final_slot + 4;
        } while (object_index_m < 2);
        state = ((S_800253C0_0 *)sequence)->unk_9B.n;
        ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
        return;
    }

    case 12:
        ((S_800253C0_3 *)actor)->unk_2C = D_800DD150;
        anim_entry = D_800DD150 + ((((g_game_work.view.camera_rotation.parts.viewAngle +
            ((S_800253C0_1 *)owner)->unk_2A.s) + 0x100) >> 9) & 7);
        set_sprite_animation_frame(actor, *anim_entry, 0, 1);
        state = ((S_800253C0_0 *)sequence)->unk_9B.n;
        ((S_800253C0_0 *)sequence)->unk_9B.n = state + 1;
        return;

    case 13:
        if ((((S_800253C0_8 *)actor)->unk_14 & 0xE000) == 0) {
            return;
        }
        {
            u16 value;
            value = g_dungeon_status.flags;
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.flags = value | 0x812;
        }
        ((S_800253C0_0 *)sequence)->unk_8C =handle_player_input;

    }
    return;
}
