#include "common.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct Block24 {
    s32 word[6];
} Block24;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800644B8(s16);           /* extern */
s16 func_800BCB04(s32, s32, s16); /* extern */
extern s16 D_800259AC;


typedef struct S_80024CE4_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
} S_80024CE4_0;   /* temp_s3 in func_80024CE4 */

typedef struct S_80024CE4_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80024CE4_1;   /* arg2 in func_80024CE4 */

typedef struct S_80024CE4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024CE4_2;   /* temp_s2 in func_80024CE4 */

typedef struct S_80024CE4_3_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80024CE4_3_pre;   /* the 0x18 bytes before (*(void **)((u8 *)arg0 + 0x2C)) in func_80024CE4, addressed as (*(void **)((u8 *)arg0 + 0x2C))[-1] */

typedef struct S_80024CE4_4 {
    u8 pad_00[0x9C];
    s16 unk_9C;
} S_80024CE4_4;   /* (*(void **)((u8 *)arg0 + 0x30)) in func_80024CE4 */

/* Updates a timed effect's oscillation, fade, and scale, then marks it finished. */
void func_80024CE4(void *effect, S_80024CE4_2 *position, S_80024CE4_1 *visual, s32 unused) {
    s16 initialized;
    s16 fade_ticks;
    s16 height_limit;
    s16 ticks_left;
    s16 angle;
    s16 step;
    s32 fade_numerator;
    s32 fade_level;
    s32 wave_height;
    s32 height_offset;
    u16 angle_step;
    u16 amplitude;
    u16 scale;
    void *init_or_snapshot;
    void *global_state;
    void *transform;
    S_80024CE4_0 *view_state;

    D_800259AC = 1;
    global_state = ((void *)&gameWork.view);
    view_state = (u8 *) global_state + 0xB8;
    initialized = (*(s16 *)((u8 *)effect + 0));
    init_or_snapshot = (void *) (u32) (*(u16 *)((u8 *)effect + 0));
    if (initialized == 0) {
        (*(s16 *)((u8 *)effect + 0)) = (s16) ((u32) init_or_snapshot + 1);
        transform = ((S_80024CE4_3_pre *)((*(void **)((u8 *)effect + 0x2C))))[-1].unk_00;
        (*(Block24 *)((u8 *)effect + 0x44)) = (*(Block24 *)((u8 *)transform + 0));
        init_or_snapshot = effect + 0x44;
        if ((view_state->unk_20 == ((u8 *)(&D_80083780))) && ((*(void **)((u8 *)effect + 0x2C)) == ((int)D_800814A8))) {
            view_state->unk_20 = (u8 *) init_or_snapshot;
            (*(s16 *)((u8 *)effect + 0xA)) = 9;
        }
    }
    (*(u16 *)((u8 *)effect + 0x3C)) = 0x40U;
    (*(u16 *)((u8 *)effect + 2)) = (u16) ((*(u16 *)((u8 *)effect + 2)) - 1);
    (*(u16 *)((u8 *)effect + 0x3A)) = (u16) ((*(u16 *)((u8 *)effect + 0x3A)) + 0x96);
    ticks_left = (*(s16 *)((u8 *)effect + 2));
    if (ticks_left >= 0x51) {
        (*(u16 *)((u8 *)effect + 0x38)) = (u16) ((*(u16 *)((u8 *)effect + 0x38)) + 4);
    } else if (ticks_left < 0x32) {
        amplitude = (*(u16 *)((u8 *)effect + 0x38)) - 5;
        (*(u16 *)((u8 *)effect + 0x38)) = amplitude;
        if ((s16) amplitude < 0) {
            (*(u16 *)((u8 *)effect + 0x38)) = 0U;
        }
    }
    fade_ticks = (s16) (*(u16 *)((u8 *)effect + 2));
    if (fade_ticks < 0x14) {
        fade_numerator = fade_ticks << 7;
        fade_level = fade_numerator / 20;
        visual->unk_0E = fade_level;
        visual->unk_0D = fade_level;
        visual->unk_0C = fade_level;
    }
    scale = visual->unk_1C;
    visual->unk_1A = (u16) (visual->unk_1A + 0x10);
    if (scale < 0x1000U) {
        visual->unk_1C = (u16) (scale + 0x100);
        visual->unk_1E = (u16) (visual->unk_1E + 0x100);
    }
    angle = (*(u16 *)((u8 *)effect + 0x3A));
    angle_step = (*(u16 *)((u8 *)effect + 0x3C));
    for (step = 0; step < 0x20; step++) {
        angle += angle_step;
        if (angle >= 0x1001) {
            angle -= 0x1000;
        }
    }
    transform = ((S_80024CE4_3_pre *)((*(void **)((u8 *)effect + 0x2C))))[-1].unk_00;
    wave_height = func_800644B8(angle) * (s16) (*(u16 *)((u8 *)effect + 0x38));
    height_offset = wave_height * 2;
    (*(s32 *)((u8 *)transform + 8)) = height_offset;
    (*(s32 *)((u8 *)transform + 8)) = (s32) (height_offset + (*(s32 *)((u8 *)effect + 0x40)));
    height_limit = func_800BCB04(position->unk_02, position->unk_06, position->unk_0A);
    if (height_limit < (*(s16 *)((u8 *)transform + 0xA))) {
        (*(s16 *)((u8 *)transform + 0xA)) = height_limit;
    }
    if ((s16) (*(u16 *)((u8 *)effect + 2)) <= 0) {
        ((S_80024CE4_4 *)((*(void **)((u8 *)effect + 0x30))))->unk_9C = 1;
        if ((*(s16 *)((u8 *)effect + 0xA)) == 9) {
            view_state->unk_20 = ((u8 *)(&D_80083780));
        }
        (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
