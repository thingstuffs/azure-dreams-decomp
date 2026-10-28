#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "dungeon/actor.h"

struct Dst;
struct Elem;

extern void select_record_entry_and_value(void *state, void *entries, short index);        /* extern */
s32 generate_random_value(void);   /* extern */
extern u8 actor_alternate_frames[];

typedef struct S_80097898_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80097898_0;   /* arg0 in run_saved_actor_action */

typedef struct S_80097898_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_80097898_1;   /* saved in run_saved_actor_action */

/* Resets the actor action state, sometimes clears flags 0x620, and selects the alternate animation for
   its facing. */
void run_saved_actor_action(void *object, s32 unused, void *animation, void *actor) {
        /* MATCH: retain retail's a0 table base after the explicit argument call. */
    u8 *table;
        /* MATCH: save a2 then a3 before loading the state-byte constant. */
    SpriteFrameState *saved2 = animation;
    S_80097898_1 *saved = actor;
    ((S_80097898_0 *)object)->unk_9A = 0x39;
    ((S_80097898_0 *)object)->unk_9B = 0;
    ((S_80097898_0 *)object)->unk_8C = 0;
    if (!(generate_random_value() & 3)) {
        saved->unk_1C = (s32) (saved->unk_1C & ~0x620);
    }
    table = actor_alternate_frames;
    saved2->frameTable = table;
    select_record_entry_and_value(saved2, (*(void **)((u8 *)table + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + saved->unk_2A
        + 0x100) >> 7) & 0x1C))), 0);
}
