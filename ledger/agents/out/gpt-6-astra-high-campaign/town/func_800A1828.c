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


/* Updates motion toward the target and resolves the entity when its countdown expires. */
void func_8009EF88(void *entity, s32 context, void *motion, s32 mode) {
    s32 result[5];
    s32 *target_pos;
    s8 *linked_flag;
    s8 *clear_flag;
    u16 ticks_left;
    u32 delta_y;
    s32 offset_z;
    u8 slot;

    target_pos = D_80083780;
    ((S_8009EF88_0 *)motion)->unk_0C = (s32)((s32)(D_80083780[0] - ((S_8009EF88_0 *)motion)->unk_00.at00.v) / 2);
    delta_y = ((S_8009EF88_1 *)target_pos)->unk_04 - ((S_8009EF88_0 *)motion)->unk_04.at00.v;
    ((S_8009EF88_0 *)motion)->unk_10 = (s32)((s32)(delta_y + (delta_y >> 31)) >> 1);
    offset_z = ((S_8009EF88_0 *)motion)->unk_08 + 0x200000;
    ((S_8009EF88_0 *)motion)->unk_14 = (s32)((s32)(((S_8009EF88_1 *)target_pos)->unk_08 - offset_z) / 2);
    func_8009539C(motion);
    ticks_left = ((Rec_D_800CFCB4 *)entity)->unk_6C.as_u16 - 1;
    ((Rec_D_800CFCB4 *)entity)->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        slot = ((Rec_D_800CFCB4 *)entity)->unk_95;
        if (func_8009EB9C(entity, context, motion, mode, result) != 0) {
            if (((Rec_D_800CFCB4 *)entity)->unk_4D.as_u8 == 0x13) {
                u8 *state_table = (u8 *)0x80010000;
                s32 record_index = state_table[slot * 4 + 0x983] & 0x3F;
                state_table[record_index * 0x54 + 0xAC4] = 1;
                linked_flag = ((Rec_D_800CFCB4 *)entity)->unk_98;
                if (linked_flag != NULL) {
                    *linked_flag = 0;
                }
                D_800D09C8[0] = 0;
                clear_flag = linked_flag;
            } else {
                (*(s32 *)((u8 *)((slot * 4)) + (0x80010980))) = 0;
                clear_flag = ((Rec_D_800CFCB4 *)entity)->unk_98;
                if (clear_flag != NULL) {
                    *clear_flag = 0;
                }
            }
            func_800C0C88(clear_flag);
            return;
        }
        ((S_8009EF88_0 *)motion)->unk_00.at00.v = 0;
        ((S_8009EF88_0 *)motion)->unk_04.at00.v = 0;
        ((S_8009EF88_0 *)motion)->unk_00.at02.v = ((Rec_D_800CFCB4 *)entity)->unk_84;
        ((S_8009EF88_0 *)motion)->unk_04.at02.v = ((Rec_D_800CFCB4 *)entity)->unk_86;
        func_8009F148(entity, context, motion, mode);
    }
}
