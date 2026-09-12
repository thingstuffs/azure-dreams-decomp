#include "common.h"
#include "records/Rec_D_80082E80.h"


extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80171D3C();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80173C74[];


typedef struct S_8017139C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8017139C_0;   /* state in func_8017139C */


typedef struct S_8017139C_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    u8 unk_9A;
} S_8017139C_2;   /* arg0 in func_8017139C */

typedef struct S_8017139C_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8017139C_3;   /* (u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s in func_8017139C */

/* Advances the entity along its stored path and updates movement state and timing. */
void func_8017139C(void *controller, void *context, void *entity, void *path_state)
{
    register void *state ASM_REG("$17") = path_state;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 move_flags;
    s16 direction;
    s16 move_result;
    s32 x;
    s32 y;
    register u16 control_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    if (((S_8017139C_0 *)state)->unk_71.s <= 0) {
        return;
    }

    if (((S_8017139C_0 *)state)->unk_71.u <= ((S_8017139C_0 *)state)->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != D_80173C74) {
        (*(u8 * *)((u8 *)entity + (0x2C))) = D_80173C74;
        func_80047784(
            entity,
            D_80173C74[((D_80083228 + ((S_8017139C_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    move_flags = 0x3000;
    if (((S_8017139C_0 *)state)->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    func_8009A3D0(x, y, move_flags);

    direction = func_800A0818(
        x,
        y,
        ((S_8017139C_3 *)((u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s))->unk_74,
        ((S_8017139C_3 *)((u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)controller + 0x98);
    move_result = func_8009A66C(direction, entity, state, 0x20);

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((S_8017139C_3 *)((u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((S_8017139C_3 *)((u8 *)state + ((S_8017139C_0 *)state)->unk_8A.s))->unk_7C;
    ((S_8017139C_0 *)state)->unk_8A.u++;

    {
        s32 next_x = ((Rec_D_80082E80 *)entity)->unk_24;
        s32 next_y = ((Rec_D_80082E80 *)entity)->unk_25;

        if (((S_8017139C_0 *)state)->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        func_8009A21C(next_x, next_y, move_flags);
    }

    ((S_8017139C_0 *)state)->unk_2A = direction;
    if (move_result == 3) {
        if (!(D_80083462 & 0x80) && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            func_80171D3C(controller, context, entity, state);
            ((S_8017139C_2 *)controller)->unk_8C = 0;
        } else {
            ((S_8017139C_2 *)controller)->unk_9A = 0xF;
            ((S_8017139C_2 *)controller)->unk_8C = 0;
        }
    } else {
        control_flags = ((S_8017139C_2 *)controller)->unk_98;
        ((S_8017139C_2 *)controller)->unk_9A = 0xF;
        control_flags &= ~8;
        ((S_8017139C_2 *)controller)->unk_98 = control_flags;
        ASM_KEEP(control_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_8017139C_2 *)controller)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_8017139C_2 *)controller)->unk_96 = 0;
        return;
    }

    ((S_8017139C_2 *)controller)->unk_96 = 8;
    {
        s32 step_count = ((S_8017139C_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((S_8017139C_2 *)controller)->unk_96 = 8 / step_count;
        }
    }
}
