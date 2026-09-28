#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800AD058_arg2.h"



extern void func_80047784(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174D48(void *, void *, void *);

extern u8 D_801710F4[];
extern u8 D_80174F00[];


typedef struct S_80174BF8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174BF8_0;   /* arg0 in func_80174BF8 */



typedef struct S_80174BF8_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80174BF8_3;   /* counter in func_80174BF8 */

/* Initialize a timed action, then restore animation and clear the entity flags. */
void func_80174BF8(S_80174BF8_0 *action, void *context, Rec_func_800AD058_arg2 *animation, EntityRec *entity)
{
    void *entity_arg;
    u16 ticks_left;
    u8 state;

    state = action->unk_9B;
    if (state != 0) {
        if (state != 1) {
            return;
        }
        goto active;
    }

    func_800A56E0(0x50C);
    action->unk_96 = 10;
    func_80174D48(context, animation, entity);
    entity->unk_48 = 0;
    entity->unk_49 = 0;
    action->unk_9B++;

active:
    if (!(animation->unk_14 & 0x8000)) {
        ticks_left = action->unk_96;
        action->unk_96 = ticks_left - 1;
        if ((s16)ticks_left > 0) {
            return;
        }
    }

    entity_arg = entity;
    dungeonStatus.unk_0A--;
    animation->unk_2C = D_80174F00;
    func_800AD594(entity_arg, 0x200);
    func_80047784(animation,
        animation->unk_2C[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
    action->unk_8C = D_801710F4;
    func_800A4ACC(entity);
    entity->unk_6D = 0;
    entity->unk_46 &= 0x7FFF;
}
