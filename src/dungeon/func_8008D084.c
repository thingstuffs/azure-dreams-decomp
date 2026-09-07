#include "common.h"


extern s32 func_8003DE58();
extern void func_80048A44();
extern void func_80091934();
extern void func_80092A08();
extern void func_80092AFC() __attribute__((noreturn));
extern void func_80092B98() __attribute__((noreturn));
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_8009929C();
extern s32 func_80099368();
extern s32 func_8009965C();
extern s32 func_80099734();
extern void func_80099F04();
extern void func_80099F70();
extern void func_800A5720();
extern void *func_800A8608(void *, void *, s32, s32, s32);

extern s16 D_80083228[12];
extern u8 D_80083460[12];
extern u8 D_8008ACDC[12];
extern u8 D_8008D470[12];
extern u8 D_800DD0B8[8];
extern u8 D_800E06EE[9];
extern u8 D_800E06F7[9];


typedef struct S_800927E4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x74];
    void * unk_110;
} S_800927E4_0;   /* arg0 in func_800927E4 */

typedef struct S_800927E4_1 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_800927E4_1;   /* callArg in func_800927E4 */

typedef struct S_800927E4_2 {
    u8 pad_00[0x3228];
    s16 unk_3228;
} S_800927E4_2;   /* hitBase in func_800927E4 */

typedef struct S_800927E4_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x30];
    s32 unk_5C;
    u8 pad_60[0x28];
    u16 unk_88;
} S_800927E4_3;   /* arg3 in func_800927E4 */

typedef struct S_800927E4_4 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800927E4_4;   /* page in func_800927E4 */

typedef struct S_800927E4_5 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_800927E4_5;   /* (void *)coordUnsigned in func_800927E4 */

typedef struct S_800927E4_6 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800927E4_6;   /* arg2 in func_800927E4 */

typedef struct S_800927E4_7 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    u8 * unk_10;
} S_800927E4_7;   /* obj in func_800927E4 */

typedef struct S_800927E4_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800927E4_8;   /* prim in func_800927E4 */

typedef struct S_800927E4_9 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    s16 unk_AA;
    u8 pad_AC[0x2];
    s16 unk_AE;
} S_800927E4_9;   /* effect in func_800927E4 */

typedef struct S_800927E4_10 {
    u8 pad_00[0x1];
    u8 unk_01;
    s8 unk_02;
} S_800927E4_10;   /* entity in func_800927E4 */

typedef struct S_800927E4_11 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800927E4_11;   /* flagsBase in func_800927E4 */

void func_800927E4(void *arg0, s32 arg1, S_800927E4_6 *arg2, S_800927E4_3 *arg3) {
    u16 pos[3];
    register void *obj ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    S_800927E4_8 *prim;
    S_800927E4_9 *effect;
    S_800927E4_10 *entity;
    s32 text;
    s32 root;
    s32 state;
    u16 timer;
    u8 *pageHi;
    s16 *page;
    s32 tailValue;
    u8 *flagsBase;

    state = ((S_800927E4_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        ASM_CLOBBER("$2");   /* MATCH pin: retail delay-slot fill depends on it */
        if (state == 0) {
            goto state_zero;
        }
        goto dflt;
    } else if (state == 2) {
        goto state_two;
    }
dflt:
    return;

state_zero:
        if (((S_800927E4_0 *)arg0)->unk_9A == 0x2C) {
            register void *callArg ASM_REG("$4") = arg2;   /* MATCH pin: retail schedule: same instructions, different order without it */
            u8 *table = D_800DD0B8;
            u8 *hitBase;

            ASM_CLOBBER("$2");   /* MATCH pin: retail delay-slot fill depends on it */
            hitBase = (u8 *)0x80080000;
            ASM_KEEP(hitBase);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ((S_800927E4_1 *)callArg)->unk_2C = table;
            func_80048A44(
                callArg,
                table[((((S_800927E4_2 *)hitBase)->unk_3228 +
                        arg3->unk_2A.s + 0x100) >> 9) & 7],
                0,
                1);
            tailValue = ((S_800927E4_0 *)arg0)->unk_9B + 1;
            ASM_TAILSLOT_PIN_TIED(tailValue);   /* MATCH pin: retail delay-slot fill depends on it */
            func_80092AFC();
            return;
        }

        pageHi = (u8 *)0x80080000;
        ASM_KEEP(pageHi);   /* MATCH pin: load-bearing for the whole function shape */
        page = (s16 *)(pageHi + 0x3160);
        ASM_KEEP(page);   /* MATCH pin: retail delay-slot fill depends on it */
        {
            s32 pageCoord = ((S_800927E4_4 *)page)->unk_C8;
            s32 coordSigned = arg3->unk_2A.s;
            register s32 coordUnsigned ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            register s32 nextCoord ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

            ASM_MEM_BARRIER();   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            coordUnsigned = arg3->unk_2A.u;
            if ((((pageCoord + coordSigned + 0x100) >> 9) & 7) == 2) {
            coordUnsigned = (s32)arg2;
            {
            register u8 *table ASM_REG("$3") = D_800DD0B8;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

            ((S_800927E4_5 *)((void *)coordUnsigned))->unk_2C = table;
            func_80048A44(
                (void *)coordUnsigned,
                table[((((S_800927E4_4 *)page)->unk_C8 +
                        arg3->unk_2A.s + 0x100) >> 9) & 7],
                0,
                1);
            tailValue = ((S_800927E4_0 *)arg0)->unk_9B + 1;
            ASM_TAILSLOT_PIN_TIED(tailValue);   /* MATCH pin: retail delay-slot fill depends on it */
            func_80092AFC();
            return;
            }
            }

            nextCoord = coordUnsigned + 0x200;
            arg3->unk_2A.u = nextCoord;
        }
        func_80092B98();
        return;

state_one:
        if (func_8003DE58(arg2->unk_08, arg2, pos, 0) == 0 &&
            !(arg2->unk_14 & 0x8000)) {
            return;
        }

        if (!(arg3->unk_1C & 0x100000)) {
            void *callA0 = (u8 *)arg0 - 0x20;
            register s32 zero ASM_REG("$6") = 0;   /* MATCH pin: load-bearing for the whole function shape */
            ASM_KEEP_NV(callA0);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ASM_KEEP_NV(zero);   /* MATCH pin: retail register colouring depends on it */
            obj = func_800A8608(
                callA0, ((S_800927E4_0 *)arg0)->unk_110, zero, zero, 0);
            if (obj != 0) {
                u8 *handler = (u8 *)0x80090000;

                ASM_KEEP(handler);   /* MATCH pin: keeps a constant in a register as retail does */
                handler -= 0x2B90;
                ((S_800927E4_7 *)obj)->unk_10 = handler;
                prim = ((S_800927E4_7 *)obj)->unk_08;
                prim->unk_02 = (arg2->unk_24 << 6) + 0x20;
                prim->unk_06 = (arg2->unk_25 << 6) + 0x20;

                if (arg2->unk_14 & 0x8000) {
                    effect = (u8 *)obj + 0x20;
                    tailValue = arg3->unk_88 - 0x50;
                    ASM_TAILSLOT_PIN_TIED(tailValue);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_80092A08(prim, effect);
                    return;
                }

                effect = (u8 *)obj + 0x20;
                ASM_KEEP(effect);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                prim->unk_02 += pos[0];
                prim->unk_06 += pos[1];
                prim->unk_0A = pos[2] + arg3->unk_88;
                effect->unk_A8 = 0x1E;
                effect->unk_AA = 2;
                effect->unk_90 = arg2;
                effect->unk_8C = arg1;
                effect->unk_9C = (u8 *)arg0 + 0x108;

                entity = ((S_800927E4_0 *)arg0)->unk_110;
                if (entity != 0 && entity->unk_01 == 4 &&
                    entity->unk_02 != 0) {
                    effect->unk_AE = 1;
                    effect->unk_A8 = 0x3C;
                }
            }

            root = func_800990FC();
            state = func_80099734(arg3, func_8009929C(8, root));
            state = func_80099194(D_800E06EE, state);
            state = func_80099368(((S_800927E4_0 *)arg0)->unk_110, state);
            text = func_80099194(D_800E06F7, state);
            entity = ((S_800927E4_0 *)arg0)->unk_110;
            if (entity->unk_01 != 4) {
                text = func_8009965C(entity, text);
            }
            func_80099290(text);
            func_800A5720(root);
        }

        ((S_800927E4_0 *)arg0)->unk_96 = 0x1E;
        ((S_800927E4_0 *)arg0)->unk_9B++;
        func_80092B98();
        return;

state_two:
        if ((arg2->unk_14 & 0x8000) ||
            (timer = ((S_800927E4_0 *)arg0)->unk_96 - 1,
             ((S_800927E4_0 *)arg0)->unk_96 = timer,
             (s32)(timer << 16) <= 0)) {
            if (((S_800927E4_0 *)arg0)->unk_110 != 0) {
                func_80091934(arg0, arg1, arg2, arg3);
                func_80092B98();
                return;
            }
            func_80099F70(arg3->unk_5C);
            func_80099F04(arg3->unk_5C);
            flagsBase = D_80083460;
            ASM_KEEP(flagsBase);   /* MATCH pin: load-bearing for the whole function shape */
            ((S_800927E4_11 *)flagsBase)->unk_02 |= 0x812;
            ((S_800927E4_0 *)arg0)->unk_8C = D_8008ACDC;
        }
        return;
}
