#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"


extern s32 func_80042900();
extern s32 has_enough_available_runtime_nodes(s32);
extern void spawn_vertical_particle_burst(s16 x, s16 y, s16 z, s32 sprite_id, s16 play_sound);
extern s32 play_sound_if_enabled();
extern void display_fixed_item_action_message();
extern s32 generate_random_value(void);
extern s32 run_action_ten_if_eligible(EntityRec *entity, s8 action_arg);
extern u8 D_800CD910[];
extern u8 D_800DF820[];

/* Step trigger: stop when all four 0x2C slots are taken, then roll the object's 0x3 chance and either spawn the 0x613 effect object over the owning tile (returning -1) or give the fallback cue. */
s32 trigger_step_trap_effect(void *object) {
    s16 index;
    s32 seed;
    s32 result;
    void *entry;
    void *effect;

    result = 1;
    if ((func_80042900(object, 0xA) << 0x10) == 0) {
        index = 0;
        for (; index < 4; index++) {
            if (*(s8 *)((u8 *)object + ((index << 0x10) >> 0xF) + 0x2C) == 0) {
                break;
            }
        }
        if (index >= 4) {
            return 1;
        }
        if (D_800E3D40 == 0) {
            seed = generate_random_value() & 0xFFFF;
            if (*(u8 *)((u8 *)object + 3) != 0) {
                index = seed % *(u8 *)((u8 *)object + 3);
            } else {
                index = 0;
            }
        } else {
            index = 0;
        }
        if (index < 0x40) {
            entry = *(void **)((u8 *)object - 0x14);
            if (*(u16 *)((u8 *)entry + 0x14) & 0x8000) {
                run_action_ten_if_eligible(object, 0x10);
                return -1;
            }
            result = 0;
            if (has_enough_available_runtime_nodes(2) != 0) {
                effect = func_8003FC64(2);
                *(u8 **)((u8 *)effect + 0x10) = D_800CD910;
                *(void **)((u8 *)effect + 0x20) = object;
                *(s16 *)((u8 *)effect + 0x26) = 0xC;
                spawn_vertical_particle_burst(
                    ((*(u8 *)((u8 *)entry + 0x24)) << 6) | 0x20,
                    ((*(u8 *)((u8 *)entry + 0x25)) << 6) | 0x20,
                    *(s16 *)((u8 *)object + 0x88), D_800DF820, 0);
                play_sound_if_enabled(0x613);
                {
                    (((u16)g_dungeon_status.unk_0A))++;
                }
                return -1;
            }
            return result;
        }
        if (*(u8 *)((u8 *)object + 0x13) == 0) {
            display_fixed_item_action_message();
        }
        return result;
    }
    return result;
}
