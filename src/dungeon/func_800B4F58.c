#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BA6B8_0_pre {
    u16 unk_00;
} S_800BA6B8_0_pre;   /* the 0x2 bytes before arg0 in func_800BA6B8, addressed as arg0[-1] */

typedef struct S_800BA6B8_0 {
    u8 pad_00[0x30];
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
} S_800BA6B8_0;   /* arg0 in func_800BA6B8 */

typedef struct S_800BA6B8_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800BA6B8_1;   /* arg2 in func_800BA6B8 */


s32 func_800644B8();                             /* extern */
extern M2C_UNK D_800814A0;
extern u16 D_80083164;
extern u16 D_800DF37C;

/* Updates enabled output channels with a shared value and sets flags when active. */
void func_800BA6B8(void *channel_config, void *unused, void *output) {
    s8 channel_value;

    if (D_800DF37C != 0) {
        (*(u16 *)((u8 *)channel_config + -2)) = (u16) (((S_800BA6B8_0_pre *)channel_config)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
    channel_value = (func_800644B8(D_80083164 << 8) >> 7) - 0x80;
    if (((S_800BA6B8_0 *)channel_config)->unk_30 != 0) {
        ((S_800BA6B8_1 *)output)->unk_0C = channel_value;
    }
    if (((S_800BA6B8_0 *)channel_config)->unk_31 != 0) {
        ((S_800BA6B8_1 *)output)->unk_0D = channel_value;
    }
    if (((S_800BA6B8_0 *)channel_config)->unk_32 != 0) {
        ((S_800BA6B8_1 *)output)->unk_0E = channel_value;
    }
}
