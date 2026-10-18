#include "modules/dungeon_town_map.h"

void process_pending_resource_load(void)
{
    s32 entry_result;
    s32 *entry_table;

    if (D_800CF874[0] != 0) {
        func_80067014(0);
        entry_table = &D_800CF838[15];
        entry_result = func_80047E78(entry_table[D_800CF874[0]]);
        D_80081458[0] = entry_result;
        if (D_800CF874[0] == 1) {
            D_800CF874[0] = 0;
            return;
        }
        D_800CF874[0] = 1;
    }
}
