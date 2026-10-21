#include "common.h"

extern void *check_inputs_after_threshold_two(void *);

extern s32 scene_dispatch_mode_index[3];
extern void *D_80019698[3];
extern u8 D_8001A730[9];
extern u8 D_8001AAEC[9];
extern u8 D_8001DE58[9];

/* Returns data selected by kind and the current global index. */
void *select_data_by_kind_and_index(s32 unused_0, s32 unused_1, s32 data_kind) {
    void *data = 0;

    if (data_kind == 8) {
        data = check_inputs_after_threshold_two(D_80019698[scene_dispatch_mode_index[0]]);
    } else if (data_kind == 6) {
        data = D_8001A730;
    } else if (data_kind == 1) {
        if (scene_dispatch_mode_index[0] != 3) {
            data = D_8001DE58;
        } else {
            data = D_8001AAEC;
        }
    }

    return data;
}
