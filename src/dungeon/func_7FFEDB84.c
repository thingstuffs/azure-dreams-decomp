#include "modules/dungeon_town_load.h"

s32 resource_value_table_contains(s32 value) {
    s32 i = 0;

    while (D_800CF85C[i] != 0) {
        if (value == D_800CF85C[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
