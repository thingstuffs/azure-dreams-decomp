#include "common.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"

typedef struct S_80027364_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80027364_0;   /* base in create_save_heading */

typedef struct S_80027364_1 {
    u8 pad_00[0xEC];
    s32 unk_EC;
} S_80027364_1;   /* work in create_save_heading */

extern void process_nonzero(void *record);
extern void func_8002727C(void *work_state, s32 value);
extern s32 link_save_heading_draw_nodes(void *input);
extern void func_80027324(void *work_state, s32 init_value);

extern u8 menu_backdrop_tag[];

/* Creates or resets the shared object and initializes its work state. */
void *create_save_heading(s32 init_value)
{
    u8 *object;
    u8 *work_state;

    object = D_8002B968;
    work_state = D_8002B968 + 0x20;
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x68);
        register_node(object, menu_backdrop_tag);
    } else {
        process_nonzero(object);
        ((S_80027364_0 *)object)->unk_1E &= 0x7FFF;
        bzero(work_state, 0x180);
    }

    func_8002727C(work_state, 4);
    ((S_80027364_0 *)object)->unk_0C = work_state + 0xE0;
    ((S_80027364_1 *)work_state)->unk_EC = link_save_heading_draw_nodes(work_state + 0xF0);
    func_80027324(work_state, init_value);
    return object;
}
