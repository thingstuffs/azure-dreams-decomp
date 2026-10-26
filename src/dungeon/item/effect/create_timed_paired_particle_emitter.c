#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800C4AFC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x18];
    void * unk_1C;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    s32 unk_28;
} S_800C4AFC_0;   /* state in create_timed_paired_particle_emitter */

   /* arg0 in create_timed_paired_particle_emitter */

   /* (void *)temp in create_timed_paired_particle_emitter */

extern void *allocate_list_node(s32, void *);
extern void draw_textured_ellipse(void *, s32 *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void tick_paired_particle_emitter(void);

extern u8 D_800DCF78[12];

/* Create an effect object, copy its source components, and initialize its state. */
void create_timed_paired_particle_emitter(MovingPosition *source, s32 effect_param, s32 state_param)
{
    s32 effect_init[2];
    ObjectNodeHeader *object;
    s32 init_value;
    ObjectPosition *components;
    DungeonGlobalStatus *status;
    u8 *state;
    u8 *effect;
    u16 component_x;
    u16 component_y;
    u16 component_z;

    object = allocate_list_node(0x202, &scene_object_list_anchor.next);
    if (object == NULL) {
        return;
    }

    *(s32 *)D_800DCF78 = effect_param;
    effect_init[0] = 0x01000340;
    init_value = 0x00200020;
    effect_init[1] = init_value;
    effect = D_800DCF78;
    effect -= 0x10;
    draw_textured_ellipse(effect, effect_init, 1, 0);

    state = (u8 *)object + 0x20;
    ((S_800C4AFC_0 *)state)->unk_02 = 0x40;
    object->update_callback = (void *)tick_paired_particle_emitter;
    components = object->position;
    component_x = source->x;
    components->x.w.i = component_x;
    ((S_800C4AFC_0 *)state)->unk_20 = component_x;
    component_y = source->y;
    components->y.w.i = component_y;
    ((S_800C4AFC_0 *)state)->unk_22 = component_y;
    component_z = source->z;
    components->z.w.i = component_z;
    ((S_800C4AFC_0 *)state)->unk_24 = component_z;
    ((S_800C4AFC_0 *)state)->unk_1C = source;
    ((S_800C4AFC_0 *)state)->unk_28 = state_param;
    play_sound_if_enabled(0x702);
    status = &g_dungeon_status;
    (*(u16 *)&status->activity_counts.parts.pending_action_count)++;
}

/* MECHANISM: The 0x30 frame, s1/s2/s3 argument holds, two-word init record, and callee ABIs
   reproduce the retail structure. Moving init[1]'s store immediately before draw_textured_ellipse
   schedules move a3,zero at word 25 and the stack store into the jal delay slot at word 28. */
