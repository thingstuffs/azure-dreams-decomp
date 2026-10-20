#include "modules/dungeon_ovl_cb3000.h"

void complete_timed_actor_animation(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 next_state;
    s32 start_state;
    u16 timer;

    state = ((CB_801729A8_S_801729A8_0 *)action)->unk_9B;
    start_state = 1;
    switch (state) {
    case 0:
        ((CB_801729A8_S_801729A8_0 *)action)->unk_9B = start_state;
                        /* fall through */
    case 1:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((CB_801729A8_S_801729A8_0 *)action)->unk_9B = 3;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, ((EntityRec *)actor)->facing, 1);
            return;
        }

        ((CB_801729A8_S_801729A8_3 *)motion)->unk_14 = 0;
        ((CB_801729A8_S_801729A8_3 *)motion)->unk_10 = 0;
        ((CB_801729A8_S_801729A8_3 *)motion)->unk_0C = 0;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801752DC;
        select_sprite_entry(sprite,
            D_801752DC[((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        next_state = ((CB_801729A8_S_801729A8_0 *)action)->unk_9B;
        ((CB_801729A8_S_801729A8_0 *)action)->unk_96.s = 0;
        next_state++;
        ((CB_801729A8_S_801729A8_0 *)action)->unk_9B = next_state;
        return;
    case 2:
        timer = ((CB_801729A8_S_801729A8_0 *)action)->unk_96.s + 1;
        ((CB_801729A8_S_801729A8_0 *)action)->unk_96.s = timer;
        if ((s16)timer == 7 || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, ((EntityRec *)actor)->facing, 1);
        }
        if (((CB_801729A8_S_801729A8_0 *)action)->unk_96.u == 6) {
            play_sound_if_enabled(0x808);
        }
        if (((CB_801729A8_S_801729A8_0 *)action)->unk_96.u == 8) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
        }
        if (((CB_801729A8_S_801729A8_0 *)action)->unk_96.u == 15 ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            next_state = ((CB_801729A8_S_801729A8_0 *)action)->unk_9B;
            next_state++;
            ((CB_801729A8_S_801729A8_0 *)action)->unk_9B = next_state;
        }
        return;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            reduce_actor_food_meter(actor, 0x100);
            ((CB_801729A8_S_801729A8_0 *)action)->unk_8C = func_8017102C;
            g_dungeon_status.unk_0C = 0;
            advance_status_timers(actor);
            ((EntityRec *)actor)->unk_46 &= 0x7FFF;
        }
        return;
    default:
        return;
    }
}
