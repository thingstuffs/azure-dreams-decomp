#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

M2C_UNK func_80035208();
M2C_UNK func_8008B158();
M2C_UNK func_80092C48();
M2C_UNK func_80092CB0();
M2C_UNK func_8009451C();
M2C_UNK func_800945B8();
M2C_UNK func_80094660();
M2C_UNK func_800946A0();
M2C_UNK func_80094944();
M2C_UNK func_80094984();
M2C_UNK func_80094C1C();
M2C_UNK func_80094C74();
M2C_UNK func_80095094();
M2C_UNK func_8009567C();
s32 func_80095760();
s16 func_80095978();
M2C_UNK func_80095A94();
M2C_UNK func_80095C80();
M2C_UNK func_800988C8();
s32 func_8009FF50();
s32 func_800A9D74();

extern u8 D_80083160[];
extern M2C_UNK D_80093B00;
extern M2C_UNK D_8009B828;
extern M2C_UNK D_8009B8E8;
extern u8 D_8009B9BC[];
extern s32 D_800CFCB4;
extern u8 D_800CFCEF;
extern M2C_UNK D_800D0128;
extern u8 D_800FE488[];
extern s32 *D_800FE5D8;

void func_80092A84(void *arg0, void *arg1, M2C_UNK arg2) {
    u8 *state;
    u8 *pal;
    s32 *ctrl;
    s16 position;
    s32 flags;
    s32 result;
    void *entity;
    void *handler;
    void *base;

    state = D_80083160;
    func_80095C80(arg1);
    func_80095094(arg1);

    pal = D_800FE488;
    position = func_80095978(arg1, pal);
    if ((position - FIELD(arg1, s16, 0xA)) >= 4) {
        if (D_800CFCEF == 0) {
            func_80094660(arg0, arg1, arg2);
            func_80092CB0();
            return;
        }
    } else if (D_800CFCEF == 0) {
        func_80095A94(arg1, position, pal);
    }

    flags = FIELD(state, s32, 0x10);
    if (flags & 0x10) {
        func_800945B8(arg0, arg1, arg2);
        func_80092CB0();
        return;
    }
    if (flags & 0x40) {
        func_800946A0(arg0, arg1, arg2);
        func_80092CB0();
        return;
    }

    ctrl = &D_800CFCB4;
    if ((func_80095760(ctrl) == -1) && (func_8009FF50() == 0)) {
        func_8009567C(ctrl);
        func_80094C1C(arg0);
        func_80094984(&D_800D0128, arg0, arg2);
        func_800988C8(arg0, arg1, arg2);

        entity = FIELD(arg0, void *, 0x2C);
        handler = FIELD(entity, void *, 0x50);
        if ((handler != &D_8009B828) && (handler != &D_8009B8E8)) {
            if (handler != D_8009B9BC) {
                FIELD(arg0, void *, 0x2C) = 0;
            }
        }

        base = &D_800CFCB4;
        result = func_800A9D74(FIELD(base, s32, 0x10),
                               FIELD(arg0, void *, 0x2C));
        if (result != 0) {
            register u32 page ASM_REG("$3");

            func_80035208(result);
            page = 0x80100000;
            ASM_PAGEBASE_PIN(page);
            func_80092C48();
            return;
        }

        func_8008B158(FIELD(base, s32, 0x10));
        D_800FE5D8 = (s32 *)&D_80093B00;
        func_80092CB0();
        return;
    }

    if (FIELD(state, s32, 8) & 0xF000) {
        position = FIELD(arg0, u16, 0x3E) - 1;
        FIELD(arg0, u16, 0x3E) = position;
        func_80094944(position, 0xC);
        func_80094C1C(arg0);
        func_80094C74(arg1);
        func_80092CB0();
        return;
    }

    func_8009451C(arg0, arg1, arg2);
}

/* MECHANISM (byte-exact @2.8.1-G0, 148/148 words):
   1. DEPIN. The census candidate's three ASM_REG pins WERE the residue. The $18
      pin forced `lui $18,%hi;addiu $18,$18,%lo` where retail splits the la as
      `lui $v0,%hi; addiu $s2,$v0,%lo` (gcc only self-bases a la into a HARD-reg
      pseudo); the $16 pin on arg0 demoted arg0's parm copy behind arg1/arg2, so
      the prologue emitted sw17/mv17,sw19/mv19,sw16/mv16 instead of retail's
      ascending sw16/mv16,sw17/mv17,sw19/mv19. Unpinned, gcc picks the identical
      colouring ($16=arg0,$17=arg1,$19=arg2,$18=temp,$20=&D_80083160) by itself.
   2. ARITY. func_80095760 takes ONE arg: retail's `move a0,s2` sits in that
      jal's own delay slot and the $a1 it sees is leftover from the `beqz` delay
      of the flags&0x40 test. The candidate's phantom 2nd arg was the +1 word.
   3. SPLIT one name per live range (pal / ctrl / base) instead of re-assigning
      one `work`; base=&D_800CFCB4 recolours into arg1's dead $17 exactly as
      retail does after the three handler compares.
   4. LEAD 27 page-base tail slot: retail parks a DEAD `lui $v1,0x8010`
      (%hi(D_800FE5D8), rematerialised from the sibling path) in the delay slot
      of the converted `j func_80092C48`. gcc shares one page base across the
      branch and DCEs the copy, so nothing exists to reschedule — it must be
      MATERIALISED in C: `register u32 page ASM_REG("$3"); page = 0x80100000;
      ASM_PAGEBASE_PIN(page);` after the last intervening call. */
