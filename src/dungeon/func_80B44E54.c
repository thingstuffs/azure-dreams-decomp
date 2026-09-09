#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172654_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 s; volatile u8 u; } unk_9B;   /* accessed as both */
} S_80172654_0;   /* arg0 in func_80172654 */

typedef struct S_80172654_1 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172654_1;   /* arg3 in func_80172654 */


typedef struct S_80172654_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172654_3;   /* call_a0 in func_80172654 */

typedef struct S_80172654_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172654_4;   /* arg1 in func_80172654 */

typedef struct S_80172654_5 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_80172654_5;   /* obj in func_80172654 */

typedef struct S_80172654_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
} S_80172654_6;   /* tail in func_80172654 */

/* m2c compatibility helpers used by the validated warm seed. */

s32 func_8003DE58(s32, void *, s16 *, s16);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
void func_80047784(void *, u8, s32);
void func_8009C12C(void *, void *, s16, s32);
void func_800A2B04(void *, u8, u8);
void func_800A4ACC(void *);
void func_800A56E0(s32);
void func_800AD594(void *, s32);
s32 func_800BCB04(s32, s32, s16);
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern void *D_800E3DE8;
extern u8 D_80170E70;
extern u8 D_80173F38[];
extern u8 D_80173FDC[];
extern u8 D_80175A4C[];
extern u8 D_80175A8C[];

void func_80172654(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 pos[3];
    s32 temp_s5;
    s32 temp_s6;
    s32 offset;
    s32 state;
    s32 count;
    u8 next_state;
    s32 shifted_count;
    register void *call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    void *obj;
    u8 *tail;

    state = ((S_80172654_0 *)arg0)->unk_9B.s;
    offset = (((S_80172654_1 *)arg3)->unk_2A.s >> 8) & 0xE;
    temp_s5 = *(s16 *)((u8 *)&D_8006CCD8 + offset);
    temp_s6 = *(s16 *)((u8 *)&D_8006CCE8 + offset);
    count = ((S_80172654_0 *)arg0)->unk_96.s - 1;
    ((S_80172654_0 *)arg0)->unk_96.s = count;

    if (state == 2) goto state_2;
    if (state < 3) {
        if (state == 0) goto state_0;
        if (state == 1) {
            shifted_count = count << 16;
            goto state_1;
        }
        ASM_SCHED_BARRIER(); /* MATCH: preserve the state-1 branch and shared epilogue jump. */
        goto done;
    }
    if (state == 4) goto state_4;
    if (state < 4) goto state_3;
    if (state == 0xFF) goto state_255;
    goto done;

state_0:
    call_a0 = arg3;
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172654_0 *)arg0)->unk_9B.s = 0xFF;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(call_a0, arg2, ((S_80172654_3 *)call_a0)->unk_2A, 1);
        goto done;
    }
    ((S_80172654_4 *)arg1)->unk_0C = (-temp_s5) << 17;
    ((S_80172654_4 *)arg1)->unk_10 = (-temp_s6) << 17;
    ((S_80172654_4 *)arg1)->unk_14 = 0;
    (*(void **)((u8 *)arg2 + 0x2C)) = D_80175A4C;
    func_80047784(arg2,
        D_80175A4C[((D_80083228 + ((S_80172654_1 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    next_state = ((S_80172654_0 *)arg0)->unk_9B.u;
    count = 8;
    ((S_80172654_0 *)arg0)->unk_96.s = count;
    goto store_next_state;

state_1:
    if (shifted_count > 0) goto done;
    ((S_80172654_4 *)arg1)->unk_10 = 0;
    ((S_80172654_4 *)arg1)->unk_0C = 0;
    (*(void **)((u8 *)arg2 + 0x2C)) = D_80175A8C;
    func_80047784(arg2,
        D_80175A8C[((D_80083228 + ((S_80172654_1 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    goto increment_state;

state_2:
    if (((((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 4) &&
         (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x800;
        ((S_80172654_0 *)arg0)->unk_96.s = 0x10;
        if (func_8003DE58(((Rec_D_80082E80 *)arg2)->unk_08, arg2, pos, 0) == 0) {
            pos[2] = 0;
            pos[1] = 0;
            pos[0] = 0;
        }
        obj = func_8003FD64(0x12, D_80083498);
        if (obj != NULL) {
            func_8004491C(obj, D_80173FDC);
            ((S_80172654_5 *)obj)->unk_10 = D_80173F38;
            ((S_80172654_5 *)obj)->unk_20 = ((S_80172654_4 *)arg1)->unk_00.at02.v + pos[0];
            tail = (u8 *)obj + 0x20;
            ((S_80172654_6 *)tail)->unk_02 = ((S_80172654_4 *)arg1)->unk_04.at02.v + pos[1];
            ((S_80172654_6 *)tail)->unk_04 = ((S_80172654_4 *)arg1)->unk_0A + pos[2];
            ((S_80172654_6 *)tail)->unk_08 = 0xC0C0C0;
            ((S_80172654_6 *)tail)->unk_0E = 8;
            ((S_80172654_6 *)tail)->unk_12 =
                func_800BCB04(((((Rec_D_80082E80 *)arg2)->unk_24 + temp_s5) << 6) & 0xFFC0,
                              ((((Rec_D_80082E80 *)arg2)->unk_25 + temp_s6) << 6) & 0xFFC0,
                              (s16)(((S_80172654_4 *)arg1)->unk_0A - 0x80)) -
                ((S_80172654_4 *)arg1)->unk_0A;
            ((S_80172654_6 *)tail)->unk_10 = ((S_80172654_1 *)arg3)->unk_2A.s;
            goto increment_state;
        }
        goto increment_state;
    }
    goto done;

state_3:
    if ((s16)count == 0xA) {
        func_8009C12C(arg3, arg2, ((S_80172654_1 *)arg3)->unk_2A.u, 1);
        func_800A56E0(0x813);
    }
    if (((S_80172654_0 *)arg0)->unk_96.u > 0) goto done;
    ((S_80172654_0 *)arg0)->unk_96.s = 8;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
    goto increment_state;

increment_state:
    next_state = ((S_80172654_0 *)arg0)->unk_9B.u;
store_next_state:
    next_state += 1;
    ((S_80172654_0 *)arg0)->unk_9B.s = next_state;
    goto done;

state_4:
    if ((count << 16) > 0) goto done;
    (*(void **)((u8 *)arg2 + 0x2C)) = D_80175A4C;
    func_80047784(arg2,
        D_80175A4C[((D_80083228 + ((S_80172654_1 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    ((S_80172654_0 *)arg0)->unk_96.s = state;
    ((S_80172654_0 *)arg0)->unk_9B.s = 0xFF;
    goto done;

state_255:
    ((S_80172654_4 *)arg1)->unk_0C =
        (s32)((((((Rec_D_80082E80 *)arg2)->unk_24 << 6) + 0x20) << 16) -
              ((S_80172654_4 *)arg1)->unk_00.at00.v) >> 1;
    ((S_80172654_4 *)arg1)->unk_10 =
        (s32)((((((Rec_D_80082E80 *)arg2)->unk_25 << 6) + 0x20) << 16) -
              ((S_80172654_4 *)arg1)->unk_04.at00.v) >> 1;
    if ((((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) ||
        (((S_80172654_0 *)arg0)->unk_96.u <= 0)) {
        ((S_80172654_4 *)arg1)->unk_14 = 0;
        ((S_80172654_4 *)arg1)->unk_10 = 0;
        ((S_80172654_4 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24,
                     ((Rec_D_80082E80 *)arg2)->unk_25);
        func_800AD594(arg3, 0x100);
        ((S_80172654_0 *)arg0)->unk_8C = &D_80170E70;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        if (((S_80172654_1 *)arg3)->unk_6D == 0) {
            ((S_80172654_1 *)arg3)->unk_46 &= 0x7FFF;
            goto done;
        }
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

done:
    return;
}
