# Source-level return audit: `func_80049374` chain

This is a bounded textual audit over `src/slus` and `include`, following direct C callers through at most two wrapper levels. It does not inspect retail instructions or assembly call tables; source-level return propagation alone cannot decide whether retail consumes `$v0`.

`src/slus/w_80049374.c:25,34,69` declares `extern s32 func_8004DD2C(char *)`, defines `s32 func_80049374(Item *, StrPair *)`, and returns `func_8004DD2C(item_text)`. The target C definition at `src/slus/w_8004DD2C.c:11` is `void func_8004DD2C(void *)`; its body ends after a call to `func_8003528C` and has no return expression. The apparent return from `func_80049374` therefore rests on an incompatible cross-file declaration.

The direct source callers of `func_80049374` are:

| Caller | Source use | Return handling |
|---|---|---|
| `func_80049490` | `src/slus/code.c:449-454` | Declared `int`; directly returns `func_80049374(object, D_800713FC)`. |
| `func_800494B4` | `src/slus/w_800494B4.c:4,10-22` | Declared `int`; directly returns `func_80049374(saved_object, selected_array)`. |

A direct-name search finds no further source caller of either `func_80049490` or `func_800494B4` within `src/slus` and `include`; their only additional hits are definitions/index entries. Thus the two C wrappers propagate an `int` in source, but no in-scope C callsite visibly tests, stores, or otherwise consumes it. This is consistent with false-return propagation from decompilation, but is not proof that a retail caller does not consume `$v0`: assembly references, function-pointer tables, or callers outside the bounded source scope remain unexamined.

There is a separate call-signature conflict on the callee path. `w_8004DD2C.c:8,37` locally declares `func_8003528C(void *)` and passes `&D_80083D98[submit_index]`. The canonical source definition is `src/slus/konami_runtime_w_8003528C.c:10-11`: `void func_8003528C(s32 value)`, which forwards `value` to `func_80034F88(&D_80082A38, value)`. `src/slus/konami_runtime_w_80034F88.c:10` defines `func_80034F88(void *, s32)` and returns `void`. `w_8004DDE4.c:8,50` similarly declares the pointer form and passes a pointer; `w_8004E130.c:7,22` declares/calls a no-argument form. These source declarations do not agree with the canonical definition. Root-level machine-dataflow review is needed to interpret their retail argument and return behavior.

The two wrapper functions and their direct callers are the complete source-level chain found within the requested scope:

`func_80049374` → (`func_80049490` → no direct C caller found; `func_800494B4` → no direct C caller found).

No build or source edit was made. Search commands were bounded to `src/slus` and `include` with `rg --max-filesize 4M`.
