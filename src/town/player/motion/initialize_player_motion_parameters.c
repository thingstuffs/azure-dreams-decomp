#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/player/motion.h"


typedef struct S_8009A344_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_8009A344_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in initialize_player_motion_parameters */


void call_the_handler_selects_nonzero_entry(s32 *entries, Rec_func_80094268_arg0 *record, void *ptr2);
void set_player_travel_timing(void *actor, void *motion, s32 context);



/* Initialize the record from linked data and apply its update parameters. */
void initialize_player_motion_parameters(void *record, s32 update_value, s32 init_context) {
    call_the_handler_selects_nonzero_entry(((S_8009A344_1 *)(((Rec_func_80094268_arg0 *)record)->unk_44))->unk_24, record, init_context);
    set_player_travel_timing(record, update_value, init_context);
}
