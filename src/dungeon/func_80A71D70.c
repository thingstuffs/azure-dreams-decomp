#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80171570_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} S_80171570_0;   /* state in func_80171570 */


typedef struct S_80171570_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_80171570_2;   /* arg0 in func_80171570 */

typedef struct S_80171570_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171570_3;   /* (u8 *)state + ((S_80171570_0 *)state)->unk_8A in func_80171570 */



extern void func_80047784(void *, s16, s16);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_80171EFC(void *, s32, void *, void *);

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174138[];

/* Advances the entity along its stored path and updates movement timing. */
void func_80171570(void *action, s32 action_id, void *entity, void *move_state) {
    register void *state ASM_REG("$17") = move_state;
    s32 tile_mask;
    s16 move_result;
    s16 direction;
    s32 x;
    s32 y;
    s32 step_count;
    u8 new_x;
    u8 new_y;

    if (((S_80171570_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (((S_80171570_0 *)state)->unk_71.u <= ((S_80171570_0 *)state)->unk_8A) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != D_80174138) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_80174138;
        func_80047784(
            entity,
            D_80174138[((D_80083228 + ((S_80171570_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A3D0(x, y, tile_mask);

    direction = func_800A0818(
        x,
        y,
        ((S_80171570_3 *)((u8 *)state + ((S_80171570_0 *)state)->unk_8A))->unk_74,
        ((S_80171570_3 *)((u8 *)state + ((S_80171570_0 *)state)->unk_8A))->unk_7C,
        (u8 *)action + 0x98);
    move_result = func_8009A66C(direction, entity, state, 0x20);

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((S_80171570_3 *)((u8 *)state + ((S_80171570_0 *)state)->unk_8A))->unk_74;
    tile_mask = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((S_80171570_3 *)((u8 *)state + ((S_80171570_0 *)state)->unk_8A))->unk_7C;
    ((S_80171570_0 *)state)->unk_8A = (u16)((S_80171570_0 *)state)->unk_8A + 1;

    new_x = ((Rec_D_80082E80 *)entity)->unk_24;
    new_y = ((Rec_D_80082E80 *)entity)->unk_25;
    if (((S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A21C(new_x, new_y, tile_mask);
    ((S_80171570_0 *)state)->unk_2A = direction;

    if (move_result == 3 && !(D_80083462 & 0x80) && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
        func_80171EFC(action, action_id, entity, state);
        ((S_80171570_2 *)action)->unk_8C = 0;
    } else {
        ((S_80171570_2 *)action)->unk_9A = 0x0F;
        ((S_80171570_2 *)action)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_80171570_2 *)action)->unk_96 = 0;
        return;
    }

    ((S_80171570_2 *)action)->unk_96 = 8;
    step_count = ((S_80171570_0 *)state)->unk_71.u;
    if (step_count > 0) {
        ((S_80171570_2 *)action)->unk_96 = 8 / step_count;
    }
}
