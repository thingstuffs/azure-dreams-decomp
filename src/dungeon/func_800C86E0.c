#include "modules/trap_effects_candidate.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"











/* Add amount to active entries at the given coordinates in both arrays. */
void func_800CDE40(s16 x, s16 y, s32 amount)
{
    s32 entry_index;
    s32 first_x;
    s32 first_y;
    s32 second_x;
    s32 second_y;
    DungeonItemEntry *first_active;
    ActiveEntry *second_active;
    FirstEntry *first_entry;
    SecondEntry *second_entry;

    entry_index = 0;
    first_x = x;
    first_y = y;
    do {
        first_entry = &D_800E36C8[entry_index];
        first_active = &D_800E3548[entry_index];
        if (first_active->kind != 0 &&
            first_entry->x == first_x &&
            first_entry->y == first_y) {
            first_entry->value += amount;
        }
        entry_index++;
    } while (entry_index < 64);

    entry_index = 0;
    second_x = x;
    second_y = y;
    do {
        second_active = &D_800E3648[entry_index];
        second_entry = &D_800E39C8[entry_index];
        if (second_active->active != 0 &&
            second_entry->x == second_x &&
            second_entry->y == second_y) {
            second_entry->value += amount;
        }
        entry_index++;
    } while (entry_index < 32);
}
