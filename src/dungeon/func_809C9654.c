#include "common.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171344(void) __attribute__((noreturn));
extern void func_80171378(void) __attribute__((noreturn));
extern void func_8017139C(void);
extern void func_801715F4(void *, void *, void *, void *);
extern s32 func_80171DA0(void *, void *, void *, void *);
extern void func_80171F64(void *, void *, void *, void *);
extern s32 func_8017207C(void *, void *, void *, s32);
extern void func_80173A30(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170E54;
extern u8 D_80173C7C[];
extern u8 D_80173C84[];
extern u8 D_80173CCC[];
extern u8 D_80173CD4[];
extern u8 D_80173CDC[];


typedef struct S_80170E54_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80170E54_0;   /* arg0 in func_80170E54 */

typedef struct S_80170E54_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80170E54_1;   /* arg3 in func_80170E54 */

typedef struct S_80170E54_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170E54_2;   /* arg2 in func_80170E54 */

typedef struct S_80170E54_3 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80170E54_3;   /* D_800814A8 in func_80170E54 */

typedef struct S_80170E54_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170E54_4;   /* origin in func_80170E54 */

typedef struct S_80170E54_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E54_5;   /* global in func_80170E54 */

void func_80170E54(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void *p0;
    void *p1;
    void *p2;
    register void *p3 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *table;
    s32 result;
    s32 scratch;
    u32 initial_flags = D_80083462;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    p3 = arg3;
#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    if (initial_flags & 0x1000) {
        ((S_80170E54_0 *)arg0)->unk_9A = 0xE;
        func_8017139C();
        func_80171378();
        return;
    }

    ASM_KEEP(p1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(p3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    if (((S_80170E54_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80170E54_2 *)arg2)->unk_2C != D_80173CDC) {
#ifdef __mips__
            register void *state ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
            state = D_80173CD4;
            ASM_TAILSLOT_PIN(state);   /* MATCH pin: retail delay-slot contents depend on it */
#endif
            func_80171344();
        }
        return;
    }

    if (((S_80170E54_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80170E54_2 *)arg2)->unk_2C == D_80173CDC) {
            ((S_80170E54_0 *)arg0)->unk_9A = 0xD;
            ((S_80170E54_0 *)arg0)->unk_9B = 1;
            ((S_80170E54_0 *)arg0)->unk_8C = 0;
            ((S_80170E54_1 *)arg3)->unk_1C &= ~0x40000;
            func_80171378();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80173CD4)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80170E54_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_80171378();
            return;
        }

        ASM_KEEP(arg0);   /* MATCH pin: keeps a statement from moving across a call/branch */
        if (((S_80170E54_0 *)arg0)->unk_9A != 0xE) {
            u8 state = 0xE;

            table = D_80173C7C;
            if (((S_80170E54_2 *)arg2)->unk_2C != table) {
                (*(void * *)((u8 *)arg2 + (0x2C))) = table;
                func_80047784(arg2,
                    table[((D_80083228 + ((S_80170E54_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170E54_0 *)arg0)->unk_9A = state;
        }

        ((S_80170E54_0 *)arg0)->unk_98 &= 0xFFF3;
        if (((S_80170E54_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80173C84)) {
                return;
            }
        }

        if (((S_80170E54_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173A30(arg0, arg1, arg2, arg3);
            func_80171378();
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_80170E54_2 *)arg2)->unk_24.at00.v, ((S_80170E54_2 *)arg2)->unk_24.at01.v);
    ((S_80170E54_2 *)arg2)->unk_26 = result;

    if (((S_80170E54_1 *)arg3)->unk_6D > 0) {
        if (((S_80170E54_1 *)arg3)->unk_1C & 0x20) {
            goto special_cleanup;
        }
        if (((S_80170E54_2 *)arg2)->unk_24.at00u.v == D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(((S_80170E54_1 *)arg3)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(arg3,
                        (u8 *)((S_80170E54_3 *)D_800814A8)->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8017207C(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            ((S_80170E54_1 *)arg3)->unk_46 |= 0x4000;
            if (!(((S_80170E54_1 *)arg3)->unk_46 & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

#ifdef __mips__
        {
            static void *volatile dispatch_labels[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&ordinary_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            s32 dispatch_index;

            dispatch_index = (((S_80170E54_1 *)arg3)->unk_46 & 0x3FFF) - 1;
            if ((u32)dispatch_index >= 12) {
                goto ordinary_cleanup;
            }
            goto *D_80170808[dispatch_index];
        }
handler_case:
#else
        switch (((S_80170E54_1 *)arg3)->unk_46 & 0x3FFF) {
        case 8:
        case 9:
#endif
            if ((s16)func_80171DA0(arg0, arg1, arg2, arg3) == 0) {
                func_80171F64(arg0, arg1, arg2, arg3);
                func_80171378();
            }
            return;

#ifdef __mips__
coords_case:
#else
        case 5:
        case 6:
        case 7:
#endif
        {
            u8 *origin = D_80082E80;
            void *global;
            s32 direction;

            direction = func_800A0818(
                ((S_80170E54_2 *)arg2)->unk_24.at00.v, ((S_80170E54_2 *)arg2)->unk_24.at01.v,
                ((S_80170E54_4 *)origin)->unk_24, ((S_80170E54_4 *)origin)->unk_25,
                &scratch);
            global = D_800814A8;
            ((S_80170E54_1 *)arg3)->unk_2A = direction;
            if (((S_80170E54_5 *)global)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
            goto special_cleanup;
        }
#ifndef __mips__
        case 1:
        case 2:
        case 3:
            goto aaf_cleanup;

        case 12:
            goto special_cleanup;

        default:
            goto ordinary_cleanup;
        }
#endif

special_cleanup:
        func_800A9A0C(arg3);
        func_80171378();
        return;

aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, D_80173CCC, &D_80170E54);
        func_80171378();
        return;

ordinary_cleanup:
        func_801715F4(arg0, arg1, arg2, arg3);
        func_80171378();
        return;
    } else if (!(((S_80170E54_1 *)arg3)->unk_1C & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) || !(D_800E2970[index].flags & 2)) {
            if (!(((S_80170E54_1 *)arg3)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(((S_80170E54_2 *)arg2)->unk_24.at00.v,
                        ((S_80170E54_2 *)arg2)->unk_24.at01.v, ((S_80170E54_4 *)origin)->unk_24,
                        ((S_80170E54_4 *)origin)->unk_25) != 0) {
                    ((S_80170E54_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_80170E54_2 *)arg2)->unk_24.at00.v, ((S_80170E54_2 *)arg2)->unk_24.at01.v,
                        ((S_80170E54_4 *)origin)->unk_24, ((S_80170E54_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170E54_2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    table = D_80173C7C;
    if (((S_80170E54_2 *)arg2)->unk_2C == table) {
        return;
    }
    ASM_KEEP(arg2);   /* MATCH pin: retail basic-block layout depends on it */
    (*(void * *)((u8 *)arg2 + (0x2C))) = table;
    func_80047784(arg2,
        ((((D_80083228 + ((S_80170E54_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) + table)[0],
        0);
}
