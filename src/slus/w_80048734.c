#include "common.h"

#include "common.h"

void func_80048734(u8 *a0, u8 *a1)
{
  u32 a2;
  s32 v0;
  s32 v1;
  goto test;
  body:
  v0 = (*a0) >> 6;

  cont:
  v1 = v0;

  v0 = -1;
  if (v1 == v0)
  {
    goto skip;
  }
  a2 &= 0x3F;
  write:
  *a1 = a2;

  v1--;
  a1++;
  if (v1 != v0)
  {
    goto write;
  }
  skip:
  a0++;

  test:
  a2 = *a0;

  if (a2 != 1)
  {
    if (1)
    {
      v0 = a2 >> 6;
      goto cont;
    }
    do
    {
    }
    while (0);
  }
  v0 = a0[1];
  v1 = v0 != a2;
  if (v1)
  {
    goto body;
  }
  return;
}
