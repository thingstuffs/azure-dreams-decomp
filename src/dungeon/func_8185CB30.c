#include "common.h"
#include "records/Rec_D_80082E80.h"




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8002421C();
extern M2C_UNK func_8003DB94();
extern M2C_UNK func_800478B8();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s16 D_80083160[];
extern u8 D_800DEAE0[];

typedef struct S_8185CB30_0 {
    void * unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x10];
    u16 unk_1C;
    s16 unk_1E;
    u16 unk_20;
    u16 unk_22;
    s16 unk_24;
} S_8185CB30_0;   /* arg0 in func_8185CB30 */

typedef struct S_8185CB30_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8185CB30_1;   /* temp_v1 in func_8185CB30 */

typedef struct S_8185CB30_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8185CB30_2;   /* arg1 in func_8185CB30 */


/* Advance expanding spiral motion and update the moving object. */
void func_8185CB30(S_8185CB30_0 *motion, S_8185CB30_2 *position, Rec_D_80082E80 *object)
{
    s16 next_angle;
    u16 cycle_tick;
    u16 next_tick;
    s16 *angle_table;
    S_8185CB30_1 *owner;

    owner = motion->unk_00;
    owner->unk_14 = (u16)(owner->unk_14 + 1);
    angle_table = D_80083160;
    cycle_tick = motion->unk_22;
    next_tick = cycle_tick + 1;
    motion->unk_22 = next_tick;
    if ((s16)next_tick >= 8) {
        motion->unk_22 = (u16)(cycle_tick - 7);
    }
    if ((s16)motion->unk_22 == motion->unk_24) {
        func_8002421C(motion->unk_00, position);
    }
    if (motion->unk_1E < 0xC1) {
        motion->unk_1E = (s16)((u16)motion->unk_1E + 8);
    }
    next_angle = motion->unk_1C + (u16)motion->unk_1E;
    motion->unk_1C = (u16)next_angle;
    motion->unk_1C = (u16)(next_angle % 0x1000);
    motion->unk_20 = (u16)(motion->unk_20 + 4);
    position->unk_02 =
        (s16)(motion->unk_06 +
              ((s32)((func_800644B8((s16)motion->unk_1C) >> 4) *
                     (s16)motion->unk_20) >> 8));
    position->unk_06 =
        (s16)(motion->unk_0A +
              ((s32)((func_80064584((s16)motion->unk_1C) >> 4) *
                     (s16)motion->unk_20) >> 8));
    object->unk_1A.as_s16 =
        (s16)((s32)(0 - ((func_80064584((s16)motion->unk_1C -
                                      angle_table[100]) >> 4) << 8)) >> 8);
    func_800478B8(object);
    if (object->unk_14.at00_u16.v & 0x6000) {
        func_8003DB94(object, D_800DEAE0, 0);
    }
}
