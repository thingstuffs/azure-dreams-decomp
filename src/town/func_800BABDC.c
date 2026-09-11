#include "common.h"

#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef unsigned long uptr;
#endif

extern void func_800B7B48();
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];

/* Processes populated entity entries and sets their state field to 1. */
void func_800B833C(void)
{
    s32 entry_index = 0;
    u8 *entities = D_800D2644;
    u8 *record = D_800D2EA4;
    u8 *ram_page = (u8 *)0x80010000;
    u8 entity_id;

    do {
        entity_id = ram_page[(entry_index * 2) + 0x33A4];
        if (entity_id != 0) {
            s8 state_value;
            s16 *entity_state;

            func_800B7B48(record[0], record[1],
                          *(u8 *)((uptr)(entity_id << 5) + (uptr)entities));
            entity_id = ram_page[(entry_index * 2) + 0x33A4];
            state_value = 1;
            entity_state = (s16 *)((uptr)(entity_id << 5) + (uptr)entities + 0xA);
            *entity_state = state_value;
        }
        record += 8;
        entry_index++;
    } while (entry_index < 0x21);
}
