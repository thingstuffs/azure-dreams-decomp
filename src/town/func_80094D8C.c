#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800924EC_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800924EC_1;   /* state in func_800924EC */


#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80033B2C(s32);
extern void func_80094088(void *, void *, s32);
extern void func_800942B0(void *, void *, s32);
extern void func_80094378(void *, void *, s32);
extern void func_80094474(void *, void *, s32);
extern void func_800944BC(void *, void *, s32);
extern void func_8009451C(void *, void *, s32);
extern void func_80094C1C(void *);
extern void func_80095094(void *);
extern s32 func_8009567C(void *);
extern s32 func_80095840(void *, void *);
extern s16 func_80095978(void *, void *);
extern void func_80095A94(void *, s16, void *);
extern void func_80095C80(void *);

extern u8 D_80083160[];
extern s32 D_800CFCB4;
extern u8 D_800CFCEF;
extern u8 D_800FE488[];

void func_800924EC(void *arg0, void *arg1, s32 arg2)
{
    u8 *state = D_80083160;
    s16 value;
    s32 state_flags;
    s32 result;

    func_80095C80(arg1);
    func_80095094(arg1);
    value = func_80095978(arg1, D_800FE488);
    if ((value - ((Rec_D_800E3D7C *)arg1)->unk_08.at02_s16.v) >= 4)
    {
        if (D_800CFCEF == 0)
        {
            func_80094378(arg0, arg1, arg2);
            goto block_end;
        }
    }
    else if (D_800CFCEF == 0)
    {
        func_80095A94(arg1, value, D_800FE488);
    }

    state_flags = ((S_800924EC_1 *)state)->unk_10;
    if (state_flags & 0x10)
    {
        func_800942B0(arg0, arg1, arg2);
        goto block_end;
    }
    if (state_flags & 0x40)
    {
        result = func_80095840(arg0, &D_800CFCB4);
        if (result != 0)
        {
            if (result == 2)
            {
                func_8009451C(arg0, arg1, arg2);
                goto block_end;
            }
            func_800944BC(arg0, arg1, arg2);
            goto block_end;
        }
        if (func_80033B2C(0xA4) != 0)
        {
            func_80094088(arg0, arg1, arg2);
            goto block_end;
        }
    }
    else
    {
        if (((S_800924EC_1 *)state)->unk_08 & 0xF000)
        {
            func_80094C1C(arg0);
            if (func_8009567C(&D_800CFCB4) > 0)
            {
                goto block_end;
            }
        }
        func_80094474(arg0, arg1, arg2);
    }

block_end:
    return;
}

/* MECHANISM: The state base is held and the work base is first materialized at its call,
   producing the five saved registers and 0x28 frame; 0x80092674 is a local epilogue.
   The one-argument func_80094C1C ABI and reused state flags preserve the retail CFG. */
