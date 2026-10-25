#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/node.h"



extern s32 actor_fade_draw_address;


/* Resets object state, runs object setup, and updates property and status flags. */
void initialize_actor_object_action(void *object_state, void *unused_context, Rec_D_80082E80 *properties, EntityRec *status) {
    void *object;

    ((Rec_func_800A9E70_arg0 *)object_state)->unk_9A.as_s8 = 0x13;
    ((Rec_func_800A9E70_arg0 *)object_state)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)object_state)->unk_8C = 0;
    properties->unk_14.at00_u16.v = (u16)(properties->unk_14.at00_u16.v & 0xF7FF);
    ((Rec_func_800A9E70_arg0 *)object_state)->unk_96.as_s16 = 0;
    object = object_state - 0x20;
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    unlink_node(object);
    register_node(object, &actor_fade_draw_address);
    properties->unk_0C.at03_s8.v = 0;
    properties->unk_0C.at02_s8.v = 0;
    properties->unk_0C.at01_s8.v = 0;
    properties->unk_0C.at00_s8.v = 0;
    properties->unk_10.as_s16 = 0x20;
    properties->unk_12.at00_u16.v = (u16)(properties->unk_12.at00_u16.v - 0x80);
    status->flags1C = (s32)(status->flags1C | 0x10000000);
}
