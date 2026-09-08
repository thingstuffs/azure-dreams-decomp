#include "common.h"

typedef struct S_80172050_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172050_0;   /* actor in func_80172050 */

typedef struct S_80172050_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172050_1;   /* info in func_80172050 */

typedef struct S_80172050_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172050_2;   /* out in func_80172050 */

typedef struct S_80172050_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
} S_80172050_3;   /* call_actor in func_80172050 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C93C(void *, void *, s32, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, s32, s32, s32);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80175F48;

s32 func_80172050(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    volatile u8 frame_pad[8];
    void *out;
    s32 held_arg1;
    register void *info ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *actor;
    void *call_actor;
    u16 *state;
    u8 *table;
    register s32 temp_v0 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 raw_v0;
    s32 result;
    s32 actor84_value;
    u16 flags;

    out = arg0;
    actor = arg3;
    ((S_80172050_0 *)actor)->unk_71 &= 0x7F;
    held_arg1 = arg1;
    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    state = (u16 *)&D_80083460;
    if (state[1] & 0x2000) {
        goto failure;
    }
    info = arg2;

    raw_v0 = func_800A04F0(actor, ((S_80172050_1 *)info)->unk_24,
        ((S_80172050_1 *)info)->unk_25, ((S_80172050_0 *)actor)->unk_2A);
    call_actor = actor;
    temp_v0 = raw_v0;
    if ((func_800A2CB8(call_actor, temp_v0) << 16) == 0) {
        result = 0;
        goto done;
    }

    flags = state[1];
    if (flags & 0x2000) {
        result = -1;
        goto done;
    }
    if (!(((S_80172050_0 *)actor)->unk_46 & 0x8000)) {
        if (flags & 8) {
            result = -1;
            goto done;
        }
    }

    if ((u16)(-func_800A0134(temp_v0, actor) + 0x3F) >= 0x7F) {
        result = 0;
        goto done;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        result = -1;
        goto done;
    }

    func_800C7930((u8 *)actor - 0x20, held_arg1, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        goto success;
    }

failure:
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    result = -1;
    goto done;

success:
    ((S_80172050_2 *)out)->unk_9A = 0x11;
    actor84_value = 0x7C;
    ((S_80172050_2 *)out)->unk_9B = 0;
    ((S_80172050_2 *)out)->unk_8C = 0;
    ASM_KEEP(out);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((S_80172050_0 *)actor)->unk_84 = actor84_value;
    ((S_80172050_0 *)actor)->unk_85 = 4;
    table = &D_80175F48;
    (*(void * *)((u8 *)info + 0x2C)) = table;
    func_80047784(info,
        table[((D_80083228 + ((S_80172050_0 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    call_actor = actor;
    ASM_KEEP(call_actor);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ((S_80172050_3 *)call_actor)->unk_6D--;
    func_8009C93C(call_actor, info, ((S_80172050_3 *)call_actor)->unk_2A, 1, 0);
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    result = 1;

done:
    return result;
}

/* MECHANISM: The eight-byte frame object and pinned long-lived roles reproduce
   retail's 0x40 frame; the held D_80083460 base remains in s2 across calls.
   A fall-through schedule barrier blocks the flags andi, while removing the
   target-head temp_v0 keep lets dbr duplicate move a0,s1 into branch slot R#42. */
