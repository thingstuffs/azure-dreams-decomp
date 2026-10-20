#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172D04_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80172D04_0;   /* script in update_actor_knockback */


extern void set_record_integer_tile_center(void *, u8, u8);
extern s32 generate_random_value(void);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);
extern void create_knockback_travel_object(void *, void *, void *, void *);
extern void spawn_manoeva_particle_burst(void *, void *);

extern u8 D_80170EE4[];
extern u8 D_80176640[];

/* Three-stage knockback script driven by the 0x9B step byte: stage 0 seeds the velocity from the facing table and picks the timer, stage 1 decays that velocity a quarter per frame, stage 2 steers back to the tile centre and ends by clearing the motion record. */
void update_actor_knockback(S_80172D04_0 *script, EntityRec *motion, Rec_D_80082E80 *tile, EntityRec *actor)
{
    s16 timer;
    s32 value;
    s32 value2;
    s32 adjusted;
    s32 state;
    s32 random;
    s32 one;

    state = script->unk_9B;
    one = 1;
    switch (state) {
    case 0:
        spawn_manoeva_particle_burst(motion, tile);
        apply_clamped_actor_value_delta(actor);
        motion->unk_0C =
            -*(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((actor->unk_6A >> 8) & 0xE)) << 15;
        motion->unk_10 =
            -*(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((actor->unk_6A >> 8) & 0xE)) << 15;
        script->unk_9B++;

        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(script, motion, tile, D_80176640);
            return;
        }
        random = generate_random_value() & 3;
        if (tile->unk_14.at00_u16.v & 0x8000) {
            if (random == 0) {
                create_knockback_travel_object(script, motion, tile, actor);
            }
            script->unk_A8.s = -1;
            script->unk_96.s = 0;
            script->unk_9B = 2;
            return;
        }
        timer = -1;
        if (actor->flags1C & 0x228) {
            timer = 8;
        }
        script->unk_96.s = timer;
        if (random != 0) {
            script->unk_A8.s = -1;
        } else {
            script->unk_A8.u = one;
        }
                        /* fall through */
    case 1:
        value = motion->unk_0C;
        adjusted = value;
        if (value < 0) {
            adjusted = value + 3;
        }
        value2 = motion->unk_10;
        motion->unk_0C = value - (adjusted >> 2);

        adjusted = value2;
        motion->unk_10 = value2 - (adjusted / 4);

        timer = script->unk_A8.u - 1;
        script->unk_A8.u = timer;
        if ((timer << 16) == 0) {
            create_knockback_travel_object(script, motion, tile, actor);
        }

        if (script->unk_96.s > 0) {
            script->unk_96.u = script->unk_96.u - 1;
        } else if (tile->unk_14.at00_u16.v & 0x6000) {
            script->unk_96.s = 0;
        }

        if (script->unk_96.s != 0) {
            return;
        }
        if (actor->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(script, motion, tile, D_80176640);
        } else {
            script->unk_96.s = 8;
            script->unk_9B++;
        }
        return;
    case 2:
        timer = script->unk_96.s;
        if (timer != 0) {
            s32 sub, m;
            m = tile->unk_24;
            m <<= 6;
            sub = motion->x.w.i - 0x20;
            motion->unk_0C = ((m - sub) << 15) / timer;
            sub = motion->y.w.i - 0x20;
            motion->unk_10 =
                (((tile->unk_25 << 6) - sub) << 15) /
                script->unk_96.s;
        }

        timer = script->unk_A8.u - 1;
        script->unk_A8.u = timer;
        if ((timer << 16) == 0) {
            create_knockback_travel_object(script, motion, tile, actor);
        }

        timer = script->unk_96.u - 1;
        script->unk_96.s = timer;
        if ((timer << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, tile->unk_24,
            tile->unk_25);
        {

            value = ((s32)g_dungeon_status.unk_10);
            if (value == (s32)((u8 *)actor - 0x20)) {
                g_dungeon_status.unk_10 = value & 0x7FFFFFFF;
            }
        }
        script->unk_8C = D_80170EE4;
    }
}
