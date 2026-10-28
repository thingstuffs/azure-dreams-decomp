#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_8009A3A4_1 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A3A4_1;   /* call_arg0 in run_player_indexed_handler */

typedef struct S_8009A3A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A3A4_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in run_player_indexed_handler */


extern s32 call_the_handler_selects_nonzero_entry();
extern s32 initialize_record_with_handler_table();

/* Run the object's indexed handler, clear its table flag, and reset its state. */
void run_player_indexed_handler(Rec_func_80094268_arg0 *object, s32 position, s32 context) {
    call_the_handler_selects_nonzero_entry(((S_8009A3A4_2 *)(object->unk_44))->unk_14, object, context);
    *(((u8 *)object_index_slots) + (object->unk_40 * 8)) = 0;
    initialize_record_with_handler_table(object, position, context);
}
