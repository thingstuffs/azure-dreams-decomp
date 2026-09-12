#include "common.h"
#include "records/Rec_D_800814A8.h"


extern void func_8004491C(void *, void *);
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800644B8(s32);

extern s32 D_80045340;
extern s32 D_800814A0;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 *D_800E3D18;


typedef struct S_800240F0_0 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
    union { s16 n; u16 n2; volatile u16 v; } unk_0C;   /* accessed as both */
    u8 pad_0E[0x2];
    union { u16 u; s16 s; } unk_10;   /* accessed as both */
    u16 unk_12;
} S_800240F0_0;   /* arg0 in func_800240F0 */

typedef struct S_800240F0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800240F0_1;   /* source in func_800240F0 */

typedef struct S_800240F0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800240F0_2;   /* arg1 in func_800240F0 */

typedef struct S_800240F0_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800240F0_3;   /* position in func_800240F0 */

typedef struct S_800240F0_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
} S_800240F0_4;   /* arg2 in func_800240F0 */


typedef struct S_800240F0_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800240F0_6;   /* ((S_800240F0_0 *)arg0)->unk_00 in func_800240F0 */

typedef struct S_800240F0_7 {
    u16 unk_00;
} S_800240F0_7;   /* ((S_800240F0_0 *)arg0)->unk_08 in func_800240F0 */

typedef struct S_800240F0_8 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800240F0_8;   /* ((S_800240F0_0 *)arg0)->unk_04 in func_800240F0 */

/* Updates an effect that follows its source, arcs to a target, then grows and brightens. */
void func_800240F0(void *effect, void *motion, void *sprite)
{
    u16 prev_state;
    u16 offset[3];
    s32 state;

    state = ((S_800240F0_0 *)effect)->unk_0C.n;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto tick;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto tick;

state_zero:
    func_8004491C((u8 *)effect - 0x20, &D_80045340);
    ((S_800240F0_0 *)effect)->unk_0C.n2 = ((S_800240F0_0 *)effect)->unk_0C.n2 + 1;
state_one:
    {
        void *source;
        source = ((S_800240F0_6 *)(((S_800240F0_0 *)effect)->unk_00))->unk_0C;
        if ((((S_800240F0_1 *)source)->unk_14 & 0x8000) ||
            func_8003DE58(((S_800240F0_1 *)source)->unk_08, source, offset, 0) != 0) {
            void *position;
            u16 source_z;

            position = ((S_800240F0_6 *)(((S_800240F0_0 *)effect)->unk_00))->unk_08;
            ((S_800240F0_2 *)motion)->unk_00.at02.v = ((S_800240F0_3 *)position)->unk_00.at02.v;
            ((S_800240F0_2 *)motion)->unk_04.at02.v = ((S_800240F0_3 *)position)->unk_04.at02.v;
            source_z = ((S_800240F0_3 *)position)->unk_0A;
            ((S_800240F0_2 *)motion)->unk_08.at02.v = source_z;

            if (!(((S_800240F0_1 *)source)->unk_14 & 0x8000)) {
                u16 offset_z;

                ((S_800240F0_2 *)motion)->unk_00.at02.v += offset[0];
                ((S_800240F0_2 *)motion)->unk_04.at02.v += offset[1];
                offset_z = ((S_800240F0_2 *)motion)->unk_08.at02.v + offset[2];
                ((S_800240F0_2 *)motion)->unk_08.at02.v = offset_z;
            } else {
                ((S_800240F0_2 *)motion)->unk_08.at02.v = source_z - 0x20;
            }
        }
    }

    if (((S_800240F0_7 *)(((S_800240F0_0 *)effect)->unk_08))->unk_00 & 0x80) {
        u16 travel_frames;

        travel_frames = 10;
        ASM_KEEP_NV(travel_frames);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        prev_state = ((S_800240F0_0 *)effect)->unk_0C.v;
        ((S_800240F0_0 *)effect)->unk_10.u = travel_frames;
        goto advance_state;
    }
    goto tick;

state_two:
    {
        u16 scale;
        scale = ((S_800240F0_4 *)sprite)->unk_1E + 0x200;
        ((S_800240F0_4 *)sprite)->unk_1E = scale;
        ((S_800240F0_4 *)sprite)->unk_1C = scale;
    }
    {
        void *position;
        position = ((S_800240F0_8 *)(((S_800240F0_0 *)effect)->unk_04))->unk_08;
        ((S_800240F0_2 *)motion)->unk_0C = ((S_800240F0_3 *)position)->unk_00.at00.v;
        ((S_800240F0_2 *)motion)->unk_10 = ((S_800240F0_3 *)position)->unk_04.at00.v;
    }
    ((S_800240F0_2 *)motion)->unk_14 = (((Rec_D_800814A8 *)D_800814A8)->unk_88.as_s16 - 0x50) << 16;

    {
        s32 angle_index;
        angle_index = (D_80083228 + ((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_s16 + 0x100) >> 7;
        if (func_8003DE58(*(void **)((angle_index & 0x1C) + (s32)D_800E3D18),
                          D_80082E80, offset, 0) != 0) {
            ((S_800240F0_2 *)motion)->unk_0C += ((s16 *)offset)[0] << 16;
            ((S_800240F0_2 *)motion)->unk_10 += ((s16 *)offset)[1] << 16;
            ((S_800240F0_2 *)motion)->unk_14 += ((s16 *)offset)[2] << 16;
        }
    }

    ((S_800240F0_2 *)motion)->unk_00.at00.v +=
        (((S_800240F0_2 *)motion)->unk_0C - ((S_800240F0_2 *)motion)->unk_00.at00.v) /
        ((S_800240F0_0 *)effect)->unk_10.s;
    ((S_800240F0_2 *)motion)->unk_04.at00.v +=
        (((S_800240F0_2 *)motion)->unk_10 - ((S_800240F0_2 *)motion)->unk_04.at00.v) /
        ((S_800240F0_0 *)effect)->unk_10.s;
    ((S_800240F0_2 *)motion)->unk_08.at00.v +=
        (((S_800240F0_2 *)motion)->unk_14 - ((S_800240F0_2 *)motion)->unk_08.at00.v) /
            ((S_800240F0_0 *)effect)->unk_10.s -
        (func_800644B8(((S_800240F0_0 *)effect)->unk_10.s * 0xAA) << 7);

    {
        u16 frames_left;
        frames_left = ((S_800240F0_0 *)effect)->unk_10.u - 1;
        ((S_800240F0_0 *)effect)->unk_10.u = frames_left;
        if ((s16)frames_left > 0) {
            goto tick;
        }
    }

    ((S_800240F0_2 *)motion)->unk_00.at00.v = ((S_800240F0_2 *)motion)->unk_0C;
    ((S_800240F0_2 *)motion)->unk_04.at00.v = ((S_800240F0_2 *)motion)->unk_10;
    ((S_800240F0_2 *)motion)->unk_08.at00.v = ((S_800240F0_2 *)motion)->unk_14;
    prev_state = ((S_800240F0_0 *)effect)->unk_0C.n2;
    ((S_800240F0_0 *)effect)->unk_10.u = state;

advance_state:
    ((S_800240F0_0 *)effect)->unk_0C.n2 = prev_state + 1;
    goto tick;

state_three:
    {
        u16 scale;
        u8 brightness;
        scale = ((S_800240F0_4 *)sprite)->unk_1E + 0x200;
        brightness = ((S_800240F0_4 *)sprite)->unk_0E + 8;
        ((S_800240F0_4 *)sprite)->unk_1E = scale;
        ((S_800240F0_4 *)sprite)->unk_1C = scale;
        ((S_800240F0_4 *)sprite)->unk_0E = brightness;
        ((S_800240F0_4 *)sprite)->unk_0D = brightness;
        ((S_800240F0_4 *)sprite)->unk_0C = brightness;
    }
    {
        u16 frames_left;
        frames_left = ((S_800240F0_0 *)effect)->unk_10.u - 1;
        ((S_800240F0_0 *)effect)->unk_10.u = frames_left;
        if ((s16)frames_left > 0) {
            goto tick;
        }
    }

    (*(u16 *)((u8 *)effect + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;
    return;

tick:
    ((S_800240F0_0 *)effect)->unk_12 = ((S_800240F0_0 *)effect)->unk_12 + 1;
}
