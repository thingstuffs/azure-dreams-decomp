#include "common.h"


typedef struct {
    u32 words[6];
} Copy24;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3u16;

extern void *func_8003FC64(s32 size);
extern void func_8004491C(void *object, void *callback);
extern void func_80047784(void *object, s32 kind, s32 arg2);
extern void *func_8003DE58(void *arg0, void *arg1, Vec3u16 *out, s32 arg3);

extern s32 D_80045340;
extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern u8 D_80175978;


typedef struct S_80175D04_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x86];
    s16 unk_B2;
} S_80175D04_0;   /* arg0 in func_80175D04 */

typedef struct S_80175D04_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80175D04_1;   /* &local in func_80175D04 */

typedef struct S_80175D04_2 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80175D04_2;   /* render in func_80175D04 */

typedef struct S_80175D04_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x1C];
    s32 unk_28;
} S_80175D04_3;   /* source in func_80175D04 */

typedef struct S_80175D04_4 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u16 unk_0E;
    s32 unk_10;
    s32 unk_14;
} S_80175D04_4;   /* out in func_80175D04 */

typedef struct S_80175D04_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80175D04_5;   /* child in func_80175D04 */

void *func_80175D04(S_80175D04_0 *arg0, Copy24 *input, S_80175D04_3 *source)
{
    Copy24 local;
    Vec3u16 delta;
    u16 selector;
    s32 table_offset;
    s16 table_value;
    Copy24 *out;
    void *object;
    S_80175D04_5 *child;
    S_80175D04_2 *render;

    selector = arg0->unk_2A;
    local = *input;
    table_offset = (selector >> 8) & 0xE;

    table_value = *(s16 *)((u8 *)&D_8006CCD8 + table_offset);
    ((S_80175D04_1 *)(&local))->unk_02 +=
        (table_value * arg0->unk_B2 * 0x40) +
        (table_value * 0x20);

    table_value = *(s16 *)((u8 *)&D_8006CCE8 + table_offset);
    ((S_80175D04_1 *)(&local))->unk_06 +=
        (table_value * arg0->unk_B2 * 0x40) +
        (table_value * 0x20);

    object = func_8003FC64(0x312);
    if (object != 0) {
        (*(void * *)((u8 *)object + 0x10)) = &D_80175978;
        func_8004491C(object, &D_80045340);

        render = (*(void * *)((u8 *)object + 0xC));
        render->unk_28 = source->unk_28;
        render->unk_1E = 0x800;
        render->unk_1C = 0x800;
        render->unk_0C = 0x00808080;
        render->unk_14 |= 0xC;
        render->unk_10 |= 0x20;
        func_80047784(render, 0x47, 0);

        child = (*(void * *)((u8 *)object + 8));
        (*(Copy24 *)((u8 *)object + 0x24)) = *input;
        out = (Copy24 *)((u8 *)object + 0x20);

        delta.z = 0;
        delta.y = 0;
        delta.x = 0;
        if (func_8003DE58(source->unk_08, source, &delta, 1) != 0) {
            ((S_80175D04_4 *)out)->unk_04.at02.v += delta.x;
            child->unk_02 = ((S_80175D04_4 *)out)->unk_04.at02.v;
            ((S_80175D04_4 *)out)->unk_08.at02.v += delta.y;
            child->unk_06 = ((S_80175D04_4 *)out)->unk_08.at02.v;
            ((S_80175D04_4 *)out)->unk_0E += delta.z;
            child->unk_0A = ((S_80175D04_4 *)out)->unk_0E;
        }

        ((S_80175D04_4 *)out)->unk_10 =
            ((s32)local.words[0] - ((S_80175D04_4 *)out)->unk_04.at00.v) / 0x20;
        ((S_80175D04_4 *)out)->unk_14 =
            ((s32)local.words[1] - ((S_80175D04_4 *)out)->unk_08.at00.v) / 0x20;

        return object;
    }

    return 0;
}
