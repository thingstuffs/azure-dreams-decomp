#include "common.h"

typedef struct S_80024D58_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_80024D58_0;   /* base in render_rotated_grid_surface */

typedef struct S_80024D58_1 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    s32 unk_80;
    u8 pad_84[0xAB4];
    s32 unk_B38;
} S_80024D58_1;   /* work in render_rotated_grid_surface */


extern s32 find_active_list_node(void *object);
extern void *initialize_scene_object_in_buffer(s32 value0, void *object, s32 value1);
extern void func_8004491C(void *entry, void *registration_id);
extern void func_80024EEC(void *object);
extern void bzero(void *ptr, s32 size);
extern void func_80024C70(void *work, s32 value);
extern s32 update_effect_color_rotation_and_motion(void *target);
extern void func_80024D18(void *work, s32 parent);

extern u8 D_80027DD0[];
extern u8 D_8002A990[];

/* Create or reset the shared object and initialize its work area. */
void *render_rotated_grid_surface(s32 parent, s32 context, s32 mode)
{
    u8 *base;
    u8 *work;

    base = D_8002A990;
    work = D_8002A990 + 0x20;
    if (find_active_list_node(base) == 0) {
        base = initialize_scene_object_in_buffer(0, base, 0x394);
        func_8004491C(base, D_80027DD0);
    } else {
        func_80024EEC(base);
        ((S_80024D58_0 *)base)->unk_1E &= 0x7FFF;
        bzero(work, 0xE30);
    }

    ((S_80024D58_1 *)work)->unk_7C = context;
    ((S_80024D58_1 *)work)->unk_80 = mode;
    func_80024C70(work, 0x15);
    ((S_80024D58_0 *)base)->unk_0C = work + 0xB2C;
    ((S_80024D58_1 *)work)->unk_B38 = update_effect_color_rotation_and_motion(work + 0xB3C);
    func_80024D18(work, parent);
    ((S_80024D58_0 *)base)->unk_10 = 0;
    return base;
}
