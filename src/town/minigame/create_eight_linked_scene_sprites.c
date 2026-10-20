#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_payload.h"

   /* (u8 *)arg0 + count * 4 in create_eight_linked_scene_sprites */

typedef struct S_8002082C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8002082C_1;   /* object in create_eight_linked_scene_sprites */

typedef struct S_8002082C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_8002082C_2;   /* image in create_eight_linked_scene_sprites */

typedef struct S_8002082C_3 {
    u8 pad_00[0x34];
    s16 unk_34;
} S_8002082C_3;   /* arg0 in create_eight_linked_scene_sprites */

extern s32 func_8003DB94();
extern void *allocate_list_node();
extern s32 register_node();

typedef struct {
    u16 field_0;
    u16 field_2;
} D_80026DE0Entry;

extern s32 D_80022698[3];
extern D_80026DE0Entry D_80026DE0[3][8];
extern s32 D_800F29B4[3];

/* Create and initialize eight child objects using the owner's image table selection. */
void create_eight_linked_scene_sprites(void *owner) {
    s32 slot_offset;
    s32 slot_index;
    SpriteFrameState *object_data;
    S_8002082C_1 *object;
    S_8002082C_2 *image;

    slot_index = 7;
    do {
        object = allocate_list_node(0x136, ((s32 *)(&D_80083498)));
        ((ObjectPayloadView *)((u8 *)owner + slot_index * 4))->unk_08 = object;
        slot_offset = slot_index * 4;
        if (object != 0) {
            object->unk_10 = D_80022698;
            register_node(object, project_sprite_chain);
            object->unk_20 = owner;
            image = object->unk_08;
            object_data = object->unk_0C;
            image->unk_02 = D_80026DE0[((S_8002082C_3 *)owner)->unk_34][slot_index].field_0;
            image->unk_06 = D_80026DE0[((S_8002082C_3 *)owner)->unk_34][slot_index].field_2;
            object_data->tpage_abr = 0x60;
            object_data->color.word = 0;
            object_data->scale_y = 0x1000;
            object_data->scale_x = 0x1000;
            object_data->flags |= 0xC;
            func_8003DB94(object_data, D_800F29B4, 0);
        }
        slot_index--;
    } while (slot_index >= 0);
}

/* MECHANISM: Two-u16 table records force one D_80026DE0 base and lhu offsets 0/2.
   Array decay holds D_80022698 in s6; count-indexed slot access lets strength reduction
   place s3 after both held bases, reproducing the -0x30 frame, save order, and loop CFG. */
