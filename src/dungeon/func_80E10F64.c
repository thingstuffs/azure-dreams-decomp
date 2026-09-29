#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80174764_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80174764_0;   /* arg0 in func_80174764 */



typedef struct S_80174764_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80174764_3;   /* target in func_80174764 */

typedef struct S_80174764_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80174764_4;   /* ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in func_80174764 */



extern void func_80047784(void *, s16, s16);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80175AF4(void *, void *, void *);
extern s32 func_801761AC(void *);
extern s32 func_80176258(void *);
extern void func_801762A4(s32, void *);
extern void func_80176330(s32, void *);
extern void func_801763CC(s32, void *);

extern u8 D_80171094;
extern u8 D_80176460[8];

/* Advances the timed target interaction and updates the directional animation. */
void func_80174764(void *action, void *scene, void *sprite, void *actor)
{
    u16 sprite_flags;
    u16 timer;
    void *target;

    switch (((S_80174764_0 *)action)->unk_9B) {
    case 0:
        sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
        if (sprite_flags & 0x8000) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = sprite_flags | 0x6000;
            if (((EntityRec *)actor)->flags14 & 0x4000) {
                target = ((EntityRec *)actor)->target;
                if (func_80176258(target)) {
                    func_801763CC(1, ((EntityRec *)actor)->target);
                } else {
                    func_801763CC(0, ((EntityRec *)actor)->target);
                }
            } else {
                target = ((EntityRec *)actor)->target;
                if (((S_80174764_3 *)target)->unk_14 & 0x4000) {
                    if (func_801761AC(target)) {
                        func_80176330(1, ((EntityRec *)actor)->target);
                    } else {
                        func_80176330(0, ((EntityRec *)actor)->target);
                    }
                } else {
                    func_801761AC(target);
                }
            }
            ((S_80174764_0 *)action)->unk_9B = 2;
            return;
        }

        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 1) {
            if (!(sprite_flags & 0x1000)) {
                if (!(sprite_flags & 0x6000)) {
                    break;
                }
            }
        } else if (!(sprite_flags & 0x6000)) {
            break;
        }

        func_80175AF4(action, scene, sprite);
        if (((EntityRec *)actor)->flags14 & 0x4000) {
            func_801762A4(1, actor);
        } else if (((S_80174764_4 *)(((EntityRec *)actor)->target))->unk_14 & 0x4000) {
            func_801762A4(0, actor);
        }
        func_800A56E0(0x708);
        timer = 0x20;
        ((S_80174764_0 *)action)->unk_96 = timer;
        ((S_80174764_0 *)action)->unk_9B++;
        break;

    case 1:
        timer = ((S_80174764_0 *)action)->unk_96 - 1;
        ((S_80174764_0 *)action)->unk_96 = timer;
        if ((timer << 16) == 0 || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            if (((EntityRec *)actor)->flags14 & 0x4000) {
                target = ((EntityRec *)actor)->target;
                if (func_80176258(target)) {
                    func_801763CC(1, ((EntityRec *)actor)->target);
                } else {
                    func_801763CC(0, ((EntityRec *)actor)->target);
                }
            } else {
                target = ((EntityRec *)actor)->target;
                if (((S_80174764_3 *)target)->unk_14 & 0x4000) {
                    if (func_801761AC(target)) {
                        func_80176330(1, ((EntityRec *)actor)->target);
                    } else {
                        func_80176330(0, ((EntityRec *)actor)->target);
                    }
                } else {
                    func_801761AC(target);
                }
            }
            ((S_80174764_0 *)action)->unk_96 = 4;
            ((S_80174764_0 *)action)->unk_9B++;
        }
        break;

    case 2:
        timer = ((S_80174764_0 *)action)->unk_96 - 1;
        ((S_80174764_0 *)action)->unk_96 = timer;
        if ((timer << 16) == 0 || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            func_800AD594(actor, 0x400);
            func_800A2B04(scene, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            ((S_80174764_0 *)action)->unk_8C = &D_80171094;
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        }
        break;
    }

    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        s32 direction;

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80176460;
        direction = (gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9;
        func_80047784(sprite, D_80176460[direction & 7], 0);
        ((S_80174764_0 *)action)->unk_98 &= 0xFFF7;
    }
}
