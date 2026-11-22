#ifndef SHARED_GAME_STATE_H
#define SHARED_GAME_STATE_H

/* The resident game state block at 0x80010000, below the executable. One record tiles +0x0 .. +0x5C84; the
 * save file is the first 0x6000 bytes of it (0xC0 card units of 128 bytes), so the card image runs 0x37C bytes
 * past the cleared block (+0x5C84 .. +0x5FFF are written and checksummed but never accessed). The block is
 * reset by one bzero of 0x5C84 bytes; options, message speed and the first familiar direction and command
 * survive the reset. In-block addresses are built with lui/ori, so every access spells the address as an integer
 * constant, never as a linked symbol (&game_state would assemble to addiu). */

#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/resident_resources.h"

#define GAME_STATE ((GameState *)0x80010000)

/* Resident item-data slot (19-byte stride). */
typedef struct ItemDataSlotRecord {
    char bytes[0x13];
} ItemDataSlotRecord;

/* The 84-byte encoded slot snapshot written by build_entity_slot_snapshot: ActorRecord +0x00..+0x4B copied as 0x13
 * words, then the two items[] indices of the equipped item pointers (+0x4C, +0x4D) and the +0x54 word. */
typedef struct S_800422DC_Self {
    unsigned char  pad0[0x4C];
    unsigned char  f4C;
    unsigned char  f4D;
    unsigned char  pad4E[2];
    int f50;
} TownSlotSnapshot;

/* The 12-byte header copied by the floor exit and cleared field by field at each floor change. */
typedef struct ActionLogHeader {
    s32 seed;      /* floor random seed, restored, advanced and rewritten when a floor is built */
    u16 flags;     /* general session flag word (system_update_flags); bits 0-1 record/resume, bit 2 go-up path */
    u16 length;    /* entries recorded; append_packed_action_record writes at data + length * 2 */
    u16 repeat;    /* countdown the monster script readers decrement; one retail word read, compared with 3 */
    u16 cursor;
} ActionLogHeader;                    /* 0x0C */

typedef struct ActionLog {
    ActionLogHeader head;
    u8 *data;      /* log_data, or a boss script's own table */
} ActionLog;                          /* 0x10 */

typedef struct GameOptions {
    u32 option_color;  /* options rows 4..6, three 0..255 channels in the low 24 bits */
    u8 unk_3184;       /* options menu stores shade << 5, shade cycled 0..3; consumer not shown */
    u8 unk_3185;       /* reset to 1; render_map_cell_mesh reads it as draw flags */
    u8 unk_3186;       /* bit 0 = inverse of the options row-0 toggle */
    u8 pad_3187;
} GameOptions;                        /* 0x08 */

typedef struct MapViewSettings {
    s16 rect[4];       /* 0xD5, 0x38, 0x6B, 0x70 after a reset: the viewport rectangle */
    s16 unk_08;        /* 0x100 */
    s16 unk_0A;        /* 0x78 */
    s32 scale;         /* 0x4000 */
} MapViewSettings;                    /* 0x10; +0x3630/+0x3634 are also read as words by the viewport transition */

typedef struct TextRecord {
    u8 text[0x12];
    u8 type;           /* +0x12; +0x11 is also read alone as a prefix byte */
} TextRecord;                         /* 0x13 */

/* Written at each floor exit (snapshot_inventory_and_familiars), read back by floor setup. */
typedef struct FloorCarry {
    TownSlotSnapshot player;                      /* 0x000 build_entity_slot_snapshot(0x80012194, player) */
    DungeonItemEntry items[20];                   /* 0x054 */
    u8 item_list[20];                             /* 0x0A4 items[] index of each list entry, 0xFF none */
    u8 familiar_slots[20];                        /* 0x0B8 familiar_record_storage index, 0xFF none */
    u8 familiar_records[20][0x8C];                /* 0x0CC copy of familiar_record_storage (0xAF0) */
    u16 player_F8;                                /* 0xBBC copy of player +0xF8 */
    u8 familiar_items[2];                         /* 0xBBE items[] index held by each familiar slot */
    u8 unk_BC0[4];
    s32 dungeon_money;                            /* 0xBC4 gold picked up in the tower (player +0xFC); added to town_money on return */
} FloorCarry;                                     /* 0xBC8 */

typedef struct GameState {
    u8 card_header[0x200];        /* 0x0000 card file header: magic word, title +0x04, CLUT +0x60, 3 icon frames +0x80 */
    u8 unk_0200[4];
    s32 checksum;                 /* 0x0204 XOR of 0x177E words from +0x208 */
    s16 dungeon_save_marker;      /* 0x0208 1 when the save mode is 2 (card title "D" or "T"); cleared after a load */
    s16 resume_in_dungeon;        /* 0x020A same (mode == 2) value; picks scene mode 5 or 6 on load */
    char player_name[16];         /* 0x020C default "Koh" */
    u32 unk_021C;                 /* 0x021C main() adds animation_tick_scale once per frame; no reader found */
    u8 unk_0220[4];
    s32 saved_money;              /* 0x0224 town_money at save time */
    s32 saved_building_total;     /* 0x0228 */
    s32 tower_entry_count;        /* 0x022C ++ on a fresh tower visit; trailing number of the card title */
    s32 saved_flag_mask;          /* 0x0230 eight event flags: seven Ft_*_love and F_veld_kill */
    s32 dungeon_floor;            /* 0x0234 */
    char kewne_name[16];          /* 0x0238 default "Kewne" */
    DungeonItemEntry items[20];   /* 0x0248 */
    DungeonItemEntry pickup_item; /* 0x0298 */
    DungeonItemEntry *item_list[21]; /* 0x029C town_item_list, zero-terminated (the 21st word has no decoded access) */
    TownSlotSnapshot item_monsters[20]; /* 0x02F0 */
    DungeonItemEntry town_monster_entries[64]; /* 0x0980 */
    TownSlotSnapshot town_monsters[64]; /* 0x0A80 monster hut records */
    DungeonItemEntry unk_1F80[64];      /* 0x1F80 house storage (read from function names only) */
    ActionLogHeader saved_log_header;   /* 0x2080 */
    s32 ending_requested;         /* 0x208C set on floor 40 while resident bit 0xA2 (F_end_ending) is clear */
    s32 dungeon_mode_state;       /* 0x2090 */
    u16 familiar_direction[2];    /* 0x2094 */
    u16 familiar_command[2];      /* 0x2098 */
    u16 fruit_counter_saved;      /* 0x209C */
    u16 fruit_counter;            /* 0x209E */
    u16 camera_depth_index;       /* 0x20A0 */
    u16 camera_pitch_index;       /* 0x20A2 */
    u16 unk_20A4;
    u8 unk_20A6[0xEE];
    FloorCarry carry;             /* 0x2194 */
    s32 town_money;               /* 0x2D5C */
    u32 deepest_floor;            /* 0x2D60 */
    u8 unk_2D64[4];
    s32 unk_2D68;
    u8 carry_player_FA[2];        /* 0x2D6C copy of player +0xFA..+0xFB */
    u8 message_speed;             /* 0x2D6E */
    u8 pad_2D6F;
    u32 event_flags[0x104];       /* 0x2D70 resident flag bitmap; script ids reach 5327 (word 166), the rest is an upper bound */
    GameOptions options;          /* 0x3180 */
    u8 unk_3188[0x214];
    s16 best_score_339C, best_score_339E; /* 0x339C */
    u8 unk_33A0[4];               /* held: the town reads an s16, the dungeon a word */
    u8 building_slots[34][2];     /* 0x33A4 */
    ItemDataSlotRecord item_data[20]; /* 0x33E8 */
    ResourceCategoryPair item_data_keys[20]; /* 0x3564 */
    s32 keima_best_time;          /* 0x35B4 */
    u8 unk_35B8[4];
    u16 high_display_best_score;  /* 0x35BC */
    u16 tako_best_score;          /* 0x35BE */
    u16 snowball_best_score;      /* 0x35C0 */
    s16 gym_high_score;           /* 0x35C2 */
    u8 unk_35C4[17][4];           /* 0x35C4 byte-accessed records: byte 0 a count capped at 3, bytes 2/3 per speaker */
    u8 building_palette[2][2];    /* 0x3608 */
    u8 resident_bytes[8];         /* 0x360C */
    u8 catalog_flags[16];         /* 0x3614 two bits per entry */
    u16 egg_counter_saved;        /* 0x3624 */
    u16 egg_counter;              /* 0x3626 */
    s32 dungeon_seed;             /* 0x3628 */
    s32 saved_turn_counter;       /* 0x362C */
    MapViewSettings map_view;     /* 0x3630 */
    u8 unk_3640[0x78];
    u8 unk_36B8;                  /* 0x36B8 read-only: 0xB/0xC/0xD choose map entry lists and texture sets */
    u8 unk_36B9[0x57];
    ActionLog log;                /* 0x3710 */
    u8 log_data[0x2000];          /* 0x3720 */
    u8 item_mark_bits[0x13][8];   /* 0x5720 one bit per item of each item category group (item flag 0x400) */
    u8 unk_57B8[8];
    TextRecord text_records[64];  /* 0x57C0 */
    s32 text_record_next;         /* 0x5C80 wraps at 64 */
} GameState;                                      /* 0x5C84 */

/* The card file is this block plus the unused tail. */
typedef struct GameStateSaveFile {
    GameState state;
    u8 tail[0x37C];
} GameStateSaveFile;                              /* 0x6000 */

#endif
