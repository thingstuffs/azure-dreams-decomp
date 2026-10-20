#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad[0x9B];
    u8 unk9B;
} StructArg0;

typedef struct {
    u8 pad[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 unk0F;
    u8 pad10[2];
    u16 unk12;
    u16 unk14;
} StructArg2;

void unlink_node(void *);
void register_node(void *, void *);

/* Restores neutral color, then counts down and finalizes the effect. */
s32 update_actor_fade_in(StructArg0 *object_arg, s32 unused, StructArg2 *effect_arg) {
    StructArg0 *object = object_arg;
    StructArg2 *effect = effect_arg;
    u8 phase = object->unk9B;
    u16 effect_count;
    StructArg0 *owner;

    switch (phase) {
    case 0:
        ((SpriteFrameState *)effect)->color.c.code++;
        ((SpriteFrameState *)effect)->color.c.r += (0x80 - ((SpriteFrameState *)effect)->color.c.r) / ((SpriteFrameState *)effect)->color.c.code;
        ((SpriteFrameState *)effect)->color.c.g += (0x80 - ((SpriteFrameState *)effect)->color.c.g) / ((SpriteFrameState *)effect)->color.c.code;
        ((SpriteFrameState *)effect)->color.c.b += (0x80 - ((SpriteFrameState *)effect)->color.c.b) / ((SpriteFrameState *)effect)->color.c.code;
        if (((SpriteFrameState *)effect)->color.c.code >= 8) {
            ((SpriteFrameState *)effect)->color.c.b = 0x80;
            ((SpriteFrameState *)effect)->color.c.g = 0x80;
            ((SpriteFrameState *)effect)->color.c.r = 0x80;
            object->unk9B++;
        }
        return 0;
    case 1:
        ((SpriteFrameState *)effect)->color.c.code--;
        if (((SpriteFrameState *)effect)->color.c.code != 0) {
            return 0;
        }
        owner = (StructArg0 *)((u8 *)object - 0x20);
        unlink_node(owner);
        ((SpriteFrameState *)effect)->clut += 0x80;
        ((SpriteFrameState *)effect)->flags &= 0xFFF3;
        register_node(owner, project_sprite_chain);
        effect_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
        effect_count--;
        g_dungeon_status.activity_counts.parts.pending_action_count = effect_count;
        return 1;
    default:
        return 0;
    }
}
