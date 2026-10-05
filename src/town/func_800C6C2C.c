#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

extern void func_800C2E84(void *state, s32 output, void *entries);
extern void func_800C3C5C(void);

/* Apply descriptor setup, clear the indexed flag, and reset the object callback and state. */
void func_800C438C(void *object, s32 unused, s32 setup_context) {
    func_800C2E84(object, setup_context, *(void **) ((u8 *) *(void **) ((u8 *) object + 0x80) + 0x14));
    D_80082660[*(s32 *) ((u8 *) object + 0x60)].unk_00 = 0;
    *(void **) ((u8 *) object + 0x54) = (void *) func_800C3C5C;
    *(s16 *) ((u8 *) object + 0x72) = 0;
}
