#include "common.h"

extern void submit_global_cd_command_six(void);
extern void drain_cd_command_queue(void);
extern void allocate_item_without_data_override(void *a0, void *a1, s32 a2, void *a3);

/* Calls func_8004B634 and drain_cd_command_queue, then forwards the pointers to func_800253A0 with mode 3. */
void open_view_alternate(void *first_data, void *second_data, void *extra_data)
{
    submit_global_cd_command_six();
    drain_cd_command_queue();
    allocate_item_without_data_override(first_data, second_data, 3, extra_data);
}
