#include "common.h"

extern s32 scene_choice_index[];
extern void *D_80016774[];
extern void *D_80016794[];
extern u8 D_8001BA8C[];
extern u8 D_8001BA91[];

// Selects a data pointer by kind, using the current index for table entries.
void *select_scene_choice_by_mode(s32 unused0, s32 unused1, s32 dataKind) {
    if (dataKind == 5) {
        return D_8001BA91;
    }
    if (dataKind == 4) {
        return D_8001BA8C;
    }
    if (dataKind == 1) {
        return D_80016794[scene_choice_index[0]];
    }
    return D_80016774[scene_choice_index[0]];
}
