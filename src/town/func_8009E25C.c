#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082D58.h"


typedef struct {
    s32 current;
    u8 pad04[0x28];
    s32 previous_owner;
} TownState;

typedef void (*DispatchFn)(void *, void *, void *, s32);


typedef struct S_8009B9BC_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8009B9BC_1;   /* arg1 in func_8009B9BC */


typedef struct S_8009B9BC_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009B9BC_3;   /* ((S_8009B9BC_1 *)arg1)->unk_0C in func_8009B9BC */

typedef struct S_8009B9BC_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    void * unk_10;
    s32 unk_14;
} S_8009B9BC_4;   /* ((Rec_D_80082D58 *)arg0)->unk_58 in func_8009B9BC */


extern TownState D_800834B8;
extern s32 D_80083780[];
extern s32 D_800D0420[];
extern u8 D_800FE488[];

extern s32 D_80090A6C;
extern s32 D_80092698;
extern s32 D_800927EC;
extern s32 D_80092A84;
extern s32 D_80092CD4;
extern s32 D_80092DA8;
extern s32 D_80092ECC;
extern s32 D_80092FF0;
extern s32 D_800930E4;
extern s32 D_80093250;
extern s32 D_80093328;
extern s32 D_800933FC;
extern s32 D_80093638;
extern s32 D_800AA5F8;

extern void func_8008F170(void *, void *);
extern void func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern s32 func_800352FC();
extern s32 func_8009B120(void *);
extern void func_8009C340(void *, void *, void *, s32);
extern void func_800C172C(void);

void func_8009B9BC(void *arg0, S_8009B9BC_1 *arg1, Rec_D_800E3D7C *arg2, s32 arg3)
{
    TownState *state = &D_800834B8;
    s32 *position = D_80083780;
    s32 *offset = D_800D0420;
    s32 previous_owner = state->previous_owner;
    s32 current;
    s32 target;
    s32 flag;
    DispatchFn selector;
    register void *a0r ASM_REG("$4"); /* MATCH: keep dispatch arguments in retail setup order. */
    register void *a1r ASM_REG("$5"); /* MATCH: keep dispatch arguments in retail setup order. */
    void *a2r;

    arg2->unk_00.at00_s32.v = D_80083780[0];
    arg2->unk_04.at00_s32.v = position[1];
    arg2->unk_08.at00_s32.v = position[2] + offset[2];

    func_8008F170(arg2, D_800FE488);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);

    target = position[2] + offset[2];
    if (target - arg2->unk_08.at00_s32.v >= 0x10) {
        arg2->unk_08.at00_s32.v =
            target + ((S_8009B9BC_3 *)(arg1->unk_0C))->unk_14;
        a2r = arg2;
    }

    current = D_800834B8.current;
    flag = 1;

    if (current == (s32)&D_800930E4 || current == (s32)&D_80093250) {
        a0r = arg0;
        a1r = arg1;
        ASM_KEEP(a0r); /* MATCH: retain argument setup before the dispatch load. */
        selector = (DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)arg0)->unk_58))->unk_08;
        a2r = arg2;
    } else if (current == (s32)&D_800AA5F8) {
        a0r = arg0;
        a1r = arg1;
        ASM_KEEP(a0r); /* MATCH: retain argument setup before the dispatch load. */
        selector = (DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)arg0)->unk_58))->unk_14;
        a2r = arg2;
    } else if (current == (s32)&D_80093328) {
        ASM_USE2(arg3, arg3); /* MATCH: preserve the fourth argument register allocation. */
        a0r = arg0;
        a1r = arg1;
        ASM_KEEP(a0r); /* MATCH: retain argument setup before the dispatch load. */
        selector = (DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)arg0)->unk_58))->unk_0C;
        a2r = arg2;
    } else if (current == (s32)&D_80093638) {
        func_8009C340(arg0, arg1, arg2, arg3);
        goto tail;
    } else {
        if (current == (s32)&D_80092698 || current == (s32)&D_800927EC ||
            current == (s32)&D_80092A84 || current == (s32)&D_80092FF0 ||
            current == (s32)&D_80092CD4 || current == (s32)&D_80092DA8 ||
            current == (s32)&D_80092ECC || current == (s32)&D_800933FC ||
            current == (s32)&D_80090A6C || func_800352FC() != 0) {
            if (previous_owner == (s32)arg1) {
                goto skip;
            }
        }

        a0r = arg0;
        a1r = arg1;
        ASM_KEEP(a0r); /* MATCH: retain argument setup before the dispatch load. */
        selector = (DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)arg0)->unk_58))->unk_10;
        a2r = arg2;
    }
    selector(a0r, a1r, a2r, arg3);
    goto tail;

skip:
    flag = 0;
tail:
    if (flag != 0 && func_8009B120((u8 *)arg0 + 0x4C) != 0) {
        func_800C172C();
    }
}
