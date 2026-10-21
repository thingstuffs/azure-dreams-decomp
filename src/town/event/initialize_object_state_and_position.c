#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_handler.h"
#include "shared/vector.h"


extern u8 D_800AA5F8[];
extern void *D_800D0B14;
extern s16 D_80100D18;
extern s32 D_80100D1C;
extern IntVector3 D_80100D28;
extern s16 D_80100D40;
extern s16 D_80100D42;
extern s16 D_80100D60[];
extern u8 D_80100D68[];
extern s16 town_motion_x_step;
extern s16 town_motion_y_step;

/* Initializes object state and sets its starting position. */
void initialize_object_state_and_position(void **object, IntVector3 *start_position, void *ptr2) {
        s32 *position;

    call_the_handler_selects_nonzero_entry((s32 *) D_800D0130, (Rec_func_80094268_arg0 *) object, ptr2);
    *object = D_800AA5F8;
    D_80100D1C = 0;
    town_motion_x_step = 8;
    town_motion_y_step = 8;
    D_80100D40 = 0;
    D_80100D42 = 0;
    D_80100D18 = 0;
    D_80100D60[1] = 0;
    D_80100D60[0] = 0;
    D_80100D28.x = start_position->x;
    position = &D_80100D28.x;
    position[1] = start_position->y;
    D_800D0B14 = D_80100D68;
    position[2] = start_position->z;
}
