/* Complete native TU in retail file order. Review pending. */
#include "dungeon/system/util.h"
#include "common.h"

extern s16 D_800E3CCE;

/* Increment the counter up to 32 and report whether it advanced. */
s32 increment_bounded_counter(void) {
    if (D_800E3CCE < 0x20) {
        D_800E3CCE++;
        return 1;
    }
    return 0;
}
#include "common.h"

extern s16 D_800E3CCE;

/* Decrement the counter if it is nonzero. */
void decrement_bounded_counter(void) {
    if (D_800E3CCE != 0) {
        D_800E3CCE = (u16) D_800E3CCE - 1;
    }
}
#include "common.h"
#include "shared/sys_flags.h"

extern s16 SD_Call(s32 query_value);

/* Query the low 16 bits of the input unless flag bit 1 disables the call. */
s32 play_sound_if_enabled(s32 query_value) {
    s32 result;

    if (system_update_flags & 2) {
        result = 0;
    } else {
        result = SD_Call(query_value & 0xFFFF);
    }
    return result;
}
#include "common.h"
#include "shared/sys_flags.h"

extern s32 enqueue_runtime_pool_script(s8 *text);

typedef struct S_800A5720_0 {
    u8 unk_00;
    u8 unk_01;
} S_800A5720_0;

/* When enabled, uppercase a fullwidth Latin letter after the ASCII prefix and process the text. */
s32 display_text_with_fullwidth_adjustment(s8 *text) {
    s8 *cursor;
    u8 trail_byte;

    if (!(system_update_flags & 2)) {
        cursor = text;
        if (*text > 0) {
            do {
                cursor += 1;
            } while (*cursor > 0);
        }
        if (((S_800A5720_0 *)cursor)->unk_00 == 0x82) {
            trail_byte = ((S_800A5720_0 *)cursor)->unk_01;
            if ((u32) ((trail_byte + 0x7F) & 0xFF) < 0x1AU) {
                ((S_800A5720_0 *)cursor)->unk_01 = (u8) (trail_byte - 0x21);
            }
        }
        return enqueue_runtime_pool_script(text);
    }
    return 0;
}
#include "common.h"

/* Return the first of three entries matching the target's group, or -1. */
s32 find_slot_by_item_group(void *entry, s16 target) {
    s32 index;

    index = 0;
    do {
        u8 value = *((u8 *)entry + 8);

        if (value != 0 && (target - 1) / 3 == (value - 1) / 3) {
            return (s16)index;
        }
        index++;
        entry = (u8 *)entry + 3;
    } while (index < 3);
    return -1;
}
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

typedef struct GlobalState {
    s32 pad0;
    u16 flags;
    u8 pad6[6];
} GlobalState;


extern s32 func_800644B8(s32);

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Fades and pulses the effect, restoring the linked primitive when the fade ends. */
void update_pulsing_effect_brightness(void *effect, s32 unused, void *render_state)
{
    s32 fade_step;
    s32 brightness;
    s32 pulse_scale;
    s16 current_brightness;
    u16 tilt;
    void *linked_prim;
    GameWork *global_state = &g_game_work;

    if (S16_AT(effect, 0x64) == 0) {
        if (global_state->unk_004 & 1) {
            brightness = (s16)U16_AT(effect, 0x6A) >> 1;
        } else {
            current_brightness = U16_AT(effect, 0x6A);
            U16_AT(effect, 0x6A) =
                U16_AT(effect, 0x6A) + (192 - current_brightness) / S16_AT(effect, 0x66);
            brightness = U8_AT(effect, 0x6A);
        }
        U8_AT(render_state, 0xE) = brightness;
        U8_AT(render_state, 0xD) = brightness;
        U8_AT(render_state, 0xC) = brightness;

        U16_AT(effect, 0x66)--;
        if (S16_AT(effect, 0x66) <= 0) {
            U16_AT(effect, 0x66) = 16;
            U16_AT(effect, 0x64)++;
        }
    } else {
        if (global_state->unk_004 & 1) {
            S32_AT(render_state, 0xC) = 0;
        } else {
            fade_step = S16_AT(effect, 0x6A) / S16_AT(effect, 0x66);
            U16_AT(effect, 0x6A) -= fade_step;
            brightness = U8_AT(effect, 0x6A);
            U8_AT(render_state, 0xE) = brightness;
            U8_AT(render_state, 0xD) = brightness;
            U8_AT(render_state, 0xC) = brightness;
        }

        U16_AT(effect, 0x66)--;
        if (S16_AT(effect, 0x66) <= 0) {
            linked_prim = *(void **)((u8 *)(*(void **)((u8 *)effect + 4)) - 0x14);
            U8_AT(linked_prim, 0xC) = 0x80;
            U8_AT(linked_prim, 0xD) = 0x80;
            U8_AT(linked_prim, 0xE) = 0x80;
            U16_AT(effect, -2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
    }

    U16_AT(effect, 0x68)++;
    pulse_scale = (func_800644B8((s16)U16_AT(effect, 0x68) << 9) >> 4) + 0x1000;
    S16_AT(render_state, 0x1C) = pulse_scale;
    S16_AT(render_state, 0x1E) = pulse_scale;

    tilt = 0xFFC0;
    if (U16_AT(effect, 0x68) & 1) {
        tilt = 64;
    }
    S16_AT(render_state, 0x1A) = tilt;

    brightness = ((U16_AT(effect, 0x68) & 3) << 4) + 64;
    linked_prim = *(void **)((u8 *)(*(void **)((u8 *)effect + 4)) - 0x14);
    U8_AT(linked_prim, 0xC) = brightness;
    U8_AT(linked_prim, 0xD) = brightness;
    U8_AT(linked_prim, 0xE) = brightness;
}
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

void *allocate_list_node();            /* extern */
s32 register_node();           /* extern */
s32 play_sound_if_enabled();                     /* extern */
void draw_textured_ellipse(); /* extern */
extern M2C_UNK D_800A5828;
extern M2C_UNK D_800DD854;
extern M2C_UNK D_800DD860;

typedef struct S_800A5A18_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800A5A18_0;

typedef struct S_800A5A18_1 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_800A5A18_1;

typedef struct S_800A5A18_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_800A5A18_2;

/* Creates an object and initializes its attached data and resources. */
void *create_textured_ellipse_effect(s32 object_id, s32 state_value) {
    s32 resource_params[2];
    void *object;
    S_800A5A18_1 *render_data;
    S_800A5A18_2 *state_data;

    object = allocate_list_node(0x212, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        ((S_800A5A18_0 *)object)->unk_10 = &D_800A5828;
        register_node(object, project_sprite_chain);
        render_data = ((S_800A5A18_0 *)object)->unk_0C;
        ((S_800A5A18_0 *)object)->unk_08 = object_id;
        render_data->unk_08 = &D_800DD854;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        state_data = object + 0x20;
        state_data->unk_04 = state_value;
        state_data->unk_66 = 4;
        resource_params[0] = 0x01800340;
        resource_params[1] = 0x400040;
        draw_textured_ellipse(&D_800DD860, resource_params, 1, 0);
        play_sound_if_enabled(0x60F);
    }
    return object;
}
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"


typedef struct S_800A5AF0_0_pre {
    u16 unk_00;
} S_800A5AF0_0_pre;   /* the 0x2 bytes before arg0 in update_effect_position_and_scale_transition, addressed as arg0[-1] */

typedef struct S_800A5AF0_0 {
    u8 pad_00[0x4];
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    s16 unk_06;
    s16 unk_08;
} S_800A5AF0_0;   /* arg0 in update_effect_position_and_scale_transition */

typedef struct S_800A5AF0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800A5AF0_1;   /* arg1 in update_effect_position_and_scale_transition */

typedef struct S_800A5AF0_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
} S_800A5AF0_2;   /* arg2 in update_effect_position_and_scale_transition */

/* Interpolate effect values, hold briefly, then fade the colors and mark completion. */
void update_effect_position_and_scale_transition(void *transition, S_800A5AF0_1 *output, S_800A5AF0_2 *appearance) {
    s16 divisor;
    s16 timer;
    s16 state;
    u16 level;
    u16 next_state; /* MATCH: Both arms merge the updated state in retail's $v0. */

    state = ((S_800A5AF0_0 *)transition)->unk_04.s;
    if (state == 0) {
        output->unk_02 = (s16)(
            (u16)output->unk_02 +
            ((s32)(((S_800A5AF0_0 *)transition)->unk_08 - output->unk_02) /
             (s16)((S_800A5AF0_0 *)transition)->unk_06));

        level = appearance->unk_1C;
        divisor = ((S_800A5AF0_0 *)transition)->unk_06;
        appearance->unk_1C =
            (u16)(level + ((s32)(0x1000 - level) / divisor));

        timer = (u16)((S_800A5AF0_0 *)transition)->unk_06 - 1;
        ((S_800A5AF0_0 *)transition)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            ((S_800A5AF0_0 *)transition)->unk_06 = 0x30;
            appearance->unk_1C = 0x1000;
            ((S_800A5AF0_0 *)transition)->unk_04.u = ((S_800A5AF0_0 *)transition)->unk_04.u + 1;
        }
    } else if (state == 1) {
        if (((s32)g_game_work.pressed_buttons) != 0) {
            ((S_800A5AF0_0 *)transition)->unk_06 = 0;
        }

        timer = (u16)((S_800A5AF0_0 *)transition)->unk_06 - 1;
        ((S_800A5AF0_0 *)transition)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            next_state = ((S_800A5AF0_0 *)transition)->unk_04.u;

            ((S_800A5AF0_0 *)transition)->unk_06 = 0x20;
            next_state = next_state + 1;
            ((S_800A5AF0_0 *)transition)->unk_04.u = next_state;
        }
    } else {
        appearance->unk_0E = (u8)(
            appearance->unk_0E -
            ((s32)appearance->unk_0E / (s16)((S_800A5AF0_0 *)transition)->unk_06));
        appearance->unk_0D = (u8)(
            appearance->unk_0D -
            ((s32)appearance->unk_0D / (s16)((S_800A5AF0_0 *)transition)->unk_06));
        appearance->unk_0C = (u8)(
            appearance->unk_0C -
            ((s32)appearance->unk_0C / (s16)((S_800A5AF0_0 *)transition)->unk_06));

        timer = (u16)((S_800A5AF0_0 *)transition)->unk_06 - 1;
        ((S_800A5AF0_0 *)transition)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            ((S_800A5AF0_0_pre *)transition)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
extern int abs(int);


typedef struct S_800A5C70_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A5C70_0_pre;   /* the 0x14 bytes before cursor in check_action_available_without_nearby_actor, addressed as cursor[-1] */

typedef struct S_800A5C70_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_800A5C70_0;   /* cursor in check_action_available_without_nearby_actor */

typedef struct S_800A5C70_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A5C70_1;   /* coords in check_action_available_without_nearby_actor */

typedef struct S_800A5C70_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A5C70_2;   /* other in check_action_available_without_nearby_actor */

/* Checks buttons and state, rejecting eligible entries within four tiles on both axes. */
s32 check_action_available_without_nearby_actor(void) {
    u16 buttons;
    TileObject *origin_coords;
    void **entry_addr;
    void *entry;
    void *first_entry;
    S_800A5C70_2 *entry_coords;

    entry_addr = &dungeon_actor_ring_anchor;
    buttons = system_update_flags;
    entry = *entry_addr;
    if (buttons & 2) {
        return 1;
    }
    if (buttons & 9) {
        return 0;
    }
    if (dungeon_floor_flags & 0x200000) {
        return 0;
    }

    origin_coords = &reference_tile_object;
    first_entry = entry;
    do {
        if (!(((S_800A5C70_0 *)entry)->unk_1C & 0x2208)) {
            s32 axis_distance;
            s32 abs_axis_distance;
            s32 abs_axis_distance_2;

            entry_coords = ((S_800A5C70_0_pre *)entry)[-1].unk_00;
            abs_axis_distance = abs((origin_coords->tile_position.parts.tile_x) - (entry_coords->unk_24));
            if (abs_axis_distance < 5) {
                abs_axis_distance_2 = abs((origin_coords->tile_position.parts.tile_y) - (entry_coords->unk_25));
                if (abs_axis_distance_2 < 5) {
                    return 0;
                }
            }
        }
        entry = (u8 *)((S_800A5C70_0 *)entry)->unk_5C + 0x20;
    } while (entry != first_entry);

    return 1;
}
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/dungeon_status.h"

/* Store the dungeon turn counter in its retained word. */
void store_dungeon_turn_counter(void) {
    *(s32 *)0x8001362C = (s32) g_dungeon_status.turn_counter;
}
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;


/* Advance the counter and mark completion at 16 ticks, decrementing the global count. */
void advance_timed_object_and_retire(void *counter) {
    u16 tick_count;

    tick_count = *(u16 *)counter + 1;
    *(u16 *)counter = tick_count;
    if ((s16)tick_count >= 0x10) {
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        *(u16 *)((u8 *)counter - 2) |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
#include "shared/object_node.h"
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 D_800A5D5C;


/* Set the object data pointer and increment the global state counter. */
void create_timed_status_object(void) {

    ((s32 **)allocate_flagged_object_node(0))[4] = &D_800A5D5C;
    g_dungeon_status.activity_counts.parts.pending_action_count += 1;
}
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A5DFC_arg1.h"

void *create_actor_value_popup(); /* extern */
void *spawn_randomized_particle_burst();
typedef struct S_800A5DFC_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A5DFC_0_pre;   /* the 0x14 bytes before arg0 in apply_capped_damage_and_hit_effect, addressed as arg0[-1] */


typedef struct S_800A5DFC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800A5DFC_2;   /* ((S_800A5DFC_0_pre *)arg0)[-1].unk_00 in apply_capped_damage_and_hit_effect */

/* extern */

/* Applies damage capped to leave one HP and displays the hit effect when applicable. */
void apply_capped_damage_and_hit_effect(ActorRecord *entity, Rec_func_800A5DFC_arg1 *effect_pos) {
    s32 current_hp;
    s32 rounded_hp;
    s32 damage;
    u8 max_hp;

    if ((entity->flags1C & 0x40) && ((entity->hp + entity->unk_64) >= 2)) {
        max_hp = entity->max_hp;
        rounded_hp = max_hp + 0xF;
        entity->movement_facing = (s16) (((u16)entity->facing) + 0x800);
        if (rounded_hp < 0) {
            rounded_hp = max_hp + 0x1E;
        }
        damage = rounded_hp >> 4;
        current_hp = entity->hp + entity->unk_64;
        if ((current_hp - damage) <= 0) {
            damage = current_hp - 1;
        }
        if (damage != 0) {
            entity->flags1C = (s32) (entity->flags1C & 0xDFFFFFFF);
            if (!(((S_800A5DFC_2 *)(((S_800A5DFC_0_pre *)entity)[-1].unk_00))->unk_14 & 0x8000)) {
                create_actor_value_popup(3, entity, (s16) damage, 0);
                entity->unk_64 = (s16) ((u16) entity->unk_64 - damage);
                spawn_randomized_particle_burst(effect_pos->unk_02, effect_pos->unk_06, (s16) (effect_pos->unk_0A - 8), 0x802080, 0x20,
                    1);
                return;
            }
            entity->hp = (u8) (entity->hp - damage);
        }
    }
}
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 lookup_item_category_mapped_value(u8, u8);
extern void clear_slot_and_update_linked_state(void *);
extern s32 play_sound_if_enabled(s32);
extern void place_item_at_valid_floor_position(u16, u16, s16, s32, void *);

/* Processes a target using the linked object's position, then decrements the shared count. */
void place_actor_item(void *object_context, void *target) {
    void *object;

    object = *(void **)((s8 *)object_context - 0x18);
    place_item_at_valid_floor_position(*(u16 *)((s8 *)object + 2) >> 6,
                  *(u16 *)((s8 *)object + 6) >> 6,
                  *(s16 *)((s8 *)object + 0xA),
                  lookup_item_category_mapped_value(*((u8 *)target + 1), *(u8 *)target), target);
    play_sound_if_enabled(0x50C);
    clear_slot_and_update_linked_state(target);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
}
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_D_80083160.h"
#include "m2c_compat.h"

typedef struct S_800A5FC0_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800A5FC0_0;


typedef struct S_800A5FC0_2 {
    s32 unk_00;
    s32 unk_04;
    u16 unk_08;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    s16 unk_0C;
} S_800A5FC0_2;   /* arg0 in draw_expanding_screen_rectangle */

typedef struct S_800A5FC0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u16 unk_0C;
    s16 unk_0E;
    s32 unk_10;
    u16 unk_14;
    s16 unk_16;
} S_800A5FC0_3;

typedef struct S_800A5FC0_4 {
    void * unk_00;
} S_800A5FC0_4;

typedef struct S_800A5FC0_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800A5FC0_5;   /* ((Rec_D_80083160 *)(&D_80083160))->unk_00.as_pv in draw_expanding_screen_rectangle */


extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_800666E0(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Advance a rectangle's right edge toward 320 and queue it for rendering. */
s32 draw_expanding_screen_rectangle(S_800A5FC0_2 *state) {
    u16 frames_left;
    u16 right_x;
    void *quad;
    void *draw_mode;
    S_800A5FC0_0 *render_ctx;
    void **render_ctx_ref;

    render_ctx = g_game_work.draw_buffer;
    draw_mode = render_ctx->unk_8D0;
    render_ctx->unk_8D0 = (void *) (draw_mode + 0xC);
    quad = ((S_800A5FC0_5 *)(((Rec_D_80083160 *)(((void * *)(&g_game_work))))->unk_00.as_pv))->unk_8D0;
    ((S_800A5FC0_5 *)(((Rec_D_80083160 *)(((void * *)(&g_game_work))))->unk_00.as_pv))->unk_8D0 = (void *) (quad + 0x18);
    render_ctx_ref = (void **)((void * *)(&g_game_work));
    func_80067F20(draw_mode, 0, 0, state->unk_04, 0);
    ((S_800A5FC0_3 *)quad)->unk_04 = (s32) state->unk_00;
    func_800666E0(quad);
    func_80066640(quad, 1);
    ((S_800A5FC0_3 *)quad)->unk_10 = 0xE00000;
    ((S_800A5FC0_3 *)quad)->unk_08 = 0;
    ((S_800A5FC0_3 *)quad)->unk_0E = 0;
    ((S_800A5FC0_3 *)quad)->unk_16 = 0xE0;
    frames_left = state->unk_08 - 1;
    state->unk_08 = frames_left;
    if ((s16) frames_left > 0) {
        s32 x_delta = 0x140 - state->unk_0A.s;
        state->unk_0A.s = state->unk_0A.u + x_delta / (s16) frames_left;
    } else {
        state->unk_08 = 0U;
        state->unk_0A.s = 0x140;
    }
    right_x = (u16) state->unk_0A.s;
    ((S_800A5FC0_3 *)quad)->unk_14 = right_x;
    ((S_800A5FC0_3 *)quad)->unk_0C = right_x;
    func_8006658C((u8 *)((S_800A5FC0_4 *)render_ctx_ref)->unk_00 + ((state->unk_0C * 4) + 0x70), quad);
    func_8006658C((u8 *)((S_800A5FC0_4 *)render_ctx_ref)->unk_00 + ((state->unk_0C * 4) + 0x70), draw_mode);
    return 0;
}
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "m2c_compat.h"

extern void *D_800DCF64;

typedef struct S_800A6104_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800A6104_0;   /* D_800DCF64 in configure_shared_fade_primitive */

typedef struct S_800A6104_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
} S_800A6104_1;

/* Initialize the optional object settings to their default values. */
void configure_shared_fade_primitive(void) {
    S_800A6104_1 *settings;

    if (D_800DCF64 != NULL) {
        ((S_800A6104_0 *)D_800DCF64)->unk_20 = 0xFFFFFF;
        settings = D_800DCF64 + 0x20;
        settings->unk_04 = 0x40;
        settings->unk_0C = 1;
    }
}
#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"

struct S_800A5FC0_2;

s32 register_node();              /* extern */
extern s32 D_800A5FC0(struct S_800A5FC0_2 *state);

typedef struct S_800A613C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
} S_800A613C_0;

/* Create an object, attach its descriptor, and initialize its data fields. */
s32 create_expanding_screen_rectangle(void) {
    s32 object;
    S_800A613C_0 *object_data;

    object = (s32)allocate_flagged_object_node(0);
    if (object != 0) {
        register_node(object, &D_800A5FC0);
        object_data = object + 0x20;
        object_data->unk_08 = 6;
        object_data->unk_0C = 0x10;
    }
    return object;
}
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/object_flags.h"


/* Advance the timed ramp to 255 and update completion and shutdown flags. */
void advance_timed_intensity_ramp(void *ramp) {
    u16 ticks_left;
    u32 initial_flags;
    u32 current_flags;

    ticks_left = *(u16 *)((s8 *)ramp + 8) - 1;
    *(u16 *)((s8 *)ramp + 8) = ticks_left;
    if ((s16)ticks_left > 0) {
        *(s16 *)((s8 *)ramp + 10) += (0xFF - *(s16 *)((s8 *)ramp + 10)) / (s16)ticks_left;
    } else {
        *(s16 *)((s8 *)ramp + 10) = 0xFF;
        initial_flags = ((u32)dungeon_floor_flags);
        *(u16 *)((s8 *)ramp + 8) = 0;
        dungeon_floor_flags = initial_flags | 0x02000000;
    }
    current_flags = (u32) dungeon_floor_flags;
    if (!(current_flags & 0x01000000)) {
        dungeon_floor_flags = current_flags & 0xFDFFFFFF;
        *(s16 *)((s8 *)ramp - 2) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"



typedef struct {
    u8 pad[0xA];
    s16 color;
    s16 index;
} Input;

typedef struct {
    s32 unk0;
    s32 color;
    s32 unk8;
    s32 width;
    s32 start;
    s32 end;
} Work;


extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_800666E0(void *);
extern void func_80066640(void *, s32);
extern void func_8006658C(void *, void *);

/* Queue a full-screen grayscale quad with its draw mode at the input ordering index. */
s32 draw_fullscreen_grayscale_quad(Input *input) {
    GpuContext *arena;
    u8 *draw_mode;
    Work *quad;
    s16 color;

    arena = (GpuContext *)g_game_work.draw_buffer;
    draw_mode = arena->packetCursor;
    arena->packetCursor = draw_mode + 0xC;
    arena = (GpuContext *)g_game_work.draw_buffer;
    quad = (Work *)arena->packetCursor;
    arena->packetCursor = (u8 *)quad + 0x18;

    func_80067F20(draw_mode, 0, 0, 0x40, 0);

    color = input->color;
    quad->color = color | (color << 8) | (color << 16);
    func_800666E0(quad);
    func_80066640(quad, 1);

    quad->width = 0x140;
    quad->unk8 = 0;
    quad->start = 0xE00000;
    quad->end = 0xE00140;

    func_8006658C((u8 *)g_game_work.draw_buffer + ((input->index * 4) + 0xB0), quad);
    func_8006658C((u8 *)g_game_work.draw_buffer + ((input->index * 4) + 0xB0), draw_mode);
    return 0;
}
#include "shared/object_node.h"
#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"
#include "m2c_compat.h"

s32 register_node(void *entry, s32 registration_id);           /* extern */
extern M2C_UNK D_800A6194;
extern M2C_UNK D_800A624C;

typedef struct S_800A634C_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800A634C_0;

typedef struct S_800A634C_1 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
} S_800A634C_1;

/* Allocates an object and initializes its state with the supplied value. */
void *create_fullscreen_quad_updater(s16 initialValue) {
    void *object;
    S_800A634C_1 *objectState;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        ((S_800A634C_0 *)object)->unk_10 = &D_800A6194;
        register_node(object, &D_800A624C);
        objectState = object + 0x20;
        objectState->unk_08 = 8;
        objectState->unk_0C = initialValue;
    }
    return object;
}
#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"
#include "m2c_compat.h"

s32 expand_text_control_codes();                  /* extern */
s32 append_typed_formatted_value();                    /* extern */
s32 append_entity_display_text();                        /* extern */
s32 write_status_prefix_bytes();                             /* extern */
extern u8 fullwidth_period[];
extern M2C_UNK D_800E0A03[];
extern M2C_UNK D_800E0A12[];

/* Builds and displays an item message with the selected phrase and entity name. */
void display_item_status_message(s32 entity, s32 item, s32 message_kind, s32 buffer_arg) {
    s32 message;

    s32 text_end;

    message = get_unused_text_buffer(entity, item, message_kind, buffer_arg);
    if ((s16)message_kind == 0x15) {
        text_end = expand_text_control_codes(D_800E0A03, append_typed_formatted_value(item, message));
    } else {
        text_end = expand_text_control_codes(D_800E0A12, append_typed_formatted_value(item, message));
    }
    clear_byte_and_advance(write_status_prefix_bytes(expand_text_control_codes(&fullwidth_period, append_entity_display_text(entity, text_end))));
    display_text_with_fullwidth_adjustment(message);
}
#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"

extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 append_typed_formatted_value(void *data, s32 buffer);
extern s32 append_entity_display_text(void *record, u8 *out);
extern s32 write_status_prefix_bytes(s32 dst);
extern u8 fullwidth_period[];
extern u8 D_800E0A1B[];

void display_actor_item_status_message(s32 actor, void *item, s32 buffer_arg2, s32 buffer_arg3) {
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;

    adjusted_value = append_typed_formatted_value(item, current_value = get_unused_text_buffer());
    original_value = current_value;
    current_value = adjusted_value;
    clear_byte_and_advance(write_status_prefix_bytes(expand_text_control_codes(fullwidth_period,
        append_entity_display_text(actor, expand_text_control_codes(D_800E0A1B, current_value)))));
    display_text_with_fullwidth_adjustment(original_value);
}
#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void display_formatted_context_message();                   /* extern */
extern M2C_UNK D_800E092B;

/* Passes D_800E092B to display_formatted_context_message by address. */
void display_fixed_item_action_message(void) {
    display_formatted_context_message(&D_800E092B);
}
#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"

extern s32 get_entity_effect_value(void *, s32);

extern s32 D_800DCF08[];
extern s32 D_800DCF3C;
extern s32 D_800DCF44;
extern s32 D_800DCF48;

/* Selects a value from object flags and the highest matching state index. */
s32 select_object_state_value(void *object) {
    s32 state_result;
    s32 state_index;
    s32 special_index;
    s32 selected_value;

    if (*(u8 *)((u8 *)object + 0x13) != 0) {
        if (*(u8 *)((u8 *)object + 0x25) == 0) {
            selected_value = D_800DCF44;
            return selected_value;
        }
        if (!(*(s32 *)((u8 *)object + 0x1C) & 0x20000)) {
            selected_value = D_800DCF3C;
            return selected_value;
        }
    }
    state_index = 14;
    special_index = 7;
    for (; state_index >= 0; state_index--) {
        state_result = (s16)get_entity_effect_value(object, (s8)state_index);
        if (state_result > 0) {
            if (state_index == special_index) {
                selected_value = D_800DCF48;
                return selected_value;
            }
        }
        if (state_result != 0) {
            selected_value = D_800DCF08[state_index];
            return selected_value;
        }
    }
    selected_value = D_800DCF08[0];

    return selected_value;
}
#include "common.h"
#include "m2c_compat.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"


typedef struct S_800A6620_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A6620_1_pre;   /* the 0x14 bytes before object in release_entity_slot_and_update_flags, addressed as object[-1] */

typedef struct S_800A6620_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x23];
    u8 unk_43;
    u8 unk_44;
} S_800A6620_1;   /* object in release_entity_slot_and_update_flags */

typedef struct S_800A6620_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800A6620_2;   /* entry in release_entity_slot_and_update_flags */

typedef struct S_800A6620_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A6620_3;   /* owner in release_entity_slot_and_update_flags */


extern void build_entity_slot_snapshot(void *ptr, void *object);
extern s32 get_entity_effect_value(void *object, s32 value);
extern void clear_slot_and_update_linked_state(void *handle);
extern void unlink_entity_node(void *object);
extern void update_map_cell_flags_with_item_limit(u8 sound_x, u8 sound_y, s32 sound_mode);
extern s16 find_entity_slot_by_field_ac(void *object);
extern void detach_record_and_update_slot_state(void *object);

extern void *familiar_record_slots[];

/* Removes the object from its slot, performs flagged cleanup, and releases its handle. */
s16 release_entity_slot_and_update_flags(void *handle, s32 extra_cleanup)
{
    s32 sound_mode;
    s32 index;
    void **object_slot;
    void **object_table;
    void *object;
    void *state_entry;
    void *owner;
    u8 sound_x;
    u8 sound_y;

    object_table = familiar_record_slots;
    index = ((u8 *)handle)[3] & 0x1F;
    object_slot = &object_table[index];
    object = *object_slot;
    *object_slot = 0;
    index = ((S_800A6620_1 *)object)->unk_43;

    if (index < 0x40) {
        ((S_800A6620_1 *)object)->unk_44 = 0;
        build_entity_slot_snapshot((void *)(0x80010A80 + index * 0x54), object);
    }

    if (((u8 *)handle)[3] & 0x20) {
        index = find_entity_slot_by_field_ac(object);
        if (index >= 0) {
            state_entry = (void *)(index * 4 + ((s32)dungeon_actor_ring_anchor));
            ((S_800A6620_2 *)state_entry)->unk_AC = 0;
            ((S_800A6620_2 *)state_entry)->unk_D0 = 0;
        }

        if ((get_entity_effect_value(object, 0x1B) << 16) == 0) {
            owner = ((S_800A6620_1_pre *)object)[-1].unk_00;
            sound_x = ((S_800A6620_3 *)owner)->unk_24;
            sound_y = ((S_800A6620_3 *)owner)->unk_25;
            sound_mode = 0x3000;
            if (((S_800A6620_1 *)object)->unk_1C & 0x2000) {
                sound_mode = 0x300;
            }
            update_map_cell_flags_with_item_limit(sound_x, sound_y, sound_mode);
        }

        if (extra_cleanup != 0) {
            detach_record_and_update_slot_state(object);
        }
        unlink_entity_node(object);
        (*(u16 *)((u8 *)object + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    clear_slot_and_update_linked_state(handle);
    return index;
}
#include "common.h"

extern s8 scene_music_hold;   /* keep-floor-music flag; declared scalar as in func_80087A70, func_802833F4, func_80084340 and the town readers */

/* Preserve the sound sequence for tutorial mode or within a normal floor group. */
s32 check_action_boundary_and_set_flag(void) {
    s32 *stateBase = (s32 *)0x80010000;   /* integer page, two genuine reads (decision 44) */
    s32 mode;
    s32 boundaryValue;

    mode = stateBase[0x2090 / 4];
    scene_music_hold = 0;
    if (mode == 1 || (mode == 0 &&
        (boundaryValue = stateBase[0x234 / 4],
         boundaryValue / 5 == (boundaryValue + 1) / 5))) {
        scene_music_hold = 1;
        return 1;
    }
    return 0;
}
#include "modules/dungeon_engine_dungeon_util_fragment_c1094.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"

extern s8 dungeon_event_pending_flag[];
extern s8 D_800E045C[];

extern s32 call_script(void *arg);
extern void runtime_clear_state_and_entry_range(void);

/* When unblocked, clears a set flag and decrements its counter before running updates. */
void clear_pending_item_action_state(void) {
    if (!(dungeon_floor_flags & 0x200000) && !(system_update_flags & 8)) {
        if (dungeon_event_pending_flag[0] != 0) {
            dungeon_event_pending_flag[0] = 0;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        call_script(&D_800E045C[0]);
        runtime_clear_state_and_entry_range();
    }
}
#include "modules/dungeon_engine_dungeon_util_fragment_c1094.h"
#include "common.h"

s32 generate_random_value();                             /* extern */

/* Combine the adjusted input divided by four with the helper result low bits. */
s32 get_random_scaled_value(s16 input_value) {
    s16 adjusted_value;

    adjusted_value = input_value;
    if (input_value == 0xFF) {
        adjusted_value = 0x1E;
    }
    return ((s32) (adjusted_value << 0x10) >> 0x12) + (generate_random_value() & 3);
}
#include "modules/dungeon_engine_dungeon_util_fragment_c1094.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"



/* Save and clear bit 4 of the current record flags. */
void save_and_clear_entity_flag_ten(void) {
    D_800DD878 = ((u32) ((u32)dungeon_actor_ring_anchor->flags1C) >> 4) & 1;
    dungeon_actor_ring_anchor->flags1C = (u32) (((u32)dungeon_actor_ring_anchor->flags1C) & ~0x10);
}
#include "modules/dungeon_engine_dungeon_util_fragment_c1094.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"



/* Restore bit 4 of the current record flags when it was saved as set. */
void restore_entity_flag_ten(void) {
    if (D_800DD878 != 0) {
        dungeon_actor_ring_anchor->flags1C = (s32) (dungeon_actor_ring_anchor->flags1C | 0x10);
    }
}
#include "modules/dungeon_engine_dungeon_util_fragment_c1094.h"
#include "common.h"

/* Count the 20 table entries whose first halfword matches the packed input bytes. */
s16 count_matching_packed_entity_keys(s32 high_byte, s32 low_byte) {
    u8 *entry_cursor;
    u32 table_page;
    s32 match_count;
    s32 entry_index;
    s32 packed_value;

    packed_value = (high_byte << 8) | (low_byte & 0xFF);
    match_count = 0;
    entry_index = 0x13;
    packed_value &= 0xFFFF;
    table_page = 0x80010000;
    entry_cursor = (u8 *)(table_page | 0x4C);
    do {
        if (*(u16 *)*(u32 *)(entry_cursor + 0x29C) == packed_value) {
            match_count++;
        }
        entry_index--;
        entry_cursor -= 4;
    } while (entry_index >= 0);
    return match_count;
}
#include "common.h"

extern s32 utility_count_word(s32, s32) __asm__("count_matching_packed_entity_keys");

/* Returns 1 if the packed byte pair is in the table, otherwise checks count_matching_packed_entity_keys. */
s16 has_recorded_value_pair(s32 highByte, s32 lowByte) {
    s32 packedBytes = highByte << 8;
    s32 remainingEntries;
    s32 searchKey;
    u16 *entry;

    packedBytes |= lowByte & 0xFF;
    remainingEntries = 0x3F;
    searchKey = packedBytes & 0xFFFF;
    entry = (u16 *)0x8001207C;

    while (1) {
        if (*entry == searchKey)
            return 1;
        if (--remainingEntries < 0)
            break;
        entry -= 2;
    }
    return utility_count_word(highByte & 0xFF, lowByte & 0xFF);
}
#include "common.h"

extern void spawn_floor_monster_from_table(s32 spawn_mode);
extern s32 random_dungeon_range_16(u32 bound_a, u32 bound_b);

/* Initializes monster spawn rates with values 2 through 17 and a random number of value 1 entries. */
void spawn_initial_floor_monsters(void) {
    s32 repeat_count;
    s32 call_index;
    s32 scaled_value;

    repeat_count = random_dungeon_range_16(4, 8) & 0xFFFF;
    call_index = 0;
    do {
        scaled_value = (call_index + 2) << 0x10;
        spawn_floor_monster_from_table(scaled_value >> 0x10);
        call_index += 1;
    } while (call_index < 0x10);
    call_index = 0;
    if (call_index < repeat_count) {
        do {
            spawn_floor_monster_from_table(1);
            call_index += 1;
        } while (call_index < repeat_count);
    }
}
#include "common.h"
#include "m2c_compat.h"

void clear_selected_item_flag_400();                        /* extern */

/* Sends the two-byte command 1, 0x12. */
void clear_item_flag_400_for_egg_one(void) {
    s8 command[2];

    command[0] = 1;
    command[1] = 0x12;
    clear_selected_item_flag_400((s8 *)&command[0]);
}
#include "common.h"


typedef struct {
    u16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[2];
    u8 count;
    u8 pad3[9];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern void clear_item_flag_400_for_egg_one(void);
extern DungeonGroup item_category_groups[];

typedef struct {
    u8 pad[0x5720];
    u8 data[1];
} RamPage;


typedef struct S_800A6A9C_0 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 pad_03[0x9];
    DungeonItem * unk_0C;
} S_800A6A9C_0;

/* Restores item flag 0x400 across the item category table from the RAM bitmap, then calls clear_item_flag_400_for_egg_one. */
void restore_item_flag_400_bitmap(void)
{
    u8 *group;
    s32 bitmap_byte;
    s32 item_index;
    s32 item_offset;
    s32 group_index;
    s32 bitmap_offset;
    s32 clear_flag_mask;
    RamPage *ram_page;
    s16 *item_flags;
    s16 *marked_flags;

    group_index = 0;
    clear_flag_mask = -0x401;
    ram_page = (RamPage *)0x80010000;
    do {
        group = (u8 *)item_category_groups + group_index * sizeof(DungeonGroup);
        item_index = 0;
        if (((S_800A6A9C_0 *)group)->unk_02 != 0) {
            bitmap_offset = group_index * 8;
            item_offset = 0;
            do {
                item_flags = (s16 *)(item_offset +
                    (s32)((S_800A6A9C_0 *)group)->unk_0C);
                *item_flags = *item_flags & clear_flag_mask;
                bitmap_byte = item_index / 8;
                if (((s32)*(u8 *)(bitmap_offset + bitmap_byte + (s32)ram_page + 0x5720) >>
                     (item_index & 7)) & 1) {
                    marked_flags = (s16 *)(item_offset +
                        (s32)((S_800A6A9C_0 *)group)->unk_0C);
                    *marked_flags |= 0x400;
                }
                item_offset += 0x14;
            } while (++item_index < (s32)((S_800A6A9C_0 *)group)->unk_02);
        }
        group_index += 1;
    } while (group_index < 0x13);
    clear_item_flag_400_for_egg_one();
}

/* MECHANISM: The 0x18 frame has only the $ra save; explicit clear_flag_mask/page locals
   fix preheader order, and preincrement loads count before the inner increment.
   Loop-top ASM_KEEP holds the unrebased group base, yielding v0-high/a2-low
   split addressing with +2/+0xC fields; index-first RAM arithmetic fixes addu. */
#include "common.h"

s32 func_800644B8();                             /* extern */

typedef struct S_800A6B70_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6B70_0;   /* arg0 in update_sine_pulse_color */

typedef struct S_800A6B70_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800A6B70_1;   /* arg2 in update_sine_pulse_color */

/* Advances the phase and sets all three color channels to the same intensity. */
void update_sine_pulse_color(S_800A6B70_0 *phase_state, s32 unused, S_800A6B70_1 *color) {
    s32 phase;
    s8 intensity;

    phase = phase_state->unk_0C + 1;
    phase_state->unk_0C = phase;
    intensity = (func_800644B8(phase << 6) >> 7) + 0x60;
    color->unk_0E = intensity;
    color->unk_0D = intensity;
    color->unk_0C = intensity;
}
#include "common.h"

typedef struct {
    s8 state;
    u8 pad1;
    u8 value;
    u8 pad3[9];
} Record;

/* Adds successive multiples of the step to record values through the terminal record. */
void advance_record_values_by_step(Record *record, s16 step)
{
    u8 *value;
    s32 offset;
    s32 wide_step;

    wide_step = step;
    value = &record->value;
    offset = 0;

    for (;;) {
        *value += offset;
        if (record->state < 0) {
            return;
        }
        offset += wide_step;
        value += sizeof(Record);
        record++;
    }
}

/* MECHANISM: retail word 4 (`j 0x800A6BCC` == true_name+0x10) is a loop
   back-edge, not a call -- func_800A6BCC was m2c's fake callee name for the
   function's own mid-body label. Written as the for(;;) it actually is, gcc's
   own dbr sinks record++'s addiu into the back-edge j's delay slot with no
   pin; the former ASM_KEEP(value)/ASM_TAILSLOT_PIN_TIED(record) pair (needed
   only to fake liveness across the old pseudo-call) is gone along with the call. */
#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"



s32 register_node(void *entry, s32 registration_id);
s32 decode_fullwidth_text();
void advance_record_values_by_step();
void offset_record_coordinates();
void set_record_flags_and_negate_x();
void apply_record_flags_through_end();
void set_record_byte_flags_through_end();
extern M2C_UNK D_80089074;
extern M2C_UNK D_800A6B70;
extern M2C_UNK D_800B06F0;

typedef struct S_800A6C00_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x9C];
    s32 unk_C0;
    u8 pad_C4[0x2C];
    s32 unk_F0;
    s32 unk_F4;
} S_800A6C00_0;

typedef struct S_800A6C00_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A6C00_1;

typedef struct S_800A6C00_2 {
    u8 pad_00[0x4];
    void * unk_04;
    s16 unk_08;
} S_800A6C00_2;

typedef struct S_800A6C00_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A6C00_3;

typedef struct S_800A6C00_4 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800A6C00_4;

/* Allocate an object and initialize its sprite, position, scale, and render state. */
void *create_pulsing_effect_object(void) {
    S_800A6C00_3 *transform;
    S_800A6C00_4 *sprite;
    S_800A6C00_2 *render_state;
    void *object;
    S_800A6C00_1 *position;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        position = ((S_800A6C00_0 *)object)->unk_08;
        transform = ((S_800A6C00_0 *)object)->unk_0C;
        render_state = object + 0x20;
        position->unk_02 = 0x3C;
        position->unk_06 = 0x40;
        render_state->unk_08 = 1;
        transform->unk_1E = 0x1800;
        transform->unk_1C = 0x1800;
        ((S_800A6C00_0 *)object)->unk_10 = &D_800A6B70;
        register_node(object, &D_800B06F0);
        sprite = object + 0x30;
        ((S_800A6C00_0 *)object)->unk_20 = (void *)(object + 0xF0);
        render_state->unk_04 = (void *)(object + 0xC0);
        ((S_800A6C00_0 *)object)->unk_F0 = decode_fullwidth_text(sprite, &D_80089074, 0) & 0x7FFFFFFF;
        offset_record_coordinates(sprite, 0xA8, (s16)((0 - (s8)sprite->unk_03) + 8));
        advance_record_values_by_step(sprite, 4);
        set_record_flags_and_negate_x(sprite, 8);
        apply_record_flags_through_end(sprite, 0x20);
        set_record_byte_flags_through_end(sprite, 2);
        ((S_800A6C00_0 *)object)->unk_C0 = 0x808080;
        ((S_800A6C00_0 *)object)->unk_F4 = 0;
    }
    return object;
}
#include "common.h"
#include "shared/game_work.h"

/* Advances the random seed and returns a 15-bit random value. */
s32 generate_random_value(void) {
    u32 next_seed;

    next_seed = (((u32)g_game_work.randSeed) * 0x41C64E6D) + 0x3039;
    g_game_work.randSeed = next_seed;
    return (next_seed >> 0x10) & 0x7FFF;
}
#include "common.h"
#include "shared/game_work.h"

extern s32 saved_random_seed[];

/* Saves or restores the random seed according to the low 16 bits of save_seed. */
void save_or_restore_random_seed(s32 save_seed) {
    GameWork *rng_state = &g_game_work;
    s32 save_flag = save_seed << 16;

    if (save_flag != 0) {
        saved_random_seed[0] = rng_state->randSeed;
        return;
    }
    rng_state->randSeed = saved_random_seed[0];
}
#include "common.h"
#include "shared/game_work.h"

/* Restore the saved dungeon RNG seed before the SLUS category shuffle.
 * randSeed is the resident 32-bit RNG state at g_game_work + 0x1FC. */
void restore_dungeon_random_seed(s32 saved_seed) {
    g_game_work.randSeed = saved_seed;
}
#include "common.h"

extern s32 generate_random_value(void);


/* Return a 16-bit random value within the inclusive bounds. */
s32 random_dungeon_range_16(u32 bound_a, u32 bound_b) {
    u32 result;
    u32 range;
    u32 random_value;
    u32 upper;
    u32 lower;

    lower = bound_a;
    upper = bound_b;
    if (upper < lower) {
        random_value = upper;
        upper = lower;
        lower = random_value;
    }
    random_value = generate_random_value() & 0xFFFF;
    range = (upper - lower) + 1;
    result = ((random_value % range) + lower) & 0xFFFF;
    return result;
}
#include "shared/dungeon_item_entries.h"
#include "common.h"



extern s32 dungeon_ground_item_positions;

/* Counts active entries whose first two key bytes match the given values. */
s16 count_floor_items_at_tile(s16 first_key, s16 second_key) {
    s32 *status_entry;
    s32 *key_entry;
    s16 match_count;
    s32 entry_index;
    s32 match_first;
    s32 match_second;
    s8 zero;

    zero = 0;
    match_count = zero;
    entry_index = zero;
    match_first = first_key;
    match_second = second_key;
    key_entry = &dungeon_ground_item_positions;
    status_entry = ((s32 *)dungeon_ground_items);
    do {
        if ((*((u8 *) status_entry + 1) != 0) && (*((u8 *) key_entry) == match_first)
            && (*((u8 *) key_entry + 1) == match_second)) {
            match_count += 1;
        }
        key_entry += 3;
        entry_index += 1;
        status_entry += 1;
    } while (entry_index < 0x40);
    return match_count;
}
