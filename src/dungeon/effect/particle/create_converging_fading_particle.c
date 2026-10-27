/* row func_8132E2FC, true base 0x801652FC -- exemplar-seeded from landed
 * func_80BC1528 (MATCH @2.7.2-cdk-G0, gate_verified). Opcode-sequence
 * similarity 0.9843. Ordinary code: no symbol alias, no .text section
 * attribute, no literal word arrays, first word is the prologue.
 *
 * Adaptation measured off the retail stream:
 *   - one fewer parameter (exemplar's arg2 is gone; the value stored at
 *     obj+0x20 / tail+8 is arg1 here), so every later arg shifts one slot
 *   - `((S_801652FC_0 *)tail)->unk_14 = arg1` is absent
 *   - the six vector fields sit 0xC higher (0x36->0x42 ... 0x54->0x60)
 *   - the z bias is -40, not -100
 *   - the two overlay data symbols are this image's
 */
#include "common.h"
#include "dungeon/effect/particle.h"
#include "shared/object_node.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_801652FC_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0xE];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
    u8 pad_48[0x4];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_801652FC_0;   /* tail in create_converging_fading_particle */

typedef struct S_801652FC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_801652FC_1;   /* obj in create_converging_fading_particle */

typedef struct S_801652FC_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801652FC_2;   /* saved_arg0 in create_converging_fading_particle */

typedef struct S_801652FC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_801652FC_3;   /* ((S_801652FC_1 *)obj)->unk_08 in create_converging_fading_particle */

   /* ((S_801652FC_2 *)saved_arg0)->unk_08 in create_converging_fading_particle */

extern void *allocate_list_node(s32, void *);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern u8 child_particle_draw_address[];

/* Creates an offset object and initializes its source position and motion parameters. */
void create_converging_fading_particle(
    void *source, s32 initial_value, s32 duration, s32 offset_x,
    s32 offset_y, s32 offset_z)
{
    S_801652FC_2 *source_obj = source;
    s32 saved_offset_x = offset_x;
    s32 saved_offset_y = offset_y;
    s32 saved_offset_z = offset_z;
    ObjectNodeHeader *object;
    void *state;
    s32 calculation;
    s32 quotient_x;
    s32 quotient_y;
    s32 quotient_z;
    s32 rounded_x;
    s32 rounded_z;

    object = allocate_list_node(0x211, source_obj);
    if (object != 0) {
        object->update_callback = update_converging_fading_particle;

        ((S_801652FC_3 *)(object->position))->unk_02 =
            ((MovingPosition *)(source_obj->unk_08))->x + saved_offset_x;
        ((S_801652FC_3 *)(object->position))->unk_06 =
            ((MovingPosition *)(source_obj->unk_08))->y + saved_offset_y;
        ((S_801652FC_3 *)(object->position))->unk_0A =
            ((MovingPosition *)(source_obj->unk_08))->z + saved_offset_z - 40;

        state = (u8 *)object + 0x20;
        ((S_801652FC_0 *)state)->unk_42 = ((MovingPosition *)(source_obj->unk_08))->x;
        ((S_801652FC_0 *)state)->unk_44 = ((MovingPosition *)(source_obj->unk_08))->y;
        ((S_801652FC_0 *)state)->unk_46 = ((MovingPosition *)(source_obj->unk_08))->z;

        quotient_x = -(saved_offset_x << 16) / ((s16)duration / 8);
        calculation = quotient_x / 2;
        ((S_801652FC_0 *)state)->unk_4C = calculation;
        calculation = -(saved_offset_y << 16);
        quotient_y = calculation / ((s16)duration / 8);
        calculation = quotient_y / 2;
        ((S_801652FC_0 *)state)->unk_50 = calculation;
        calculation = -(saved_offset_z << 16);
        quotient_z = calculation / ((s16)duration / 8);
        rounded_x = quotient_z / 2;
        ((S_801652FC_0 *)state)->unk_54 = rounded_x;

        rounded_x = quotient_x;
        if (rounded_x < 0) {
            rounded_x += 3;
        }
        ((S_801652FC_0 *)state)->unk_58 = rounded_x >> 2;

        rounded_z = quotient_y;
        if (rounded_z < 0) {
            rounded_z += 3;
        }
        ((S_801652FC_0 *)state)->unk_5C = rounded_z >> 2;

        rounded_z = quotient_z;
        ((S_801652FC_0 *)state)->unk_60 = (rounded_z / 4);

        ((S_801652FC_0 *)state)->unk_32 = duration;
        register_node(object, child_particle_draw_address);
        rounded_x = initial_value;
        ((S_801652FC_1 *)object)->unk_20 = rounded_x;
        ((S_801652FC_0 *)state)->unk_08 = initial_value;
    }

}
