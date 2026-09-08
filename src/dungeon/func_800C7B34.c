#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CD294_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x74];
    s16 unk_9C;
} S_800CD294_0;   /* arg0 in func_800CD294; pointer addresses record offset 0x14 */

typedef struct S_800CD294_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD294_1;   /* temp_v1 in func_800CD294 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_800E3D40[];
extern s32 D_800DCF14;
void func_80099844();           /* extern */
s32 func_800A56E0();                     /* extern */
void func_800A6508();                          /* extern */
M2C_UNK func_800C5BBC(); /* extern */
s32 func_800C8C1C();        /* extern */
void func_800DC1B8();                         /* extern */
extern M2C_UNK D_800E1C03;

s32 func_800CD294(void *arg0) {
    /* fidelity: retail forwards $a0..$a3 into func_800A6508 untouched (it reads
       $a3, which this row never writes).  Name them at the call site through
       ASM_REG pins so the C says what retail does without emitting a byte. */
    register void *fwd_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 fwd_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 fwd_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 fwd_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    M2C_UNK var_a1;
    S_800CD294_1 *temp_v1;

    var_a1 = 0x40;
    if (*D_800E3D40 != 0) {
        var_a1 = 0x400;
    }
    if (func_800C8C1C(arg0, var_a1, 0x10) == 0) {
        if (((S_800CD294_0 *)((u8 *)arg0 - 0x14))->unk_27 == 0) {
            func_800A6508(fwd_a0, fwd_a1, fwd_a2, fwd_a3);
            return 1;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return 1;
    }
    func_80099844(arg0, &D_800E1C03);
    if (((S_800CD294_0 *)((u8 *)arg0 - 0x14))->unk_27 == 0) {
        func_800DC1B8(D_800DCF14);
    }
    temp_v1 = ((S_800CD294_0 *)((u8 *)arg0 - 0x14))->unk_00;
    if (!(temp_v1->unk_14 & 0x8000)) {
        func_800C5BBC((temp_v1->unk_24 << 6) | 0x20, (temp_v1->unk_25 << 6) | 0x20, ((S_800CD294_0 *)((u8 *)arg0 - 0x14))->unk_9C, 0xFFFFFF, 0x40, 0);
        func_800A56E0(0x612);
    }
    return 1;
}
