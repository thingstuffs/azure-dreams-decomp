#include "shared/entity.h"
#include "common.h"
#include "dungeon/item.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/item/effect.h"
#include "dungeon/system.h"
#include "engine/node.h"

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
    void *unk_28;
} S_800C4AFC_0;   /* state in create_timed_paired_particle_emitter */

   /* arg0 in create_timed_paired_particle_emitter */

   /* (void *)temp in create_timed_paired_particle_emitter */

#include "dungeon/effect/screen.h"
extern void tick_paired_particle_emitter(void);

extern u8 D_800DCF78[12];

/* Create an effect object, copy its source components, and initialize its state. */
void create_timed_paired_particle_emitter(ObjectPosition *source, s32 effect_param, void *state_param)
{
    GpuRectBuffer effect_init;
    ObjectNodeHeader *object;
    s32 init_value;
    ObjectPosition *components;
    DungeonGlobalStatus *status;
    S_800C4AFC_0 *state;
    u8 *effect;
    u16 component_x;
    u16 component_y;
    u16 component_z;

    object = allocate_list_node(0x202, &scene_object_list_anchor.next);
    if (object == NULL) {
        return;
    }

    *(s32 *)D_800DCF78 = effect_param;
    effect_init.words[0] = 0x01000340;
    init_value = 0x00200020;
    effect_init.words[1] = init_value;
    effect = D_800DCF78;
    effect -= 0x10;
    draw_textured_ellipse(effect, &effect_init.rect, 1, 0);

    state = (S_800C4AFC_0 *)((u8 *)object + 0x20);
    state->unk_02 = 0x40;
    object->update_callback = (void *)tick_paired_particle_emitter;
    components = object->position;
    component_x = (u16)source->x.w.i;
    components->x.w.i = component_x;
    state->unk_20 = component_x;
    component_y = (u16)source->y.w.i;
    components->y.w.i = component_y;
    state->unk_22 = component_y;
    component_z = (u16)source->z.w.i;
    components->z.w.i = component_z;
    state->unk_24 = component_z;
    state->unk_1C = source;
    state->unk_28 = state_param;
    play_sound_if_enabled(0x702);
    status = &g_dungeon_status;
    (*(u16 *)&status->activity_counts.parts.pending_action_count)++;
}

/* MECHANISM: The 0x30 frame, s1/s2/s3 argument holds, two-word init record, and callee ABIs
   reproduce the retail structure. Moving init[1]'s store immediately before draw_textured_ellipse
   schedules move a3,zero at word 25 and the stack store into the jal delay slot at word 28. */
