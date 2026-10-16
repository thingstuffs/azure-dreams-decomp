#define func_80173E00 func_801726B8
#define func_800A2C34 func_800A1904
#define D_800814A8 D_800803DC
#define func_800A9A0C func_800A86C4
#define dungeonBeginPushedActorMove func_800A8F10
#define func_800AA888 func_800A9540
#define func_800A9A04 townUpdateFadingEffectMotion
#define D_80174160 D_80172ECC
#define D_80174158 D_80172EC4
#define dungeonBeginReadyActorDirectionalAction func_800A936C
#define func_80047784 func_80047320
#define D_801714D4 D_80170514
#define dungeonCheckEntityRelation func_80098F70
/* Relink of matched dungeon/func_809782AC at file 0x9982AC; imports and data use paired retail relocations. */
#define dungeonStatus D_80085990
#define gameWork D_80084818
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_func_8017360C_arg0.h"


extern void func_80047320(void *, s32, s32);
extern s32 func_80098F70(void *, void *);
extern s32 func_800A1904(void *);
extern void townUpdateFadingEffectMotion(void *);
extern void func_800A86C4(void *);
extern void func_800A8F10(void *, void *, void *, void *);
extern s32 func_800A936C(void *, void *, void *, s32);
extern void func_800A9540(void *, void *, void *, void *);
extern void func_801726B8(void *, void *, void *, void *);

extern s32 D_80170514;
extern u8 D_80172EC4[];
extern u8 D_80172ECC[];

/* Advance actor states, select directional animations, and process entity actions. */
void func_80172364(void *actor, void *context, void *animation, EntityRec *entity)
{
    s32 state;

    state = ((Rec_func_8017360C_arg0 *)actor)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }

        dungeonStatus.unk_0A--;
        direction_anims = D_80172EC4;
        (*(void * *)((u8 *)animation + 0x2C)) = direction_anims;
        func_80047320(animation,
            direction_anims[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->tileY != 0) {

            (*(void * *)((u8 *)animation + 0x2C)) = D_80172ECC;
            func_80047320(animation,
                D_80172ECC[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            dungeonStatus.unk_0A++;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
            return;
        }

        if (dungeonStatus.flags & 0x1000) {
            return;
        }

        if (entity->unk_64 != 0) {
            if (func_800A936C(actor, context, animation, 0) != 0) {
                return;
            }
        }

        if ((func_800A1904(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            func_800A8F10(actor, context, animation, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stored_value;
            u16 pending_decrement;

            func_800A9540(actor, context, animation, entity);
            stored_value = ((Rec_func_8017360C_arg0 *)actor)->unk_92;
            pending_decrement = ((Rec_func_8017360C_arg0 *)actor)->unk_A2;
            ((Rec_func_8017360C_arg0 *)actor)->unk_A2 = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_9E = 0;
            ((Rec_func_8017360C_arg0 *)actor)->unk_92 = stored_value - pending_decrement;
            func_801726B8(actor, context, animation, entity);
            return;
        }

        if (entity->unk_6D == 0) {
            return;
        }
        if ((func_800A1904(entity) << 16) != 0) {
            if ((func_80098F70(entity,
                    (u8 *)D_800803DC->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A86C4(entity);
        townUpdateFadingEffectMotion(entity);
        if (entity->tileY == 0) {
            return;
        }

        (*(void * *)((u8 *)animation + 0x2C)) = D_80172ECC;
        func_80047320(animation,
            D_80172ECC[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        dungeonStatus.unk_0A++;
        ((Rec_func_8017360C_arg0 *)actor)->unk_9B++;
    }
        break;
    case 2:
        if (((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000) {

            dungeonStatus.unk_0A--;
            entity->flags1C &= ~8;
            ((Rec_func_8017360C_arg0 *)actor)->unk_8C.as_pv = &D_80170514;
        }

        return;
    }
}
