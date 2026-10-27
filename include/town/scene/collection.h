#ifndef TOWN_SCENE_COLLECTION_H
#define TOWN_SCENE_COLLECTION_H

#include "common.h"

struct ObjectNodeHeader;
extern struct ObjectNodeHeader *scene_object_factory_data;

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
    /* 0x28 */ TownCollectionHalf unk_28;
    /* 0x2A */ TownCollectionHalf flags;
    /* 0x2C */ TownCollectionHalf angle;
    /* 0x2E */ TownCollectionHalf angle_step;
    /* 0x30 */ TownCollectionHalf saved_x;
    /* 0x32 */ TownCollectionHalf saved_y;
    /* 0x34 */ TownCollectionHalf round_index;
    /* 0x36 */ TownCollectionHalf state;
} TownCollectionSequence;

/* Actor body linked back to the collection controller at +0xAC. The callback
 * switches on +0x68, decrements +0x6C, and sets/clears flag bit 0 at +0xA8 on
 * contact. This callback layout is distinct from the stat-bearing ActorRecord. */
typedef struct TownCollectionActor {
    /* 0x00 */ u8 pad_00[0x15];
    /* 0x15 */ s8 unk_15;
    /* 0x16 */ u8 pad_16[0x52];
    /* 0x68 */ TownCollectionHalf state;
    /* 0x6A */ u8 pad_6A[2];
    /* 0x6C */ TownCollectionHalf timer;
    /* 0x6E */ u8 pad_6E[0x3A];
    /* 0xA8 */ s32 flags;
    /* 0xAC */ TownCollectionSequence *sequence;
} TownCollectionActor;

void run_collection_round_sequence(TownCollectionSequence *sequence);

void create_record_with_three_data_blocks(void *callback, void *data_blocks);
void create_eight_objects_from_kind_table(void *owner_data);
void create_object_from_pairs_and_words(void *callback, void *pair_data, void *word_data, void *owner);

/* The linked minigame image retains these address aliases. */
void allocate_record_and_store_three_blocks(void *callback, void *data_blocks);
void create_initialize_eight_objects_table(void *owner_data);
void create_object_pair_word(void *callback, void *pair_data, void *word_data, void *owner);

#endif
