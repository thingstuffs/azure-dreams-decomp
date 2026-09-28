#include "shared/game_work.h"

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
