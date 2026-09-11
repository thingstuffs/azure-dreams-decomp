#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033C1C();
M2C_UNK func_80033D08();
M2C_UNK func_800375C0();
M2C_UNK func_8003DB94(void *, M2C_UNK *, s32);
M2C_UNK func_8004491C();
extern M2C_UNK D_80033D54;
extern M2C_UNK D_80037714;
extern M2C_UNK D_800794AC;
extern s32 D_80082ABC;
extern M2C_UNK D_8008B9D8;
extern M2C_UNK D_8008BA00;
extern s32 D_800CFB74[];
extern u8 D_800CFC38[];
extern s32 D_800CFC44[];
/* Initializes a town object and its state for the selected type. */
void func_8008B818(s32 type_id, s32 *init_value_ptr, void *object, void *context)
{
  s32 type_data;
  s32 init_value;
  void *state;
  void *render_data;
  void *transform;
  s32 *type_table;
  s32 *value_table_base;
  s32 *value_table;
  s32 *type_entry;
  *((M2C_UNK **) (((s8 *) object) + 0x10)) = &D_8008B9D8;
  func_8004491C(object, &D_80033D54);
  init_value = 0;
  transform = *((void **) (((s8 *) object) + 8));
  render_data = *((void **) (((s8 *) object) + 0xC));
  state = object + 0x20;
  if (init_value_ptr != 0)
  {
    init_value = *init_value_ptr;
  }
  func_80033C1C(context, init_value);
  {
    s32 context_mode;
    context_mode = 2;
    type_table = D_800CFB74;
    *((void **) (((s8 *) object) + 0x20)) = context;
    *((s32 *) (((s8 *) context) + 0x60)) = context_mode;
  }
  *((s32 *) (((s8 *) state) + 4)) = 0;
  *((s16 *) (((s8 *) state) + 0x66)) = type_id;
  type_entry = type_table - (-type_id);
  type_data = *type_entry;
  if (type_data != 0)
  {
    *((M2C_UNK **) (((s8 *) state) + 8)) = &D_80037714;
    func_800375C0(state, type_data);
  }
  else
  {
    *((M2C_UNK **) (((s8 *) state) + 8)) = 0;
  }
  *((s16 *) (((s8 *) state) + 0x60)) = 0;
  *((s32 *) (((s8 *) render_data) + 0xC)) = 0x808080;
  if (((u32) (type_id - 9)) < 2U)
  {
    func_8003DB94(render_data, &D_800794AC, 0);
  }
  else
  {
    *((s32 *) (((s8 *) render_data) + 8)) = 0;
  }
  if (type_id == 0)
  {
    *((s16 *) (((s8 *) transform) + 2)) = 0x20;
    *((s16 *) (((s8 *) transform) + 6)) = -0x20;
    *((s16 *) (((s8 *) transform) + 0xA)) = 0x200;
  }
  if (type_id == 0xA)
  {
    *((s32 *) (((s8 *) state) + 0x74)) = 0;
    D_80082ABC = (s32) (*(*((u8 **) (((s8 *) state) + 0x7C))));
  }
  *((M2C_UNK **) (((s8 *) state) + 0x68)) = &D_8008BA00;
  value_table_base = D_800CFC44;
  value_table = value_table_base;
  *((s16 *) (((s8 *) state) + 0x64)) = (s16) ((s8) D_800CFC38[type_id]);
  *((s32 *) (((s8 *) state) + 0x6C)) = value_table[type_id];
  if (type_id == 9)
  {
    func_80033D08(state);
  }
}
