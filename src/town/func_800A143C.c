#include "common.h"

typedef s32 M2C_UNK;

extern void update_the_data_set_local_global_flags();
extern s32 get_item_chk();

/* Process the item index when available and report success. */
s32 process_the_item_index_available_report_success(s32 context) {
    s32 item_index;

    item_index = get_item_chk();
    if (item_index == -1) {
        return 0;
    }
    update_the_data_set_local_global_flags(context, item_index);
    return 1;
}
