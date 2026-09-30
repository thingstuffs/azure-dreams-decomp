## Rounds 81-83 rules (09-30; read before the rows)
Full text (paths relative to the repository root): tools/learnings/pin_removal_possibilities.md sections "Round 81", "Round 82", "Round 83".
- **Cell and flags first.** Many pins were fitted at the WRONG compiler cell or with a per-row crutch flag. Check the
  row's module recipe with `python3 tools/lanes/modcell.py` before hunting a shape. If your
  pin-free text is exact only at the module recipe (no crutch flag / cdk instead of 2.8.x), stage it there with
  `lab.py stage-cell <row> cand.c --cfg "<module recipe>" --note "..."` - never at a cfg that ADDS a flag, never toward
  2.8.x, and report the cell move in REPORT.md.
- **`-fno-strength-reduce` hid INDEXED loops:** a hand pointer walk (`p += K; p->f`) with >= 2 constant-offset accesses
  is what cdk reduces into 0-offset registers; retail's stepping register with offsets kept = `base[i].f` in a for
  loop (counter as loop variable, increment after the last giv use). A hand cursor `q = p + c` beside a real walker is
  loop.c's own combined register: delete q, read fields off p. An `(s16)counter` cast at several sites = an s16 counter.
- **Scratchpad (0x1F800000) accesses are struct members:** REG/KEEP/BARRIER pins between scratch stores and struct-pointer
  loads fall when the scratch stores go through a struct pointer instead of scalar casts at a constant address.
- **volatile byte reads / BARRIER+KEEP holding `lbu` apart from `sll 24/sra 24`** = HImode locals: `s16 x = (s8)p->f ...`.
- **Parameter REG_EQUIV halves global priority:** a never-reassigned parameter ranks at half; a local copy ranks double.
  Use the parameter directly (or the inverse) to flip a callee-saved swap.
- **Reload right after a store = an intervening store** in the source (cse invalidates varying-address MEMs on a store).
- **expand_preferences is one in-order pass:** test/dereference `q->f` directly where q is argument N of a call so the
  load temp inherits q's argument-register preference.
- **Read-modify-write temp pinned to v0/v1:** a two-set local (`t = x; t |= c;`) instead of a tied local quantity.
- **cdk marks every sibling field of a struct with a volatile member volatile** (front end) - a volatile field in a
  typed struct can explain "extra reloads" of its neighbours.
- **A VAR_DECL array read `table[i]` expands base-first**; a `&table[i]` pointer local gives the shift first.
- **Static inline helper with field arguments** reproduces integrate.c's parameter copies (w_800597A8 5 -> 0).
