#include "common.h"

typedef struct S_80016714_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    u8 * unk_40;
} S_80016714_0;   /* D_80016000 in func_80016714 */

typedef struct S_80016714_1 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016714_1;   /* ((S_80016714_0 *)D_80016000)->unk_08 * 8 +
              ((S_80016714_0 *)D_80016000)->unk_40 in func_80016714 */

typedef struct S_80016714_2 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_80016714_2;   /* ((S_80016714_0 *)D_80016000)->unk_08 * 8 +
                  ((S_80016714_0 *)D_80016000)->unk_40 in func_80016714 */



extern void *D_80016000;
extern u8 D_800189DC[16];
extern u8 D_80018B94[16];
extern u8 D_8001A3AE[];
extern u8 D_8001A495[];

extern s32 func_800178A8(void *, s32, s32);
extern void *func_80017960(void *, void *, s32, s32);
extern void func_80018594(s32);
extern s32 func_8001868C(s32);

/* Looks up event data and applies special-event state updates and overrides. */
void *func_80016714(s32 entry_id, s32 unused, s32 event_id)
{
    void *event_data;
    u8 *event_table;

    event_table = D_800189DC;
    event_data = func_80017960(event_table, D_80018B94, entry_id, event_id);
    if (event_id == 0xB) {
        func_80018594(0x1458);
        if (func_800178A8(event_table, entry_id, 0xB) != 0) {
            return &D_8001A3AE[0];
        }
        ((S_80016714_1 *)(((S_80016714_0 *)D_80016000)->unk_08 * 8 +
              ((S_80016714_0 *)D_80016000)->unk_40))->unk_04++;
        if (((S_80016714_2 *)(((S_80016714_0 *)D_80016000)->unk_08 * 8 +
                  ((S_80016714_0 *)D_80016000)->unk_40))->unk_04 >= 5U) {
            func_80018594(0x1459);
        }
        return event_data;
    }
    if (event_id == 0x1C) {
        if (func_8001868C(0x992) == 0) {
            func_80018594(0x992);
            return &D_8001A495[0];
        }
    }
    return event_data;
}
