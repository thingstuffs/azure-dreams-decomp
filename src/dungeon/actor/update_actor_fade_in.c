#include "common.h"
#include "dungeon/actor/effect.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"

void unlink_node(void *);
void register_node(void *, void *);

/* Restores neutral color, then counts down and finalizes the effect. */
s32 update_actor_fade_in(ActorRecord *object_arg, ObjectPosition *unused, SpriteFrameState *effect_arg) {
    ActorRecord *object = object_arg;
    SpriteFrameState *effect = effect_arg;
    u8 phase = object->action_phase;
    u16 effect_count;
    ObjectNodeHeader *owner;

    switch (phase) {
    case 0:
        effect->color.c.code++;
        effect->color.c.r += (0x80 - effect->color.c.r) / effect->color.c.code;
        effect->color.c.g += (0x80 - effect->color.c.g) / effect->color.c.code;
        effect->color.c.b += (0x80 - effect->color.c.b) / effect->color.c.code;
        if (effect->color.c.code >= 8) {
            effect->color.c.b = 0x80;
            effect->color.c.g = 0x80;
            effect->color.c.r = 0x80;
            object->action_phase++;
        }
        return 0;
    case 1:
        effect->color.c.code--;
        if (effect->color.c.code != 0) {
            return 0;
        }
        owner = NODE_HEADER(object);
        unlink_node(owner);
        effect->clut += 0x80;
        effect->flags &= 0xFFF3;
        register_node(owner, project_sprite_chain);
        effect_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
        effect_count--;
        g_dungeon_status.activity_counts.parts.pending_action_count = effect_count;
        return 1;
    default:
        return 0;
    }
}
