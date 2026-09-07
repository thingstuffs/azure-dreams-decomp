#include "common.h"

#ifndef NULL
#define NULL ((void *)0)
#endif


typedef void (*Callback)(void *, void *, void *, void *);

extern void func_800353F4();
extern void func_80042B68();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern void func_800A48F0();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern void func_80169FC0() __attribute__((noreturn));
extern void func_8016A158() __attribute__((noreturn));
extern void func_8016A17C() __attribute__((noreturn));
extern void func_8016A1E8() __attribute__((noreturn));
extern void func_8016A280() __attribute__((noreturn));
extern void func_8016A298() __attribute__((noreturn));
extern void func_8016A318() __attribute__((noreturn));
extern void func_8016A348() __attribute__((noreturn));
extern void D_8016A36C();

extern u16 D_80013714;
extern s16 D_80083228;
extern u16 D_80083462;
extern s16 D_8008346A;
extern u8 *D_800E3D7C;
extern Callback D_80173B94[];
extern u8 D_80173DDC[];


typedef struct S_80169EC0_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80169EC0_0;   /* scan in func_80169EC0 */

typedef struct S_80169EC0_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80169EC0_1_pre;   /* the 0x14 bytes before entry in func_80169EC0, addressed as entry[-1] */

typedef struct S_80169EC0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80169EC0_2;   /* record in func_80169EC0 */

typedef struct S_80169EC0_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} S_80169EC0_3;   /* actor in func_80169EC0 */

typedef struct S_80169EC0_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80169EC0_4;   /* data in func_80169EC0 */

typedef struct S_80169EC0_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80169EC0_5;   /* motion in func_80169EC0 */

void func_80169EC0(void *arg0, void *arg1, void *arg2)
{
    void *owner = arg0;
    void *motion = arg1;
    register void *data ASM_REG("$19") = arg2;   /* MATCH pin: load-bearing for the whole function shape */
    register void *actor ASM_REG("$16") = owner;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 initialWork ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s16 work ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u32 initialRaw ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    Callback callback;
    Callback callback2;
    s32 result;
    s32 flags;
    s32 i;
    u8 *scan;
    void *entry;
    S_80169EC0_2 *record;
    u16 status;
    u16 height;
    s16 signedHeight;

    if ((*(u8 *)((u8 *)owner + (0xB1))) == 0 &&
        !(D_80013714 & 1) && D_8008346A == 0) {
        (*(u8 *)((u8 *)owner + (0xB1))) = 1;
        func_800353F4(D_80173DDC);
        (*(u8 *)((u8 *)owner + (0x6D))) = 0;
        (*(u8 *)((u8 *)owner + (0x9B))) = 0;
    }

    ASM_MEM_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */

    if (D_80013714 & 8) {
        i = 1;
        scan = D_800E3D7C + 4;
        do {
            entry = ((S_80169EC0_0 *)scan)->unk_AC;
            if (entry != NULL) {
                record = ((S_80169EC0_1_pre *)entry)[-1].unk_00;
                record->unk_14 &= 0xFFBF;
            }
            i--;
            scan -= 4;
        } while (i >= 0);
    }

    if ((*(u8 *)((u8 *)owner + (0xB0))) == 1) {
        u32 page;
        func_800A48F0(actor, 7, 1);
        page = 0x80080000;
        ASM_PAGEBASE_PIN(page);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80169FC0();
        return;
    }

    func_80042B68(actor, 7);
    if (D_80083462 & 0x2000) {
        callback = (*(Callback *)((u8 *)owner + (0x8C)));
        if (callback == (Callback)D_8016A36C) {
            callback(owner, motion, data, actor);
            func_8016A348();
            return;
        } else {
            ((S_80169EC0_3 *)actor)->unk_71 &= 0x7F;
            func_8016A348();
            return;
        }
    }

    {
        register void *callOwner ASM_REG("$4") = owner;   /* MATCH pin: retail schedule: same instructions, different order without it */
        register void *callMotion ASM_REG("$5") = motion;   /* MATCH pin: retail schedule: same instructions, different order without it */
        register void *callData ASM_REG("$6") = data;   /* MATCH pin: retail schedule: same instructions, different order without it */

        initialRaw = ((S_80169EC0_3 *)actor)->unk_6D.u;
        initialRaw <<= 24;
        ASM_KEEP_NV(initialRaw);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        initialWork = (s32)initialRaw >> 24;
        if (func_800A9E70(callOwner, callMotion, callData, actor) != 0) {
            return;
        }
    }

    callback2 = (*(Callback *)((u8 *)owner + (0x8C)));
    if (callback2 != NULL) {
        callback2(owner, motion, data, actor);
    }
    D_80173B94[(*(u8 *)((u8 *)owner + (0x9A)))](owner, motion, data, actor);
    if (initialWork != ((S_80169EC0_3 *)actor)->unk_6D.s) {
        func_800AA36C(owner, motion, data, actor);
    }

    status = ((S_80169EC0_4 *)data)->unk_14;
    if (!(status & 0x8000)) {
        register s32 angleCalc ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        u16 lowStatus;
        u16 lowCleared;
        angleCalc = D_80083228 + ((S_80169EC0_3 *)actor)->unk_2A + 0x100;
        work = (angleCalc >> 9) & 7;
        if ((*(s16 *)((u8 *)owner + (0x94))) != work) {
            u8 *steps = ((S_80169EC0_4 *)data)->unk_2C;
            if (steps != NULL) {
                func_80047738(data, steps[work], ((S_80169EC0_4 *)data)->unk_04);
            }
            (*(s16 *)((u8 *)owner + (0x94))) = work;
        }

        lowStatus = ((S_80169EC0_4 *)data)->unk_14;
        lowCleared = lowStatus & 0xFFFE;
        ((S_80169EC0_4 *)data)->unk_14 = lowCleared;
        if (!(((S_80169EC0_3 *)actor)->unk_1C & 0x20)) {
            if (!(lowStatus & 0x40)) {
                func_800478B8(data);
                func_8016A158();
                return;
            }
        } else {
            ((S_80169EC0_4 *)data)->unk_14 = lowCleared | 0x7000;
        }
        func_800A020C(((S_80169EC0_3 *)actor)->unk_1C, (u8 *)data + 0xC);
        func_8016A17C();
        return;
    }

    ((S_80169EC0_4 *)data)->unk_14 = (status & 0x800) ?
                            (status & 0x8FFF) : (status | 0x7000);

    ((S_80169EC0_5 *)motion)->unk_00.at00.v += ((S_80169EC0_5 *)motion)->unk_0C;
    ((S_80169EC0_5 *)motion)->unk_04.at00.v += ((S_80169EC0_5 *)motion)->unk_10;
    if ((*(u16 *)((u8 *)owner + (0x98))) & 8) {
        (*(u8 *)((u8 *)owner + (0x9D))) = 0;
        func_8016A1E8();
        return;
    }

    ((S_80169EC0_5 *)motion)->unk_14 += (*(s8 *)((u8 *)owner + (0x9D))) * 0x14000;
    (*(u8 *)((u8 *)owner + (0x9D)))++;
    ASM_MEM_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
    (*(s32 *)((u8 *)owner + (0x90))) += ((S_80169EC0_5 *)motion)->unk_14;

    if ((*(u16 *)((u8 *)owner + (0x98))) & 4) {
        goto clear_movement_flag;
    }
    result = func_800BCB04(((S_80169EC0_5 *)motion)->unk_00.at02.v, ((S_80169EC0_5 *)motion)->unk_04.at02.v,
                           (s16)(((S_80169EC0_3 *)actor)->unk_88.u - 0x20));
    if ((s16)result >= 0x200) {
        goto clear_movement_flag;
    }
    signedHeight = ((S_80169EC0_3 *)actor)->unk_88.s;
    height = ((S_80169EC0_3 *)actor)->unk_88.u;
    if ((*(s16 *)((u8 *)owner + (0x92))) + signedHeight < (s16)result) {
        ((S_80169EC0_3 *)actor)->unk_1C &= 0xF7FFFFFF;
        func_8016A298(height, result, signedHeight);
        return;
    }
    if ((s16)result >= signedHeight) {
        (*(s32 *)((u8 *)owner + (0x90))) = 0;
        func_8016A280(height, result, signedHeight);
        return;
    }
    (*(s16 *)((u8 *)owner + (0x92))) = result - height;
    ((S_80169EC0_5 *)motion)->unk_14 = 0;
    ((S_80169EC0_3 *)actor)->unk_1C |= 0x08000000;
    (*(u8 *)((u8 *)owner + (0x9D))) = 0;
    flags = ((S_80169EC0_3 *)actor)->unk_1C;
    if (flags & 0x40000000) {
        ((S_80169EC0_3 *)actor)->unk_1C = flags & 0xBFFFFFFF;
        result = func_800BCB04((((S_80169EC0_4 *)data)->unk_24 << 6) | 0x20,
                               (((S_80169EC0_4 *)data)->unk_25 << 6) | 0x20,
                               (s16)(((S_80169EC0_3 *)actor)->unk_88.u - 0x20));
        (*(s16 *)((u8 *)owner + (0x92))) += ((S_80169EC0_3 *)actor)->unk_88.u - result;
        ((S_80169EC0_3 *)actor)->unk_88.u = result;
        func_8016A318();
        return;
    }
    goto finish;

clear_movement_flag:
    ((S_80169EC0_3 *)actor)->unk_1C &= 0xF7FFFFFF;

finish:
    ((S_80169EC0_5 *)motion)->unk_0A = (*(s8 *)((u8 *)owner + (0xAA))) +
                              (((S_80169EC0_3 *)actor)->unk_88.u +
                               (*(u16 *)((u8 *)owner + (0x92))));
    ((S_80169EC0_4 *)data)->unk_14 |= 0x40;
    ASM_KEEP(owner);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(work);   /* MATCH pin: load-bearing for the whole function shape */
}
