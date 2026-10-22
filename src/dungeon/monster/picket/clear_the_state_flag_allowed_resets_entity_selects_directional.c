#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[0x8C];
    s32 unk8C;
    u8 pad90[0x0A];
    s8 unk9A;
    s8 unk9B;
} Entity;

typedef struct {
    u8 pad00[0x2C];
    u8 *unk2C;
} Object;

typedef struct {
    u8 pad00[0x2A];
    s16 unk2A;
    u8 pad2C[0x41];
    u8 unk6D;
    u8 pad6E[3];
    u8 unk71;
} State;

extern s32 has_pending_dungeon_activity(State *state);
extern void select_sprite_entry(Object *object, u8 value, s32 entry_index);
extern u8 D_80174F08[];

/* Clears the state flag and, when allowed, resets the entity and selects a directional object value. */
void clear_the_state_flag_allowed_resets_entity_selects_directional(Entity *entity, s32 unused, SpriteFrameState *object, State *state) {
    DungeonGlobalStatus *flags = &g_dungeon_status;

    state->unk71 &= 0x7F;
    if (!(flags->flags & 0x2000) && ((has_pending_dungeon_activity(state) << 16) == 0)) {
        entity->unk9A = 0x18;
        entity->unk8C = 0;
        entity->unk9B = 0;
        object->frameTable = D_80174F08;
        select_sprite_entry(object,
                      D_80174F08[((g_game_work.view.camera_rotation.parts.viewAngle + state->unk2A + 0x100) >> 9) & 7],
                      0);
        state->unk6D--;
        flags->activity_counts.parts.pending_action_count++;
    }
}
