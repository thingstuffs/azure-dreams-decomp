# Independent review

## Verdict

The captured run supports the proposed reload-CSE transition for this exact compiler and input. In RTL chain order, UID 350 records `CONST_INT 0` for hard register 19 (`$s3`) in SI mode; UID 362 later sees that same SI cache entry while considering an SI write of zero to register 17. The intervening chain is explicit rather than inferred from UID numbering. After note 364, `CODE_LABEL` UID 365, and note 367, the UID 368 snapshot has an empty register-19 cache. The compiler implementation at the label path clears the cache heads, so the loss at UID 368 has a direct control-flow explanation.

The halfword experiment gives the complementary observation. Its relevant event is UID 367 (UIDs are compilation-local and should not be equated with UID 362 in the original input): register 19 holds the same zero value in a mode-2/HI cache entry, while the destination and comparator request are mode-4/SI. The comparator rejects register 19 along with every other tested register and the source remains `CONST_INT 0`. Paired with the SI run, this isolates the HI/SI cache-mode difference as the changed discriminator in these executions.

This is evidence for the compiler mechanism, not evidence that `grid_y` should semantically be `u16` in C. Both C-shape probes remain nonexact: the bound halfword form is 229/224 words with 17 edits, and the unbound form is 237/224 words with 64 edits. The trace therefore does not establish a source repair or an impossibility result.

## Trace and non-perturbation checks

- The main trace hooks the real entries for `reload_cse_regs`, `reload_cse_noop_set_p`, and `reload_cse_record_set`. Its event sequence records an empty cache immediately before UID 350, the mode-4 zero entry immediately after UID 350, persistence at UID 362, and an empty cache at UID 368.
- The halfword trace hooks the real entries for `reload_cse_simplify_set` and `reload_cse_regno_equal_p`. At its UID 367, the saved register-19 entry is mode 2 while the comparison requests mode 4; the returned comparison for register 19 is false and the source is unchanged afterward.
- Both `result.json` files name compiler SHA-256 `90db2db7bcfe372244ca4d9785a7bfbf7613d711f69ee3bfe6c91d82a85e611d`, which matches the compiler binary inspected for these hooks.
- `assembly_equal` is true for both runs. The normalized assembly streams contain 221 items in the main run and 226 in the halfword run and compare equal. A raw comparison shows only reordered command-line options in an emitted comment (`-G0 -O2 -w` versus `-O2 -G0 -w`), with no instruction or data difference.
- The scripts do not assign inferior registers, call inferior functions, or write inferior memory. They read registers/memory, install breakpoints, and write host-side JSON. GDB software and finish breakpoints can transiently patch inferior text as part of breakpoint operation, so “read-only” here means that the instrumentation performs no intentional compiler-state/RTL writes; it is not a claim that debugging has no runtime perturbation at all.

## Limits

The scripts are tied to this 32-bit compiler build: addresses, calling convention, RTL field offsets, mode numbers, and cache globals are hard-coded. The main cache sampler covers only registers 0, 17, and 19 and caps each linked-list walk at 12 nodes. Pattern-address-to-UID mapping assumes addresses remain unique for the sampled chain, and the scripts do not validate call-frame ancestry. The main checkpoints are snapshots before `reload_cse_noop_set_p`; the current main trace alone does not re-record every comparator decision. The halfword run establishes the observed rejection but does not prove a general rule for all modes or all source programs.

## Bound artifacts

| Artifact | SHA-256 |
|---|---|
| `trace.py` | `d25122c9e2fd2c8131d60e5d386dc0eb13355a643cd45a875cc33d660e10390d` |
| `run.py` | `a32226329c326fe86216ab4d2646a94b221cb806025a708b587c4588a0f38575` |
| `result.json` | `ce0bf5bff8bb4f008a55d3e52bde1d73a571c8dadd3ae7aed47f4c902685bb81` |
| `trace.json` | `1889c5a457806232c811afaa2611c82d0fb293e29e836ecfa18ce972685f363a` |
| `halfword/trace.py` | `cb33efdf5e2a66ac9cdda8b176c62c8f9cb4dbaa3fee63a3335f2761a4c020e` |
| `halfword/run.py` | `d3ac558a9f7b9b837fab3e6fdffd1b2ed933addee79f83a0d9711050a77bf75c` |
| `halfword/result.json` | `81011a11887408c1e45de021724f54e0c4178cc46dbfeb365dca31be66cf735f` |
| `halfword/trace.json` | `2bedd966f8751688f4a2e4936ab18ed179fd4da8b5b09219c39c902b649a6f98` |
| `v1_row_halfword.summary.json` | `acb05dd2da1367b32c3f80030c654efba756d51f3a4dc89fa88165b7ffa324a9` |
| `v2_row_halfword_unbound.summary.json` | `d0ffcb07e656b878a9d98c21af91c22fe997e9aba99f5aa98bb9681937fb7948` |
