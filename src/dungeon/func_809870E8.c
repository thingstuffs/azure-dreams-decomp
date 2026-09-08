#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8015E8E8_0 {
    u16 unk_00;
    u8 pad_02[0x96];
    s16 unk_98;
    u8 pad_9A[0x12];
    s16 unk_AC;
} S_8015E8E8_0;   /* arg0 in func_8015E8E8; pointer addresses record offset 0x2 */



#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern s32 D_800814A0[3];

/* Applies a countdown-based fade to three output channels and flags completion. */
void func_8015E8E8(void *record_data, void *unused, Rec_D_80082E80 *output) {
    s16 ticks_left;
    s32 fade_level;

    fade_level = (s32) (((S_8015E8E8_0 *)((u8 *)record_data - 0x2))->unk_98 << 7) / (s16) ((S_8015E8E8_0 *)((u8 *)record_data - 0x2))->unk_AC;
    output->unk_0C.at02_s8.v = (s8) fade_level;
    output->unk_0C.at01_s8.v = (s8) fade_level;
    output->unk_0C.at00_s8.v = (s8) fade_level;
    func_800478B8(output);
    ticks_left = (u16) ((S_8015E8E8_0 *)((u8 *)record_data - 0x2))->unk_98 - 1;
    ((S_8015E8E8_0 *)((u8 *)record_data - 0x2))->unk_98 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_8015E8E8_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_8015E8E8_0 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
