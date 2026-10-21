#include "common.h"

#include "common.h"
#include "engine/cd.h"
#include "engine/item.h"
#include "slus.h"

void allocate_item_without_data_override(s32 owner, s32 context, s32 mode, s32 item_id);

/* Prepares shared state and initializes an item in mode 1. */
void open_view_primary(s32 context, s32 user_data, s32 item) {
    submit_global_cd_command_six();
    drain_cd_command_queue();
    allocate_item_without_data_override(context, user_data, 1, item);
}
