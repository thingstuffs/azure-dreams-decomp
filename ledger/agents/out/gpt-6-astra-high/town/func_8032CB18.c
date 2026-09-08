
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
typedef s32 M2C_UNK;
M2C_UNK func_80019B54();
M2C_UNK func_80019C68();
M2C_UNK func_8001ACE8();
s32 func_8001ADE0();
/* Update the context flag and dispatch the selected entry according to active flags. */
void func_80017318(void *context, M2C_UNK entry_index)
{
  if (func_8001ADE0(0x1459) != 0)
  {
    func_8001ACE8(*((s16 *) (((s8 *) context) + 0x18)));
    func_80019C68(context, entry_index);
    return;
  }
  if (func_8001ADE0(0x1458) != 0)
  {
    func_8001ACE8(*((s16 *) (((s8 *) context) + 0x18)));
  }
  func_80019B54(context, entry_index);
}
