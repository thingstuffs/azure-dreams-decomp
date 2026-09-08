#include "common.h"


typedef void (*Callback3)(void *, void *, s32);
typedef void (*Callback1)(s32);

typedef struct S_806D2AB0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_806D2AB0_0;   /* arg0 in func_806D2AB0 */

typedef struct S_806D2AB0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_806D2AB0_1;   /* ptr in func_806D2AB0 */

typedef struct S_806D2AB0_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_806D2AB0_2;   /* (offset - index) * 4 + (u8 *)arg0 in func_806D2AB0 */

typedef struct S_806D2AB0_3 {
    u8 pad_00[0x20];
    void * unk_20;
} S_806D2AB0_3;   /* D_80016000[0] in func_806D2AB0 */


extern void *D_80016000[];
extern u8 D_80016148[16];
extern u8 D_80016170[16];

/* Returns the entry index for a key, asserting at main.c line 54 if absent. */
s32 func_806D2AB0(s32 *entries, s32 target_key)
{
    s32 *entry;
    s32 entry_index;
    s32 key_or_offset;

    entry_index = 0;
    if (((S_806D2AB0_0 *)entries)->unk_08 != 0) {
        entry = entries;
loop:
        key_or_offset = *entry;
        if (key_or_offset != target_key) {
            entry += 7;
            entry_index++;
            if (((S_806D2AB0_1 *)entry)->unk_08 == 0) {
                key_or_offset = entry_index * 8;
            } else {
                goto loop;
            }
        } else {
            key_or_offset = entry_index * 8;
        }
        if (((S_806D2AB0_2 *)((key_or_offset - entry_index) * 4 + (u8 *)entries))->unk_08 == 0) {
            goto notify;
        }
        return entry_index;
    } else {
notify:
        (*(Callback3 *)((u8 *)(((S_806D2AB0_3 *)(D_80016000[0]))->unk_20) + 0x168))(
            D_80016148, D_80016170, 0x36);
        (*(Callback1 *)((u8 *)(((S_806D2AB0_3 *)(D_80016000[0]))->unk_20) + 0x174))(1);
    }
    return entry_index;
}
