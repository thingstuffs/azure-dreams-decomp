#ifndef TOWN_SCENE_COLLECTION_H
#define TOWN_SCENE_COLLECTION_H

#include "common.h"
#include "shared/entity.h"

struct ObjectNodeHeader;
extern struct ObjectNodeHeader *scene_object_factory_data;

/* Collection-round setup initializes the three velocity words. The betting scene
 * integrates them into the 16.16 positions before running its bounce callback. */
extern ObjectPosition town_motion_state;
/* Interior Y coordinate imported independently at 0x80132AEC. */
extern volatile s32 collection_target_y;

/* Collection controllers and their actor callbacks share this body. The snowball
 * initializer stores the actor node at controller +4 and stores the controller
 * body back at actor +0xAC. The paired callbacks exchange flags, angle and state
 * through that link. The collection-round callbacks use the same handshake.
 * Keep signed and unsigned halfword accesses explicit; +0x28 changes from a
 * countdown to an angular phase. This is an observed extent, not an allocation. */
typedef union TownCollectionHalf {
    s16 s;
    u16 u;
} TownCollectionHalf;

typedef struct TownCollectionSequence {
    /* 0x00 */ s32 speed;
    /* 0x04 */ struct ObjectNodeHeader *owner;
    /* 0x08 */ u8 pad_08[0x20];
    /* 0x28 */ TownCollectionHalf timer_or_angle;
    /* 0x2A */ u16 flags; /* Bit zero is set when the terminal countdown expires. */
    /* 0x2C */ TownCollectionHalf angle;
    /* 0x2E */ TownCollectionHalf angle_step;
    /* 0x30 */ TownCollectionHalf saved_x;
    /* 0x32 */ TownCollectionHalf saved_y;
    /* 0x34 */ TownCollectionHalf round_index;
    /* 0x36 */ TownCollectionHalf state;
} TownCollectionSequence;

enum { TOWN_COLLECTION_FINISHED = 1 };

/* Actor body linked back to the collection controller at +0xAC. The callback
 * switches on +0x68, decrements +0x6C, and sets/clears flag bit 0 at +0xA8 on
 * contact. This callback layout is distinct from the stat-bearing ActorRecord. */
typedef struct TownCollectionActor {
    /* 0x00 */ u8 pad_00[0x15];
    /* 0x15 */ s8 scene_active;
    /* 0x16 */ u8 pad_16[0x52];
    /* 0x68 */ TownCollectionHalf state;
    /* 0x6A */ u8 pad_6A[2];
    /* 0x6C */ TownCollectionHalf timer;
    /* 0x6E */ u8 pad_6E[0x3A];
    /* 0xA8 */ s32 flags;
    /* 0xAC */ TownCollectionSequence *sequence;
} TownCollectionActor;

/* The panel initializer passes these forty bytes to the rectangle factory.
 * Its main panel and delayed lines both retain the sequence at +4. */
typedef struct TownCollectionPanel {
    s16 state;
    u16 timer;
    TownCollectionSequence *sequence;
    s32 color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 style;
    u16 flags;
    u8 pad_18[0x10];
} TownCollectionPanel;

typedef void (*TownCollectionPanelUpdate)(TownCollectionPanel *);
void create_payload_object(TownCollectionPanelUpdate callback, const TownCollectionPanel *payload);
void create_object_payload_registers_callback(TownCollectionPanelUpdate callback, const TownCollectionPanel *payload);

void run_collection_round_sequence(TownCollectionSequence *sequence);

/* Forty-eight bytes copied from the collection setup into each text node. */
typedef struct TownCollectionText {
    s16 state;
    u16 timer;
    char *text;
    s16 *value;
    TownCollectionSequence *sequence;
    s32 color;
    s16 x;
    s16 y;
    s16 style;
    s16 clut;
    u16 flags;
    u8 pad_1E[0x12];
} TownCollectionText;

typedef void (*TownCollectionTextUpdate)(TownCollectionText *);
void create_record_with_three_data_blocks(TownCollectionTextUpdate callback, const TownCollectionText *data_blocks);
void create_eight_objects_from_kind_table(void *owner_data);
void create_object_from_pairs_and_words(void *callback, void *pair_data, void *word_data, void *owner);

/* The linked minigame image retains these address aliases. */
void allocate_record_and_store_three_blocks(TownCollectionTextUpdate callback, const TownCollectionText *data_blocks);
void create_initialize_eight_objects_table(void *owner_data);
void create_object_pair_word(void *callback, void *pair_data, void *word_data, void *owner);

#endif
