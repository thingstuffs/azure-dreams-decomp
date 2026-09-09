#include "common.h"
#include "records/Rec_D_800CFCB4.h"

#ifndef NULL
#define NULL 0
#endif


extern s32 func_8009539C(void *);
extern s32 func_8009EB9C();
extern s32 func_8009F148();
extern s32 func_800C0C88();
extern s32 D_80083780[];
extern s32 D_800D09C8[];


typedef struct S_8009EF88_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009EF88_0;   /* arg2 in func_8009EF88 */

typedef struct S_8009EF88_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8009EF88_1;   /* temp_a2 in func_8009EF88 */


void func_8009EF88(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 sp18[5];
    s32 *temp_a2;
    s8 *temp_a0;
    s8 *temp_a0_2;
    u16 temp_v0_2;
    u32 temp_v0;
    s32 temp_v1;
    u8 temp_s1;

    temp_a2 = D_80083780;
    ((S_8009EF88_0 *)arg2)->unk_0C = (s32)((s32)(D_80083780[0] - ((S_8009EF88_0 *)arg2)->unk_00.at00.v) / 2);
    temp_v0 = ((S_8009EF88_1 *)temp_a2)->unk_04 - ((S_8009EF88_0 *)arg2)->unk_04.at00.v;
    ((S_8009EF88_0 *)arg2)->unk_10 = (s32)((s32)(temp_v0 + (temp_v0 >> 31)) >> 1);
    temp_v1 = ((S_8009EF88_0 *)arg2)->unk_08 + 0x200000;
    ((S_8009EF88_0 *)arg2)->unk_14 = (s32)((s32)(((S_8009EF88_1 *)temp_a2)->unk_08 - temp_v1) / 2);
    func_8009539C(arg2);
    temp_v0_2 = ((Rec_D_800CFCB4 *)arg0)->unk_6C.as_u16 - 1;
    ((Rec_D_800CFCB4 *)arg0)->unk_6C.as_u16 = temp_v0_2;
    if ((temp_v0_2 << 16) <= 0) {
        temp_s1 = ((Rec_D_800CFCB4 *)arg0)->unk_95;
        if (func_8009EB9C(arg0, arg1, arg2, arg3, sp18) != 0) {
            if (((Rec_D_800CFCB4 *)arg0)->unk_4D.as_u8 == 0x13) {
                u8 *table = (u8 *)0x80010000;
                s32 index = table[temp_s1 * 4 + 0x983] & 0x3F;
                table[index * 0x54 + 0xAC4] = 1;
                temp_a0 = ((Rec_D_800CFCB4 *)arg0)->unk_98;
                if (temp_a0 != NULL) {
                    *temp_a0 = 0;
                }
                D_800D09C8[0] = 0;
                temp_a0_2 = temp_a0;
            } else {
                (*(s32 *)((u8 *)((temp_s1 * 4)) + (0x80010980))) = 0;
                temp_a0_2 = ((Rec_D_800CFCB4 *)arg0)->unk_98;
                if (temp_a0_2 != NULL) {
                    *temp_a0_2 = 0;
                }
            }
            func_800C0C88(temp_a0_2);
            return;
        }
        ((S_8009EF88_0 *)arg2)->unk_00.at00.v = 0;
        ((S_8009EF88_0 *)arg2)->unk_04.at00.v = 0;
        ((S_8009EF88_0 *)arg2)->unk_00.at02.v = ((Rec_D_800CFCB4 *)arg0)->unk_84;
        ((S_8009EF88_0 *)arg2)->unk_04.at02.v = ((Rec_D_800CFCB4 *)arg0)->unk_86;
        func_8009F148(arg0, arg1, arg2, arg3);
    }
}

/* MECHANISM: The 0x48 frame comes from the five-word outgoing stack object and
   four held input roles plus s1. func_8009539C has a one-argument ABI: leaving
   the 0x200000 value in a1 and D_80083780 base in a2 removes the false a1->a3
   preservation copy and yields retail's exact prologue schedule and lifetimes. */
