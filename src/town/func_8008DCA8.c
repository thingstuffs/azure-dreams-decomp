#include "common.h"

extern u8 D_800CF828[];
extern u8 D_800CF838[];

s32 resource_value_table_contains(void *);
s32 find_slot_for_resource_entry(void);

/* reserve_twch_load: reserve a town character load in an available character_slot and process it. */
void reserve_twch_load(s32 character_id) {
    s32 i;
    s32 found;

    found = resource_value_table_contains(((void **)D_800CF838)[character_id]);
    i = 0;
    if (found != 0) {
        i = find_slot_for_resource_entry();
        if (i >= 0) {
            D_800CF828[i] = character_id;
            return;
        }
        i = 0;
    }

    do {
        if (D_800CF828[i] == 0) {
            D_800CF828[i] = character_id;
            D_800CF828[i + 1] = 0;
            return;
        }
        i++;
    } while (i < 15);
}
