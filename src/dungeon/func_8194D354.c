#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "m2c_compat.h"

typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct S_80024B54_0_pre {
    u16 unk_00;
} S_80024B54_0_pre;   /* the 0x2 bytes before arg0 in func_80024B54, addressed as arg0[-1] */

typedef struct S_80024B54_0 {
    s32 unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u16 unk_18;
    s16 unk_1A;
} S_80024B54_0;   /* arg0 in func_80024B54 */

typedef struct S_80024B54_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024B54_1_pre;   /* the 0x14 bytes before temp_v1_2 in func_80024B54, addressed as temp_v1_2[-1] */

typedef struct S_80024B54_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    s16 unk_88;
    u8 pad_8A[0x1C];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
    u8 pad_F8[0x13B0];
    void * unk_14A8;
} S_80024B54_1;   /* temp_v1_2 in func_80024B54 */

typedef struct S_80024B54_3 {
    u8 pad_00[0x14A8];
    void * unk_14A8;
} S_80024B54_3;   /* case2_page in func_80024B54 */

typedef struct S_80024B54_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80024B54_4;   /* table_s5 in func_80024B54 */

typedef struct S_80024B54_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80024B54_5;   /* temp_a0 in func_80024B54 */

typedef struct S_80024B54_6_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
} S_80024B54_6_pre;   /* the 0x18 bytes before temp_v0_3 in func_80024B54, addressed as temp_v0_3[-1] */

typedef struct S_80024B54_7 {
    u8 pad_00[0x2];
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
} S_80024B54_7;   /* var_s1 in func_80024B54 */

typedef struct S_80024B54_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024B54_8;   /* held_arg1 in func_80024B54 */

typedef struct S_80024B54_9 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024B54_9;   /* temp_a2 in func_80024B54 */

typedef struct S_80024B54_10 {
    u8 pad_00[0x2E94];
    u16 unk_2E94;
} S_80024B54_10;   /* var_v0 in func_80024B54 */

typedef struct S_80024B54_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80024B54_11;   /* var_v1 in func_80024B54 */

typedef struct S_80024B54_12 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_80024B54_12;   /* D_800814A8 in func_80024B54 */

typedef struct S_80024B54_13_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024B54_13_pre;   /* the 0x14 bytes before ((S_80024B54_0 *)arg0)->unk_14 in func_80024B54, addressed as ((S_80024B54_0 *)arg0)->unk_14[-1] */

typedef struct {
    UnalignedS32 word;
} Packed4;

typedef struct {
    s32 words[4];
} FourWords __attribute__((aligned(4)));

typedef struct {
    Packed4 part[2];
} Packed8;

void func_8002401C();
void func_80024494();
void func_800249E4();
s32 func_8003DE58();
s32 func_80053EF0();
M2C_UNK func_80065820();
s32 func_80069EF8();
M2C_UNK func_8009CE1C();
void *func_800A05A4();
s32 func_800A45D8();
s32 func_800A56E0();
s16 func_800BCAD0();
extern M2C_UNK D_800DE5DC;
extern s32 D_800E3D18;

/* Updates a three-way effect, selects its target, and animates the target color. */
void func_80024B54(void *effect_arg, void *position) {
    void *effect = effect_arg;
    M2C_UNK fallback_pos[6];
    Packed8 direction;
    FourWords transform[2];
    s16 offset[3];
    M2C_UNK *target_pos;
    register u8 *target_page ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *tile_or_y_steps;
    M2C_UNK *effect_pool;
    EntityRec *origin;
    register void *source_pos ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 phase;
    s32 state_or_heading;
    s32 rounded_phase;
    s32 step_count;
    u16 *input_page;
    s32 position_valid;
    register s32 step_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 clear_tint_mask;
    s32 neutral_color;
    u16 start_delay;
    u16 ground_height;
    u16 near_height;
    u16 tint_delay;
    u16 next_state_c1;
    u16 next_state_c2;
    u16 next_state_c3;
    u8 tile_y;
    void *actor_or_frame;
    void *effect_data;
    s32 offset_mode;
    void *target;
    void *actor_value;
    void *actor_value_2;

    source_pos = position;
    state_or_heading = ((S_80024B54_0 *)effect)->unk_0A.s;
    ((S_80024B54_0 *)effect)->unk_10 = (u16)(((S_80024B54_0 *)effect)->unk_10 + 1);
    switch ((u32)state_or_heading) {
    case 0:
        ((S_80024B54_0 *)effect)->unk_10 = 0U;
        ((S_80024B54_0 *)effect)->unk_0A.s++;
        D_800814A8->unk_F4 = 0;
        func_80024494(((S_80024B54_0 *)effect)->unk_00 - 0x20, ((S_80024B54_0 *)effect)->unk_04, &D_800DE5DC);
    case 1:
        if (*((S_80024B54_0 *)effect)->unk_04 & 0x80) {
            ((S_80024B54_0 *)effect)->unk_18 = 0xAU;
            ((S_80024B54_1 *)D_800814A8)->unk_A6--;
            ((S_80024B54_1 *)D_800814A8)->unk_A8 = ((S_80024B54_0 *)effect)->unk_08;
            next_state_c1 = ((S_80024B54_1 *)D_800814A8)->unk_2A.u;
            ((S_80024B54_0 *)effect)->unk_0A.s++;
            ((S_80024B54_0 *)effect)->unk_0E = next_state_c1;
            if (func_80053EF0(4) != 2) {
                func_800A56E0(0x300);
                ((S_80024B54_0 *)effect)->unk_1A = 0;
                return;
            }
            func_800A56E0(0x4300);
            ((S_80024B54_0 *)effect)->unk_1A = 0;
            return;
        }
        break;
    case 2:
        start_delay = ((S_80024B54_0 *)effect)->unk_18 - 1;
        ((S_80024B54_0 *)effect)->unk_18 = start_delay;
        if ((start_delay << 0x10) > 0) {
            break;
        }
        actor_or_frame = (void *)func_80069EF8();
        rounded_phase = (s32)actor_or_frame;
        if (((s32)actor_or_frame) < 0) {
            rounded_phase = ((s32)actor_or_frame) + 0xFFF;
        }
        origin = &D_80083780;
        step_value = (s32)D_80083780.x.v;
        ASM_CLOBBER("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        target_page = (u8 *)0x80080000;
        (*(s32 *)((u8 *)source_pos + 0)) = step_value;
        step_value = rounded_phase >> 0xC;
        step_value <<= 0xC;
        phase = ((s32)actor_or_frame) - step_value;
        actor_value = (void *)origin->y.v;
        (*(s32 *)((u8 *)source_pos + 4)) = (s32)actor_value;
        ASM_KEEP_NV(target_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        step_value = (s32)0x80080000;
        ASM_KEEP(step_value);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        actor_value = ((S_80024B54_3 *)target_page)->unk_14A8;
        tile_or_y_steps = (u8 *)(step_value + 0x2E80);
        step_value = ((S_80024B54_1 *)actor_value)->unk_88;
        effect_data = offset;
        step_value = (step_value - 0x50) << 0x10;
        (*(s32 *)((u8 *)source_pos + 8)) = step_value;
        step_count = gameWork.view.viewAngle;
        step_value = step_count;
        state_or_heading = ((S_80024B54_1 *)actor_value)->unk_2A.s;
        offset_mode = 0;
        step_value = ((step_value + state_or_heading + 0x100) >> 7) & 0x1C;
        actor_or_frame = (void *)(s32)*(M2C_UNK *)(step_value + D_800E3D18);
        ASM_KEEP_DEP_NV(tile_or_y_steps, actor_or_frame);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if (func_8003DE58(actor_or_frame, tile_or_y_steps, effect_data, offset_mode) != 0) {
            (*(s32 *)((u8 *)source_pos + 0)) = (s32)((*(s32 *)((u8 *)source_pos + 0)) + (offset[0] << 0x10));
            (*(s32 *)((u8 *)source_pos + 4)) = (s32)((*(s32 *)((u8 *)source_pos + 4)) + (offset[1] << 0x10));
            (*(s32 *)((u8 *)source_pos + 8)) = (s32)((*(s32 *)((u8 *)source_pos + 8)) + (offset[2] << 0x10));
        }
        actor_or_frame = ((S_80024B54_3 *)target_page)->unk_14A8;
        target = func_800A05A4(actor_or_frame, ((S_80024B54_4 *)tile_or_y_steps)->unk_24,
            ((S_80024B54_4 *)tile_or_y_steps)->unk_25, (s16)((S_80024B54_5 *)actor_or_frame)->unk_2A, 8);
        ((S_80024B54_0 *)effect)->unk_14 = target;
        if (target != NULL) {
            target_pos = ((S_80024B54_6_pre *)target)[-1].unk_00;
        } else {
            target_pos = fallback_pos;
            step_count = 0;
            ((S_80024B54_7 *)target_pos)->unk_02.u = (u16)((((S_80024B54_4 *)tile_or_y_steps)->unk_24 << 6) + 0x20);
            tile_y = ((S_80024B54_4 *)tile_or_y_steps)->unk_25;
            ((S_80024B54_7 *)target_pos)->unk_06.u = (u16)((tile_y << 6) + 0x20);
            do {
                actor_or_frame = ((S_80024B54_3 *)target_page)->unk_14A8;
                step_value = dirStepX[(((S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                ((S_80024B54_7 *)target_pos)->unk_02.u = (u16)(((S_80024B54_7 *)target_pos)->unk_02.u + (step_value << 6));
                step_value = dirStepY[(((S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                ((S_80024B54_7 *)target_pos)->unk_06.u = (u16)(((S_80024B54_7 *)target_pos)->unk_06.u + (step_value << 6));
                ((S_80024B54_7 *)target_pos)->unk_0A.u = (u16)((S_80024B54_5 *)actor_or_frame)->unk_88;
                ground_height = func_800BCAD0(target_pos);
                ((S_80024B54_7 *)target_pos)->unk_0A.u = ground_height;
                if ((s16)ground_height > 0x200) {
                    ((S_80024B54_7 *)target_pos)->unk_0A.u =
                        (u16)((S_80024B54_12 *)(((S_80024B54_3 *)target_page)->unk_14A8))->unk_88;
                }
                position_valid = func_800A45D8(((S_80024B54_7 *)target_pos)->unk_02.u,
                    ((S_80024B54_7 *)target_pos)->unk_06.u, (s16)((S_80024B54_7 *)target_pos)->unk_0A.u);
                if ((position_valid << 0x10) != 0) {
                    actor_or_frame = ((S_80024B54_3 *)target_page)->unk_14A8;
                    step_value = dirStepX[(((S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                    ((S_80024B54_7 *)target_pos)->unk_02.u = (u16)(((S_80024B54_7 *)target_pos)->unk_02.u - (step_value
                        << 5));
                    step_value = dirStepY[(((S_80024B54_5 *)actor_or_frame)->unk_2A >> 9) & 7];
                    ((S_80024B54_7 *)target_pos)->unk_06.u = (u16)(((S_80024B54_7 *)target_pos)->unk_06.u - (step_value
                        << 5));
                    ((S_80024B54_7 *)target_pos)->unk_0A.u = (u16)((S_80024B54_5 *)actor_or_frame)->unk_88;
                    near_height = func_800BCAD0(target_pos);
                    ((S_80024B54_7 *)target_pos)->unk_0A.u = near_height;
                    if ((s16)near_height > 0x200) {
                        ((S_80024B54_7 *)target_pos)->unk_0A.u =
                            (u16)((S_80024B54_12 *)(((S_80024B54_3 *)target_page)->unk_14A8))->unk_88;
                    }
                    break;
                }
                step_count += 1;
            } while (step_count < 8);
        }
        func_8002401C(((S_80024B54_8 *)source_pos)->unk_02, ((S_80024B54_8 *)source_pos)->unk_06,
            ((S_80024B54_8 *)source_pos)->unk_0A, ((S_80024B54_7 *)target_pos)->unk_02.s,
            (s32)((S_80024B54_7 *)target_pos)->unk_06.s, (s32)((S_80024B54_7 *)target_pos)->unk_0A.s, &direction);
        func_80065820(&direction, transform);
        func_800249E4((s32)effect, source_pos, target_pos, phase, transform[0], transform[1], direction);
        func_800249E4((s32)effect, source_pos, target_pos, (s16)(phase + 0x555), transform[0], transform[1], direction);
        func_800249E4((s32)effect, source_pos, target_pos, (s16)(phase + 0xAAA), transform[0], transform[1], direction);
        next_state_c2 = ((S_80024B54_0 *)effect)->unk_0A.u;
        ((S_80024B54_0 *)effect)->unk_18 = 0x18U;
        ((S_80024B54_0 *)effect)->unk_0A.s = (s16)(next_state_c2 + 1);
        break;
    case 3:
        actor_or_frame = ((S_80024B54_0 *)effect)->unk_14;
        if (actor_or_frame != NULL) {
            (*(s32 *)((u8 *)actor_or_frame + 0x1C)) = (s32)((*(s32 *)((u8 *)actor_or_frame + 0x1C)) | 0x10000000);
            effect_data = ((S_80024B54_13_pre *)(((S_80024B54_0 *)effect)->unk_14))[-1].unk_00;
            if ((s16)((S_80024B54_0 *)effect)->unk_18 >= 0xC) {
                ((S_80024B54_9 *)effect_data)->unk_0C = (u8)(((S_80024B54_9 *)effect_data)->unk_0C + 8);
                ((S_80024B54_9 *)effect_data)->unk_0D = (u8)(((S_80024B54_9 *)effect_data)->unk_0D - 8);
                ((S_80024B54_9 *)effect_data)->unk_0E = (u8)(((S_80024B54_9 *)effect_data)->unk_0E - 8);
                if ((u8)((S_80024B54_9 *)effect_data)->unk_0C >= 0xE1U) {
                    ((S_80024B54_9 *)effect_data)->unk_0C = 0xE0U;
                }
                if ((u8)((S_80024B54_9 *)effect_data)->unk_0D < 0x20U) {
                    ((S_80024B54_9 *)effect_data)->unk_0D = 0x20U;
                }
                if ((u8)((S_80024B54_9 *)effect_data)->unk_0E < 0x20U) {
                    ((S_80024B54_9 *)effect_data)->unk_0E = 0x20U;
                }
                input_page = (u16 *)0x80080000;
            } else {
                ((S_80024B54_9 *)effect_data)->unk_0C = (u8)(((S_80024B54_9 *)effect_data)->unk_0C - 8);
                ((S_80024B54_9 *)effect_data)->unk_0D = (u8)(((S_80024B54_9 *)effect_data)->unk_0D + 8);
                ((S_80024B54_9 *)effect_data)->unk_0E = (u8)(((S_80024B54_9 *)effect_data)->unk_0E + 8);
                if ((u8)((S_80024B54_9 *)effect_data)->unk_0C < 0x80U) {
                    ((S_80024B54_9 *)effect_data)->unk_0C = 0x80U;
                }
                if ((u8)((S_80024B54_9 *)effect_data)->unk_0D >= 0x81U) {
                    ((S_80024B54_9 *)effect_data)->unk_0D = 0x80U;
                }
                input_page = (u16 *)(u32)((S_80024B54_9 *)effect_data)->unk_0E;
                if ((u32)input_page >= 0x81U) {
                    ((S_80024B54_9 *)effect_data)->unk_0E = 0x80U;
                }
                input_page = (u16 *)0x80080000;
            }
        } else {
            input_page = (u16 *)0x80080000;
        }
        if (!(((S_80024B54_10 *)input_page)->unk_2E94 & 0x8000)) {
            tint_delay = ((S_80024B54_0 *)effect)->unk_18 - 1;
            ((S_80024B54_0 *)effect)->unk_18 = tint_delay;
            if ((s16)tint_delay >= 0) {
                break;
            }
        }
        if (((S_80024B54_0 *)effect)->unk_14 != NULL) {
            func_8009CE1C(((S_80024B54_0 *)effect)->unk_14, 0xA, ((S_80024B54_0 *)effect)->unk_09, 9,
                (s32)(s16)((((S_80024B54_0 *)effect)->unk_0E << 9) + 0x800), ((S_80024B54_0 *)effect)->unk_00, 1);
            clear_tint_mask = 0xEFFFFFFF;
            neutral_color = 0x00808080;
            actor_value_2 = ((S_80024B54_0 *)effect)->unk_14;
            ((S_80024B54_1 *)actor_value_2)->unk_1C = (s32)(((S_80024B54_1 *)actor_value_2)->unk_1C & clear_tint_mask);
            effect_data = ((S_80024B54_1_pre *)actor_value_2)[-1].unk_00;
            (*(s32 *)((u8 *)effect_data + 0xC)) = neutral_color;
        }
        effect_pool = (M2C_UNK *)0x80080000;
        if (((S_80024B54_0 *)effect)->unk_1A != 0) {
            next_state_c3 = ((S_80024B54_0 *)effect)->unk_0A.u;
            ((S_80024B54_0 *)effect)->unk_0A.s = (s16)(next_state_c3 + 1);
            break;
        }
    case 4:
        effect_pool = (M2C_UNK *)0x80080000;
        if (((S_80024B54_0 *)effect)->unk_1A != 0) {
            break;
        }
        effect_pool = (M2C_UNK *)((u8 *)effect_pool + 0x3460);
        (*(s32 *)((u8 *)effect_pool + 0xC)) = 0;
        ((S_80024B54_11 *)effect_pool)->unk_0A = (u16)(((S_80024B54_11 *)effect_pool)->unk_0A - 1);
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_80024B54_0_pre *)effect)[-1].unk_00 | 0x8000);
        (*(s32 *)&objectFlagBlock.flags) = (s32)((*(s32 *)((u8 *)(&objectFlagBlock.flags) + 0)) | 0x8000);
        return;
    default:
        break;
    }
    ((S_80024B54_0 *)effect)->unk_1A = 0;
    return;
}
