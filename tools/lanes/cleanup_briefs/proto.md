
## Your task: real prototypes instead of `M2C_UNK`

The decompiler declared callees it could not type as `M2C_UNK func_X();  /* extern */` (and sometimes parameters or
locals as `M2C_UNK`). Replace each `M2C_UNK` with the REAL type:
1. Find the callee's definition: `src/<container>/func_X.c` (same container first; for SLUS callees `src/slus/w_X.c` or
   a `slus/*` file - `ls src/slus | grep -i X`), or its declaration in `include/` (`rg --max-filesize 4M -n "func_X\b" include`).
   Use its return type exactly (void, s32, u8 *, a struct pointer ...). If a shared header in `include/` already
   declares it, prefer including that header ONLY if the row already includes it; otherwise write the prototype line
   with the real type and keep the `/* extern */` comment.
2. If the callee's definition has a full parameter list, you MAY copy it into the prototype ONLY if the row stays exact
   (a prototype changes argument promotion - measure). Otherwise keep `()`.
3. An `M2C_UNK` parameter or local: give it the type its uses imply (a value stored to an s16 field and compared
   signed -> s16, etc.); measure; if not exact, try s32; if still not exact, leave it.
4. A callee whose definition you cannot find: leave it and list it in the report.
Return type `void` for a callee whose result the row never uses is the commonest exact fix; `s32` the next.
