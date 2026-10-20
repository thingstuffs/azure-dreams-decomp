#include "modules/dungeon_ovl_197e800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

   /* obj in update_directional_actor_effect */

   /* the 0x18 bytes before source in update_directional_actor_effect, addressed as source[-1] */

   /* display in update_directional_actor_effect */

   /* ((S_8002401C_0 *)obj)->unk_04 in update_directional_actor_effect */

extern s32 D_80027328;
extern u8 D_80027374[];
extern u8 D_800273BE;

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The switch table follows it at 0x80024008
 * (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_197e800_entry)(void *) = update_directional_actor_effect;

/* Advances the object's state and draws its 7-by-7 grid. */
void update_directional_actor_effect(void *object)
{
    u8 *object_bytes = object;
    GameWork *palette = &g_game_work;
    u8 *source;
    s32 *row;
    s32 *clear_row;
    s32 *clear_cell;
    s16 rect[4];
    s32 row_index;
    s32 col_index;
    s32 y;
    s32 cell_value;
    s32 cell_size;
    s32 direction_offset;
    EntityRec *map_data;
    u8 config_byte;
    void *created_obj;
    void *display;
    void *source_obj;
    s32 dependency_scratch;
    s32 state;

    state = ((S_8002401C_0 *)object_bytes)->unk_0A.s;
    switch (state) {
    case 0:
        row_index = 0;
        D_800273BC.value = 1;
        config_byte = ((S_8002401C_0 *)object_bytes)->unk_09;
        D_80027328 = 0;
        source_obj = ((S_8002401C_0 *)object_bytes)->unk_00.s;
        D_800273BE = config_byte;
        D_800273C0 = ((S_8002401C_0 *)object_bytes)->unk_00.s;
        D_8002732C = source_obj;

        D_800814A8->unk_F4 = 0;
        D_800814A8->unk_102 = 1;
        D_800814A8->unk_A8 = ((S_8002401C_0 *)object_bytes)->unk_08;

        clear_row = D_800274DC[0];
        do {
            col_index = 6;
            clear_cell = clear_row + 6;
            do {
                *clear_cell = 0;
                clear_cell--;
                col_index--;
            } while (col_index >= 0);
            row_index++;
            if (row_index >= 7) {
                break;
            }
            clear_row += 8;
        } while (1);

        D_800273A8 = 0;
        map_data = (u8 *)D_800E3D7C;
        direction_offset = (((u16)map_data->facing) >> 8) & 0xE;
        flag_nearby_seven_by_seven_tiles(
            (s16)(D_80082E80.tileX +
                  (dir_step_x[direction_offset >> 1] * 4)),
            (s16)(D_80082E80.tileY +
                  (dir_step_y[direction_offset >> 1] * 4)));
        ((S_8002401C_0 *)object_bytes)->unk_0A.u++;
                        /* fallthrough */

    case 1:
        if ((((S_8002401C_4 *)(((S_8002401C_0 *)object_bytes)->unk_04))->unk_00 & 0x80) != 0) {
            source = ((S_8002401C_0 *)object_bytes)->unk_00.u;
            created_obj = func_8002453C(((S_8002401C_2_pre *)source)[-1].unk_00, source);
            ((S_8002401C_0 *)object_bytes)->unk_0C = created_obj;
            if (created_obj != 0) {
                display = D_800814A8;
                ((S_8002401C_0 *)object_bytes)->unk_1C.s = 0x10;
                ((S_8002401C_3 *)display)->unk_A6--;
                ((S_8002401C_0 *)object_bytes)->unk_0A.u++;
            }
        }
        break;

    case 2:
        ((S_8002401C_0 *)object_bytes)->unk_1C.u--;
        if (((S_8002401C_0 *)object_bytes)->unk_1C.s >= 0) {
            break;
        }
        play_sound_if_enabled(0x300);
        ((S_8002401C_0 *)object_bytes)->unk_0A.u++;
                            /* fallthrough */

    case 3:
        if ((s16)D_800273BC.value == 0) {
            func_80025C8C();
            ((S_8002401C_0 *)object_bytes)->unk_0A.u++;
        }
        break;

    case 4:
        if ((s16)D_80027330 == 0) {
            g_dungeon_status.unk_0C = 0;
            g_dungeon_status.unk_0A--;
            (*(u16 *)((u8 *)object_bytes + -2)) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
        break;
    }

    rect[0] = 0x340;
    rect[1] = 0x180;
    rect[2] = 0x70;
    rect[3] = 0x70;
    draw_textured_ellipse(D_80027398, rect, 0, 2);

    for (row_index = 0, cell_size = 0x10, row = D_800274DC[0], y = 0x180;
         row_index < 7; row_index++) {
        for (col_index = 0; col_index < 7;) {
            rect[0] = 0x340 + col_index * 0x10;
            rect[1] = y;
            rect[2] = cell_size;
            rect[3] = cell_size;
            cell_value = row[col_index];
            func_80026064(rect, cell_value);
            col_index++;
        }
        row += 8;
        y += 0x10;
    }

    D_80027330 = 0;
    D_80027374[8] = (palette->unk_004 & 0x1F) + 0x80;
    D_80027374[9] = palette->unk_004 & 0x1F;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

   /* the 0x2 bytes before arg0 in update_brightening_fading_effect, addressed as arg0[-1] */

   /* arg0 in update_brightening_fading_effect */

   /* arg1 in update_brightening_fading_effect */

   /* arg2 in update_brightening_fading_effect */

   /* ((S_8195EB88_0 *)arg0)->unk_0C in update_brightening_fading_effect */

/* Updates the effect position, brightens and fades its primitive, and marks completion. */
void update_brightening_fading_effect(void *effect, S_8195EB88_2 *position, S_8195EB88_4 *primitive)
{
    s16 phase;
    u16 phase_value;
    S_8195EB88_3 *base_position;
    S_8195EB88_1 *source_state;

    (*(u16 *)&D_80027330) = (*(u16 *)&D_80027330) + 1;
    phase = ((S_8195EB88_0 *)effect)->unk_48.s;
    phase_value = ((S_8195EB88_0 *)effect)->unk_48.u;

    if (phase == 0) {
        source_state = ((S_8195EB88_5 *)(((S_8195EB88_0 *)effect)->unk_0C))->unk_0C;
        if (((S_8195EB88_0 *)effect)->unk_4A == 0) {
            if (resolve_record_orientation_or_fallback(source_state->unk_08, source_state,
                              (u8 *)effect + 0x40, 0) != 0) {
                ((S_8195EB88_0 *)effect)->unk_4A = 1;
            } else if (source_state->unk_14 & 0x8000) {
                ((S_8195EB88_0 *)effect)->unk_4A = 1;
                ((S_8195EB88_0 *)effect)->unk_44.s = -0x40;
            }
            if (((S_8195EB88_0 *)effect)->unk_4A == 0) {
                return;
            }
        }

        base_position = ((S_8195EB88_5 *)(((S_8195EB88_0 *)effect)->unk_0C))->unk_08;
        position->unk_02 =
            base_position->unk_02 + ((S_8195EB88_0 *)effect)->unk_40;
        position->unk_06 =
            base_position->unk_06 + ((S_8195EB88_0 *)effect)->unk_42;
        position->unk_0A =
            base_position->unk_0A + ((S_8195EB88_0 *)effect)->unk_44.u;
        if (allocate_nine_position_objects(position) != 0) {
            register_node((u8 *)effect - 0x20, project_sprite_chain);
            ((S_8195EB88_0 *)effect)->unk_48.u = ((S_8195EB88_0 *)effect)->unk_48.u + 1;
        }
    } else if (phase == 1) {
        if (primitive->unk_0C.u8 < 0xC0) {
            primitive->unk_0C.u32 += 0x202020;
        } else {
            ((S_8195EB88_0 *)effect)->unk_48.u = phase_value + 1;
        }
    } else if (phase == 2) {
        primitive->unk_0C.u32 += 0xFFEFEFF0;
        if (primitive->unk_0C.u8 == 0) {
            ((S_8195EB88_0_pre *)effect)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"

   /* obj in func_8002453C */

   /* part in func_8002453C */

   /* arg0 in func_8002453C */

#define NULL 0

extern s32 D_80027380;
extern s32 D_800273B0;
extern s32 D_800DF334;

/* Creates an object, initializes its parts, and loads its graphics. */
void *func_8002453C(S_8195ED3C_2 *source, s32 offset)
{
    s32 rect[2];
    s32 rect_size;
    void *obj;
    S_8195ED3C_1 *part;
    void *handle;

    obj = func_8003FC64(2);
    if (obj != NULL) {
        rect[0] = 0x01000340;
        rect_size = 0x200020;
        rect[1] = rect_size;
        draw_textured_ellipse(&D_800DF334, rect, 1, 0);
        rect[0] = 0x01000360;
        rect[1] = rect_size;
        draw_textured_ellipse(&D_80027380, rect, 1, 0);
        part = ((S_8195ED3C_0 *)obj)->unk_08;
        ((S_8195ED3C_0 *)obj)->unk_10 = update_brightening_fading_effect;
        part->unk_02 = source->unk_02;
        part->unk_06 = source->unk_06;
        part->unk_08.at02.v = source->unk_0A;
        part = ((S_8195ED3C_0 *)obj)->unk_0C;
        part->unk_08.at00.v = &D_800273B0;
        part->unk_1E = 0xC00;
        part->unk_1C = 0xC00;
        ((S_8195ED3C_0 *)obj)->unk_2C = offset - 0x20;
    }
    handle = NULL;
    if (obj != NULL) {
        handle = (u8 *)obj + 0x20;
    }
    return handle;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"

   /* arg0 in update_effect_and_spawn_fragments */

   /* arg1 in update_effect_and_spawn_fragments */

extern s32 rand();

/* Interpolates height with jitter until the phase ends, then advances position by velocity. */
void update_effect_and_spawn_fragments(S_8195EE48_0 *state, S_8195EE48_1 *motion)
{
    s32 phase_or_height;
    s16 ticks_left;
    s16 next_ticks;
    u16 counter;

    counter = (*(u16 *)&D_80027330);
    phase_or_height = state->unk_48;
    (*(u16 *)&D_80027330) = counter + 1;
    if (phase_or_height == 0) {
        ticks_left = state->unk_4C;
        if (ticks_left > 0) {
            s32 phase_or_height;
            phase_or_height = state->unk_3C;
            state->unk_3C =
                (u16)state->unk_3C +
                ((state->unk_62 + state->unk_60 - phase_or_height) / ticks_left);
            motion->unk_08.at02.v =
                ((u16)state->unk_3C + (rand() & 3)) - 2;
        }
        next_ticks = (u16)state->unk_4C - 1;
        state->unk_4C = next_ticks;
        if ((next_ticks << 16) <= 0) {
            state->unk_4C = 0x20;
            state->unk_48 = (u16)state->unk_48 + 1;
            return;
        }
    } else {
        motion->unk_00 += motion->unk_0C;
        motion->unk_04 += motion->unk_10;
        motion->unk_08.at00.v += motion->unk_14;
    }
}

/* MECHANISM: An s32-held 0x48 condition produces retail's signed load and exact s0/s1/ra frame.
   Reading the counter first preserves retail emission order; a guarded $v1 runtime-value pin
   fixes the final counter/base coloring while the natural CFG retains both delay-slot stores. */
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

   /* work in allocate_map_cell_object */

   /* render in allocate_map_cell_object */

   /* coord in allocate_map_cell_object */

/* Allocate and initialize an object using the map cell at the supplied position. */
void *allocate_map_cell_object(s16 world_x, s16 world_y, s16 world_z, s16 coord_60)
{
    void *obj;
    SpriteFrameState *work;
    MapGrid *map;
    u8 *coord;
    void *render;
    s32 cell_x;
    s32 cell_y;
    u16 cell;

    map = &g_game_work.map;
    obj = func_8003FC64(2);
    if (obj != NULL) {
        work = *(void **)((u8 *)obj + 0xC);
        cell_x = world_x / 64;
        cell_y = world_y / 64;
        cell = ((u16 *)map->cells)[(cell_x + (cell_y << map->shiftX)) * 3];
        work->source = cell;
        if (cell == 0) {
            u16 obj_flags = *(u16 *)((u8 *)obj + 0x1E) | 0x8000;
            s32 global_flags = object_flag_block.flags | 0x8000;
            *(u16 *)((u8 *)obj + 0x1E) = obj_flags;
            object_flag_block.flags = global_flags;
            return NULL;
        }
        coord = (u8 *)obj + 0x20;
        *(void **)((u8 *)obj + 0x10) = update_effect_and_spawn_fragments;
        register_node(obj, func_80046398);
        render = *(void **)((u8 *)obj + 8);
        ((S_8195EF44_4 *)render)->unk_02 = world_x;
        ((S_8195EF44_5 *)coord)->unk_38 = world_x;
        ((S_8195EF44_4 *)render)->unk_06 = world_y;
        ((S_8195EF44_5 *)coord)->unk_3A = world_y;
        ((S_8195EF44_4 *)render)->unk_0A = world_z;
        ((S_8195EF44_5 *)coord)->unk_3C = world_z;
        work->unk_20 = 0x1000;
        work->scale_y = 0x1000;
        work->scale_x = 0x1000;
        work->tpage_abr = 0x20;
        work->color.word = 0x808080;
        work->flags = 0xC;
        ((S_8195EF44_5 *)coord)->unk_4C = 0xC;
        ((S_8195EF44_5 *)coord)->unk_60 = coord_60;
        ((S_8195EF44_5 *)coord)->unk_62 = world_z;
    }
    return obj;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"

extern u8 D_80027334[][8];
extern u8 D_800273BE;

/* Animate nearby tile heights and fade the color, then finalize the dungeon transition. */
void animate_tile_heights_and_transition(DungeonState *state, DungeonOrigin *origin) {
    FadeColor *fade_color;
    s32 grid_x;
    s32 grid_y;
    s32 tile_x;
    s32 grid_y_fixed;
    s32 tile_y;
    s32 grid_x_fixed;
    s32 scratch;
    s32 offset_y;
    s32 random_value;
    void *tile;
    u16 timer;

    (*(u16 *)&D_80027330)++;
    if (state->active == 0) {
        if (!(state->timer & 3)) {
            func_800419EC(8, 16);
        }
        fade_color = (FadeColor *)&D_80027398;
        fade_color->red += (0xF0 - fade_color->red) / (s16)state->timer;
        fade_color->green += (0x40 - fade_color->green) / (s16)state->timer;
        fade_color->blue += (0x20 - fade_color->blue) / (s16)state->timer;

        grid_y = 1;
        do {
            grid_x = 1;
            scratch = ((u16)origin->y >> 6) - 3;
            tile_y = scratch + grid_y;
            do {
                scratch = ((u16)origin->x >> 6) - 3;
                tile_x = scratch + grid_x;
                random_value = func_80069EF8() & 7;
                D_8002745C[grid_y][grid_x] += (s8)D_80027334[grid_y][grid_x] - random_value;
                tile = find_eligible_entry_at_coordinates(D_800E3D7C, tile_x & 0xFFFF, tile_y & 0xFFFF);
                if (tile != 0 && tile != D_8002732C) {
                    *(u16 *)(*(u8 **)((u8 *)tile - 0x18) + 0xA) =
                        D_8002745C[grid_y][grid_x] + origin->height;
                }
                if (!(func_80069EF8() & 7)) {
                    set_record_pair_to_one((s16)(tile_x << 6), (s16)(tile_y << 6),
                                  (s16)D_8002745C[grid_y][grid_x], (s16)grid_x,
                                  (s16)grid_y);
                }
                grid_x++;
            } while (grid_x < 7);
            grid_y++;
        } while (grid_y < 7);

        timer = state->timer - 1;
        state->timer = timer;
        if ((timer << 16) <= 0) {
            grid_y = 0;
            do {
                grid_x = 0;
                grid_y_fixed = grid_y << 16;
                grid_x_fixed = grid_x;
                do {
                    scratch = grid_x - 3;
                    tile = find_eligible_entry_at_coordinates(D_800E3D7C,
                                         (((u16)origin->x >> 6) + scratch) & 0xFFFF,
                                         (((u16)origin->y >> 6) + (offset_y = grid_y - 3)) & 0xFFFF);
                    if (tile != 0 && tile != D_8002732C) {
                        apply_attack_power_and_element_effects(
                            tile, 16, D_800273BE, 9,
                            (s16)forward_monster_coordinate_delta(grid_x_fixed >> 16,
                                               grid_y_fixed >> 16, 3, 3),
                            D_800273C0, 2);
                        *(s32 *)((u8 *)tile + 0x14) &= 0xFFEFFFFF;
                    }
                    create_terrain_tile_quad(grid_x_fixed >> 16, grid_y_fixed >> 16, origin);
                    grid_x_fixed += 0x10000;
                    grid_x++;
                } while (grid_x < 7);
                grid_y++;
            } while (grid_y < 7);
            state->timer = 8;
            state->active++;
            return;
        }
    } else {
        timer = state->timer - 1;
        state->timer = timer;
        if ((timer << 16) <= 0) {
            *((u16 *)state - 1) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
#include "modules/dungeon_ovl_197e800.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

   /* scratch in project_height_grid_object_quad */

   /* arg1 in project_height_grid_object_quad */

   /* table in project_height_grid_object_quad */

   /* table2 in project_height_grid_object_quad */

   /* base in project_height_grid_object_quad */

   /* object in project_height_grid_object_quad */

   /* texture in project_height_grid_object_quad */

   /* packet in project_height_grid_object_quad */

   /* *global in project_height_grid_object_quad */

#define VFIELD(p, type, offset) (*(volatile type *)((u8 *)(p) + (offset)))
#define PFIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

static __inline__ void set_v_width(s32 *rect, s32 v, s32 width)
{
    VFIELD(rect, s32, 0x10) = width;
    rect[3] = v;
}

/* Project a textured object quad onto the height grid and add it to the ordering table. */
void project_height_grid_object_quad(void *unused, void *origin, u8 *object, s16 tile_x, s16 tile_y)
{
    u8 **render_state = (u8 **)((u8 *)(&g_game_work));
    u8 *scratch = (u8 *)0x1F800000;
    u8 *height_grid = ((u8 *)D_8002745C);
    u8 *render_ctx;
    u8 *packet;
    u8 *texture;
    u8 *height_row;
    u8 *next_height_row;
    u32 depth;
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    s32 visible_0;
    s32 visible_1;
    s32 visible_2;
    s32 visible_3;
    s32 visible_01;
    s32 visible_012;
    s32 edge_uv;
    u32 address_mask;
    u32 tag_mask;
    u16 page_offset;
    s32 scale_y;

    (void)unused;
    render_ctx = *render_state;
    ((S_8195F43C_0 *)scratch)->unk_20 = render_ctx + 0xB0;
    ((S_8195F43C_0 *)scratch)->unk_E4 = ((S_8195F43C_1 *)origin)->unk_02 + ((tile_x - 3) << 6);
    ((S_8195F43C_0 *)scratch)->unk_E8 = ((S_8195F43C_1 *)origin)->unk_06 + ((tile_y - 3) << 6);
    ((S_8195F43C_0 *)scratch)->unk_EC = ((S_8195F43C_1 *)origin)->unk_0A;

    height_row = (u8 *)((u32)(tile_y * 2) +
        (u32)(height_grid + tile_x * 0x10));
    height_grid += 0x10;
    next_height_row = (u8 *)((u32)(tile_y * 2) +
        (u32)(height_grid + tile_x * 0x10));
    {

        depth = ((S_8195F43C_2 *)height_row)->unk_00;
        ((S_8195F43C_0 *)scratch)->unk_74 = (s16)depth / 2;
    }
    ((S_8195F43C_0 *)scratch)->unk_7C = (s16)((S_8195F43C_3 *)next_height_row)->unk_00 / 2;
    ((S_8195F43C_0 *)scratch)->unk_84 = (s16)((S_8195F43C_2 *)height_row)->unk_02 / 2;
    ((S_8195F43C_0 *)scratch)->unk_8C = (s16)((S_8195F43C_3 *)next_height_row)->unk_02 / 2;

    packet = ((GpuContext *)render_ctx)->packetCursor;
    func_800649A0();

    VFIELD(scratch, u32, 0x30) = ((S_8195F43C_5 *)object)->unk_1C * 2;
    scale_y = ((S_8195F43C_5 *)object)->unk_1E;
    VFIELD(scratch, u32, 0x38) = 0x2000;
    VFIELD(scratch, u16, 0x102) = 0;
    VFIELD(scratch, u16, 0x104) = 0;
    VFIELD(scratch, u16, 0x100) = 0;
    ((S_8195F43C_0 *)scratch)->unk_34 = scale_y * 2;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(scratch + 0x11C);
    func_80064840(scratch + 0x11C, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    texture = ((S_8195F43C_5 *)object)->unk_08;
    left = (s8)((S_8195F43C_6 *)texture)->unk_02;
    ((S_8195F43C_0 *)scratch)->unk_80 = left;
    ((S_8195F43C_0 *)scratch)->unk_70 = left;
    right = left + ((S_8195F43C_6 *)texture)->unk_0A;
    ((S_8195F43C_0 *)scratch)->unk_88 = right;
    ((S_8195F43C_0 *)scratch)->unk_78 = right;
    top = (s8)((S_8195F43C_6 *)texture)->unk_03;
    ((S_8195F43C_0 *)scratch)->unk_7A = top;
    ((S_8195F43C_0 *)scratch)->unk_72 = top;
    bottom = top + ((S_8195F43C_6 *)texture)->unk_0B;
    ((S_8195F43C_0 *)scratch)->unk_8A = bottom;
    ((S_8195F43C_0 *)scratch)->unk_82 = bottom;

    depth = func_80065590(scratch + 0x70, scratch + 0x78,
                          scratch + 0x80, scratch + 0x88,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0x90, scratch + 0x94);
    ((S_8195F43C_0 *)scratch)->unk_C0 = depth;

    if (depth < 0x1E0U) {
        visible_0 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_08.u + 0x20) < 0x181U) {
            visible_0 = (u16)(((S_8195F43C_7 *)packet)->unk_0A.u + 0x20) < 0x121U;
        }
        visible_1 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_10 + 0x20) < 0x181U) {
            visible_1 = (u16)(((S_8195F43C_7 *)packet)->unk_12 + 0x20) < 0x121U;
        }
        visible_01 = visible_0 | visible_1;
        visible_2 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_18 + 0x20) < 0x181U) {
            visible_2 = (u16)(((S_8195F43C_7 *)packet)->unk_1A + 0x20) < 0x121U;
        }
        visible_012 = visible_01 | visible_2;
        visible_3 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_20.u + 0x20) < 0x181U) {
            visible_3 = (u16)(((S_8195F43C_7 *)packet)->unk_22.u + 0x20) < 0x121U;
        }

        if ((visible_012 | visible_3) != 0) {
            PFIELD(scratch, s32, 8) = ((S_8195F43C_6 *)texture)->unk_08;
            PFIELD(scratch, s32, 0x10) = ((S_8195F43C_6 *)texture)->unk_0A;
            PFIELD(scratch, s32, 0xC) = ((S_8195F43C_6 *)texture)->unk_09;
            PFIELD(scratch, s32, 0x14) = ((S_8195F43C_6 *)texture)->unk_0B;

            ((S_8195F43C_7 *)packet)->unk_0E = ((S_8195F43C_5 *)object)->unk_12 + (*(u16 *)((u8 *)texture + 6));
            page_offset = ((S_8195F43C_5 *)object)->unk_10;
            if (page_offset != 0) {
                (*(u16 *)((u8 *)packet + 0x16)) = page_offset + (((S_8195F43C_6 *)texture)->unk_04 & 0xFF9F);
            } else {
                (*(u16 *)((u8 *)packet + 0x16)) = ((S_8195F43C_6 *)texture)->unk_04;
            }

            {
                s32 u;
                s32 width;

                u = PFIELD(scratch, s32, 8);
                width = PFIELD(scratch, s32, 0x10);
                if (u + width >= 0x100) {
                    PFIELD(scratch, s32, 0x10) = width - 1;
                }
            }
            {
                s32 v;
                s32 height;

                v = PFIELD(scratch, s32, 0xC);
                height = PFIELD(scratch, s32, 0x14);
                if (v + height >= 0x100) {
                    PFIELD(scratch, s32, 0x14) = height - 1;
                }
            }

            {
                s32 v_end;
                u16 uv_row;
                u16 packed_u;

                {
                    s32 v;

                    {
                        s32 width;

                        width = PFIELD(scratch, s32, 0x10);
                        edge_uv = PFIELD(scratch, s32, 8);
                        v = *(s32 *)((u8 *)scratch + 0xC);
                        width += edge_uv;
                        edge_uv = v;
                        set_v_width((s32 *)scratch, edge_uv, width);
                    }
                    {

                        v_end = VFIELD(scratch, s32, 0x14);
                        edge_uv <<= 8;
                        PFIELD(scratch, s32, 0xC) = edge_uv;
                        uv_row = VFIELD(scratch, u16, 0xC);
                        v_end += v;
                    }
                }
                VFIELD(scratch, s32, 0x14) = v_end;
                packed_u = *(u16 *)((u8 *)scratch + 8);
                PFIELD(scratch, s32, 0x14) = v_end << 8;
                (*(u16 *)((u8 *)packet + 0xC)) = uv_row + packed_u;
            }
            (*(u16 *)((u8 *)packet + 0x14)) = PFIELD(scratch, u16, 0xC) + PFIELD(scratch, u16, 0x10);
            (*(u16 *)((u8 *)packet + 0x1C)) = PFIELD(scratch, u16, 0x14) + PFIELD(scratch, u16, 8);
            (*(u16 *)((u8 *)packet + 0x24)) = PFIELD(scratch, u16, 0x14) + PFIELD(scratch, u16, 0x10);

            if (((S_8195F43C_0 *)scratch)->unk_50 >= 0x1800) {
                edge_uv = ((S_8195F43C_7 *)packet)->unk_24;
                {
                    s32 edge_uv_prev;

                    edge_uv_prev = edge_uv + 0xFF;
                    ((S_8195F43C_7 *)packet)->unk_24 = edge_uv_prev;
                }
                ((S_8195F43C_7 *)packet)->unk_14 = edge_uv;
            }
            if (((S_8195F43C_0 *)scratch)->unk_58 >= 0x1800) {
                edge_uv = ((S_8195F43C_7 *)packet)->unk_25;
                {
                    s32 edge_uv_prev;

                    edge_uv_prev = edge_uv + 0xFF;
                    ((S_8195F43C_7 *)packet)->unk_25 = edge_uv_prev;
                }
                ((S_8195F43C_7 *)packet)->unk_1D = edge_uv;
            }
            if (((S_8195F43C_7 *)packet)->unk_08.s > ((S_8195F43C_7 *)packet)->unk_20.s) {
                ((S_8195F43C_7 *)packet)->unk_14--;
                ((S_8195F43C_7 *)packet)->unk_24--;
            }
            if (((S_8195F43C_7 *)packet)->unk_0A.s > ((S_8195F43C_7 *)packet)->unk_22.s) {
                ((S_8195F43C_7 *)packet)->unk_1D--;
                ((S_8195F43C_7 *)packet)->unk_25--;
            }

            ((S_8195F43C_7 *)packet)->unk_04.at00.v = ((S_8195F43C_5 *)object)->unk_0C;
            ((S_8195F43C_7 *)packet)->unk_00.at03.v = 9;
            ((S_8195F43C_7 *)packet)->unk_04.at03.v = 0x2C;
            if (((S_8195F43C_5 *)object)->unk_14 & 4) {
                ((S_8195F43C_7 *)packet)->unk_04.at03.v = 0x2E;
            }

            address_mask = 0x00FFFFFF;
            tag_mask = 0xFF000000;
            ((S_8195F43C_7 *)packet)->unk_00.at00.v = (((S_8195F43C_7 *)packet)->unk_00.at00.v & tag_mask) |
                ((*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20)
                    + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) & address_mask);
            (*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20) + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) =
                ((*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20)
                    + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) & tag_mask) |
                ((u32)packet & address_mask);
            packet += 0x28;
        }
    }

    func_80064A40();
    ((GpuContext *)(*render_state))->packetCursor = packet;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"

/* Sets tile bounds and dispatches tiles for a seven-by-seven grid. */
s32 dispatch_seven_by_seven_tile_grid(void *tile_data, s32 draw_arg_1, s32 draw_arg_2) {
    s32 column;
    s32 row;
    s32 tile_y;
    s32 row_arg;
    s32 tile_size;
    s32 edge_size;
    s32 last_tile;

    row = 0;
    last_tile = 6;
    edge_size = 0xF;
    tile_size = 0x10;
    tile_y = -0x80;
    do {
        column = 0;
        row_arg = (s16)row;
        do {
            *(s8 *)((s8 *)tile_data + 8) = column * 0x10;
            *(s8 *)((s8 *)tile_data + 9) = tile_y;
            if (column == last_tile) {
                *(s8 *)((s8 *)tile_data + 0xA) = edge_size;
            } else {
                *(s8 *)((s8 *)tile_data + 0xA) = tile_size;
            }
            if (row == last_tile) {
                *(s8 *)((s8 *)tile_data + 0xB) = edge_size;
            } else {
                *(s8 *)((s8 *)tile_data + 0xB) = tile_size;
            }
            project_height_grid_object_quad(tile_data, draw_arg_1, draw_arg_2, (s16)column, row_arg);
            column += 1;
        } while (column < 7);
        row += 1;
        tile_y += 0x10;
    } while (row < 7);
    return 0;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "m2c_compat.h"

/* Clears the 8-by-8 grid and initializes an object at the given position. */
void func_80025334(s16 x, s16 y, s16 z) {
    s16 row_index;
    s16 column_index;
    s16 next_row;
    s16 next_column;
    s32 column_shifted;
    s8 *grid;
    s8 *row;
    void *init_object;
    void *callback;
    S_8195FB34_2 *render_state;
    void *object;
    S_8195FB34_1 *position;
    S_8195FB34_3 *object_data;

    row_index = 0;
    grid = ((s8 *)D_8002745C);
    do {
        column_index = 0;
        row = (s8 *)(((s32) (row_index << 0x10) >> 0xC) + (u32)grid);
        do {
            column_shifted = column_index << 0x10;
            *(s16 *)((column_shifted >> 0xF) + (u32)row) = 0;
            next_column = column_index + 1;
            column_index = next_column;
        } while (next_column < 8);
        next_row = row_index + 1;
        row_index = next_row;
    } while (next_row < 8);
    object = func_8003FC64(0x202);
    if (object != NULL) {
        init_object = object;

        callback = animate_tile_heights_and_transition;

        ((S_8195FB34_0 *)object)->unk_10 = callback;
        register_node(init_object, dispatch_seven_by_seven_tile_grid);
        position = ((S_8195FB34_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        render_state = ((S_8195FB34_0 *)object)->unk_0C;
        render_state->unk_1E = 0x2000;
        render_state->unk_1C = 0x2000;
        render_state->unk_0C = 0x808080;
        object_data = object + 0x20;
        render_state->unk_10 = 0x20;
        ((S_8195FB34_0 *)object)->unk_20 = 0xF8F82CC0;
        object_data->unk_04 = 0x13D;
        render_state->unk_08 = object_data;
        object_data->unk_4C = 0x10;
    }
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/object_flags.h"

/* Advance motion, fade the effect, and flag expiry when its timer runs out. */
void func_80025460(u16 *state, Motion *motion, Effect *effect)
{
    u8 brightness;
    s16 ticks_left;

    (*(u16 *)&D_80027330)++;

    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dz += 0x40000;

    effect->x += effect->dx;
    effect->y += effect->dy;

    brightness = effect->red;
    brightness = brightness - brightness / *(s16 *)((u8 *)state + 0x4C);
    effect->blue = effect->green = effect->red = brightness;

    ticks_left = state[0x26] - 1;
    state[0x26] = ticks_left;
    if ((ticks_left << 16) <= 0) {
        state[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
#include "modules/dungeon_ovl_197e800.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

   /* scratch in func_80025540 */

   /* arg1 in func_80025540 */

   /* *global in func_80025540 */

   /* arg2 in func_80025540 */

   /* packet in func_80025540 */

   /* texture in func_80025540 */

   /* (u8 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                              ((S_8195FD40_0 *)scratch)->unk_20) in func_80025540 */

/* Transform a textured quad and add it to the ordering table if visible. */
void func_80025540(s32 unused, S_8195FD40_1 *position, S_8195FD40_3 *quad, s16 depth_bias)
{
    s32 view_matrix[8];
    u8 *scratch = (u8 *)0x1F800000;
    u8 **render_context = (u8 **)((u8 *)(&g_game_work));
    s32 *ot_entry;
    s32 packet_addr;
    s32 corner0_visible;
    s32 corner1_visible;
    s32 corner2_visible;
    s32 corner3_visible;
    s32 first_two_visible;
    s32 first_three_visible;
    s8 u_right;
    s8 v_bottom;
    u32 depth;
    u8 u_left;
    u8 v_top;
    u8 *packet;
    u8 *texture;

    (void)unused;
    ((S_8195FD40_0 *)scratch)->unk_20 = *render_context + 0xB0;
    ((S_8195FD40_0 *)scratch)->unk_E4 = position->unk_02;
    ((S_8195FD40_0 *)scratch)->unk_E8 = position->unk_06;
    ((S_8195FD40_0 *)scratch)->unk_EC = position->unk_0A;
    packet = ((GpuContext *)(*render_context))->packetCursor;
    texture = quad->unk_08;
    func_800649A0();

    ((S_8195FD40_0 *)scratch)->unk_30 = quad->unk_1C * 2;
    ((S_8195FD40_0 *)scratch)->unk_34 = quad->unk_1E * 2;
    ((S_8195FD40_0 *)scratch)->unk_38 = 0x2000;
    ((S_8195FD40_0 *)scratch)->unk_100 = quad->unk_16;
    ((S_8195FD40_0 *)scratch)->unk_104 = quad->unk_1A;
    ((S_8195FD40_0 *)scratch)->unk_102 = quad->unk_18;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(&view_matrix);
    func_80064840(&view_matrix, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    ((S_8195FD40_0 *)scratch)->unk_78 = 0x20;
    ((S_8195FD40_0 *)scratch)->unk_88 = 0x200000;
    ((S_8195FD40_0 *)scratch)->unk_80 = 0x200000;
    ((S_8195FD40_0 *)scratch)->unk_70 = 0;
    ((S_8195FD40_0 *)scratch)->unk_8C = 0;
    ((S_8195FD40_0 *)scratch)->unk_84 = 0;
    ((S_8195FD40_0 *)scratch)->unk_7C = 0;
    ((S_8195FD40_0 *)scratch)->unk_74 = 0;
    depth = func_80065590(scratch + 0x70, scratch + 0x78,
                          scratch + 0x80, scratch + 0x88,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0x90, scratch + 0x94) - depth_bias;
    ((S_8195FD40_0 *)scratch)->unk_C0 = depth;

    if (depth < 0x1E0U) {
        corner0_visible = 0;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_08 + 0x20) < 0x181U) {
            corner0_visible = (u16)(((S_8195FD40_4 *)packet)->unk_0A + 0x20) < 0x121U;
        }
        corner1_visible = 0;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_10 + 0x20) < 0x181U) {
            corner1_visible = (u16)(((S_8195FD40_4 *)packet)->unk_12 + 0x20) < 0x121U;
        }
        corner2_visible = 0;
        first_two_visible = corner0_visible | corner1_visible;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_18 + 0x20) < 0x181U) {
            corner2_visible = (u16)(((S_8195FD40_4 *)packet)->unk_1A + 0x20) < 0x121U;
        }
        corner3_visible = 0;
        first_three_visible = first_two_visible | corner2_visible;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_20 + 0x20) < 0x181U) {
            corner3_visible = (u16)(((S_8195FD40_4 *)packet)->unk_22 + 0x20) < 0x121U;
        }

        if ((first_three_visible | corner3_visible) != 0) {
            u_left = ((S_8195FD40_5 *)texture)->unk_08;
            ((S_8195FD40_4 *)packet)->unk_1C = u_left;
            ((S_8195FD40_4 *)packet)->unk_0C = u_left;
            u_right = ((S_8195FD40_5 *)texture)->unk_08 + ((S_8195FD40_5 *)texture)->unk_0A;
            ((S_8195FD40_4 *)packet)->unk_24 = u_right;
            ((S_8195FD40_4 *)packet)->unk_14 = u_right;
            v_top = ((S_8195FD40_5 *)texture)->unk_09;
            ((S_8195FD40_4 *)packet)->unk_15 = v_top;
            ((S_8195FD40_4 *)packet)->unk_0D = v_top;
            v_bottom = ((S_8195FD40_5 *)texture)->unk_09 + ((S_8195FD40_5 *)texture)->unk_0B;
            ((S_8195FD40_4 *)packet)->unk_25 = v_bottom;
            ((S_8195FD40_4 *)packet)->unk_1D = v_bottom;
            ((S_8195FD40_4 *)packet)->unk_16 = ((S_8195FD40_5 *)texture)->unk_04;
            ((S_8195FD40_4 *)packet)->unk_04.at00.v = quad->unk_0C;
            ((S_8195FD40_4 *)packet)->unk_00.at03.v = 9;
            ((S_8195FD40_4 *)packet)->unk_04.at03.v = 0x2C;
            if (quad->unk_14 & 4) {
                ((S_8195FD40_4 *)packet)->unk_04.at03.v = 0x2E;
            }
            packet_addr = (s32)packet & 0xFFFFFF;
            ((S_8195FD40_4 *)packet)->unk_00.at00.v = (((S_8195FD40_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                (((S_8195FD40_6 *)((u8 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                              ((S_8195FD40_0 *)scratch)->unk_20)))->unk_00 & 0xFFFFFF);
            ot_entry = (s32 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                               ((S_8195FD40_0 *)scratch)->unk_20);
            packet += 0x28;
            *ot_entry = (*ot_entry & 0xFF000000) | packet_addr;
        }
    }
    func_80064A40();
    ((GpuContext *)(*render_context))->packetCursor = packet;
}
#include "modules/dungeon_ovl_197e800.h"
#include "modules/dungeon_draw_chain.h"

/* Object-list node header (0x20 bytes) that precedes each payload. */

struct S_8195FD40_1;
struct S_8195FD40_3;

/* Draw each payload in the linked object chain: the payload follows its node
 * header, and the header's link leads to the next object's header.
 */
s32 draw_linked_object_chain(void *payload, void *position, void *render)
{
    DrawChainNode *next;
    while (1) {
        func_80025540((s32)payload, position, render, ((DrawChainRender *)render)->depth);
        next = ((DrawChainNode *)payload - 1)->next;
        if (next == 0) return 0;
        payload = next + 1;
        position = next->position;
        render = next->render;
    }
}
#include "modules/dungeon_ovl_197e800.h"
#include "modules/dungeon_draw_chain.h"

#ifndef NULL
#define NULL 0
#endif

   /* object in set_record_pair_to_one */

   /* position in set_record_pair_to_one */

   /* render in set_record_pair_to_one */

   /* primitive in set_record_pair_to_one */

struct RegistrationNode;
extern s32 rand();

/* Spawn a textured particle with randomized motion at the given position. */
void set_record_pair_to_one(s16 x, s16 y, s16 z, s16 tile_col, s16 tile_row) {
    s32 random_angle;
    s32 primitive_word;
    s16 tile_row_copy;
    S_8196012C_1 *position;
    S_8196012C_3 *primitive;
    S_8196012C_2 *render;
    void *object;

    tile_row_copy = tile_row;
    object = func_8003FC64(0x202);
    if (object != NULL) {
        ((S_8196012C_0 *)object)->unk_10 = func_80025460;
        register_node(object, (s32)draw_linked_object_chain);
        position = ((S_8196012C_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        position->unk_0E = (rand() & 0xF) - 8;
        position->unk_12 = (rand() & 0xF) - 8;
        position->unk_16 = -0x10 - (rand() & 0xF);
        render = ((S_8196012C_0 *)object)->unk_0C;
        render->unk_1E = 0x400;
        render->unk_1C = 0x400;
        random_angle = rand();
        render->unk_20 = func_80064584(random_angle);
        render->unk_22 = func_800644B8(random_angle);
        render->unk_10 = 0x20;
        primitive = (s8 *)object + 0x20;
        render->unk_14 = 0xC;
        render->unk_0C = 0x808080;
        primitive_word = 0xF8F82CC0;
        ((S_8196012C_0 *)object)->unk_20 = primitive_word;
        primitive->unk_04 = 0x13D;
        primitive->unk_08 = (s8)(tile_col * 0x10);
        primitive->unk_09 = (s8)(((s32)(tile_row << 0x10) >> 0xC) - 0x80);
        primitive->unk_0A = tile_col == 7 ? 0xF : 0x10;
        primitive->unk_0B = tile_row_copy == 7 ? 0xF : 0x10;
        primitive->unk_4C = (rand(primitive_word) & 0x1F) + 0x20;
        render->unk_08 = primitive;
    }
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

extern u16 D_800273CC[];
extern u8 D_8002744C[9];
extern u8 D_8002744D[9];

/* Sample a 7 by 7 area around the given tile and flag the tiles found there. */
void flag_nearby_seven_by_seven_tiles(s32 input_x, s32 center_y) {
    u16 center_x = input_x;
    MapGrid *width_ref = &g_game_work.map;
    s32 one = 1;
    s16 tile_x;
    s32 signed_y;
    s32 tile_y;
    u8 *sample_row;
    s32 world_y;
    s32 sample_y;
    u16 *sample_ptr;
    u32 col;
    u32 row;
    s32 sample_x;
    s32 tile_sample;
    void *map;
    S_819602D8_0 *tile;
    u32 output_row;
    s32 output_value;

    tile_y = center_y - 3;
    row = 0;
    sample_row = D_800273CC;
    *D_8002744C = center_x;
    *D_8002744D = center_y;
    do {
        tile_x = center_x - 3;
        col = 0;
        tile_sample = tile_y << 16;
        signed_y = tile_sample >> 16;
        world_y = signed_y;
        world_y <<= 6;
        sample_y = world_y + 0x20;
        sample_ptr = (u16 *)sample_row;
        do {
            tile_sample = get_surface_height_at_coordinates((tile_x << 6) & 0xFFC0, world_y);
            map = ((u8 *)D_800E3D7C);
            *sample_ptr = 0 - tile_sample;
            tile = find_eligible_entry_at_coordinates(map, (u16)tile_x, (u16)tile_y);
            if ((tile != NULL) && (tile != (s32)D_8002732C)) {
                tile->unk_14 = (s32)(tile->unk_14 | 0x100000);
            }
            sample_x = (s16)tile_x;
            if (sample_x < 0 || sample_x >= (one << width_ref->shiftX) || signed_y < 0 ||
                signed_y >= (one << width_ref->shiftY)) {
                output_value = 0;
            } else {
                sample_x <<= 6;
                sample_x += 0x20;
                sample_x &= 0xFFE0;
                output_value = select_containing_cell_surface(sample_x, sample_y & 0xFFFF, -0x400);
            }
            tile_sample = (u32)&D_800274DC[0][0];
            output_row = (u32)tile_sample;
            output_row += row << 5;
            ((s32 *)output_row)[col] = output_value;
            sample_ptr += 1;
            col += 1;
            tile_x += 1;
        } while (col < 7U);
        sample_row += 16;
        row += 1;
        tile_y += 1;
    } while (row < 7U);
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"

extern u16 D_800273CC[];
extern u8 D_8002744C[9];
extern u8 D_8002744D[9];

/* Copies a 7-by-7 tile region from the source grid into the dungeon map around the current coordinates. */
void func_80025C8C(void)
{
    s8 *dungeon_state;
    DungeonMap *map;
    s16 row;
    s16 first_column;
    s32 rows_copied;
    s32 columns_copied;
    u16 *source_row;
    u16 *source_tile;
    u16 tile_value;
    u8 center_row;
    u8 center_column;

    dungeon_state = ((u8 *)(&g_game_work));
    map = (DungeonMap *)(dungeon_state + 0x1DC);
    rows_copied = 0;
    source_row = D_800273CC;
    center_row = D_8002744D[0];
    center_column = D_8002744C[0];
    row = center_row - 3;
    first_column = center_column - 3;
    do {
        s16 column;
        s32 row_index;

        column = first_column;
        columns_copied = 0;
        row_index = row;
        source_tile = source_row;
        do {
            tile_value = *source_tile++;
            columns_copied++;
            map->tiles[(column + (row_index << map->row_shift)) * 3 + 1] = tile_value;
            column++;
            if (columns_copied >= 7) {
                break;
            }
        } while (1);
        source_row += 8;
        rows_copied++;
        row++;
    } while (rows_copied < 7);
}

#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"

   /* scratch in select_containing_cell_surface */

   /* map_entry in select_containing_cell_surface */

   /* best in select_containing_cell_surface */

   /* current in select_containing_cell_surface */

   /* copy_vertex in select_containing_cell_surface */

   /* plane_ptr in select_containing_cell_surface */

   /* dot_vertex in select_containing_cell_surface */

   /* planes + ((S_81960530_3 *)best)->unk_10 * 8 in select_containing_cell_surface */

   /* planes + ((S_81960530_4 *)current)->unk_10 * 8 in select_containing_cell_surface */

/* Select a cell surface at the given position using plane height and containment tests. */
void *select_containing_cell_surface(s32 world_x, s32 world_y, s16 min_height) {
    u8 *scratch;
    u8 *polygon;
    u8 *vertices;
    u8 *planes;
    u8 *best_polygon;
    u8 *map_entry;
    u8 *vertex;
    u8 *plane_vertex;
    MapGrid *map_data;
    u8 *plane;
    s16 cell_index;
    s32 height;
    u16 cell_x;
    u16 cell_y;

    scratch = (u8 *)0x1F800000;
    ((S_81960530_0 *)scratch)->unk_148 = 0x400;
    ((S_81960530_0 *)scratch)->unk_140.s = world_x & 0x3F;
    ((S_81960530_0 *)scratch)->unk_142.s = world_y & 0x3F;
    ((S_81960530_0 *)scratch)->unk_14C = min_height;

    cell_index = (u16)world_x >> 6;
    ((S_81960530_0 *)scratch)->unk_150 = cell_index;
    map_data = &g_game_work.map;
    cell_index += ((u16)world_y >> 6) << map_data->shiftX;
    (*(s16 *)((u8 *)scratch + 0x150)) = cell_index;
    map_entry = (u8 *)((long)cell_index * 6 + (unsigned long)*(u8 **)((u8 *)(&g_game_work.map)));
    vertices = ((u8 *)map_data->unk_08);
    planes = ((u8 *)map_data->unk_0C);
    best_polygon = 0;
    if (((S_81960530_2 *)map_entry)->unk_00 != 0) {
        ((S_81960530_0 *)scratch)->unk_152.s = -((S_81960530_2 *)map_entry)->unk_02;
        best_polygon = (*(u8 * *)((u8 *)(((u8 **)map_data->unk_04)) + ((S_81960530_2 *)map_entry)->unk_00 * 4));
        polygon = best_polygon;
        if (((S_81960530_8 *)(planes + ((S_81960530_3 *)best_polygon)->unk_10 * 8))->unk_04 < -0x7FF) {
            do {
                if ((((S_81960530_4 *)polygon)->unk_17.u & 1) == 0) {
                    cell_x = ((S_81960530_0 *)scratch)->unk_140.u;
                    cell_y = ((S_81960530_0 *)scratch)->unk_142.u;

                    vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_00 * 8 + (unsigned long)vertices);
                    ((S_81960530_0 *)scratch)->unk_154.at00.v = ((S_81960530_5 *)vertex)->unk_00;
                    ((S_81960530_0 *)scratch)->unk_154.at00u.v = ((S_81960530_0 *)scratch)->unk_154.at00p.v - cell_x;
                    ((S_81960530_0 *)scratch)->unk_154.at02.v = ((S_81960530_0 *)scratch)->unk_154.at02u.v - cell_y;

                    vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_02 * 8 + (unsigned long)vertices);
                    ((S_81960530_0 *)scratch)->unk_158.at00.v = ((S_81960530_5 *)vertex)->unk_00;
                    ((S_81960530_0 *)scratch)->unk_158.at00u.v = ((S_81960530_0 *)scratch)->unk_158.at00p.v - cell_x;
                    ((S_81960530_0 *)scratch)->unk_158.at02.v = ((S_81960530_0 *)scratch)->unk_158.at02u.v - cell_y;

                    vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_06 * 8 + (unsigned long)vertices);
                    ((S_81960530_0 *)scratch)->unk_15C.at00.v = ((S_81960530_5 *)vertex)->unk_00;
                    ((S_81960530_0 *)scratch)->unk_15C.at00u.v = ((S_81960530_0 *)scratch)->unk_15C.at00p.v - cell_x;
                    ((S_81960530_0 *)scratch)->unk_15C.at02.v = ((S_81960530_0 *)scratch)->unk_15C.at02u.v - cell_y;

                    vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_04 * 8 + (unsigned long)vertices);
                    ((S_81960530_0 *)scratch)->unk_160.at00.v = ((S_81960530_5 *)vertex)->unk_00;
                    ((S_81960530_0 *)scratch)->unk_160.at00u.v = ((S_81960530_0 *)scratch)->unk_160.at00p.v - cell_x;
                    ((S_81960530_0 *)scratch)->unk_160.at02.v = ((S_81960530_0 *)scratch)->unk_160.at02u.v - cell_y;

                    if (are_quad_corner_turns_within_half_revolution(scratch) != 0) {
                        plane = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_10 * 8 + (unsigned long)planes);
                        plane_vertex = (u8 *)((unsigned long)((S_81960530_4 *)polygon)->unk_00 * 8
                            + (unsigned long)vertices);
                        height = (((S_81960530_6 *)plane)->unk_00 * (((S_81960530_7 *)plane_vertex)->unk_00
                            - (s16)((S_81960530_0 *)scratch)->unk_140.u) +
                                  ((S_81960530_6 *)plane)->unk_02 * (((S_81960530_7 *)plane_vertex)->unk_02
                                      - (s16)((S_81960530_0 *)scratch)->unk_142.u) +
                                  ((S_81960530_6 *)plane)->unk_04 * ((S_81960530_7 *)plane_vertex)->unk_04) /
                                ((S_81960530_6 *)plane)->unk_04;
                        ((S_81960530_0 *)scratch)->unk_144 = height;
                        height += (s16)((S_81960530_0 *)scratch)->unk_152.u;
                        ((S_81960530_0 *)scratch)->unk_144 = height;
                        if (height >= ((S_81960530_0 *)scratch)->unk_14C &&
                            height < ((S_81960530_0 *)scratch)->unk_148) {
                            best_polygon = polygon;
                            ((S_81960530_0 *)scratch)->unk_148 = height;
                        }
                    }
                }

                if ((((S_81960530_4 *)polygon)->unk_16 & 0xF) == 1) {
                    if (((S_81960530_4 *)polygon)->unk_17.s < 0) {
                        break;
                    }
                    if ((((S_81960530_4 *)polygon)->unk_16 & 0xF0) != 0) {
                        polygon += ((((S_81960530_4 *)polygon)->unk_16 >> 4) * 3) * 8 + 0x18;
                        continue;
                    }
                }
                polygon += 0x18;
            } while (((S_81960530_9 *)(planes + ((S_81960530_4 *)polygon)->unk_10 * 8))->unk_04 < -0x7FF);
        }
    }

    return best_polygon;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"

extern u8 D_801C9E40[16];

/* Renders data with the active buffer offset between ordering-table commands. */
void func_80026064(void *draw_data, s32 draw_mode)
{
    s32 start_packet;
    s32 end_packet;
    s16 buffer_shift;
    void *ordering_table;
    s32 mode_offset;
    s32 base_offset;
    void **draw_contexts;
    void *draw_context;
    void *end_context;

    draw_context = g_game_work.unk_000;
    draw_contexts = ((void * *)(&g_game_work));
    buffer_shift = draw_context != (void *)D_801C9E40;
    start_packet = *(s32 *)((u8 *)draw_context + 0x8D0);
    ordering_table = (u8 *)draw_context + 0x8B0;
    *(s32 *)((u8 *)draw_context + 0x8D0) = start_packet + 0xC;
    func_80067E2C(start_packet, g_game_work.unk_000, draw_context);
    {
        void *packet_table;
        s32 packet_addr;

        packet_table = ordering_table;
        packet_addr = start_packet;
        func_8006658C(packet_table, packet_addr);
    }

    if (draw_mode != 0) {
        s32 needs_shift;

        needs_shift = buffer_shift;
        mode_offset = 0;
        if (needs_shift != 0) {
            mode_offset = -0xE0;
        }
        build_shaded_textured_quad(mode_offset, draw_data, draw_mode, ordering_table);
    }

    {
        s32 needs_shift;

        needs_shift = buffer_shift;
        base_offset = 0;
        if (needs_shift != 0) {
            base_offset = -0xE0;
        }
    }
    build_shaded_textured_quad(base_offset, draw_data, 0, ordering_table);

    end_context = *draw_contexts;
    end_packet = *(s32 *)((u8 *)end_context + 0x8D0);
    *(s32 *)((u8 *)end_context + 0x8D0) = end_packet + 0xC;
    func_80067E2C(end_packet, draw_data);
    func_8006658C(ordering_table, end_packet);
}

/* MECHANISM: The 0x30 frame holds s0-s5; D_80083160 stays in s5 and the long-lived OT base in s1.
   Fixed a0/a1 ABI locals move both args before func_8006658C, freeing its delay slot for the disjoint s0=s2 copy.
   Leaving buffer_shift naturally allocated preserves retail's xor-in-v0 followed by sltu-into-s2 sequence. */
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"

extern u8 D_80027374[12];
typedef struct TextureConfig {
    u8 pad0[4];
    u16 word4;
    u16 word6;
    u8 byte8;
    u8 byte9;
    u8 byteA;
    u8 byteB;
} TextureConfig;

static __inline__ u16 translate_x(s32 x, u16 offset) { x -= 0xA0; return offset + x; }

/* Builds and submits a shaded textured quad at the requested screen position. */
void build_shaded_textured_quad(s32 y_offset, Input *origin, Input *quad_data, s32 draw_depth) {
    Root *root = g_game_work.unk_000;
    Record *record;
    Record *quad_packet;
    Input *quad_input = quad_data;
    GameWork *globals;
    TableEntry *vertex_table;
    Bank56_8196096C_Scratch *scratch;
    register void *rotation;
    register void *matrix;
    s32 saved_y_offset = y_offset;
    TextureConfig *texture_config;
    u16 texture_word;
    s32 corner_uv;
    s32 neutral_color;
    s32 shade;

    record = root->record;
    globals = &g_game_work;
    scratch = (Bank56_8196096C_Scratch *)0x1F800000;
    scratch->value = draw_depth;
    vertex_table = ((struct TableEntry *)globals->map.unk_08);
    func_800649A0();
    rotation = (void *)0x1F800028;
    matrix = (void *)0x1F800050;
    scratch->w6C = 0;
    scratch->w68 = 0;
    scratch->w64 = 0;
    scratch->h2C = 0;
    scratch->h2A = 0;
    scratch->h28 = 0;
    func_80065820(rotation, matrix);
    func_80064D80(&scratch->w50);
    func_80064CF0(&scratch->w50);
    scratch->h8C = 0x800;
    scratch->h84 = 0x800;
    scratch->h7C = 0x800;
    scratch->h74 = 0x800;
    if (quad_input != 0) {
        scratch->w70 = vertex_table[quad_input->index0].value;
        scratch->w78 = vertex_table[quad_input->index1].value;
        scratch->w80 = vertex_table[quad_input->index2].value;
        scratch->w88 = vertex_table[quad_input->index3].value;
        record->fC.w = quad_input->value8;
        record->f14.w = quad_input->valueC;
        record->f1C.h[0] = quad_input->value12;
        neutral_color = 0x808080;
        corner_uv = quad_input->value14;
        quad_packet = record;
        record->f4.w = neutral_color;
        record->f24.h[0] = corner_uv;
        func_800666F4(record);
    } else {
        scratch->w78 = 0x40;
        scratch->w70 = 0;
        scratch->w80 = 0x400000;
        scratch->w88 = 0x400040;
        texture_config = (TextureConfig *)D_80027374;
        texture_word = texture_config->word4;
        record->f14.h[1] = texture_word;
        texture_word = texture_config->word6;
        record->fC.h[1] = texture_word;
        record->f1C.b[0] = texture_config->byte8;
        record->fC.b[0] = record->f1C.b[0];
        record->f24.b[0] = texture_config->byte8 + texture_config->byteA;
        record->f14.b[0] = record->f24.b[0];
        record->f14.b[1] = texture_config->byte9;
        record->fC.b[1] = record->f14.b[1];
        record->f24.b[1] = texture_config->byte9 + texture_config->byteB;
        record->f1C.b[1] = record->f24.b[1];
        shade = ((u8)D_800273A8 << 7) / 240;
        *(u8 *)&record->f4.b[0] = shade;
        *(u8 *)&record->f4.b[2] = shade;
        *(u8 *)&record->f4.b[1] = shade;
        func_800666F4(record);
    }
    func_800654B0((void *)((u32)scratch | 0x70),
                  (void *)((u32)scratch | 0x78),
                  (void *)((u32)scratch | 0x80),
                  (void *)((u32)scratch | 0x88),
                  &record->f8.h[0], &record->f10.h[0],
                  &record->f18.h[0], &record->f20.h[0],
                  &scratch->w90, &scratch->w94);

    record->f8.h[0] = translate_x(record->f8.h[0], origin->index0);
    record->f18.h[0] = translate_x(record->f18.h[0], origin->index0);
    record->f10.h[0] = translate_x(record->f10.h[0], origin->index0);
    record->f20.h[0] = translate_x(record->f20.h[0], origin->index0);
    {
        s32 coord_y;
        coord_y = record->f8.h[1] - 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f8.h[1] = coord_y;
        coord_y = record->f10.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f10.h[1] = coord_y;
        coord_y = record->f18.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f18.h[1] = coord_y;
        coord_y = record->f20.h[1];
        coord_y -= 0x78;
        coord_y += origin->index1 + saved_y_offset;
        record->f20.h[1] = coord_y;
    }
    func_8006658C(scratch->value, record);
    func_80064A40();
    record = (Record *)((u8 *)record + 0x28);
    ((Root *)globals->unk_000)->record = record;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

   /* scratch in create_linked_objects */

   /* the 0x2 bytes before arg0 in create_linked_objects, addressed as arg0[-1] */

   /* arg0 in create_linked_objects */

   /* arg1 in create_linked_objects */

   /* arg2 in create_linked_objects */

s32 rand();

/* Rotate and move a quad, fade its color in and out, then mark it for removal. */
void create_linked_objects(void *quad, S_81960CD4_2 *motion, S_81960CD4_3 *effect) {
    u8 *scratch = (u8 *)0x1F800000;
    u16 rotation[3];
    s16 remaining_count;
    s16 fade_in_ticks;
    s16 fade_out_ticks;
    s32 blue_step;
    u16 center_z;
    u16 effect_count;
    u8 fade_in_blue;
    u8 fade_in_red;
    u8 fade_in_green;
    u8 fade_out_red;
    u8 fade_out_green;
    u8 fade_out_blue;
    u16 update_count;
    u16 vertex_z;

    ((S_81960CD4_0 *)scratch)->unk_70 = ((S_81960CD4_1 *)quad)->unk_10 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_78 = ((S_81960CD4_1 *)quad)->unk_18 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_80 = ((S_81960CD4_1 *)quad)->unk_20 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_88 = ((S_81960CD4_1 *)quad)->unk_28 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_72 = ((S_81960CD4_1 *)quad)->unk_12 - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_7A = ((S_81960CD4_1 *)quad)->unk_1A - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_82 = ((S_81960CD4_1 *)quad)->unk_22 - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_8A = ((S_81960CD4_1 *)quad)->unk_2A - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_74 = ((S_81960CD4_1 *)quad)->unk_14 - motion->unk_08.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_7C = ((S_81960CD4_1 *)quad)->unk_1C - motion->unk_08.at02.v;
    update_count = D_80027330;
    vertex_z = ((S_81960CD4_1 *)quad)->unk_24;
    center_z = motion->unk_08.at02.v;
    D_80027330 = (u16)(update_count + 1);
    ((S_81960CD4_0 *)scratch)->unk_84 = vertex_z - center_z;
    ((S_81960CD4_0 *)scratch)->unk_8C = ((S_81960CD4_1 *)quad)->unk_2C - motion->unk_08.at02.v;
    func_800649A0(center_z);
    rotation[0] = effect->unk_16;
    rotation[1] = effect->unk_18;
    rotation[2] = 0;
    ((S_81960CD4_0 *)scratch)->unk_30 = effect->unk_1C;
    ((S_81960CD4_0 *)scratch)->unk_34 = effect->unk_1E;
    ((S_81960CD4_0 *)scratch)->unk_38 = 0x1000;
    ((S_81960CD4_0 *)scratch)->unk_6C = 0;
    ((S_81960CD4_0 *)scratch)->unk_68 = 0;
    ((S_81960CD4_0 *)scratch)->unk_64 = 0;
    func_80065820(rotation, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);
    func_80065320(scratch + 0x70, scratch + 0x98, scratch + 0x94);
    func_80065320(scratch + 0x78, scratch + 0xA0, scratch + 0x94);
    func_80065320(scratch + 0x80, scratch + 0xA8, scratch + 0x94);
    func_80065320(scratch + 0x88, scratch + 0xB0, scratch + 0x94);
    func_80064A40();
    motion->unk_00.at00.v = (s32)(motion->unk_00.at00.v + motion->unk_0C);
    motion->unk_04.at00.v = (s32)(motion->unk_04.at00.v + motion->unk_10);
    motion->unk_08.at00.v = (s32)(motion->unk_08.at00.v + motion->unk_14);
    ((S_81960CD4_1 *)quad)->unk_10 = (u16)(((S_81960CD4_0 *)scratch)->unk_98 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_18 = (u16)(((S_81960CD4_0 *)scratch)->unk_A0 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_20 = (u16)(((S_81960CD4_0 *)scratch)->unk_A8 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_28 = (u16)(((S_81960CD4_0 *)scratch)->unk_B0 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_12 = (u16)(((S_81960CD4_0 *)scratch)->unk_9A + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_1A = (u16)(((S_81960CD4_0 *)scratch)->unk_A2 + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_22 = (u16)(((S_81960CD4_0 *)scratch)->unk_AA + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_2A = (u16)(((S_81960CD4_0 *)scratch)->unk_B2 + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_14 = (u16)(((S_81960CD4_0 *)scratch)->unk_9C + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_1C = (u16)(((S_81960CD4_0 *)scratch)->unk_A4 + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_24 = (u16)(((S_81960CD4_0 *)scratch)->unk_AC + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_2C = (u16)(((S_81960CD4_0 *)scratch)->unk_B4 + motion->unk_08.at02.v);
    if (((S_81960CD4_1 *)quad)->unk_48.s == 0) {
        fade_in_red = effect->unk_0C;
        effect->unk_0C = (u8)(fade_in_red + ((s32)(0xC0 - fade_in_red) / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_in_green = effect->unk_0D;
        remaining_count = ((S_81960CD4_1 *)quad)->unk_4C;
        fade_in_blue = effect->unk_0E;
        effect->unk_0D = (u8)(fade_in_green + ((s32)(0xC0 - fade_in_green) / remaining_count));
        blue_step = (s32)(0xC0 - fade_in_blue) / (s16)((S_81960CD4_1 *)quad)->unk_4C;
        effect->unk_0E = (u8)(fade_in_blue + blue_step);
        fade_in_ticks = (u16)((S_81960CD4_1 *)quad)->unk_4C - 1;
        ((S_81960CD4_1 *)quad)->unk_4C = fade_in_ticks;
        if ((fade_in_ticks << 0x10) <= 0) {
            motion->unk_0C = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            motion->unk_10 = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            motion->unk_14 = (s32)(((rand() & 0x3F) - 0x20) << 0x10);
            effect->unk_16 = (u16)((rand() & 0x3FF) - 0x200);
            effect->unk_18 = (u16)((rand() & 0x3FF) - 0x200);
            ((S_81960CD4_1 *)quad)->unk_4C = 0x10;
            ((S_81960CD4_1 *)quad)->unk_48.u = (u16)(((S_81960CD4_1 *)quad)->unk_48.u + 1);
            return;
        }
    } else {
        fade_out_red = effect->unk_0C;
        effect->unk_0C = (u8)(fade_out_red - ((s32)fade_out_red / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_green = effect->unk_0D;
        effect->unk_0D = (u8)(fade_out_green - ((s32)fade_out_green / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_blue = effect->unk_0E;
        effect->unk_0E = (u8)(fade_out_blue - ((s32)fade_out_blue / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_ticks = (u16)((S_81960CD4_1 *)quad)->unk_4C - 1;
        ((S_81960CD4_1 *)quad)->unk_4C = fade_out_ticks;
        if ((fade_out_ticks << 0x10) <= 0) {
            remaining_count = *(s16 *)((u16 *)&D_800273BC);
            if (remaining_count != 0) {
                effect_count = D_800273BC.value - 1;
                (*(u16 *)((u16 *)&D_800273BC)) = effect_count;
                if ((s16)effect_count == 1) {
                    (*(u16 *)((u16 *)&D_800273BC)) = 0U;
                }
            }
            ((S_81960CD4_1_pre *)quad)[-1].unk_00 = (u16)(((S_81960CD4_1_pre *)quad)[-1].unk_00 | 0x8000);
            object_flag_block.flags = object_flag_block.flags | 0x8000;
        }
    }
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/game_work.h"

#define SCRATCH ((Bank56_819611CC_Scratch *)0x1F800000)

/* Project a textured quad and queue it with semitransparency when its depth is in range. */
s32 project_and_queue_semitransparent_quad(Quad *quad, s32 unused, Material *material)
{
    Bank56_819611CC_Scratch *scratch;
    Bank56_819611CC_PolyFT4 *packet;
    Texture *texture;
    Bank56_819611CC_PolyFT4 *draw_packet;
    QuadLink *link;
    u32 depth;
    RenderState **slot;
    u32 xy3;
    u16 z0;
    u16 z;
    u16 z3;

    slot = ((RenderState * *)(&g_game_work));
    packet = (Bank56_819611CC_PolyFT4 *)(*slot)->packet;
    scratch = SCRATCH;
    scratch->ot_base = (u32)*slot + 0xB0;
    for (;;) {
        scratch->v[0].xy = quad->v[0].xy;
        scratch->v[1].xy = quad->v[1].xy;
        scratch->v[2].xy = quad->v[2].xy;
        z0 = quad->v[0].z;
        texture = material->texture;
        xy3 = quad->v[3].xy;
        scratch->v[0].z = z0;
        z = quad->v[1].z;
        scratch->v[1].z = z;
        z = quad->v[2].z;
        scratch->v[3].xy = xy3;
        scratch->v[2].z = z;
        z3 = quad->v[3].z;
        scratch->v[3].z = z3;
        depth = func_800654B0(&scratch->v[0], &scratch->v[1], &scratch->v[2], &scratch->v[3],
                              &packet->x0, &packet->x1, &packet->x2, &packet->x3,
                              &scratch->out_a, &scratch->out_b) - 8;
        scratch->depth = depth;
        if (depth < 480) {
            packet->u0 = packet->u2 = texture->u;
            packet->u1 = packet->u3 = texture->u + texture->w;
            packet->v0 = packet->v1 = texture->v;
            packet->v2 = packet->v3 = texture->v + texture->h;
            packet->tpage = texture->tpage;
            *(u32 *)&packet->r0 = material->color;
            func_800666F4(packet);
            draw_packet = packet;
            packet->code |= 2;
            packet++;
            func_8006658C(scratch->ot_base + (scratch->depth << 2), draw_packet);
        }
        link = ((QuadLink **)quad)[-2];
        if (link == 0) {
            break;
        }
        quad = &link->quad;
        material = link->material;
    }
    (*slot)->packet = (u8 *)packet;
    return 0;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "m2c_compat.h"

   /* arg2 in create_terrain_tile_quad */

/* Creates a terrain tile quad using grid heights and the supplied origin. */
void create_terrain_tile_quad(s16 tile_x, s32 tile_y, S_819613A8_0 *origin) {
    s16 left_x;
    s16 right_x;
    s16 top_y;
    s16 bottom_y;
    s32 row;
    s32 bottom_heights_addr;
    s32 y_offset;
    s32 column;
    s32 x_offset;
    s32 x_or_height;
    s32 y_or_color;
    s32 height;
    s32 height_tr;
    s32 height_bl;
    s32 height_br;
    s32 origin_height;
    s16 saved_row;
    s8 *height_row;
    void *output;
    void *quad;
    s16 *top_heights;
    s16 *top_row;
    s32 height_or_child;
    TempObj *object;

    object = (TempObj *)func_8003FC64(0x202);
    saved_row = tile_y;
    if (object != NULL) {
        s32 local_x_or_height;
        s32 local_height;
        s32 local_y;
        object->field10 = create_linked_objects;
        register_node(object, project_and_queue_semitransparent_quad);
        column = (s16) tile_x;
        x_offset = (column - 3);
        x_offset <<= 6;
        row = (u32) tile_y << 16;
        row >>= 16;
        height_row = ((s8 *)D_8002745C);
        tile_y = row;
        tile_y <<= 4;
        top_heights = (s16 *)(tile_y + (s32)height_row);
        top_row = top_heights;
        bottom_heights_addr = column << 1;
        top_heights = (s16 *)(bottom_heights_addr + (s32)top_row);
        height_row += 0x10;
        height_row = (s8 *)(tile_y + (s32)height_row);
        bottom_heights_addr += (s32)height_row;
        y_offset = (row - 3) << 6;
        output = object->field8;
        local_x_or_height = ((s16 *)origin)[1];
        local_y = ((s16 *)origin)[3];
        local_height = top_heights[0];
        height_tr = (u16)top_heights[1];
        height_tr = (u32)height_tr << 16;
        height_tr >>= 16;
        height_bl = (u16) ((s16 *)bottom_heights_addr)[0];
        height_bl = (u32)height_bl << 16;
        height_bl >>= 16;
        height_br = (u16)((s16 *)bottom_heights_addr)[1];
        height_br = (u32)height_br << 16;
        height_br >>= 16;
        origin_height = (u16)((s16 *)origin)[5];
        origin_height = (u32)origin_height << 16;
        origin_height >>= 16;
        local_x_or_height += x_offset;
        local_x_or_height <<= 16;
        local_x_or_height = (u32)local_x_or_height >> 16;
        local_y += y_offset;
        local_y <<= 16;
        local_y = (u32)local_y >> 16;
        local_height += height_tr;
        local_height += height_bl;
        local_height += height_br;
        local_height >>= 2;
        local_height += origin_height;
        ((TempBuffer *)output)->fieldA = local_height;
        ((TempBuffer *)output)->field2 = local_x_or_height;
        output = (s16 *)output + 3;
        *(s16 *)output = local_y;
        height_or_child = (s32)object->fieldC;
        quad = (void *)&object->field20;
        ((TempChild *)height_or_child)->field1E = 0x800;
        ((TempChild *)height_or_child)->field1C = 0x800;
        ((TempChild *)height_or_child)->field14 = 0xC;
        left_x = ((u16) origin->unk_02 + x_offset) - 0x20;
        ((TempOutput *)quad)->field20 = left_x;
        ((TempOutput *)quad)->field10 = left_x;
        right_x = ((u16) origin->unk_02 + ((column - 2) << 6)) - 0x20;
        ((TempOutput *)quad)->field28 = right_x;
        ((TempOutput *)quad)->field18 = right_x;
        top_y = ((u16) origin->unk_06 + y_offset) - 0x20;
        ((TempOutput *)quad)->field1A = top_y;
        ((TempOutput *)quad)->field12 = top_y;
        row -= 2;
        row <<= 2;
        row <<= 2;
        row <<= 2;
        bottom_y = ((u16) origin->unk_06 + row) - 0x20;
        ((TempOutput *)quad)->field2A = bottom_y;
        ((TempOutput *)quad)->field22 = bottom_y;
        ((TempOutput *)quad)->field14 = (s16) ((u16) origin->unk_0A + (u16) top_heights[0]);
        ((TempOutput *)quad)->field1C = (s16) ((u16) origin->unk_0A + (u16) top_heights[1]);
        tile_y -= 0x80;
        ((TempOutput *)quad)->field24 = (s16) ((u16) origin->unk_0A + (u16) ((s16 *)bottom_heights_addr)[0]);
        height = (u16) origin->unk_0A;
        x_or_height = (u16) ((s16 *)bottom_heights_addr)[1];
        height += x_or_height;
        ((TempOutput *)quad)->field2C = height;
        y_or_color = 0xF8F82CC0;
        height = 0x13D;
        object->field20 = y_or_color;
        ((TempOutput *)quad)->field4 = height;
        height = column * 0x10;
        ((TempOutput *)quad)->field8 = (s8) height;
        height = 6;
        ((TempOutput *)quad)->field9 = (s8) tile_y;
        if (column == height) {
            height = 0xF;
        } else {
            height = 0x10;
        }
        height_bl = (s8)height;
        ((TempOutput *)quad)->fieldA = height_bl;
        height = saved_row;
        x_or_height = 6;
        if (height == x_or_height) {
            height = 0xF;
        } else {
            height = 0x10;
        }
        height_tr = height;
        height_tr = (u32)height_tr << 24;
        height_tr >>= 24;
        ((TempOutput *)quad)->fieldB = height_tr;
        ((TempChild *)height_or_child)->field8 = quad;
        ((TempOutput *)quad)->field4C = 8;
        (*(s16 *)((s16 *)&D_800273BC)) = (s16) ((*(u16 *)((s16 *)&D_800273BC)) + 1);
    }
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"

extern void **D_800E3D18;

/* Interpolate the target position, fade its color, and finish the transition. */
/* MECHANISM: state->state selects with a switch, cases 0..3 laid out in source order so the
   dispatch tree's last `beq ==3` is followed by case 0's body (an if-chain puts case 3's body
   right after the default jump and jump.c inverts the test).  case 0 falls through into case 1.
   The `j 0x271ec` sites are the switch's end-of-switch edge = `return`; the `j 0x2711c` from
   case 1 ends with the same `state->state = value + 1; return` tail as case 2 (written out
   in both arms), and case 2's step != 0 path repeats case 3's flag-setting tail.  The 0x80080000 page plus 0x2E80 is the symbol D_80082E80,
   which is what frees the $2 pin; one u16 carrying the 5 and the 4 keeps the join value in v0. */
void interpolate_target_and_finish_transition(State *state, Target *target, S_func_819615E4_0 *color)
{
    Vec3s position_offset;
    Vec3s position;
    s32 distance;
    s32 current_coord;
    s16 smoothed_coord;
    u16 phase_value;
    u16 const_reg;

    D_80027330++;

    switch (state->state) {
    case 0:
    {
        s32 transform_offset;

        position.x = ((u16)D_80083780.x.w.i);
        position.y = ((u16)D_80083780.y.w.i);
        position.z = ((S_func_819615E4_2 *)((u8 *)D_800E3D7C))->unk_88.u16_value - 0x50;
        transform_offset = ((g_game_work.view.viewAngle + ((S_func_819615E4_2 *)((u8 *)D_800E3D7C))->unk_2A.s16_value + 0x100) >> 7) & 0x1C;
        resolve_record_orientation_or_fallback(((S_func_819615E4_3 *)((s32)transform_offset + (s32)D_800E3D18))->unk_00, ((u8 *)(&D_80082E80)),
                      &position_offset, 0);
        position.x += position_offset.x;
        state->x = position.x;
        position.y += position_offset.y;
        state->y = position.y;
        position.z += position_offset.z;
        state->z = position.z;
        state->state++;
    }
    case 1:
    {
        s32 step_offset;

        current_coord = state->cur_x;
        distance = state->x - current_coord;
        if (distance < 0) {
            distance += 7;
        }
        step_offset = (distance >> 3) * (state->step + 1);
        target->x = (u16)target->x +
            (current_coord + step_offset - target->x) / state->timer;
    }
    {
        s32 step_offset;

        current_coord = state->cur_y;
        distance = state->y - current_coord;
        if (distance < 0) {
            distance += 7;
        }
        step_offset = (distance >> 3) * (state->step + 1);
        target->y = (u16)target->y +
            (current_coord + step_offset - target->y) / state->timer;
    }
    {
        s32 step_offset;

        current_coord = state->cur_z;
        distance = state->z - current_coord;
        step_offset = (distance / 8) * (state->step + 1);
        target->z = (u16)target->z +
            (current_coord + step_offset - target->z) / state->timer;
    }

    smoothed_coord = (u16)state->cur_x + ((target->x - state->cur_x) >> 2);
    state->cur_x = smoothed_coord;
    target->cur_x = smoothed_coord;
    smoothed_coord = (u16)state->cur_y + ((target->y - state->cur_y) >> 2);
    state->cur_y = smoothed_coord;
    target->cur_y = smoothed_coord;
    smoothed_coord = (u16)state->cur_z + ((target->z - state->cur_z) >> 2);
    state->cur_z = smoothed_coord;
    target->cur_z = smoothed_coord;

    phase_value = state->timer - 1;
    state->timer = phase_value;
    if ((s16)phase_value > 0) {
        return;
    }
    spawn_blinking_sprite_flash(state->x, state->y, state->z);
    phase_value = state->state;
    const_reg = 5;
    state->timer = const_reg;
    state->state = phase_value + 1;
    return;

    case 2:
    color->unk_0C -= color->unk_0C / state->timer;
    phase_value = state->timer - 1;
    state->timer = phase_value;
    if ((s16)phase_value > 0) {
        return;
    }
    if (state->step == 0) {
        color->unk_0C = 0;
        const_reg = 4;
        state->phase = const_reg;
        phase_value = state->state;
        state->state = phase_value + 1;
        return;
    }
    *(u16 *)((u8 *)state - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
    return;

    case 3:
    {
        s32 direction_offset;
        TileObject *table;

        table = &D_80082E80;
        resolve_record_orientation_or_fallback(((void *)table->unk_008), table, &position, 0);
        phase_value = state->phase - 1;
        state->phase = phase_value;
        if ((s16)phase_value > 0) {
            return;
        }
        direction_offset = ((((S_func_819615E4_2 *)((u8 *)D_800E3D7C))->unk_2A.u16_value >> 8) & 0xE);
        func_80025334(
            (s16)(((table->tileX +
                    (((S_func_819615E4_5 *)((u8 *)((s8 *)dir_step_x) + direction_offset))->unk_00 * 4)) << 6) + 0x20),
            (s16)(((table->tileY +
                    (((S_func_819615E4_6 *)((u8 *)((s8 *)dir_step_y) + direction_offset))->unk_00 * 4)) << 6) + 0x20),
            ((S_func_819615E4_2 *)((u8 *)D_800E3D7C))->unk_88.s16_value);
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }
    }
    return;
}
#include "modules/dungeon_ovl_197e800.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 D_800273B0;
extern u8 D_800CEEFC[];

/* Allocates and initializes objects at the supplied position across nine slots. */
void *allocate_nine_position_objects(void *position)
{
    S_81961A04_1 *source_pos;
    s32 slot;
    s32 *object_handler;
    s32 *control_handler;
    s32 last_slot;
    void *object;
    s16 slot_offset;
    s16 control_value;
    u16 control_scale;
    u16 pos_x;
    u16 pos_y;
    u16 pos_z;
    S_81961A04_4 *control;
    S_81961A04_3 *state;
    S_81961A04_2 *positions;

    source_pos = position;
    slot = 0;
    object_handler = interpolate_target_and_finish_transition;
    control_handler = &D_800273B0;
    last_slot = 8;
    do {
        object = func_8003FC64(2);
        if (object != NULL) {
            ((S_81961A04_0 *)object)->unk_10 = object_handler;
            register_node(object, &D_800CEEFC);
            positions = ((S_81961A04_0 *)object)->unk_08;
            pos_x = source_pos->unk_02;
            state = object + 0x20;
            positions->unk_02 = pos_x;
            positions->unk_0E = pos_x;
            state->unk_38 = pos_x;
            pos_y = source_pos->unk_06;
            positions->unk_06 = pos_y;
            positions->unk_12 = pos_y;
            state->unk_3A = pos_y;
            pos_z = source_pos->unk_0A;
            positions->unk_0A = pos_z;
            positions->unk_16 = pos_z;
            state->unk_3C = pos_z;
            control = ((S_81961A04_0 *)object)->unk_0C;
            ((SpriteFrameState *)control)->source = control_handler;
            if (slot != last_slot) {
                ((SpriteFrameState *)control)->scale_y = 0x200U;
            } else {
                ((SpriteFrameState *)control)->scale_y = 0x800U;
            }
            slot_offset = (last_slot - slot) * 4;
            control_value = -0x80 - slot_offset;
            control_scale = ((SpriteFrameState *)control)->scale_y;
            ((SpriteFrameState *)control)->color.c.r = (s8)control_value;
            ((SpriteFrameState *)control)->scale_x = control_scale;
            state->unk_54 = slot;
            if (slot == last_slot) {
                state->unk_54 = 7;
            }
            state->unk_4C = last_slot;
        }
        slot += 1;
    } while (slot < 9);
    return object;
}
