#ifndef SHARED_ENTITY_H
#define SHARED_ENTITY_H

#include "shared/actor_status.h"

struct DungeonItemEntry;

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

/* One position component stored as a 16.16 word; position initializers and motion updates write it. */
typedef union Fixed1616 {
    int v; /* complete signed 16.16 value */
    struct { unsigned short frac; /* low 16 fractional bits */ short i; /* signed integer part, read by terrain and tile queries */ } w;   /* w.i: the integer half (lh at +2) */
} Fixed1616;

/* ObjectPosition: the 0x18-byte position/motion record an object node points at through ObjectNodeHeader.unk_08
 * (decision 69(C); r121 opus_entity2 split of EntityRec).  The pool allocator places it at node+0xDC / +0xE8 /
 * +0xF4 / +0x10C by flags (payload - 0x18); the static player and town scene nodes point it at D_80083780, which
 * initialize_dungeon_actor clears with six words.  add_motion_deltas_to_position adds each velocity word to the
 * matching coordinate (medium; views call them velocityX/Y/Z).  Leaf types are exactly EntityRec's at 0x00-0x17. */
/* World position and motion owned through ObjectNodeHeader.position.
 * Pooled storage lasts until node retirement; scene setup clears the separate static player position. */
typedef struct ObjectPosition {
    /* 0x00 */ Fixed1616 x; /* world X, signed 16.16; tile centers are tile * 64 + 32 */
    /* 0x04 */ Fixed1616 y; /* world Y on the ground plane, signed 16.16 */
    /* 0x08 */ Fixed1616 z; /* world height, signed 16.16; integer half is used for terrain queries */
    /* 0x0C */ int velocity_x; /* X increment per motion update, in the same 16.16 units as x */
    /* 0x10 */ int velocity_y; /* Y increment per motion update, in the same 16.16 units as y */
    /* 0x14 */ int velocity_z; /* height increment per motion update, in the same 16.16 units as z */
} ObjectPosition;                                  /* 0x18 */

/* EntityRec: LEGACY overlaid view (see above), same 0x12C-byte layout as the r78 record. */
/* Legacy overlay used where the backing record kind is unresolved; it has no independent allocation.
 * The actual owner determines field meaning and lifetime: actor +0x24 is MP, sprite +0x24 is a tile column. */
typedef struct EntityRec {
    /* 0x000 */ Fixed1616 x;                      /* world x, 16.16: lw 26 / integer half lh+2 91 (tile*64+32 in func_800A08A0) */
    /* 0x004 */ Fixed1616 y;                      /* world y (the second ground axis; dirStepY pairs with it) */
    /* 0x008 */ Fixed1616 z;                      /* height: compared with the ground height func_800BCB04 returns (func_807B0110) */
    /* 0x00C */ int unk_0C; /* overlays ObjectPosition.velocity_x and packed ActorRecord ability bytes; owner determines meaning */
    /* 0x010 */ int unk_10; /* overlays ObjectPosition.velocity_y and ActorRecord template bytes; some users read individual bytes */
    /* 0x014 */ int flags14; /* overlays ObjectPosition.velocity_z and ActorRecord property flags; not a universal flag word */
    /* 0x018 */ int unk_18;                       
    /* 0x01C */ int flags1C;                      /* as_s32 125 / u32 74: bit sets/clears (|= 0x80000, &= ~0x10000, >> 19 & 1 in slus/w_80042BDC) */
    /* 0x020 */ short unk_20;                     
    /* 0x022 */ unsigned char pad_22[2];          
    /* 0x024 */ unsigned char tileX; /* tile-column spelling in legacy consumers; the actor layout has fractional MP at this offset */
    /* 0x025 */ unsigned char tileY; /* tile-row spelling in legacy consumers; the actor layout has whole MP at this offset */
    /* 0x026 */ unsigned char unk_26;             
    /* 0x027 */ unsigned char unk_27;             
    /* 0x028 */ unsigned char unk_28; /* actor users read current HP here; sprite users read an animation/resource handle at the same offset */
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
    /* 0x110 */ struct DungeonItemEntry *unk_110; /* player: item whose use is deferred (PlayerRecord.pending_item_action) */
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
 * Leaf types are EntityRec's except +0x10..+0x13 (four template bytes here, one word there); names from r121w_entity1 field_roles / naming_decisions (scope actor_data,
 * medium unless marked), the rest stay unk_.  Callback variants at +0x8A/+0xA4/+0xA8/+0xAC stay unk_ (O08). */
struct ActorRecord;
struct SpriteFrameState;

/* Actor action handler stored at ActorRecord +0x8C. The actor update dispatchers call it as
 * handler(body, position, sprite, body): the actor body, its node's ObjectPosition and SpriteFrameState,
 * and the body again as the actor whose statistics the handler reads. */
typedef void (*ActorActionHandler)(struct ActorRecord *body, struct ObjectPosition *position,
                                   struct SpriteFrameState *sprite, struct ActorRecord *actor);

/* Live monster, familiar or player statistics and action state.
 * allocate_list_node owns pooled bodies; init_monster_from_stats seeds monster template bytes. */
typedef struct ActorRecord {
    /* 0x000 */ unsigned char unk_00[0xC]; /* template bytes: +0/+1 attack/defense, +4/+5 MP/HP; ability groups begin at +8 */
    /* 0x00C */ int unk_0C; /* packed bytes within the three ability groups beginning at +0x08 */
    /* 0x010 */ unsigned char unk_10; /* stored level of the third ability group (MonsterInitialStats abilities[2] ends here); no fixed-offset reader */
    /* 0x011 */ unsigned char level; /* experience level; indexes the level experience table */
    /* 0x012 */ unsigned char unk_12; /* template byte; movement handlers skip adjacent attacks when it is 2 or more */
    /* 0x013 */ unsigned char species; /* monster species id (shared/monster_ids.h); init_monster_from_stats and the spawn factories store it */
    /* 0x014 */ int flags14; /* template/property mask; resistance and class bits are documented in shared/actor_property_flags.h */
    /* 0x018 */ int experience; /* accumulated experience, compared with the next-level requirement */
    /* 0x01C */ int flags1C; /* current side, attachment, movement and active-status bits; see shared/actor_status_flags.h */
    /* 0x020 */ short unk_20; /* prepared attack power; attack preparation seeds it, damage resolution adjusts it before deriving the target HP delta */
    /* 0x022 */ unsigned char pad_22[2];
    /* 0x024 */ unsigned char mp_fraction; /* low byte of current 8.8 MP; initialization and max-MP clamping set it to 0xFF */
    /* 0x025 */ unsigned char mp; /* current familiar/monster MP; high half of the 8.8 value at +0x24 */
    /* 0x026 */ unsigned char current_attack; /* current attack stat; restored from base_attack after temporary changes */
    /* 0x027 */ unsigned char current_defense; /* current defense stat; restored from base_defense after temporary changes */
    /* 0x028 */ unsigned char hp; /* current HP; damage may first accumulate in the signed delta at +0x64 */
    /* 0x029 */ unsigned char max_hp; /* effective maximum HP; doubled template HP is capped at 255 */
    /* 0x02A */ short facing; /* actor angle; 0x1000 units per turn, direction = (facing >> 9) & 7 */
    /* 0x02C */ ActorStatusSlot status[4]; /* status id (ActorStatusId, 0 = empty) and signed duration/value per slot; zero value does not expire; advance_status_timers moves a nonzero value toward zero and clears the id on expiry */
    /* 0x034 */ unsigned char pad_34[13];
    /* 0x041 */ signed char pending_experience_high; /* high byte of a pending experience award */
    /* 0x042 */ signed char pending_experience_low; /* low byte of a pending experience award */
    /* 0x043 */ unsigned char unk_43; /* snapshot index when below 0x40; removal uses 0x54-byte snapshots, while 0xFD..0xFF select special removal paths */
    /* 0x044 */ unsigned short unk_44; /* packed bytes: fusion/removal write the low byte; init_monster_from_stats sets the high byte at +0x45 to 6 */
    /* 0x046 */ unsigned short action_flags; /* action selection flags; bit 0x8000 is cleared after pending actor updates */
    /* 0x048 */ unsigned char unk_48; /* item subtype byte of the four-byte drop descriptor at +0x48; defeat passes the complete descriptor to item spawning */
    /* 0x049 */ unsigned char unk_49; /* drop item category; zero means no item, and defeat spawns it only when the +0x4B suppression bit is clear */
    /* 0x04A */ unsigned char unk_4A; /* third byte of the four-byte drop descriptor; payload meaning follows the item category */
    /* 0x04B */ unsigned char unk_4B; /* drop descriptor flags; bit 0x20 prevents the defeat drop, and fusion preserves descriptors carrying that bit */
    /* 0x04C */ void * unk_4C; /* player: equipped sword/wand record pointer; actor snapshots serialize it as an index in the 20-slot item table */
    /* 0x050 */ unsigned short unk_50; /* player: shield record address spans +0x50..+0x53; actor snapshots serialize it as one item-table index */
    /* 0x052 */ unsigned short unk_52; /* high half of the +0x50 equipment pointer in item/snapshot users; separate halfword access form is retained */
    /* 0x054 */ int status_flags; /* derived-effect mask; bits 1..4 double HP/MP/attack/defense baselines, capped at 255 by apply_entity_effects */
    /* 0x058 */ void * previous_actor_header; /* previous live actor list entry, pointing to its ObjectNodeHeader */
    /* 0x05C */ int next_actor_header; /* next live actor list entry, stored as the address of its ObjectNodeHeader */
    /* 0x060 */ void * target; /* borrowed actor-body target; while lifted, this is the carrier backlink rather than an attack target */
    /* 0x064 */ short hp_delta; /* signed pending HP delta; effective HP is hp + unk_64 before applying queued damage */
    /* 0x066 */ unsigned char max_mp; /* effective maximum MP; doubled template MP is capped at 255 */
    /* 0x067 */ unsigned char pad_67[1];
    /* 0x068 */ unsigned char base_attack; /* effective baseline attack; doubled template attack is capped at 255 */
    /* 0x069 */ unsigned char base_defense; /* effective baseline defense; doubled template defense is capped at 255 */
    /* 0x06A */ unsigned short movement_facing; /* queued movement angle copied to facing; 0x1000 units per turn */
    /* 0x06C */ unsigned char pad_6C[1];
    /* 0x06D */ signed char pending_turn_updates; /* queued turn updates; update_actor_status_and_mp spends MP and advances status timers once per decrement */
    /* 0x06E */ unsigned char pad_6E[3];
    /* 0x071 */ unsigned char movement_queue_state; /* queued-path state/count; update_actor_status_and_mp clears its high control bit before processing */
    /* 0x072 */ signed char target_tile_x; /* target map column, in tiles */
    /* 0x073 */ signed char target_tile_y; /* target map row, in tiles */
    /* 0x074 */ unsigned char pad_74[16];
    /* 0x084 */ signed char unk_84; /* unsigned hit-roll baseline despite the signed leaf; attack preparation adds random multiples of 4 and compares with 0x80 */
    /* 0x085 */ signed char unk_85;
    /* 0x086 */ unsigned char pad_86[2];
    /* 0x088 */ short ground_height; /* terrain height sampled beneath the actor, in world units */
    /* 0x08A */ short unk_8A;                     /* queued terrain height / throw travel steps (callback variants) */
    /* 0x08C */ union {
        void *address; /* callback address; return contracts differ between actor handlers */
        void (*run)(void *, void *, void *, void *); /* Kewne calls this view and discards any result */
        ActorActionHandler handler; /* the current action handler */
    } unk_8C;
    /* 0x090 */ union {
        int value;
        struct { unsigned short low; union { short s; unsigned short u; } high; } parts;
    } unk_90; /* callback scratch word; signed and unsigned high-half accesses */
    /* 0x094 */ short unk_94;
    /* 0x096 */ unsigned short action_timer;
    /* 0x098 */ unsigned short action_state_flags;
    /* 0x09A */ unsigned char action_id; /* actor action-table selector; id meanings depend on the dispatcher */
    /* 0x09B */ unsigned char action_phase; /* phase byte within the selected action; reset when a new action starts */
    /* 0x09C */ signed char unk_9C;
    /* 0x09D */ union { signed char s; unsigned char u; } unk_9D;
    /* 0x09E */ union { short s; unsigned short u; } unk_9E;
    /* 0x0A0 */ union {
        int value;
        struct { unsigned short low; unsigned short high; } parts;
    } unk_A0; /* callback scratch word with an unsigned high-half view */
    /* 0x0A4 */ int unk_A4; /* callback scratch with word/halfword views; landing uses it for accumulated 16.16 vertical displacement */
    /* 0x0A8 */ unsigned char unk_A8;             /* saved species (temporary 0x2E form) or player transition mode */
    /* 0x0A9 */ unsigned char pad_A9[1];
    /* 0x0AA */ short unk_AA;
    /* 0x0AC */ void * unk_AC;                    /* player: familiar slot 0; other actors: saved node callback (O08) */
    /* 0x0B0 */ void * unk_B0; /* player: familiar slot 1; Kewne reads/writes this slot as a script-bit word */
    /* 0x0B4 */ unsigned char pad_B4[4];
    /* 0x0B8 */ unsigned char unk_B8;
    /* 0x0B9 */ unsigned char unk_B9;
    /* 0x0BA */ unsigned char pad_BA[2];
} ActorRecord;                                    /* 0xBC: the pooled actor body */

/* PlayerRecord: the dungeon player's body, 0x12C bytes after its static node header (initialize_dungeon_actor
 * clears 0x53 words = 0x14C and points the node's position/sprite slots at the external D_80083780 / D_80082E80).
 * The first 0xBC bytes are the player's ActorRecord; the tail is player-only and never exists in a pooled actor.
 * D_800814A8 / D_800E3D7C are typed as the ActorRecord they point at (almost every use is actor-generic); a
 * player-only field is reached as ((PlayerRecord *)actor)->field. */
/* Player body in the static scene node; initialize_dungeon_actor clears and reuses it on setup.
 * The tail after ActorRecord is player-only and must not be read from pooled monster/familiar bodies. */
typedef struct PlayerRecord {
    /* 0x000 */ ActorRecord actor; /* shared player statistics and action state; occupies the first 0xBC bytes */
    /* 0x0BC */ unsigned char pad_BC[12];
    /* 0x0C8 */ void * unk_C8; /* borrowed menu/selection/transition node; waiters test its header flag 0x8000, then clear this pointer */
    /* 0x0CC */ unsigned char pad_CC[6];
    /* 0x0D2 */ unsigned char unk_D2;
    /* 0x0D3 */ unsigned char pad_D3[5];
    /* 0x0D8 */ int unk_D8;
    /* 0x0DC */ unsigned char pad_DC[8];
    /* 0x0E4 */ void *menu_alternate[2]; /* menu cache alternate familiar slots */
    /* 0x0EC */ unsigned char pad_EC[4];
    /* 0x0F0 */ void *selected_floor_entry; /* selected four-byte floor/map item entry, or null */
    /* 0x0F4 */ int unk_F4;                       /* player transition data */
    /* 0x0F8 */ unsigned char pad_F8[10];
    /* 0x102 */ unsigned char unk_102;            /* player transition flag */
    /* 0x103 */ unsigned char pad_103[1];
    /* 0x104 */ int unk_104; /* selected familiar actor address during command selection; cleared when player input starts a new selection */
    /* 0x108 */ unsigned char pad_108[4];
    /* 0x10C */ unsigned short unk_10C;           /* completion/status bits of the timed sequence */
    /* 0x10E */ unsigned char pad_10E[2];
    /* 0x110 */ struct DungeonItemEntry *pending_item_action; /* item whose use is deferred until the player's action runs; stored only when the owner is the player */
    /* 0x114 */ int unk_114;                      /* word stores 0x202080 / 0x802020 before item-effect dispatch */
    /* 0x118 */ unsigned char pad_118[12];
    /* 0x124 */ void *unk_124; /* borrowed carried/linked actor body, or null; lift sets its carrier backlink and release clears ACTOR_LIFTED */
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

