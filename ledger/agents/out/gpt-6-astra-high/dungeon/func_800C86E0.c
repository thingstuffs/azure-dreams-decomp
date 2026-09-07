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
    u16 value;
    u8 pad6[6];
} FirstEntry;

typedef struct {
    u8 pad0[6];
    u8 x;
    u8 y;
    u8 pad8[10];
    u16 value;
    u8 pad14[4];
} SecondEntry;

extern ActiveEntry D_800E3548[64];
extern ActiveEntry D_800E3648[32];
extern FirstEntry D_800E36C8[64];
extern SecondEntry D_800E39C8[32];

/* Add amount to active entries at the given coordinates in both arrays. */
void func_800CDE40(s16 x, s16 y, s32 amount)
{
    s32 entry_index;
    s32 first_x;
    s32 first_y;
    s32 second_x;
    s32 second_y;
    ActiveEntry *first_active;
    ActiveEntry *second_active;
    FirstEntry *first_entry;
    SecondEntry *second_entry;

    entry_index = 0;
    first_x = x;
    first_y = y;
    first_entry = D_800E36C8;
    first_active = D_800E3548;
    do {
        if (first_active->active != 0 &&
            first_entry->x == first_x &&
            first_entry->y == first_y) {
            first_entry->value += amount;
        }
        first_entry++;
        entry_index++;
        first_active++;
    } while (entry_index < 64);

    entry_index = 0;
    second_x = x;
    second_y = y;
    second_entry = D_800E39C8;
    second_active = D_800E3648;
    do {
        if (second_active->active != 0 &&
            second_entry->x == second_x &&
            second_entry->y == second_y) {
            second_entry->value += amount;
        }
        second_entry++;
        entry_index++;
        second_active++;
    } while (entry_index < 32);
}
