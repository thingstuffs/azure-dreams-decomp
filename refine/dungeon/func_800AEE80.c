#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B45E0_0_pre {
    u16 unk_00;
} S_800B45E0_0_pre;   /* the 0x2 bytes before arg0 in func_800B45E0, addressed as arg0[-1] */

typedef struct S_800B45E0_0 {
    void * unk_00;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    s16 unk_0E;
    u8 pad_10[0x4];
    void * unk_14;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
} S_800B45E0_0;   /* arg0 in func_800B45E0 */

typedef struct S_800B45E0_1 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800B45E0_1;   /* temp_v0 in func_800B45E0 */

typedef struct S_800B45E0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800B45E0_2;   /* arg1 in func_800B45E0 */

typedef struct S_800B45E0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B45E0_3;   /* temp_v0_2 in func_800B45E0 */

typedef struct S_800B45E0_4 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800B45E0_4;   /* arg2 in func_800B45E0 */

typedef struct S_800B45E0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B45E0_5;   /* ((S_800B45E0_0 *)arg0)->unk_14 in func_800B45E0 */


extern void *D_800892CC[];
extern s32 D_800814A0[];
s32 func_8004491C();
extern M2C_UNK D_80044C54;

/* Update an anchored effect with fading, damped vertical motion, and optional flashing. */
void func_800B45E0(void *effect, S_800B45E0_2 *motion, S_800B45E0_4 *sprite) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 phase;
    s16 next_phase;
    s32 rebound_speed;
    s32 velocity;
    s32 rebound_velocity;
    s32 half_speed;
    s32 update_value;
    u16 fade_in_ticks;
    u16 hold_ticks;
    u16 fade_out_ticks;
    u16 frame;
    register u8 brightness ASM_REG("$3");   /* MATCH pin: retail keeps a computation the compiler would drop */
    u8 next_brightness;
    S_800B45E0_1 *owner;
    S_800B45E0_3 *anchor;

    owner = ((S_800B45E0_0 *)effect)->unk_00;
    if (owner == NULL) {
        goto follow_anchor;
    }
    if (!(owner->unk_1E & 0x8000)) {
        goto follow_anchor;
    }
    ((S_800B45E0_0 *)effect)->unk_00 = NULL;
    ((S_800B45E0_0 *)effect)->unk_14 = NULL;
follow_anchor:
    anchor = ((S_800B45E0_0 *)effect)->unk_14;
    if (anchor == NULL) {
        goto update_phase;
    }
    motion->unk_02 = (u16) (motion->unk_02 - (((S_800B45E0_0 *)effect)->unk_18 - anchor->unk_02));
    ((S_800B45E0_0 *)effect)->unk_18 = (u16) ((S_800B45E0_5 *)(((S_800B45E0_0 *)effect)->unk_14))->unk_02;
    motion->unk_06 = (u16) (motion->unk_06 - (((S_800B45E0_0 *)effect)->unk_1A - ((S_800B45E0_5 *)(((S_800B45E0_0 *)effect)->unk_14))->unk_06));
    ((S_800B45E0_0 *)effect)->unk_1A = (u16) ((S_800B45E0_5 *)(((S_800B45E0_0 *)effect)->unk_14))->unk_06;
    motion->unk_08.at02.v = (u16) (motion->unk_08.at02.v - (((S_800B45E0_0 *)effect)->unk_1C - ((S_800B45E0_5 *)(((S_800B45E0_0 *)effect)->unk_14))->unk_0A));
    ((S_800B45E0_0 *)effect)->unk_1C = (u16) ((S_800B45E0_5 *)(((S_800B45E0_0 *)effect)->unk_14))->unk_0A;
update_phase:
    phase = ((S_800B45E0_0 *)effect)->unk_08;
    if ((u32) phase >= 5U) {
        goto update_motion;
    }
    (void)jt_keep; goto *D_800892CC[(u32)(phase)];
jt_c0:
    motion->unk_14 = 0x200000;
    motion->unk_08.at02.v = (u16) (motion->unk_08.at02.v - 0x40);
    ((S_800B45E0_0 *)effect)->unk_04.at00.v = 0x200000;
    sprite->unk_1E = 0x1000;
    sprite->unk_1C = 0x1000;
    func_8004491C(effect - 0x20, &D_80044C54);
    ((S_800B45E0_0 *)effect)->unk_0A = 0x10U;
    ((S_800B45E0_0 *)effect)->unk_08 = (s16) ((u16) ((S_800B45E0_0 *)effect)->unk_08 + 1);
jt_c1:
    fade_in_ticks = ((S_800B45E0_0 *)effect)->unk_0A - 1;
    ((S_800B45E0_0 *)effect)->unk_0A = fade_in_ticks;
    if ((s16) fade_in_ticks <= 0) {
        goto finish_fade_in;
    }
    brightness = sprite->unk_0C.at02.v;
    next_brightness = brightness + ((s32) (0x80 - brightness) / (s16) fade_in_ticks);
    sprite->unk_0C.at02.v = next_brightness;
    sprite->unk_0C.at01.v = next_brightness;
    sprite->unk_0C.at00.v = next_brightness;
    goto update_motion;
finish_fade_in:
    next_phase = (u16) ((S_800B45E0_0 *)effect)->unk_08 + 1;
    goto advance_phase;
jt_c3:
    hold_ticks = ((S_800B45E0_0 *)effect)->unk_0A - 1;
    ((S_800B45E0_0 *)effect)->unk_0A = hold_ticks;
    if ((hold_ticks << 0x10) > 0) {
        goto update_motion;
    }
    update_value = 8;
    ((S_800B45E0_0 *)effect)->unk_0A = update_value;
    next_phase = (u16) ((S_800B45E0_0 *)effect)->unk_08 + 1;
advance_phase:
    ((S_800B45E0_0 *)effect)->unk_08 = next_phase;
    goto update_motion;
jt_c4:
    fade_out_ticks = ((S_800B45E0_0 *)effect)->unk_0A - 1;
    ((S_800B45E0_0 *)effect)->unk_0A = fade_out_ticks;
    if ((s16) fade_out_ticks <= 0) {
        goto expire;
    }
    brightness = sprite->unk_0C.at02.v;
    next_brightness = brightness + ((s32) (0 - brightness) / (s16) fade_out_ticks);
    sprite->unk_0C.at02.v = next_brightness;
    sprite->unk_0C.at01.v = next_brightness;
    sprite->unk_0C.at00.v = next_brightness;
    goto update_motion;
expire:
    ((S_800B45E0_0_pre *)effect)[-1].unk_00 = (u16) (((S_800B45E0_0_pre *)effect)[-1].unk_00 | 0x8000);
    D_800814A0[0] |= 0x8000;
jt_c2:
update_motion:
    motion->unk_08.at00.v = (s32) (motion->unk_08.at00.v + motion->unk_14);
    frame = ((S_800B45E0_0 *)effect)->unk_0C + 1;
    ((S_800B45E0_0 *)effect)->unk_0C = frame;
    if (!(frame & 1)) {
        goto update_flash;
    }
    velocity = motion->unk_14;
    update_value = velocity >> 1;
    half_speed = velocity >> 0x11;
    if (half_speed >= 0) {
        goto apply_decay;
    }
    half_speed = 0 - half_speed;
apply_decay:
    motion->unk_14 = update_value;
    if (half_speed >= 2) {
        goto update_flash;
    }
    rebound_velocity = 0 - ((s32) ((S_800B45E0_0 *)effect)->unk_04.at00.v >> 1);
    ((S_800B45E0_0 *)effect)->unk_04.at00.v = rebound_velocity;
    motion->unk_14 = rebound_velocity;
    rebound_speed = ((S_800B45E0_0 *)effect)->unk_04.at02.v;
    if (rebound_speed >= 0) {
        goto check_settled;
    }
    rebound_speed = 0 - rebound_speed;
check_settled:
    if (rebound_speed >= 2) {
        goto update_flash;
    }
    if (((S_800B45E0_0 *)effect)->unk_08 >= 3) {
        goto update_flash;
    }
    ((S_800B45E0_0 *)effect)->unk_08 = 3;
    ((S_800B45E0_0 *)effect)->unk_0A = 8U;
update_flash:
    if (((S_800B45E0_0 *)effect)->unk_0E == 0) {
        goto done;
    }
    update_value = 0x2CF0F0F0;
    if (!(((S_800B45E0_0 *)effect)->unk_0C & 3)) {
        goto apply_flash;
    }
    update_value = 0x2C404040;
apply_flash:
    sprite->unk_0C.at00u.v = update_value;
done:
    return;
}
