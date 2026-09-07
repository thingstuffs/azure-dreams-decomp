#include "common.h"
typedef struct 
{
  u8 *value;
  u8 pad[8];
} Global83160;
typedef struct 
{
  u16 x;
  u16 y;
  u16 z;
  u16 pad;
} TableEntry;
extern s16 D_8002632A;
extern u8 D_80026478[];
extern Global83160 D_80083160;
extern void func_80025398(void) __attribute__((noreturn));
extern void func_8002556C(void) __attribute__((noreturn));
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
s32 func_80025340(void *arg0, void *arg1, void *arg2)
{
  register TableEntry *table = (TableEntry *) D_80026478;
  {
    u8 *global_value = D_80083160.value;
    register void *owner ASM_REG("$20") = arg0;
    register void *vertex ASM_REG("$16") = arg1;
    register void *interp ASM_REG("$18") = arg2;
    register u8 **global ASM_REG("$22") = (u8 **) &D_80083160;
    register u8 *scratch ASM_REG("$17") = (u8 *) 0x1F800000;
    register u8 *prim ASM_REG("$19");
    u8 *packet;
    register u32 color_even ASM_REG("$3");
    register u32 color_odd ASM_REG("$2");
    register void *next ASM_REG("$6");
    s32 depth;
    s16 amount;
    s32 index;
    s32 packet_word;
    ASM_KEEP(owner);
    ASM_KEEP(vertex);
    ASM_KEEP(interp);
    ASM_KEEP(global);
    ASM_KEEP(scratch);
    *((u8 **) (((u8 *) scratch) + 0x18)) = *((u8 **) (((u8 *) global_value) + 0x8D0));
    *((u8 **) (((u8 *) scratch) + 0x20)) = global_value + 0xB0;
    ASM_MEM_BARRIER();
    prim = *((u8 **) (((u8 *) scratch) + 0x18));
    *((u8 **) (((u8 *) scratch) + 0x18)) = prim + 0x14;
    amount = *((s16 *) (((u8 *) interp) + 6));
    if (amount >= 0)
    {
      *((u16 *) (((u8 *) scratch) + 0)) = *((u16 *) (((u8 *) vertex) + 0xE));
      *((u16 *) (((u8 *) scratch) + 2)) = *((u16 *) (((u8 *) vertex) + 0x12));
      *((u16 *) (((u8 *) scratch) + 4)) = *((u16 *) (((u8 *) vertex) + 0x16));
      *((s32 *) (((u8 *) scratch) + 0xC0)) = func_80065420(scratch, prim + 8, scratch + 0x90, scratch + 0x94);
      *((u16 *) (((u8 *) scratch) + 0)) = (*((u16 *) (((u8 *) vertex) + 0xE))) + ((((*((s16 *) (((u8 *) vertex) + 2))) - (*((s16 *) (((u8 *) vertex) + 0xE)))) * (*((s16 *) (((u8 *) interp) + 6)))) >> 8);
      *((u16 *) (((u8 *) scratch) + 2)) = (*((u16 *) (((u8 *) vertex) + 0x12))) + ((((*((s16 *) (((u8 *) vertex) + 6))) - (*((s16 *) (((u8 *) vertex) + 0x12)))) * (*((s16 *) (((u8 *) interp) + 6)))) >> 8);
      *((u16 *) (((u8 *) scratch) + 4)) = (*((u16 *) (((u8 *) vertex) + 0x16))) + ((((*((s16 *) (((u8 *) vertex) + 0xA))) - (*((s16 *) (((u8 *) vertex) + 0x16)))) * (*((s16 *) (((u8 *) interp) + 6)))) >> 8);
      index = (*((s16 *) (((u8 *) owner) + 0x22))) + 0x10;
      if (D_8002632A < index)
      {
        register s32 table_index ASM_REG("$2");
        register u16 table_value ASM_REG("$3");
        table[index].x = *((u16 *) (((u8 *) scratch) + 0));
        table_index = *((s16 *) (((u8 *) owner) + 0x22));
        table_value = *((u16 *) (((u8 *) scratch) + 2));
        table_index += 0x10;
        table[table_index].y = table_value;
        table_index = *((s16 *) (((u8 *) owner) + 0x22));
        table_value = *((u16 *) (((u8 *) scratch) + 4));
        table_index += 0x10;
        table[table_index].z = table_value;
        func_8002556C();
      }
    }
    else
    {
      *((u16 *) (((u8 *) scratch) + 0)) = (*((u16 *) (((u8 *) vertex) + 2))) - ((((*((s16 *) (((u8 *) vertex) + 0xE))) - (*((s16 *) (((u8 *) vertex) + 2)))) * amount) >> 8);
      *((u16 *) (((u8 *) scratch) + 2)) = (*((u16 *) (((u8 *) vertex) + 6))) - ((((*((s16 *) (((u8 *) vertex) + 0x12))) - (*((s16 *) (((u8 *) vertex) + 6)))) * (*((s16 *) (((u8 *) interp) + 6)))) >> 8);
      *((u16 *) (((u8 *) scratch) + 4)) = (*((u16 *) (((u8 *) vertex) + 0xA))) - ((((*((s16 *) (((u8 *) vertex) + 0x16))) - (*((s16 *) (((u8 *) vertex) + 0xA)))) * (*((s16 *) (((u8 *) interp) + 6)))) >> 8);
      *((s32 *) (((u8 *) scratch) + 0xC0)) = func_80065420(scratch, prim + 8, scratch + 0x90, scratch + 0x94);
      *((u16 *) (((u8 *) scratch) + 0)) = *((u16 *) (((u8 *) vertex) + 2));
      *((u16 *) (((u8 *) scratch) + 2)) = *((u16 *) (((u8 *) vertex) + 6));
      *((u16 *) (((u8 *) scratch) + 4)) = *((u16 *) (((u8 *) vertex) + 0xA));
    }
    ASM_MEM_BARRIER();
    depth = ((*((s32 *) (((u8 *) scratch) + 0xC0))) + func_80065420(scratch, prim + 0x10, scratch + 0x90, scratch + 0x94)) >> 1;
    *((s32 *) (((u8 *) scratch) + 0xC0)) = depth;
    if (((u32) depth) < 0x1E0U)
    {
      packet = prim;
      *((u8 *) (((u8 *) packet) + 3)) = (packet_word = *((s32 *) (((u8 *) interp) + 0xC)), 4);
      *((s32 *) (((u8 *) packet) + 4)) = packet_word;
      color_even = *((u8 *) (((u8 *) packet) + 4));
      ASM_KEEP(color_even);
      *((volatile u8 *) (((u8 *) packet) + 7)) = 0x52;
      ASM_MEM_BARRIER();
      color_odd = *((u8 *) (((u8 *) packet) + 5));
      ASM_KEEP(color_odd);
      color_even >>= 1;
      *((u8 *) (((u8 *) packet) + 0xC)) = color_even;
      color_even = *((u8 *) (((u8 *) packet) + 6));
      ASM_KEEP(color_even);
      color_odd >>= 1;
      *((volatile u8 *) (((u8 *) packet) + 0xD)) = color_odd;
      ASM_MEM_BARRIER();
      color_even >>= 1;
      *((u8 *) (((u8 *) packet) + 0xE)) = color_even;
      func_8006658C((*((u8 **) (((u8 *) scratch) + 0x20))) + ((*((s32 *) (((u8 *) scratch) + 0xC0))) * 4), packet);
      vertex = *((u8 **) (((u8 *) scratch) + 0x18));
      *((u8 **) (((u8 *) scratch) + 0x18)) = ((u8 *) vertex) + 0xC;
      func_80067F20(vertex, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
      func_8006658C((*((u8 **) (((u8 *) scratch) + 0x20))) + ((*((s32 *) (((u8 *) scratch) + 0xC0))) * 4), vertex);
    }
    next = *((void **) (((u8 *) owner) + (-8)));
    if (next != 0)
    {
      owner = ((u8 *) next) + 0x20;
      vertex = *((void **) (((u8 *) next) + 8));
      interp = *((void **) (((u8 *) next) + 0xC));
      ASM_KEEP(owner);
      ASM_KEEP(vertex);
      ASM_KEEP(interp);
      func_80025398();
    }
    ASM_CLOBBER("$2");
    ASM_CLOBBER("$6");
    *((u8 **) (((u8 *) (*global)) + 0x8D0)) = *((u8 **) (((u8 *) scratch) + 0x18));
    return 0;
  }
}
