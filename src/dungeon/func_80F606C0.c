#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80F606C0_0_pre {
    u16 unk_00;
} S_80F606C0_0_pre;   /* the 0x2 bytes before arg0 in func_80F606C0, addressed as arg0[-1] */

typedef struct S_80F606C0_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x36];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80F606C0_0;   /* arg0 in func_80F606C0 */

typedef struct S_80F606C0_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80F606C0_1;   /* arg1 in func_80F606C0 */



/* cfail-repair: tf7-phase1-cache-v3 */
extern int   D_800814A0[];
/* Moves the effect toward its target, shrinks it, and marks completion after the countdown. */
void func_80F606C0(void *effect, S_80F606C0_1 *position, Rec_D_80082E80 *transform) {
    s16 phase;
    s32 x_delta;
    u16 scale;
    u16 frames_left;

    x_delta = ((S_80F606C0_0 *)effect)->unk_0C - position->unk_00.at02.v;
    if (x_delta < 0) {
        x_delta += 3;
    }
    position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((x_delta >> 2) << 0x10));
    position->unk_04.at00.v = (s32) (position->unk_04.at00.v + (((s32) (((S_80F606C0_0 *)effect)->unk_0E - position->unk_04.at02.v) / 4) << 0x10));
    position->unk_08.at00.v = (s32) (position->unk_08.at00.v + (((s32) (((S_80F606C0_0 *)effect)->unk_10 - position->unk_08.at02.v) / 4) << 0x10));
    func_800478B8(transform);
    phase = ((S_80F606C0_0 *)effect)->unk_4C;
    switch (phase) {                              /* irregular */
    case 0:
        scale = transform->unk_1C.at02_u16.v - 0x80;
        transform->unk_1C.at02_u16.v = scale;
        transform->unk_1C.at00_u16.v = scale;
        frames_left = ((S_80F606C0_0 *)effect)->unk_48 - 1;
        ((S_80F606C0_0 *)effect)->unk_48 = frames_left;
        if ((frames_left << 0x10) <= 0) {
            ((S_80F606C0_0 *)effect)->unk_4C = (s16) ((u16) ((S_80F606C0_0 *)effect)->unk_4C + 1);
            return;
        }
        return;
    case 1:
        ((S_80F606C0_0_pre *)effect)[-1].unk_00 = (u16) (((S_80F606C0_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
        break;
    }
}
