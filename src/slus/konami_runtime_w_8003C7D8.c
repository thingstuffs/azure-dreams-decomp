#include "common.h"

#include "common.h"

typedef struct {
    void *data;
    s32 value;
} Entry;

extern s32 func_8003C5F0(s32 arg0);
extern s32 func_8003C758(void *arg0);
extern void func_8003C67C(s32 arg0);
extern void LoadImage(void *rect, void *data);

extern s32 D_80082D58[];
extern s32 D_8006B200[];
extern s32 D_8006B220[];

/* Processes the selected entry and uploads its two image regions to VRAM. */
s32 func_8003C7D8(s32 entry_group, s32 entry_index) {
    s32 *state = D_80082D58;
    Entry *entries;
    void *entry_data;
    s32 result;

    if (entry_index >= 0) {
        entries = (Entry *)func_8003C5F0(entry_group);
        if (entries != 0) {
            entry_data = entries[entry_index].data;
            if (entry_data != 0) {
                state[2] = entries[entry_index].value;
                result = func_8003C758(entry_data);
                func_8003C67C(result);

                LoadImage(D_8006B220, (void *)D_8006B200[1]);
                LoadImage(&D_8006B220[2],
                          (void *)(D_8006B200[1] + 0x2000));

                return result;
            }
        }
    }

    return -1;
}
