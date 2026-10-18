#include "modules/trap_effects_candidate.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern s32 D_800CBDB4;
extern u8 D_800E1B5D;

extern s32 has_enough_available_runtime_nodes(s32 a0);
extern s32 func_80042900();
extern s16 set_or_clear_actor_status_slot();
extern void func_800419EC();
extern s32 play_sound_if_enabled();
extern void display_formatted_context_message();

/* Creates an effect for the active entity or displays its status message. */
s32 create_active_entity_effect_or_message(s32 entity)
{
    void *effect;
    s32 status;
    register s32 effect_id;
    register s32 effect_id_half;

    if (entity == ((s32)D_800E3D7C)) {
        if (has_enough_available_runtime_nodes(1) == 0) {
            return 0;
        }
        status = func_80042900(entity, 0x1C);
        if ((status << 0x10) == 0) {
            if ((set_or_clear_actor_status_slot(entity, 0x1C, 0x10) << 0x10) >= 0) {
                effect = func_8003FC64(2);
                effect_id = 0x10;
                *(void **)((u8 *)effect + 0x10) = &D_800CBDB4;
                effect_id_half = effect_id;
                *(s16 *)((u8 *)effect + 0x24) = effect_id_half;
                g_dungeon_status.unk_0A = (u16)(((u16)g_dungeon_status.unk_0A) + 1);
                func_800419EC(effect_id, 8);
                play_sound_if_enabled(0x818);
                return 1;
            }
        } else {
            display_formatted_context_message(&D_800E1B5D);
        }
    }
    return 1;
}
