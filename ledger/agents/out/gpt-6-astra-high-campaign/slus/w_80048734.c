#include "common.h"

#include "common.h"

/* Expands six-bit values into runs of one to four bytes until the 1, 1 terminator. */
void func_80048734(u8 *source, u8 *output)
{
  u32 encoded_byte;
  s32 run_limit;
  s32 remaining;
  goto test;
  body:
  run_limit = (*source) >> 6;

  cont:
  remaining = run_limit;

  run_limit = -1;
  if (remaining == run_limit)
  {
    goto skip;
  }
  encoded_byte &= 0x3F;
  write:
  *output = encoded_byte;

  remaining--;
  output++;
  if (remaining != run_limit)
  {
    goto write;
  }
  skip:
  source++;

  test:
  encoded_byte = *source;

  if (encoded_byte != 1)
  {
    if (1)
    {
      run_limit = encoded_byte >> 6;
      goto cont;
    }
    do
    {
    }
    while (0);
  }
  run_limit = source[1];
  remaining = run_limit != encoded_byte;
  if (remaining)
  {
    goto body;
  }
  return;
}
