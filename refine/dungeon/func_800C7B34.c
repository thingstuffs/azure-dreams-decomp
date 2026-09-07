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

/* Checks the record and triggers the associated visual and sound effects on success. */
s32 func_800CD294(void *record_data) {
    /* fidelity: retail forwards $a0..$a3 into func_800A6508 untouched (it reads
       $a3, which this row never writes).  Name them at the call site through
       ASM_REG pins so the C says what retail does without emitting a byte. */
    register void *fwd_a0 ASM_REG("$4");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 fwd_a1 ASM_REG("$5");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 fwd_a2 ASM_REG("$6");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 fwd_a3 ASM_REG("$7");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    M2C_UNK check_mask;
    S_800CD294_1 *entity;

    check_mask = 0x40;
    if (*D_800E3D40 != 0) {
        check_mask = 0x400;
    }
    if (func_800C8C1C(record_data, check_mask, 0x10) == 0) {
        if (((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_27 == 0) {
            func_800A6508(fwd_a0, fwd_a1, fwd_a2, fwd_a3);
            return 1;
        }
        return 1;
    }
    func_80099844(record_data, &D_800E1C03);
    if (((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_27 == 0) {
        func_800DC1B8(D_800DCF14);
    }
    entity = ((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_00;
    if (!(entity->unk_14 & 0x8000)) {
        func_800C5BBC((entity->unk_24 << 6) | 0x20, (entity->unk_25 << 6) | 0x20, ((S_800CD294_0 *)((u8 *)record_data - 0x14))->unk_9C, 0xFFFFFF, 0x40, 0);
        func_800A56E0(0x612);
    }
    return 1;
}
