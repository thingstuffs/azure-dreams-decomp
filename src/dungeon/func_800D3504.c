#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800AA258_arg2.h"

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
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xE;
        func_800D904C();
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        void *current;
        u32 globalPage;

        func_800AA79C(arg0, arg1, arg2, arg3);
        current = ((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv;
        table = D_800E262C;
        if (current != table) {
            globalPage = 0x80080000;
            ASM_KEEP(globalPage);   /* MATCH pin: retail delay-slot contents depend on it */
            ((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv = table;
            func_800D8FFC();
        }
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x200) {
        if (((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv == D_800E262C) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, 0)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 != 0xE) {
            u8 state = 0xE;

            table = D_800E262C;
            if (((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv != table) {
                (*(void * *)((u8 *)arg2 + (0x2C))) = table;
                func_8003DB94(arg2,
                    *(void **)((u8 *)table +
                        (((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 7) & 0x1C)),
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = state;
        }

        ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 &= 0xFFF3;
        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0)) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_90.at00_s32.v = 0;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 &= 0xFFFE;
            ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
            func_800AA888(arg0, arg1, arg2, arg3);
            func_800DA660(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((Rec_func_800AA258_arg2 *)arg2)->unk_24, ((Rec_func_800AA258_arg2 *)arg2)->unk_25);
    ((Rec_func_800AA258_arg2 *)arg2)->unk_26.as_u8 = result;

    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x20) {
            func_800A9A0C(arg3);
            return;
        }
        func_800D92C0(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(((Rec_func_800AA258_arg2 *)arg2)->unk_24,
                        ((Rec_func_800AA258_arg2 *)arg2)->unk_25, ((S_800D8C64_4 *)origin)->unk_24,
                        ((S_800D8C64_4 *)origin)->unk_25) != 0) {
                    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
                        ((Rec_func_800AA258_arg2 *)arg2)->unk_24, ((Rec_func_800AA258_arg2 *)arg2)->unk_25,
                        ((S_800D8C64_4 *)origin)->unk_24, ((S_800D8C64_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    table = D_800E262C;
    if (((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv == table) {
        return;
    }
    if (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 1) {
        return;
    }
    (*(void * *)((u8 *)arg2 + (0x2C))) = table;
    func_8003DB94(arg2,
        *(void **)((u8 *)table +
            (((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 7) & 0x1C)),
        0);
}
