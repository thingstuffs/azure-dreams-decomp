#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/monster/beldo.h"


typedef struct S_80170B50_2 {
    void * unk_00;
    u8 pad_04[0x3A];
    u16 unk_3E;
} S_80170B50_2;   /* arg0 in create_attached_sprite_with_offset; pointer addresses record offset 0x14 */

   /* arg1 in create_attached_sprite_with_offset */

typedef struct S_80170B50_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80170B50_6;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Copy4;

extern void *beldo_object_callback[];
extern u8 beldo_frame_set_3[8];
extern s32 resolve_record_orientation_or_fallback();
extern void *allocate_list_node();
extern s32 register_node();
extern void select_sprite_entry();

/* Creates an attached sprite object with copied appearance and an optional position offset. */
void create_attached_sprite_with_offset(void *owner_data, MovingPosition *base_position, SpriteFrameState *sprite_template, s16 offset_id) {
    u32 sprite_flags;
    u16 sprite_height;
    s16 saved_offset_id;
    S_80170B50_6 *owner_model;
    ObjectPosition *position;
    SpriteFrameState *sprite;
    void *object_data;
    ObjectNodeHeader *object;
    void *copy_dst;
    void *copy_src;

    saved_offset_id = offset_id;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != NULL) {
        object_data = ((void *)object) + 0x20;
        object->update_callback = beldo_object_callback;
        ((AttachedSpriteWithOffsetBody *)object_data)->unk_B6 = offset_id;
        ((AttachedSpriteWithOffsetBody *)object_data)->unk_AC.integer = (s32) (owner_data - 0x20);
        ((AttachedSpriteWithOffsetBody *)object_data)->unk_94 = (u16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E;
        copy_src = sprite_template;
        ((AttachedSpriteWithOffsetBody *)object_data)->unk_2A = (u16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E;
        sprite = object->sprite;
        copy_dst = sprite;
        do {
            *(Copy4 *)copy_dst = *(Copy4 *)copy_src;
            copy_src += 0x10;
            copy_dst += 0x10;
        } while (copy_src != (((void *)sprite_template) + 0x30));
        register_node(object, project_sprite_chain, copy_dst, copy_src);
        sprite->frameTable = &beldo_frame_set_3;
        select_sprite_entry(sprite, *((u8 *)&beldo_frame_set_3 + ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle
            + (s16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E + 0x100) >> 9) & 7))), 0);
        sprite_flags = sprite->flags | 0xC;
        sprite->flags = sprite_flags;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0x80;
        position = object->position;
        position->x.w.i = (u16) base_position->x;
        position->y.w.i = (u16) base_position->y;
        position->z.w.i = (u16) base_position->z;
        owner_model = ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_00;
        if (resolve_record_orientation_or_fallback(owner_model->unk_08, owner_model, object_data + 0xB0, saved_offset_id) != 0) {
            position->x.w.i = (u16) ((u16)position->x.w.i + ((AttachedSpriteWithOffsetBody *)object_data)->unk_B0.u);
            position->y.w.i = (u16) ((u16)position->y.w.i + ((AttachedSpriteWithOffsetBody *)object_data)->unk_B2.u);
            position->z.w.i = (u16) ((u16)position->z.w.i + ((AttachedSpriteWithOffsetBody *)object_data)->unk_B4.u);
        }
        sprite->scale_x = (u16) sprite_template->scale_x;
        sprite_height = (u16) sprite_template->scale_y;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = sprite_height;
    }
}
