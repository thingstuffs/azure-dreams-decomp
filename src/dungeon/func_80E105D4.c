#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80173DD4_arg0.h"


typedef struct S_80173DD4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173DD4_3;   /* counter_base in func_80173DD4 */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174520(void *, void *, void *, void *);
extern void func_80175060(void *, void *);

extern u8 D_80171094[];
extern u8 D_80176470[];
extern u8 D_80176478[];

/* Updates actor behavior and directional animation through three states, then sets its next callback. */
void func_80173DD4(void *controller, void *context_in, void *object_in, EntityRec *actor)
{
    register void *object ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 actor_flags;
    u16 current_value;
    u16 value_adjustment;
    DungeonGlobalStatus *global_base;
    s32 state;

    object = object_in;

    state = ((Rec_func_80173DD4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)object)->unk_14.at00_u16.v & 0xE000)) {
            func_80175060(controller, context_in);
            func_80175060(controller, context_in);
            func_80175060(controller, context_in);
            func_80175060(controller, context_in);
            break;
        }
        (*(void * *)((u8 *)object + 0x2C)) = D_80176470;
        func_80047784(object,
            D_80176470[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {
            u8 *counter_base = (u8 *)&dungeonStatus.unk_00;

            ((S_80173DD4_3 *)counter_base)->unk_0A--;
        }
        ((Rec_func_80173DD4_arg0 *)controller)->unk_9B++;
        break;
    case 1:
        if ((func_80042900(actor, 1) << 16) != 0) {
            global_base = &dungeonStatus;
            if (global_base->flags & 0x1000) {
                break;
            }
            if (actor->unk_64 != 0) {
                if (func_800AA6B4(controller, context_in, object, 0) != 0) {
                    break;
                }
            }
            if (actor->tileY == 0) {
                if (global_base->flags & 0x2008) {
                    break;
                }
                func_800AA79C(controller, context_in, object, actor);
                break;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                break;
            }
            actor_flags = actor->flags1C;
            if (actor_flags & 0x100) {
                func_800AA258(controller, context_in, object, actor);
                break;
            }
            if (actor_flags & 0x80000) {
                func_800AA888(controller, context_in, object, actor);
                current_value = ((Rec_func_80173DD4_arg0 *)controller)->unk_92;
                value_adjustment = ((Rec_func_80173DD4_arg0 *)controller)->unk_A6;
                ((Rec_func_80173DD4_arg0 *)controller)->unk_A6 = 0;
                ((Rec_func_80173DD4_arg0 *)controller)->unk_AC = 0;
                ((Rec_func_80173DD4_arg0 *)controller)->unk_92 = current_value - value_adjustment;
                func_80174520(controller, context_in, object, actor);
                break;
            }
            if (actor->unk_6D == 0) {
                break;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                EntityRec *owner = D_800814A8;

                if ((func_8009A180(actor,
                        (u8 *)owner->unk_58 + 0x20) << 16) != 0) {
                    break;
                }
            }
            func_800A9A0C(actor);
            func_800A9A04(actor);
            if ((func_80042900(actor, 1) << 16) != 0) {
                TileObject *origin = &D_80082E80;
                s8 tile = ((Rec_D_80082E80 *)object)->unk_26.as_s8;

                if (((tile == origin->unk_026) && (tile >= 0)) ||
                    ((s16)func_8009FD40(origin, object) < 2)) {
                    if (!(func_800A6D30() & 7)) {
                        func_80042B68(actor, 1);
                    }
                }
            }
            if ((func_80042900(actor, 1) << 16) != 0) {
                break;
            }
        }
        (*(void * *)((u8 *)object + 0x2C)) = D_80176478;
        func_80047784(object,
            D_80176478[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        (*(u32 *)&actor->flags1C) |= 0x40000;
        if (((Rec_D_80082E80 *)object)->unk_14.at00_u16.v & 0x8000) {
            ((Rec_func_80173DD4_arg0 *)controller)->unk_8C = D_80171094;
            break;
        }
        {
            u8 *counter_base = (u8 *)&dungeonStatus.unk_00;

            ((Rec_func_80173DD4_arg0 *)controller)->unk_9B++;
            ((S_80173DD4_3 *)counter_base)->unk_0A++;
        }
        break;
    case 2:
        if (((Rec_D_80082E80 *)object)->unk_14.at00_u16.v & 0xE000) {
            u8 *counter_base;

            counter_base = (u8 *)&dungeonStatus.unk_00;
            ((S_80173DD4_3 *)counter_base)->unk_0A--;
            ((Rec_func_80173DD4_arg0 *)controller)->unk_8C = D_80171094;
        } else {
            func_80175060(controller, context_in);
            func_80175060(controller, context_in);
            func_80175060(controller, context_in);
            func_80175060(controller, context_in);
        }
        break;
    }

    ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return;
}
