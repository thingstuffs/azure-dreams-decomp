#include "common.h"
#include "engine/cd.h"
#include "engine/item.h"
#include "slus.h"

extern void allocate_item_without_data_override(void *a0, void *a1, s32 a2, void *a3);

/* Submits and drains CD task 6, then allocates the item with mode 2 and the supplied data pointers. */
void open_view_secondary(void *first_ptr, void *second_ptr, void *last_ptr)
{
    submit_global_cd_command_six();
    drain_cd_command_queue();
    allocate_item_without_data_override(first_ptr, second_ptr, 2, last_ptr);
}
