#include "common.h"
#include "shared/entity.h"
#include "town/player/position.h"


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 resident_globals_page[];
s32 call_the_same_context_both_processing_routines(s32, ObjectPosition *);             /* extern */
s32 handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(s32, ObjectPosition *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */             /* extern */
s32 initialize_object_and_maybe_play_sound(void *, s32, ObjectPosition *, s32); /* extern */


typedef struct S_7FFFE188_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_7FFFE188_1;   /* arg0 in follow_target_until_timeout */

/* Updates motion toward the target and handles countdown expiration. */
void follow_target_until_timeout(S_7FFFE188_1 *entity, s32 context, ObjectPosition *motion, s32 completion_data) {
    s32 *target_pos;
    u16 remaining_ticks;

    target_pos = resident_globals_page + 0xDE0;
    motion->velocity_x = (s32) ((s32) (target_pos[0] - motion->x.v) / 2);
    motion->velocity_y = (s32) ((s32) (target_pos[1] - motion->y.v) / 2);
    add_motion_deltas_to_position(motion);
    call_the_same_context_both_processing_routines(context, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(context, motion);
    remaining_ticks = entity->unk_6C - 1;
    entity->unk_6C = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_object_and_maybe_play_sound(entity, context, motion, completion_data);
    }
}
