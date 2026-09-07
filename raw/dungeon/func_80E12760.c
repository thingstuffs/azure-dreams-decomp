
struct S_80083178Vector
{
  short x;
  short y;
  short z;
  short pad;
};
struct S_80083178State
{
  struct S_80083178Vector v[4];
};
struct S_80083178
{
  char pad0[2];
  unsigned short unk2;
  char pad4[6];
  unsigned short unkA;
  char padC[0x94 - 0xC];
  struct S_80083178State state_94;
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
extern struct S_80083178State D_80083CE8;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct 
{
  u32 words[6];
} Copy24;
typedef struct 
{
  u16 x;
  u16 y;
  u16 z;
} Vec3u16;
extern void *func_8003FC64(s32 size);
extern void func_8004491C(void *object, void *callback);
extern void func_80047784(void *object, s32 kind, s32 arg2);
extern void *func_8003DE58(void *arg0, void *arg1, Vec3u16 *out, s32 arg3);
extern s32 D_80045340;
extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern u8 D_80175978;
void *func_80175F60(void *arg0, Copy24 *input, void *source)
{
  void *new_var;
  Copy24 local;
  Vec3u16 delta;
  u16 selector;
  s32 table_offset;
  Copy24 *held_input;
  void *object;
  void *child;
  void *held_source;
  void *render;
  void *result;
  held_input = input;
  held_source = source;
  selector = *((u16 *) (((u8 *) arg0) + 0x2A));
  new_var = arg0;
  local = *held_input;
  table_offset = (selector >> 8) & 0xE;
  *((u16 *) (((u8 *) (&local)) + 2)) += ((*((s16 *) (((u8 *) (&D_8006CCD8)) + table_offset))) * (*((s16 *) (((u8 *) arg0) + 0xB2)))) * 0x40;
  *((u16 *) (((u8 *) (&local)) + 6)) += ((*((s16 *) (((u8 *) (&D_8006CCE8)) + table_offset))) * (*((s16 *) (((u8 *) new_var) + 0xB2)))) * 0x40;
  object = func_8003FC64(0x312);
  if (object != 0)
  {
    *((void **) (((u8 *) object) + 0x10)) = &D_80175978;
    func_8004491C(object, &D_80045340);
    render = *((void **) (((u8 *) object) + 0xC));
    *((s32 *) (((u8 *) render) + 0x28)) = *((s32 *) (((u8 *) held_source) + 0x28));
    *((s16 *) (((u8 *) render) + 0x1E)) = 0x800;
    *((s16 *) (((u8 *) render) + 0x1C)) = 0x800;
    *((u32 *) (((u8 *) render) + 0xC)) = 0x00808080;
    *((u16 *) (((u8 *) render) + 0x14)) |= 0xC;
    *((u16 *) (((u8 *) render) + 0x10)) |= 0x20;
    func_80047784(render, 0x47, 0);
    child = *((void **) (((u8 *) object) + 8));
    *((Copy24 *) (((u8 *) object) + 0x24)) = *held_input;
    held_input = (Copy24 *) (((u8 *) object) + 0x20);
    delta.z = 0;
    delta.y = 0;
    delta.x = 0;
    if (func_8003DE58(*((void **) (((u8 *) held_source) + 8)), held_source, &delta, 1) != 0)
    {
      *((u16 *) (((u8 *) held_input) + 6)) += delta.x;
      *((u16 *) (((u8 *) child) + 2)) = *((u16 *) (((u8 *) held_input) + 6));
      *((u16 *) (((u8 *) held_input) + 0xA)) += delta.y;
      *((u16 *) (((u8 *) child) + 6)) = *((u16 *) (((u8 *) held_input) + 0xA));
      *((u16 *) (((u8 *) held_input) + 0xE)) += delta.z;
      *((u16 *) (((u8 *) child) + 0xA)) = *((u16 *) (((u8 *) held_input) + 0xE));
    }
    *((s32 *) (((u8 *) held_input) + 0x10)) = (((s32) local.words[0]) - (*((s32 *) (((u8 *) held_input) + 4)))) / 0x20;
    *((s32 *) (((u8 *) held_input) + 0x14)) = (((s32) local.words[1]) - (*((s32 *) (((u8 *) held_input) + 8)))) / 0x20;
    result = object;
    return result;
  }
  if (held_input || source)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}
