#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_func_8133A3F0_0 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    s32 *unk_10;
    u8 pad_14[0x24];
    s16 unk_38;
} S_func_8133A3F0_0;

extern s32 register_node();
extern s32 encounter_actor_update_address;
extern s8 encounter_recovery_flag;

/* Creates object 0x112 and initializes its position and render state. */
void create_encounter_actor_object(void) {
    S_func_8133A3F0_0 *object;
    SpriteFrameState *render_state;
    MovingPosition *position;

    object = allocate_flagged_object_node(0x112);
    if (object != 0) {
        render_state = object->unk_0C;
        object->unk_38 = 0;
        object->unk_10 = &encounter_actor_update_address;
        register_node(object, project_sprite_chain);
        position = object->unk_08;
        render_state->flags = (u16)(render_state->flags | 0x80);
        position->x = ((u16)view_reference_entity.x.w.i);
        position->y = ((u16)view_reference_entity.y.w.i);
        position->z = ((u16)view_reference_entity.z.w.i);
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        render_state->color.c.b = 0x80;
        render_state->color.c.g = 0x80;
        render_state->color.c.r = 0x80;
        encounter_recovery_flag = 0;
    }
}
