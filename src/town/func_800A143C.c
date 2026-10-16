#include "common.h"

typedef s32 M2C_UNK;

extern void townUpdateTheDataSetLocalGlobalFlags();
extern s32 get_item_chk();

/* Process the item index when available and report success. */
s32 townProcessTheItemIndexAvailableReportSuccess(s32 context) {
    s32 item_index;

    item_index = get_item_chk();
    if (item_index == -1) {
        return 0;
    }
    townUpdateTheDataSetLocalGlobalFlags(context, item_index);
    return 1;
}
