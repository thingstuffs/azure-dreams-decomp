#include "common.h"

extern s32 func_80033B2C();
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];

s32 func_800B8834(s32 arg0, s32 arg1)
{
    s32 i;
    s32 index;
    s32 record_index;
    s32 compare_index;
    register s32 arg0_hold ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 arg1_hold ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 kind;
    u8 *entity_base;
    u8 *entity;
    u8 *record_base;
    u8 *record;
    u8 *first_page;
    u8 *loop_page;
    u8 *slot;

    arg0_hold = arg0;
    arg1_hold = arg1;
    entity_base = D_800D2644;
    index = arg1_hold & 0xFF;
    entity = entity_base + (index << 5);
    if (func_80033B2C(*(s16 *)(entity + 8)) == 0) {
        goto return_zero;
    }

    record_base = D_800D2EA4;
    record_index = arg0_hold & 0xFF;
    record = record_base + (record_index << 3);
    if (record[2] != entity[4]) {
        return 0;
    }
    if (record[3] != entity[5]) {
        return 0;
    }
    ASM_KEEP(record);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */

    first_page = (u8 *)0x80010000;
    if (first_page[((arg0_hold & 0xFF) << 1) + 0x33A5] != 0) {
        return 0;
    }

    kind = record[4];
    switch (kind) {
    case 0:
        goto return_zero;

    case 1:
        if ((entity[3] & 1) == 0) {
            goto return_zero;
        }

        i = 0;
        loop_page = (u8 *)0x80010000;
        compare_index = index;
loop:
        slot = (u8 *)(((u32)(i & 0xFF) << 1) + (u32)loop_page);
        if (slot[0x33A4] == compare_index) {
            return 0;
        }
        i++;
        if (slot[0x33A5] != compare_index) {
            goto continue_loop;
        }

return_zero:
        ASM_SCHED_BARRIER(); /* MATCH: Keep this zero-return block distinct so GCC shares the retail epilogue through a jump. */
        return 0;

continue_loop:
        if ((u32)(i & 0xFF) < 0x21U) {
            goto loop;
        }
        return 1;

    case 2:
    case 3:
        do {
            register s32 case_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            s32 other_index;
            u8 *other_entity_base;
            u8 *other_entity;
            u8 *case_page;

            case_result = 0;
            other_entity_base = D_800D2644;
            case_page = (u8 *)0x80010000;
            other_index = case_page[((arg0_hold & 0xFF) << 1) + 0x33A4];
            other_entity = other_entity_base + (other_index << 5);
            ASM_KEEP(arg0_hold);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (other_entity[7] != (arg1_hold & 0xFF)) {
                return case_result;
            }
            ASM_KEEP(arg1_hold);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            return 1;
        } while (0);

    default:
        return 1;
    }
}

/* MECHANISM: Preserve raw arg0/arg1 across the call while separately holding the
   masked entity index and entity base, yielding the retail four-save frame.
   Name D_800D2644 before the index init; split case-2 temporaries from original ranges.
   Guarded s2/s3 holds and named region bases preserve retail materialization order.
   A guarded v0 case zero plus the record fence place delay slots; split pages keep CFG. */
