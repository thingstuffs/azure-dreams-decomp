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
    register s8 *initial_base ASM_REG("$5");   /* MATCH pin: retail immediate-load split depends on it */
    DungeonRecord *loop_record;
    DungeonState *state;
    register s8 *initial_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 initial_index ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 initial_offset;
    s32 loop_index;
    DungeonCell *cell;
    register s16 inner_count ASM_REG("$18");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 loaded_x;
    s32 loaded_count;
    register s32 row_bits ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 row ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 row_offset ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    register s32 scaled ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 x;
    register s32 scan_bits ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s16 next_count;
    s16 result;
    u16 y;
    register s32 scan_y ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */
    s16 outer_count;
    u16 flags;

    initial_page = (s8 *)0x800E0000;
    ASM_KEEP_NV(initial_page);   /* MATCH pin: load-bearing for the whole function shape */
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
            register DungeonRecord *record_base ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */

            record_offset = loop_index << 2;
            record_offset += loop_index;
            record_offset <<= 2;
            record_base = (DungeonRecord *)0x800E0000;
            ASM_KEEP_NV(record_base);   /* MATCH pin: load-bearing for the whole function shape */
            record_base = (DungeonRecord *)((s8 *)record_base + 0x2970);
            loop_record = (DungeonRecord *)(record_offset + (s32)record_base);
        }
        row_bits = (s32)y << 16;
        row = row_bits >> 16;
        loaded_x = loop_record->x;
        row_offset = state->shift;
        ASM_KEEP_DEP_NV(loop_record, row_offset);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        loaded_count = loop_record->count;
        x = loaded_x;
        ASM_KEEP_NV(loaded_x);   /* MATCH pin: load-bearing for the whole function shape */
        row_offset = row << row_offset;
        scaled = row_offset * sizeof(DungeonCell);
        row_offset = (s32)state->cells;
        inner_count = loaded_count;
        row_offset += scaled;
        scaled = loaded_x * sizeof(DungeonCell);
        cell = (DungeonCell *)(row_offset + scaled);

        if (loaded_count > 0) {
            scan_bits = row << 6;
            ASM_KEEP_NV(scan_bits);   /* MATCH pin: load-bearing for the whole function shape */
            scan_y = scan_bits + 0x20;
            ASM_KEEP_NV(scan_y);   /* MATCH pin: retail register colouring depends on it */
inner_loop:
            flags = cell->flags;
            if (!(flags & 0x8400)) {
                if ((flags & 0x300) == 0x200) {
                    result = func_800BCB04(
                        ((((s32)x << 16) >> 10) + 0x20) & 0xFFE0,
                        (u16)scan_y,
                        -0x400);
                    if (result < 0x200) {
                        register s16 *final_ptr ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */

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
