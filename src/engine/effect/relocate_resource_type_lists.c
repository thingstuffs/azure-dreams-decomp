#include "common.h"
#include "shared/game_work.h"
#include "engine/effect.h"
#include "engine/resource_type_list_layouts_data.h"

/* D_80083160: shared state table (own view here); this function only touches
 * a small sub-record living at +0x1DC (five s32 fields; f0 is untouched by
 * this function, f4/f8/fC/f10 are written). */
typedef struct S_80046D64_Dst {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} S_80046D64_Dst;

typedef struct S_80083160_View {
    u8 pad0[0x1DC];
    S_80046D64_Dst sub;
} S_80083160_View;


/* Sets four list pointers from type offsets and relocates the first list entries. */
void relocate_resource_type_lists(s32 data_base, s16 type_index)
{
    S_80083160_View *state = ((S_80083160_View *)&g_game_work);
    S_80046D64_Dst *lists = &state->sub;
    s32 *first_list;
    s32 *entry;
    s32 remaining;

    first_list = (s32 *) (data_base + resource_type_list_layouts[type_index]->off8 * 4);
    lists->f4 = (s32) first_list;

    entry = first_list;
    remaining = resource_type_list_layouts[type_index]->relocation_count;
    if (remaining > 0) {
        do {
            remaining--;
            *entry += data_base;
            entry++;
        } while (remaining > 0);
    }

    lists->f8 = data_base + resource_type_list_layouts[type_index]->offA * 4;
    lists->fC = data_base + resource_type_list_layouts[type_index]->offC * 4;
    lists->f10 = data_base + resource_type_list_layouts[type_index]->offE * 4;
}
