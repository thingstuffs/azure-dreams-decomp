#include "common.h"

extern void func_8003DB94(void *, void *, s32);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, s32);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800D8FFC(void);
extern void func_800D9028(void);
extern void func_800D904C(void);
extern void func_800D92C0(void *, void *, void *, void *);
extern void func_800DA660(void *, void *, void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern u16 D_80083462;
extern void *D_800E262C[];
extern s8 D_800E2970[];


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;


typedef struct S_800D8C64_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_800D8C64_0;   /* arg0 in func_800D8C64 */

typedef struct S_800D8C64_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_800D8C64_1;   /* arg3 in func_800D8C64 */

typedef struct S_800D8C64_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_800D8C64_2;   /* arg2 in func_800D8C64 */

typedef struct S_800D8C64_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800D8C64_3;   /* arg1 in func_800D8C64 */

typedef struct S_800D8C64_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800D8C64_4;   /* origin in func_800D8C64 */

void func_800D8C64(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void **table;
    s32 result;
    s32 scratch;

    if (D_80083462 & 0x1000) {
        ((S_800D8C64_0 *)arg0)->unk_9A = 0xE;
        func_800D904C();
        func_800D9028();
        return;
    }

    if (((S_800D8C64_1 *)arg3)->unk_25 == 0) {
        void *current;
        u32 globalPage;

        func_800AA79C(arg0, arg1, arg2, arg3);
        current = ((S_800D8C64_2 *)arg2)->unk_2C;
        table = D_800E262C;
        if (current != table) {
            globalPage = 0x80080000;
            ASM_KEEP(globalPage);   /* MATCH pin: retail delay-slot contents depend on it */
            ((S_800D8C64_2 *)arg2)->unk_2C = table;
            func_800D8FFC();
        }
        return;
    }

    if (((S_800D8C64_1 *)arg3)->unk_1C & 0x200) {
        if (((S_800D8C64_2 *)arg2)->unk_2C == D_800E262C) {
            ((S_800D8C64_0 *)arg0)->unk_9A = 0xD;
            ((S_800D8C64_0 *)arg0)->unk_9B = 1;
            ((S_800D8C64_0 *)arg0)->unk_8C = 0;
            ((S_800D8C64_1 *)arg3)->unk_1C &= ~0x40000;
            func_800D9028();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, 0)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_800D8C64_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_800D9028();
            return;
        }

        if (((S_800D8C64_0 *)arg0)->unk_9A != 0xE) {
            u8 state = 0xE;

            table = D_800E262C;
            if (((S_800D8C64_2 *)arg2)->unk_2C != table) {
                (*(void * *)((u8 *)arg2 + (0x2C))) = table;
                func_8003DB94(arg2,
                    *(void **)((u8 *)table +
                        (((D_80083228 + ((S_800D8C64_1 *)arg3)->unk_2A + 0x100) >> 7) & 0x1C)),
                    0);
            }
            ((S_800D8C64_0 *)arg0)->unk_9A = state;
        }

        ((S_800D8C64_0 *)arg0)->unk_98 &= 0xFFF3;
        if (((S_800D8C64_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0)) {
                return;
            }
        }

        if (((S_800D8C64_1 *)arg3)->unk_1C & 0x80000) {
            ((S_800D8C64_0 *)arg0)->unk_90 = 0;
            ((S_800D8C64_0 *)arg0)->unk_98 &= 0xFFFE;
            ((S_800D8C64_3 *)arg1)->unk_14 = 0;
            func_800AA888(arg0, arg1, arg2, arg3);
            func_800DA660(arg0, arg1, arg2, arg3);
            func_800D9028();
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_800D8C64_2 *)arg2)->unk_24, ((S_800D8C64_2 *)arg2)->unk_25);
    ((S_800D8C64_2 *)arg2)->unk_26 = result;

    if (((S_800D8C64_1 *)arg3)->unk_6D > 0) {
        if (((S_800D8C64_1 *)arg3)->unk_1C & 0x20) {
            func_800A9A0C(arg3);
            func_800D9028();
            return;
        }
        func_800D92C0(arg0, arg1, arg2, arg3);
        func_800D9028();
        return;
    }

    if (!(((S_800D8C64_1 *)arg3)->unk_1C & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((S_800D8C64_1 *)arg3)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(((S_800D8C64_2 *)arg2)->unk_24,
                        ((S_800D8C64_2 *)arg2)->unk_25, ((S_800D8C64_4 *)origin)->unk_24,
                        ((S_800D8C64_4 *)origin)->unk_25) != 0) {
                    ((S_800D8C64_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_800D8C64_2 *)arg2)->unk_24, ((S_800D8C64_2 *)arg2)->unk_25,
                        ((S_800D8C64_4 *)origin)->unk_24, ((S_800D8C64_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_800D8C64_2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    table = D_800E262C;
    if (((S_800D8C64_2 *)arg2)->unk_2C == table) {
        return;
    }
    if (((S_800D8C64_0 *)arg0)->unk_98 & 1) {
        return;
    }
    (*(void * *)((u8 *)arg2 + (0x2C))) = table;
    func_8003DB94(arg2,
        *(void **)((u8 *)table +
            (((D_80083228 + ((S_800D8C64_1 *)arg3)->unk_2A + 0x100) >> 7) & 0x1C)),
        0);
}
