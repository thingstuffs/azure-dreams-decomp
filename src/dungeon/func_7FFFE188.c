#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80080000[];
M2C_UNK call_the_same_context_both_processing_routines();             /* extern */
M2C_UNK handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis();             /* extern */
M2C_UNK add_motion_deltas_to_position();                      /* extern */
M2C_UNK initialize_object_and_maybe_play_sound(); /* extern */


typedef struct S_7FFFE188_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_7FFFE188_1;   /* arg0 in func_7FFFE188 */

/* Updates motion toward the target and handles countdown expiration. */
void func_7FFFE188(S_7FFFE188_1 *entity, M2C_UNK context, EntityRec *motion, M2C_UNK completion_data) {
    s32 *target_pos;
    u16 remaining_ticks;

    target_pos = D_80080000 + 0xDE0;
    motion->unk_0C = (s32) ((s32) (target_pos[0] - motion->x.v) / 2);
    motion->unk_10 = (s32) ((s32) (target_pos[1] - motion->y.v) / 2);
    add_motion_deltas_to_position(motion);
    call_the_same_context_both_processing_routines(context, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(context, motion);
    remaining_ticks = entity->unk_6C - 1;
    entity->unk_6C = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_object_and_maybe_play_sound(entity, context, motion, completion_data);
    }
}
