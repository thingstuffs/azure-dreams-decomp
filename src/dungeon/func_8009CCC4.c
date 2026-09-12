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
extern s32 func_800A56E0();
extern s32 func_800A5720();
extern s32 func_800B4C7C();

extern u16 D_80013714[];
extern u8 D_8006D168[];
extern u8 D_8006DE24[];
extern u16 D_80083460[];
extern s32 D_800835E8[];
extern M2C_UNK D_80089000;
extern s8 D_800DCF4F[];
extern u8 D_800DDCBC[];
extern M2C_UNK D_800E0458;
extern M2C_UNK D_800E098B;
extern M2C_UNK D_800E099A;
extern M2C_UNK D_800E09B2;
extern M2C_UNK D_800E09BB;

/* Lower an entity by one level, adjust its stats and spells, and optionally show a message. */
s32 func_800A2424(void *entity_data, s32 show_message) {
    u8 spell_lowered[3];
    u8 *entity;
    u8 *stat_growth;
    u8 *initial_stats;
    s32 level;
    s32 level_offset;
    s32 monster_id;
    s32 spell_index;
    s32 message_start;
    s32 message_end;
    s32 lower_stat;
    s32 level_term;
    volatile s32 *xp_table;

    entity = (u8 *)entity_data;
    if (entity[0x11] < 2U) {
        return 0;
    }
    entity[0x11] -= 1;
    level = entity[0x11];
    monster_id = entity[0x13];
    xp_table = D_800835E8;
    *(s32 *)(entity + 0x18) = xp_table[level] - 1;
    stat_growth = D_800DDCBC + (monster_id * 8);
    level_offset = level - 1;
    initial_stats = D_8006D168 + (monster_id * 0x18);

    {
        register s32 base_hp ASM_REG("$6");
        s32 hp_curve;
        s32 lower_hp_growth;
        s32 lower_hp_curve;
        s32 upper_hp_growth;
        s32 upper_hp_curve;
        s32 upper_hp_base;
        register s32 upper_base_hp ASM_REG("$5");
        s32 upper_stat;
        s32 lower_hp_base;
        s32 stat_value;
        hp_curve = func_800647A0((level_offset * stat_growth[5]) << 0xB, monster_id);
        base_hp = *(volatile u8 *)(initial_stats + 5);
        lower_hp_growth = stat_growth[5] * level_offset;
        if (lower_hp_growth < 0) {
            lower_hp_growth += 0xF;
        }
        lower_hp_curve = stat_growth[5] * hp_curve;
        lower_hp_base = base_hp + (lower_hp_growth >> 4);
        if (lower_hp_curve < 0) {
            lower_hp_curve += 0x7FFF;
        }
        lower_stat = lower_hp_base + (lower_hp_curve >> 0xF);

        level_term = level * stat_growth[5];
        hp_curve = func_800647A0(level_term << 0xB, lower_hp_curve, base_hp);
        upper_base_hp = *(volatile u8 *)(initial_stats + 5);
        upper_hp_growth = stat_growth[5] * level;
        if (upper_hp_growth < 0) {
            upper_hp_growth += 0xF;
        }
        upper_hp_curve = stat_growth[5] * hp_curve;
        upper_hp_base = upper_base_hp + (upper_hp_growth >> 4);
        if (upper_hp_curve < 0) {
            upper_hp_curve += 0x7FFF;
        }
        upper_stat = upper_hp_base + (upper_hp_curve >> 0xF);
        ASM_KEEP(upper_base_hp);

        stat_value = entity[5] + (lower_stat - upper_stat);
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[5] = stat_value;
    }

    {
        s32 lower_growth;
        s32 upper_stat;
        s32 stat_value;
        register s32 growth_product ASM_REG("$16");
        {
            s32 base_stat;
            lower_growth = stat_growth[4];
            base_stat = initial_stats[4];
            growth_product = lower_growth * base_stat;
            lower_growth = growth_product * level_offset;
        }
        if (lower_growth < 0) {
            lower_growth += 0x3FF;
        }
        stat_value = growth_product * level;
        lower_stat = initial_stats[4] + (lower_growth >> 0xA);
        if (stat_value < 0) {
            stat_value += 0x3FF;
        }
        upper_stat = initial_stats[4] + (stat_value >> 0xA);
        stat_value = entity[4] + (lower_stat - upper_stat);
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[4] = stat_value;
    }

    {
        s32 base_stat;
        s32 lower_growth;
        s32 upper_growth;
        s32 upper_stat;
        s32 stat_value;
        lower_growth = stat_growth[0];
        base_stat = initial_stats[0];
        spell_index = lower_growth * base_stat;
        lower_growth = spell_index * level_offset;
        stat_value = entity[0];
        if (lower_growth < 0) {
            lower_growth += 0x3F;
        }
        upper_growth = spell_index * level;
        lower_stat = initial_stats[0] + (lower_growth >> 6);
        if (upper_growth < 0) {
            upper_growth += 0x3F;
        }
        upper_stat = initial_stats[0] + (upper_growth >> 6);
        stat_value += lower_stat - upper_stat;
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[0] = stat_value;
    }

    {
        s32 stat_level_offset;
        s32 base_stat;
        s32 lower_growth;
        register s32 upper_growth ASM_REG("$4");
        register s32 upper_stat ASM_REG("$2");
        s32 stat_value;
        stat_level_offset = level - 1;
        lower_growth = stat_growth[1];
        base_stat = initial_stats[1];
        spell_index = lower_growth * base_stat;
        lower_growth = spell_index * stat_level_offset;
        stat_value = entity[1];
        if (lower_growth < 0) {
            lower_growth += 0x3F;
        }
        upper_growth = spell_index * level;
        lower_stat = base_stat + (lower_growth >> 6);
        if (upper_growth < 0) {
            upper_growth += 0x3F;
        }
        upper_stat = base_stat + (upper_growth >> 6);
        stat_value += lower_stat - upper_stat;
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[1] = stat_value;

        lower_growth = stat_growth[2];
        base_stat = initial_stats[2];
        spell_index = lower_growth * base_stat;
        lower_growth = spell_index * stat_level_offset;
        stat_value = entity[2];
        if (lower_growth < 0) {
            lower_growth += 0x3F;
        }
        upper_growth = spell_index * level;
        lower_stat = base_stat + (lower_growth >> 6);
        if (upper_growth < 0) {
            upper_growth += 0x3F;
        }
        upper_stat = base_stat + (upper_growth >> 6);
        stat_value += lower_stat - upper_stat;
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[2] = stat_value;

        lower_growth = stat_growth[3];
        base_stat = initial_stats[3];
        spell_index = lower_growth * base_stat;
        lower_growth = spell_index * stat_level_offset;
        stat_value = entity[3];
        if (lower_growth < 0) {
            lower_growth += 0x3FF;
        }
        upper_growth = spell_index * level;
        lower_stat = base_stat + (lower_growth >> 0xA);
        if (upper_growth < 0) {
            upper_growth += 0x3FF;
        }
        upper_stat = base_stat + (upper_growth >> 0xA);
        stat_value += lower_stat - upper_stat;
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[3] = stat_value;
    }

    {
        s16 base_xp;
        register s32 linear_xp ASM_REG("$4");
        s32 xp_growth;
        s32 xp_factor;
        s32 growth_product;
        u32 xp_given;

        base_xp = *(s16 *)(initial_stats + 6);
        linear_xp = level * base_xp;
        xp_growth = stat_growth[6] * level;
        ASM_KEEP(xp_growth);
        level_term = level * level;
        xp_factor = base_xp + xp_growth;
        growth_product = level_term * xp_factor;
        xp_given = base_xp + linear_xp;
        if (growth_product < 0) {
            growth_product += 0x1FF;
        }
        xp_given += growth_product >> 9;
        if (xp_given > 0xFFFFU) {
            xp_given = 0xFFFF;
        }
        *(u16 *)(entity + 6) = xp_given;
    }

    if (entity[0x13] != 0) {
        spell_index = 2;
        {
            register u8 *spell_flags ASM_REG("$7");
            u8 *spell_table;
            register u8 *spell_cursor ASM_REG("$5");
            register s32 spell_id ASM_REG("$4");
            u8 *lowered_flag;
            spell_flags = spell_lowered;
            spell_table = D_8006DE24;
            level_term = 1;
            spell_cursor = entity + 6;
            do {
                lowered_flag = spell_flags + spell_index;
                *lowered_flag = 0;
                spell_id = spell_cursor[8];
                ASM_KEEP(spell_id);
                if (spell_id != 0 && (((spell_table[spell_id * 0x14 + 0x10] >> 4) & (*(s32 *)(entity + 0x14))) != 0)) {
                    u8 spell_level = spell_cursor[10];
                    if (spell_level >= 2U) {
                        spell_cursor[10] = spell_level - 1;
                        *lowered_flag = level_term;
                    }
                }
                spell_index -= 1;
                spell_cursor -= 3;
            } while (spell_index >= 0);
        }
    }

    func_80041E70(entity);

    if (entity[0x29] < entity[0x28]) {
        entity[0x28] = entity[0x29];
    }
    if (entity[0x66] < entity[0x25]) {
        entity[0x25] = entity[0x66];
        entity[0x24] = (u8)0xFF;
    }
    if (entity[0x68] < entity[0x26]) {
        entity[0x26] = entity[0x68];
    }
    if (entity[0x69] < entity[0x27]) {
        entity[0x27] = entity[0x69];
    }

    if ((show_message << 0x10) == 0) {
        return 1;
    }
    ASM_SCHED_BARRIER();
    {
        if (!(*(volatile u16 *)D_80013714 & 1)) {
            D_800DCF4F[0] = 1;
            D_80083460[5]++;
        }
        func_800B4C7C(0x8003, entity, -3, 1);
        func_800A56E0(0x615);

        message_start = func_800990FC();
        message_end = func_80099194(&D_800E098B, message_start);
        message_end = func_8009929C(0xA, message_end);
        message_end = func_80099734(entity, message_end);
        message_end = func_80099194(&D_800E099A, message_end);
        message_end = func_8003AD08(entity[0x11], message_end);
        message_end = func_80099194(&D_80089000, message_end);

        if (entity[0x13] != 0 && ((*(s32 *)(entity + 0x14) & 0x4000) != 0)) {
            spell_index = 0;
            do {
                if (spell_lowered[spell_index] != 0) {
                    message_end = func_8009929C(0xA, message_end);
                    message_end = func_80099194(*(s32 *)(D_8006DE24 + entity[8] * 0x14), message_end);
                    message_end = func_80099194(&D_800E09B2, message_end);
                    message_end = func_80099194(&D_800E09BB, message_end);
                }
                spell_index += 1;
                entity += 3;
            } while (spell_index < 3);
        }

        if (!(D_80013714[0] & 1)) {
            message_end = func_8009929C(0x11, message_end);
            message_end = func_8009929C(0x4C, message_end);
            message_end = func_80099254(&D_800E0458, message_end);
        }
        func_80099290(message_end, message_end);
        func_800A5720(message_start);
    }
    return 1;
}
