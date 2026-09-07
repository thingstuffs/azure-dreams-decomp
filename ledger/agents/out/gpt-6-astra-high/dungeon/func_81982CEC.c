#include "common.h"

typedef struct S_800244EC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x14];
    s32 unk_28;
} S_800244EC_0;   /* obj in func_800244EC */

typedef struct S_800244EC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_800244EC_1;   /* part in func_800244EC */

typedef struct S_800244EC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800244EC_2;   /* arg0 in func_800244EC */


#define NULL 0

extern void *func_8003FC64(s32);
extern s32 func_800B835C(void *, void *, s32, s32);
extern s32 D_8002432C;
extern s32 D_800269D4;
extern s32 D_800269FC;
extern s32 D_800DF31C;

/* Allocate and initialize a two-part object and return its payload pointer. */
void *func_800244EC(S_800244EC_2 *source_part, s32 offset)
{
    s32 rect[2];
    s32 rect_size;
    void *obj;
    S_800244EC_1 *part;
    void *result;

    obj = func_8003FC64(2);
    if (obj != NULL) {
        rect[0] = 0x01000340;
        rect_size = 0x200020;
        rect[1] = rect_size;
        func_800B835C(&D_800DF31C, rect, 1, 0);
        rect[0] = 0x01200340;
        rect[1] = rect_size;
        func_800B835C(&D_800269D4, rect, 1, 0);
        part = ((S_800244EC_0 *)obj)->unk_08;
        ((S_800244EC_0 *)obj)->unk_10 = &D_8002432C;
        part->unk_02 = source_part->unk_02;
        part->unk_06 = source_part->unk_06;
        part->unk_08.at02.v = source_part->unk_0A;
        part = ((S_800244EC_0 *)obj)->unk_0C;
        part->unk_08.at00.v = &D_800269FC;
        part->unk_1E = 0xC00;
        part->unk_1C = 0xC00;
        ((S_800244EC_0 *)obj)->unk_28 = offset - 0x20;
    }
    result = NULL;
    if (obj != NULL) {
        result = (u8 *)obj + 0x20;
    }
    return result;
}
