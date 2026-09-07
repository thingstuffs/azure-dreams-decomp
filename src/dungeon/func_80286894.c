#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

void func_800199A8(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_8003E4FC();       /* extern */
M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_8003F5E0();                         /* extern */
M2C_UNK func_80053DA8();                    /* extern */
s16 func_8005405C();                             /* extern */
M2C_UNK func_800542BC();                            /* extern */
M2C_UNK func_8005FE18();                     /* extern */
M2C_UNK func_80067014();                     /* extern */
extern M2C_UNK D_8006E61C;
extern M2C_UNK D_80080AF0;
extern s32 D_80081480;
extern M2C_UNK D_8008148C;

typedef struct S_80019894_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    void * unk_08;
} S_80019894_0;   /* temp_s1 in func_80019894 */


s32 func_80019894(s16 arg0) {
    s16 temp_v0;
    s32 temp_a1;
    u8 *temp_s0;
    S_80019894_0 *temp_s1;
    void *temp_arg8;

    temp_s1 = (arg0 * 0xC) + (s8 *)&D_8006E61C;
    temp_v0 = temp_s1->unk_00 - 1;
    temp_s0 = temp_v0 + (u8 *)&D_80080AF0;
    temp_a1 = arg0 + 1;
    if (*temp_s0 == temp_a1) {
        s32 zero = 0;

        ASM_TAILSLOT_PIN(zero);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800199A8();
        return 0;
    }
    func_80053DA8(0x72, temp_a1);
    func_800542BC();
    *temp_s0 = arg0 + 1;
    func_80067014(0);
    func_8005FE18(0);
    temp_arg8 = temp_s1->unk_08;
    D_80081480 = ((Rec_D_80082E80 *)(&D_8008148C))->unk_00;
    func_8003E4FC(6, temp_arg8, 0);
    func_8003E4FC(6, temp_s1->unk_04, 0);
    func_8003F320();
    func_8003F5E0(D_8008148C);
    func_80053DA8(((2 << temp_v0) | 0x10) & 0xFFFF);
    func_800542BC();
    do {

    } while (func_8005405C((s16) temp_s1->unk_00) != 1);
    return 1;
}

/* MECHANISM: Byte-addressed bases preserve the 12-byte record and byte counter indexing,
   while their lifetimes naturally produce the retail 0x28 frame and s1/s3/s2/s0 saves.
   A named field8 argument exposes the global-copy jal slot; the zero-arg noreturn contract
   plus guarded v0 tail-slot pin produces the retail j with move-zero delay. */
