#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

extern s32 func_8004491C();
s32 rand();                                /* extern */
struct DungeonObject;
extern s32 draw_particle_effect_primitives(struct DungeonObject *object, u16 *position);


typedef struct S_800BAF04_0_pre {
    u16 unk_00;
} S_800BAF04_0_pre;   /* the 0x2 bytes before arg0 in advance_particle_effect_state, addressed as arg0[-1] */

typedef struct S_800BAF04_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    s8 unk_10;
    u8 unk_11;
    u8 pad_12[0x20];
    u8 unk_32;
} S_800BAF04_0;   /* arg0 in advance_particle_effect_state */

typedef struct S_800BAF04_1 {
    u8 pad_00[0x12];
    s8 unk_12;
} S_800BAF04_1;

/* Initializes random values, advances counters, and flags the object when inactive. */
void advance_particle_effect_state(void *object) {
    s16 next_index;
    s16 state;
    s16 sample_index;
    u16 cycle_tick;
    u8 ramp_step;

    state = ((S_800BAF04_0 *)object)->unk_0A;
    if (state != 0) {
        if (state != 1) {
            return;
        }
    } else {
        sample_index = 0;
        do {
            ((S_800BAF04_1 *)((object + sample_index)))->unk_12 = (s8) (rand() & 0x1F);
            next_index = sample_index + 1;
            sample_index = next_index;
        } while (next_index < 0x40);
        ((S_800BAF04_0 *)object)->unk_0E = 0U;
        ((S_800BAF04_0 *)object)->unk_10 = 0;
        ((S_800BAF04_0 *)object)->unk_32 = 0U;
        ((S_800BAF04_0 *)object)->unk_11 = 1U;
        func_8004491C(object - 0x20, draw_particle_effect_primitives);
        ((S_800BAF04_0 *)object)->unk_0A = (s16) ((u16) ((S_800BAF04_0 *)object)->unk_0A + 1);
    }
    cycle_tick = ((S_800BAF04_0 *)object)->unk_0E + 1;
    ((S_800BAF04_0 *)object)->unk_0E = cycle_tick;
    if ((s16) cycle_tick >= 0x11) {
        ((S_800BAF04_0 *)object)->unk_0E = 0U;
    }
    ramp_step = ((S_800BAF04_0 *)object)->unk_32 + 1;
    ((S_800BAF04_0 *)object)->unk_32 = ramp_step;
    if ((s8) ramp_step >= 0x21) {
        ((S_800BAF04_0 *)object)->unk_32 = 0x20U;
        ((S_800BAF04_0 *)object)->unk_10 = 1;
    }
    if (((S_800BAF04_0 *)object)->unk_11 == 0) {
        ((S_800BAF04_0_pre *)object)[-1].unk_00 = (u16) (((S_800BAF04_0_pre *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
