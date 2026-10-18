#include "common.h"

#include "common.h"

void func_800253A0(s32 owner, s32 context, s32 mode, s32 item_id);
void drain_cd_command_queue(void);
void func_8004B634(void);

/* Prepares shared state and initializes an item in mode 1. */
void func_8004B660(s32 context, s32 user_data, s32 item) {
    func_8004B634();
    drain_cd_command_queue();
    func_800253A0(context, user_data, 1, item);
}
