
struct S_80083178
{
  char pad0[2];
  unsigned short unk2;
  char pad4[6];
  unsigned short unkA;
  char padC[0x94];
  short f_A0;
  char pad_a2[2];
  short f_A4;
  short f_A6;
  short f_A8;
  char pad_aa[0xB4 - 0xAA];
  void (*callback)(void);
  void *field_B8;
  char pad_bc[(0xD8 - 0xB8) - 4];
  void *ptr;
  char pad_dc[0x1C4 - 0xDC];
};
typedef struct 
{
  unsigned char data[24];
} MonsterInitialStats;
typedef struct 
{
  unsigned char data[12];
} Trap;
typedef struct 
{
  unsigned char data[8];
} StatGrowth;
extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
extern struct S_80083178 D_80083178;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern u8 D_800E3DB0[];
/* Initializes seven indexed records with kinds 1, 3, and 2 and clears their remaining fields. */
void func_80016EC0(void)
{
  s16 next_type1_count;
  s16 next_type3_count;
  u8 *type2_payload;
  s16 type1_count;
  s16 type3_count;
  u8 *record;
  u8 *type1_payload;
  u8 *type3_payload;
  short record_index;
  s32 record_kind;
  record = D_800E3DB0;
  type1_count = 0;
  record_index = 0;
  record_kind = 1;
  type1_payload = record + 4;
  do
  {
    next_type1_count = type1_count + 1;
    type1_count = next_type1_count;
    *record = record_kind;
    *((volatile s8 *) (((u8 *) type1_payload) + (-1))) = record_index;
    record_index += 1;
    *((volatile s8 *) (((u8 *) type1_payload) + (-3))) = 0;
    *((volatile s8 *) (((u8 *) type1_payload) + (-2))) = 0;
    *((volatile s32 *) (((u8 *) type1_payload) + 0)) = 0;
    type1_payload += 8;
    record += 8;
  }
  while (next_type1_count < 4);
  type3_count = 0;
  record_kind = 3;
  type3_payload = record + 4;
  do
  {
    next_type3_count = type3_count + 1;
    type3_count = next_type3_count;
    *record = record_kind;
    *((volatile s8 *) (((u8 *) type3_payload) + (-1))) = record_index;
    record_index += 1;
    *((volatile s8 *) (((u8 *) type3_payload) + (-3))) = 0;
    *((volatile s8 *) (((u8 *) type3_payload) + (-2))) = 0;
    *((volatile s32 *) (((u8 *) type3_payload) + 0)) = 0;
    type3_payload += 8;
    record += 8;
  }
  while (next_type3_count < 2);
  *((volatile s8 *) (((u8 *) record) + 0)) = 2;
  *((volatile s8 *) (((u8 *) record) + 1)) = 0;
  *((volatile s8 *) (((u8 *) record) + 2)) = 0;
  type2_payload = record + 4;
  *((volatile s8 *) (((u8 *) record) + 3)) = record_index;
  *((s32 *) type2_payload) = 0;
}
