#include "common.h"
#include "engine/node.h"
#include "slus.h"

/* struct Elem / struct Dst as established in src/code.c for func_8003DB94 */
struct Elem {
    unsigned char b0;
    unsigned char pad1;
    unsigned char pad2;
    unsigned char pad3;
    int f4;
};

struct Dst {
    struct Elem *f0;
    unsigned char f4;
    unsigned char f5;
    unsigned char pad6;
    unsigned char pad7;
    int f8;
    int fc;
    int f10;
    unsigned short f14;
};

extern void update_staged_motion_effect(void);
extern void draw_linked_sprites(void);

/* Sized >8B to force %hi/%lo (not $gp) addressing, matching retail's lui/addiu. */
extern struct Elem arc_motion_sprite_source[2];

typedef struct {
    unsigned char pad00[8];
    int *f8;             /* 0x08: pointer to a 3-int vector */
    struct Dst *fc;      /* 0x0C */
    void (*func)(void);  /* 0x10 */
    unsigned char pad14[0x20 - 0x14];
    void *f20;           /* 0x20 */
    short f24;           /* 0x24 */
    short f26;           /* 0x26 */
} S_80051708;

/* Initializes the object callbacks, sub-object state, linked record, and fixed vector. */
void scene_initialize_arc_motion_sprite(S_80051708 *object, void *sub_object)
{
    struct Dst *record;
    int *vector;
    char *sub_fields = (char *)&object->f20;

    object->func = update_staged_motion_effect;
    object->f20 = sub_object;
    ((short *)sub_fields)[2] = 0;
    ((short *)sub_fields)[3] = 0;

    record = object->fc;
    record->fc = 0x808080;
    select_record_entry_and_value(record, arc_motion_sprite_source, 0);

    *(short *)((char *)record + 0x1E) = 0x1000;
    *(short *)((char *)record + 0x1C) = 0x1000;
    register_node(object, draw_linked_sprites);

    vector = object->f8;
    vector[0] = 0x1C00000;
    vector[1] = 0xC00000;
    vector[2] = 0x800000;
}
