#include "common.h"
#include "shared/object_node.h"
#include "shared/town_state.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80024100_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80024100_0;   /* obj in initialize_mogura_minigame */

typedef struct S_80024100_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x4];
    s16 unk_0A;
    u16 unk_0C;
} S_80024100_1;   /* root in initialize_mogura_minigame */

typedef struct S_80024100_2 {
    u8 pad_00[0x4];
    union { s32 i; void * p; } unk_04;   /* accessed as both */
    union { void * p; s32 i; } unk_08;   /* accessed as both */
    union {
        struct { void * v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_0C;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_10;   /* overlapping accesses */
    s16 unk_14;
    union { s16 s; u16 u; } unk_16;   /* accessed as both */
    s16 unk_18;
    s16 unk_1A;
} S_80024100_2;   /* part in initialize_mogura_minigame */



extern TownRewardValues D_80020090;
extern TownRewardValues D_800200A8;
extern s32 D_800243D8;
extern s32 D_80024954;
extern s32 D_800249A0;
extern s32 D_80024A30;
extern s32 D_80053858[4];
extern s32 display_registration_tag;

extern void set_resident_bit(s32);
extern void func_8003E188(s32, void *);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void load_default_object_palette(s32);
extern s32 rand(void);
extern void tw_sd_sq_ld_call(s32, s32);

/* Initializes shared state and three columns of linked display objects. */
s32 initialize_mogura_minigame(void)
{
    TownRewardValues primary_values;
    TownRewardValues secondary_values;
    void *parent_state;
    void *object;
    S_80024100_2 *element;
    void *update_callback;
    void *render_data;
    void *value_ptr;
    s32 column;
    s32 x_first;
    s32 x_second;
    s32 x_third;
    s32 random_value;
    u16 element_flags;

    parent_state = NULL;
    primary_values = D_80020090;
    secondary_values = D_800200A8;

    tw_sd_sq_ld_call(0x24, 0x200);
    set_resident_bit(0x552);
    set_resident_bit(0xA4);
    set_resident_bit(0xA5);
    load_default_object_palette(7);
    func_8003E188(0x3F, parent_state);

    object = allocate_list_node(0x136, ((u8 *)(&scene_object_list_anchor)));
    if (object != NULL) {
        parent_state = (u8 *)object + 0x20;
        ((S_80024100_0 *)object)->unk_10 = &D_800243D8;
        ((S_80024100_1 *)parent_state)->unk_0A = 0x1E;
        random_value = rand();
        ((S_80024100_1 *)parent_state)->unk_04 = random_value & 3;
        ((S_80024100_1 *)parent_state)->unk_0C |= 4;
    }

    column = 2;
    update_callback = &D_80024954;
    x_first = 0xD0;
    do {
        object = allocate_list_node(1, ((u8 *)(&scene_object_list_anchor)));
        element = (u8 *)object + 0x20;
        if (object != NULL) {
            ((S_80024100_0 *)object)->unk_10 = update_callback;
            register_node(object, D_80053858);
            element->unk_16.s = 0xB4;
            element->unk_18 = 3;
            element->unk_1A = 0x7C80;
            element->unk_14 = x_first;
            element->unk_10.at00.v = 0x808080;
            element->unk_04.i = ((s32 *)&primary_values)[column];
            element->unk_0C.at00.v = parent_state;
        }
        column--;
        x_first -= 0x58;
    } while (column >= 0);

    column = 2;
    update_callback = &D_800249A0;
    x_second = 0xD8;
    do {
        object = allocate_list_node(1, ((u8 *)(&scene_object_list_anchor)));
        element = (u8 *)object + 0x20;
        if (object != NULL) {
            ((S_80024100_0 *)object)->unk_10 = update_callback;
            register_node(object, D_80053858);
            element->unk_16.s = 0xC4;
            element->unk_18 = 3;
            element->unk_1A = 0x7C80;
            element->unk_14 = x_second;
            element->unk_10.at00.v = 0x808080;
            element->unk_04.i = ((s32 *)&secondary_values)[column];
            switch (column) {
            case 0:
                element->unk_08.p = (u8 *)parent_state + 6;
                break;
            case 1:
                element->unk_08.p = (u8 *)parent_state + 8;
                break;
            case 2:
                element->unk_08.p = (u8 *)parent_state + 0xA;
                break;
            }
            element->unk_0C.at00.v = parent_state;
        }
        column--;
        x_second -= 0x58;
    } while (column >= 0);

    column = 2;
    update_callback = &D_80024A30;
    x_third = 0xCC;
    do {
        object = allocate_list_node(1, ((u8 *)(&scene_object_list_anchor)));
        if (object != NULL) {
            S_80024100_2 *third_element;
            render_data = &display_registration_tag;
            third_element = (u8 *)object + 0x20;
            ((S_80024100_0 *)object)->unk_10 = update_callback;
            register_node(object, render_data);
            element_flags = third_element->unk_16.u;
            third_element->unk_0C.at02.v = 0xB0;
            third_element->unk_10.at00u.v = 0x50;
            third_element->unk_10.at02.v = 0x20;
            third_element->unk_0C.at00u.v = x_third;
            third_element->unk_14 = 2;
            third_element->unk_08.i = 0x404040;
            third_element->unk_04.p = parent_state;
            element_flags |= 1;
            third_element->unk_16.u = element_flags;
        }
        column--;
        x_third -= 0x58;
    } while (column >= 0);

    return 0;
}
