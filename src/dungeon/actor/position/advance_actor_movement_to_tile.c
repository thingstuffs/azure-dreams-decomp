#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"


extern s32 update_actor_movement_to_tile(void);
extern void advance_status_timers(void *);
extern void set_actor_action_state_eight(void *, s32, s32);

extern u8 actor_motion_resume_address;


typedef struct S_800CAAC8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x22];
    u16 unk_B6;
} S_800CAAC8_0;   /* entity in advance_actor_movement_to_tile */

typedef struct S_800CAAC8_1 {
    u8 pad_00[0x71];
    u8 unk_71;
    u8 pad_72[0x18];
    s16 unk_8A;
} S_800CAAC8_1;   /* actor in advance_actor_movement_to_tile */

/* Updates the actor and entity counter, then advances the entity or sets its callback. */
void advance_actor_movement_to_tile(void *entity_ptr, s32 input_arg_1, s32 input_arg_2, void *actor_ptr)
{
    s32 update_arg_1 = input_arg_1;
    s32 update_arg_2 = input_arg_2;
    void *actor = actor_ptr;
    u16 remaining_count;

    if (update_actor_movement_to_tile() != 0) {
        advance_status_timers(actor);
        remaining_count = ((S_800CAAC8_0 *)entity_ptr)->unk_B6 - 1;
        ((S_800CAAC8_0 *)entity_ptr)->unk_B6 = remaining_count;

        if (((remaining_count << 16) <= 0 || ((*(u16 *)0x80013714) & 8)) &&
            ((S_800CAAC8_1 *)actor)->unk_71 == ((S_800CAAC8_1 *)actor)->unk_8A) {
            set_actor_action_state_eight(entity_ptr, update_arg_1, update_arg_2);
            return;
        }
        ((S_800CAAC8_0 *)entity_ptr)->unk_8C = &actor_motion_resume_address;
    }

    if (g_dungeon_status.flags & 0x80) {
        ((S_800CAAC8_0 *)entity_ptr)->unk_92 = -0x20;
    }
}

