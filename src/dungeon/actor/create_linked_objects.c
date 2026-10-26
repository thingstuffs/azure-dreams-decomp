#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800264D4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800264D4_0;

   /* arg0 in create_linked_objects */


typedef struct S_800264D4_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    struct {
        u16 x;
        u16 y;
        u16 z;
        u16 pad;
    } history[8];
    u8 pad_64[0x2];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
    u8 pad_70[0x2];
    s16 unk_72;
} S_800264D4_4;

typedef struct {
    u8 unk00[8];
    void *addr;
    u8 unk0c[4];
    s16 unk10;
    s16 unk12;
    u16 flags;
    u8 unk16[6];
    s16 unk1c;
    s16 unk1e;
} NodeA;

extern u8 linked_graphic_sprite_entries;
extern u8 D_800260DC[];
extern u8 linked_object_draw_address[];

void *allocate_list_node(s32, void *);
s32 register_node(void *, void *);

/* Creates six linked objects at the source position and initializes their position histories. */
void *create_linked_objects(MovingPosition *source_pos, s32 effect_value, s16 sprite_id, s16 effect_option) {
    s32 object_index;
    s32 sprite_index;
    s32 fixed_x;
    s32 fixed_y;
    s32 fixed_z;
    s32 history_index;
    u16 pos_x;
    u16 pos_y;
    u16 pos_z;
    u16 sprite_flags;
    s32 new_flags;
    SpriteFrameState *sprite;
    S_800264D4_4 *effect_state;
    ObjectPosition *position;
    ObjectNodeHeader *object;
    void *previous_object;
    u8 *page_base;

    previous_object = NULL;
    object_index = 0;
    page_base = &D_800260DC[0];
    sprite_index = (sprite_id << 0x10) >> 16;
create_object:
    object = allocate_list_node(0x12, &scene_object_list_anchor.next);
    if (object != NULL) {
        object->update_callback = page_base;
        register_node(object, &linked_object_draw_address);
        position = object->position;
        pos_x = source_pos->x;
        position->x.w.i = pos_x;
        *((u16 *)&position->velocity_x + 1) = pos_x;
        pos_y = source_pos->y;
        position->y.w.i = pos_y;
        *((u16 *)&position->velocity_y + 1) = pos_y;
        pos_z = source_pos->z;
        position->z.w.i = pos_z;
        *((u16 *)&position->velocity_z + 1) = pos_z;
        sprite = object->sprite;
        sprite_flags = sprite->flags;
        sprite->source = (void *) ((sprite_index * 0xC) + &linked_graphic_sprite_entries);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->tpage_abr = 0x60;
        new_flags = sprite_flags;
        new_flags |= 0xC;
        sprite->flags = new_flags;
        effect_state = ((void *)object) + 0x20;
        effect_state->unk_04 = effect_value;
        ((S_800264D4_0 *)object)->unk_20 = source_pos;
        effect_state->unk_66 = 0x20;
        effect_state->unk_6E = object_index;
        fixed_x = position->x.v;
        effect_state->unk_18 = fixed_x;
        effect_state->unk_0C = fixed_x;
        fixed_y = position->y.v;
        effect_state->unk_1C = fixed_y;
        effect_state->unk_10 = fixed_y;
        fixed_z = position->z.v;
        effect_state->unk_20 = fixed_z;
        effect_state->unk_14 = fixed_z;
        for (history_index = 0; history_index < 8; history_index++) {
            effect_state->history[history_index].x = *(u16 *)&position->x.w.i;
            effect_state->history[history_index].y = *(u16 *)&position->y.w.i;
            effect_state->history[history_index].z = *(u16 *)&position->z.w.i;
        }
        effect_state->unk_08 = previous_object;
        previous_object = object;
        object_index += 1;
        effect_state->unk_72 = effect_option;
        if (object_index >= 6) {

        } else {
            goto create_object;
        }
    }
    return object;
}
