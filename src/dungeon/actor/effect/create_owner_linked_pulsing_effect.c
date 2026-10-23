
struct ObjectNodeHeader;
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_800287A4.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "dungeon/actor/effect.h"

typedef struct S_800CB82C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800CB82C_2;   /* arg0 in create_owner_linked_pulsing_effect */

typedef struct S_800CB82C_4 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[0x9];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
    u8 pad_8A[0x6];
    s32 unk_90;
} S_800CB82C_4;

typedef struct S_800CB82C_5 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800CB82C_5;   /* &D_800E3CC8 in create_owner_linked_pulsing_effect */

   /* the 0x14 bytes before arg2 in create_owner_linked_pulsing_effect, addressed as arg2[-1] */

/* cfail-repair: tf7-phase1-cache-v3 */
s32 register_node();                /* extern */
void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *entry);                      /* extern */
s32 create_actor_spell_effect(); /* extern */
extern void D_800CB600();
extern M2C_UNK D_800E03BC;
extern u8 active_spell_parameters;

/* Create and register an object using the spawn position, source state, and owner. */
void *create_owner_linked_pulsing_effect(void *spawn_pos, EntityRec *source_state, void *owner) {
    u16 object_flags;
    s32 global_flags;
    SpriteFrameState *map_data;
    void *object_state;
    MovingPosition *position;
    ObjectNodeHeader *object;
    MovingTile *owner_map;
    u16 object_count;

    object = allocate_flagged_object_node(0x102);
    if (object != NULL) {
        object->update_callback = &D_800CB600;
        register_node(object, project_sprite_chain);
        position = object->position;
        position->x = (u16) ((S_800CB82C_2 *)spawn_pos)->unk_02;
        position->y = (u16) ((S_800CB82C_2 *)spawn_pos)->unk_06;
        position->z = (u16) ((S_800CB82C_2 *)spawn_pos)->unk_08.at02.v;
        map_data = object->sprite;
        map_data->source = &D_800E03BC;
        map_data->flags = (u16) (map_data->flags | 0xC);
        map_data->tile_x = (s8) ((u16) position->x >> 6);
        map_data->tile_y = (s8) ((u16) position->y >> 6);
        object_state = ((void *)object) + 0x20;
        (*(s16 *)((u8 *)object_state + 0x96)) = 0x10;
        ((S_800CB82C_4 *)object_state)->unk_08 = (u8) active_spell_parameters;
        ((S_800CB82C_4 *)object_state)->unk_09 = (u8) ((S_800CB82C_5 *)(&active_spell_parameters))->unk_01;
        ((S_800CB82C_4 *)object_state)->unk_60 = owner;
        owner_map = ((SpriteLinkPrefixView *)owner)[-1].sprite;
        ((S_800CB82C_4 *)object_state)->unk_72 = (u8) owner_map->tile_x;
        ((S_800CB82C_4 *)object_state)->unk_73 = (u8) owner_map->tile_y;
        ((S_800CB82C_4 *)object_state)->unk_88 = (u16) ((u16)source_state->unk_88);
        ((S_800CB82C_4 *)object_state)->unk_13 = 0xFF;
        ((S_800CB82C_4 *)object_state)->unk_14 = (s32) source_state->flags14;
        ((S_800CB82C_4 *)object_state)->unk_1C = (s32) source_state->flags1C;
        ((S_800CB82C_4 *)object_state)->unk_2A = (s16) (((Rec_D_800287A4 *)owner)->unk_2A - 0x800);
        ((S_800CB82C_4 *)object_state)->unk_90 = (s32) ((S_800CB82C_2 *)spawn_pos)->unk_08.at00.v;
        if (create_actor_spell_effect(object_state, ((void *)object) + 0x28, 0, ((void *)object) + 0xB8) == 0) {
            object_flags = object->flags | 0x8000;
            global_flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            object->flags = object_flags;
            object_flag_block.flags = global_flags;
            return NULL;
        }
        clear_entry_flag_and_link_owner(object);
        object_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
        object_count = (u16) (object_count + 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = object_count;
    }
    return object;
}
