#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern u8 D_80016524[];
extern u8 D_80016578[];
extern u8 D_800165CC[];
extern u8 D_80016620[];
extern u8 D_80016674[];
extern void *D_80017C7C;

/* Stores one of five data tables in D_80017C7C chosen by the scene root's entry index. */
void select_scene_data_table_by_entry_index(void) {
    switch (town_scene_root->entry_index) {
    case 37:
        D_80017C7C = D_80016524;
        return;
    case 38:
        D_80017C7C = D_80016578;
        return;
    case 39:
        D_80017C7C = D_800165CC;
        return;
    case 40:
        D_80017C7C = D_80016620;
        return;
    default:
        D_80017C7C = D_80016674;
        return;
    }
}
