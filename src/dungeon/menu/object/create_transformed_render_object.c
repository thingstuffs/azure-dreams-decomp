#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct {
    u8 value0;
    u8 value1;
    u8 value2;
    u8 pad03[0x17];
    s16 state;
    u16 counter;
    u8 pad20[8];
    s32 flags;
    u8 pad2c[2];
    s16 mode;
} InterpState;
typedef struct {
    u8 pad00[0x0c];
    u8 value0;
    u8 value1;
    u8 value2;
    u8 pad0f[0x0d];
    u16 counter;
    u16 counter_copy;
} InterpTarget;

s32 func_80064BC0(void *, void *);
s32 func_80064CF0(void *);
s32 func_80064D80(void *);
s32 func_80065420(void *, void *, void *, void *);
s32 func_80065820(void *, void *);
void interpolate_delayed_target_values(InterpState *state, void *unused, InterpTarget *target);
extern M2C_UNK D_800DD824;

/* Creates an object at transformed coordinates and initializes its rendering and state. */
void *create_transformed_render_object(s32 x, s32 y, s32 initial_value, s32 update_param, s32 mode) {
    s32 alloc_flags;
    ObjectPosition *position;
    ObjectNodeHeader *object;
    SpriteFrameState *render_data;
    void *state;
    u8 *scratchpad;
    MapGrid *view_config;
    u8 *camera_config;

    alloc_flags = 2;
    view_config = &g_game_work.map;
    camera_config = (u8 *)view_config - 0x1C4;
    scratchpad = (u8 *)0x1F800000;
    if (mode != 0) {
        alloc_flags = 0x202;
    }
    object = allocate_flagged_object_node(alloc_flags);
    if (object != NULL) {
        position = *(void **)((u8 *)object + 8);
        object->unk_10 = &interpolate_delayed_target_values;
        *(u16 *)(scratchpad + 0x98) = 0;
        *(u16 *)(scratchpad + 0x9A) = 0;
        *(u32 *)(scratchpad + 0x34) = 0x1800;
        *(u32 *)(scratchpad + 0x30) = 0x1800;
        *(u32 *)(scratchpad + 0x38) = 0;
        *(u16 *)(scratchpad + 0x9C) = *(u16 *)(camera_config + 0xB0);
        func_80065820((void *)0x1F800098, (void *)0x1F8000D0);
        func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
        *(u32 *)(scratchpad + 0xE4) = 0;
        *(u32 *)(scratchpad + 0xE8) = 0;
        *(u32 *)(scratchpad + 0xEC) = 0;
        func_80064CF0((void *)0x1F8000D0);
        func_80064D80((void *)0x1F8000D0);
        *(u16 *)(scratchpad + 0x74) = 0;
        *(u16 *)(scratchpad + 0x70) = x - ((s32)(1 << view_config->shiftX) / 2);
        *(u16 *)(scratchpad + 0x72) = y - ((s32)(1 << view_config->shiftY) / 2);
        func_80065420((void *)0x1F800070, (void *)0x1F8000F0,
                      (void *)0x1F800090, (void *)0x1F800094);
        *(u16 *)((u8 *)position + 2) = *(u16 *)(scratchpad + 0xF0);
        position->y.w.i = *(u16 *)(scratchpad + 0xF2);
        render_data = object->sprite;
        render_data->flags = 0xC;
        render_data->source = &D_800DD824;
        render_data->scale_y = 0x2000;
        render_data->scale_x = 0x2000;
        state = (u8 *)object + 0x20;
        *(s16 *)((u8 *)state + 0x1C) = 8;
        *(s32 *)((u8 *)object + 0x20) = initial_value;
        *(s32 *)((u8 *)state + 0x28) = update_param;
        *(s16 *)((u8 *)state + 0x2E) = (s16)mode;
        if (mode == 0) {
            dungeon_floor_flags |= 0x40000;
        }
    }
    return object;
}
