
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
/* Create a render object and initialize its position and motion toward a directional target. */
void *func_80175F60(void *emitter, Copy24 *position, void *source)
{
  void *emitter_copy;
  Copy24 target_position;
  Vec3u16 position_offset;
  u16 direction_flags;
  s32 direction_offset;
  Copy24 *position_data;
  void *object;
  void *transform;
  void *source_copy;
  void *render;
  void *result;
  position_data = position;
  source_copy = source;
  direction_flags = *((u16 *) (((u8 *) emitter) + 0x2A));
  emitter_copy = emitter;
  target_position = *position_data;
  direction_offset = (direction_flags >> 8) & 0xE;
  *((u16 *) (((u8 *) (&target_position)) + 2)) += ((*((s16 *) (((u8 *) (&D_8006CCD8)) + direction_offset))) * (*((s16 *) (((u8 *) emitter) + 0xB2)))) * 0x40;
  *((u16 *) (((u8 *) (&target_position)) + 6)) += ((*((s16 *) (((u8 *) (&D_8006CCE8)) + direction_offset))) * (*((s16 *) (((u8 *) emitter_copy) + 0xB2)))) * 0x40;
  object = func_8003FC64(0x312);
  if (object != 0)
  {
    *((void **) (((u8 *) object) + 0x10)) = &D_80175978;
    func_8004491C(object, &D_80045340);
    render = *((void **) (((u8 *) object) + 0xC));
    *((s32 *) (((u8 *) render) + 0x28)) = *((s32 *) (((u8 *) source_copy) + 0x28));
    *((s16 *) (((u8 *) render) + 0x1E)) = 0x800;
    *((s16 *) (((u8 *) render) + 0x1C)) = 0x800;
    *((u32 *) (((u8 *) render) + 0xC)) = 0x00808080;
    *((u16 *) (((u8 *) render) + 0x14)) |= 0xC;
    *((u16 *) (((u8 *) render) + 0x10)) |= 0x20;
    func_80047784(render, 0x47, 0);
    transform = *((void **) (((u8 *) object) + 8));
    *((Copy24 *) (((u8 *) object) + 0x24)) = *position_data;
    position_data = (Copy24 *) (((u8 *) object) + 0x20);
    position_offset.z = 0;
    position_offset.y = 0;
    position_offset.x = 0;
    if (func_8003DE58(*((void **) (((u8 *) source_copy) + 8)), source_copy, &position_offset, 1) != 0)
    {
      *((u16 *) (((u8 *) position_data) + 6)) += position_offset.x;
      *((u16 *) (((u8 *) transform) + 2)) = *((u16 *) (((u8 *) position_data) + 6));
      *((u16 *) (((u8 *) position_data) + 0xA)) += position_offset.y;
      *((u16 *) (((u8 *) transform) + 6)) = *((u16 *) (((u8 *) position_data) + 0xA));
      *((u16 *) (((u8 *) position_data) + 0xE)) += position_offset.z;
      *((u16 *) (((u8 *) transform) + 0xA)) = *((u16 *) (((u8 *) position_data) + 0xE));
    }
    *((s32 *) (((u8 *) position_data) + 0x10)) = (((s32) target_position.words[0]) - (*((s32 *) (((u8 *) position_data) + 4)))) / 0x20;
    *((s32 *) (((u8 *) position_data) + 0x14)) = (((s32) target_position.words[1]) - (*((s32 *) (((u8 *) position_data) + 8)))) / 0x20;
    result = object;
    return result;
  }
  if (position_data || source)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}
