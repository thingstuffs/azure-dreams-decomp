#ifndef SHARED_ENTITY_H
#define SHARED_ENTITY_H

/* EntityRec: the actor/entity record of the DUNGEON (and TOWN) object system, hand-recovered (r78 phase 5).
 * It supersedes the generated include/records/Rec_D_800E3D7C.h: same 0x12C-byte layout, its "accessed as both"
 * unions resolved to one field type each (the majority retail access; the minority reads keep a cast or a view
 * at the use).  Instances: the pointee of D_800E3D7C (record_ptrs.h), the 537 functions that take one as a
 * parameter (Rec census), and the records the census rooted at D_80083780 / D_80083498.
 * Objects carry a 0x20-byte header BEFORE the record (callers pass `record - 0x20` to the object system and
 * mark `((u16 *)record)[-1] |= 0x8000` when it finishes); that header is not part of this type.
 * Names only where every use agrees (tileX/tileY, facing, x/y/z, target, flags words); the rest stay unk_. */

typedef union Fixed1616 {
    int v;                          /* the whole 16.16 word (lw/sw) */
    struct { unsigned short frac; short i; } w;   /* w.i: the integer half (lh at +2) */
} Fixed1616;

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
    /* 0x0DC */ unsigned char pad_DC[24];         
    /* 0x0F4 */ int unk_F4;                       /* Rec_D_800814A8 */
    /* 0x0F8 */ unsigned char pad_F8[10];         
    /* 0x102 */ unsigned char unk_102;            /* Rec_D_800814A8 */
    /* 0x103 */ unsigned char pad_103[1];         
    /* 0x104 */ int unk_104;                      
    /* 0x108 */ unsigned char pad_108[4];         
    /* 0x10C */ unsigned short unk_10C;           /* Rec_D_800814A8 */
    /* 0x10E */ unsigned char pad_10E[2];         
    /* 0x110 */ int unk_110;                      
    /* 0x114 */ unsigned char pad_114[20];        
    /* 0x128 */ int unk_128;                      
} EntityRec;

#endif

