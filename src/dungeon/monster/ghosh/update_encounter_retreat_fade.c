#include "slus.h"
#include "shared/entity.h"

struct ObjectPosition;
#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "slus/imports.h"
#include "dungeon/monster/ghosh.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "dungeon/system.h"

typedef struct {
    s32 field_00;
    u8 unk04[8];
    s32 field_0C;
} Vec3;

typedef struct {
    u8 unk00[6];
    s16 field_06;
    u8 unk08[4];
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 unk0F;
    s16 field_10;
    u8 unk12[2];
    u16 flags_14;
    u8 unk16[6];
    s16 field_1C;
    s16 field_1E;
    u8 unk20[12];
    u8 *field_2C;
} Sub;

typedef struct {
    u8 unk00[42];
    s16 facing;
    u8 unk2C[106];
    u16 action_timer;
    u8 unk98[2];
    u8 action_id;
    u8 unk9B[3];
    s16 fade_duration;
} Extra;

typedef struct {
    u8 unk00[8];
    Vec3 *position;
    Sub *sub;
    void *callback;
} Node;

extern u8 D_80174B30[9];

struct SpriteFrameState;
extern void func_80170CE0(void);

/* Delays an effect, then moves and fades its sprite before finishing. */
void update_encounter_retreat_fade(void) {
    Extra *effect;
    ObjectPosition *position;
    SpriteFrameState *sprite;
    Extra *direction_data;
    ObjectNodeHeader *node;
    s32 intensity;
    u16 elapsed;
    s32 state;
    s32 duration;

    node = ghosh_pulunpa_node;
    effect = NODE_BODY(node);
    position = node->position;
    state = effect->action_id;
    sprite = node->sprite;
    direction_data = effect;

    switch (state) {
    case 0:
        effect->action_id = 1;
        effect->action_timer = 0;

    case 1:
        elapsed = effect->action_timer++;
        if ((s16)elapsed >= 0x24) {
            effect->action_timer = 0x14;
            effect->fade_duration = 0x14;
            effect->action_id++;
            initialize_timed_motion_step(6, 12);
            create_fixed_offset_effect_sprite(effect, position, sprite);
            play_sound_if_enabled(0x601);
            position->velocity_x = -0x200000;
            sprite->tpage_abr = 0x20;
            sprite->frameTable = D_80174B30;
            sprite->flags |= 0xC;
            select_sprite_entry(sprite, D_80174B30[((g_game_work.view.camera_rotation.parts.viewAngle + direction_data->facing + 0x100) >> 9) & 7],
                0);
        }
        break;

    case 2:
        position->x.v += position->velocity_x;
        position->velocity_x /= 2;
        duration = effect->fade_duration;
        intensity = ((s32)(s16)(effect->action_timer - 1) << 7) / duration;
        effect->action_timer--;
        sprite->color.c.b = (s8)intensity;
        sprite->color.c.g = (s8)intensity;
        sprite->color.c.r = (s8)intensity;
        if ((s16)effect->action_timer <= 0) {
            func_80170CE0();
        }
    }

    advance_sprite_animation_and_textures(sprite);
}
