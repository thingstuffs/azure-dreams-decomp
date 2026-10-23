#include "common.h"
#include "shared/record_ptrs.h"
/* Call the scene object's 0x248 method, then copy the state's two coordinate pairs across with an offset. */
void copy_event_object_coordinates(void)
{
    void *state;
    void *state_2;
    (*((s32 (**)(s32)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&town_scene_root))) + 0))))
        + 0x20)))) + 0x248)))(0);
    state = *((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&town_scene_root))) + 0)))) + 0x1C));
    *((s32 *) (((s8 *) state) + 0x10)) = (s32) ((*((s32 *) (((s8 *) state) + 4))) + 0x28);
    state_2 = *((void **) (((s8 *) (*((void **) (((s8 *) (((s32 *)&town_scene_root))) + 0)))) + 0x1C));
    *((s32 *) (((s8 *) state_2) + 0x14)) = (s32) (*((s32 *) (((s8 *) state_2) + 8)));
}
