#include "common.h"
#include "town/scene.h"

extern s32 scene_captured_flags[];
extern u8 D_00004154[];
extern s32 D_0000414C[];
extern s32 D_000045F8[];

/* Return the base value plus the unsigned-index table adjustment. */
s32 get_unsigned_indexed_adjustment(void) {
    return D_000045F8[0] + D_0000414C[D_00004154[scene_captured_flags[0]]];
}
