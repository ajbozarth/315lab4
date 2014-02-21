#include "mipsim.hpp"

Stats stats;
Caches caches(0);

unsigned int signExtend16to32ui(short i) {
   return static_cast<unsigned int>(static_cast<int>(i));
}

void execute() {
   Data32 instr = imem[pc];
   GenericType rg(instr);
   RType rt(instr);
   IType ri(instr);
   JType rj(instr);
   unsigned int pctarget = pc + 4;
   unsigned int addr;
   stats.instrs++;
   pc = pctarget;
   switch(rg.op) {
      case OP_SPECIAL:
         switch(rg.func) {
            case SP_ADDU:
               rf.write(rt.rd, rf[rt.rs] + rf[rt.rt]);
               break;
            case SP_SLL:
               rf.write(rt.rd, rf[rt.rt] << rt.sa);
               break;
         // Our modifications start here
            // Freebie from the ppt slides:
            case SP_ADDU:
               rf.write(rt.rd, rf[rt.rs] + rf[rt.rt]);
               break;
            case SP_SLT:
               break;
            case SP_JR:
               break;
            case SP_SLL:
               break;
            case SP_SRL:
               break;
            case SP_SRA:
               break;
            case SP_ADD:
               break;
            case SP_SUB:
               break;
            case SP_SUBU:
               break;
            case SP_AND:
               break;
            case SP_OR:
               break;
            case SP_XOR:
               break;
            case SP_NOR:
               break;
            case SP_JALR:
               break;
         // Our modifications end here
            default:
               cout << "Unsupported instruction: ";
               instr.printI(instr);
               exit(1);
               break;
         }
         break;
      case OP_ADDIU:
         rf.write(ri.rt, rf[ri.rs] + signExtend16to32ui(ri.imm));
         break;
   // Our modifications start here
      case OP_ORI:
         break;
      case OP_SB:
         break;
      case OP_LW:
         break;
      case OP_LBU:
         break;
      case OP_LB:
         break;
      case OP_SLTI:
         break;
      case OP_SLTIU:
         break;
      case OP_BNE:
         break;
      case OP_BEQ:
         break;
      case OP_BLEZ:
         break;
      case OP_LUI:
         break;
      case OP_JAL:
         break;
      case OP_J:
         break;
      case OP_LUI:
         break;
   // Our modifications end here
      case OP_SW:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         dmem.write(addr, rf[ri.rt]);
         break;
      case OP_LW:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         rf.write(ri.rt, dmem[addr]);
         break;
      default:
         cout << "Unsupported instruction: ";
         instr.printI(instr);
         exit(1);
         break;
   }
}
