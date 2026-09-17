Working paths refer to `work/native_lane/r42_pair/`.

# Round 42 Pair24 object-identity follow-up

## Scope and starting evidence

I am applying the `az-c-rebuild` diagnostic workflow to `town/func_800AB37C` / `func_800A8ADC`. The current base SHA-256 is `8a20ccbd54212b560f465add7c004a2f82b66d3b458b009ee8c923ca566ad5e6`; its recorded `2.7.2` control is exact at 47/47 words. The clean-tree copy does not contain `tools/lineage_fingerprint.py`, so `evidence/lineage_fingerprint.txt` records that unavailable diagnostic rather than substituting a config sweep.

The preserved retail map remains the specification: a 72-byte frame; input position held in `$s0`; a 24-byte global copied to stack offsets 16..36; raised position at offsets 40..48; then the two output helpers. Retail words 0..17 form the unresolved prefix. The address is built as page `$v0 = 0x80090000`, followed after the `$ra` save by source `$a2 = $v0 - 0x6ed8`. Words 18..46 already match the ordinary whole-Pair reconstruction.

## Object identity audit before reconstruction

The true runtime/file mapping follows from true symbol `0x800A8ADC` at row file offset `0x2b37c`, giving image base `0x8007d760`. Runtime `0x80089128` therefore maps to TOWN file offset `0xb9c8`. The retail bytes there are six little-endian words:

```
00000020 00000000 00000000 00000000 00000000 00000000
```

The preceding object is `D_80089110`, a six-entry jump table occupying exactly `0x18` bytes and ending at `0x80089128`. The following object is `D_80089140`, beginning exactly `0x18` bytes later. Thus `D_80089128` has a definite, independently bounded 24-byte extent. Its contents and consumer support two three-word vectors, with the first vector initialized to `{ 32, 0, 0 }` and the second to zero.

A word scan of the complete `town_scene` range (`0..0x52000`) for recognized direct MIPS address immediates `0x9128`/`0x6ed8` finds one address formation only, at file offset `0x2b390` inside this function. This rules out another direct reference of that form in the scanned image. Indirect/table access and an original translation-unit definition remain open, so the scan does not prove that every possible shared-page relationship is absent.

The remaining plausible identity fact is qualification and array shape. The object sits among static jump tables/string data, is only read, is exactly two vectors, and has no mutable user. Three bounded reconstructions will test: a const `Pair`, a const two-element `Vec3` array copied as one block, and a const six-word array copied as one block. Each retains the verified one-argument `func_800374F4` contract and contains no pins, fake uses, volatile access, pointer narrowing, or page literal.

## Results

All three candidates compile to the same 47-word body and the same aligned residue: 13 substitutions, 2 indels, global total 15, class `addressing`. Each matches retail exactly from word 18 through return.

1. `scratch/const_pair.c` declares `extern const Pair D_80089128` and uses one whole-Pair assignment. Const qualification does not alter RTL lowering or allocation.
2. `scratch/const_vec_array.c` declares the bounded object as `const Vec3[2]`, models the local as the same two-vector array, and copies it in one 24-byte `memcpy`. Array decay and the known two-element extent still lower to the same direct symbolic BLK source.
3. `scratch/const_word_array.c` declares the bounded object as `const s32[6]` and copies those six words into the local Pair in one block. Scalar element identity likewise produces the same output.

The three diffs are retained in `evidence/const_pair.diff`, `evidence/const_vec_array.diff`, and `evidence/const_word_array.diff`. No candidate was placed in `out/`.

## Causal conclusion and semantic review

The object audit recovered the identity facts that were previously missing, but they do not explain retail's address lifetime:

- `D_80089128` is one isolated, immutable-in-practice 24-byte template; it is not a field of a larger object used by this function.
- It has no other recognized direct address use in the complete scene range. The scan does not exclude indirect/table use or source-level relationships from the original translation unit.
- Const, `Pair`, `Vec3[2]`, and `s32[6]` source identities all become the same direct `mem:BLK(symbol_ref D_80089128)` at this compilation boundary. They therefore inherit the single source address colored `$a1`, rather than pinned retail page pseudo 74 in `$v0` and derived source pseudo 75 in `$a2`.

The helper implementations strengthen the type interpretation without changing that result. `func_800A895C` and `func_80097AD0` consume signed/unsigned spread values at offsets `0`, `4`, and `8`; the first three words `{32,0,0}` are exactly their spread record. Retail nonetheless copies the full symbol-bounded 24 bytes and passes the same local base to both helpers. The second zero vector is therefore part of the real template extent even though the currently reconstructed helper fields do not read it. Both random-count calls genuinely take only the limit `2`; no extra source/template arguments are semantically available to extend the source lifetime.

The remaining source fact is likely outside an extern-only one-function declaration: the original translation unit may have contained the static template definition, allowing old GCC to see different linkage/definition context when expanding its address. This is a tracked hypothesis, not a conclusion. Testing it requires evidence for the original TU/data definition and a way to model that context without emitting duplicate data or adding address scaffolding. More extern type spellings are refuted by the byte-identical results above.

Result: bounded unresolved. The round-42 success criterion was not met, and the recovered real object model still yields one source pseudo. This is not an impossibility or floor claim.
