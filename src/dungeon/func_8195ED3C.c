#include "common.h"

typedef struct S_8195ED3C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_8195ED3C_0;   /* obj in func_8195ED3C */

typedef struct S_8195ED3C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_8195ED3C_1;   /* part in func_8195ED3C */

typedef struct S_8195ED3C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8195ED3C_2;   /* arg0 in func_8195ED3C */


#define NULL 0

extern void *func_8003FC64(s32);
extern s32 func_800B835C(void *, void *, s32, s32);
extern s32 D_80024388;
extern s32 D_80027380;
extern s32 D_800273B0;
extern s32 D_800DF334;

void *func_8195ED3C(S_8195ED3C_2 *arg0, s32 arg1)
{
    s32 rect[2];
    s32 common;
    void *obj;
    S_8195ED3C_1 *part;
    void *result;

    obj = func_8003FC64(2);
    if (obj != NULL) {
        rect[0] = 0x01000340;
        common = 0x200020;
        rect[1] = common;
        func_800B835C(&D_800DF334, rect, 1, 0);
        rect[0] = 0x01000360;
        rect[1] = common;
        func_800B835C(&D_80027380, rect, 1, 0);
        part = ((S_8195ED3C_0 *)obj)->unk_08;
        ((S_8195ED3C_0 *)obj)->unk_10 = &D_80024388;
        part->unk_02 = arg0->unk_02;
        part->unk_06 = arg0->unk_06;
        part->unk_08.at02.v = arg0->unk_0A;
        part = ((S_8195ED3C_0 *)obj)->unk_0C;
        part->unk_08.at00.v = &D_800273B0;
        part->unk_1E = 0xC00;
        part->unk_1C = 0xC00;
        ((S_8195ED3C_0 *)obj)->unk_2C = arg1 - 0x20;
    }
    result = NULL;
    if (obj != NULL) {
        result = (u8 *)obj + 0x20;
    }
    return result;
}
