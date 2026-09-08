#include "common.h"
#include "records/Rec_D_80082E80.h"


extern void func_800478B8(void *arg0);
typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;

extern GlobalFlags D_800814A0;



typedef struct S_80099B18_1_pre {
    u16 unk_00;
} S_80099B18_1_pre;   /* the 0x2 bytes before arg0 in func_80099B18, addressed as arg0[-1] */

typedef struct S_80099B18_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    u16 unk_10;
} S_80099B18_1;   /* arg0 in func_80099B18 */

typedef struct S_80099B18_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80099B18_2;   /* arg1 in func_80099B18 */

/* Flag blocked records or advance their state, damping motion and fading color when enabled. */
void func_80099B18(void *state, S_80099B18_2 *motion, Rec_D_80082E80 *record)
{
    u16 update_count;
    u8 red;
    u8 blue;
    u8 green;

    if (record->unk_14.at00_u16.v & 0xE000) {
        ((S_80099B18_1_pre *)state)[-1].unk_00 =
            (s16)(((S_80099B18_1_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0.value |= 0x8000;
        return;
    }
    update_count = ((S_80099B18_1 *)state)->unk_10 + 1;
    ((S_80099B18_1 *)state)->unk_10 = update_count;
    if ((update_count << 0x10) > 0) {
        record->unk_14.at00_u16.v =
            (u16)(record->unk_14.at00_u16.v & 0xFF7F);
        func_800478B8(record);
    }
    if (((S_80099B18_1 *)state)->unk_0E != 0) {
        motion->unk_00 =
            (s32)(motion->unk_00 + motion->unk_0C);
        motion->unk_04 =
            (s32)(motion->unk_04 + motion->unk_10);
        motion->unk_08 =
            (s32)(motion->unk_08 + motion->unk_14);
        motion->unk_0C =
            (s32)(motion->unk_0C - (motion->unk_0C >> 2));
        motion->unk_10 =
            (s32)(motion->unk_10 - (motion->unk_10 >> 2));
        motion->unk_14 =
            (s32)(motion->unk_14 - (motion->unk_14 >> 2));
        red = record->unk_0C.at00_u8.v;
        green = record->unk_0C.at01_u8.v;
        record->unk_0C.at00_u8.v =
            (u8)(red - (red >> 1));
        blue = record->unk_0C.at02_u8.v;
        record->unk_0C.at01_u8.v =
            (u8)(green - (green >> 1));
        record->unk_0C.at02_u8.v =
            (u8)(blue - (blue >> 1));
    }
}
