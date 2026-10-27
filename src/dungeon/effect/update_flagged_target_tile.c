#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800B2FAC_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800B2FAC_0;   /* arg2 in update_flagged_target_tile */

typedef struct S_800B2FAC_1_pre {
    u16 unk_00;
} S_800B2FAC_1_pre;   /* the 0x2 bytes before arg3 in update_flagged_target_tile, addressed as arg3[-1] */

struct EntityLinkNode;
void unlink_entity_node(struct EntityLinkNode *node);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);             /* extern */
s32 distribute_experience_awards();                      /* extern */
void * detach_record_and_update_slot_state(void *record);                      /* extern */

/* Update a flagged target and its tile state, then mark it dirty. */
void update_flagged_target_tile(void *unused_0, void *unused_1, void *source, ActorRecord *target) {
    void *target_body;
    s32 update_mask;
    s32 target_flags;
    u8 tile_x;
    u8 tile_y;

    target_body = target;
    if (((S_800B2FAC_0 *)source)->unk_14 & 0xE000) {
        if (((s32)g_dungeon_status.pending_display_owner) == (target_body - 0x20)) {
            g_dungeon_status.pending_display_owner = ((s32)g_dungeon_status.pending_display_owner) & 0x7FFFFFFF;
        }
        distribute_experience_awards(target);
        detach_record_and_update_slot_state(target);
        target_flags = target->flags1C;
        tile_x = ((S_800B2FAC_0 *)source)->unk_24;
        tile_y = ((S_800B2FAC_0 *)source)->unk_25;
        update_mask = 0x3000;
        if (target_flags & 0x2000) {
            update_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, update_mask);
        unlink_entity_node(target_body);
        (*(u16 *)((u8 *)target + -2)) = (u16) (((S_800B2FAC_1_pre *)target)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
