#ifndef SHARED_ENTITY_H
#define SHARED_ENTITY_H

#include "game.h" /* ActorAbility */
#include "shared/actor_status.h"
#include "shared/dungeon_item_entries.h" /* DungeonItemEntry (ActorRecord.carried_item) */

struct DungeonItemEntry;

/* Object-system records of the DUNGEON (and TOWN) object pools.  An object is a 0x20-byte ObjectNodeHeader
 * (shared/object_node.h) followed by a callback-specific body; the node's +0x08 / +0x0C slots point at separate
 * position (ObjectPosition) and sprite (SpriteFrameState) records.  Decision 73 (draft) split
 * the r78 catch-all EntityRec into the records the game allocates: ObjectPosition (0x18), ActorRecord (0xBC, the
 * pooled actor body) and PlayerRecord (0x12C, the static player body = ActorRecord + player tail).
 *
 * EntityRec (below) is now only the LEGACY overlaid view: the r78 union of every record that census reached
 * (motion x/y/z at 0x00..0x17 overlapping actor stats, sprite tile bytes at 0x24 overlapping the actor's MP).
 * Its remaining users are held sites whose record kind is not yet proven (no traced allocation / callback /
 * caller), effect payloads, and the relinked copies that follow their homes; the held-site lists give each its reason.
 * New code must use the split records; do not add members to EntityRec. */

/* One position component stored as a 16.16 word; position initializers and motion updates write it. */
typedef union Fixed1616 {
    int v; /* complete signed 16.16 value */
    struct { unsigned short frac; /* low 16 fractional bits */ short i; /* signed integer part, read by terrain and tile queries */ } w;   /* w.i: the integer half (lh at +2) */
    /* Sprite-position copies also load the integer half with lhu. */
    struct { unsigned short fraction; unsigned short integer; } unsigned_parts;
} Fixed1616;

/* ObjectPosition: the 0x18-byte position/motion record an object node points at through ObjectNodeHeader.unk_08
 * (decision 69(C); split of EntityRec).  The pool allocator places it at node+0xDC / +0xE8 /
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
    /* 0x01C */ int flags1C;                      /* the actor status bit word (ActorRecord.flags1C, shared/actor_status_flags.h) under the legacy view */
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
    /* 0x05C */ void *unk_5C;                     
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
    /* 0x084 */ unsigned char unk_84; /* the ActorRecord.accuracy byte (unsigned by its sign trial); no EntityRec user reads it */
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
 * ObjectNodeHeader in a pooled 0x124-byte node allocated with flags 0x112 (reset_node_pool strides
 * 0x124; allocate_list_node then puts the ObjectPosition at node+0xDC and the SpriteFrameState at node+0xF4, so
 * actor+0xBC is already the position record).  Decision 73 (draft) split it out of EntityRec:
 * +0x00..+0x14 are the level stats, the three ability slots and the template flag word that init_monster_from_stats
 * seeds from the species' MonsterInitialStats (same layout to +0x13), NOT world coordinates (those live in the
 * separate ObjectPosition); +0x24/+0x25 are MP (decision 73), NOT tile coordinates (those are the sprite's).
 * Members without behaviour evidence stay unk_.  Callback variants at +0x8A/+0xA4/+0xA8/+0xAC stay unk_ (O08). */
struct ActorRecord;
struct SpriteFrameState;

/* Actor action handler stored at ActorRecord +0x8C. The actor update dispatchers call it as
 * handler(body, position, sprite, body): the actor body, its node's ObjectPosition and SpriteFrameState,
 * and the body again as the actor whose statistics the handler reads. */
typedef void (*ActorActionHandler)(struct ActorRecord *body, struct ObjectPosition *position,
                                   struct SpriteFrameState *sprite, struct ActorRecord *actor);

/* Two halfwords of a 4-byte action-scratch slot (+0xA4/+0xAC/+0xB0/+0xB4); action handlers read either
 * signedness, so each half keeps both views. */
typedef struct ActorScratchHalves {
    union { short s; unsigned short u; } low;
    union { short s; unsigned short u; } high;
} ActorScratchHalves;

/* Live monster, familiar or player statistics and action state.
 * allocate_list_node owns pooled bodies; init_monster_from_stats seeds monster template bytes. */
typedef struct ActorRecord {
    /* 0x000 */ unsigned char attack; /* attack stat: level-up grows it from the species growth row, the attack item adds one; apply_entity_effects derives base_attack from it */
    /* 0x001 */ unsigned char defense; /* defense stat: level-up grows it, the defense item adds one; apply_entity_effects derives base_defense from it */
    /* 0x002 */ unsigned char agility; /* agility stat: level-up grows it; the speed item adds one up to 0xFF and reports "agility increased"; no other consumer of this byte found */
    /* 0x003 */ unsigned char luck; /* luck stat: chance rolls take a random value modulo it and skip the roll at zero; level-up grows it, the luck item adds one; the player's swings with a sine each turn (lower while cursed); prepare_directional_attack adds (random % attacker luck) * 4 to the hit baseline, takes luck >> 6 (>> 1 when angry) as the critical chance and rolls the target's luck for the dodge */
    /* 0x004 */ unsigned char level_max_mp; /* maximum MP from level growth; apply_entity_effects copies it to max_mp, doubled (capped at 255) under status_flags bit 0x4 */
    /* 0x005 */ unsigned char level_max_hp; /* maximum HP from level growth; apply_entity_effects copies it to max_hp, doubled (capped at 255) under status_flags bit 0x2 */
    /* 0x006 */ unsigned short exp_reward; /* experience awarded for defeating this actor: init_monster_from_stats copies the species base, raise_entity_level and lower_entity_level recompute it (clamped to 0xFFFF), distribute_experience_awards shares it out */
    /* 0x008 */ ActorAbility abilities[3]; /* ability slots for action codes 1..3 (action_flags & ACTOR_ACTION_CODE_MASK) */
    /* 0x011 */ unsigned char level; /* experience level; indexes the level experience table */
    /* 0x012 */ unsigned char ai_mode; /* template byte; movement handlers skip adjacent attacks when it is 2 or more */
    /* 0x013 */ unsigned char species; /* monster species id (shared/monster_ids.h); init_monster_from_stats and the spawn factories store it */
    /* 0x014 */ int flags14; /* template/property mask; resistance and class bits are documented in shared/actor_property_flags.h */
    /* 0x018 */ int experience; /* accumulated experience, compared with the next-level requirement */
    /* 0x01C */ int flags1C; /* current side, attachment, movement and active-status bits; see shared/actor_status_flags.h */
    /* 0x020 */ short attack_power; /* the attacker's power for one attack, not a base stat: prepare_directional_attack stores (current_attack + the weapon bonus) * 2 plus a random 0..2, damage resolution scales it for element and height before deriving the target HP delta, apply_spell_element_bonus takes the weapon part out again */
    /* 0x022 */ unsigned short defense_power; /* the target's defence for one hit, derived per hit: its current_defense plus the shield bonus, halved under the frog status and raised to 1 when zero; both damage functions read it signed (copy_entity_record also copies the halfword with the actor snapshot) */
    /* 0x024 */ unsigned char mp_fraction; /* low byte of the 8.8 current MP; spending, draining and feeding read and write mp_fraction..mp as one halfword, and a clamp to max_mp sets it to 0xFF */
    /* 0x025 */ unsigned char mp; /* current MP in whole points: the byte displays, max_mp clamps and empty-MP tests read */
    /* 0x026 */ unsigned char current_attack; /* current attack stat; restored from base_attack after temporary changes */
    /* 0x027 */ unsigned char current_defense; /* current defense stat; restored from base_defense after temporary changes */
    /* 0x028 */ unsigned char hp; /* current HP; damage may first accumulate in the signed delta at +0x64 */
    /* 0x029 */ unsigned char max_hp; /* effective maximum HP: level_max_hp, doubled under a status bit and capped at 255 */
    /* 0x02A */ short facing; /* actor angle; 0x1000 units per turn, direction = (facing >> 9) & 7 */
    /* 0x02C */ ActorStatusSlot status[4]; /* status id (ActorStatusId, 0 = empty) and signed duration/value per slot; zero value does not expire; advance_status_timers moves a nonzero value toward zero and clears the id on expiry */
    /* 0x034 */ unsigned char name[13]; /* the creature's name text, 13 bytes: copy_entity_record copies all 13 into the town snapshot, party-member message text and the town status text print it from +0x34 */
    /* 0x041 */ signed char pending_experience_high; /* high byte of a pending experience award */
    /* 0x042 */ signed char pending_experience_low; /* low byte of a pending experience award */
    /* 0x043 */ unsigned char town_monster_slot; /* index into the stored town monster table (town_monsters[64], 0x54 bytes each) when below 0x40; 0xFD..0xFF mark dungeon-made familiars (0xFF: released, 0xFE: vanished) */
    /* 0x044 */ unsigned char unk_44; /* copied with the actor snapshot or cleared before it is taken; no other reader */
    /* 0x045 */ unsigned char approach_direction; /* direction, relative to the player's facing, of the player-adjacent tile this actor keeps station on or approaches (target tile = player tile + dir_step[(approach_direction + player facing >> 9) & 7]); familiars load it from the saved familiar direction, init_monster_from_stats starts monsters at 6 */
    /* 0x046 */ unsigned short action_flags; /* action selection flags; bit 0x8000 is cleared after pending actor updates */
    /* 0x048 */ DungeonItemEntry carried_item; /* the item this actor carries and drops: defeat passes the whole entry to item spawning, the town shop row and the fusion copy use the same four bytes; kind zero means no item, and bit 0x20 of the last byte prevents the defeat drop (fusion preserves entries carrying it); whole-entry copies stay word views */
    /* 0x04C */ void * weapon; /* player: equipped sword/wand record pointer; actor snapshots serialize it as an index in the 20-slot item table */
    /* 0x050 */ union {
        struct {
            unsigned short low; /* actor snapshots serialize it as one item-table index */
            unsigned short high; /* high half of the equipment pointer in item/snapshot users */
        } halves;
        void *address; /* player: shield record address spanning +0x50..+0x53 */
        struct DungeonItemEntry *item; /* the same record, typed */
    } shield; /* the equipped shield: one word, read as two halfwords or as the player's shield record pointer */
    /* 0x054 */ int status_flags; /* derived-effect mask; bits 1..4 double HP/MP/attack/defense baselines, capped at 255 by apply_entity_effects */
    /* 0x058 */ struct ObjectNodeHeader *previous_actor_header; /* previous live actor list entry: its ObjectNodeHeader (check_entity_relation and insert_node_before_primary_actor store node headers; readers take NODE_BODY) */
    /* 0x05C */ struct ObjectNodeHeader *next_actor_header; /* next live actor list entry: its ObjectNodeHeader (check_entity_relation and insert_node_before_primary_actor store node headers; readers take NODE_BODY) */
    /* 0x060 */ void * target; /* borrowed actor-body target; while lifted, this is the carrier backlink rather than an attack target */
    /* 0x064 */ short hp_delta; /* signed pending HP delta; effective HP is hp + hp_delta before applying queued damage */
    /* 0x066 */ unsigned char max_mp; /* effective maximum MP: level_max_mp, doubled under a status bit and capped at 255 */
    /* 0x067 */ unsigned char unk_67;
    /* 0x068 */ unsigned char base_attack; /* effective baseline attack: attack, doubled under a status bit and capped at 255 */
    /* 0x069 */ unsigned char base_defense; /* effective baseline defense: defense, doubled under a status bit and capped at 255 */
    /* 0x06A */ short movement_facing; /* queued movement angle copied to facing; 0x1000 units per turn */
    /* 0x06C */ unsigned char turn_fraction; /* fractional turn progress: turn_speed is added into turn_fraction..pending_turn_updates as one 8.8 halfword each turn (the same shape as mp_fraction..mp), 0x100 is one action; the idle reset clears it */
    /* 0x06D */ signed char pending_turn_updates; /* queued turn updates; update_actor_status_and_mp spends MP and advances status timers once per decrement */
    /* 0x06E */ short turn_speed; /* 8.8 turns per game turn: apply_entity_effects sets 0x100, doubles it under the speed status and halves it when slowed; apply_scaled_entity_velocity and the tile classifier multiply by it, nothing accumulates it */
    /* 0x070 */ unsigned char unk_70;
    /* 0x071 */ unsigned char movement_queue_state; /* queued-path state/count; update_actor_status_and_mp clears its high control bit before processing */
    /* 0x072 */ signed char target_tile_x; /* target map column, in tiles */
    /* 0x073 */ signed char target_tile_y; /* target map row, in tiles */
    /* 0x074 */ unsigned char path_x[8]; /* queued path map columns; indexed by the path cursor the movement handlers keep at +0x8A */
    /* 0x07C */ unsigned char path_y[8]; /* queued path map rows, parallel to path_x */
    /* 0x084 */ unsigned char accuracy; /* the attacker's hit baseline: attack preparation adds (random % luck) * 4 and hits at 0x80 or more; try_attack_target_tile stores 0x80, the weapon tables 0x60..0x80, a thrown actor 0x78; unsigned by opposite-sign compile trial (no function changes, and the 0x80 stores compile plain) */
    /* 0x085 */ signed char attack_bonus; /* weapon attack bonus added to current_attack in damage preparation (get_clamped_adjusted_value pairs it with the weapon value); sign not yet trialled; declared signed, the only reader loads it unsigned through a view */
    /* 0x086 */ unsigned char defense_bonus; /* shield defense bonus read on the target (get_shield_defense_bonus pairs it with the shield value); equip loads it from the shield table */
    /* 0x087 */ unsigned char unk_87;
    /* 0x088 */ short ground_height; /* terrain height sampled beneath the actor, in world units */
    /* 0x08A */ short unk_8A;                     /* mostly the path cursor into path_x/path_y; callback variants also keep five other values here (queued terrain height, throw travel steps, ...) */
    /* 0x08C */ union {
        void *address; /* callback address; return contracts differ between actor handlers */
        void (*run)(void *, void *, void *, void *); /* Kewne calls this view and discards any result */
        ActorActionHandler handler; /* the current action handler */
        int word; /* Step 0b width view: handlers clear the slot through an int store */
        unsigned char *byte_ptr; /* Step 0b width view: a handler address stored through a byte-pointer view */
        int *word_ptr; /* ghosh/clown install the address of an action entry word */
    } unk_8C;
    /* 0x090 */ union {
        int value;
        struct { unsigned short low; short high; } parts;
    } unk_90; /* callback scratch word; its high half is signed (unsigned reads take value casts) */
    /* 0x094 */ short sprite_direction; /* the sprite direction frame shown, ((view angle + facing + 0x100) >> 9) & 7; the frame is reselected when it changes */
    /* 0x096 */ short action_timer;
    /* 0x098 */ unsigned short action_state_flags;
    /* 0x09A */ unsigned char action_id; /* action-table selector */
    /* 0x09B */ unsigned char action_phase; /* phase within the selected action */
    /* 0x09C */ signed char route_room; /* room index of the exit the actor routes toward; select_actor_route_target keeps the target while the sprite's room matches it */
    /* 0x09D */ signed char fall_ticks; /* ticks spent airborne: the gravity update adds it times 0x14000 to the fall speed, increments it while airborne and clears it on contact */
    /* 0x09E */ short unk_9E;
    /* UNION: src/dungeon/monster/kewne/advance_kewne_ellipse_attack.c:65,67,69,80 (high half) and :111,142 (whole word) -
     * the same ActorRecord body reads and writes the high half and updates the whole scratch word. */
    /* 0x0A0 */ union {
        int value;
        struct { short low; short high; } parts;
    } unk_A0; /* callback scratch word with signed halves */
    /* 0x0A4 */ union {
        int value; /* landing uses it for accumulated 16.16 vertical displacement */
        ActorScratchHalves halves;
        unsigned char bytes[4];
        void *address; /* kraken links its child ObjectNodeHeader through this scratch slot */
        unsigned char *byte_address; /* byte-addressed callback scratch pointer */
    } unk_A4; /* callback scratch with word/halfword/byte views */
    /* 0x0A8 */ short unk_A8; /* action scratch: a halfword (saved species, tile coordinate, move or fade ticks) in the 65 units
                               * that use it, kept short by opposite-sign compile trial; some action handlers use +0xA8..+0xAB as
                               * one word instead (ashra's jump keeps a vertical accumulator there, the snowman transition its
                               * tint-restore effect node, death's handlers a saved +0xA4 scratch word) through a word view */
    /* 0x0AA */ short unk_AA;
    /* 0x0AC */ union { void *address; int value; unsigned char byte; signed char signed_byte; ActorScratchHalves halves; unsigned char bytes[4]; } unk_AC; /* familiar slot 0 or callback scratch */
    /* 0x0B0 */ union { void *address; int value; unsigned char bytes[4]; signed char signed_bytes[4]; ActorScratchHalves halves; } unk_B0; /* familiar slot 1 or callback scratch, including byte +0xB3 */
    /* 0x0B4 */ union { int value; ActorScratchHalves halves; unsigned char bytes[4]; signed char signed_bytes[4]; } unk_B4; /* callback scratch */
    /* 0x0B8 */ unsigned char unk_B8; /* action scratch: kewne's update keeps a 0..3 state byte here (lbu/sb) and a flag byte at +0xB9; the flame, death and u_boat action handlers use +0xB8 (u_boat also +0xBA) as one halfword through a recorded width view */
    /* 0x0B9 */ unsigned char unk_B9;
    /* 0x0BA */ unsigned char unk_BA;
    /* 0x0BB */ unsigned char unk_BB;
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
    /* 0x0BC */ struct DungeonItemEntry *held_item; /* item the player holds for the current action: begin_holding_item and the egg and menu target paths store it; the pickup animation renders it and tests its kind, the targeted action reads its slot number */
    /* 0x0C0 */ unsigned char pad_C0[8];
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
    /* 0x0F8 */ unsigned char pad_F8[8];
    /* 0x100 */ short unk_100; /* signed: the destination-move handlers start the trap trigger when it is zero or more */
    /* 0x102 */ unsigned char unk_102;            /* player transition flag */
    /* 0x103 */ unsigned char pad_103[1];
    /* 0x104 */ int unk_104; /* selected familiar actor address during command selection; cleared when player input starts a new selection */
    /* 0x108 */ unsigned char pad_108[4];
    /* 0x10C */ unsigned short unk_10C;           /* completion/status bits of the timed sequence */
    /* 0x10E */ unsigned char pad_10E[2];
    /* 0x110 */ struct DungeonItemEntry *pending_item_action; /* item whose use is deferred until the player's action runs; stored only when the owner is the player */
    /* 0x114 */ int unk_114;                      /* word stores 0x202080 / 0x802020 before item-effect dispatch */
    /* 0x118 */ unsigned char pad_118[2];
    /* 0x11A */ short unk_11A; /* the facing saved before the player turns toward a target; no reader found */
    /* 0x11C */ unsigned char pad_11C[8];
    /* 0x124 */ void *unk_124; /* borrowed carried/linked actor body, or null; lift sets its carrier backlink and release clears ACTOR_LIFTED */
    /* 0x128 */ int unk_128;
} PlayerRecord;                                   /* 0x12C */

#endif

