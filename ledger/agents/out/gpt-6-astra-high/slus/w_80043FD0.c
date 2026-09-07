#include "common.h"

#include "common.h"
typedef struct S_80083120
{
  s16 field0;
  s16 field2;
  s16 field4;
  s16 field6;
} S_80083120;
extern S_80083120 D_80083120[8];
extern s8 D_80080A86;
extern s32 D_800814A0;
#ifdef NON_MATCHING
#define D_80080A86_store D_80080A86
#define D_800814A0_load (&D_800814A0)
#define D_800814A0_store D_800814A0
#else
#define D_80080A86_store (*(s8 *)0x80080A86)
extern s32 D_800814A0_load[3];
__asm__(".set D_800814A0_load, 0x800814A0");
#define D_800814A0_store (*(s32 *)0x800814A0)
#endif
extern s16 func_8003F794(s16 a0, s16 a1);
extern void func_80040454(void);
extern void func_80040418(void);
typedef struct S_80043FD0_Node
{
  struct S_80043FD0_Node *next;
  u8 pad[0x1E - 4];
  u16 field_1E;
} S_80043FD0_Node;
typedef struct S_80043FD0
{
  S_80043FD0_Node *(*field_0)(void *);
  void *field_4;
  s16 field_8;
  s16 field_A;
  s16 field_C;
} S_80043FD0;
/* Advances the controller state and updates node and global status flags. */
void func_80043FD0(S_80043FD0 *controller)
{
  s16 state = controller->field_A;
  S_80043FD0_Node *node;
  s32 global_flags;
  if (state == 2)
  {
    if ((*((u8 *) controller->field_4)) != 0)
    {
      s16 slot_arg = controller->field_C;
      if (slot_arg != 0)
      {
        controller->field_8 = func_8003F794(5, slot_arg);
      }
      func_80040454();
      D_80080A86_store = 0;
      controller->field_A = 0;
    }
    return;
  }
  if (D_80083120[controller->field_8].field0 != 0)
  {
    return;
  }
  if (state != 0)
  {
    node = controller->field_0(controller->field_4);
    if (node == 0)
    {
      D_80083120[controller->field_8].field0 = 6;
      D_80083120[controller->field_8].field2 = 1;
      D_80083120[controller->field_8].field4 = 1;
      D_80083120[controller->field_8].field6 = 0;
      return;
    }
    func_80040418();
    D_80080A86_store = (state = 1);
    node->field_1E &= 0xF3FF;
  }
  *((u16 *) (((char *) controller) - 2)) |= 0x8000;
  global_flags = D_800814A0_load[0];
  global_flags |= 0x8000;
  
  D_800814A0_store = global_flags;
}
