#include "common.h"
#include "m2c_compat.h"

typedef s32 (*M2C_CALLBACK)(void *, s32);

typedef struct S_80019F94_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019F94_1;   /* (temp_s0 + held_arg0->unk_10) in func_80019F94 */


M2C_UNK func_80019EA8();
s32 func_8001ADE0();
extern M2C_UNK D_8001C378[];

typedef struct S_80019F94_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
} S_80019F94_0;   /* held_arg0 in func_80019F94 */

/* Returns the first eligible entry with a zero callback result, restarting when requested. */
s32 func_80019F94(void *context) {
    S_80019F94_0 *scan;
    M2C_UNK *flag_page;
    s32 entry_offset;
    s32 entry_index;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scan = context;
    func_80019EA8(scan->unk_14, scan->unk_1A);
    flag_page = (M2C_UNK *)0x80020000;
    do {
        flag_page[-3874] = 0;
        entry_index = 0;
        for (;;) {
            entry_offset = entry_index * 0x10;
            if ((func_8001ADE0(((S_80019F94_1 *)(entry_offset + scan->unk_10))->unk_0C) != 0) ||
                (*(M2C_CALLBACK *)(entry_offset + scan->unk_10))(scan, entry_index) != 0) {
                entry_index++;
                continue;
            }
            break;
        }
    } while (flag_page[-3874] != 0);
    return entry_index;
}
