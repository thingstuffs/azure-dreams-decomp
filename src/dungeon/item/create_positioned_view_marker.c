#include "modules/dungeon_ovl_7ce800.h"
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
/* Forwards the third argument to func_800478B8. */
void update_sprite_from_third_argument(s32 unused_first, s32 unused_second, s32 value) {
    advance_sprite_animation_and_textures(value);
}
#include "modules/dungeon_ovl_7ce800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_800DEAE0[];

typedef struct S_800F6090_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800F6090_0;

typedef struct S_800F6090_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800F6090_2;

/* Creates and initializes an object at the given coordinates with adjusted height. */
void create_positioned_view_marker(s16 x, s16 y) {
    SpriteFrameState *render_state;
    S_800F6090_2 *position;
    S_800F6090_0 *object;
    u32 render_config;

    object = allocate_flagged_object_node(0x16);
    if (object != NULL) {
        object->unk_10 = (void *)update_sprite_from_third_argument;
        register_node(object, project_sprite_chain);
        render_state = object->unk_0C;
        render_config = (u32) *((u32 *)(&g_game_work.view.tint.parts.tint_r));
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->color.word = render_config;
        select_record_entry_and_value(render_state, D_800DEAE0, 0);
        render_state->tpage_abr = 0x20;
        render_state->flags = 0xC;
        position = object->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = (s16) (sample_terrain_surface_height(x & 0xFFFF, y & 0xFFFF, -0x400) - 8);
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_807AE960_1 {
    union { u16 s; s16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    union { s16 s; s16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x4];
    s16 unk_0A;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    u16 unk_0E;
    s16 unk_10;
} S_807AE960_1;   /* state in advance_dungeon_tile_action_state */

typedef struct S_807AE960_2 {
    u8 pad_00[0x1A];
    s16 unk_1A;
} S_807AE960_2;   /* target in advance_dungeon_tile_action_state */

typedef struct S_807AE960_3 {
    u8 pad_00[0x2090];
    s32 unk_2090;
    u8 pad_2094[0x1686];
    u16 unk_371A;
} S_807AE960_3;   /* global in advance_dungeon_tile_action_state */

typedef struct S_807AE960_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_807AE960_4;   /* actor in advance_dungeon_tile_action_state */

typedef struct S_807AE960_5 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_807AE960_5;   /* global_end in advance_dungeon_tile_action_state */

typedef struct S_807AE960_6 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_807AE960_6;   /* entry in advance_dungeon_tile_action_state */


extern void *D_800F6000[];
s32 Control_CD(s32 event_code, void *event_data, s32 payload);
s32 get_cd_command_queue_depth();
void sound_set_cd_cue_parameters();
int read_stream_cue_start_offset();
s32 read_sound_mode_blocking_status();
extern M2C_UNK D_80010000;
extern u16 D_8001371A;
extern s32 cd_cue_base;

/* Dispatch the CD-audio fade state machine, then step the actor's shake counter and raise the finished flag. */
void advance_dungeon_tile_action_state(u8 *state, u8 *actor, u8 *target) {
    s16 steps;
    s32 dispatch_index;
    s16 remaining;
    s32 countdown;
    u16 countdown_u;
    s32 actor_pos;
    u8 *global;
    u32 cd_mode;
    s32 table_base;
    u8 *global_end;
    GameWork *dungeon_data;
    S_807AE960_6 *entry;

    dungeon_data = &g_game_work;
    global_end = (u8 *)dungeon_data + 0x1DC;
    table_base = ((s32)dungeon_data->map.cells);
    dispatch_index = (s16)(((S_807AE960_1 *)state)->unk_00.s - 1);
    switch (dispatch_index + 1) {
    case 1:
    case 2:
        if (get_cd_command_queue_depth() != 0) {
            return;
        }
        if (((S_807AE960_1 *)state)->unk_10 == 0) {
            play_sound_if_enabled(0x300);
        }
        ((S_807AE960_1 *)state)->unk_00.u = 3;
        break;
    case 17:
        ((S_807AE960_1 *)state)->unk_0A = 0x400;
        ((S_807AE960_2 *)target)->unk_1A = (s16) (u16) ((S_807AE960_1 *)state)->unk_0A;
        ((S_807AE960_1 *)state)->unk_00.u = 0;
        break;
    case 3:
        steps = ((S_807AE960_1 *)state)->unk_04.s;
        if (steps > 0) {
            ((S_807AE960_2 *)target)->unk_1A = (s16) ((u16) ((S_807AE960_2 *)target)->unk_1A
                + ((s32) (((S_807AE960_1 *)state)->unk_0A - ((S_807AE960_2 *)target)->unk_1A) / steps));
        }
        remaining = (u16) ((S_807AE960_1 *)state)->unk_04.s - 1;
        ((S_807AE960_1 *)state)->unk_04.u = remaining;
        global = (u8 *)0x80010000;
        if (((S_807AE960_3 *)global)->unk_371A < 4U) {
            if (remaining < 0) {
                ((S_807AE960_1 *)state)->unk_04.s = 0;
            }
            break;
        }
        if (((S_807AE960_3 *)global)->unk_2090 == 1) {
            g_dungeon_status.activity_counts.parts.pending_action_count = 1;
        }
        if (((S_807AE960_1 *)state)->unk_04.s > 0) {
            break;
        }
        cd_mode = ((S_807AE960_3 *)global)->unk_2090;
        if (cd_mode == 1) {
            if (read_sound_mode_blocking_status(4) != 0) {
                ((S_807AE960_1 *)state)->unk_04.s = 0;
                break;
            }
            if (((S_807AE960_3 *)global)->unk_2090 == cd_mode) {
                g_dungeon_status.activity_counts.parts.pending_action_count = 0;
            }
        }
        ((S_807AE960_2 *)target)->unk_1A = (s16) (u16) ((S_807AE960_1 *)state)->unk_0A;
        ((S_807AE960_1 *)state)->unk_00.u = 0;
        break;
    case 4:
        if (((S_807AE960_1 *)state)->unk_10 == 0) {
            sound_set_cd_cue_parameters(0, cd_cue_base, 0x0600065E, 0x030008B6);
            Control_CD(0x15, read_stream_cue_start_offset(), 0);
        }
        ((S_807AE960_1 *)state)->unk_04.s = 0x60;
        ((S_807AE960_1 *)state)->unk_0C.s = 0x60;
    case 20:
        ((S_807AE960_1 *)state)->unk_00.s = 2U;
        ((S_807AE960_1 *)state)->unk_0A = (s16) ((S_807AE960_1 *)state)->unk_02;
        break;
    default:
        break;
    }
    countdown = ((S_807AE960_1 *)state)->unk_0C.s;
    countdown_u = ((S_807AE960_1 *)state)->unk_0C.u;
    if (countdown != 0) {
        countdown = countdown_u - 1;
        ((S_807AE960_1 *)state)->unk_0C.s = countdown;
        actor_pos = ((S_807AE960_4 *)actor)->unk_0A;
        if (countdown & 1) {
            countdown = actor_pos + 1;
        } else {
            countdown = actor_pos - 1;
        }
        ((S_807AE960_4 *)actor)->unk_0A = countdown;
        if (((S_807AE960_1 *)state)->unk_0C.s == 0) {
            ((S_807AE960_4 *)actor)->unk_0A = (s16) ((S_807AE960_1 *)state)->unk_0E;
        }
    }
    if (((S_807AE960_1 *)state)->unk_00.u != 0) {
        return;
    }
    if ((u8) reference_tile_object.tile_position.parts.tile_y >= 0x3DU) {
        return;
    }
    if (((S_807AE960_1 *)state)->unk_0A == (s16) ((S_807AE960_1 *)state)->unk_02) {
        return;
    }
    ((S_807AE960_1 *)state)->unk_00.s = 4U;
    entry = ((0x3E << ((S_807AE960_5 *)global_end)->unk_14) * 6) + table_base + 0xBA;
    entry->unk_04 = (u16) (entry->unk_04 | 0x8000);
    return;
}
const DirectionOffsets dungeon_7ce800_directions = {1,0,1,1,0,1,-1,1,-1,0,-1,-1,0,-1,1,-1};
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"

typedef struct S_800F643C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800F643C_0;

typedef struct S_800F643C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800F643C_1;

typedef struct S_800F643C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800F643C_2;

typedef struct S_800F643C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x4];
    s16 unk_0E;
    s16 unk_10;
} S_800F643C_3;


s32 draw_linked_lit_meshes(void *,s32,void *);
extern s32 default_textured_quad_color;
extern s16 *D_800F8A44[];

/* Creates a dungeon object at the given position and records it in its slot. */
void create_slot_positioned_effect(s16 x, s16 y, s32 slot) {
    s16 height;
    s32 render_config;
    void *object_data;
    void *position;
    void *model;
    void *object;

    object = allocate_flagged_object_node(0x16);
    if (object != NULL) {
        ((S_800F643C_0 *)object)->unk_10 = (void *)advance_dungeon_tile_action_state;
        register_node(object, (s32)draw_linked_lit_meshes);
        render_config = default_textured_quad_color;
        model = ((S_800F643C_0 *)object)->unk_0C;
        (*(s16 *)((u8 *)model + 0x20)) = 0x1000;
        ((S_800F643C_1 *)model)->unk_1E = 0x1000;
        ((S_800F643C_1 *)model)->unk_1C = 0x1000;
        ((S_800F643C_1 *)model)->unk_06 = 4;
        ((S_800F643C_1 *)model)->unk_0C = render_config;
        ((S_800F643C_1 *)model)->unk_08 = 0x70;
        position = ((S_800F643C_0 *)object)->unk_08;
        ((S_800F643C_2 *)position)->unk_02 = x;
        ((S_800F643C_2 *)position)->unk_06 = y;
        height = sample_terrain_surface_height(x & 0xFFFF, y & 0xFFFF, -0x400) - 0xC0;
        object_data = object + 0x20;
        ((S_800F643C_2 *)position)->unk_0A = height;
        ((S_800F643C_3 *)object_data)->unk_0E = height;
        do {
            ((S_800F643C_3 *)object_data)->unk_08 = slot;
        } while (0);
        if (slot != 0) {
            ((S_800F643C_3 *)object_data)->unk_02 = 0x800;
            ((S_800F643C_1 *)model)->unk_1A = 0x800;
        }
        D_800F8A44[slot] = object_data;
        ((S_800F643C_3 *)object_data)->unk_10 = slot;
    }
}

/* MECHANISM: The 0x30/no-local frame follows from six natural held values; s32 slot plus symbolic
   D_800F8A44[index] removes the sign-extension and scale-by-16 length cascade. */
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

extern s32 D_80013718;
extern s16 *D_800F8A44[];

/* Update both state targets and set flags when the mode is 3. */
void update_overlay_state_and_retire(void *data)
{
    s16 **state_slot;
    s16 **state_table;
    s16 *state_ptr;
    s16 state;
    s32 slot_index;
    DungeonGlobalStatus *flags;

    if (*(s32 *)0x80013718 == 3) {
        slot_index = 1;
        flags = &g_dungeon_status;
        state_table = D_800F8A44;
        state_slot = state_table + 1;
        do {
            state_ptr = *state_slot;
            if (state_ptr != 0) {
                state = 4;
                if (flags->flags & 0x80) {
                    state = 0x14;
                }
                *state_ptr = state;
            }
            slot_index -= 1;
            state_slot -= 1;
        } while (slot_index >= 0);
        ((u16 *)data)[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

/* MECHANISM: Frameless leaf; an absolute scalar lvalue makes the assembler reuse $v1
   for the D_80013718 lui/lw pair instead of gcc's separate symbolic page register.
   A held 0x80080000 page splits the flags address around count initialization as
   retail's lui / li / addiu while preserving both pointer inductions and the exact CFG. */
#include "modules/dungeon_ovl_7ce800.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
typedef struct S_800F65CC_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x10];
    s16 unk_24;
} S_800F65CC_0;

typedef struct S_800F65CC_1 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_800F65CC_1;   /* s1 in initialize_overlay_effect_state */

typedef struct S_800F65CC_2 {
    u8 pad_00[0x4];
    union { u16 s; s16 u; } unk_04;   /* accessed as both */
} S_800F65CC_2;


struct S_8003E2D8 {
    u8 pad0[0x1DC];
    s32 *field_1DC;
    s16 pad_1E0[8];
    s16 field_1F0;
};
typedef struct S_8003E2D8 S_8003E2D8;
struct S_80082E60 {
    u8 pad0[0x10];
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
};
typedef struct S_80082E60 S_80082E60;
extern s16 *D_800F8A44[];

extern u8 D_800F8A4C[];
struct S_10 {
    u8 data[10];
};

/* Initializes effect state and sets the high flag bit on three adjacent entries. */
void initialize_overlay_effect_state(void) {
    s16 **state_slot;
    s16 *state_value;
    s32 entries_base;
    s32 index;
    GameWork *world_state;
    s16 *entry_info;
    RuntimeDispatchState *effect_state;
    s16 **state_table;
    s32 state_code;
    u16 entry_flags;
    S_800F65CC_0 *effect;
    S_800F65CC_2 *entry;

    world_state = &g_game_work;
    entry_info = (s16 *)((u8 *)world_state + 0x1DC);
    entries_base = ((s32 *)world_state->map.cells);
    index = 1;
    state_code = 0x11;
    state_table = D_800F8A44;
    state_slot = state_table + 1;
    effect_state = &runtime_dispatch_state;
    effect_state->unk_10 = 0x1F;
    effect_state->unk_12 = 0x3E;
    effect_state->flags16 = (u16)(((s16)effect_state->flags16) | 1);
    do {
        state_value = *state_slot;
        if (state_value != 0) {
            *state_value = state_code;
        }
        index -= 1;
        state_slot -= 1;
    } while (index >= 0);
    effect = allocate_flagged_object_node(0x12);
    if (effect != 0) {
        s16 *status_base;

        effect->unk_10 = (void *)update_overlay_state_and_retire;
        effect->unk_24 = 0x38;
        status_base = (s16 *)0x80010000;
        if (!((u16)status_base[0x3714 / 2] & 1)) {
            *(struct S_10 *)((u32)0x80010000 | 0x3720) = *(struct S_10 *)D_800F8A4C;
            status_base[0x371A / 2] = 0;
            status_base[0x3718 / 2] = 0;
            status_base[0x3716 / 2] = 4;
            status_base[0x3714 / 2] = (u16)(status_base[0x3714 / 2] | 1);
        }
    }
    index = 0x1E;
    do {
        entry = ((index + (0x3E << ((S_800F65CC_1 *)entry_info)->unk_14)) * 6) + entries_base;
        entry_flags = entry->unk_04.s;
        index += 1;
        entry->unk_04.u = (s16)(entry_flags | 0x8000);
    } while (index < 0x21);
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"


typedef struct S_800F6738_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_800F6738_0;

/* Set flag 0x800000 on type 0x32 entities in the ring and set the global state to 0x1F. */
void mark_special_actors_and_set_player_tile(void) {
    void *first_entity;
    S_800F6738_0 *entity;

    entity = dungeon_actor_ring_anchor;
    first_entity = entity;
    do {
        if (entity->unk_13 == 0x32) {
            entity->unk_14 = (s32) (entity->unk_14 | 0x800000);
        }
        entity = entity->unk_5C + 0x20;
    } while (entity != first_entity);
    reference_tile_object.tile_position.parts.tile_x = 0x1F;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    s32 base;
    u8 pad_04[0x10];
    s16 shift;
} DungeonState;

typedef struct {
    u8 bytes[8];
} __attribute__((packed)) Packed8;

extern DungeonState scene_geometry;
extern Packed8 D_800F8B24;

extern void clear_scaled_cell_flags_8000(void);
extern void clear_player_linked_action_flags(void);

#define CLEAR_HIGH_BIT(ptr) \
(*(u16 *)((u8 *)(ptr) + 4) = *(u16 *)((u8 *)(ptr) + 4) & 0x7FFF)

/* Reveal the fixed-map cheat: set the map mode from the item used, clear the hidden bit on every listed tile and finish the owner. */
void update_dungeon_tile_boundary_state(void *owner) {
    DungeonState *state;
    s32 base;
    u8 *tile;
    u8 *tile_b;
    u8 *row_tile;
    u8 *row_tile_b;
    u8 *col_tile;
    u8 *col_tile_b;
    u8 *edge_tile;
    u8 *edge_tile_b;
    u8 *mode_page;
    u8 *objects;
    u8 *object;
    u32 copy_dest;
    u16 flags;
    s16 mode;
    s32 i;
    s32 i3;

    base = scene_geometry.base;
    mode = 0;
    state = &scene_geometry;
    if (!(g_dungeon_status.flags & 2)) {
        return;
    }
    if (*(s32 *)((u8 *)dungeon_actor_ring_anchor + 0x14) & 0x100000) {
        return;
    }
    if (reference_tile_object.tile_position.parts.tile_y != 0x24) {
        return;
    }
    if (reference_tile_object.tile_position.parts.tile_x == 0x1F) {
        mode = 2;
    } else if (reference_tile_object.tile_position.parts.tile_x == 0x20) {
        mode = 1;
    }
    if (mode == 0) {
        return;
    }

    clear_player_linked_action_flags();
    copy_dest = 0x80013720;
    *(Packed8 *)copy_dest = D_800F8B24;
    mode_page = (u8 *)0x80010000;
    flags = *(u16 *)(mode_page + 0x3714);
    *(s16 *)(mode_page + 0x371A) = mode - 1;
    *(u16 *)(mode_page + 0x3718) = 0;
    *(u16 *)(mode_page + 0x3716) = 0;
    *(u16 *)(mode_page + 0x3714) = flags | 1;

    tile = (u8 *)(((0x23 << state->shift) * 6) + base + 0xBA);
    CLEAR_HIGH_BIT(tile);
    tile_b = (u8 *)(((0x23 << state->shift) * 6) + base + 0xC0);
    CLEAR_HIGH_BIT(tile_b);

    i = 0x10;
    do {
        row_tile = (u8 *)(((i + (0x11 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(row_tile);
        i++;
    } while (i < 0x1D);

    i = 0x23;
    do {
        row_tile_b = (u8 *)(((i + (0x11 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(row_tile_b);
        i++;
    } while (i < 0x30);

    i3 = 0x12;
    do {
        col_tile = (u8 *)(((i3 << state->shift) * 6) + base + 0x60);
        CLEAR_HIGH_BIT(col_tile);
        col_tile_b = (u8 *)(((i3 << state->shift) * 6) + base + 0x11A);
        CLEAR_HIGH_BIT(col_tile_b);
        i3++;
    } while (i3 < 0x20);

    i = 0x10;
    do {
        edge_tile = (u8 *)(((i + (0x20 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(edge_tile);
        edge_tile_b = (u8 *)(((i + (0x21 << state->shift)) * 6) + base);
        CLEAR_HIGH_BIT(edge_tile_b);
        i++;
    } while (i < 0x30);

    clear_scaled_cell_flags_8000();
    i = 0;
    *(u16 *)((u8 *)owner - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
    objects = primary_actor_record;
    do {
        object = *(u8 **)(objects + 0xAC);
        if (object != 0) {
            *(u16 *)(object + 0x46) &= 0x7FFF;
        }
        i++;
        objects += 4;
    } while (i < 2);
    D_800DCF5B.first = 0;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"


typedef struct S_807AF2CC_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_807AF2CC_0;   /* func_8003FC64(0) in func_800F6ACC */

/* Set the returned object's data pointer to update_dungeon_tile_boundary_state. */
void create_tile_boundary_updater(void) {
    ((S_807AF2CC_0 *)(allocate_flagged_object_node(0)))->unk_10 = (void *)update_dungeon_tile_boundary_state;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"

typedef struct {
    s32 field0;
    u16 flags;
} DungeonCell;



extern void set_scaled_cell_flags_8000(void);

/* Mark fixed dungeon cells and initialize global coordinates and flags. */
void mark_scripted_map_boundary(void)
{
    MapGrid *dungeon;
    u8 *cells;
    RuntimeDispatchState *global_state;
    s32 coord;

    dungeon = &g_game_work.map;
    cells = ((u8 *)dungeon->cells);

    coord = 0x10;
    do {
        ((DungeonCell *)(cells + (coord + (0x11 << dungeon->shiftX)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x1D);

    coord = 0x23;
    do {
        ((DungeonCell *)(cells + (coord + (0x11 << dungeon->shiftX)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x30);

    coord = 0x12;
    do {
        ((DungeonCell *)(cells + (coord << dungeon->shiftX) * 6 + 0x60))->flags |= 0x8000;
        ((DungeonCell *)(cells + (coord << dungeon->shiftX) * 6 + 0x11A))->flags |= 0x8000;
        coord++;
    } while (coord < 0x20);

    coord = 0x10;
    do {
        ((DungeonCell *)(cells + (coord + (0x20 << dungeon->shiftX)) * 6))->flags |= 0x8000;
        ((DungeonCell *)(cells + (coord + (0x21 << dungeon->shiftX)) * 6))->flags |= 0x8000;
        coord++;
    } while (coord < 0x30);

    ((DungeonCell *)(cells + (0x23 << dungeon->shiftX) * 6 + 0xBA))->flags |= 0x8000;
    ((DungeonCell *)(cells + (0x23 << dungeon->shiftX) * 6 + 0xC0))->flags |= 0x8000;

    set_scaled_cell_flags_8000();

    global_state = &runtime_dispatch_state;
    global_state->unk_10 = 0x1F;
    global_state->unk_12 = 0x39;
    D_800DCF5B.bytes[0] = 1;
    global_state->flags16 |= 1;
    dungeon_floor_flags |= 0x10000000;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/entity_objects.h"


/* Returns the direction to the target position, or 9 for a coincident position. */
s32 get_direction_toward_target_position(s16 *target_pos)
{
    if (view_reference_entity.x.w.i == target_pos[1] && view_reference_entity.y.w.i == target_pos[3]) {
        return 9;
    }

    if (view_reference_entity.x.w.i < target_pos[1]) {
        if (view_reference_entity.y.w.i < target_pos[3]) {
            return 5;
        }
        if (target_pos[3] < view_reference_entity.y.w.i) {
            return 3;
        }
        return 4;
    }

    if (target_pos[1] < view_reference_entity.x.w.i) {
        if (view_reference_entity.y.w.i < target_pos[3]) {
            return 7;
        }
        return target_pos[3] < view_reference_entity.y.w.i;
    }

    if (view_reference_entity.y.w.i >= target_pos[3]) {
        return (target_pos[3] < view_reference_entity.y.w.i) * 2;
    }
    return 6;
}
#include "modules/dungeon_ovl_7ce800.h"
/* Return the base of the next type 0x15 entity in the ring, or null if absent. */
void *find_linked_entity_of_type_21(void *entity)
{
    void *entity_base;
    void *first_entity;
    void *next_base;
    next_base = *((void **) (((u8 *) entity) + 0x5C));
    first_entity = entity;
    entity = (u8 *) next_base + 0x20;
    if (entity != first_entity) {
        s32 target_type = 0x15;
        do {
            entity_base = (u8 *) entity - 0x20;
            if ((*((u8 *) (((u8 *) entity) - -0x13))) == target_type) {
                return entity_base;
            }
            entity = (*((void **) (((u8 *) entity) + 0x5C))) + 0x20;
        } while (entity != first_entity);
    }
    return 0;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct DungeonRoot DungeonRoot;
struct DungeonRoot {
    u8 pad[0x8D0];
    s32 cursor;
};

typedef struct DungeonObject DungeonObject;
struct DungeonObject {
    void *state;
    u8 pad04[0x08];
    s16 coord;
    u8 active;
    u8 count;
    s8 level;
};

typedef struct Scratch Scratch;

struct Scratch {
    u16 values[3];
    u8 pad06[0x1A];
    u8 *base;
    u8 pad24[0x4C];
    u16 x70;
    u16 y72;
    u16 z74;
    u8 pad76[2];
    u16 x78;
    u16 y7A;
    u16 z7C;
    u8 pad7E[0x42];
    s32 length;
};

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s16 func_80069EF8(void);

typedef union {
    u32 word;
    struct { u8 r, g, b, code; } bytes;
} ParticleColor;
typedef union {
    u32 word;
    struct { u16 x, y; } halves;
} ParticlePoint;
typedef union {
    u32 word;
    struct { u8 address[3], length; } bytes;
} ParticleTag;
typedef struct {
    ParticleTag tag;
    ParticleColor color0;
    ParticlePoint point0;
    ParticleColor color1;
    ParticlePoint point1;
    ParticleColor color2;
    ParticlePoint point2;
    ParticleColor color3;
    ParticlePoint point3;
} ParticleQuad;

/* Advances particle levels and queues colored quads in the dungeon ordering table. */
s32 draw_linked_particle_effect_primitives(DungeonObject *object, u16 *origin) {
    DungeonRoot *dungeon = *(DungeonRoot **)((u8 *)(&g_game_work));
    s32 packet_cursor = dungeon->cursor;
    GameWork *root_slot = &g_game_work;
    Scratch *scratch;
    s16 particle_index = 0;
    u8 *projection_param = (u8 *)0x1F800090;
    u8 *projection_flags;

    object->count = 0;
    scratch = (Scratch *)0x1F800000;
    scratch->base = *(u8 **)((u8 *)(&g_game_work)) + 0xB0;
    scratch->values[0] = origin[1];
    projection_flags = (u8 *)scratch;
    scratch->values[1] = origin[3];
    projection_flags = (u8 *)((u32)projection_flags | 0x94);
    scratch->values[2] = origin[5];
    for (; particle_index < 32; particle_index++) {
        {
            DungeonObject *particle_view = (DungeonObject *)((u8 *)object + (s16)particle_index);
            particle_view->level += 4;
            if ((s8)particle_view->level >= 48) {
                if (object->active != 0) {
                    particle_view->level = 48;
                    continue;
                }
                particle_view->level = 0;
            }
        }
        {
            s32 particle_offset = particle_index;
            ((ParticleQuad *)packet_cursor)->color0.word = 0;
            ((ParticleQuad *)packet_cursor)->color1.word = 0;
            scratch->x70 = scratch->values[0] +
                ((func_80064584((particle_offset + (object->coord << 6)) << 7) << 4) >> 11);
            scratch->x78 = scratch->x70;
            scratch->y72 = scratch->values[1] +
                ((func_800644B8((particle_offset + (object->coord << 6)) << 7) << 4) >> 11);
            scratch->y7A = scratch->y72;
            scratch->z74 = scratch->values[2] -
                *(s8 *)((u8 *)object + particle_offset + 0x10) * 2;
            scratch->z7C = scratch->z74 + 64;

            {
                s16 intensity = func_80069EF8();
                s8 level = *(s8 *)((u8 *)object + particle_offset + 0x10);
                if (level >= 33) {
                    intensity = intensity / (level - 32);
                } else if (level < 16) {
                    intensity = intensity / (16 - level);
                }
                ((ParticleQuad *)packet_cursor)->color2.bytes.r = (*(s32 *)((u8 *)object->state + 0x14) & 1) ? intensity : 0;
                ((ParticleQuad *)packet_cursor)->color3.bytes.r = ((ParticleQuad *)packet_cursor)->color2.bytes.r;
                ((ParticleQuad *)packet_cursor)->color2.bytes.g = (*(s32 *)((u8 *)object->state + 0x14) & 4) ? intensity : 0;
                ((ParticleQuad *)packet_cursor)->color3.bytes.g = ((ParticleQuad *)packet_cursor)->color2.bytes.g;
                ((ParticleQuad *)packet_cursor)->color2.bytes.b = (*(s32 *)((u8 *)object->state + 0x14) & 2) ? intensity : 0;
                ((ParticleQuad *)packet_cursor)->color3.bytes.b = ((ParticleQuad *)packet_cursor)->color2.bytes.b;
            }

            scratch->length = func_80065420(&scratch->x70, (void *)(packet_cursor + 8),
                projection_param, projection_flags);
            ((ParticleQuad *)packet_cursor)->point1.word = ((ParticleQuad *)packet_cursor)->point0.word;
            ((ParticleQuad *)packet_cursor)->point1.halves.x += 4;
            scratch->length += func_80065420(&scratch->x78, (void *)(packet_cursor + 24),
                projection_param, projection_flags);
            ((ParticleQuad *)packet_cursor)->point3.word = ((ParticleQuad *)packet_cursor)->point2.word;
            ((ParticleQuad *)packet_cursor)->point3.halves.x += 2;
            scratch->length >>= 1;
            ((ParticleQuad *)packet_cursor)->tag.bytes.length = 8;
            ((ParticleQuad *)packet_cursor)->color0.bytes.code = 58;
            {
                func_8006658C((void *)(scratch->base + scratch->length * 4),
                    (void *)packet_cursor);
                packet_cursor += 36;
            }
            func_80067F20((void *)packet_cursor, 0, 0, 96, 0);
            func_8006658C((void *)(scratch->base + scratch->length * 4),
                (void *)packet_cursor);
            {
                u8 particle_count = object->count;
                packet_cursor += 12;
                object->count = particle_count + 1;
            }
        }
    }
    ((DungeonRoot *)root_slot->draw_buffer)->cursor = packet_cursor;
    return 0;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/object_flags.h"

extern s32 rand(void);

typedef struct S807AF9A4 {
    u8 unk00[8];
    s16 state;      /* 0x08 */
    u8 unk0A[2];
    u16 counter1;   /* 0x0C */
    s8 flag_e;      /* 0x0E */
    u8 flag_f;      /* 0x0F */
    u8 buf[0x40];   /* 0x10 - 0x4F */
} S807AF9A4;

/* Initializes random buffer data and advances the cycle and completion counters. */
void advance_linked_particle_effect_state(S807AF9A4 *data)
{
    s16 state;
    s16 buf_index;
    u16 cycle_count;
    u8 progress_count;

    state = data->state;
    if (state != 0) {
        if (state != 1) {
            return;
        }
    } else {
        buf_index = 0;
        do {
            data->buf[buf_index] = rand() & 0x1F;
            buf_index = buf_index + 1;
        } while (buf_index < 0x40);
        data->counter1 = 0;
        data->flag_e = 0;
        data->buf[0x20] = 0;
        data->flag_f = 1;
        register_node((u8 *)data - 0x20, (void *)draw_linked_particle_effect_primitives);
        data->state = (u16) data->state + 1;
    }
    cycle_count = data->counter1 + 1;
    data->counter1 = cycle_count;
    if ((s16) cycle_count >= 0x11) {
        data->counter1 = 0;
    }

    progress_count = data->buf[0x20] + 1;
    data->buf[0x20] = progress_count;
    if ((s8) progress_count >= 0x41) {
        data->buf[0x20] = 0x40;
        data->flag_e = 1;
    }

    if (data->flag_f == 0) {
        *(u16 *)((u8 *)data - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
typedef struct S_807AFAE4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x6];
    u16 unk_2A;
} S_807AFAE4_0;

typedef struct S_807AFAE4_1 {
    s32 unk_00;
    u8 pad_04[0x3E];
    u16 unk_42;
} S_807AFAE4_1;   /* arg0 in func_800F72E4; pointer addresses record offset 0x18 */


/* cfail-repair: tf7-phase1-cache-v3 */

/* Initializes a linked object from the source record and invokes play_sound_if_enabled on success. */
void create_linked_particle_controller(void *sourceData) {
    S_807AFAE4_0 *linkedObject;

    linkedObject = allocate_list_node(2, sourceData - 0x20);
    if (linkedObject != 0) {
        linkedObject->unk_10 = (void *)advance_linked_particle_effect_state;
        linkedObject->unk_20 = sourceData;
        linkedObject->unk_08 = (s32) ((S_807AFAE4_1 *)((u8 *)sourceData - 0x18))->unk_00;
        linkedObject->unk_2A = (u16) ((S_807AFAE4_1 *)((u8 *)sourceData - 0x18))->unk_42;
        play_sound_if_enabled(0x703);
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_807AFB48_3 {
    void * unk_00;
    void * unk_04;
} S_807AFB48_3;   /* arg0 in func_800F7348 */

typedef struct S_807AFB48_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFB48_4;   /* ((S_807AFB48_3 *)arg0)->unk_04 in func_800F7348 */

typedef struct S_807AFB48_5 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFB48_5;   /* ((S_807AFB48_3 *)arg0)->unk_00 in func_800F7348 */


typedef struct S_807AFB48_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFB48_0;   /* arg1 in func_800F7348 */

typedef struct S_807AFB48_1 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
} S_807AFB48_1;   /* arg0 in func_800F7348; pointer addresses record offset 0x2 */

typedef struct S_807AFB48_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_807AFB48_2;   /* arg2 in func_800F7348 */


/* Advances position and selected color channels toward their targets and flags completion. */
void converge_particle_position_and_color(void *transition, S_807AFB48_0 *position, S_807AFB48_2 *color) {
    s16 steps_left;
    s32 color_bits;
    u8 next_level;

    position->unk_02 = (s16) ((u16) position->unk_02
        + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)transition)->unk_04))->unk_02
        - position->unk_02) / (s16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E));
    position->unk_06 = (s16) ((u16) position->unk_06
        + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)transition)->unk_04))->unk_06
        - position->unk_06) / (s16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E));
    position->unk_0A = (s16) ((u16) position->unk_0A
        + ((s32) (((S_807AFB48_4 *)(((S_807AFB48_3 *)transition)->unk_04))->unk_0A
        - position->unk_0A) / (s16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E));
    color_bits = color->unk_0E | (color->unk_0C | color->unk_0D);
    next_level = color_bits + ((s32) (0xC0 - color_bits) / (s16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E);
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)transition)->unk_00))->unk_14 & 1) {
        color->unk_0C = next_level;
    }
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)transition)->unk_00))->unk_14 & 2) {
        color->unk_0E = next_level;
    }
    if (((S_807AFB48_5 *)(((S_807AFB48_3 *)transition)->unk_00))->unk_14 & 4) {
        color->unk_0D = next_level;
    }
    steps_left = (u16) ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E - 1;
    ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_0E = steps_left;
    if ((steps_left << 0x10) <= 0) {
        ((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_00 = (u16) (((S_807AFB48_1 *)((u8 *)transition - 0x2))->unk_00
            | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

s32 rand();                                /* extern */
extern M2C_UNK D_800FBE24;

typedef struct S_807AFC9C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_807AFC9C_0;

typedef struct S_807AFC9C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFC9C_1;

   /* arg1 in func_800F749C */

typedef struct S_807AFC9C_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFC9C_4;   /* arg2 in func_800F749C */

typedef struct S_807AFC9C_5 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
} S_807AFC9C_5;

/* Spawns an effect near the origin with color channels selected by the source flags. */
void create_converging_color_particle(s32 spawn_arg, MovingPosition *origin, S_807AFC9C_4 *source) {
    SpriteFrameState *sprite;
    S_807AFC9C_1 *position;
    void *effect;
    S_807AFC9C_5 *effect_state;

    effect = allocate_list_node(0x212, spawn_arg);
    if (effect != NULL) {
        ((S_807AFC9C_0 *)effect)->unk_10 = (void *)converge_particle_position_and_color;
        register_node(effect, project_sprite_chain);
        position = ((S_807AFC9C_0 *)effect)->unk_08;
        position->unk_02 = (s16) ((origin->unk_02 + (rand() & 0x3F)) - 0x20);
        position->unk_06 = (s16) ((origin->unk_06 + (rand() & 0x3F)) - 0x20);
        position->unk_0A = (s16) ((origin->unk_0A + (rand() & 0x3F)) - 0x20);
        sprite = ((S_807AFC9C_0 *)effect)->unk_0C;
        sprite->source = &D_800FBE24;
        if (source->unk_14 & 1) {
            sprite->color.c.r = 0x20;
        }
        if (source->unk_14 & 2) {
            sprite->color.c.b = 0x20;
        }
        if (source->unk_14 & 4) {
            sprite->color.c.g = 0x20;
        }
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->unk_06 = 8;
        effect_state = effect + 0x20;
        sprite->flags = (u16) (sprite->flags | 0xC);
        effect_state->unk_0C = 0x10;
        ((S_807AFC9C_0 *)effect)->unk_20 = source;
        effect_state->unk_04 = origin;
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/object_flags.h"


typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Offset3;

typedef struct Position3 {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position3;

typedef struct ColorPart {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
} ColorPart;

extern u8 D_800DDC42;



typedef struct S_807AFDEC_0 {
    void * unk_00;
    u8 pad_04[0x4];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
    u8 pad_0A[0x2];
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
} S_807AFDEC_0;   /* arg0 in update_owner_attached_color_effect */

typedef struct S_807AFDEC_1_pre {
    Position3 * unk_00;
    u8 pad_04[0x14];
} S_807AFDEC_1_pre;   /* the 0x18 bytes before ((S_807AFDEC_0 *)arg0)->unk_00 in update_owner_attached_color_effect, addressed as ((S_807AFDEC_0 *)arg0)->unk_00[-1] */

typedef struct S_807AFDEC_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFDEC_1;   /* ((S_807AFDEC_0 *)arg0)->unk_00 in update_owner_attached_color_effect */

/* Position the effect and fade its selected color channels in, then out. */
void update_owner_attached_color_effect(void *effect, Position3 *position, ColorPart *tint)
{
    void *effect_base;
    Offset3 offset;
    Position3 *source_pos;
    s32 intensity;
    u16 source_x;
    s16 ticks_left;

    offset.x = 0;
    offset.y = 0;
    offset.z = -D_800DDC42 - 8;

    source_pos = ((S_807AFDEC_1_pre *)(((S_807AFDEC_0 *)effect)->unk_00))[-1].unk_00;
    source_x = source_pos->x;
    position->x = source_x;
    position->y = source_pos->y + offset.y;
    position->z = source_pos->z + offset.z;

    if (((S_807AFDEC_0 *)effect)->unk_08.s == 0) {
        intensity = tint->b | (tint->r | tint->g);
        intensity += (0xC0 - intensity) / ((S_807AFDEC_0 *)effect)->unk_0C.s;

        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 1) {
            tint->r = intensity;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 4) {
            tint->g = intensity;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 2) {
            tint->b = intensity;
        }

        {
            effect_base = (u8 *)effect - 0x20;

            if (((S_807AFDEC_0 *)effect)->unk_0C.s >= 8) {
                create_converging_color_particle(effect_base, position, ((S_807AFDEC_0 *)effect)->unk_00);
                create_converging_color_particle(effect_base, position, ((S_807AFDEC_0 *)effect)->unk_00);
                create_converging_color_particle(effect_base, position, ((S_807AFDEC_0 *)effect)->unk_00);
            }

            ticks_left = ((S_807AFDEC_0 *)effect)->unk_0C.u - 1;
            ((S_807AFDEC_0 *)effect)->unk_0C.u = ticks_left;
            if ((ticks_left << 16) <= 0) {
                ((S_807AFDEC_0 *)effect)->unk_0C.u = 8;
                ((S_807AFDEC_0 *)effect)->unk_08.u++;
                return;
            }
        }
    } else {
        intensity = tint->b | (tint->r | tint->g);
        intensity += -intensity / ((S_807AFDEC_0 *)effect)->unk_0C.s;

        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 1) {
            tint->r = intensity;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 4) {
            tint->g = intensity;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 2) {
            tint->b = intensity;
        }

        ticks_left = ((S_807AFDEC_0 *)effect)->unk_0C.u - 1;
        ((S_807AFDEC_0 *)effect)->unk_0C.u = ticks_left;
        if ((ticks_left << 16) <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct Bank7ce_18_Pair {
    s32 first;
    s32 second;
} Bank7ce_18_Pair;

extern void draw_textured_ellipse();
extern u8 D_800FBE30[12];
extern u8 D_800FBE3C[12];

typedef struct S_807B004C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_807B004C_0;

typedef struct S_807B004C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s16 unk_0C;
} S_807B004C_2;

typedef struct S_807B004C_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_807B004C_3;   /* arg0 in func_800F784C */

/* Creates a child object, initializes its state, and loads its graphics. */
void create_owner_attached_color_effect(void *parent_data) {
    Bank7ce_18_Pair texture_rect;
    s32 rect_origin;
    s32 rect_size;
    Bank7ce_18_Pair *rect_ptr;
    void *child;
    SpriteFrameState *render_state;
    S_807B004C_2 *child_data;

    child = allocate_list_node(2, (u8 *)parent_data - 0x20);
    if (child != 0) {
        ((S_807B004C_0 *)child)->unk_10 = update_owner_attached_color_effect;
        register_node(child, project_sprite_chain);
        rect_origin = 0x01000340;
        rect_size = 0x200020;
        rect_ptr = &texture_rect;
        render_state = ((S_807B004C_0 *)child)->unk_0C;
        render_state->source = D_800FBE30;
        render_state->scale_x = 0x1000;
        render_state->scale_y = 0x800;
        child_data = (u8 *)child + 0x20;
        ((S_807B004C_0 *)child)->unk_20 = parent_data;
        child_data->unk_0A = ((S_807B004C_3 *)parent_data)->unk_2A;
        child_data->unk_0C = 0x30;
        texture_rect.second = rect_size;
        texture_rect.first = rect_origin;
        draw_textured_ellipse(D_800FBE3C, rect_ptr, 1, 0);
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"


/* Updates position using decaying speed and sets completion flags when speed expires. */
void advance_reverse_direction_particle(void *motion_data, s16 *position) {
    s16 *motion = motion_data;
    s16 next_speed;

    if (position[5] < (s16)sample_terrain_surface_height((u16) position[1], (u16) position[3], position[5] + 2)) {
        ((s32 *) position)[0] -= (dir_step_x[motion[10]] * motion[25]) << 11;
        ((s32 *) position)[1] -= (dir_step_y[motion[10]] * motion[25]) << 11;
        ((s32 *) position)[2] += (0xC0 - motion[25]) << 10;
    }

    next_speed = (u16) motion[25] - 8;
    motion[25] = next_speed;
    if ((next_speed << 16) <= 0) {
        ((u16 *) motion)[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_807B0238_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_807B0238_3;

typedef struct S_807B0238_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807B0238_5;

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_800F7A38 */

s32 rand();                                /* extern */
extern M2C_UNK D_800FBE24;

typedef struct S_807B0238_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 * unk_10;
} S_807B0238_0;

typedef struct S_807B0238_2 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_807B0238_2;

/* Creates an effect at a randomized offset from the source and initializes its state. */
void create_reverse_direction_particle(EntityRec *source, s16 state_value, s32 render_value) {
    S_807B0238_2 *effect_state;
    void *effect;
    SpriteFrameState *render_data;

    effect = allocate_list_node(0x212, source);
    if (effect != NULL) {
        ((S_807B0238_0 *)effect)->unk_10 = (void *)advance_reverse_direction_particle;
        register_node(effect, project_sprite_chain);
        ((S_807B0238_5 *)(((S_807B0238_3 *)effect)->unk_08))->unk_02 =
            (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_02 + (rand() & 0x3F)) - 0x20);
        ((S_807B0238_5 *)(((S_807B0238_3 *)effect)->unk_08))->unk_06 =
            (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_06 + (rand() & 0x3F)) - 0x20);
        ((S_807B0238_5 *)(((S_807B0238_3 *)effect)->unk_08))->unk_0A =
            (s16) ((((MovingPosition *)((*(void * *)&source->z)))->unk_0A + (rand() & 0x3F)) - 0x20);
        render_data = ((S_807B0238_0 *)effect)->unk_0C;
        effect_state = effect + 0x20;
        render_data->source = &D_800FBE24;
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        render_data->color.word = render_value;
        render_data->unk_06 = 8;
        effect_state->unk_14 = state_value;
        effect_state->unk_32 = (s16) ((rand() & 0xFF) | 0x80);
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"

extern s8 spell_effect_selector_cache;

/* Set the current entity state to one, reset the global status, increment the counter, and set flag 8. */
void begin_active_object_action(void) {
    *((s8 *)D_800FBE1C + 0xD8) = 1;
    spell_effect_selector_cache = -1;
    g_dungeon_status.activity_counts.parts.pending_action_count++;
    system_update_flags |= 8;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Calls play_sound_if_enabled with the fixed argument 0xB4. */
void func_800F7BA0(void) {
    play_sound_if_enabled(0xB4);
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[0x71];
    u8 flags;
    u8 pad1[0x46];
    u8 state;
} Entity;


/* Set the current entity state to three, decrement the counter, and clear the global and entity flags. */
void finish_active_object_action(void) {
    Entity *entity;

    entity = (Entity *)((u8 *)D_800FBE1C + 0x20);
    entity->state = 3;
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    system_update_flags &= 0xFFF7;
    entity->flags &= 0x7F;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
extern int abs(int);

typedef struct S_807B040C_0 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 * unk_0C;
} S_807B040C_0;   /* root in update_special_actor_transition */

typedef struct S_807B040C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0xC];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    union { s16 s16; u8 u8; } unk_AA;   /* accessed as both */
    u8 pad_AC[0x2];
    union { s16 s16; u8 u8; } unk_AE;   /* accessed as both */
    u8 pad_B0[0x8];
    u8 unk_B8;
} S_807B040C_1;   /* entity in update_special_actor_transition */

typedef struct S_807B040C_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_807B040C_6;   /* entity_aux in update_special_actor_transition */

typedef struct S_807B040C_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0xE];
    u16 unk_16;
} S_807B040C_7;   /* motion in update_special_actor_transition */

extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void get_offset_map_cell_value_and_flags(u8, u8, s16, u16 *);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern s32 check_left_tile_and_center_height(s32, s32, s16);

/* Move the entity to a passable tile near the room and update tile occupancy. */
s32 update_special_actor_transition(void) {
    DirectionOffsets offsets = dungeon_7ce800_directions;
    u16 collision_flags;
    u8 *root = (u8 *)D_800FBE1C;
    u8 *entity = root + 0x20;
    s32 *motion = ((S_807B040C_0 *)root)->unk_08;
    s32 entity_flags;
    s32 state = ((S_807B040C_1 *)entity)->unk_9B;
    u8 *target = ((S_807B040C_0 *)root)->unk_0C;
    u8 *entity_aux = entity;
    s32 direction;
    s32 dx;
    s32 dy;
    s32 distance_x;
    s32 world_x;
    s32 target_y;
    s32 delta_y;
    s32 move_ticks;
    s16 ground_height;
    s32 tile_flags;
    u8 tile_x;
    u8 tile_y;
    s16 *direction_offset;
    TileObject *room;
    ObjectPosition *collision;
    s32 distance_y;

    switch (state) {
    case 0:
        {
            u8 *room_page;
            TileObject *nearby_room;
            s32 target_coord;
            s32 room_distance_y;

            room_page = (u8 *)0x80080000;
            nearby_room = &reference_tile_object;
            dx = nearby_room->tile_position.parts.tile_x;
            target_coord = ((SpriteFrameState *)target)->unk_24;
            dx -= target_coord;
            dx = abs(dx);
            if (dx < 3) {
                room_distance_y = nearby_room->tile_position.parts.tile_y;
                target_coord = ((SpriteFrameState *)target)->unk_25;
                room_distance_y -= target_coord;
                room_distance_y = abs(room_distance_y);
                if (room_distance_y < 3) {
                    s32 result;
                    s16 next_state;

                    result = 1;
                    ((S_807B040C_1 *)entity)->unk_9B = ((s16)(0x63));
                    next_state = 2;
                    ((S_807B040C_1 *)entity)->unk_B8 = next_state;
                    return result;
                }
            }
        }

        ((S_807B040C_1 *)entity)->unk_9B++;
        direction = get_direction_toward_target_position(motion);
        direction += 4;
        if (direction >= 8) {
            direction -= 8;
        }
        room = &reference_tile_object;
        collision = &view_reference_entity;

        while (1) {
            get_offset_map_cell_value_and_flags(room->tile_position.parts.tile_x, room->tile_position.parts.tile_y,
                          (s16)direction, &collision_flags);
            if (!(collision_flags & 0xB400)) {
                direction_offset = (s16 *)&offsets + direction * 2;
                ((S_807B040C_1 *)entity)->unk_AA.s16 = room->tile_position.parts.tile_x + (u16)direction_offset[0];
                ((S_807B040C_1 *)entity)->unk_AE.s16 = room->tile_position.parts.tile_y + (u16)direction_offset[1];
                if ((s16)check_left_tile_and_center_height(
                        ((((S_807B040C_1 *)entity)->unk_AA.s16 << 6) + 0x20) & 0xFFE0,
                        ((((S_807B040C_1 *)entity)->unk_AE.s16 << 6) + 0x20) & 0xFFE0,
                        collision->z.w.i) == 0) {
                    break;
                }
            }
            direction++;
            if (direction >= 8) {
                direction = 0;
            }
        }

        {
            s32 y_is_farther;

            distance_x = ((S_807B040C_1 *)entity)->unk_AA.s16;
            delta_y = ((SpriteFrameState *)target)->unk_24;
            target_y = ((SpriteFrameState *)target)->unk_25;
            distance_x -= delta_y;
            delta_y = ((S_807B040C_1 *)entity)->unk_AE.s16;
            if (distance_x < 0) {
                distance_x = -distance_x;
            }
            delta_y -= target_y;
            move_ticks = delta_y;
            distance_y = abs(move_ticks);
            y_is_farther = distance_x < distance_y;
            if (y_is_farther) {
                move_ticks = distance_y * 4;
            } else {
                move_ticks = distance_x * 4;
            }
            ((S_807B040C_1 *)entity)->unk_96.s = move_ticks;

            entity_flags = ((S_807B040C_6 *)entity_aux)->unk_1C;
            tile_x = ((SpriteFrameState *)target)->unk_24;
            tile_y = ((SpriteFrameState *)target)->unk_25;
            tile_flags = 0x3000;
            if (entity_flags & 0x2000) {
                tile_flags = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_flags);
        }
        /* fall through */
    case 1:
    move_entity:
        {
            s32 aligned_x;

            world_x = ((S_807B040C_1 *)entity)->unk_AA.s16;
            world_x <<= 6;
            world_x += 0x20;
            move_ticks = ((S_807B040C_1 *)entity)->unk_AE.s16 << 6;
            distance_y = move_ticks + 0x20;
            aligned_x = world_x & 0xFFE0;
            ground_height = (s16)sample_terrain_surface_height(aligned_x, distance_y & 0xFFE0, -0x400);
        }
        world_x = ((S_807B040C_1 *)entity)->unk_AA.s16;
        world_x <<= 6;
        world_x += 0x20;
        motion[3] = ((world_x << 16) - motion[0]) /
                    ((S_807B040C_1 *)entity)->unk_96.s;
        motion[4] = ((((((S_807B040C_1 *)entity)->unk_AE.s16 << 6) + 0x20) << 16) -
                     motion[1]) /
                    ((S_807B040C_1 *)entity)->unk_96.s;
        motion[5] = (((s16)ground_height - ((S_807B040C_6 *)entity_aux)->unk_88) << 16) /
                    ((S_807B040C_1 *)entity)->unk_96.s;
        ((S_807B040C_6 *)entity_aux)->unk_88 =
            (u16)((S_807B040C_6 *)entity_aux)->unk_88 + ((S_807B040C_7 *)motion)->unk_16;

        dx = motion[3];
        motion[5] = 0;
        if (dx == 0) {
            direction = 6;
            if (motion[4] > 0) {
                direction = 2;
            }
        } else {
            dy = motion[4];
            if (dy == 0) {
                direction = (dx < 1) << 2;
            } else {
                if (dx > 0) {
                    direction = 7;
                    if (dy > 0) {
                        direction = 1;
                    }
                } else {
                    direction = 5;
                    if (dy > 0) {
                        direction = 3;
                    }
                }
            }
        }
        ((S_807B040C_6 *)entity_aux)->unk_2A = direction << 9;
        ((S_807B040C_1 *)entity)->unk_96.u--;
        if ((s16)((S_807B040C_1 *)entity)->unk_96.u > 0) {
            return 0;
        }
        ((S_807B040C_1 *)entity)->unk_9B++;
        break;

    case 2:
        ((SpriteFrameState *)target)->unk_24 = ((S_807B040C_1 *)entity)->unk_AA.u8;
        ((SpriteFrameState *)target)->unk_25 = ((S_807B040C_1 *)entity)->unk_AE.u8;
        motion[0] = ((((SpriteFrameState *)target)->unk_24 << 6) + 0x20) << 16;
        motion[1] = ((((SpriteFrameState *)target)->unk_25 << 6) + 0x20) << 16;
        motion[5] = 0;
        motion[4] = 0;
        motion[3] = 0;
        ((S_807B040C_1 *)entity)->unk_88 = (s16)sample_terrain_surface_height(((S_807B040C_7 *)motion)->unk_02,
                                                 ((S_807B040C_7 *)motion)->unk_06, -0x400);
        set_record_integer_tile_center(motion, ((SpriteFrameState *)target)->unk_24, ((SpriteFrameState *)target)->unk_25);
        {

            entity_flags = ((S_807B040C_1 *)entity)->unk_1C;
            tile_x = ((SpriteFrameState *)target)->unk_24;
            tile_y = ((SpriteFrameState *)target)->unk_25;
            tile_flags = 0x3000;
            if (entity_flags & 0x2000) {
                tile_flags = 0x300;
            }
        }
        cycle_map_cell_flags(tile_x, tile_y, tile_flags);
        ((S_807B040C_1 *)entity)->unk_B8 = state;
        return 1;
    default:
        break;
    }
    return 0;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "m2c_compat.h"


typedef struct S_807B08D4_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    s8 unk_9B;
} S_807B08D4_0;

/* Clears the state block's fields at offsets 0x96 and 0x9B. */
void reset_active_object_action(void) {
    S_807B08D4_0 *state;

    state = D_800FBE1C + 0x20;
    state->unk_96 = 0;
    state->unk_9B = 0;
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"


typedef struct S_807B08F0_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_807B08F0_0;

typedef struct S_807B08F0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
} S_807B08F0_1;

/* Allocate and initialize an object at the center of the specified tile. */
void func_800F80F0(s16 tile_x, s16 tile_y, s16 initial_value) {
    S_807B08F0_1 *state;
    void *object;

    object = allocate_flagged_object_node(2);
    if (object != NULL) {
        ((S_807B08F0_0 *)object)->unk_10 = (void *)emit_scattered_animated_particles;
        register_node(object, (void *)render_particle_effect_object);
        state = object + 0x20;
        ((S_807B08F0_0 *)object)->unk_20 = (u16) (tile_x * 0x40 + 0x20);
        state->unk_02 = (u16) (tile_y * 0x40 + 0x20);
        state->unk_04 = (s16)sample_terrain_surface_height(((S_807B08F0_0 *)object)->unk_20, state->unk_02, -0x400);
        state->unk_06 = initial_value;
        state->unk_08 = 0;
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_807B09A0_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_807B09A0_4;

typedef struct S_807B09A0_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_807B09A0_5;

s32 rand();
extern M2C_UNK D_800DEED0;

typedef struct S_807B09A0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_807B09A0_0;   /* arg0 in func_800F81A0 */

typedef struct S_807B09A0_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 * unk_10;
} S_807B09A0_1;

typedef struct S_807B09A0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_807B09A0_3;   /* &D_800DEED0 in func_800F81A0 */

/* Spawn a particle near the emitter with randomized motion every other update. */
void emit_scattered_animated_particles(S_807B09A0_0 *emitter) {
    s32 spawn_x;
    s32 spawn_y;
    s32 sprite_config;
    u16 tick_count;
    SpriteFrameState *sprite;
    S_807B09A0_1 *particle;

    tick_count = emitter->unk_08 + 1;
    emitter->unk_08 = tick_count;
    if (tick_count & 1) {
        particle = allocate_list_node(0x312, ((s32 *)&scene_object_list_anchor.next));
        if (particle != NULL) {
            particle->unk_10 = (void *)move_sprite_until_animation_finishes;
            register_node(particle, project_sprite_chain);
            sprite = particle->unk_0C;
            spawn_x = (emitter->unk_00 + (rand() % 48)) - 0x18;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_02 = spawn_x;
            spawn_y = (emitter->unk_02 + (rand() % 48)) - 0x18;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_06 = spawn_y;
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_0A = (u16) (emitter->unk_04 - (rand() & 7));
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_0C = (s32) (((rand() & 0xFF) - 0x7F) << 0xA);
            ((S_807B09A0_5 *)(((S_807B09A0_4 *)particle)->unk_08))->unk_10 = (s32) (((rand() & 0xFF) - 0x7F) << 0xA);
            sprite->scale_y = 0xC00;
            sprite->scale_x = 0xC00;
            sprite->tpage_abr = 0x60;
            sprite->unk_00 = &D_800DEED0;
            sprite->flags = (u16) (sprite->flags | 0xC);
            sprite_config = ((S_807B09A0_3 *)(&D_800DEED0))->unk_04;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->color.word = 0xA0A0A0;
            sprite->source = sprite_config;
        }
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
/* The root-pointer member at D_80083150 + 0x10. */
typedef struct { u8 *root; } RenderRootSlot;

typedef struct S_807B0B3C_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_807B0B3C_0_pre;   /* the 0x8 bytes before initial in render_particle_effect_object, addressed as initial[-1] */

typedef struct S_807B0B3C_0 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_807B0B3C_0;   /* initial in render_particle_effect_object */

typedef struct S_807B0B3C_1 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u16 unk_04;
    s16 unk_06;
    union { u16 u16; u8 u8; } unk_08;   /* accessed as both */
} S_807B0B3C_1;   /* effect in render_particle_effect_object */

typedef struct S_807B0B3C_2 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
} S_807B0B3C_2;   /* a3p in render_particle_effect_object */

typedef struct S_807B0B3C_3 {
    union { u16 v; s16 n; } unk_00;   /* accessed as both */
    union { u16 v; s16 n; } unk_02;   /* accessed as both */
    u16 unk_04;
} S_807B0B3C_3;   /* a0p in render_particle_effect_object */

typedef struct S_807B0B3C_4 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x6];
    u16 unk_0C;
} S_807B0B3C_4;   /* (u8 *)a2v in render_particle_effect_object */

typedef struct S_807B0B3C_5 {
    u16 unk_00;
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_807B0B3C_5;   /* (u8 *)a2p in render_particle_effect_object */

typedef struct S_807B0B3C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_807B0B3C_6;   /* (u8 *)v1 in render_particle_effect_object */

typedef struct S_807B0B3C_7 {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    s32 unk_10;
    s32 unk_14;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s16 v; } at02; } unk_18;   /* overlapping accesses */
    s32 unk_1C;
    s32 unk_20;
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    s32 unk_2C;
    s8 unk_30;
    s8 unk_31;
} S_807B0B3C_7;   /* prim in render_particle_effect_object */

typedef struct S_807B0B3C_8 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_807B0B3C_8;   /* verts in render_particle_effect_object */

typedef struct S_807B0B3C_9 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_9;   /* rootp in render_particle_effect_object */

typedef struct S_807B0B3C_10 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_10;   /* entryp in render_particle_effect_object */

typedef struct S_807B0B3C_11 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_807B0B3C_11;   /* a1p in render_particle_effect_object */

typedef struct S_807B0B3C_12 {
    union { u32 u; s32 s; } unk_00;   /* accessed as both */
    union { u32 u; s32 s; } unk_04;   /* accessed as both */
    union { u32 u; s32 s; } unk_08;   /* accessed as both */
    union { u32 u; s32 s; } unk_0C;   /* accessed as both */
} S_807B0B3C_12;   /* colors in render_particle_effect_object */

typedef struct S_807B0B3C_13 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_807B0B3C_13;   /* dst in render_particle_effect_object */

typedef struct S_807B0B3C_14 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x4];
    u16 unk_10;
    u8 pad_12[0x6];
    u16 unk_18;
} S_807B0B3C_14;   /* scratch in render_particle_effect_object */

typedef struct S_807B0B3C_15 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_15;   /* (u8 *)offset in render_particle_effect_object */

typedef struct {
    s32 projection_flag;
} StackLocals;

extern s32 func_80065420(void *, void *, void *, void *);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern void func_80066640(void *, s32);
extern void func_80066708(void *);
extern void func_8006671C(u8 *primitive);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern u8 D_80083150[];

/* Builds and queues textured and shaded quads for an effect and advances to the next object. */
s32 render_particle_effect_object(void *object, s32 caller_a1, void *caller_a2) {
    u8 *scratch;
    u8 *colors;
    u8 *verts;
    u8 *effect;
    s16 saved_a1 = caller_a1;
    void *saved_a2 = caller_a2;
    StackLocals stack;
    u32 draw_value;
    s32 vertex_index;
    s32 frame_remainder;
    s32 pair_addr;
    s32 depth;
    s32 bucket_offset;
    s32 gray;
    void *prim_arg;
    s32 tex_coord;
    s32 tex_left;
    u8 *world_vertex;
    u8 *screen_vertex;
    u8 *prim;
    u8 *shaded_prim;
    u8 *draw_prim;
    u8 *next_object;
    u16 component;
    u16 component_2;
    u16 component_3;
    u16 component_4;
    u16 component_5;
    s32 coord;
    u8 **global_slot;
    u8 *render_state_m;
    u8 *bucket_ptr_m;

    scratch = (u8 *)0x1F800000;
    colors = scratch;
    verts = scratch;
    colors = (u8 *)((u32)colors | 0x40);
    verts = (u8 *)((u32)verts | 0x80);
    do {
        global_slot = (u8 **)(D_80083150 + 0x10);
        effect = (u8 *)object;
        if ((((S_807B0B3C_0 *)object)->unk_06 >> 10) & 1) {
            u8 *vertex_pair;
            u8 *vertex_ptr;
            s32 coord_half;

            for (vertex_index = 0; vertex_index < 2; vertex_index++) {
                vertex_pair = scratch + vertex_index * 0x10;
                bucket_ptr_m = (u8 *)(vertex_index * 2);
                coord_half = ((S_807B0B3C_1 *)effect)->unk_00.u;
                stack.projection_flag = (s32)bucket_ptr_m;
                ((S_807B0B3C_2 *)vertex_pair)->unk_08 = coord_half;
                ((S_807B0B3C_2 *)vertex_pair)->unk_00 = coord_half;
                vertex_ptr = vertex_pair + 8;
                bucket_ptr_m = (u8 *)(((S_807B0B3C_1 *)effect)->unk_02.s);
                if (vertex_index < 2) {
                    coord_half = (s32)bucket_ptr_m - 0x20;
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_02.v = coord_half;
                } else {
                    coord_half = (s32)bucket_ptr_m + 0x20;
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_02.v = coord_half;
                }
                pair_addr = stack.projection_flag;
                coord_half = ((S_807B0B3C_3 *)vertex_ptr)->unk_02.v;
                pair_addr <<= 3;
                ((S_807B0B3C_2 *)vertex_pair)->unk_02 = coord_half;
                draw_value = (u32)(((S_807B0B3C_1 *)effect)->unk_04);
                pair_addr += (u32)scratch;
                ((S_807B0B3C_4 *)((u8 *)pair_addr))->unk_0C = (s32)draw_value;
                coord_half = ((S_807B0B3C_1 *)effect)->unk_08.u16;
                frame_remainder = (s16)coord_half;
                frame_remainder %= 5;
                draw_value += frame_remainder;
                draw_value -= 0x36;
                ((S_807B0B3C_4 *)((u8 *)pair_addr))->unk_04 = (s32)draw_value;
            }
        } else {
            u8 *vertex_ptr;
            s32 second_pair;
            s32 pairs_end;

            pair_addr = (s32)scratch;
            second_pair = (s32)scratch + 0x10;
            pairs_end = (s32)scratch + 0x20;
    build_x_pairs:
            bucket_ptr_m = (u8 *)(((S_807B0B3C_1 *)effect)->unk_00.s);
            vertex_ptr = (u8 *)pair_addr + 8;
            if (pair_addr < second_pair) {
                caller_a1 = (s32)bucket_ptr_m - 0x20;
                ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_08 = caller_a1;
            } else {
                caller_a1 = (s32)bucket_ptr_m + 0x20;
                ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_08 = caller_a1;
            }
            caller_a1 = ((S_807B0B3C_3 *)vertex_ptr)->unk_00.v;
            ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_00 = caller_a1;
            caller_a1 = ((S_807B0B3C_1 *)effect)->unk_02.u;
            bucket_ptr_m = (u8 *)((s32)((u32)8 + (u32)pair_addr));
            ((S_807B0B3C_6 *)((u8 *)(s32)bucket_ptr_m))->unk_02 = caller_a1;
            ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_02 = caller_a1;
            draw_value = (u32)(((S_807B0B3C_1 *)effect)->unk_04);
            ((S_807B0B3C_6 *)((u8 *)(s32)bucket_ptr_m))->unk_04 = (s32)draw_value;
            caller_a1 = ((S_807B0B3C_1 *)effect)->unk_08.u16;
            frame_remainder = (s16)caller_a1;
            frame_remainder %= 5;
            draw_value += frame_remainder;
            draw_value -= 0x36;
            ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_04 = draw_value;
            pair_addr += 0x10;
            if (pair_addr < pairs_end) goto build_x_pairs;
        }

        depth = 0;

        for (vertex_index = 0; vertex_index < 4; vertex_index++) {
            s32 vertex_depth = func_80065420(scratch + vertex_index * 8, verts + vertex_index * 4, &stack.projection_flag, &stack.projection_flag);
            bucket_ptr_m = (u8 *)(depth - 8);
            depth = (s32)bucket_ptr_m + vertex_depth;
        }

        {
            s32 rounded_depth;

            rounded_depth = depth;
            depth = (rounded_depth / 4);
        }

        {
            u8 *render_state;

            render_state = ((RenderRootSlot *)global_slot)->root;
            prim = *(u8 **)(render_state + 0x8D0);
            prim_arg = (void *)prim;
            *(u8 **)(render_state + 0x8D0) = prim + 0x34;
        }
        gray = 0xA0A0A0;
        ((S_807B0B3C_7 *)prim)->unk_1C = 0;
        ((S_807B0B3C_7 *)prim)->unk_04 = 0;
        ((S_807B0B3C_7 *)prim)->unk_28 = gray;
        ((S_807B0B3C_7 *)prim)->unk_10 = gray;
        func_8006671C(prim_arg);
        func_80066640(prim, 1);
        ((S_807B0B3C_7 *)prim)->unk_18.at02.v = func_80066460(0, 1, 0x280, 0x100);
        {
            u16 clut;

            clut = func_8006649C(0x90, 0x1F7);
            tex_left = ((S_807B0B3C_8 *)verts)->unk_00;
            ((S_807B0B3C_7 *)prim)->unk_0C.at02.v = clut;
            ((S_807B0B3C_7 *)prim)->unk_08 = tex_left;
        }
        ((S_807B0B3C_7 *)prim)->unk_14 = ((S_807B0B3C_8 *)verts)->unk_04;
        ((S_807B0B3C_7 *)prim)->unk_20 = ((S_807B0B3C_8 *)verts)->unk_08;
        ((S_807B0B3C_7 *)prim)->unk_2C = ((S_807B0B3C_8 *)verts)->unk_0C;

        draw_value = ((S_807B0B3C_1 *)effect)->unk_08.u16;
        draw_value &= 7;
        tex_coord = (draw_value & 3) << 5;
        tex_left = tex_coord - 0x80;
        tex_coord -= 0x61;
        draw_value >>= 2;
        draw_value <<= 5;
        ((S_807B0B3C_7 *)prim)->unk_30 = tex_coord;
        ((S_807B0B3C_7 *)prim)->unk_24 = tex_coord;
        tex_coord = draw_value - 0x40;
        draw_value -= 0x21;
        ((S_807B0B3C_7 *)prim)->unk_31 = tex_coord;
        ((S_807B0B3C_7 *)prim)->unk_18.at01.v = tex_coord;
        ((S_807B0B3C_7 *)prim)->unk_18.at00.v = tex_left;
        ((S_807B0B3C_7 *)prim)->unk_0C.at00.v = tex_left;
        ((S_807B0B3C_7 *)prim)->unk_25 = draw_value;
        ((S_807B0B3C_7 *)prim)->unk_0C.at01.v = draw_value;

        if ((u32)depth < 0x1E0U) {
            s32 textured_offset;

            {
                u32 prim_tag;
                u32 bucket_tag;

                textured_offset = depth * 4;
                prim_tag = ((S_807B0B3C_7 *)prim)->unk_00;
                render_state_m = (u8 *)((u32)textured_offset + (u32)((RenderRootSlot *)global_slot)->root);
                prim_tag &= 0xFF000000U;

                bucket_tag = ((S_807B0B3C_9 *)render_state_m)->unk_B0;

                ((S_807B0B3C_7 *)prim)->unk_00 = prim_tag | (bucket_tag & 0xFFFFFFU);
            }
            {
                u8 *render_state;
                u8 *bucket_ptr;

                render_state = ((RenderRootSlot *)global_slot)->root;

                bucket_ptr = (u8 *)((u32)textured_offset + (u32)render_state);
                ((S_807B0B3C_10 *)bucket_ptr)->unk_B0 =
                    (((S_807B0B3C_10 *)bucket_ptr)->unk_B0 & 0xFF000000U) |
                    ((u32)prim & 0xFFFFFFU);
            }
        }

        {
            u8 *vertex_ptr;
            u8 *color_ptr;

            for (vertex_index = 3; vertex_index >= 0; vertex_index--) {
                vertex_ptr = scratch + vertex_index * 8;
                color_ptr = colors + vertex_index * 4;
                coord = ((S_807B0B3C_1 *)effect)->unk_00.s;
                if (vertex_index < 2) {
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_00.n = coord - 0x20;
                } else {
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_00.n = coord + 0x20;
                }
                coord = ((S_807B0B3C_1 *)effect)->unk_02.s;
                if (vertex_index & 1) {
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_02.n = coord + 0x20;
                } else {
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_02.n = coord - 0x20;
                }
                ((S_807B0B3C_3 *)vertex_ptr)->unk_04 = ((S_807B0B3C_1 *)effect)->unk_04;
                tex_coord = (((S_807B0B3C_1 *)effect)->unk_08.u8 & 3) * 8;
                ((S_807B0B3C_11 *)color_ptr)->unk_02 = tex_coord;
                ((S_807B0B3C_11 *)color_ptr)->unk_01 = tex_coord;
                ((S_807B0B3C_11 *)color_ptr)->unk_00 = tex_coord;
            }
        }

        coord = ((S_807B0B3C_1 *)effect)->unk_06;
        switch (coord) {
        case 0:
            ((S_807B0B3C_12 *)colors)->unk_08.u = 0x808080;
            ((S_807B0B3C_12 *)colors)->unk_00.u = 0x808080;
            component = (*(u16 *)((u8 *)effect + 2));
            {
                u8 *vertex_ptr;

                vertex_ptr = scratch + 0x10;
                ((S_807B0B3C_13 *)vertex_ptr)->unk_02 = component;
            }
            ((S_807B0B3C_14 *)scratch)->unk_02 = component;
            break;
        case 0x400:
            component_2 = ((S_807B0B3C_1 *)effect)->unk_00.u;
            ((S_807B0B3C_12 *)colors)->unk_0C.u = 0x808080;
            ((S_807B0B3C_12 *)colors)->unk_08.u = 0x808080;
            ((S_807B0B3C_14 *)scratch)->unk_18 = component_2;
            ((S_807B0B3C_14 *)scratch)->unk_10 = component_2;
            break;
        case 0x800:
            ((S_807B0B3C_12 *)colors)->unk_0C.u = 0x808080;
            ((S_807B0B3C_12 *)colors)->unk_04.u = 0x808080;
            component_3 = (*(u16 *)((u8 *)effect + 2));
            {
                u8 *vertex_ptr;

                vertex_ptr = scratch + 0x18;
                (*(u16 *)((u8 *)vertex_ptr + 2)) = component_3;
            }
            ((S_807B0B3C_14 *)scratch)->unk_0A = component_3;
            break;
        case 0xC00:
            component_4 = ((S_807B0B3C_1 *)effect)->unk_00.u;
            ((S_807B0B3C_12 *)colors)->unk_04.u = 0x808080;
            ((S_807B0B3C_12 *)colors)->unk_00.u = 0x808080;
            ((S_807B0B3C_14 *)scratch)->unk_08 = component_4;
            ((S_807B0B3C_14 *)scratch)->unk_00 = component_4;
            break;
        }
        for (vertex_index = 3; vertex_index >= 0; vertex_index--) {
            func_80065420(scratch + vertex_index * 8, verts + vertex_index * 4, &stack.projection_flag, &stack.projection_flag);
        }

        if ((u32)depth < 0x1E0U) {
            s32 blend_mode;
            s32 page_x;
            s32 page_y;

            {
                u8 *render_state;

                render_state = ((RenderRootSlot *)global_slot)->root;
                shaded_prim = *(u8 **)(render_state + 0x8D0);
                {
                    s32 first_color;

                    first_color = ((S_807B0B3C_12 *)colors)->unk_00.s;
                    *(u8 **)(render_state + 0x8D0) = shaded_prim + 0x24;
                    ((S_807B0B3C_7 *)shaded_prim)->unk_04 = first_color;
                }
            }
            ((S_807B0B3C_7 *)shaded_prim)->unk_0C.at00u.v = ((S_807B0B3C_12 *)colors)->unk_04.s;
            ((S_807B0B3C_7 *)shaded_prim)->unk_14 = ((S_807B0B3C_12 *)colors)->unk_08.s;
            ((S_807B0B3C_7 *)shaded_prim)->unk_1C = ((S_807B0B3C_12 *)colors)->unk_0C.s;
            func_80066708(shaded_prim);
            func_80066640(shaded_prim, 1);
            {
                s32 vertex;
                u32 prim_tag;
                u32 bucket_tag;

                vertex = ((S_807B0B3C_8 *)verts)->unk_00;
                prim_tag = ((S_807B0B3C_7 *)shaded_prim)->unk_00;

                ((S_807B0B3C_7 *)shaded_prim)->unk_08 = vertex;
                vertex = ((S_807B0B3C_8 *)verts)->unk_04;
                bucket_offset = depth * 4;
                ((S_807B0B3C_7 *)shaded_prim)->unk_10 = vertex;
                vertex = ((S_807B0B3C_8 *)verts)->unk_08;
                draw_value = 0;
                ((S_807B0B3C_7 *)shaded_prim)->unk_18.at00u.v = vertex;
                vertex = ((S_807B0B3C_8 *)verts)->unk_0C;
                blend_mode = 1;
                ((S_807B0B3C_7 *)shaded_prim)->unk_20 = vertex;
                prim_tag &= 0xFF000000U;

                render_state_m = (u8 *)((u32)bucket_offset + (u32)((RenderRootSlot *)global_slot)->root);
                bucket_tag = ((S_807B0B3C_9 *)render_state_m)->unk_B0;

                ((S_807B0B3C_7 *)shaded_prim)->unk_00 = prim_tag | (bucket_tag & 0xFFFFFFU);
            }
            {
                u32 bucket_tag;
                u8 *bucket;

                bucket = (u8 *)((u32)bucket_offset + (u32)((RenderRootSlot *)global_slot)->root);
                bucket_tag = ((S_807B0B3C_10 *)bucket)->unk_B0 & 0xFF000000U;
                bucket_tag |= (u32)shaded_prim & 0xFFFFFFU;

                (((S_807B0B3C_10 *)bucket)->unk_B0) = bucket_tag;
                bucket_ptr_m = ((RenderRootSlot *)global_slot)->root;
                page_x = draw_value;
                draw_prim = *(u8 **)(bucket_ptr_m + 0x8D0);
                page_y = draw_value;
                *(u8 **)(bucket_ptr_m + 0x8D0) = draw_prim + 0xC;
            }
            component_5 = func_80066460(draw_value, blend_mode, page_x, page_y);
            {
                s32 zero;
                void *draw_mode_arg;

                draw_mode_arg = (void *)draw_prim;
                zero = 0;
                func_80067F20(draw_mode_arg, zero, zero, component_5, 0);
            }

            {
                u32 prim_tag;
                u32 bucket_tag;

                prim_tag = ((S_807B0B3C_7 *)draw_prim)->unk_00;
                render_state_m = (u8 *)((u32)bucket_offset + (u32)((RenderRootSlot *)global_slot)->root);
                prim_tag &= 0xFF000000U;

                bucket_tag = ((S_807B0B3C_10 *)render_state_m)->unk_B0;

                ((S_807B0B3C_7 *)draw_prim)->unk_00 = prim_tag | (bucket_tag & 0xFFFFFFU);
            }
            {
                u8 *render_state;

                render_state = ((RenderRootSlot *)global_slot)->root;

                bucket_offset += (s32)render_state;
                ((S_807B0B3C_15 *)((u8 *)bucket_offset))->unk_B0 =
                    (((S_807B0B3C_15 *)((u8 *)bucket_offset))->unk_B0 & 0xFF000000U) |
                    ((u32)draw_prim & 0xFFFFFFU);
            }
        }

        draw_value = (u32) ((S_807B0B3C_0_pre *)object)[-1].unk_00;
        if (draw_value == 0) break;
        draw_value += 0x20;
        object = (u8 *)draw_value;
    } while (1);
    {
        s32 zero_result = 0;

        return zero_result;
    }
}
#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"

extern struct { s32 v; s32 pad[2]; } D_800814A0;

typedef struct UnkStruct807B11B8 {
    s32 unk0;
    s32 unk4;
    u8 pad8[4];
    s32 unkC;
    s32 unk10;
} UnkStruct807B11B8;

/* Advance motion and propagate update flags to the object and global state. */
void move_sprite_until_animation_finishes(u16 *object_data, UnkStruct807B11B8 *motion, u16 *update_state) {
    motion->unk0 += motion->unkC;
    motion->unk4 += motion->unk10;
    advance_sprite_animation_and_textures(update_state);
    if (*(u16 *)((u8 *)update_state + 0x14) & 0x6000) {
        u16 *object_flags = (u16 *)((u8 *)object_data - 2);
        *object_flags = (u16)(*object_flags | 0x8000);
        D_800814A0.v = D_800814A0.v | 0x8000;
    }
}
