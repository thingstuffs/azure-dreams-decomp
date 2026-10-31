#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node/allocation.h"
typedef struct S_801745F0_0 S_801745F0_0;

typedef struct S_80047784 S_80047784;

typedef struct S_80174690_4 {
    u8 pad_00[0x18];
    void * unk_18;
} S_80174690_4;

typedef struct S_80174690_5 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80174690_5;

s32 register_node(ObjectNodeHeader *entry, void *registration_id);           /* extern */
void select_sprite_entry(void *object, s16 table_index, s16 entry_index);    /* extern */
void copy_linked_position_and_check_status(void *object, MovingPosition *dest, SpriteFrameState *status);

typedef struct S_80174690_1 {
    u8 pad_00[0x18];
    void * unk_18;
    s32 unk_1C;
} S_80174690_1;

typedef struct S_80174690_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_80174690_2;   /* arg0 in create_action_sprite_effect */

/* Creates an effect from the source and initializes its sprite and callbacks. */
void create_action_sprite_effect(S_80174690_2 *source) {
    void *allocation_head_address;
    ObjectNodeHeader **allocation_head;
    SpriteFrameState *sprite;
    S_80174690_1 *effect_data;
    ObjectNodeHeader *effect;

    allocation_head_address = source;
    allocation_head = allocation_head_address;
    effect = allocate_list_node(0x112,allocation_head);
    if (effect != 0) {
        sprite = effect->sprite;
        effect->update_callback = &copy_linked_position_and_check_status;
        effect_data = ((void *)effect) + 0x20;
        effect_data->unk_18 = source->unk_0C;
        effect_data->unk_1C = (s32) source->unk_08;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.word = 0x808080;
        sprite->clut = (u16) (sprite->clut - 0x80);
        sprite->flags = (u16) (sprite->flags | 0xC);
        sprite->animation_resource = (s32) ((S_80174690_5 *)effect_data->unk_18)->unk_28;
        select_sprite_entry(sprite, 0x44, 0);
        register_node(effect, project_sprite_chain);
    }
}
