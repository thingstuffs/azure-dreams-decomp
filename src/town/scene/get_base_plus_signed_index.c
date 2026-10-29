/* Relinked copy of town/func_808B82AC (func_808B82AC.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene.h"

extern s32 scene_captured_flags[];
extern s32 D_00004124[];
extern s8 D_00004130[];
extern s32 D_000045F8[];

/* Return the base value plus the signed-index table adjustment. */
s32 get_base_plus_signed_index(void) {
    return D_000045F8[0] + D_00004124[D_00004130[scene_captured_flags[0]]];
}
