/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef void (*Callback)(void *, s32, void *);

M2C_UNK func_800C2C80();
M2C_UNK func_800C2CB0();
s32 func_800C2E1C();
s32 func_800C2F14();
M2C_UNK func_800C8F4C();



void func_800C8E9C(void *arg0, void *arg1, Rec_D_80082E80 *arg2) {
    s32 temp_v0;

    (*(Callback *)((u8 *)arg0 + 0x50))(arg0, arg1, arg2);
    if (!((*(u16 *)((u8 *)arg0 + -2)) & 0x8000)) {
        temp_v0 = func_800C2E1C((*(s16 *)((u8 *)arg0 + 0x72)), (*(s16 *)((u8 *)arg0 + 0x64)));
        if ((*(s16 *)((u8 *)arg0 + 0x74)) != temp_v0) {
            func_800C2CB0(arg0, arg2, (*(M2C_UNK **)((u8 *)arg0 + 0x78))[temp_v0], arg2->unk_04.as_s8);
            (*(s16 *)((u8 *)arg0 + 0x74)) = temp_v0;
        }
        if ((func_800C2F14((*(s16 *)((u8 *)arg0 + 0x72)), (*(s16 *)((u8 *)arg0 + 0x64))) << 0x10) != 0) {
            u16 bit_value = arg2->unk_14.at00_u16.v | 1;
            ASM_TAILSLOT_PIN(bit_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_800C8F4C();
            return;
        }
        arg2->unk_14.at00_u16.v = (s16) (arg2->unk_14.at00_u16.v & 0xFFFE);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800C2C80(arg0, arg2, 0, 0);
    }
}
