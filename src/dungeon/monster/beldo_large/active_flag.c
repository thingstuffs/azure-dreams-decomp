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


typedef struct S_80173140_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173140_2;

typedef struct S_80173140_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173140_5;   /* ((Rec_D_800E3D7C *)(&D_80083498))->unk_08.at00_pv.v in create_scripted_encounter_object */

void *allocate_list_node();            /* extern */
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
void select_sprite_entry();         /* extern */
void unlink_entity_node();                      /* extern */
void update_map_cell_flags_with_item_limit();             /* extern */
void initialize_actor_sprite_and_animation(void *, void *, void *, s32); /* extern */
#include "dungeon/monster/beldo_large.h"
extern u8 beldo_large_frame_set_8[16];
extern void *beldo_script_node;

/* Extracts flag 0x2000 from the supplied word. */
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
    ObjectNodeHeader *object;
    s32 cell_mask;
    s32 origin_x;
    s32 origin_y;
    void *object_attrs;
    SpriteFrameState *sprite;
    ActorRecord *state;
    ActorRecord *st;

    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        st = state;
        object->update_callback = &advance_linked_actor_motion_script;
        st->species = MONSTER_KEWNE;
        register_node(object, project_sprite_chain);
        object_attrs = object->position;
        ((S_80173140_2 *)object_attrs)->unk_0A =
            (u16) ((S_80173140_5 *)((*(void **)&((EntityRec *)(((s32 *)&scene_object_list_anchor.next)))->z)))->unk_0A;
        sprite = object->sprite;
        origin_x = reference_tile_object.tile_position.parts.tile_x;
        sprite->tile_x = (u8) (origin_x - 1);
        origin_y = reference_tile_object.tile_position.parts.tile_y;
        sprite->frameTable = &beldo_large_frame_set_8;
        sprite->tile_y = (u8) (origin_y + 7);
        initialize_actor_sprite_and_animation(object, object_attrs, sprite, 0);
        st->facing = 0xC00;
        select_sprite_entry(sprite, ((u8 *) sprite->frameTable)[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + 0xD00)
            >> 9) & 7], 0);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        flag_mask = 0x40000;
        state_flags = st->flags1C | flag_mask;
        st->flags1C = state_flags;
        st->unk_A0.value = 0;
        masked_flags = active_flag(st->flags1C);
        initial_offset = -0x20;
        st->unk_90.parts.high.s = initial_offset;
        cell_x = sprite->tile_x;
        cell_y = sprite->tile_y;
        cell_mask = 0x3000;
        if (masked_flags) {
            cell_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(cell_x, cell_y, cell_mask);
        unlink_entity_node(st);
        beldo_script_node = object;
        object->update_callback = (s32 *) ((s32) *(s32 * *)&object->update_callback | 0x80000000);
    }
}
