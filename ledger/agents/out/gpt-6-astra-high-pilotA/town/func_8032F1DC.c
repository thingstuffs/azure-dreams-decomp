
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
typedef s8 M2C_UNK8;
s32 func_8001ADE0();
extern s16 D_8001B8AA;
/* Checks the object's short value at offset 0x18 when the global check returns zero. */
s32 func_800199DC(void *object)
{
  s32 result;
  void *object_ref;
  int initial_result;
  void *saved_object;
  if (initial_result)
  {
    initial_result = 0;
    result = initial_result;
    object_ref = object;
    saved_object = object_ref;
  }
  else
  {
    initial_result = 0;
    result = initial_result;
    object_ref = object;
    saved_object = object_ref;
  }
  if (func_8001ADE0(D_8001B8AA) == 0)
  {
    result = func_8001ADE0(*(s16 *) (((s8 *) saved_object) + 0x18)) != 0;
  }
  return result;
}
