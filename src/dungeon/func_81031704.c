#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172F04_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F04_0;   /* arg0 in func_80172F04 */


typedef struct S_80172F04_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172F04_2;   /* actor in func_80172F04 */

typedef struct S_80172F04_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172F04_3;   /* arg1 in func_80172F04 */

typedef struct S_80172F04_4 {
    u8 unk_00;
    u8 pad_01[0x3227];
    s16 unk_3228;
    u8 pad_322A[0x242];
    s32 unk_346C;
} S_80172F04_4;   /* (u8 *)work in func_80172F04 */



extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_80083228[];
extern u8 D_801714B8[];
extern u8 D_801760CC[];

/* Advances a timed actor animation sequence and resets its action on completion. */
void func_80172F04(S_80172F04_0 *action, S_80172F04_3 *motion, Rec_D_80082E80 *animation, void *actor_ptr)
{
    register void *actor ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 state;
    u8 current_state;
    u16 timer;
    u8 *direction_table;
    u32 work;
    register void *call_actor ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(animation);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(motion);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    actor = actor_ptr;
    state = action->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    if (animation->unk_14.at00_u16.v & 0x8000) {
        action->unk_9B = 3;
        animation->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, animation, ((S_80172F04_2 *)actor)->unk_2A, 1);
        goto end;
    }
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    goto advance;

state_1:
    timer = action->unk_96 + 1;
    action->unk_96 = timer;
    direction_table = (u8 *)0x80170000;
    if (((s16)timer == 4) || (animation->unk_14.at00_u16.v & 0x8000)) {
        ASM_KEEP(direction_table);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        direction_table += 0x60CC;
        work = 0x80080000;
        ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        animation->unk_2C.as_pu8 = direction_table;
        work = ((S_80172F04_4 *)((u8 *)work))->unk_3228 + ((S_80172F04_2 *)actor)->unk_2A + 0x100;
        work = ((s32)work >> 9) & 7;
        work += (u32)direction_table;
        func_80047784(animation,
            ((S_80172F04_4 *)((u8 *)work))->unk_00,
            0);
        func_800A56E0(0x809);
        goto advance;
    }
    goto end;

state_2:
    timer = action->unk_96 + 1;
    action->unk_96 = timer;
    if (((s16)timer == 4) || (animation->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, animation, ((S_80172F04_2 *)actor)->unk_2A, 1);
        goto advance;
    }
    goto end;

advance:
    current_state = action->unk_9B;
    action->unk_96 = 0;
    action->unk_9B = current_state + 1;
    goto end;

state_3:
    if (animation->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x140);
        call_actor = actor;
        work = (u32)D_801714B8;
        action->unk_8C = (u8 *)work;
        work = 0x80080000;
        ASM_KEEP(work);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_80172F04_4 *)((u8 *)work))->unk_346C = 0;
        func_800A4ACC(call_actor);
        ((S_80172F04_2 *)actor)->unk_46 &= 0x7FFF;
    }

end:
    return;
}
