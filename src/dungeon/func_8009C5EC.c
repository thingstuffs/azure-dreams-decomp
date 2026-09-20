#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_8003AD08();
extern s32 func_80041E70();
extern s32 func_800647A0();
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099254();
extern s32 func_80099290();
extern s32 func_8009929C();
extern s32 func_80099734();
extern s32 func_800A5720();
extern s32 func_800B4C7C();

extern u16 D_80013714[];
extern u8 D_8006D168[];
extern u8 D_8006DE24[];
extern u16 D_80083460[];
extern M2C_UNK D_80089000;
extern s8 D_800DCF4F[];
extern u8 D_800DDCBC[];
extern M2C_UNK D_800E0458;
extern M2C_UNK D_800E0953;
extern M2C_UNK D_800E095F;
extern M2C_UNK D_800E0970;
extern M2C_UNK D_800E0979;

/* Raise the entity one level, update its stats, XP reward and abilities, and optionally display a message. */
s32 func_800A1D4C(void *entity_data, s32 show_message) {
    u8 ability_gained[3];
    u8 *stat_growth;
    u8 *initial_stats;
    s32 level;
    s32 prev_level;
    s32 species_id;
    s32 slot;
    s32 message;
    s32 text_end;
    s32 effect_id;
    s32 old_stat;
    s32 level_product;
    s32 level_product_2;

    if (((u8 *)entity_data)[0x11] < 99U) {
        register s32 stat_gain_m ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        level = ((u8 *)entity_data)[0x11];
        species_id = ((u8 *)entity_data)[0x13];
        ((u8 *)entity_data)[0x11] = level + 1;
        stat_growth = D_800DDCBC + (species_id * 8);
        prev_level = level - 1;
        initial_stats = D_8006D168 + (species_id * 0x18);

        {
            register s32 old_base ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            s32 curve_value;
            s32 old_linear;
            s32 old_curve;
            s32 new_linear;
            s32 new_curve;
            s32 new_sum;
            register s32 new_base ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 new_stat;
            s32 old_sum;
            s32 stat;
            s32 old_value;
            curve_value = func_800647A0((prev_level * stat_growth[5]) << 0xB, species_id);
            old_base = *(volatile u8 *)(initial_stats + 5);
            old_linear = stat_growth[5] * prev_level;
            if (old_linear < 0) {
                old_linear += 0xF;
            }
            old_curve = stat_growth[5] * curve_value;
            old_sum = old_base + (old_linear >> 4);
            if (old_curve < 0) {
                old_curve += 0x7FFF;
            }
            old_stat = old_sum + (old_curve >> 0xF);

            level_product = level * stat_growth[5];
            curve_value = func_800647A0(level_product << 0xB, old_curve, old_base);
            new_base = *(volatile u8 *)(initial_stats + 5);
            new_linear = stat_growth[5] * level;
            if (new_linear < 0) {
                new_linear += 0xF;
            }
            new_curve = stat_growth[5] * curve_value;
            new_sum = new_base + (new_linear >> 4);
            if (new_curve < 0) {
                new_curve += 0x7FFF;
            }
            new_stat = new_sum + (new_curve >> 0xF);
            ASM_KEEP(new_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            stat = ((u8 *)entity_data)[5];
            old_value = stat;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            stat_gain_m = stat - old_value;
            ((u8 *)entity_data)[5] = stat;
            ((u8 *)entity_data)[0x28] += stat_gain_m;
        }

        {
            s32 old_scaled;
            s32 new_scaled;
            s32 new_stat;
            s32 stat;
            s32 old_value;
            {
                s32 base_stat;
                old_scaled = stat_growth[4];
                base_stat = initial_stats[4];
                slot = old_scaled * base_stat;
                old_scaled = slot * prev_level;
            }
            if (old_scaled < 0) {
                old_scaled += 0x3FF;
            }
            new_scaled = slot * level;
            old_stat = initial_stats[4] + (old_scaled >> 0xA);
            if (new_scaled < 0) {
                new_scaled += 0x3FF;
            }
               /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            new_stat = initial_stats[4] + (new_scaled >> 0xA);
            stat = ((u8 *)entity_data)[4];
            old_value = stat;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            stat_gain_m = stat - old_value;
            ((u8 *)entity_data)[4] = stat;
            ((u8 *)entity_data)[0x25] += stat_gain_m;
        }

        {
            s32 base_stat;
            s32 old_scaled;
            s32 new_scaled;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s32 new_stat;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 stat;
            s32 old_value;
            old_scaled = stat_growth[0];
            base_stat = initial_stats[0];
            slot = old_scaled * base_stat;
            old_scaled = slot * prev_level;
            stat = ((u8 *)entity_data)[0];
            old_value = stat;
            if (old_scaled < 0) {
                old_scaled += 0x3F;
            }
            new_scaled = slot * level;
            old_stat = initial_stats[0] + (old_scaled >> 6);
            if (new_scaled < 0) {
                new_scaled += 0x3F;
            }
            new_stat = initial_stats[0] + (new_scaled >> 6);
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            stat_gain_m = stat - old_value;
            ((u8 *)entity_data)[0] = stat;
            ((u8 *)entity_data)[0x26] += stat_gain_m;
        }

        {
            s32 prev_step;
            s32 base_stat;
            s32 old_scaled;
            s32 new_stat;
            s32 stat;
            s32 old_value;
            prev_step = level - 1;

            old_scaled = stat_growth[1];
            base_stat = initial_stats[1];
            slot = old_scaled * base_stat;
            old_scaled = slot * prev_step;
            stat = ((u8 *)entity_data)[1];
            old_value = stat;
            if (old_scaled < 0) {
                old_scaled += 0x3F;
            }
            stat_gain_m = slot * level;
            old_stat = base_stat + (old_scaled >> 6);
            if (stat_gain_m < 0) {
                stat_gain_m += 0x3F;
            }
            old_scaled = stat_gain_m >> 6;
            new_stat = base_stat + old_scaled;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            stat_gain_m = stat - old_value;
            ((u8 *)entity_data)[1] = stat;
            ((u8 *)entity_data)[0x27] += stat_gain_m;

            old_scaled = stat_growth[2];
            base_stat = initial_stats[2];
            slot = old_scaled * base_stat;
            old_scaled = slot * prev_step;
            stat = ((u8 *)entity_data)[2];
            if (old_scaled < 0) {
                old_scaled += 0x3F;
            }
            stat_gain_m = slot * level;
            old_stat = base_stat + (old_scaled >> 6);
            if (stat_gain_m < 0) {
                stat_gain_m += 0x3F;
            }
               /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            old_scaled = stat_gain_m >> 6;
            new_stat = base_stat + old_scaled;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            ((u8 *)entity_data)[2] = stat;

            old_scaled = stat_growth[3];
            base_stat = initial_stats[3];
            slot = old_scaled * base_stat;
            old_scaled = slot * prev_step;
            stat = ((u8 *)entity_data)[3];
            if (old_scaled < 0) {
                old_scaled += 0x3FF;
            }
            stat_gain_m = slot * level;
            old_stat = base_stat + (old_scaled >> 0xA);
            if (stat_gain_m < 0) {
                stat_gain_m += 0x3FF;
            }
               /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            old_scaled = stat_gain_m >> 0xA;
            new_stat = base_stat + old_scaled;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            ((u8 *)entity_data)[3] = stat;
        }

        {
            s16 base_xp;
            u32 linear_word;
            s32 word_growth;
            s32 xp_sum;
            s32 growth_product;
            u32 xp_given;

            base_xp = *(s16 *)(initial_stats + 6);
            linear_word = level * base_xp;
            word_growth = stat_growth[6] * level;
            level_product_2 = level * level;
            xp_sum = base_xp + word_growth;
            growth_product = level_product_2 * xp_sum;
            xp_given = base_xp + linear_word;
            if (growth_product < 0) {
                growth_product += 0x1FF;
            }
            xp_given += growth_product >> 9;
            if (xp_given > 0xFFFFU) {
                xp_given = 0xFFFF;
            }
            *(u16 *)(((u8 *)entity_data) + 6) = xp_given;
        }

        if (((u8 *)entity_data)[0x13] != 0) {
            u8 *gained_base;
            s32 gained_flag;
            u8 *ability_table;
            s32 levels_left;
            u8 *ability_slot;
            u8 *gained;
            s32 ability_value;

            slot = 2;
            gained_base = ability_gained;
            ability_table = D_8006DE24;
            gained_flag = 1;
            levels_left = 100 - level;
            ability_slot = ((u8 *)entity_data) + 6;
            loop_0: {
                gained = gained_base + slot;
                *gained = 0;
                ability_value = ability_slot[8];
                if (ability_value != 0) {
                    s32 type_mask = ability_table[ability_value * 0x14 + 0x10] >> 4;
                    if ((type_mask & (*(s32 *)(((u8 *)entity_data) + 0x14))) || !(type_mask & 7)) {
                        s32 ability_level = ability_slot[10];
                        if ((u32) ability_level < 99U) {
                            s32 new_level;
                            s32 level_bonus;
                            ability_slot[10] = ability_level + 1;
                            *gained = gained_flag;
                            ability_value = ability_slot[10];
                            level_bonus = 99;
                            level_bonus = level_bonus - ability_value;
                            level_bonus = level_bonus / levels_left;
                            new_level = level_bonus + ability_value;
                            if (new_level >= 100) {
                                new_level = 99;
                            }
                            ability_slot[10] = new_level;
                        }
                    }
                }
                slot -= 1;
                ability_slot -= 3;
            } if (slot >= 0) goto loop_0;
        }

        func_80041E70(((u8 *)entity_data));

        if ((show_message << 0x10) != 0) {
            if (!(D_80013714[0] & 1)) {
                D_800DCF4F[0] = 1;
                D_80083460[5]++;
            }
            effect_id = 0x8003;
            if ((*(s32 *)(((u8 *)entity_data) + 0x14) & 0x2000) != 0) {
                effect_id = 0x8002;
            }
            func_800B4C7C(effect_id, ((u8 *)entity_data), -2, 1);

            message = func_800990FC();
            text_end = func_80099194(&D_800E0953, message);
            text_end = func_8009929C(0xA, text_end);
            text_end = func_80099734(((u8 *)entity_data), text_end);
            text_end = func_80099194(&D_800E095F, text_end);
            text_end = func_8003AD08(((u8 *)entity_data)[0x11], text_end);
            text_end = func_80099194(&D_80089000, text_end);

            if (((u8 *)entity_data)[0x13] != 0 && ((*(s32 *)(((u8 *)entity_data) + 0x14) & 0x4000) != 0)) {
                u8 *ability_slot;
                u8 *ability_table;
                slot = 0;
                ability_table = D_8006DE24;
                ability_slot = ((u8 *)entity_data);
                do {
                    if (ability_gained[slot] != 0) {
                        text_end = func_8009929C(0xA, text_end);
                        text_end = func_80099194(*(s32 *)(ability_table + ability_slot[8] * 0x14), text_end);
                        text_end = func_80099194(&D_800E0970, text_end);
                        text_end = func_80099194(&D_800E0979, text_end);
                    }
                    slot += 1;
                    ability_slot += 3;
                } while (slot < 3);
            }

            if (!(D_80013714[0] & 1)) {
                text_end = func_8009929C(0x11, text_end);
                text_end = func_8009929C(0x4C, text_end);
                text_end = func_80099254(&D_800E0458, text_end);
            }
            func_80099290(text_end, text_end);
            func_800A5720(message);
        }
    }
}
