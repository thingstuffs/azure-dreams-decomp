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

s32 func_8003C7D8(s32 arg0, s32 arg1) {
    s32 *state = D_80082D58;
    Entry *entries;
    void *data;
    s32 result;

    if (arg1 >= 0) {
        entries = (Entry *)func_8003C5F0(arg0);
        if (entries != 0) {
            data = entries[arg1].data;
            if (data != 0) {
                state[2] = entries[arg1].value;
                result = func_8003C758(data);
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
