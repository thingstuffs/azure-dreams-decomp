#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80171CD4_arg0.h"
#include "records/Rec_func_80171CD4_arg1.h"


extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80172688();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174DE4[];


typedef struct S_80171CD4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171CD4_0;   /* state in func_80171CD4 */




typedef struct S_80171CD4_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171CD4_4;   /* (u8 *)state + ((S_80171CD4_0 *)state)->unk_8A.s in func_80171CD4 */

/* Advance the entity along its stored path and update movement timing. */
void func_80171CD4(void *movement, void *motion, void *entity, void *path_state) {
    void *state = path_state;
    s32 move_flags;
    s16 heading;
    s16 move_result;
    s16 x;
    s32 y;

    if (((S_80171CD4_0 *)state)->unk_71.s <= 0) {
        return;
    }

    if (((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 != 0xF) {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_90 = 0;
        ((Rec_func_80171CD4_arg1 *)motion)->unk_14 = 0;
        ((Rec_func_80171CD4_arg0 *)movement)->unk_9D = 0;
    }

    if (((S_80171CD4_0 *)state)->unk_71.u <= ((S_80171CD4_0 *)state)->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != D_80174DE4) {
        (*(u8 * *)((u8 *)entity + (0x2C))) = D_80174DE4;
        func_80047784(
            entity,
            D_80174DE4[((D_80083228 + ((S_80171CD4_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    move_flags = 0x3000;
    if (((S_80171CD4_0 *)state)->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    func_8009A3D0(x, y, move_flags);

    heading = func_800A0818(
        x,
        y,
        ((S_80171CD4_4 *)((u8 *)state + ((S_80171CD4_0 *)state)->unk_8A.s))->unk_74,
        ((S_80171CD4_4 *)((u8 *)state + ((S_80171CD4_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)movement + 0x98);
    move_result = func_8009A66C(heading, entity, state, 0x20);

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((S_80171CD4_4 *)((u8 *)state + ((S_80171CD4_0 *)state)->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((S_80171CD4_4 *)((u8 *)state + ((S_80171CD4_0 *)state)->unk_8A.s))->unk_7C;
    ((S_80171CD4_0 *)state)->unk_8A.u++;

    {
        s32 next_x = ((Rec_D_80082E80 *)entity)->unk_24;
        s32 next_y = ((Rec_D_80082E80 *)entity)->unk_25;

        if (((S_80171CD4_0 *)state)->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        func_8009A21C(next_x, next_y, move_flags);
    }

    ((S_80171CD4_0 *)state)->unk_2A = heading;
    if (move_result == 3) {
        if (!(D_80083462 & 0x80) && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            func_80172688(movement, motion, entity, state);
            ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
        } else {
            ((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 = 0xF;
            ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
        }
    } else {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 = 0xF;
        ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 0;
        return;
    }

    ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 8;
    {
        s32 step_count = ((S_80171CD4_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 8 / step_count;
        }
    }
}
