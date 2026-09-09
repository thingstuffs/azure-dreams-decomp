#include "common.h"
#include "records/Rec_D_80082E80.h"


extern void func_8003DB94(void *, void *, s32);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800D9820(void *, s32, void *, void *);

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800E260C[];


typedef struct S_800D904C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} S_800D904C_0;   /* state in func_800D904C */


typedef struct S_800D904C_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800D904C_2;   /* entry in func_800D904C */

typedef struct S_800D904C_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_800D904C_3;   /* arg0 in func_800D904C */

typedef struct S_800D904C_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800D904C_4;   /* (u8 *)state + ((S_800D904C_0 *)state)->unk_8A in func_800D904C */

/* Advance the actor along its queued path and update movement timing. */
void func_800D904C(void *action, s32 action_id, void *actor, void *move_state)
{
    register void *state ASM_REG("$17") = move_state;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *anim_table;
    s32 tile_mask;
    s16 direction;
    s16 move_result;
    s32 old_x;
    s32 old_y;
    s32 step_count;
    void *step;

    if ((((S_800D904C_0 *)state)->unk_71.s > 0) &&
        ((s32)((S_800D904C_0 *)state)->unk_71.u > ((S_800D904C_0 *)state)->unk_8A)) {
        anim_table = ((Rec_D_80082E80 *)actor)->unk_2C.as_pv;
        if (anim_table != D_800E260C) {
            void *anim_slot;

            (*(void * *)((u8 *)actor + (0x2C))) = D_800E260C;
            anim_slot = D_800E260C +
                (((D_80083228 + ((S_800D904C_0 *)state)->unk_2A + 0x100) >> 7) & 0x1C);
            func_8003DB94(actor, *(void **)anim_slot, 0);
        } else if (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x6000) {
            func_8003DB94(
                actor,
                *(void **)(D_800E260C +
                    (((D_80083228 + ((S_800D904C_0 *)state)->unk_2A + 0x100) >> 7) & 0x1C)),
                0);
        }

        old_x = ((Rec_D_80082E80 *)actor)->unk_24;
        old_y = ((Rec_D_80082E80 *)actor)->unk_25;
        tile_mask = 0x3000;
        if (((S_800D904C_0 *)state)->unk_1C & 0x2000) {
            tile_mask = 0x300;
        }
        func_8009A3D0(old_x, old_y, tile_mask);

        step = (u8 *)state + ((S_800D904C_0 *)state)->unk_8A;
        direction = func_800A0818(old_x, old_y,
                                    ((S_800D904C_2 *)step)->unk_74,
                                    ((S_800D904C_2 *)step)->unk_7C,
                                    (u8 *)action + 0x98);
        move_result = func_8009A66C(direction, actor, state, 0x20);

        ((Rec_D_80082E80 *)actor)->unk_24 =
            ((S_800D904C_4 *)((u8 *)state + ((S_800D904C_0 *)state)->unk_8A))->unk_74;
        tile_mask = 0x3000;
        ((Rec_D_80082E80 *)actor)->unk_25 =
            ((S_800D904C_4 *)((u8 *)state + ((S_800D904C_0 *)state)->unk_8A))->unk_7C;
        ((S_800D904C_0 *)state)->unk_8A = (u16)((S_800D904C_0 *)state)->unk_8A + 1;

        {
            s32 new_x = ((Rec_D_80082E80 *)actor)->unk_24;
            s32 new_y = ((Rec_D_80082E80 *)actor)->unk_25;
            if (((S_800D904C_0 *)state)->unk_1C & 0x2000) {
                tile_mask = 0x300;
            }
            func_8009A21C(new_x, new_y, tile_mask);
        }

        ((S_800D904C_0 *)state)->unk_2A = direction;
        if ((move_result == 3) &&
            ((D_80083462 & 0x80) || (((Rec_D_80082E80 *)actor)->unk_14.at00_u16.v & 0x8000))) {
            ((S_800D904C_3 *)action)->unk_9A = 0xF;
        } else {
            func_800D9820(action, action_id, actor, state);
        }
        ((S_800D904C_3 *)action)->unk_8C = 0;
        (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
        if (D_80083462 & 0x80) {
            ((S_800D904C_3 *)action)->unk_96 = 0;
            return;
        }

        ((S_800D904C_3 *)action)->unk_96 = 8;
        step_count = ((S_800D904C_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((S_800D904C_3 *)action)->unk_96 = 8 / step_count;
        }
    }
}
