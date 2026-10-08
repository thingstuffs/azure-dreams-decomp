#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
extern int abs(int);


typedef s32 Any;

typedef struct S_801737B0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737B0_0;   /* arg0 in func_8016D7B0 */


typedef struct S_801737B0_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801737B0_2_pre;   /* the 0x14 bytes before ptr in func_8016D7B0, addressed as ptr[-1] */

typedef struct S_801737B0_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801737B0_3;   /* desc in func_8016D7B0 */


extern u8 D_8016BCE8[];
extern u8 D_8016EEB8[];

extern s32 func_8003F270();
extern Any func_80047784();
extern s32 func_80069EF8();
extern void *func_800A05A4();
extern Any func_800A2B04();
extern Any func_800A4ACC();
extern Any func_800A56E0();
extern s32 func_800A94A0();
extern Any func_8016B498();

/* Updates an actor action through targeting, particle effects, and recovery. */
void func_8016D7B0(void *action, EntityRec *motion, void *sprite, EntityRec *actor) {
    s32 use_player_target;
    s32 particle_count;
    s32 offset_z;
    s32 direction;
    s32 action_kind;
    s32 particle_zero;
    s32 particle_color;
    s32 offset_x;
    s32 offset_y;
    u16 timer;
    u16 sprite_flags;
    u16 raw_kind;
    u32 kind_index;
    u8 state;
    u8 *action_data;
    u8 *particle_origin;

    state = ((S_801737B0_0 *)action)->unk_9B;
    use_player_target = 0;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            raw_kind = actor->unk_46 & 0x3FFF;
            kind_index = raw_kind - 1;
            switch (kind_index) {
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                action_data = (u8 *)actor + 0xE;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                action_data = (u8 *)actor + 0xB;
                break;
            case 4:
                use_player_target = 1;
                /* fall through */
            case 0:
                action_data = (u8 *)actor + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        } else {
            action_kind = actor->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 3:
                action_data = (u8 *)actor + 0xE;
                break;
            case 2:
                action_data = (u8 *)actor + 0xB;
                break;
            case 1:
                action_data = (u8 *)actor + 8;
                break;
            default:
                action_data = 0;
                break;
            }
        }
        if (*action_data != 0) {

            direction = ((S_801737B0_0 *)action)->unk_98;
            direction &= 0xFF7F;
            ((S_801737B0_0 *)action)->unk_98 = direction;
            direction = use_player_target;
            if (((void *)direction) != 0) {
                direction = (s32)D_800814A8;
                actor->target = (void *)direction;
                {
                    u8 facing;

                    action_kind = (s32)(((S_801737B0_2_pre *)((void *)direction))[-1].unk_00);
                    facing = ((S_801737B0_3 *)((u8 *)action_kind))->unk_24;
                    actor->unk_72 = facing;
                    facing = ((S_801737B0_3 *)((u8 *)action_kind))->unk_25;
                    actor->unk_73 = facing;
                }
            } else if (D_8006DE24[*action_data].kind == 2) {
                direction = (s32)(actor->target);
                if (((void *)direction) != 0) {
                    {
                        u8 facing;

                        action_kind = (s32)(((S_801737B0_2_pre *)((void *)direction))[-1].unk_00);
                        facing = ((S_801737B0_3 *)((u8 *)action_kind))->unk_24;
                        actor->unk_72 = facing;
                        facing = ((S_801737B0_3 *)((u8 *)action_kind))->unk_25;
                        actor->unk_73 = facing;
                    }
                }
            } else {

                actor->target = func_800A05A4(
                    actor,
                    ((Rec_D_80082E80 *)sprite)->unk_24,
                    ((Rec_D_80082E80 *)sprite)->unk_25,
                    actor->facing,
                    0x10);

                actor->unk_72 = abs(actor->unk_72);
                actor->unk_73 = abs(actor->unk_73);
            }

            if (func_800A94A0(actor, action_data, use_player_target, (u8 *)action + 0x98) == 0) {
                return;
            }
            ((S_801737B0_0 *)action)->unk_9B++;
            return;

        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
        func_800A4ACC(actor);
        actor->unk_6D--;
        ((S_801737B0_0 *)action)->unk_8C = D_8016BCE8;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_801737B0_0 *)action)->unk_9B++;
        func_800A56E0(0x703);

    case 2:
        sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
        if (sprite_flags & 0x8000) {
            ((S_801737B0_0 *)action)->unk_96.s = 0;
            ((S_801737B0_0 *)action)->unk_9B++;
            ((S_801737B0_0 *)action)->unk_98 |= 0x80;
            return;
        }

        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2) && (sprite_flags & 0x1000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = sprite_flags | 0x800;
            ((S_801737B0_0 *)action)->unk_96.s = 0x16;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 < 2) {
            return;
        }

        timer = ((S_801737B0_0 *)action)->unk_96.s - 1;
        ((S_801737B0_0 *)action)->unk_96.s = timer;
        if ((s16)timer <= 0) {
            ((S_801737B0_0 *)action)->unk_96.s = 0;
            ((S_801737B0_0 *)action)->unk_9B++;
        }
        if (((S_801737B0_0 *)action)->unk_96.u == 2) {
            ((S_801737B0_0 *)action)->unk_98 |= 0x80;
        }
        if (((S_801737B0_0 *)action)->unk_96.u < 0xA) {
            return;
        }

        particle_count = 0;
        do {
            particle_count++;
            offset_x = (s16)((func_80069EF8() & 0x3F) - 0x20);
            offset_y = (s16)((func_80069EF8() & 0x3F) - 0x20);
            offset_z = func_80069EF8();
            particle_origin = (u8 *)action - 0x20;
            particle_zero = 0;
            particle_color = 0xC0C0C0;
            offset_z = (s16)((offset_z & 0x3F) - 0x20);
            func_8016B498(
                particle_origin,
                particle_zero,
                particle_color,
                (s16)(((S_801737B0_0 *)action)->unk_96.s - 2),
                offset_x,
                offset_y,
                offset_z);
            if ((u32)(particle_count & 0xFFFF) >= 3U) {
                return;
            }
        } while (1);

    case 3:
        ((S_801737B0_0 *)action)->unk_96.s = 0x14;
        ((S_801737B0_0 *)action)->unk_9B++;

    case 4:
        if (((s32)dungeonStatus.unk_0C) == 0) {
            ((S_801737B0_0 *)action)->unk_96.s = 0;
        }
        timer = ((S_801737B0_0 *)action)->unk_96.s - 1;
        ((S_801737B0_0 *)action)->unk_96.s = timer;
        if ((s16)timer <= 0) {
            ((S_801737B0_0 *)action)->unk_96.s = 0;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pv != D_8016EEB8) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_8016EEB8;
            direction = ((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7;
            func_80047784(sprite, D_8016EEB8[direction], 0);
        }
        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }

        dungeonStatus.unk_0A--;
        ((S_801737B0_0 *)action)->unk_8C = D_8016BCE8;
        func_800A4ACC(actor);
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_6D--;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
    }
}
