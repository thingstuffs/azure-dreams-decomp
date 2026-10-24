#include "common.h"
#include "engine/entity.h"
#include "slus/data.h"

/* Build a cumulative cubic table with a quadratic correction after index 20, then store a fixed constant. */
void build_cubic_cumulative_table(void)
{
    s32 cube_base;
    s32 bonus_base;
    s32 index;

    cube_base = 4;
    bonus_base = -20;
    entity_level_thresholds[0] = 0;
    for (index = 1; index < 100; index++, cube_base++) {
        bonus_base++;
        entity_level_thresholds[index] = ((u32)(cube_base * cube_base * cube_base) >> 3) + entity_level_thresholds[index - 1];
        if (bonus_base > 0) {
            entity_level_thresholds[index] = entity_level_thresholds[index] + ((bonus_base * bonus_base) << 5);
        }
    }

    {
        s32 fixed_value = 0xFA56EA00;
        entity_cubic_table_constant[0] = fixed_value;
    }
}
