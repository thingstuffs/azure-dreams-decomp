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

/* Creates an object with a source-adjusted position and motion toward a directional target. */
void *func_80175D04(S_80175D04_0 *actor, Copy24 *start_pos, S_80175D04_3 *source)
{
    Copy24 target_pos;
    Vec3u16 source_offset;
    u16 direction_bits;
    s32 direction_offset;
    s16 axis_step;
    Copy24 *motion;
    void *object;
    S_80175D04_5 *child_pos;
    S_80175D04_2 *render;

    direction_bits = actor->unk_2A;
    target_pos = *start_pos;
    direction_offset = (direction_bits >> 8) & 0xE;

    axis_step = *(s16 *)((u8 *)&D_8006CCD8 + direction_offset);
    ((S_80175D04_1 *)(&target_pos))->unk_02 +=
        (axis_step * actor->unk_B2 * 0x40) +
        (axis_step * 0x20);

    axis_step = *(s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    ((S_80175D04_1 *)(&target_pos))->unk_06 +=
        (axis_step * actor->unk_B2 * 0x40) +
        (axis_step * 0x20);

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

        child_pos = (*(void * *)((u8 *)object + 8));
        (*(Copy24 *)((u8 *)object + 0x24)) = *start_pos;
        motion = (Copy24 *)((u8 *)object + 0x20);

        source_offset.z = 0;
        source_offset.y = 0;
        source_offset.x = 0;
        if (func_8003DE58(source->unk_08, source, &source_offset, 1) != 0) {
            ((S_80175D04_4 *)motion)->unk_04.at02.v += source_offset.x;
            child_pos->unk_02 = ((S_80175D04_4 *)motion)->unk_04.at02.v;
            ((S_80175D04_4 *)motion)->unk_08.at02.v += source_offset.y;
            child_pos->unk_06 = ((S_80175D04_4 *)motion)->unk_08.at02.v;
            ((S_80175D04_4 *)motion)->unk_0E += source_offset.z;
            child_pos->unk_0A = ((S_80175D04_4 *)motion)->unk_0E;
        }

        ((S_80175D04_4 *)motion)->unk_10 =
            ((s32)target_pos.words[0] - ((S_80175D04_4 *)motion)->unk_04.at00.v) / 0x20;
        ((S_80175D04_4 *)motion)->unk_14 =
            ((s32)target_pos.words[1] - ((S_80175D04_4 *)motion)->unk_08.at00.v) / 0x20;

        return object;
    }

    return 0;
}
