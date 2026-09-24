from pathlib import Path
import sys,json
HERE=Path(__file__).resolve().parent
sys.path.insert(0,str(HERE.parent))
import probe as P
local=HERE/'c8_registered';local.mkdir(exist_ok=True)
if not (local/'include').exists():(local/'include').symlink_to(HERE/'include')
P.HERE=local
stem='w_8003F5D4'
P.RECIPES['src/'+stem+'.c']={'src':'src/'+stem+'.c','out':'build/src/'+stem+'.o','ccver':'2.7.2','ccflags':'','asflags':''}
module=json.loads((HERE/'module.json').read_text())
module['data']=[{'symbol':'D_800814C8','asset':'assets/54240.bin','offset':0xA88,'size':4,'vram':0x800814C8,'bytes':'00000000','section':'.sdata.D_800814C8'}]
module['data_pieces']=[{'symbol':'D_800814C8','source_section':'.sdata','alignment':4}]
legs,report=P.compile_legs(stem,HERE/'c8_accessors.c','candidate')
views={k:P.A.data_piece_view(v.obj,module) for k,v in legs.items()}
out=local/'objects'/stem/'candidate'
report['projected_retail']={k:{f:P.B.retail_detail(v,f,P.EXTENTS[f],out,'projected_'+k,P.ALIGN) for f in report['functions']} for k,v in views.items()}
report['projected_generic_vs_genuine']=P.B.compare(views['generic'],views['genuine'],report['functions'])
(HERE/'c8_registered_receipt.json').write_text(json.dumps(report,indent=2)+'\n')
print({k:{f:(r['actual_words'],r['exact_unmasked']) for f,r in v.items()} for k,v in report['projected_retail'].items()})
