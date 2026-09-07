#include "common.h"

typedef struct S_80173E00_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x26];
    u8 * unk_2C;
} S_80173E00_0;   /* arg2 in func_80173E00 */

typedef struct S_80173E00_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_80173E00_1;   /* arg3 in func_80173E00 */

typedef struct S_80173E00_2 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
} S_80173E00_2;   /* arg0 in func_80173E00 */



extern void func_80047784(void *, u8, s32);
extern s32 func_800AC82C(s32, s32, void *, void *);
extern s32 func_800AD9B4(void *, void *);

extern s16 D_80083228;
extern u8 D_801714D4;
extern u8 D_801740E0[];
extern u8 D_801740E8[];
extern u8 D_80174158[];

/* Updates the directional sprite state and signals the controller after the actor update. */
void func_80173E00(s32 controller, s32 update_arg, void *sprite, void *actor)
{
    u8 *direction_table;

    direction_table = ((S_80173E00_0 *)sprite)->unk_2C;
    if (direction_table == D_801740E0) {
        if (((S_80173E00_0 *)sprite)->unk_04 == 0x103) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801740E8;
            func_80047784(
                sprite,
                D_801740E8[
                    ((D_80083228 + ((S_80173E00_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        goto update_actor;
    }
    if (direction_table != D_801740E8) {
        goto update_actor;
    }
    if (((S_80173E00_0 *)sprite)->unk_04 != 0x103) {
        goto update_actor;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801740E0;
    func_80047784(
        sprite,
        D_801740E0[
            ((D_80083228 + ((S_80173E00_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);

update_actor:
    if (func_800AC82C(controller, update_arg, sprite, actor) != 0) {
        if ((func_800AD9B4(sprite, actor) << 16) > 0) {
            ((S_80173E00_2 *)controller)->unk_8C = &D_801714D4;
        }
    } else if ((((S_80173E00_0 *)sprite)->unk_2C == D_80174158) &&
               !(((S_80173E00_1 *)actor)->unk_1C & 0x208)) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801740E0;
        func_80047784(
            sprite,
            D_801740E0[((D_80083228 + ((S_80173E00_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
}

/* MECHANISM: Four call-live arguments naturally occupy s2/s3/s0/s1 and make
   the 0x28 frame; the apparent callees are local CFG joins. Duplicated direct
   E0/E8 update arms cross-jump into one suffix with a1-held byte-table bases. */
