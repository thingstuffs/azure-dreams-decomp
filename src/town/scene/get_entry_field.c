#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} TownStruct_800198A4;

extern TownStruct_800198A4 scene_rows[];
extern s32 selected_scene_row_index;

/* Returns unk8 from the currently selected town entry. */
s32 get_selected_entry_field_8(void) {
    return scene_rows[selected_scene_row_index].unk8;
}
