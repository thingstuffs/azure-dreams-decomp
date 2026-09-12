#include "common.h"
#include "m2c_compat.h"

typedef struct Block24 {
    s32 word[6];
} Block24;
typedef union Product64 {
    s64 value;
    struct {
        s32 hi;
        u32 lo;
    } word;
} Product64;

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083780[12];
extern int D_800814A8[4];
extern s32 D_800814A0[3];
s32 func_800644B8(s16);           /* extern */
s16 func_800BCB04();              /* extern */
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
void func_80024CE4(void *effect, void *position_data, S_80024CE4_1 *visual, s32 unused) {
    s16 initialized;
    s16 fade_ticks;
    s16 next_step;
    s16 height_limit;
    s16 ticks_left;
    s16 angle;
    s16 step;
    s16 next_angle;
    s32 fade_numerator;
    s32 wave_height;
    s32 height_offset;
    s8 brightness;
    u16 angle_step;
    u16 amplitude;
    u16 scale;
    void *init_or_snapshot;
    void *global_state;
    void *transform;
    S_80024CE4_2 *position;
    S_80024CE4_0 *view_state;
    void *position_ptr;
    Product64 fade_product;

    position_ptr = position_data;
    position = position_ptr;
    D_800259AC = 1;
    global_state = &D_80083178;
    view_state = (u8 *) global_state + 0xB8;
    initialized = (*(s16 *)((u8 *)effect + 0));
    init_or_snapshot = (void *) (u32) (*(u16 *)((u8 *)effect + 0));
    if (initialized == 0) {
        (*(s16 *)((u8 *)effect + 0)) = (s16) ((u32) init_or_snapshot + 1);
        transform = ((S_80024CE4_3_pre *)((*(void **)((u8 *)effect + 0x2C))))[-1].unk_00;
        (*(Block24 *)((u8 *)effect + 0x44)) = (*(Block24 *)((u8 *)transform + 0));
        ASM_KEEP_NV(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        init_or_snapshot = effect + 0x44;
        if ((view_state->unk_20 == D_80083780) && ((*(void **)((u8 *)effect + 0x2C)) == *D_800814A8)) {
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
        {
            register s32 product_hi ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            {
                register s32 divide_magic ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                divide_magic = 0x66666667;
                fade_product.value = (s64) fade_numerator * divide_magic;
                ASM_KEEP_NV(fade_product.word.hi);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                product_hi = fade_product.word.hi;
                ASM_KEEP_NV(product_hi);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            }
            {
                register s16 fade_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                fade_value = (product_hi >> 3) - (fade_numerator >> 31);
                brightness = fade_value;
            }
        }
        visual->unk_0E = brightness;
        visual->unk_0D = brightness;
        visual->unk_0C = brightness;
    }
    scale = visual->unk_1C;
    visual->unk_1A = (u16) (visual->unk_1A + 0x10);
    if (scale < 0x1000U) {
        visual->unk_1C = (u16) (scale + 0x100);
        visual->unk_1E = (u16) (visual->unk_1E + 0x100);
    }
    do {
        step = 0;
    } while (0);
    angle = (*(u16 *)((u8 *)effect + 0x3A));
    angle_step = (*(u16 *)((u8 *)effect + 0x3C));
    next_angle = angle + angle_step;
    do {
        if (next_angle >= 0x1001) {
            angle = next_angle - 0x1000;
        } else {
            angle = next_angle;
        }
        next_step = step + 1;
        step = next_step;
        next_angle = angle + angle_step;
    } while (next_step < 0x20);
    transform = ((S_80024CE4_3_pre *)((*(void **)((u8 *)effect + 0x2C))))[-1].unk_00;
    wave_height = func_800644B8(angle) * (s16) (*(u16 *)((u8 *)effect + 0x38));
    height_offset = wave_height * 2;
    (*(s32 *)((u8 *)transform + 8)) = height_offset;
    (*(s32 *)((u8 *)transform + 8)) = (s32) (height_offset + (*(s32 *)((u8 *)effect + 0x40)));
    height_limit = func_800BCB04(position->unk_02, position->unk_06, position->unk_0A, wave_height);
    if (height_limit < (*(s16 *)((u8 *)transform + 0xA))) {
        (*(s16 *)((u8 *)transform + 0xA)) = height_limit;
    }
    if ((s16) (*(u16 *)((u8 *)effect + 2)) <= 0) {
        ((S_80024CE4_4 *)((*(void **)((u8 *)effect + 0x30))))->unk_9C = 1;
        if ((*(s16 *)((u8 *)effect + 0xA)) == 9) {
            view_state->unk_20 = D_80083780;
        }
        (*(u16 *)((u8 *)effect + -2)) = (u16) ((*(u16 *)((u8 *)effect + -2)) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
