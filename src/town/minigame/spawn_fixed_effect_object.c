#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/object_links.h"
#include "shared/vector.h"

#ifndef NULL
#define NULL 0
#endif



typedef struct S_800BF3F0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800BF3F0_1;



typedef struct S_800BF3F0_3 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800BF3F0_3;

   /* the 0x2 bytes before arg0 in spawn_fixed_effect_object, addressed as arg0[-1] */


extern void register_node(void *, void *);
extern void configure_the_set_mode_n_1(void *, void *, void *);

extern u8 D_80046398[];
extern u8 D_800BF1C8[];
extern u8 D_800D232C[];
extern s32 D_800D2344[3];

/* Creates and initializes an object, then sets the caller and global flags. */
void spawn_fixed_effect_object(void *caller_data)
{
    S_800BF3F0_3 *transform;
    IntVector3 *position;
    void *object;
    S_800BF3F0_1 *render_state;
    s32 transform_value;
    u32 color;

    object = allocate_flagged_object_node(0x136);
    if (object != NULL) {
        register_node(object, D_80046398);
        color = 0x00808080U;

        ((ProjectileObject *)object)->unk_10 = D_800BF1C8;
        render_state = ((ProjectileObject *)object)->unk_0C;
        render_state->unk_1C = 0x1000;
        render_state->unk_1E = 0x1000;
        render_state->unk_20 = 0x1000;
        render_state->unk_0C = color;
        transform = object + 0x20;
        render_state->unk_1A = 0;
        render_state->unk_08 = 0x4A;
        position = ((ProjectileObject *)object)->unk_08;
        position->x = 0x02C00000;
        position->y = 0x02300000;
        transform_value = D_800D2344[0];
        position->z = 0xFFC00000;
        transform->unk_48 = transform_value;
        configure_the_set_mode_n_1(transform, position, D_800D232C);
    }
    ((ObjectStatusPrefix16 *)caller_data)[-1].unk_00 |= 0x8000;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
