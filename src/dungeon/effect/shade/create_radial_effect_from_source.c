#include "common.h"
#include "m2c_compat.h"

#include "shared/object_node.h"
typedef struct ParticleOrigin ParticleOrigin;
void *create_moving_fading_particle(ParticleOrigin *origin, s16 angle, s16 radius, s16 height_offset, ObjectNodeHeader **allocation_head);
void *allocate_list_node();
s32 register_node();

extern M2C_UNK D_800247AC[3];
s32 draw_adjacent_row_quads(void);

/* Creates an object, copies three source fields to its child, and applies sixteen setup steps. */
void *create_radial_effect_from_source(s32 type_code, void *source, s32 unused, s32 object_value)
{
    register u32 stored_value;
    s32 type_id;
    s32 step;
    void *child;
    void *object;

    stored_value = object_value;
    type_id = type_code - 0x20;
    object = allocate_list_node(2, type_id);
    if (object != 0) {
        *(s32 **)((u8 *)object + 0x10) = D_800247AC;
        register_node(object, draw_adjacent_row_quads);

        child = *(void **)((u8 *)object + 8);
        *(u16 *)((u8 *)child + 2) = *(u16 *)((u8 *)source + 2);
        step = 0;
        *(u16 *)((u8 *)child + 6) = *(u16 *)((u8 *)source + 6);
        *(u16 *)((u8 *)child + 0xA) = *(u16 *)((u8 *)source + 0xA);
        source = (void *)type_id;
        *(s32 *)((u8 *)object + 0x20) = stored_value;

        do {
            create_moving_fading_particle(child, (s16)(step << 8), 0x40, -0x100, source);
            step += 1;
        } while (step < 0x10);
    }
    return object;
}

/* MECHANISM: The 0x38 frame holds s3=source, s5=object_value, s4=type_code-0x20,
   s2=result, s1=child, and s0=loop index; the fifth call arg uses sp+0x10.
   ASM_KEEP(s5) at its true last use changes sched2 prologue entry order only,
   placing the s5 save/copy between the s3 and s4 packets byte-exactly. */
