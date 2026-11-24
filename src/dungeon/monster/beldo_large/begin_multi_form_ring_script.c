#include "common.h"
#include "shared/game_state.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/monster/beldo_large_data.h"
#include "dungeon/data.h"

typedef struct S_8016EE8C_1 {
    u8 pad_00[0x296C];
    s32 unk_296C;
} S_8016EE8C_1;   /* page_800e in begin_multi_form_ring_script */


typedef struct S_8016EE8C_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8016EE8C_4;



void unlink_entity_node();                         /* extern */
extern u8 *D_80173C94[];
extern u8 *D_80173D5C;

/*
 * Starts the multi-form ring script: resets the shared state and flags, unlinks the actors held in
 * the two ring slots, then creates the segment ring.
 */
void begin_multi_form_ring_script(void) {
    s32 object_data;
    s32 slot_offset;
    s32 slot_index;
    BeldoScriptControl *active_data;
    GameState *page_8001;
    S_8016EE8C_1 *page_800e;
    S_8016EE8C_4 *object_header;

    slot_index = 0;
    page_8001 = GAME_STATE;
    page_800e = (void *)0x800E0000;
    active_data = NODE_BODY(beldo_actor_nodes);
    active_data->script_active = 1;
    page_8001->log.head.cursor = 0;
    page_8001->log.head.repeat = 0;
    page_8001->log.head.length = 0;
    g_dungeon_status.active_actor = 0;
    beldo_script_timer = 0;
    page_800e->unk_296C = (s32) (page_800e->unk_296C | 0x08000000);
    GAME_STATE->log.head.flags = (u16) ((GAME_STATE->log.head.flags | 9) & 0xFFEF);
    GAME_STATE->log.data = D_80173C94[0];
    encounter_script_cursor = D_80173D5C;
    active_data->script_index = 0;
    do {
        slot_offset = slot_index * 4;
        object_data = ((ActorRecord *)((slot_offset + ((EntityRec *)(((s32 *)&dungeon_actor_ring_anchor)))->x.v)))->unk_AC.value;
        if (object_data != 0) {
            unlink_entity_node(object_data);
            object_header = (S_8016EE8C_4 *)(((ActorRecord *)((slot_offset + ((EntityRec *)(((s32 *)&dungeon_actor_ring_anchor)))->x.v)))->unk_AC.value
            - 0x20);
            object_header->unk_10 = (s32) (object_header->unk_10 | 0x80000000);
        }
        slot_index += 1;
    } while (slot_index < 2);
    create_multi_form_segment_ring(&view_reference_entity.x.v);
}
