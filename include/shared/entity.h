#ifndef SHARED_ENTITY_H
#define SHARED_ENTITY_H

/* Object-system records of the DUNGEON (and TOWN) object pools.  An object is a 0x20-byte ObjectNodeHeader
 * (shared/object_node.h) followed by a callback-specific body; the node's +0x08 / +0x0C slots point at separate
 * position (ObjectPosition) and sprite (SpriteFrameState) records.  r121 opus_entity2 (decision 73 draft) split
 * the r78 catch-all EntityRec into the records the game allocates: ObjectPosition (0x18), ActorRecord (0xBC, the
 * pooled actor body) and PlayerRecord (0x12C, the static player body = ActorRecord + player tail).
 *
 * EntityRec (below) is now only the LEGACY overlaid view: the r78 union of every record that census reached
 * (motion x/y/z at 0x00..0x17 overlapping actor stats, sprite tile bytes at 0x24 overlapping the actor's MP).
 * Its remaining users are held sites whose record kind is not yet proven (no traced allocation / callback /
 * caller), effect payloads, and the relinked copies that follow their homes; lane holds list each with its reason.
 * New code must use the split records; do not add members to EntityRec. */

typedef union Fixed1616 {
    int v;                          /* the whole 16.16 word (lw/sw) */
    struct { unsigned short frac; short i; } w;   /* w.i: the integer half (lh at +2) */
} Fixed1616;

/* ObjectPosition: the 0x18-byte position/motion record an object node points at through ObjectNodeHeader.unk_08
 * (decision 69(C); r121 opus_entity2 split of EntityRec).  The pool allocator places it at node+0xDC / +0xE8 /
 * +0xF4 / +0x10C by flags (payload - 0x18); the static player and town scene nodes point it at D_80083780, which
 * initialize_dungeon_actor clears with six words.  add_motion_deltas_to_position adds each velocity word to the
 * matching coordinate (medium; views call them velocityX/Y/Z).  Leaf types are exactly EntityRec's at 0x00-0x17. */
typedef struct ObjectPosition {
    /* 0x00 */ Fixed1616 x;                        /* world x, 16.16 (integer half lh +2) */
    /* 0x04 */ Fixed1616 y;                        /* world y (the second ground axis) */
    /* 0x08 */ Fixed1616 z;                        /* height, compared with the terrain height */
    /* 0x0C */ int velocity_x;                     /* medium: added to x each update (add_motion_deltas_to_position) */
    /* 0x10 */ int velocity_y;                     /* medium: added to y each update */
    /* 0x14 */ int velocity_z;                     /* medium: added to z each update */
} ObjectPosition;                                  /* 0x18 */

/* EntityRec: LEGACY overlaid view (see above), same 0x12C-byte layout as the r78 record. */
typedef struct EntityRec {
    /* 0x000 */ Fixed1616 x;                      /* world x, 16.16: lw 26 / integer half lh+2 91 (tile*64+32 in func_800A08A0) */
    /* 0x004 */ Fixed1616 y;                      /* world y (the second ground axis; dirStepY pairs with it) */
    /* 0x008 */ Fixed1616 z;                      /* height: compared with the ground height func_800BCB04 returns (func_807B0110) */
    /* 0x00C */ int unk_0C;                       /* as_s32 176+366 / u32 1 */
    /* 0x010 */ int unk_10;                       /* at00_s32 369; bytes +1/+2/+3 read singly (views) */
    /* 0x014 */ int flags14;                      /* as_s32 219: bit tests (& 0x4000, & 0x20000000 in func_80CC266C) */
    /* 0x018 */ int unk_18;                       
    /* 0x01C */ int flags1C;                      /* as_s32 125 / u32 74: bit sets/clears (|= 0x80000, &= ~0x10000, >> 19 & 1 in slus/w_80042BDC) */
    /* 0x020 */ short unk_20;                     
    /* 0x022 */ unsigned char pad_22[2];          
    /* 0x024 */ unsigned char tileX;              /* map-grid x byte: func_8009FB34(tileX + dirStepX[d], ...), func_8009A3D0(tileX, tileY, ...) */
    /* 0x025 */ unsigned char tileY;              /* map-grid y byte (pair read as one s16 at 0x24 by some rows: a view) */
    /* 0x026 */ unsigned char unk_26;             
    /* 0x027 */ unsigned char unk_27;             
    /* 0x028 */ unsigned char unk_28;             /* 101 uses */
    /* 0x029 */ unsigned char unk_29;             
    /* 0x02A */ short facing;                     /* as_s16 692: `(viewAngle + facing + 0x100) >> 9 & 7` picks the 8-way sprite; set to direction << 9 */
    /* 0x02C */ short unk_2C;                     
    /* 0x02E */ unsigned char pad_2E[4];          
    /* 0x032 */ short unk_32;                     
    /* 0x034 */ unsigned char pad_34[13];         
    /* 0x041 */ signed char unk_41;               
    /* 0x042 */ signed char unk_42;               
    /* 0x043 */ unsigned char unk_43;             
    /* 0x044 */ unsigned short unk_44;            /* whole word read 3x (view) */
    /* 0x046 */ unsigned short unk_46;            /* at02_u16 282: bit 15 cleared (&= 0x7FFF) */
    /* 0x048 */ unsigned char unk_48;             /* s32/s8/u8 views */
    /* 0x049 */ unsigned char unk_49;             
    /* 0x04A */ unsigned char unk_4A;             
    /* 0x04B */ unsigned char unk_4B;             
    /* 0x04C */ void * unk_4C;                    /* as_pv 4 / s32 3 */
    /* 0x050 */ unsigned short unk_50;            /* u16 / pointer / s32 views */
    /* 0x052 */ unsigned short unk_52;            
    /* 0x054 */ int unk_54;                       
    /* 0x058 */ void * unk_58;                    
    /* 0x05C */ int unk_5C;                       
    /* 0x060 */ void * target;                    /* as_pv 41: the entity an action targets (func_80CC266C stores the chosen neighbour) */
    /* 0x064 */ short unk_64;                     /* as_s16 63 / u16 3 */
    /* 0x066 */ unsigned char pad_66[2];          
    /* 0x068 */ unsigned char unk_68;             
    /* 0x069 */ unsigned char unk_69;             
    /* 0x06A */ unsigned short unk_6A;            /* as_u16 93 / s16 7: (unk_6A >> 9) & 7 is a direction */
    /* 0x06C */ unsigned char pad_6C[1];          
    /* 0x06D */ signed char unk_6D;               /* as_s8 74+65 / u8 47+80 (A/B in REPORT) */
    /* 0x06E */ unsigned char pad_6E[3];          
    /* 0x071 */ unsigned char unk_71;             /* as_u8 50+78 / s8 2 */
    /* 0x072 */ signed char unk_72;               
    /* 0x073 */ signed char unk_73;               
    /* 0x074 */ unsigned char pad_74[16];         
    /* 0x084 */ signed char unk_84;               
    /* 0x085 */ signed char unk_85;               
    /* 0x086 */ unsigned char pad_86[2];          
    /* 0x088 */ short unk_88;                     
    /* 0x08A */ short unk_8A;                     
    /* 0x08C */ unsigned char pad_8C[10];         
    /* 0x096 */ unsigned short unk_96;            
    /* 0x098 */ unsigned short unk_98;            
    /* 0x09A */ unsigned char unk_9A;             
    /* 0x09B */ unsigned char unk_9B;             
    /* 0x09C */ unsigned char pad_9C[8];          
    /* 0x0A4 */ int unk_A4;                       /* s32 / s16+2 / u16+2 views (Rec_D_800814A8 reads +2 as u16) */
    /* 0x0A8 */ unsigned char unk_A8;             /* Rec_D_800814A8 */
    /* 0x0A9 */ unsigned char pad_A9[1];          
    /* 0x0AA */ short unk_AA;                     
    /* 0x0AC */ void * unk_AC;                    /* Rec_D_800814A8 */
    /* 0x0B0 */ void * unk_B0;                    /* Rec_D_800814A8 */
    /* 0x0B4 */ unsigned char pad_B4[20];         
    /* 0x0C8 */ void * unk_C8;                    
    /* 0x0CC */ unsigned char pad_CC[6];          
    /* 0x0D2 */ unsigned char unk_D2;             
    /* 0x0D3 */ unsigned char pad_D3[5];          
    /* 0x0D8 */ int unk_D8;                       
    /* 0x0DC */ unsigned char pad_DC[20];         
    /* 0x0F0 */ void *unk_F0;                    /* selected four-byte item entry, or null */
    /* 0x0F4 */ int unk_F4;                       /* Rec_D_800814A8 */
    /* 0x0F8 */ unsigned char pad_F8[10];         
    /* 0x102 */ unsigned char unk_102;            /* Rec_D_800814A8 */
    /* 0x103 */ unsigned char pad_103[1];         
    /* 0x104 */ int unk_104;                      
    /* 0x108 */ unsigned char pad_108[4];         
    /* 0x10C */ unsigned short unk_10C;           /* Rec_D_800814A8 */
    /* 0x10E */ unsigned char pad_10E[2];         
    /* 0x110 */ int unk_110;                      
    /* 0x114 */ int unk_114;                      /* word stores 0x202080 / 0x802020 before item-effect dispatch */
    /* 0x118 */ unsigned char pad_118[12];        
    /* 0x124 */ void *unk_124;                   /* linked record; flags read after null check */
    /* 0x128 */ int unk_128;                      
} EntityRec;

/* ActorRecord: the body of a live actor (monster, familiar or the player), the 0xBC bytes after a 0x20-byte
 * ObjectNodeHeader in a pooled 0x124-byte node allocated with flags 0x112 (runtime_reset_object_pool strides
 * 0x124; allocate_list_node then puts the ObjectPosition at node+0xDC and the SpriteFrameState at node+0xF4, so
 * actor+0xBC is already the position record).  r121 opus_entity2 (decision 73 draft) split it out of EntityRec:
 * +0x00..+0x14 are packed innate stats, ability slots and the actor flags word, NOT world coordinates (those live
 * in the separate ObjectPosition); +0x24/+0x25 are MP (decision 73), NOT tile coordinates (those are the sprite's).
 * Leaf types are exactly EntityRec's; names from r121w_entity1 field_roles / naming_decisions (scope actor_data,
 * medium unless marked), the rest stay unk_.  Callback variants at +0x8A/+0xA4/+0xA8/+0xAC stay unk_ (O08). */
typedef struct ActorRecord {
    /* 0x000 */ unsigned char unk_00[0xC];        /* packed innate stats and ability slots (byte views only) */
    /* 0x00C */ int unk_0C;                       /* ability-slot bytes */
    /* 0x010 */ int unk_10;                       /* level byte at +0x11 (capped at 99), species at +0x13 (byte views) */
    /* 0x014 */ int flags14;                      /* actor flags word (& 0x4000, & 0x20000000) */
    /* 0x018 */ int experience;                   /* high: accumulated experience compared with the level table (raise_entity_level) */
    /* 0x01C */ int flags1C;                      /* actor live/status flags (|= 0x80000, &= ~0x10000) */
    /* 0x020 */ short unk_20;
    /* 0x022 */ unsigned char pad_22[2];
    /* 0x024 */ unsigned char mp_fraction;        /* MP, fractional low byte (8.8 with mp) */
    /* 0x025 */ unsigned char mp;                 /* current MP (familiars and monsters; the player has none); 0 = exhausted */
    /* 0x026 */ unsigned char current_attack;     /* medium: current attack, restored from base_attack */
    /* 0x027 */ unsigned char current_defense;    /* medium: current defense, restored from base_defense */
    /* 0x028 */ unsigned char hp;                 /* high: current HP (apply_capped_damage_and_hit_effect) */
    /* 0x029 */ unsigned char max_hp;             /* high: maximum HP */
    /* 0x02A */ short facing;                     /* `(viewAngle + facing + 0x100) >> 9 & 7` picks the 8-way sprite; set to direction << 9 */
    /* 0x02C */ short unk_2C;                     /* first of four status id/value pairs (+0x2C..+0x33) */
    /* 0x02E */ unsigned char pad_2E[4];
    /* 0x032 */ short unk_32;                     /* fourth status pair */
    /* 0x034 */ unsigned char pad_34[13];
    /* 0x041 */ signed char pending_experience_high; /* medium: pending experience award, high byte first */
    /* 0x042 */ signed char pending_experience_low;  /* medium: pending experience award, low byte */
    /* 0x043 */ unsigned char unk_43;
    /* 0x044 */ unsigned short unk_44;            /* whole word read 3x (view) */
    /* 0x046 */ unsigned short action_flags;      /* medium: action selection word, bit 15 = pending (&= 0x7FFF) */
    /* 0x048 */ unsigned char unk_48;             /* s32/s8/u8 views */
    /* 0x049 */ unsigned char unk_49;
    /* 0x04A */ unsigned char unk_4A;
    /* 0x04B */ unsigned char unk_4B;
    /* 0x04C */ void * unk_4C;
    /* 0x050 */ unsigned short unk_50;            /* equipment/item pointer spans +0x50..+0x53 (candidate; u16 views) */
    /* 0x052 */ unsigned short unk_52;
    /* 0x054 */ int status_flags;                 /* medium: additional actor status bits */
    /* 0x058 */ void * unk_58;                    /* medium: previous_actor_header (live actor list link to the previous actor's
                                                   * ObjectNodeHeader); the rename waits for the relinked copies of the
                                                   * dragon, flame and arachne actions that read D_800814A8->unk_58 */
    /* 0x05C */ int next_actor_header;            /* medium: live actor list link (next actor's header; int-typed leaf kept) */
    /* 0x060 */ void * target;                    /* the actor an action targets (actor data; header at -0x20) */
    /* 0x064 */ short unk_64;                     /* pending signed HP delta (candidate) */
    /* 0x066 */ unsigned char max_mp;             /* maximum MP (stat panel prints mp / max_mp under hp / max_hp) */
    /* 0x067 */ unsigned char pad_67[1];
    /* 0x068 */ unsigned char base_attack;        /* medium: baseline restoring current_attack */
    /* 0x069 */ unsigned char base_defense;       /* medium: baseline restoring current_defense */
    /* 0x06A */ unsigned short movement_facing;   /* medium: queued movement facing copied to facing; (>> 9) & 7 is a direction */
    /* 0x06C */ unsigned char pad_6C[1];
    /* 0x06D */ signed char pending_turn_updates; /* medium: pending turn updates drained toward zero */
    /* 0x06E */ unsigned char pad_6E[3];
    /* 0x071 */ unsigned char movement_queue_state; /* medium: queue count/state, high bit = control */
    /* 0x072 */ signed char target_tile_x;        /* medium: target tile stored on the owner actor */
    /* 0x073 */ signed char target_tile_y;        /* medium */
    /* 0x074 */ unsigned char pad_74[16];
    /* 0x084 */ signed char unk_84;
    /* 0x085 */ signed char unk_85;
    /* 0x086 */ unsigned char pad_86[2];
    /* 0x088 */ short ground_height;              /* medium: terrain height beneath the actor */
    /* 0x08A */ short unk_8A;                     /* queued terrain height / throw travel steps (callback variants) */
    /* 0x08C */ unsigned char pad_8C[10];         /* +0x8C: action callback (candidate); wrappers pass the body as args 0 and 3 */
    /* 0x096 */ unsigned short unk_96;
    /* 0x098 */ unsigned short unk_98;
    /* 0x09A */ unsigned char unk_9A;             /* action callback-table selector (candidate action_id) */
    /* 0x09B */ unsigned char unk_9B;             /* phase within the selected action (candidate) */
    /* 0x09C */ unsigned char pad_9C[8];
    /* 0x0A4 */ int unk_A4;                       /* callback scratch: s32 / s16+2 / u16+2 views */
    /* 0x0A8 */ unsigned char unk_A8;             /* saved species (temporary 0x2E form) or player transition mode */
    /* 0x0A9 */ unsigned char pad_A9[1];
    /* 0x0AA */ short unk_AA;
    /* 0x0AC */ void * unk_AC;                    /* player: familiar slot 0; other actors: saved node callback (O08) */
    /* 0x0B0 */ void * unk_B0;                    /* player: familiar slot 1 */
    /* 0x0B4 */ unsigned char pad_B4[8];
} ActorRecord;                                    /* 0xBC: the pooled actor body */

/* PlayerRecord: the dungeon player's body, 0x12C bytes after its static node header (initialize_dungeon_actor
 * clears 0x53 words = 0x14C and points the node's position/sprite slots at the external D_80083780 / D_80082E80).
 * The first 0xBC bytes are the player's ActorRecord; the tail is player-only and never exists in a pooled actor.
 * D_800814A8 / D_800E3D7C are typed as the ActorRecord they point at (almost every use is actor-generic); a
 * player-only field is reached as ((PlayerRecord *)actor)->field. */
typedef struct PlayerRecord {
    /* 0x000 */ ActorRecord actor;
    /* 0x0BC */ unsigned char pad_BC[12];
    /* 0x0C8 */ void * unk_C8;
    /* 0x0CC */ unsigned char pad_CC[6];
    /* 0x0D2 */ unsigned char unk_D2;
    /* 0x0D3 */ unsigned char pad_D3[5];
    /* 0x0D8 */ int unk_D8;
    /* 0x0DC */ unsigned char pad_DC[20];
    /* 0x0F0 */ void *selected_floor_entry;       /* medium: selected four-byte floor/map entry, or null */
    /* 0x0F4 */ int unk_F4;                       /* player transition data */
    /* 0x0F8 */ unsigned char pad_F8[10];
    /* 0x102 */ unsigned char unk_102;            /* player transition flag */
    /* 0x103 */ unsigned char pad_103[1];
    /* 0x104 */ int unk_104;
    /* 0x108 */ unsigned char pad_108[4];
    /* 0x10C */ unsigned short unk_10C;           /* completion/status bits of the timed sequence */
    /* 0x10E */ unsigned char pad_10E[2];
    /* 0x110 */ int pending_item_action;          /* medium: deferred item action, stored after an equality guard with the player */
    /* 0x114 */ int unk_114;                      /* word stores 0x202080 / 0x802020 before item-effect dispatch */
    /* 0x118 */ unsigned char pad_118[12];
    /* 0x124 */ void *unk_124;                    /* linked record; flags read after null check */
    /* 0x128 */ int unk_128;
} PlayerRecord;                                   /* 0x12C */


/* Exact access views shared across registered binary consumers. */
/* Bank actor status with unsigned flags and signed facing/status fields.
 * This exact 0x70-byte view does not widen to EntityRec. */
typedef struct ActorUnsignedFlagsView {
    unsigned char pad_00[0x1C];
    unsigned int unk_1C;
    unsigned char pad_20[5];
    unsigned char unk_25;
    unsigned char pad_26[4];
    short unk_2A;
    unsigned char pad_2C[0x1A];
    unsigned short unk_46;
    unsigned char pad_48[0x1C];
    short unk_64;
    unsigned char pad_66[7];
    signed char unk_6D;
} ActorUnsignedFlagsView;

#endif

