#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_8017360C_arg0.h"






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

    direction_table = ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pu8;
    if (direction_table == D_801740E0) {
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_04 == 0x103) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801740E8;
            func_80047784(
                sprite,
                D_801740E8[
                    ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
        }
        goto update_actor;
    }
    if (direction_table != D_801740E8) {
        goto update_actor;
    }
    if (((Rec_func_800AA258_arg2 *)sprite)->unk_04 != 0x103) {
        goto update_actor;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801740E0;
    func_80047784(
        sprite,
        D_801740E0[
            ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);

update_actor:
    if (func_800AC82C(controller, update_arg, sprite, actor) != 0) {
        if ((func_800AD9B4(sprite, actor) << 16) > 0) {
            ((Rec_func_8017360C_arg0 *)controller)->unk_8C.as_pu8 = &D_801714D4;
        }
    } else if ((((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pu8 == D_80174158) &&
               !(((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x208)) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801740E0;
        func_80047784(
            sprite,
            D_801740E0[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
    }
}

/* MECHANISM: Four call-live arguments naturally occupy s2/s3/s0/s1 and make
   the 0x28 frame; the apparent callees are local CFG joins. Duplicated direct
   E0/E8 update arms cross-jump into one suffix with a1-held byte-table bases. */
