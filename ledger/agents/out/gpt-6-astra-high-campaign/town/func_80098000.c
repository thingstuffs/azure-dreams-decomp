#include "common.h"

typedef struct S_80095760_0 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_80095760_0;   /* (u8 *)arg0 + temp_v1 in func_80095760 */

typedef struct S_80095760_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80095760_1;   /* (u8 *)arg0 + temp_v1 * 4 in func_80095760 */

typedef struct S_80095760_2 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_80095760_2;   /* temp_v0_2 in func_80095760 */



typedef struct {
    u8 pad_00[8];
    s32 field_08;
    u8 pad_0C[0xBC];
    s16 field_C8;
} SharedState;

extern SharedState D_80083160;
extern s16 D_800D0464;
extern s32 D_800D046C;

extern s16 func_80094BC8(s32, s16);

/* Returns the status of the active entry matching the current direction. */
s32 func_80095760(void *entries)
{
    s16 *direction_ptr;
    s16 angle;
    s32 *slot_ptr;
    s32 direction;
    s32 slot;
    u8 state;
    s32 blocked_state;
    s32 entry_index;
    S_80095760_2 *entry;

    angle = func_80094BC8(D_80083160.field_08, D_80083160.field_C8);
    if (angle != -1) {
        entry_index = 0;
        direction = ((angle + 0x100) / 0x200) & 7;
        blocked_state = 1;
        slot_ptr = &D_800D046C;
        direction_ptr = &D_800D0464;
loop:
        if (direction == *direction_ptr) {
            slot = *slot_ptr;
            if (((S_80095760_0 *)((u8 *)entries + slot))->unk_3A != 0) {
                entry = ((S_80095760_1 *)((u8 *)entries + slot * 4))->unk_1C;
                state = entry->unk_14;
                ASM_USE2(direction_ptr, slot_ptr); /* MATCH: preserve the loop pointers' live ranges through the byte load after removing the label call. */
                if (state == blocked_state) {
                    return -1;
                }
                return 1;
            }
        }
        slot_ptr++;
        entry_index++;
        direction_ptr++;
        if (entry_index < 4) {
            goto loop;
        }
    }
    return 0;
}
