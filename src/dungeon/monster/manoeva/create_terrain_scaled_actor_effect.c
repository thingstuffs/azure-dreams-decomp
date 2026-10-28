#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "engine/graphics.h"
#include "engine/node/allocation.h"

typedef struct S_80174B90_4 {
    u8 pad_00[0x14];
    void * unk_14;
} S_80174B90_4;

typedef struct S_80174B90_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174B90_6;   /* arg0 in create_terrain_scaled_actor_effect */

typedef struct S_80174B90_7 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80174B90_7;

   /* ((S_80174B90_6 *)arg0)->unk_08 in create_terrain_scaled_actor_effect */

s32 register_node(ObjectNodeHeader *entry, void *registration_id);           /* extern */
void D_8017474C(void *effect, MovingPosition *out_position, void *out_render);
extern M2C_UNK D_80175540;

typedef struct S_80174B90_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void (*unk_10)(void *, MovingPosition *, void *);
    u8 pad_14[0xC];
    s32 unk_20;
} S_80174B90_0;

typedef struct S_80174B90_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
    void * unk_18;
    s16 unk_1C;
} S_80174B90_1;

typedef struct S_80174B90_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174B90_2;   /* arg0 in create_terrain_scaled_actor_effect */

/* Create an effect using the source object's rendering and transform data. */
void create_terrain_scaled_actor_effect(S_80174B90_2 *source, s32 state_00, s32 state_04, s32 state_08) {
    void *allocation_head_address;
    ObjectNodeHeader **allocation_head;
    SpriteFrameState *render_data;
    S_80174B90_1 *effect_state;
    ObjectNodeHeader *effect;

    allocation_head_address = source;
    allocation_head = allocation_head_address;
    effect = allocate_list_node(0x100,allocation_head);
    if (effect != NULL) {
        render_data = effect->sprite;
        effect_state = ((void *)effect) + 0x20;
        effect->update_callback = &D_8017474C;
        effect_state->unk_14 = (void *) source->unk_0C;
        effect_state->unk_18 = (void *) source->unk_08;
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        render_data->color.word = 0x808080;
        render_data->animation_resource = (s32) ((S_80174B90_7 *)effect_state->unk_14)->unk_28;
        render_data->clut = (u16) ((S_80174B90_7 *)effect_state->unk_14)->unk_12;
        ((MovingPosition *)(effect->position))->x =
            (u16) ((MovingPosition *)source->unk_08)->x;
        ((MovingPosition *)(effect->position))->y =
            (u16) ((MovingPosition *)source->unk_08)->y;
        ((MovingPosition *)(effect->position))->z =
            (u16) ((MovingPosition *)source->unk_08)->z;
        select_sprite_entry(render_data, 0x46, 0);
        register_node(effect, &D_80175540);
        ((S_80174B90_0 *)effect)->unk_20 = state_00;
        effect_state->unk_04 = state_04;
        effect_state->unk_08 = state_08;
        effect_state->unk_0C = source;
        effect_state->unk_1C = 0x1000;
    }
}
