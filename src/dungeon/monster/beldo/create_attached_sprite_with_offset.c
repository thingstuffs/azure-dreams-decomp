#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80170B50_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void ** unk_10;
} S_80170B50_0;

typedef struct S_80170B50_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u8 pad_96[0x16];
    s32 unk_AC;
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    s16 unk_B6;
} S_80170B50_1;

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

typedef struct S_80170B50_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80170B50_7;   /* arg2 in create_attached_sprite_with_offset */

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Copy4;

extern void *D_80170898[];
extern M2C_UNK D_80173EB4;
extern s32 resolve_record_orientation_or_fallback();
extern void *allocate_list_node();
extern s32 register_node();
extern M2C_UNK select_sprite_entry();

/* Creates an attached sprite object with copied appearance and an optional position offset. */
void create_attached_sprite_with_offset(void *owner_data, MovingPosition *base_position, void *sprite_template, s16 offset_id) {
    u32 sprite_flags;
    u16 sprite_height;
    s16 saved_offset_id;
    S_80170B50_6 *owner_model;
    MovingPosition *position;
    SpriteFrameState *sprite;
    void *object_data;
    void *object;
    void *copy_dst;
    void *copy_src;

    saved_offset_id = offset_id;
    object = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (object != NULL) {
        object_data = object + 0x20;
        ((S_80170B50_0 *)object)->unk_10 = D_80170898;
        ((S_80170B50_1 *)object_data)->unk_B6 = offset_id;
        ((S_80170B50_1 *)object_data)->unk_AC = (s32) (owner_data - 0x20);
        ((S_80170B50_1 *)object_data)->unk_94 = (u16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E;
        copy_src = sprite_template;
        ((S_80170B50_1 *)object_data)->unk_2A = (u16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E;
        sprite = ((S_80170B50_0 *)object)->unk_0C;
        copy_dst = sprite;
        do {
            *(Copy4 *)copy_dst = *(Copy4 *)copy_src;
            copy_src += 0x10;
            copy_dst += 0x10;
        } while (copy_src != (sprite_template + 0x30));
        register_node(object, project_sprite_chain, copy_dst, copy_src);
        sprite->frameTable = &D_80173EB4;
        select_sprite_entry(sprite, *((u8 *)&D_80173EB4 + ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle
            + (s16) ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_3E + 0x100) >> 9) & 7))), 0);
        sprite_flags = sprite->flags | 0xC;
        sprite->flags = sprite_flags;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0x80;
        position = ((S_80170B50_0 *)object)->unk_08;
        position->unk_02 = (u16) base_position->unk_02;
        position->unk_06 = (u16) base_position->unk_06;
        position->unk_0A = (u16) base_position->unk_0A;
        owner_model = ((S_80170B50_2 *)((u8 *)owner_data - 0x14))->unk_00;
        if (resolve_record_orientation_or_fallback(owner_model->unk_08, owner_model, object_data + 0xB0, saved_offset_id) != 0) {
            position->unk_02 = (u16) (position->unk_02 + ((S_80170B50_1 *)object_data)->unk_B0);
            position->unk_06 = (u16) (position->unk_06 + ((S_80170B50_1 *)object_data)->unk_B2);
            position->unk_0A = (u16) (position->unk_0A + ((S_80170B50_1 *)object_data)->unk_B4);
        }
        sprite->scale_x = (u16) ((S_80170B50_7 *)sprite_template)->unk_1C;
        sprite_height = (u16) ((S_80170B50_7 *)sprite_template)->unk_1E;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = sprite_height;
    }
}
