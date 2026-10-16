/* Relink of matched dungeon/func_809A2A14; every changed retail word is a paired relocation. */
#define D_801710EC D_80153FA4
#define D_80175EA0 D_80157C90
#define D_80175EC0 D_80157CB0
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80157078(void *, s32, void *, void *);

extern s32 D_80153FA4;
extern u8 D_80157C90[];
extern u8 D_80157CB0[];


typedef struct S_80174214_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80174214_0;   /* arg0 in func_80156D18 */


typedef struct S_80174214_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174214_2;   /* base in func_80156D18 */


typedef struct S_80174214_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80174214_4;   /* global in func_80156D18 */


/* Advances the actor action state, updating directional animation and entity status. */
void func_80156D18(void *actor, void *context, void *animation, void *entity)
{

    s32 state;

    state = ((S_80174214_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }

        dungeonStatus.unk_0A--;
        direction_anims = D_80157C90;
        if (((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv != direction_anims) {
            (*(void * *)((u8 *)animation + (0x2C))) = direction_anims;
            func_80047784(animation,
                direction_anims[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
        }
        ((S_80174214_0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (((EntityRec *)entity)->tileY != 0) {

            (*(void * *)((u8 *)animation + (0x2C))) = D_80157CB0;
            func_80047784(animation,
                D_80157CB0[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
            ((EntityRec *)entity)->flags1C |= 0x40000;
            dungeonStatus.unk_0A++;
            ((S_80174214_0 *)actor)->unk_9B++;
            return;
        }

        if (dungeonStatus.flags & 0x1000) {
            return;
        }

        if (((EntityRec *)entity)->unk_64 != 0) {
            if (func_800AA6B4(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((func_800A2C34(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)((EntityRec *)entity)->flags1C);
        if (entity_flags & 0x100) {
            func_800AA258(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stat_value;
            u16 stat_delta;

            func_800AA888(actor, context, animation, entity);
            stat_value = ((S_80174214_0 *)actor)->unk_92;
            stat_delta = ((S_80174214_0 *)actor)->unk_A2;
            ((S_80174214_0 *)actor)->unk_A2 = 0;
            ((S_80174214_0 *)actor)->unk_9E = 0;
            ((S_80174214_0 *)actor)->unk_92 = stat_value - stat_delta;
            func_80157078(actor, context, animation, entity);
            return;
        }

        if (((EntityRec *)entity)->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(entity) << 16) != 0) {
            if ((func_8009A180(entity,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(entity);
        func_800A9A04(entity);
        if (((EntityRec *)entity)->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)animation + (0x2C))) = D_80157CB0;
        func_80047784(animation,
            D_80157CB0[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((EntityRec *)entity)->flags1C |= 0x40000;
        dungeonStatus.unk_0A++;
        ((S_80174214_0 *)actor)->unk_9B++;
        return;
    }
    case 2:
        if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {

            dungeonStatus.unk_0A--;
            ((EntityRec *)entity)->flags1C &= ~8;
            ((S_80174214_0 *)actor)->unk_8C = &D_80153FA4;
        }

        return;
    default:
        return;
    }
}
