#include "shared/gpu_packets.h"
#include "dungeon/item_callbacks_api.h"
#include "shared/runtime_dispatch.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/transition_slots.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/player/item.h"
#include "engine/scene.h"
#include "slus.h"
#include "sdk/libc.h"
#include "engine/graphics.h"
#include "dungeon/data.h"


typedef struct {
    u8 pad0[4];
    s32 color_code;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} Primitive;

typedef struct {
    s32 clip_origin_xy;
    s32 clip_extent_wh;
    s16 screen_x;
    s16 screen_y;
} StackData;

void AddPrim(void *, void *);
void SetLineF2(void *);
extern void SetDrawArea();
extern void draw_transformed_sprite_with_clip_rect();

/* Draws randomized vertical streaks and advances the object's motion and fade sequence. */
void update_return_magic_ascent(ReturnMagicAscentBody *obj, ObjectPosition *motion, SpriteFrameState *effect) {
    StackData draw_data;
    s16 use_alt_buffer;
    u32 buffer_diff;
    GpuContext **render_state_slot;
    GpuContext *render_state;
    GpuContext *call_state;
    Primitive *prim;
    u32 *prim_list;
    s32 index_or_phase;
    s32 area_origin;

    area_origin = 0x01800340;
    draw_data.clip_origin_xy = area_origin;
    draw_data.clip_extent_wh = 0x00400040;
    render_state_slot = &g_game_work.draw_buffer;
    render_state = g_game_work.draw_buffer;
    prim = render_state->packetCursor;
    render_state->packetCursor = (u8 *)prim + 0xC;
    buffer_diff = (u32)render_state ^ (u32)upper_draw_context;
    prim_list = &render_state->orderTag[528];
    call_state = g_game_work.draw_buffer;
    use_alt_buffer = buffer_diff != 0;
    SetDrawArea(prim, call_state, render_state);
    AddPrim(prim_list, prim);

    if (obj->streak_count > 0) {
        index_or_phase = 0;
        do {
            GpuContext *streak_state;
            streak_state = *render_state_slot;
            prim = streak_state->packetCursor;
            streak_state->packetCursor = (u8 *)prim + 0x10;
            prim->x1 = (rand() & 0x3F) + 0x340;
            prim->x0 = prim->x1;
            {
                s32 y_offset = rand() & 0x3F;
                s32 bottom_y;
                prim->y0 = 0x180 - y_offset;
                /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_800BACA4). */
                do {
                    bottom_y = 0x1BF - y_offset;
                } while (0);
                prim->y1 = bottom_y;
                if (use_alt_buffer) {
                    bottom_y -= 0xE0;
                    prim->y1 = bottom_y;
                    prim->y0 -= 0xE0;
                }
            }
            prim->color_code = 0;
            SetLineF2(prim);
            AddPrim(prim_list, prim);
            index_or_phase += 1;
        } while (index_or_phase < obj->streak_count);
    }

    if (obj->streak_count < 0x60) {
        obj->streak_count = (u16)obj->streak_count + 1;
    }

    {
        GpuContext *area_state;
        area_state = *render_state_slot;
        prim = area_state->packetCursor;
        area_state->packetCursor = (u8 *)prim + 0xC;
        SetDrawArea(prim, &draw_data.clip_origin_xy);
        AddPrim(prim_list, prim);
    }
    draw_data.screen_x = 0x360;
    draw_data.screen_y = 0x1B8;
    draw_transformed_sprite_with_clip_rect(obj->owner, &draw_data.clip_origin_xy, &draw_data.screen_x, 1, 0);

    {
        u16 frame_count = obj->counter + 1;
        index_or_phase = (s16)obj->phase;
        obj->counter = frame_count;
        if (index_or_phase == 0) {
            if ((s16)frame_count >= 0x21) {
                if (obj->owner->species == 0) {
                    ActorRecord *dungeon_state;
                    begin_deferred_player_item_effect(obj->owner, ((u8 *)(&view_reference_entity)), ((&reference_tile_object)), 0);
                    dungeon_actor_ring_anchor->action_phase = 0x11;
                    dungeon_state = dungeon_actor_ring_anchor;
                    reference_tile_object.frame_table = (s32)return_magic_frames;
                    set_sprite_animation_frame(
                        ((u8 *)(&reference_tile_object)),
                        return_magic_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + dungeon_state->facing) + 0x100 >> 9) & 7],
                        1,
                        1);
                }
                obj->phase = (u16)obj->phase + 1;
            } else {
                return;
            }
        } else if (index_or_phase == 1) {
            ObjectPosition *node_position;
            effect->color.c.r = effect->color.c.r - (effect->color.c.r >> 3);
            effect->color.c.g = effect->color.c.g - (effect->color.c.g >> 3);
            effect->color.c.b = effect->color.c.b - (effect->color.c.b >> 3);
            effect->scale_x = effect->scale_x + ((0x400 - effect->scale_x) >> 2);
            node_position = NODE_HEADER(obj)->position;
            motion->z.v = motion->z.v + motion->velocity_z;
            node_position->z.v = motion->z.v;
            motion->velocity_z = motion->velocity_z + 0xFFFC0000;
            if (obj->owner->species == 0 &&
                (NODE_HEADER(dungeon_actor_ring_anchor)->sprite->flags & 0x6000)) {
                s16 entry_index = reserve_transition_slot(6, 0x20);
                u8 *entry_table = (u8 *)runtime_transition_slots;
                s16 *entry_flag;
                void *active_dungeon;
                transition_runtime_slot_index = entry_index;
                entry_flag = (s16 *)(entry_table + (((s32)(entry_index << 16)) >> 0xD) + 6);
                active_dungeon = dungeon_actor_ring_anchor;
                *entry_flag = index_or_phase;
                snapshot_inventory_and_familiars(active_dungeon);
                snapshot_inventory_familiar_records();
                runtime_dispatch_state.flags16 = 0x8000;
                request_scene_state_with_parameters(6, 0, 0, 0, 0x8000);
                obj->phase = (u16)obj->phase + 1;
            }
        }
    }
}
