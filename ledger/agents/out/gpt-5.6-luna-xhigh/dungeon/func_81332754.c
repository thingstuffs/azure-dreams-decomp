#include "common.h"

extern s32 D_800814A0;
extern void *D_80164900[];

extern s32 rand(void);
extern void func_800A56E0(s32);
extern void func_801656F8(void *, s32, s32, s32, s32, s32, s32);
extern void func_8016583C(void *, s32, s32, s32, s32, s32, s32);
extern void func_80165D0C(void *, s32, s32, s32, s32, s32, s32);
extern void func_80165F00(void *);
extern void func_8016604C(void *);
extern void func_80166204(void *, s32, s32, s32, s32, s32, s32);

// Advances the effect through its phases, spawning particles and triggering timed effects.
void func_80169754(void *effect_data)
{
    u8 *effect = effect_data;
    s32 spawn_index;
    s32 phase;

    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c34, &&jt_c34
    };
    (void)jt_keep;

    phase = *(s16 *)(effect + 0x12);
    if ((u32)phase >= 5) {
        goto done;
    }
    goto *D_80164900[(u32)phase];

jt_c0:
        *(u16 *)(effect + 0x12) += 1;
        *(s32 *)(effect + 0x64) = (s32)0xFFE80000;

jt_c1:
    {
        u16 timer_value;
        s32 next_timer_value;
        s32 timer_is_active;

        for (spawn_index = 0; spawn_index < 3; spawn_index++) {
            s32 offset_x;
            s32 offset_y;
            offset_x = (s16)((rand() & 0xF) - 8);
            offset_y = (s16)((rand() & 0xF) - 8);
            func_801656F8(effect - 0x20, 0, 0x2040F0, offset_x, offset_y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effect + 0x64));
        }

        for (spawn_index = 0; spawn_index < 5; spawn_index++) {
            s32 offset_x;
            s32 offset_y;
            offset_x = (s16)((rand() & 0xF) - 8);
            offset_y = (s16)((rand() & 0xF) - 8);
            func_8016583C(effect - 0x20, 0, 0x2020F0, offset_x, offset_y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effect + 0x64));
        }

        for (spawn_index = 0; spawn_index < 4; spawn_index++) {
            s32 offset_x;
            s32 offset_y;
            offset_x = (s16)((rand() & 0xF) - 8);
            offset_y = (s16)((rand() & 0xF) - 8);
            func_80166204(effect - 0x20, 0, 0x2020F0, offset_x, offset_y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effect + 0x64));
        }

        *(s32 *)(effect + 0x64) += 0xA000;
        {
            s32 offset_x;
            s32 offset_y;
            offset_x = (s16)((rand() & 0xF) - 8);
            offset_y = (s16)((rand() & 0xF) - 8);
            func_80165D0C(effect - 0x20, 0, 0x2020F0, offset_x, offset_y,
                         ~((~(rand() & 0xF)) & 0x3F),
                         *(s32 *)(effect + 0x64));
        }

        if ((*(u16 *)(effect + 0x18) & 7) == 0) {
            func_800A56E0(0x81D);
        }
        timer_value = *(u16 *)(effect + 0x18);
        next_timer_value = timer_value + 1;
        timer_is_active = (s16)timer_value < 0x14;
        goto increment_common;

jt_c2:
        for (spawn_index = 0; spawn_index < 2; spawn_index++) {
            s32 offset_x;
            s32 offset_y;
            offset_x = (s16)((rand() & 0xF) - 8);
            offset_y = (s16)((rand() & 0xF) - 8);
            func_8016583C(effect - 0x20, 0, 0x2020F0, offset_x, offset_y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effect + 0x64));
        }
        for (spawn_index = 0; spawn_index < 2; spawn_index++) {
            s32 offset_x;
            s32 offset_y;
            offset_x = (s16)((rand() & 0xF) - 8);
            offset_y = (s16)((rand() & 0xF) - 8);
            func_80166204(effect - 0x20, 0, 0x2020F0, offset_x, offset_y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effect + 0x64));
        }
        *(s32 *)(effect + 0x64) += 0x2000;
        if ((u16)(*(u16 *)(effect + 0x18) - 0xF) < 0xB) {
            func_8016604C(effect - 0x20);
        }
        if (*(s16 *)(effect + 0x18) == 0xF ||
            *(s16 *)(effect + 0x18) == 0x14 ||
            *(s16 *)(effect + 0x18) == 0x19) {
            func_80165F00(effect - 0x20);
        }
        if (*(s16 *)(effect + 0x18) < 0x1F &&
            (*(u16 *)(effect + 0x18) & 1) == 0) {
            s32 offset_x;
            s32 offset_y;
            offset_x = (s16)((rand() & 0xF) - 8);
            offset_y = (s16)((rand() & 0xF) - 8);
            func_80165D0C(effect - 0x20, 0, 0x2020F0, offset_x, offset_y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effect + 0x64));
        }
        if ((*(u16 *)(effect + 0x18) & 7) == 0) {
            func_800A56E0(0x81D);
        }
        timer_value = *(u16 *)(effect + 0x18);
        next_timer_value = timer_value + 1;
        timer_is_active = (s16)timer_value < 0x28;

increment_common:
        *(u16 *)(effect + 0x18) = next_timer_value;
        if (timer_is_active) {
            goto done;
        }
        *(u16 *)(effect + 0x18) = 0;
        *(u16 *)(effect + 0x12) += 1;
        goto done;
    }

jt_c34:
    {
        u16 timer_value;
        s32 next_timer_value;
        s32 timer_is_active;

        timer_value = *(u16 *)(effect + 0x18);
        next_timer_value = timer_value + 1;
        timer_is_active = (s16)timer_value < 0xA;
        goto increment_short;

increment_short:
        *(u16 *)(effect + 0x18) = next_timer_value;
        if (!timer_is_active) {
            *(u16 *)(effect - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }

done:
        return;
}
