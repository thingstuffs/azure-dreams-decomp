#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[4];
    u8 flag;
} State;

extern s32 D_8008099C[];
extern void func_80033CD8(void *, void *);
extern void func_80033D08(void *);
extern void func_80044BB0(void *, void *, void *);
extern void func_800478B8(void *);

/* Routes state processing according to the global gate and state flag. */
void func_8003C0C8(void *state, void *context) {
    if (D_8008099C[0] == 0) {
        if (((State *)state)->flag != 0) {
            func_80033CD8(state, func_80044BB0);
            func_800478B8(context);
            return;
        }
    }

    func_80033D08(state);
}
