#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80175D50.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80170700_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0x24];
    s16 unk_38;
} S_80170700_1;

extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 select_sprite_entry();
typedef struct {
    s32 w[12];
} Copy48;
extern s32 D_80170534;
extern u8 encounter_overlay_work[0x3A81];
extern void *beldo_actor_nodes;
extern void *D_80175D64;

/* Creates an object from the current object's data and initializes its position and appearance. */
void create_secondary_encounter_object(void) {
    s32 data_index;
    ObjectPosition *position;
    void *source_data;
    SpriteFrameState *render_data;
    S_80170700_1 *object;

    source_data = ((ObjectNodeHeader *)beldo_actor_nodes)->sprite;
    object = allocate_flagged_object_node(0x112);
    if (object != NULL) {
        render_data = object->unk_0C;
        object->unk_38 = 0;
        object->unk_10 = &D_80170534;
        *(Copy48 *)render_data = *(Copy48 *)source_data;
        render_data->flags =
            (render_data->flags & 0xFF7F) | 0x400;
        register_node(object, project_sprite_chain);
        data_index = *(&encounter_overlay_work[0x3A80]);
        render_data->frameTable = &encounter_overlay_work[0x3A80];
        select_sprite_entry(render_data, data_index, 0);
        render_data->depth_bias = 6;
        render_data->flags &= 0xFFF3;
        position = object->unk_08;
        position->x.w.i = ((u16)view_reference_entity.x.w.i);
        position->y.w.i = ((u16)view_reference_entity.y.w.i) - 0x400;
        position->z.w.i = ((u16)view_reference_entity.z.w.i);
        render_data->scale_y = 0x1000;
        render_data->scale_x = 0x1000;
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        D_80175D64 = object;
    }
}

/* MECHANISM: the 48-byte render-data copy is a struct assignment (mips block-move
   loop: lw/sw x4 through $2-$5, src $7, dst $6, end $8), and register_node takes
   two arguments, so $6 is set once in the function: sched1's birthing boost
   places `move $6,$0` right before the second jal. */
