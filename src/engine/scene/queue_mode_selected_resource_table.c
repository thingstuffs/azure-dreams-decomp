#include "common.h"

#include "common.h"

extern void Control_CD(s32, void *, s32);
extern s32 primary_mode_resource_table;
extern s32 secondary_mode_resource_table;
extern u8 runtime_dispatch_mode_alias[9];

/* Select a table based on D_80082E6A[0] and pass it to Control_CD. */
void queue_mode_selected_resource_table(void)
{
    void *table = &primary_mode_resource_table;

    if (runtime_dispatch_mode_alias[0] == 2) {
        table = &secondary_mode_resource_table;
    }
    Control_CD(6, table, 0);
}
