#include "common.h"

extern u8 D_800CF828[];
extern u8 D_800CF838[];

s32 func_8008B2E4(void *);
s32 func_8008B3AC(s32);
void func_8008B49C(s32);

/* reserve_twch_load: reserve a town character load in an available character_slot and process it. */
void reserve_twch_load(s32 character_id) {
    register s32 i ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    void **character_slot;
    u8 *character_table;
    u8 *reservation_slot;

    i = 0;
    character_table = D_800CF838;
    character_slot = (void **)(character_table + (character_id * 4));
    if (func_8008B2E4(*character_slot) == 0) {
        i = 0;
    } else {
        i = func_8008B3AC(i);
        if (i >= 0) {
            reservation_slot = D_800CF828;
            reservation_slot = (u8 *)(i + (s32)reservation_slot);
            *reservation_slot = character_id;
            func_8008B49C(i);
            return;
        }
        i = 0;
    }

    {
        u8 *free_slot;
        u8 *reservations;

        reservations = D_800CF828;
        free_slot = (u8 *)(i + (s32)reservations);
        do {
            if (*free_slot == 0) {
                *free_slot = character_id;
                ((u8 *)((s32)reservations + i))[1] = 0;
                func_8008B49C(i);
                return;
            }
            i++;
            free_slot = (u8 *)(i + (s32)reservations);
        } while (i < 15);
    }
}
