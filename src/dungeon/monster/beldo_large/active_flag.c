/* Encounter activity checks and scripted object creation. */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_80173140_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_80173140_0;

typedef struct S_80173140_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x72];
    s16 unk_92;
    u8 pad_94[0xC];
    s32 unk_A0;
} S_80173140_1;

typedef struct S_80173140_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173140_2;

typedef struct S_80173140_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173140_5;   /* ((Rec_D_800E3D7C *)(&D_80083498))->unk_08.at00_pv.v in create_scripted_encounter_object */

void *allocate_list_node();            /* extern */
s32 register_node();           /* extern */
void select_sprite_entry();         /* extern */
void unlink_entity_node();                      /* extern */
void update_map_cell_flags_with_item_limit();             /* extern */
void initialize_actor_sprite_and_animation(void *, void *, void *, s32); /* extern */
extern void advance_linked_actor_motion_script(void *state_in, void *motion_in, void *sprite_in);
extern M2C_UNK D_80173DA4;
extern void *beldo_script_node;

static __inline__ u16 active_flag(u32 value)
{
    return value & 0x2000;
}

/* Create and initialize a dungeon object and store it as the active object. */
void create_scripted_encounter_object(void) {
    s32 masked_flags;
    s32 flag_mask;
    s32 state_flags;
    s16 initial_offset;
    s32 cell_x;
    s32 cell_y;
    void *object;
    s32 cell_mask;
    s32 origin_x;
    s32 origin_y;
    void *object_attrs;
    SpriteFrameState *sprite;
    void *state;
    S_80173140_1 *st;

    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        state = object + 0x20;
        st = (S_80173140_1 *)state;
        ((S_80173140_0 *)object)->unk_10 = &advance_linked_actor_motion_script;
        st->unk_13 = MONSTER_KEWNE;
        register_node(object, project_sprite_chain);
        object_attrs = ((S_80173140_0 *)object)->unk_08;
        ((S_80173140_2 *)object_attrs)->unk_0A =
            (u16) ((S_80173140_5 *)((*(void * *)&((EntityRec *)(((s32 *)&scene_object_list_anchor.next)))->z)))->unk_0A;
        sprite = ((S_80173140_0 *)object)->unk_0C;
        origin_x = reference_tile_object.tile_position.parts.tile_x;
        sprite->unk_24 = (u8) (origin_x - 1);
        origin_y = reference_tile_object.tile_position.parts.tile_y;
        sprite->frameTable = &D_80173DA4;
        sprite->unk_25 = (u8) (origin_y + 7);
        initialize_actor_sprite_and_animation(object, object_attrs, sprite, 0);
        (*(s16 *)((u8 *)st + 0x2A)) = 0xC00;
        select_sprite_entry(sprite, ((u8 *) sprite->frameTable)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + 0xD00)
            >> 9) & 7], 0);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        flag_mask = 0x40000;
        state_flags = st->unk_1C | flag_mask;
        st->unk_1C = state_flags;
        st->unk_A0 = 0;
        masked_flags = active_flag(st->unk_1C);
        initial_offset = -0x20;
        st->unk_92 = initial_offset;
        cell_x = sprite->unk_24;
        cell_y = sprite->unk_25;
        cell_mask = 0x3000;
        if (masked_flags) {
            cell_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(cell_x, cell_y, cell_mask);
        unlink_entity_node(st);
        beldo_script_node = object;
        ((S_80173140_0 *)object)->unk_10 = (s32 *) ((s32) ((S_80173140_0 *)object)->unk_10 | 0x80000000);
    }
}
