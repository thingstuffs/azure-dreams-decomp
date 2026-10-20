#include "modules/dungeon_ovl_18a0800.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80024A98_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024A98_0;   /* node in create_radial_effect_node */

   /* coords in create_radial_effect_node */

   /* arg0 in create_radial_effect_node */

extern u8 D_800DE938[];

/* Creates a visual node at the supplied coordinates with 16 evenly spaced radial effects. */
void *create_radial_effect_node(MovingPosition *source_coords)
{
    s16 angle;
    s32 effect_index;
    SpriteFrameState *part;
    MovingPosition *coords;
    S_80024A98_0 *node;

    node = func_8003FC64(0x202);
    if (node != 0) {
        node->unk_10 = func_80024A00;
        register_node(node, (s32)project_sprite_chain);
        coords = node->unk_08;
        coords->unk_02 = source_coords->unk_02;
        coords->unk_06 = source_coords->unk_06;
        coords->unk_0A = source_coords->unk_0A;
        part = node->unk_0C;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->color.word = 0x808080;
        func_8003DB94(part, D_800DE938, 0);
        part->tpage_abr = 0x20;
        part->flags |= 0xC;
        effect_index = 0;
        angle = (s16)rand();
        do {
            allocate_jittered_effect_node(coords, angle, 0x10, 1);
            effect_index++;
            angle += 0x100;
        } while (effect_index < 0x10);
    }
    return node;
}
