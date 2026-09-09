#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C13C8_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x74];
    s16 unk_9C;
    u8 pad_9E[0x86];
    s32 unk_124;
} S_800C13C8_0;   /* arg0 in func_800C13C8; pointer addresses record offset 0x14 */

typedef struct S_800C13C8_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C13C8_1;   /* state in func_800C13C8 */

typedef struct S_800C13C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C13C8_2;   /* temp_v0 in func_800C13C8 */


M2C_UNK func_8008D344(); /* extern */
s32 func_80098864(s32, s32);           /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A6480();            /* extern */
s32 func_800AD6FC();                /* extern */
s32 func_800BBA40(); /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800C135C;
extern u16 D_800DDE84[];
extern M2C_UNK D_800DEAE0;
extern M2C_UNK D_800E1482;
extern void *D_800E3D7C[];

s32 func_800C13C8(void *arg0, s32 arg1, s16 arg2, M2C_UNK arg3) {
    S_800C13C8_2 *temp_v0;
    S_800C13C8_1 *state;
    s32 result;

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }
    if (arg0 == D_800E3D7C[0]) {
        ((S_800C13C8_0 *)((u8 *)arg0 - 0x14))->unk_124 = arg1;
        func_8008D344(arg0, &D_80083780, &D_80082E80, 0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A6480(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, D_800DDE84[((S_800C13C8_0 *)((u8 *)arg0 - 0x14))->unk_27] & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        state = &D_80083460;
        
        state->unk_0A--;
        goto shared;
    }
    temp_v0 = ((S_800C13C8_0 *)((u8 *)arg0 - 0x14))->unk_00;
    if (func_800BBA40(temp_v0->unk_24, temp_v0->unk_25, ((S_800C13C8_0 *)((u8 *)arg0 - 0x14))->unk_9C, &D_800DEAE0, 0x5000, 0x202080, &D_800C135C) != 0) {
        goto success;
    }
    result = 0;
    goto done;
success:
    func_800997FC(&D_800E1482);
shared:
    func_80098B38(arg1);
    result = 1;
done:
    return result;
}

/* MECHANISM: The natural arg0/arg1 lifetimes produce the retail 0x30 frame and s0/s1 saves.
   Exact callee arity, u16 table indexing, and a kept D_80083460 base restore the body.
   Ordered result labels form the final bnez/fallthrough CFG; a one-sided schedule barrier
   prevents cross-jump merging of the distinct constant-zero func_800C1514 tail site. */
