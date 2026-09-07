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

s32 func_8008C8BC(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *held0 ASM_REG("$18") = arg0;
    register void *held2 ASM_REG("$19") = arg2;
    register void *held3 ASM_REG("$16") = arg3;
    register s32 temp_s1 ASM_REG("$17");
    register u8 *r4 ASM_REG("$4");
    s32 temp_v1;
    u8 *state;

    ASM_KEEP(held0);
    ASM_KEEP(held2);
    ASM_KEEP(held3);
    temp_s1 = ((u16) M2C_FIELD(held3, u16 *, 0x2A) >> 9) & 7;
    if ((func_8009A540(temp_s1, M2C_FIELD(held2, u8 *, 0x24), M2C_FIELD(held2, u8 *, 0x25), (s16) (M2C_FIELD(held3, u16 *, 0x88) - 0x20)) << 0x10) != 0) {
        temp_v1 = func_8009B25C(held3, (M2C_FIELD(held2, u8 *, 0x24) + D_8006CCD8[temp_s1]) & 0xFFFF, (M2C_FIELD(held2, u8 *, 0x25) + D_8006CCE8[temp_s1]) & 0xFFFF, (s16) M2C_FIELD(held3, u16 *, 0x88));
        ASM_SCHED_BARRIER();
        r4 = (u8 *)0x80010000;
        M2C_FIELD(held3, s32 *, 0x60) = temp_v1;
        if (!(M2C_FIELD(r4, u16 *, 0x3714) & 1) && (temp_v1 != 0) && (M2C_FIELD(temp_v1, s32 *, 0x14) & 0x4000)
            && (M2C_FIELD(r4, u8 *, 0x3186) & 1) && !(M2C_FIELD(held3, s32 *, 0x1C) & 0x410)) {
            M2C_FIELD(held3, void **, 0x60) = NULL;
            ASM_MEM_BARRIER();
#ifndef NON_MATCHING
            func_8008CA80();
#else
            func_8008CA80(held3);
#endif
            return 0;
        }
        r4 = (u8 *)held3;
        ASM_KEEP(r4);
        ASM_SCHED_BARRIER();
        func_8009C93C(r4, held2, (s16) M2C_FIELD(held3, u16 *, 0x2A), 1, 0);
        func_8008C9F4();
        return 0x11;
    }
    M2C_FIELD(held3, void **, 0x60) = NULL;
    ASM_SCHED_BARRIER();
    M2C_FIELD(held0, s8 *, 0x9A) = 0x11;
    state = D_80083460;
    M2C_FIELD(held0, s8 *, 0x9B) = 0;
    M2C_FIELD(held0, s32 *, 0x8C) = 0;
    M2C_FIELD(state, void **, 0xC) = held3;
    M2C_FIELD(held0, s16 *, 0xA6) = 0;
    M2C_FIELD(held0, u16 *, 0x98) = (u16) ((M2C_FIELD(held0, u16 *, 0x98) | 0x2000) & 0xEFFF);
    M2C_FIELD(state, u16 *, 2) = (u16) (M2C_FIELD(state, u16 *, 2) | 0x400);
    func_80099F70(M2C_FIELD(held3, s32 *, 0x5C));
    func_8009F644(held3, 0x18, 0, 0);
    if (func_800A5C70() != 0) {
        M2C_FIELD(state, u16 *, 2) = (u16) (M2C_FIELD(state, u16 *, 2) | 0x80);
    }
    M2C_FIELD(held0, s16 *, 0x96) = 6;
    M2C_FIELD(held0, s8 *, 0x102) = 0;
    return 0;
}

/* MECHANISM: (1) NO dead `idx*2` statement -- an m2c-carried dead shift pins the
   `sll` before the table `lui/addiu`; deleting it restores retail's la-then-index order.
   (2) The 0x8008CA80 tail is LEAD-22 SHAPE C: `callee(); return 0;` with a memory
   barrier BETWEEN the ent->f60 store and the call, so gcc leaves the jal delay a nop
   and maspsx relocates `move v0,zero` into the converted `j`'s slot.
   (3) $a0 is a HELD frame object: one guarded `register u8 *r4 ASM_REG("$4")` carries
   both the 0x80010000 page base and the func_8009C93C a0 arg; `r4=ent; ASM_KEEP(r4);`
   at the merge (a) blocks reorg from stealing `move a1,s3` into the bnez delay (nop +
   target past the a0 move) and (b) kills cse's $a0==$s0 equivalence so `lh a2,0x2a(s0)`
   keeps its $s0 base. A sched barrier after the call result holds `lui $a0` after
   `move v1,v0`. */
