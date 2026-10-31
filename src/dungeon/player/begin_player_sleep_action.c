#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "dungeon/player.h"
#include "engine/graphics.h"

extern u8 D_800DD0E8;

/* Resets the player's sleep action state and installs the directional sleep animation. */
void begin_player_sleep_action(void *record_arg, void *unused, void *object, ActorRecord *entity) {
        Rec_func_8008ACDC_arg0 *record = record_arg;
        /* MATCH: Keep the shared data pointer in a0 after the first call. */
    u8 *data;
    s32 mask;

    record->unk_9A.as_s8 = 0xD;
    record->unk_9B.as_s8 = 0;
    record->unk_8C.as_s32 = 0;
    record->unk_96.as_s16 = 0;
    clear_player_linked_action_flags();
    mask = ~0x20;
         /* MATCH: Emit the mask before loading the data pointer. */
    data = &D_800DD0E8;
    entity->flags1C = (s32) (entity->flags1C & mask);
    (*(s32 **)((u8 *)object + 0x2C)) = data;
    set_sprite_animation_frame(object, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + data), 0, 1);
}
