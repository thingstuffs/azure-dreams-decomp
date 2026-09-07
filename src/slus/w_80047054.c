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



void func_80047054(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *header = arg0;
    s32 count;
    register u32 cursor ASM_REG("$3");   /* MATCH pin: slus-diff */
    u8 *entry;
    u8 *part;
    register u8 *coords ASM_REG("$8");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 type ASM_REG("$11");   /* MATCH pin: slus-diff */
    u32 limit;
    u16 value;
    u8 flags;

    count = ((S_80047054_0 *)header)->unk_04;
    cursor = ((S_80047054_0 *)header)->unk_00;
    count *= 4;
    cursor += count;
    ASM_KEEP(cursor);   /* MATCH pin: slus-diff */
    if (cursor < ((S_80047054_0 *)header)->unk_08) {
        ASM_KEEP(cursor);   /* MATCH pin: slus-diff */
        type = 2;
        entry = (u8 *)cursor + 4;
        do {
            if (((S_80047054_1_pre *)entry)[-1].unk_00 == type) {
                part = ((S_80047054_1 *)entry)->unk_00;
                flags = *part;
                if (!(flags & 8)) {
                    *part = flags | 8;
                    coords = part + 6;
                    do {
                        if (*part & 0x40) {
                            value = ((S_80047054_2_pre *)coords)[-1].unk_00 + arg1;
                        } else {
                            value = ((S_80047054_2_pre *)coords)[-1].unk_00 + arg3;
                        }
                        ((S_80047054_2_pre *)coords)[-1].unk_00 = value;
                        if (!(*part & 0x20)) {
                            ((S_80047054_2 *)coords)->unk_00 = ((S_80047054_2 *)coords)->unk_00 + arg2;
                        }
                        coords += 0xC;
                        value = *part & 0x80;
                        part += 0xC;
                    } while (!value);
                }
            }
            do {
                limit = ((S_80047054_0 *)header)->unk_08;
            } while (0);
            cursor += 8;
            entry += 8;
        } while (cursor < limit);
    }
}
