#include "common.h"
#include "town/map.h"

typedef unsigned long uptr;

extern void func_800B7B48(s16 x, s16 y, u8 entry_index);
extern u8 town_building_records[];
extern u8 town_building_slot_rectangles[];

/* Processes populated entity entries and sets their state field to 1. */
void mark_populated_building_entities(void)
{
    s32 entry_index = 0;
    u8 *entities = town_building_records;
    u8 *record = town_building_slot_rectangles;
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
