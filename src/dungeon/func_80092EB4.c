#include "common.h"

extern void func_800483AC(s32);
extern void func_800485B8(s32);
extern u8 *func_80097F84(u8 *, void *, void *, s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099368(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);

extern u8 D_800DD2EC[];
extern u8 D_800E07C0[];
extern u8 D_800E07D3[];
extern u8 D_800E0874[];
extern u8 D_800E089C[];
extern u8 D_800E08AB[];
extern u8 D_800E08BA[];



typedef struct S_80098614_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x30];
    union { u8 * p; void * p2; } unk_50;   /* accessed as both */
    u8 pad_54[0x32];
    u8 unk_86;
} S_80098614_0;   /* arg0 in func_80098614 */

/* Changes the actor's equipped item and displays status messages. */
void func_80098614(S_80098614_0 *actor, u8 *requested_item)
{
    u8 *item;
    u8 *equipped_item;
    u8 *item_lookup;
    s32 item_flags;
    s32 item_id;
    s32 had_equipped;
    s32 text_end;
    s32 state;

    item = requested_item;
    state = 0;

    if (item != 0) {
        item = func_80097F84(item, D_800E07C0, D_800E07D3, 0);
        if (item == 0) {
            return;
        }
    }

    equipped_item = actor->unk_50.p;
    if (equipped_item != 0) {
        item_flags = equipped_item[3];
        if (item_flags & 0x40) {
            func_800A56E0(0x70A);
            state = func_800990FC();
            text_end = func_8009929C(8, state);
            text_end = func_80099368(equipped_item, text_end);
            text_end = func_80099194(D_800E0874, text_end);
            func_80099290(text_end);
            func_800A5720(state);
            return;
        }
        equipped_item[3] = item_flags & 0xDF;
        if (equipped_item == item) {
            item = 0;
        }
        state = 1;
    }

    had_equipped = state;
    if (item != 0) {
        item[3] &= 0x7F;
        item_id = item[0];
        state = func_800990FC();
        text_end = func_8009929C(8, state);
        text_end = func_80099368(item, text_end);
        text_end = func_80099194(D_800E089C, text_end);
        func_80099290(text_end);
        func_800A5720(state);

        if (item[3] & 0x40) {
            actor->unk_1C |= 0x800;
            func_800A56E0(0x70A);
            state = func_800990FC();
            text_end = func_80099368(item, state);
            text_end = func_80099194(D_800E08AB, text_end);
            func_80099290(text_end);
            func_800A5720(state);
        }

        item[3] |= 0x20;
    } else {
        ASM_KEEP(had_equipped);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        item_id = 0;
        if (had_equipped != 0) {
            state = func_800990FC();
            text_end = func_8009929C(8, state);
            text_end = func_80099368(actor->unk_50.p2, text_end);
            text_end = func_80099194(D_800E08BA, text_end);
            func_80099290(text_end);
            func_800A5720(state);
        }

    }

    actor->unk_50.p = item;
    func_800A56E0(0x508);
    {
        s32 lookup_id;

        lookup_id = item_id;
        ASM_KEEP(lookup_id);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        item_lookup = D_800DD2EC;
        ASM_KEEP(item_lookup);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        actor->unk_86 = *(u8 *)((u32)lookup_id + (u32)item_lookup);
        if (lookup_id != 0) {
            func_800485B8(lookup_id);
            return;
        }
    }
    func_800483AC(0);
}
