#include "common.h"
#include "records/Rec_D_800E3D7C.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800644B8(s32 arg0);
extern s32 func_80064584(s32 arg0);
extern void func_80099754(void *arg0);
extern s32 D_80098690;

typedef struct S_80098764_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x1E];
    s16 unk_30;
    s16 unk_32;
} S_80098764_0;   /* arg0 in func_80098764 */


/* Interpolate the position toward an angle-based offset until the countdown expires. */
void func_80098764(void *motion, Rec_D_800E3D7C *position) {
    u16 ticks_left;
    s32 old_y;

    ticks_left = ((S_80098764_0 *)motion)->unk_0A - 1;
    ((S_80098764_0 *)motion)->unk_0A = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        position->unk_00.at00_s32.v =
            ((func_800644B8(((S_80098764_0 *)motion)->unk_10) << 9)
             + (((S_80098764_0 *)motion)->unk_30 << 0x10)
             + position->unk_00.at00_s32.v) / 2;
        position->unk_04.at00_s32.v =
            ((func_80064584(((S_80098764_0 *)motion)->unk_10) << 9)
             + (((S_80098764_0 *)motion)->unk_32 << 0x10)
             + (old_y = position->unk_04.at00_s32.v)) / 2;
        return;
    }
    func_80099754(position);
    ((S_80098764_0 *)motion)->unk_0A = 7;
    ((S_80098764_0 *)motion)->unk_04 = &D_80098690;
}
