#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801726A4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801726A4_0;   /* arg0 in func_801726A4 */


typedef struct S_801726A4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801726A4_3;   /* arg1 in func_801726A4 */


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174690(void *);

extern u8 D_80170EE4[];
extern u8 D_80176600[];
extern u8 D_80176668[];

/* Advances an actor's animation sequence and handles its completion. */
void func_801726A4(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u16 sprite_flags;
    u16 frame_count;
    s32 state;

    state = ((S_801726A4_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        ((S_801726A4_0 *)action)->unk_98 |= 1;
        ((S_801726A4_0 *)action)->unk_9B++;
                        /* fall through */
    case 1:
        sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
        if (sprite_flags & 0x8000) {
            ((S_801726A4_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, sprite, actor->facing, 1);
            return;
        }

        if (sprite_flags & 0x6000) {
            ((S_801726A4_3 *)motion)->unk_0C =
                ((S_801726A4_3 *)motion)->unk_10 =
                ((S_801726A4_3 *)motion)->unk_14 = 0;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80176600;
            func_80047784(sprite,
                D_80176600[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            func_80174690((u8 *)action - 0x20);
            ((S_801726A4_0 *)action)->unk_96 = 0;
            ((S_801726A4_0 *)action)->unk_9B++;
            func_800A56E0(0x804);
            return;
        }
        break;
    case 2:
        frame_count = ((S_801726A4_0 *)action)->unk_96 + 1;
        ((S_801726A4_0 *)action)->unk_96 = frame_count;

        if ((s16)frame_count == state ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(actor, sprite, actor->facing, 1);
        }

        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80176668;
            func_80047784(sprite,
                D_80176668[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801726A4_0 *)action)->unk_9B++;
            ((S_801726A4_0 *)action)->unk_98 &= 0xFFFE;
            return;
        }
        break;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            func_800AD594(actor, 0x100);
            ((S_801726A4_0 *)action)->unk_8C = D_80170EE4;
            dungeonStatus.unk_0C = 0;
            (actor->unk_46) &= 0x7FFF;
            func_800A4ACC(actor);
        }
    }
}
