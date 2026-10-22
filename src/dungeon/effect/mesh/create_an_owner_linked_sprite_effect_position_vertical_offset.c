#include "shared/entity_height_offsets.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_81977D08_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81977D08_0;

typedef struct S_81977D08_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81977D08_3;   /* arg1 in create_an_owner_linked_sprite_effect_position_vertical_offset */

typedef struct S_81977D08_4 {
    u8 pad_00[0x14];
    void * unk_14;
} S_81977D08_4;   /* arg0 in create_an_owner_linked_sprite_effect_position_vertical_offset */

typedef struct S_81977D08_5 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_81977D08_5;   /* ((S_81977D08_4 *)arg0)->unk_14 in create_an_owner_linked_sprite_effect_position_vertical_offset */

extern s32 select_record_entry_and_value();
extern void *allocate_list_node();
extern s32 register_node();

extern s32 D_8002548C;
extern s32 D_800DEB70;

/* Create an owner-linked sprite effect at the supplied position with a vertical offset. */
void create_an_owner_linked_sprite_effect_position_vertical_offset(S_81977D08_4 *owner, S_81977D08_3 *position)
{
    ObjectPosition *effect_pos;
    SpriteFrameState *sprite;
    S_81977D08_0 *effect;

    effect = allocate_list_node(0x212, ((s32 *)&scene_object_list_anchor.next));
    if (effect != NULL) {
        void *sprite_data = &D_800DEB70;

        effect->unk_10 = &D_8002548C;
        {
            s32 color = 0x80;

            sprite = effect->unk_0C;
            {
                s32 zero = 0;

                effect->unk_20 = owner;
                sprite->color.c.b = color;
                sprite->color.c.g = color;
                sprite->color.c.r = color;
                select_record_entry_and_value(sprite, sprite_data, zero);
            }
        }
        sprite->scale_y = 0x1800;
        sprite->scale_x = 0x1800;
        sprite->flags = sprite->flags | 0xC;
        sprite->tpage_abr = sprite->tpage_abr | 0x20;
        effect_pos = effect->unk_08;
        effect_pos->x.v = position->unk_00;
        effect_pos->y.v = position->unk_04;
        effect_pos->z.v = position->unk_08 -
            (((u8 *)((s32 *)entity_height_offsets))[((S_81977D08_5 *)(owner->unk_14))->unk_13] >> 1 << 16);
        register_node(effect, project_sprite_chain);
    }
}
