#include "shared/dungeon_item_entries.h"
#include "common.h"

typedef struct {
    u8 pad0;
    u8 active;
    u8 pad2[2];
} ActiveEntry;

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 value;
    u8 pad6[6];
} FirstEntry;

typedef struct {
    u8 pad0[6];
    u8 x;
    u8 y;
    u8 pad8[10];
    s16 value;
    u8 pad20[4];
} SecondEntry;

extern ActiveEntry D_800E3648[32];
extern FirstEntry D_800E36C8[64];
extern SecondEntry D_800E39C8[32];

/* Sets the value of all active entries at the given coordinates in both tables. */
void func_800CDF40(s16 x, s16 y, s16 value) {
    FirstEntry *first_entry;
    DungeonItemEntry *first_status;
    SecondEntry *second_entry;
    ActiveEntry *second_status;
    s32 first_index;
    s32 first_x;
    s32 first_y;
    s32 second_x;
    s32 second_y;

    first_index = 0;
    first_x = x;
    first_y = y;
    do {
        first_entry = &D_800E36C8[first_index];
        first_status = &D_800E3548[first_index];
        if (first_status->kind != 0 && first_entry->x == first_x && first_entry->y == first_y) {
            first_entry->value = value;
        }
        first_index++;
    } while (first_index < 64);

    first_index = 0;
    second_x = x;
    second_y = y;
    do {
        second_status = &D_800E3648[first_index];
        second_entry = &D_800E39C8[first_index];
        if (second_status->active != 0 && second_entry->x == second_x && second_entry->y == second_y) {
            second_entry->value = value;
        }
        first_index++;
    } while (first_index < 32);
}

/* MECHANISM: Frameless leaf with exact 12-byte/24-byte record strides and narrow stores.
   Removing inherited keeps restored raw arg holds in t1/t2 and the exact 58-word shape.
   A guarded t0 pin for the second counter closed the final a1/a3/t0 role rotation. */
