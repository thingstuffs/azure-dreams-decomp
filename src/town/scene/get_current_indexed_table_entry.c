#include "common.h"
#include "town/scene.h"


extern s32 D_80016530[];
extern s32 scene_choice_index;

/* Returns the table entry at the current index. */
s32 get_current_indexed_table_entry(void) {
    s32 index = scene_choice_index;
    return D_80016530[index];
}
