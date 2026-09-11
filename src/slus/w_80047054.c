#include "common.h"

#include "common.h"

typedef struct S_80047054_0 {
    s32 unk_00;
    s32 unk_04;
    u32 unk_08;
} S_80047054_0;   /* header in func_80047054 */

typedef struct S_80047054_1_pre {
    s16 unk_00;
} S_80047054_1_pre;   /* the 0x2 bytes before entry in func_80047054, addressed as entry[-1] */

typedef struct S_80047054_1 {
    u8 * unk_00;
} S_80047054_1;   /* entry in func_80047054 */

typedef struct S_80047054_2_pre {
    u16 unk_00;
} S_80047054_2_pre;   /* the 0x2 bytes before coords in func_80047054, addressed as coords[-1] */

typedef struct S_80047054_2 {
    u16 unk_00;
} S_80047054_2;   /* coords in func_80047054 */



/* Offset coordinates in unprocessed type-2 part chains and mark them processed. */
void func_80047054(void *data, s32 flagged_x_offset, s32 y_offset, s32 x_offset)
{
    void *header = data;
    s32 skip_bytes;
    register u32 entry_addr ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    u8 *entry;
    u8 *part;
    register u8 *coords ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 part_entry_type;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    u32 entries_end;
    u16 x_or_end_flag;
    u8 flags;

    skip_bytes = ((S_80047054_0 *)header)->unk_04;
    entry_addr = ((S_80047054_0 *)header)->unk_00;
    skip_bytes *= 4;
    entry_addr += skip_bytes;
    ASM_KEEP(entry_addr);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    if (entry_addr < ((S_80047054_0 *)header)->unk_08) {
        ASM_KEEP(entry_addr);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
        part_entry_type = 2;
        entry = (u8 *)entry_addr + 4;
        do {
            if (((S_80047054_1_pre *)entry)[-1].unk_00 == part_entry_type) {
                part = ((S_80047054_1 *)entry)->unk_00;
                flags = *part;
                if (!(flags & 8)) {
                    *part = flags | 8;
                    coords = part + 6;
                    do {
                        if (*part & 0x40) {
                            x_or_end_flag = ((S_80047054_2_pre *)coords)[-1].unk_00 + flagged_x_offset;
                        } else {
                            x_or_end_flag = ((S_80047054_2_pre *)coords)[-1].unk_00 + x_offset;
                        }
                        ((S_80047054_2_pre *)coords)[-1].unk_00 = x_or_end_flag;
                        if (!(*part & 0x20)) {
                            ((S_80047054_2 *)coords)->unk_00 = ((S_80047054_2 *)coords)->unk_00 + y_offset;
                        }
                        coords += 0xC;
                        x_or_end_flag = *part & 0x80;
                        part += 0xC;
                    } while (!x_or_end_flag);
                }
                entries_end = ((S_80047054_0 *)header)->unk_08;
            } else {
                entries_end = ((S_80047054_0 *)header)->unk_08;
            }
            entry_addr += 8;
            entry += 8;
        } while (entry_addr < entries_end);
    }
}
