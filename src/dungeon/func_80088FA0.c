#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_8008E700_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008E700_0;   /* entity in func_8008E700 */

extern void func_80048A44(void *a0, u8 a1, s32 a2, s32 a3);
extern void func_80099F04(s32 a0);
extern void func_80099F70(s32 a0);
extern s16 func_8009AF18(s16 a0, void *a1, void *a2, s32 a3);
extern void func_8009F644(void *a0, s32 a1, s16 a2, s32 a3);
extern void func_800A56E0(s32 a0);

extern s32 D_80081484;
extern u8 D_8008EAC8[];
extern u8 D_800DCFD0[8];
extern u8 D_800DD048[8];
extern u8 D_800DD060[8];
extern u8 D_800DD0C8[8];
extern s32 D_800E3540[3];

/* Advance the entity action through its motion, animation, and linked-child effects. */
void func_8008E700(u8 *action, u8 *motion, u8 *sprite, u8 *entity) {
    s16 effect_id;
    s32 entity_flags;
    s32 direction;
    u16 ticks;
    s32 phase;
    u8 *child;
    u8 *anim_sprite;

    phase = action[0x9B];
    switch (phase) {
    case 0:
        if (*(u16 *)(sprite + 0x14) & 0x6000) {
            *(s32 *)(motion + 0x14) = 0xFFEA0000;
            if (*(s32 *)(entity + 0x1C) & 0x100000) {
                *(u8 **)(sprite + 0x2C) = D_800DD0C8;
            } else {
                *(u8 **)(sprite + 0x2C) = D_800DD048;
            }
            anim_sprite = sprite;
            direction = ((gameWork.view.viewAngle + *(s16 *)(entity + 0x2A) + 0x100) >> 9) & 7;
            func_80048A44(anim_sprite, (*(u8 **)(anim_sprite + 0x2C))[direction], 0, 1);
            action[0x9B]++;
        }
        return;
    case 1:
        ticks = *(u16 *)(action + 0x96) + 1;
        *(u16 *)(action + 0x96) = ticks;
        if ((*(u16 *)(action + 0xA2) & 0x10) && ((s16)ticks >= 4)) {
            u8 *animations;
            s32 heading;
            s32 update_direction;

            *(s32 *)(motion + 0x14) = 0;
            if (*(s32 *)(entity + 0x1C) & 0x100000) {
                *(u8 **)(action + 0x8C) = D_8008EAC8;
            } else {
                anim_sprite = sprite;
                animations = D_800DD060;
                *(u8 **)(anim_sprite + 0x2C) = animations;
                update_direction = ((gameWork.view.viewAngle + *(s16 *)(entity + 0x2A) + 0x100) >> 9) & 7;
                func_80048A44(anim_sprite, animations[update_direction], 0, 1);
            }
            action[0x9B]++;
            return;
        }

        if ((*(s32 *)(entity + 0x1C) & 0x300000) == 0x100000) {
            if (!((*(u16 *)0x80013714) & 1)) {
                effect_id = func_8009AF18(*(s16 *)(entity + 0x2A), motion, sprite, 8);
                if ((effect_id << 16) != 0) {
                    child = *(u8 **)(action + 0x124);
                    *(s32 *)(child + 0x1C) |= 0x200000;
                    *(s32 *)(entity + 0x1C) |= 0x200000;
                    *(s16 *)(*(u8 **)(action + 0x124) + 0x8A) = effect_id;
                    *(u8 *)(*(u8 **)(action + 0x124) + 0x84) = 0x78;
                    *(u8 *)(*(u8 **)(action + 0x124) + 0x85) = 2;
                    func_8009F644(entity, 0x30, *(s16 *)(action + 0x96), 0);

                    {
                        s32 saved_state;
                        s32 angle;
                        s32 heading;

                        ((S_8008E700_0 *)entity)->unk_1C &= 0xFFEFFFFF;
                        saved_state = D_80081484;
                        D_80081484 = 0;
                        dungeonStatus.unk_0A++;
                        *(u8 **)(sprite + 0x2C) = D_800DCFD0;
                        angle = gameWork.view.viewAngle;
                        heading = *(s16 *)(entity + 0x2A);
                        D_800E3540[0] = saved_state;
                        func_80048A44(sprite, D_800DCFD0[((angle + heading + 0x100) >> 9) & 7], 5, 1);
                    }
                    func_800A56E0(0x512);
                    return;
                }
            }
        }
        return;
    case 2:
        anim_sprite = sprite;
        if ((*(u16 *)(anim_sprite + 0x14) & 0x6000) &&
            (dungeonStatus.unk_0A == 0)) {
            entity_flags = *(s32 *)(entity + 0x1C);
            if (entity_flags & 0x200000) {
                *(s32 *)(entity + 0x1C) = entity_flags & 0xFFDFFFFF;
                dungeonStatus.flags |= 0x412;
                func_80099F70(*(s32 *)(entity + 0x5C));
                func_80099F04(*(s32 *)(entity + 0x5C));
            }
            *(s32 **)(action + 0x8C) = func_8008ACDC;
        }
    }
}
