#ifndef SLUS_JTBL_80052144_H
#define SLUS_JTBL_80052144_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct Child {
    u8 pad00[0x1E];
    u16 flags;
} Child;

typedef struct Controller {
    s16 state;
    s16 timer;
    s16 attached;
    s16 finished;
    s16 *script;
    Child *child0;
    Child *child1;
    Child *child2;
    Child *child3;
    void *group;
} Controller;

typedef struct Shared83160 {
    u8 pad00[0x10];
    s32 flags10;
} Shared83160;

extern Shared83160 D_80083160;

extern s32 D_800814A0;


extern void reset_group_and_flag_children(struct Main *main);
extern void func_800530C4(void *);
extern s16 SD_Call(s32);
extern s32 read_sound_mode_blocking_status(s32);
extern void mark_staged_motion_effect_complete(void *);
extern void mark_sine_motion_effect_complete(void *);
extern void mark_timed_animation_sequence_complete(void *);
extern void mark_fade_in_out_effect_complete(void *);
extern void mark_color_fade_effect_complete(void *);
extern void request_scene_state_with_parameters(s32, s32, s32, s32, s32);

/* Advances the timed child sequence and retires the controller when all children finish. */

void update_scene_effect_controller(struct Controller *controller);
void func_80052144(Controller *controller);

#endif
