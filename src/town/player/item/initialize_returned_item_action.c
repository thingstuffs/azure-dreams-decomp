#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "town/player/item.h"



extern u8 D_80093458[];


typedef struct S_800947CC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800947CC_1;   /* arg1 in initialize_returned_item_action */

/* Initialize an object with its handler, two settings, and a state value of 20. */
void initialize_returned_item_action(Rec_func_80094268_arg0 *object, S_800947CC_1 *settings, void *ptr2) {
    u16 secondSetting;
    s32 *handler;

    call_the_handler_selects_nonzero_entry(type_three_action_handler_table, object, ptr2);
    object->unk_30 = (u16) settings->unk_02;
    handler = (s32 *) D_80093458;
    secondSetting = settings->unk_06;
    object->unk_00.as_pm = handler;
    object->unk_0A.as_s16 = 0x14;
    object->unk_32 = secondSetting;
}
