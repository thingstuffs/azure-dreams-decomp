#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"

typedef struct S_81976BC0_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81976BC0_0;   /* object in create_an_initialize_fields_randomized_child_state */

typedef struct S_81976BC0_1 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} S_81976BC0_1;   /* fields in create_an_initialize_fields_randomized_child_state */

extern void *allocate_list_node(s32, void *);
extern s32 rand(void);
extern u8 D_80024050[];
extern s32 D_800261E4[];

/* Create an object and initialize its fields and randomized child state. */
void create_an_initialize_fields_randomized_child_state(s32 object_value, s32 field_value)
{
    s32 random_value;
    SpriteFrameState *child;
    void *object;
    S_81976BC0_1 *fields;

    object = allocate_list_node(0x12, ((u8 *)(&D_80083498)));
    if (object != 0) {
        ((S_81976BC0_0 *)object)->unk_10 = D_80024050;
        fields = (u8 *)object + 0x20;
        fields->unk_0C = 0;
        fields->unk_0E = 0;
        fields->unk_10 = 0;
        ((S_81976BC0_0 *)object)->unk_20 = object_value;
        fields->unk_04 = ((u8 *)(&D_80083498));
        fields->unk_08 = field_value;
        child = ((S_81976BC0_0 *)object)->unk_0C;
        child->source = D_800261E4[0];
        child->color.c.b = 0x40;
        child->color.c.g = 0x40;
        child->color.c.r = 0x40;
        child->scale_y = 0x1800;
        child->scale_x = 0x1800;
        random_value = rand();
        child->angle_z = random_value % 0x1000;
        child->clut = 0x7DCF;
        child->tpage_abr |= 0x20;
        child->flags |= 0x10C;
    }
}
