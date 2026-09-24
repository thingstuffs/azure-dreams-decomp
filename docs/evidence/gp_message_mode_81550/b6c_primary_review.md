# B6C script-view review after the initial audit

The initial `b6c_evidence.md` correctly rejected the assumption that the callback
chain is an ordinary NUL-string consumer. Following that chain one step further
resolves the used data format: this is a two-byte script view, not a claim about
the original allocation size, storage class or constness.

1. `D_800714A4` selects 35208/35234/35260. Each invokes35164, then34F88 stores
   the supplied script address in the runtime's pending field +34 and saved
   field +38.
2. `konami_runtime_w_8003800C.c` consumes owner->field34, installs it as the
   embedded context's field1C cursor, clears the pending field and chooses
   dispatcher38A10. This is the missing link in the first bounded audit.
3. `konami_runtime_w_80038A10.c` calls38AB8, whose cursor is a signed-byte
   stream. The byte0x23 is positive, so38AB8 reads it as an opcode, increments
   cursor once, and invokes `D_8006AA90[0x23]`.
4. The actual retail table word at8006AB1C is80039B84. Its C and retail body
   set context->action=80038A08 without consuming any operands. The function
   at80038A08 is an eight-byte jr-ra/nop no-op (canonical C in
   `src/slus/konami_runtime.c`).
5. Returning to38AB8, the dispatcher reads the next cursor byte, which is zero
   atB6D. It does not re-enter dispatch. The action is not39AE8, so the branch
   that advances the cursor again is skipped.38A10's loop terminates because
   the action changed; the installed no-op consumes no more bytes.

Thus the entry is an opcode followed by the dispatcher's sentinel lookahead:
bytes23,00. These two bytes are sufficient for this command path independently
of whether the following two zeros were alignment padding or extra allocation.
The next named datumB70 is not included in this view. `extern char B6C[2]` is a
present typed view of that complete script, not recovered historical sizeof.
No B6C storage is claimed by the module. Keep it mutable: constness is not needed
or established. The four-byte zeroed scalar definitions at8154C and81550 are
separate ownership claims and independently receive section/address/link proof.

The measured distinction is source declaration emission, not a missing compiler:
[16] and incomplete[] emit a CDK split address, whose low half fills jalr's slot.
The two-byte script view emits a bare la pseudo-op that expands to the retail
absolute address pair and leaves the call's slot empty. Default CDK then gives
the complete sixteen-word DCEC body, including the retail v0/v1 roles. The old
-fno-schedule-insns/-fno-delayed-branch settings are no longer required for this
reviewed view. No function body or compiler/assembler pin is introduced.

This resolves the candidate's used-extent question, superseding the initial
receipt's conservative unresolved-declaration note. It does not authorize a
production assembler switch: stock still shortens DF8C's local8154C address to
one GP instruction. The existing private generic correction must pass its global
transition gates and owner signoff before this grouped candidate can land.
