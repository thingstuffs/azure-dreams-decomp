#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A58CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A58CC_0;   /* (void *) shared_s0 in func_800A58CC */

typedef struct S_800A58CC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A58CC_1;   /* coords in func_800A58CC */

typedef struct S_800A58CC_2 {
    void * unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800A58CC_2;   /* arg0 in func_800A58CC */

typedef struct S_800A58CC_3 {
    u8 pad_00[0xC4];
    union { s16 s; u16 u; } unk_C4;   /* accessed as both */
    u8 pad_C6[0x2];
    s16 unk_C8;
} S_800A58CC_3;   /* town in func_800A58CC */


s32 func_8008C180();                        /* extern */
s16 func_80094AA0();               /* extern */
M2C_UNK func_80095094();                      /* extern */
M2C_UNK func_80095388();                 /* extern */
M2C_UNK func_800954F4();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
s32 func_800A5894();                          /* extern */
M2C_UNK func_800A596C();                            /* extern */
s32 func_800C1D44();                             /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80083780;
extern s32 D_800A5A98;
extern M2C_UNK D_800FE488;

void func_800A58CC(S_800A58CC_2 *arg0, void *arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 shared_s0;
    s32 var_v0;
    s32 tail_v0;
    u16 temp_v0_3;
    u8 *town;
    u8 *coords;
    u8 *flag_page;

    shared_s0 = (s32) arg1;
    town = D_80083160;
    func_80095C80((void *) shared_s0);
    temp_v0 = func_80095978((void *) shared_s0, &D_800FE488);
    if (((S_800A58CC_0 *)((void *) shared_s0))->unk_0A >= temp_v0) {
        u32 dead_page;
        func_80095A94((void *) shared_s0, temp_v0, &D_800FE488);
        dead_page = 0x80080000;
        ASM_PAGEBASE_PIN(dead_page);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800A596C();
        return;
    }
    flag_page = (u8 *)0x800D0000;
    ASM_KEEP(flag_page);   /* MATCH pin: retail basic-block layout depends on it */
    if (flag_page[-0x311] != 0) {
        u32 dead_page;
        ((S_800A58CC_0 *)((void *) shared_s0))->unk_14 = 0;
        func_800954F4((void *) shared_s0, temp_v0);
        dead_page = 0x80080000;
        ASM_PAGEBASE_PIN(dead_page);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800A596C();
        return;
    }
    func_80095388((void *) shared_s0, temp_v0);
    coords = (u8 *)&D_80083780;
    if (func_800C1D44(func_8008C180(((S_800A58CC_1 *)coords)->unk_02, ((S_800A58CC_1 *)coords)->unk_06) & 0xFFFF) != 0) {
        ((S_800A58CC_0 *)((void *) shared_s0))->unk_14 = (s32) (((S_800A58CC_0 *)((void *) shared_s0))->unk_14 - func_800A5894((void *) shared_s0));
    }
    func_80095094((void *) shared_s0);
    func_80095094((void *) shared_s0);
    shared_s0 = (arg0->unk_10 - 0x800) & 0xFFF;
    temp_v0_2 = func_80094AA0(((S_800A58CC_3 *)town)->unk_C8, shared_s0, 0x80);
    ((S_800A58CC_3 *)town)->unk_C8 = temp_v0_2;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    var_v0 = (temp_v0_2 & 0xFFF) - shared_s0;
    if (var_v0 < 0) {
        var_v0 = 0 - var_v0;
    }
    if (var_v0 < 0x80) {
        ((S_800A58CC_3 *)town)->unk_C8 = shared_s0;
    }
    temp_v0_3 = arg0->unk_0A.s - 1;
    arg0->unk_0A.s = temp_v0_3;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    {
        s32 sign_v0;
        s32 count_a0;
        register s32 quotient_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
        sign_v0 = (s32) temp_v0_3 << 16;
        count_a0 = sign_v0 >> 16;
        quotient_v1 = -0x2B0;
        if (count_a0 <= 0) {
            arg0->unk_0A.u = 0;
        }
        tail_v0 = count_a0 > 0
            ? (quotient_v1 = (quotient_v1 - ((S_800A58CC_3 *)town)->unk_C4.s) / count_a0,
               ((S_800A58CC_3 *)town)->unk_C4.u + quotient_v1)
            : -0x2B0;
        ((S_800A58CC_3 *)town)->unk_C4.s = tail_v0;
    }
    if ((arg0->unk_0A.u == 0) && (((S_800A58CC_3 *)town)->unk_C8 == shared_s0)) {
        arg0->unk_0A.u = 0;
        arg0->unk_00 = &D_800A5A98;
    }
}
