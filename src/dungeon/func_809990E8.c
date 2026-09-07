#include "common.h"
#include "m2c_compat.h"

typedef struct S_8014C8E8_0 {
    u16 unk_00;
    u8 pad_02[0x96];
    s16 unk_98;
    u8 pad_9A[0x12];
    s16 unk_AC;
} S_8014C8E8_0;   /* arg0 in func_8014C8E8; pointer addresses record offset 0x2 */

typedef struct S_8014C8E8_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_8014C8E8_1;   /* arg2 in func_8014C8E8 */

typedef struct S_8014C8E8_2 {
    s32 unk_00;
} S_8014C8E8_2;   /* D_800814A0 in func_8014C8E8 */


/* cfail-repair: tf7-phase1-cache-v3 */

extern s32 D_800814A0[3];
extern void func_800478B8(void *arg0);
void func_8014C8E8(void *arg0, void *arg1, S_8014C8E8_1 *arg2)
{
    s16 temp_v0;
    s32 temp_lo;

    temp_lo = (s32) (((S_8014C8E8_0 *)((u8 *)arg0 - 0x2))->unk_98 << 7) / (s16) ((S_8014C8E8_0 *)((u8 *)arg0 - 0x2))->unk_AC;
    arg2->unk_0E = (s8) temp_lo;
    arg2->unk_0D = (s8) temp_lo;
    arg2->unk_0C = (s8) temp_lo;
    func_800478B8(arg2);
    temp_v0 = (u16) ((S_8014C8E8_0 *)((u8 *)arg0 - 0x2))->unk_98 - 1;
    ((S_8014C8E8_0 *)((u8 *)arg0 - 0x2))->unk_98 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_8014C8E8_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_8014C8E8_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        ((S_8014C8E8_2 *)D_800814A0)->unk_00 = (s32) (((S_8014C8E8_2 *)D_800814A0)->unk_00 | 0x8000);
    }
}
