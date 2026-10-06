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


/* Offset coordinates in unprocessed type-2 part chains and mark them processed. */
void func_80047054(void *data, s32 flagged_x_offset, s32 y_offset, s32 x_offset)
{
    void *header = data;
    s32 skip_bytes;
    u32 entry_addr;
    u8 *entry;
    u8 *part;
    s32 part_entry_type;
    u32 entries_end;
    u16 x_or_end_flag;
    u8 flags;

    skip_bytes = ((S_80047054_0 *)header)->unk_04;
    skip_bytes *= 4;
    entry_addr = ((S_80047054_0 *)header)->unk_00 + skip_bytes;
    ASM_KEEP(entry_addr);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    if (entry_addr < ((S_80047054_0 *)header)->unk_08) {
        part_entry_type = 2;
        entry = (u8 *)entry_addr + 4;
        do {
            if (((S_80047054_1_pre *)entry)[-1].unk_00 == part_entry_type) {
                part = ((S_80047054_1 *)entry)->unk_00;
                flags = *part;
                if (!(flags & 8)) {
                    *part = flags | 8;
                    do {
                        if (*part & 0x40) {
                            x_or_end_flag = *(u16 *)(part + 4) + flagged_x_offset;
                        } else {
                            x_or_end_flag = *(u16 *)(part + 4) + x_offset;
                        }
                        *(u16 *)(part + 4) = x_or_end_flag;
                        if (!(*part & 0x20)) {
                            *(u16 *)(part + 6) = *(u16 *)(part + 6) + y_offset;
                        }
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
