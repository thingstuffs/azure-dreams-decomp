#include "common.h"

typedef long long s64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_8008C9F4();
#ifndef NON_MATCHING
void func_8008CA80(void);
#else
void func_8008CA80(void *arg0);
#endif
M2C_UNK func_80099F70();
s32 func_8009A540();
s32 func_8009B25C();
M2C_UNK func_8009C93C();
M2C_UNK func_8009F644();
s32 func_800A5C70();
extern u16 D_80013714;
extern u8 D_80013186;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_80083460[];


typedef struct S_8008C8BC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    union { s32 i; void * p; } unk_60;   /* accessed as both */
    u8 pad_64[0x24];
    u16 unk_88;
} S_8008C8BC_0;   /* held3 in func_8008C8BC */

typedef struct S_8008C8BC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8008C8BC_1;   /* held2 in func_8008C8BC */

typedef struct S_8008C8BC_2 {
    u8 pad_00[0x3186];
    u8 unk_3186;
    u8 pad_3187[0x58D];
    u16 unk_3714;
} S_8008C8BC_2;   /* r4 in func_8008C8BC */

typedef struct S_8008C8BC_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8008C8BC_3;   /* temp_v1 in func_8008C8BC */

typedef struct S_8008C8BC_4 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
    u8 pad_A8[0x5A];
    s8 unk_102;
} S_8008C8BC_4;   /* held0 in func_8008C8BC */

typedef struct S_8008C8BC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_8008C8BC_5;   /* state in func_8008C8BC */

s32 func_8008C8BC(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *held0 ASM_REG("$18") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *held2 = arg2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *held3 ASM_REG("$16") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 temp_s1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *r4;
    s32 temp_v1;
    u8 *state;

    ASM_KEEP(held0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_s1 = ((u16) ((S_8008C8BC_0 *)held3)->unk_2A >> 9) & 7;
    if ((func_8009A540(temp_s1, ((S_8008C8BC_1 *)held2)->unk_24, ((S_8008C8BC_1 *)held2)->unk_25, (s16) (((S_8008C8BC_0 *)held3)->unk_88 - 0x20)) << 0x10) != 0) {
        temp_v1 = func_8009B25C(held3, (((S_8008C8BC_1 *)held2)->unk_24 + D_8006CCD8[temp_s1]) & 0xFFFF, (((S_8008C8BC_1 *)held2)->unk_25 + D_8006CCE8[temp_s1]) & 0xFFFF, (s16) ((S_8008C8BC_0 *)held3)->unk_88);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        r4 = (u8 *)0x80010000;
        ((S_8008C8BC_0 *)held3)->unk_60.i = temp_v1;
        if (!(((S_8008C8BC_2 *)r4)->unk_3714 & 1) && (temp_v1 != 0) && (((S_8008C8BC_3 *)temp_v1)->unk_14 & 0x4000)
            && (((S_8008C8BC_2 *)r4)->unk_3186 & 1) && !(((S_8008C8BC_0 *)held3)->unk_1C & 0x410)) {
            ((S_8008C8BC_0 *)held3)->unk_60.p = NULL;
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
#ifndef NON_MATCHING
            func_8008CA80();
#else
            func_8008CA80(held3);
#endif
            return 0;
        }
        r4 = (u8 *)held3;
        ASM_KEEP(r4);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_8009C93C(r4, held2, (s16) ((S_8008C8BC_0 *)held3)->unk_2A, 1, 0);
        func_8008C9F4();
        return 0x11;
    }
    ((S_8008C8BC_0 *)held3)->unk_60.p = NULL;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_8008C8BC_4 *)held0)->unk_9A = 0x11;
    state = D_80083460;
    ((S_8008C8BC_4 *)held0)->unk_9B = 0;
    ((S_8008C8BC_4 *)held0)->unk_8C = 0;
    ((S_8008C8BC_5 *)state)->unk_0C = held3;
    ((S_8008C8BC_4 *)held0)->unk_A6 = 0;
    ((S_8008C8BC_4 *)held0)->unk_98 = (u16) ((((S_8008C8BC_4 *)held0)->unk_98 | 0x2000) & 0xEFFF);
    ((S_8008C8BC_5 *)state)->unk_02 = (u16) (((S_8008C8BC_5 *)state)->unk_02 | 0x400);
    func_80099F70(((S_8008C8BC_0 *)held3)->unk_5C);
    func_8009F644(held3, 0x18, 0, 0);
    if (func_800A5C70() != 0) {
        ((S_8008C8BC_5 *)state)->unk_02 = (u16) (((S_8008C8BC_5 *)state)->unk_02 | 0x80);
    }
    ((S_8008C8BC_4 *)held0)->unk_96 = 6;
    ((S_8008C8BC_4 *)held0)->unk_102 = 0;
    return 0;
}

/* MECHANISM: (1) NO dead `idx*2` statement -- an m2c-carried dead shift pins the
   `sll` before the table `lui/addiu`; deleting it restores retail's la-then-index order.
   (2) The 0x8008CA80 tail is LEAD-22 SHAPE C: `callee(); return 0;` with a memory
   barrier BETWEEN the ent->f60 store and the call, so gcc leaves the jal delay a nop
   and maspsx relocates `move v0,zero` into the converted `j`'s slot.
   (3) $a0 is a HELD frame object: one guarded `u8 *r4` carries
   both the 0x80010000 page base and the func_8009C93C a0 arg; `r4=ent; `
   at the merge (a) blocks reorg from stealing `move a1,s3` into the bnez delay (nop +
   target past the a0 move) and (b) kills cse's $a0==$s0 equivalence so `lh a2,0x2a(s0)`
   keeps its $s0 base. A sched barrier after the call result holds `lui $a0` after
   `move v1,v0`. */
