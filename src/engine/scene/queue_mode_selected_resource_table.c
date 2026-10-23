#include "common.h"

#include "common.h"
#include "engine/scene.h"
#include "slus.h"
#include "slus/data.h"

extern u8 runtime_dispatch_mode_alias[9];

/*
 * Queues the secondary resource table in dispatch mode 2 and the primary table in other modes as
 * CD task 6.
 */
void queue_mode_selected_resource_table(void)
{
    void *table = &primary_mode_resource_table;

    if (runtime_dispatch_mode_alias[0] == 2) {
        table = &secondary_mode_resource_table;
    }
    Control_CD(6, table, 0);
}
