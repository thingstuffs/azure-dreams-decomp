#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

extern void func_800C2E84(void *state, s32 output, void *entries);
extern s16 func_800C2B88(s16 x, s16 y, s32 origin);
extern void func_800C3C5C(void);

/* Initialize the object's animation, clear its record flag, and update its facing. */
void func_800C48DC(void *object, s32 position, s32 animation_state) {
    func_800C2E84(object, animation_state, *(void **)((u8 *)*(void **)((u8 *)object + 0x80) + 0x14));
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = (void *)func_800C3C5C;
    *(s16 *)((u8 *)object + 0x72) = func_800C2B88(
        *(s16 *)((u8 *)object + 0x88),
        *(s16 *)((u8 *)object + 0x8A),
        position);
}
