# r121 particle fade depth (bounded measurement)

At fixed2.7.2-cdk-G0, TOWN file0x8D6FA8 (true0x80023FA8), the full120-byte
callback matches with a u16 depth temporary assigned (u16)(packet->depth+0x120),
then a separate depth-=packet->colour/8. One combined addition/subtraction
expression produces7 substitutions and no indels: gcc instead adds-0x120 to
the subtrahend and changes the register roles. The separate typed operations
are ordinary C and match the retail load/add/sub/store sequence exactly.
Full ELF extent and all covering production windows are independently checked.
This measurement does not assert a general compiler version signature.
