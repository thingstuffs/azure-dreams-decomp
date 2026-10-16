/* Relink of matched dungeon/func_80CBEDB8; every changed retail word is a paired relocation. */
#define D_80170F20 D_8015BB98
#define D_801762E8 D_8015E348
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801725B8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801725B8_0;   /* arg0 in func_8015D2A0 */


typedef struct S_801725B8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801725B8_3;   /* arg1 in func_8015D2A0 */


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_8015BB98;
extern u8 D_8015E348[];

/* Advances the actor's directional animation and resets its action state on completion. */
void func_8015D2A0(void *action, void *motion, void *anim, EntityRec *actor)
{
    switch (((S_801725B8_0 *)action)->unk_9B) {
    case 0:
        if (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x8000) {
            ((S_801725B8_0 *)action)->unk_9B = 2;
            ((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, anim, actor->facing, 1);
            return;
        }
        {
            u8 *direction_table;

            ((S_801725B8_3 *)motion)->unk_14 = 0;
            ((S_801725B8_3 *)motion)->unk_10 = 0;
            ((S_801725B8_3 *)motion)->unk_0C = 0;
            direction_table = D_8015E348;
            (*(u8 * *)((u8 *)anim + 0x2C)) = direction_table;
            func_80047784(anim,
                direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801725B8_0 *)action)->unk_9B++;
        }
        return;

    case 1:
        if (((Rec_D_80082E80 *)anim)->unk_04.as_s8 == 3 && (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (!((((Rec_D_80082E80 *)anim)->unk_04.as_s8 == 6 && (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0x1000)) ||
              (((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0xE000))) {
            return;
        }
        func_8009C12C(actor, anim, actor->facing, 1);
        ((S_801725B8_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 2:
        if (!(((Rec_D_80082E80 *)anim)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        func_800AD594(actor, 0x100);
        ((S_801725B8_0 *)action)->unk_8C = &D_8015BB98;
        dungeonStatus.unk_0C = 0;
        (actor->unk_46) &= 0x7FFF;
        func_800A4ACC(actor);
        return;
    }
}
