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
extern void func_8009BBDC(void *, void *, void *);
extern void func_8009BBF4(void);
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
    }

    current = D_800834B8.current;
    flag = 1;

    if (current == (s32)&D_800930E4 || current == (s32)&D_80093250) {
        register void *a0r ASM_REG("$4") = arg0;   /* MATCH pin: retail schedule: same instructions, different order without it */
        register void *a1r ASM_REG("$5") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
        s32 selector;
        ASM_KEEP(a0r);   /* MATCH pin: retail basic-block layout depends on it */
        selector = ((S_8009B9BC_4 *)(((Rec_D_80082D58 *)arg0)->unk_58))->unk_08;
        ASM_KEEP(selector);   /* MATCH pin: retail basic-block layout depends on it */
        func_8009BBDC(a0r, a1r, arg2);
        ASM_USE2(flag, arg3);   /* MATCH pin: retail keeps a computation the compiler would drop */
        return;
    }

    if (current == (s32)&D_800AA5F8) {
        register void *a0r ASM_REG("$4") = arg0;   /* MATCH pin: retail schedule: same instructions, different order without it */
        register void *a1r ASM_REG("$5") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
        s32 selector;
        ASM_KEEP(a0r);   /* MATCH pin: retail basic-block layout depends on it */
        selector = ((S_8009B9BC_4 *)(((Rec_D_80082D58 *)arg0)->unk_58))->unk_14;
        ASM_KEEP(selector);   /* MATCH pin: retail basic-block layout depends on it */
        func_8009BBDC(a0r, a1r, arg2);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot contents depend on it */
        return;
    }

    if (current == (s32)&D_80093328) {
        register void *a0r ASM_REG("$4") = arg0;   /* MATCH pin: retail schedule: same instructions, different order without it */
        register void *a1r ASM_REG("$5") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
        s32 selector;
        ASM_USE2(arg3, arg3);   /* MATCH pin: retail immediate-load split depends on it */
        ASM_KEEP(a0r);   /* MATCH pin: retail basic-block layout depends on it */
        selector = ((S_8009B9BC_4 *)(((Rec_D_80082D58 *)arg0)->unk_58))->unk_0C;
        ASM_KEEP(selector);   /* MATCH pin: retail basic-block layout depends on it */
        func_8009BBDC(a0r, a1r, arg2);
        return;
    }

    if (current == (s32)&D_80093638) {
        func_8009C340(arg0, arg1, arg2, arg3);
        func_8009BBF4();
        return;
    }

    if (current == (s32)&D_80092698 || current == (s32)&D_800927EC ||
        current == (s32)&D_80092A84 || current == (s32)&D_80092FF0 ||
        current == (s32)&D_80092CD4 || current == (s32)&D_80092DA8 ||
        current == (s32)&D_80092ECC || current == (s32)&D_800933FC ||
        current == (s32)&D_80090A6C || func_800352FC() != 0) {
        if (previous_owner == (s32)arg1) {
            goto skip;
        }
    }

    {
        void *a0r = arg0;
        void *a1r = arg1;
        ASM_KEEP(a0r);   /* MATCH pin: retail basic-block layout depends on it */
        ((DispatchFn)((S_8009B9BC_4 *)(((Rec_D_80082D58 *)arg0)->unk_58))->unk_10)(
            a0r, a1r, arg2, arg3);
    }
    func_8009BBF4();
    return;

skip:
    flag = 0;
    ASM_KEEP(flag);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (flag != 0 && func_8009B120((u8 *)arg0 + 0x4C) != 0) {
        func_800C172C();
    }
}
