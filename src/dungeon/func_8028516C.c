#include "common.h"

typedef struct DungeonCell {
    s16 unk0;
    s16 unk2;
    u16 flags;
} DungeonCell;

typedef struct DungeonRecord {
    s16 x;
    u16 y;
    s16 count;
    s16 rows;
    u8 pad[12];
} DungeonRecord;

typedef struct DungeonState {
    DungeonCell *cells;
    u8 pad[16];
    s16 shift;
} DungeonState;

extern DungeonState D_8008333C;
extern DungeonRecord D_800E2970[];

s16 func_800BCB04(s32, s32, s32);

s32 func_8001816C(s16 arg0, s16 *arg1, s16 *arg2)
{
    s8 *initial_record;
    register s8 *initial_base ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    DungeonRecord *loop_record;
    DungeonState *state;
    register s8 *initial_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 initial_index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 initial_offset;
    s32 loop_index;
    DungeonCell *cell;
    register s16 inner_count ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 loaded_x;
    s32 loaded_count;
    register s32 row_bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 row ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 row_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 scaled ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 x;
    register s32 scan_bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 next_count;
    s16 result;
    u16 y;
    register s32 scan_y ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 outer_count;
    u16 flags;

    initial_page = (s8 *)0x800E0000;
    ASM_KEEP_NV(initial_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    initial_base = initial_page + 0x2970;
    initial_index = arg0;
    initial_offset = initial_index * 20;
    initial_offset += (s32)initial_base;
    initial_record = (s8 *)initial_offset;
    outer_count = *(s16 *)(initial_record + 6);
    y = *(u16 *)(initial_record + 2);
    state = &D_8008333C;

    if (outer_count > 0) {
        loop_index = initial_index;
    outer_loop:
        {
            s32 record_offset;
            register DungeonRecord *record_base ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            record_offset = loop_index << 2;
            record_offset += loop_index;
            record_offset <<= 2;
            record_base = (DungeonRecord *)0x800E0000;
            ASM_KEEP_NV(record_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            record_base = (DungeonRecord *)((s8 *)record_base + 0x2970);
            loop_record = (DungeonRecord *)(record_offset + (s32)record_base);
        }
        row_bits = (s32)y << 16;
        row = row_bits >> 16;
        loaded_x = loop_record->x;
        row_offset = state->shift;
        ASM_KEEP_DEP_NV(loop_record, row_offset);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        loaded_count = loop_record->count;
        x = loaded_x;
        ASM_KEEP_NV(loaded_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        row_offset = row << row_offset;
        scaled = row_offset * sizeof(DungeonCell);
        row_offset = (s32)state->cells;
        inner_count = loaded_count;
        row_offset += scaled;
        scaled = loaded_x * sizeof(DungeonCell);
        cell = (DungeonCell *)(row_offset + scaled);

        if (loaded_count > 0) {
            scan_bits = row << 6;
            ASM_KEEP_NV(scan_bits);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            scan_y = scan_bits + 0x20;
            ASM_KEEP_NV(scan_y);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
inner_loop:
            flags = cell->flags;
            if (!(flags & 0x8400)) {
                if ((flags & 0x300) == 0x200) {
                    result = func_800BCB04(
                        ((((s32)x << 16) >> 10) + 0x20) & 0xFFE0,
                        (u16)scan_y,
                        -0x400);
                    if (result < 0x200) {
                        register s16 *final_ptr ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                        *arg1 = x;
                        final_ptr = *(s16 **)&arg2;
                        *final_ptr = y;
                        return result;
                    }
                }
            }

            x++;
            next_count = inner_count - 1;
            inner_count = next_count;
            cell++;
            if ((next_count << 16) > 0) {
                goto inner_loop;
            }
        }

        outer_count--;
        y++;
        if ((outer_count << 16) > 0) {
            goto outer_loop;
        }
    }

    return 0x200;
}
