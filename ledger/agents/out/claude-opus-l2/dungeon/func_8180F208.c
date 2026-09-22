#include "common.h"
#include "m2c_compat.h"
extern s32 D_800250E8[3];
extern u8 D_800251E8[9];
s32 func_80099194();
s32 func_8009929C();
extern s32 D_80025024;
extern s32 D_800250B8;
extern s32 D_800250D8;
extern s32 D_800250F4;
extern s32 D_80025110;
extern s32 D_8002512C;
extern s32 D_80025154;
extern s32 D_80025184;
extern s32 D_800251B4;
extern s32 D_80025208;
extern s32 D_8002522C;
extern s32 D_80025244;
extern s32 D_80025260;
extern s32 D_80025284;
extern s32 D_800252A4;
extern s32 D_800252C8;
extern s32 D_800252E4;
extern s32 D_80025300;
extern s32 D_80025318;
extern M2C_UNK D_80025160;
/* Build the status-effect name list for the object's 0x54 flag word, comma-separated; returns the fallback when no flag is set. */
s32 func_80028208(void *obj, s32 fallback)
{
  s32 text;
  s32 count;
  s32 result;
  count = 0;
  text = func_80099194(&D_800250B8);
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 1)
  {
    text = func_80099194(&D_800250D8, func_8009929C(0xA, text));
    count = 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 2)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_800250F4, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 4)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025110, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 8)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_8002512C, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025154, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x20)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025160, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x80)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025184, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x100)
  {
    obj++;
    obj--;
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_800251B4, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x8000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194((s32 *) D_800251E8, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x100000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025208, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_8002522C, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x02000000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025244, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x04000000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025260, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x08000000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025284, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10000000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_800252A4, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x20000000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_800252C8, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x40000000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_800252E4, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x200000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025300, func_8009929C(0xA, text));
    count += 1;
  }
  if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x4000)
  {
    if ((count << 0x10) != 0)
    {
      text = func_80099194(D_800250E8, text);
    }
    text = func_80099194(&D_80025318, func_8009929C(0xA, text));
    count += 1;
  }
  if ((count << 0x10) != 0)
  {
    result = func_80099194(&D_80025024, text);
  }
  else
  {
    result = fallback;
  }
  return result;
}
