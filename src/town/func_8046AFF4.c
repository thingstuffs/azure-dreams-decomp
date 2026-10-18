#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


typedef s32 (*Callback)(s32);


typedef struct S_8001BFF4_1 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8001BFF4_1;   /* arg0 in store_mode_2_selection_in_entry */

typedef struct S_8001BFF4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001BFF4_3;   /* (u8 *)((S_8001BFF4_1 *)arg0)->unk_10 + arg1 * 0x10 in store_mode_2_selection_in_entry */


extern s32 check_event_value_in_list(s32);
extern s32 build_selected_entry_output(s32);
extern s32 build_entry_list(s32);

/* Updates the indexed entry from the current selection in mode 2. */
s32 store_mode_2_selection_in_entry(S_8001BFF4_1 *context, s32 entry_index) {
    u8 mode;

    mode = D_8001E950->unk_05;
    if (mode == 2) {
        if (((Callback)D_80016000->unk_20->callback_2D4)(0) == mode) {
            if (check_event_value_in_list(D_8001E950->unk_04) != 0) {
                ((S_8001BFF4_3 *)((u8 *)context->unk_10 + entry_index * 0x10))->unk_08 =
                    build_selected_entry_output(D_8001E950->unk_04);
                return 0;
            } else {
                ((S_8001BFF4_3 *)((u8 *)context->unk_10 + entry_index * 0x10))->unk_08 =
                    build_selected_entry_output(0);
                return 0;
            }
        } else {
            s32 selection;

            if (check_event_value_in_list(D_8001E950->unk_04) != 0) {
                selection = D_8001E950->unk_04;
            } else {
                selection = 0;
            }
            ((S_8001BFF4_3 *)((u8 *)context->unk_10 + entry_index * 0x10))->unk_08 =
                build_entry_list(selection);
            return 0;
        }
    }
    return 1;
}
