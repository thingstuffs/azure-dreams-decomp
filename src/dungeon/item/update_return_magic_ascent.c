#include "shared/runtime_dispatch.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/transition_slots.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/player/item.h"

typedef struct {
    u8 pad0[0x8D0];
    void *nextPrim;
} RenderState;

typedef struct {
    u8 pad0[4];
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
} Primitive;

typedef struct {
    u8 pad0[0x4A];
    s16 phase;
    u16 counter;
    u8 pad50[4];
    s16 count;
    u8 pad54[0x14];
    u8 *handle;
} DungeonObject;

typedef struct {
    u8 pad0[8];
    s32 field8;
    u8 padC[8];
    s32 field14;
} MotionState;

typedef struct {
    u8 pad0[0xC];
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF[0xD];
    u16 field1C;
} EffectState;

typedef struct {
    s32 field18;
    s32 field1C;
    s16 field20;
    s16 field22;
} StackData;

extern u8 upper_draw_context[16];
extern u8 return_magic_frames[];
extern s16 transition_runtime_slot_index;

extern void AddPrim();
extern void SetLineF2();
extern void SetDrawArea();
extern s32 rand();
extern void begin_deferred_player_item_effect();
extern s32 reserve_runtime_slot();
extern void set_sprite_animation_frame();
extern void snapshot_inventory_and_familiars();
extern void draw_transformed_sprite_with_clip_rect();
extern void request_scene_state_with_parameters();

/* Draws randomized vertical streaks and advances the object's motion and fade sequence. */
void update_return_magic_ascent(DungeonObject *obj, MotionState *motion, EffectState *effect) {
    StackData draw_data;
    s16 use_alt_buffer;
    u32 buffer_diff;
    RenderState **render_state_slot;
    RenderState *render_state;
    RenderState *call_state;
    Primitive *prim;
    u8 *prim_list;
    s32 index_or_phase;
    s32 area_origin;

    area_origin = 0x01800340;
    draw_data.field18 = area_origin;
    draw_data.field1C = 0x00400040;
    render_state_slot = &g_game_work.draw_buffer;
    render_state = g_game_work.draw_buffer;
    prim = (Primitive *)render_state->nextPrim;
    render_state->nextPrim = (u8 *)prim + 0xC;
    buffer_diff = (u32)render_state ^ (u32)upper_draw_context;
    prim_list = (u8 *)render_state + 0x8B0;
    call_state = g_game_work.draw_buffer;
    use_alt_buffer = buffer_diff != 0;
    SetDrawArea(prim, call_state, render_state);
    AddPrim(prim_list, prim);

    if (obj->count > 0) {
        index_or_phase = 0;
        do {
            RenderState *streak_state;
            streak_state = *render_state_slot;
            prim = (Primitive *)streak_state->nextPrim;
            streak_state->nextPrim = (u8 *)prim + 0x10;
            prim->fieldC = (rand() & 0x3F) + 0x340;
            prim->field8 = prim->fieldC;
            {
                s32 y_offset = rand() & 0x3F;
                s32 bottom_y;
                prim->fieldA = 0x180 - y_offset;
                do {
                    bottom_y = 0x1BF - y_offset;
                } while (0);
                prim->fieldE = bottom_y;
                if (use_alt_buffer) {
                    bottom_y -= 0xE0;
                    prim->fieldE = bottom_y;
                    prim->fieldA -= 0xE0;
                }
            }
            prim->field4 = 0;
            SetLineF2(prim);
            AddPrim(prim_list, prim);
            index_or_phase += 1;
        } while (index_or_phase < obj->count);
    }

    if (obj->count < 0x60) {
        obj->count = (u16)obj->count + 1;
    }

    {
        RenderState *area_state;
        area_state = *render_state_slot;
        prim = (Primitive *)area_state->nextPrim;
        area_state->nextPrim = (u8 *)prim + 0xC;
        SetDrawArea(prim, &draw_data.field18);
        AddPrim(prim_list, prim);
    }
    draw_data.field20 = 0x360;
    draw_data.field22 = 0x1B8;
    draw_transformed_sprite_with_clip_rect(obj->handle, &draw_data.field18, &draw_data.field20, 1, 0);

    {
        u16 frame_count = obj->counter + 1;
        index_or_phase = (s16)obj->phase;
        obj->counter = frame_count;
        if (index_or_phase == 0) {
            if ((s16)frame_count >= 0x21) {
                if (obj->handle[0x13] == 0) {
                    ActorRecord *dungeon_state;
                    begin_deferred_player_item_effect(obj->handle, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), 0);
                    dungeon_actor_ring_anchor->unk_9B = 0x11;
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
            MotionState *parent_motion;
            effect->fieldC = effect->fieldC - (effect->fieldC >> 3);
            effect->fieldD = effect->fieldD - (effect->fieldD >> 3);
            effect->fieldE = effect->fieldE - (effect->fieldE >> 3);
            effect->field1C = effect->field1C + ((0x400 - effect->field1C) >> 2);
            parent_motion = *(MotionState **)((u8 *)obj - 0x18);
            motion->field8 = motion->field8 + motion->field14;
            parent_motion->field8 = motion->field8;
            motion->field14 = motion->field14 + 0xFFFC0000;
            if (obj->handle[0x13] == 0 &&
                (*(u16 *)(*(u8 * *)&((ObjectNodeHeader *)((u8 *)dungeon_actor_ring_anchor - 0x20))->sprite + 0x14) & 0x6000)) {
                s16 entry_index = reserve_runtime_slot(6, 0x20);
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
