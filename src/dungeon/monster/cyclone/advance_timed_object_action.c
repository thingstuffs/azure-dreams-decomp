#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 cyclone_action_resume_address[];
extern u8 cyclone_move_direction_frames[8];
typedef struct Obj0 {
    u8 pad04[4];
    s8 field04;
    u8 pad14[0x14 - 5];
    u16 field14;
    u8 pad8c[0x8c - 0x16];
    u8 *field8c;
    u8 pad96[0x96 - 0x90];
    u16 field96;
    u16 field98;
    u8 pad9b[1];
    u8 state9b;
} Obj0;

typedef struct Obj2 {
    u8 pad04[4];
    s8 field04;
    u8 pad14[0x14 - 5];
    u16 field14;
    u8 pad24[0x24 - 0x16];
    u8 field24;
    u8 field25;
    u8 pad2c[0x2c - 0x26];
    u8 *field2c;
} Obj2;

typedef struct Obj3 {
    u8 pad14[0x14];
    u32 field14;
    u8 pad2a[0x2a - 0x18];
    s16 field2a;
    u8 pad46[0x46 - 0x2c];
    u16 field46;
    u8 pad60[0x60 - 0x48];
    struct Obj3 *field60;
} Obj3;

extern void spend_actor_mp(Obj3 *, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
struct SpriteFrameState;
extern void select_sprite_entry(struct SpriteFrameState *, s16, s16);
extern void func_80174CB0(s32);
extern void func_80174D0C(s32);
extern void create_source_adjusted_motion_object(Obj0 *, void *, Obj2 *);
extern void format_entity_message(s32, Obj3 *);

/* Advance the timed object state sequence and update its direction from flags. */
void advance_timed_object_action(Obj0 *controller, void *context, SpriteFrameState *object, Obj3 *actor) {
    s32 state;
    s32 old_state;
    u16 ticks_left;
    u16 delay;
    u16 object_flags;
    s32 actor_selector;

    state = controller->state9b;
    actor_selector = 1;
    switch (state) {
    case 0:
        object_flags = object->flags;
        if (object_flags & 0x8000) {
            object->flags = (u16) (object_flags | 0x6000);
            controller->state9b = 2;
            return;
        }
        if (object->unk_04 != actor_selector) {
            if ((object_flags & 0x6000) == 0) {
                break;
            }
        } else if ((object_flags & 0x1000) == 0) {
            if ((object_flags & 0x6000) == 0) {
                break;
            }
        }
        create_source_adjusted_motion_object(controller, context, object);
        actor_selector = 1;
        if ((actor->field14 & 0x4000) || (actor_selector = 0, (actor->field60->field14 & 0x4000) != 0)) {
            format_entity_message(actor_selector, actor);
        }
        play_sound_if_enabled(0x80D);
        old_state = controller->state9b;
        delay = 0x20;
        controller->field96 = delay;
        controller->state9b = old_state + 1;
        break;
    case 1:
        ticks_left = controller->field96 - 1;
        controller->field96 = ticks_left;
        if ((ticks_left << 0x10) != 0) {
            if ((object->flags | 0x8000) == 0) {
                break;
            }
        }
        old_state = controller->state9b;
        delay = 4;
        controller->field96 = delay;
        controller->state9b = old_state + 1;
        break;
    case 2:
        ticks_left = controller->field96 - 1;
        controller->field96 = ticks_left;
        if ((ticks_left << 0x10) != 0 && (object->flags & 0xE000) == 0) {
            return;
        }
        spend_actor_mp(actor, 0x400);
        set_record_integer_tile_center(context, object->tile_x, object->tile_y);
        controller->field8c = cyclone_action_resume_address;
        g_dungeon_status.active_actor = 0;
        actor->field46 &= 0x7FFF;
    }

    if (object->flags & 0xE000) {
        object->frameTable = cyclone_move_direction_frames;
        select_sprite_entry(object, cyclone_move_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->field2a + 0x100) >> 9) & 7], 0);
        controller->field98 &= 0xFFF7;
    }

    return;
}
