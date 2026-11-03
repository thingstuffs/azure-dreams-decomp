#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/state.h"
struct Entry;

s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
extern void retire_effect_when_status_set(void *record);
extern s32 render_actor_sprite_chain(void *initial_state, void *context, struct Entry *entry);

typedef struct S_800ADC4C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)(void *);
    u8 pad_14[0xC];
    s8 * unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
} S_800ADC4C_0;

/* Create an object with the supplied position and render settings, and clear its status flag. */
void *create_status_linked_render_effect(ObjectPosition *source_pos, s32 render_param, s16 initial_state, s8 *status) {
    S_800ADC4C_0 *object;
    SpriteFrameState *render_data;
    MovingPosition *position;

    object = allocate_list_node(0x12, &scene_object_list_anchor.next);
    if (object != NULL) {
        object->unk_10 = &retire_effect_when_status_set;
        register_node(object, &render_actor_sprite_chain);
        position = object->unk_08;
        position->x = (u16) ((u16)source_pos->x.w.i);
        position->y = (u16) ((u16)source_pos->y.w.i);
        position->z = (u16) ((u16)source_pos->z.w.i);
        render_data = object->unk_0C;
        render_data->source = render_param;
        render_data->color.word = 0x808080;
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        object->unk_28 = initial_state;
        object->unk_20 = status;
        *status = 0;
    }
    return object;
}
