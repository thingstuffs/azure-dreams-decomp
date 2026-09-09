#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80094268_arg0.h"



M2C_UNK func_80035208();
M2C_UNK func_8008B158();
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



typedef struct S_80092A84_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80092A84_1;   /* state in func_80092A84 */


typedef struct S_80092A84_3 {
    u8 pad_00[0x50];
    void * unk_50;
} S_80092A84_3;   /* entity in func_80092A84 */

typedef struct S_80092A84_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092A84_4;   /* base in func_80092A84 */

void func_80092A84(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2) {
    u8 *state;
    u8 *pal;
    s32 *ctrl;
    s16 position;
    s32 flags;
    s32 result;
    S_80092A84_3 *entity;
    void *handler;
    S_80092A84_4 *base;

    state = D_80083160;
    func_80095C80(arg1);
    func_80095094(arg1);

    pal = D_800FE488;
    position = func_80095978(arg1, pal);
    if ((position - arg1->unk_08.at02_s16.v) >= 4) {
        if (D_800CFCEF == 0) {
            func_80094660(arg0, arg1, arg2);
            return;
        }
    } else if (D_800CFCEF == 0) {
        func_80095A94(arg1, position, pal);
    }

    flags = ((S_80092A84_1 *)state)->unk_10;
    if (flags & 0x10) {
        func_800945B8(arg0, arg1, arg2);
        return;
    }
    if (flags & 0x40) {
        func_800946A0(arg0, arg1, arg2);
        return;
    }

    ctrl = &D_800CFCB4;
    if ((func_80095760(ctrl) == -1) && (func_8009FF50() == 0)) {
        func_8009567C(ctrl);
        func_80094C1C(arg0);
        func_80094984(&D_800D0128, arg0, arg2);
        func_800988C8(arg0, arg1, arg2);

        entity = arg0->unk_2C;
        handler = entity->unk_50;
        if ((handler != &D_8009B828) && (handler != &D_8009B8E8)) {
            if (handler != D_8009B9BC) {
                arg0->unk_2C = 0;
            }
        }

        base = &D_800CFCB4;
        result = func_800A9D74(base->unk_10,
                               arg0->unk_2C);
        if (result != 0) {
            func_80035208(result);
        } else {
            func_8008B158(base->unk_10);
        }
        D_800FE5D8 = (s32 *)&D_80093B00;
        return;
    }

    if (((S_80092A84_1 *)state)->unk_08 & 0xF000) {
        position = arg0->unk_3E.as_u16 - 1;
        arg0->unk_3E.as_u16 = position;
        func_80094944(position, 0xC);
        func_80094C1C(arg0);
        func_80094C74(arg1);
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
      MATERIALISED in C: `u32 page; page = 0x80100000;
      ` after the last intervening call. */
