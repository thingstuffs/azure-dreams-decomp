#ifndef SHARED_MONSTER_IDS_H
#define SHARED_MONSTER_IDS_H

/* Species IDs: monster_species_table[0], 20-byte records, name at +4.
 * Names come from the resident game text (see monster_get_species_name_text).
 * Zero and later duplicate/special IDs are deliberately left unnamed.
 * Independent domains: 64 species-name records, 58 initial-stat records at
 * species_base_stats/initialStatsTable, and 57 eight-byte growth records.
 * These counts are not interchangeable bounds on MonsterId. */
enum MonsterId {
    MONSTER_HIKEWNE = 0x1,
    MONSTER_KEWNE = 0x2,
    MONSTER_DRAGON = 0x3,
    MONSTER_KID = 0x4,
    MONSTER_IFRIT = 0x5,
    MONSTER_FLAME = 0x6,
    MONSTER_GRINEUT = 0x7,
    MONSTER_GRIFFON = 0x8,
    MONSTER_SABER = 0x9,
    MONSTER_SNOWMAN = 0xa,
    MONSTER_ASHRA = 0xb,
    MONSTER_ARACHNE = 0xc,
    MONSTER_BATTNEL = 0xd,
    MONSTER_NYUEL = 0xe,
    MONSTER_DEATH = 0xf,
    MONSTER_CLOWN = 0x10,
    MONSTER_UNIVERN = 0x11,
    MONSTER_UNICORN = 0x12,
    MONSTER_METAL = 0x13,
    MONSTER_BLOCK = 0x14,
    MONSTER_PULUNPA = 0x15,
    MONSTER_TROLL = 0x16,
    MONSTER_NOISE = 0x17,
    MONSTER_U_BOAT = 0x18,
    MONSTER_BALOON = 0x19,
    MONSTER_DREAMIN = 0x1a,
    MONSTER_BLUME = 0x1b,
    MONSTER_VOLCANO = 0x1c,
    MONSTER_CYCLONE = 0x1d,
    MONSTER_MANOEVA = 0x1e,
    MONSTER_BARONG = 0x1f,
    MONSTER_PICKET = 0x20,
    MONSTER_KRAKEN = 0x21,
    MONSTER_WEADOG = 0x22,
    MONSTER_STEALTH = 0x23,
    MONSTER_VIPER = 0x24,
    MONSTER_NAPLASS = 0x25,
    MONSTER_ZU = 0x26,
    MONSTER_MANDARA = 0x27,
    MONSTER_KILLER = 0x28,
    MONSTER_GARUDA = 0x29,
    MONSTER_GLACIER = 0x2a,
    MONSTER_TYRANT = 0x2b,
    MONSTER_GOLEM = 0x2c,
    MONSTER_MAXIMUM = 0x2d,
    MONSTER_FROG = 0x2e,
    MONSTER_SALAMAN = 0x2f,
    MONSTER_GUY = 0x30,
    MONSTER_GHOSH = 0x31,
    MONSTER_SELFI = 0x32,
    MONSTER_WALL_OF_FIRE = 0x33,
    MONSTER_WALL_OF_ICE = 0x34,
    MONSTER_WALL_OF_STORM = 0x35,
    MONSTER_ROCK = 0x36,
    MONSTER_BELDO = 0x37,
};

#endif
