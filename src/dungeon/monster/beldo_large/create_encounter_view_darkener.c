#include "shared/object_node.h"
#include "common.h"


typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern void register_node(void *, void *);

extern u8 D_80044BB0[];
extern Copy12 D_80173B1C;
extern u8 D_801701CC[];


typedef struct S_80170298_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80170298_0;   /* part1 in create_encounter_view_darkener */

typedef struct S_80170298_1 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80170298_1;   /* part2 in create_encounter_view_darkener */

/* Allocate a type 0x12 object, clear its state, and attach a copy of the default data. */
void create_encounter_view_darkener(void)
{
    ObjectNodeHeader * object;
    S_80170298_0 *axis_state;
    S_80170298_1 *data_state;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->unk_10) = D_801701CC;
        register_node(object, D_80044BB0);

        axis_state = (object->unk_08);
        axis_state->unk_0A = 0;
        axis_state->unk_06 = 0;
        axis_state->unk_02 = 0;

        data_state = (object->unk_0C);
        data_state->unk_1E = 0;
        data_state->unk_1C = 0;
        data_state->unk_0E = 0;
        data_state->unk_0D = 0;
        data_state->unk_0C = 0;

        (*(Copy12 *)((u8 *)object + 0x48)) = D_80173B1C;
        data_state->unk_08 = (u8 *)object + 0x48;
    }
}
