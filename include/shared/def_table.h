#ifndef SHARED_DEF_TABLE_H
#define SHARED_DEF_TABLE_H

/* Read-only 0x14-byte spell/action definition at D_8006DE24 (52 text rows).
 * create_actor_spell_effect selects normal_name at +0 or alternate_name at +8.
 * Each name is followed by its description; null text slots are allowed.
 * Keep the shared DefEntry name: non-spell consumers also inspect the trailing
 * action bytes, whose complete domains have not been established. */
typedef struct DefEntry {
    /* 0x00 */ const unsigned char *normal_name;
    /* 0x04 */ const unsigned char *normal_description;
    /* 0x08 */ const unsigned char *alternate_name;
    /* 0x0C */ const unsigned char *alternate_description;
    /* 0x10 */ unsigned char unk_10;
    /* 0x11 */ unsigned char unk_11;
    /* 0x12 */ unsigned char kind;
    /* 0x13 */ unsigned char unk_13;
} DefEntry;

extern DefEntry item_action_definitions[];

#endif
