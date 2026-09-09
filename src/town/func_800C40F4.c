
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
extern void func_8003AFE0(s32 a0, s32 a1);
extern void func_80066F78(s32 a0);
extern void file_load_com(void *arg);
extern void func_8003C758(void *arg);
extern void reserve_twch_load(s32 a0);
extern void town_seq_reserve(s32 a0, s32 a1);
extern u8 D_80080E28;
extern u8 D_800D1D54;
extern u8 D_80080F48;
extern u8 D_80080F98;
/* Initialize town resources and configure the scene. */
void func_800C1854(void)
{
  u8 *resource_data;
  do {
    func_8003AFE0(1, 0x73);
    func_80066F78(1);
    file_load_com(&D_80080E28);
  } while (0);
  resource_data = &D_800D1D54;
  file_load_com(resource_data);
  func_8003C758(&D_80080F48);
  func_8003C758(&D_80080F98);
  reserve_twch_load(6);
  reserve_twch_load(3);
  town_seq_reserve(0x27, 0x200);
}
