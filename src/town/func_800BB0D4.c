#include "common.h"

extern s32 func_80033B2C();
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];

/* Checks whether a record can use an entity based on its kind and existing links. */
s32 func_800B8834(s32 record_id, s32 entity_id)
{
    s32 slot_index;
    s32 entity_index;
    s32 record_index;
    s32 match_index;
    u8 record_kind;
    u8 *entity_base;
    u8 *entity;
    u8 *record_base;
    u8 *record;
    u8 *record_link_page;
    u8 *scan_link_page;
    u8 *slot;

    entity_base = D_800D2644;
    entity_index = entity_id & 0xFF;
    entity = entity_base + (entity_index << 5);
    if (func_80033B2C(*(s16 *)(entity + 8)) == 0) {
        goto return_zero;
    }

    record_base = D_800D2EA4;
    record_index = record_id & 0xFF;
    record = record_base + (record_index << 3);
    if (record[2] != entity[4]) {
        return 0;
    }
    if (record[3] != entity[5]) {
        return 0;
    }
    ASM_KEEP(record);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */

    record_link_page = (u8 *)0x80010000;
    if (record_link_page[((record_id & 0xFF) << 1) + 0x33A5] != 0) {
        return 0;
    }

    record_kind = record[4];
    switch (record_kind) {
    case 0:
        goto return_zero;

    case 1:
        if ((entity[3] & 1) == 0) {
            goto return_zero;
        }

        slot_index = 0;
        scan_link_page = (u8 *)0x80010000;
        match_index = entity_index;
loop:
        slot = (u8 *)(((u32)(slot_index & 0xFF) << 1) + (u32)scan_link_page);
        if (slot[0x33A4] == match_index) {
            return 0;
        }
        slot_index++;
        if (slot[0x33A5] != match_index) {
            goto continue_loop;
        }

return_zero:
        ASM_SCHED_BARRIER(); /* MATCH: Keep this zero-return block distinct so GCC shares the retail epilogue through a jump. */
        return 0;

continue_loop:
        if ((u32)(slot_index & 0xFF) < 0x21U) {
            goto loop;
        }
        return 1;

    case 2:
    case 3:
        {
            register s32 no_match ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            s32 other_entity_index;
            u8 *other_entity_base;
            u8 *other_entity;
            u8 *other_link_page;

            no_match = 0;
            other_entity_base = D_800D2644;
            other_link_page = (u8 *)0x80010000;
            other_entity_index = other_link_page[((record_id & 0xFF) << 1) + 0x33A4];
            other_entity = other_entity_base + (other_entity_index << 5);
            if (other_entity[7] != (entity_id & 0xFF)) {
                return no_match;
            }
            return 1;
        }

    default:
        return 1;
    }
}
