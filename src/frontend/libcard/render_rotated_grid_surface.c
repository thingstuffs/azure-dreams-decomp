#include "common.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"

typedef struct S_80024D58_1 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    s32 unk_80;
    u8 pad_84[0xAB4];
    s32 unk_B38;
} S_80024D58_1;   /* work in render_rotated_grid_surface */

extern void func_80024EEC(void *object);
extern void func_80024C70(void *work, s32 value);
extern s32 update_effect_color_rotation_and_motion(void *target); /* Unprototyped: compile_error */
extern void func_80024D18(void *work, s32 parent);

extern u8 menu_backdrop_tag[];

/* Create or reset the shared object and initialize its work area. */
void *render_rotated_grid_surface(s32 parent, s32 context, s32 mode)
{
    ObjectNodeHeader *base;
    u8 *work;

    base = card_rotated_grid_object;
    work = card_rotated_grid_object + 0x20;
    if (find_active_list_node(base) == 0) {
        base = initialize_scene_object_in_buffer(0, base, 0x394);
        register_node(base, menu_backdrop_tag);
    } else {
        func_80024EEC(base);
        base->flags &= 0x7FFF;
        bzero(work, 0xE30);
    }

    ((S_80024D58_1 *)work)->unk_7C = context;
    ((S_80024D58_1 *)work)->unk_80 = mode;
    func_80024C70(work, 0x15);
    base->sprite = work + 0xB2C;
    ((S_80024D58_1 *)work)->unk_B38 = update_effect_color_rotation_and_motion(work + 0xB3C);
    func_80024D18(work, parent);
    base->update_callback = 0;
    return base;
}
