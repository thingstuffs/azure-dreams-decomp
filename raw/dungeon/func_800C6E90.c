
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
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
extern s32 D_800CEEFC[3];
typedef struct DungeonObject
{
  s8 pad0[8];
  struct DungeonVertex *field8;
  struct DungeonPacket *fieldC;
  void *field10;
} DungeonObject;
typedef struct DungeonVertex
{
  s8 pad0[2];
  s16 field2;
  s8 pad4[2];
  s16 field6;
  s8 pad8[2];
  s16 fieldA;
  s8 padC[2];
  s16 fieldE;
  s8 pad10[2];
  s16 field12;
  s8 pad14[2];
  s16 field16;
} DungeonVertex;
typedef struct DungeonPacket
{
  s8 pad0[6];
  s16 field6;
  void *field8;
  s32 fieldC;
  s16 field10;
  s16 field12;
  u16 field14;
  s16 field16;
  s8 pad18[4];
  u16 field1C;
  u16 field1E;
} DungeonPacket;
extern void *func_8003FC64();
extern void func_8004491C();
extern s32 D_800CC4F0;
extern s32 D_800E03D4[3];
void *func_800CC5F0(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u16 arg5)
{
  DungeonObject *obj;
  DungeonVertex *vertex;
  DungeonVertex *tail_vertex;
  DungeonPacket *packet;
  s32 packet_color;
  s16 x;
  s16 y;
  s16 sp5;
  obj = func_8003FC64(0x202);
  sp5 = (s16) arg4;
  if (obj != 0)
  {
    obj->field10 = &D_800CC4F0;
    func_8004491C(obj, D_800CEEFC);
    packet_color = 0x00800000;
    x = ((arg0 << 0x10) >> 0xA) + 0x20;
    vertex = obj->field8;
    packet_color |= 0x8080;
    vertex->field2 = x;
    vertex->fieldE = x;
    y = ((arg1 << 0x10) >> 0xA) + 0x20;
    vertex->field6 = y;
    vertex->field12 = y;
    vertex->fieldA = arg2;
    vertex->field16 = arg2;
    packet = obj->fieldC;
    packet->fieldC = packet_color;
    packet->field8 = D_800E03D4;
    packet->field14 = packet->field14 | 0xC;
    if ((arg4 << 0x10) != 0)
    {
      packet->field1E = 0x1000;
    }
    else
    {
      packet->field1E = 0x400;
    }
    packet->field1C = packet->field1E;
    if ((sp5 << 0x10) == 0)
    {
      packet->field10 = 0x20;
    }
    else
    {
      packet->field10 = 0x60;
    }
    packet->field6 = 0x20;
    tail_vertex = (DungeonVertex *) (((s8 *) obj) + 0x20);
    *((s16 *) (((s8 *) tail_vertex) + 4)) = arg3;
    tail_vertex->field2 = 8;
    *((u16 *) (((s8 *) tail_vertex) + 6)) = arg5;
  }
  return obj;
}
