#include "mipsim.hpp"

Stats stats;
Caches caches(0);

unsigned int signExtend16to32ui(short i) {
   return static_cast<unsigned int>(static_cast<int>(i));
}

unsigned int zeroExtend16to32ui(unsigned short i) {
   return static_cast<unsigned int>(i);
}

unsigned int signExtend8to32ui(unsigned int i) {
   return static_cast<unsigned int>(static_cast<int>(static_cast<char>(i)));
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
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_SLL:
               rf.write(rt.rd, rf[rt.rt] << rt.sa);
               stats.numRType++;
               stats.numRegReads++; //double check, rt.sa shouldn't be a reg read
               stats.numRegWrites++;
               break;
         // Our modifications start here
            // Freebie from the ppt slides:
            case SP_SLT:
               rf.write(rt.rd, (rf[rt.rs] < rf[rt.rt]) ? 1 : 0);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_JR:
               pc.write(rf[rt.rs]);
               stats.numRType++;
               stats.numRegReads++;
               break;
            case SP_SRL:
               rf.write(rt.rd, rf[rt.rt].data_int() >> rt.sa);
               stats.numRType++;
               stats.numRegReads++; //double check, rt.sa shouldn't be a reg read
               stats.numRegWrites++;
               break;
            case SP_SRA:
               rf.write(rt.rd, rf[rt.rt].data_uint() >> rt.sa);
               stats.numRType++;
               stats.numRegReads++; //double check, rt.sa shouldn't be a reg read
               stats.numRegWrites++;
               break;
            case SP_ADD:
               rf.write(rt.rd, rf[rt.rs] + rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_SUB:
               rf.write(rt.rd, rf[rt.rs] - rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_SUBU:
               rf.write(rt.rd, rf[rt.rs] - rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_AND:
               rf.write(rt.rd, rf[rt.rs] & rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_OR:
               rf.write(rt.rd, rf[rt.rs] | rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_XOR:
               rf.write(rt.rd, rf[rt.rs] ^ rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_NOR:
               rf.write(rt.rd, !(rf[rt.rs] | rf[rt.rt]));
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               break;
            case SP_JALR:
               rf.write(rt.rd, pc + 4);
               pc.write(rf[rt.rs]);
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
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
         stats.numIType++; 
         stats.numRegReads++;
         stats.numRegWrites++;
         break;
   // Our modifications start here
      case OP_ORI:
         rf.write(ri.rt, rf[ri.rs] | zeroExtend16to32ui(ri.imm));
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         break;
      case OP_SB:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         dmem.write(addr, (0x000000FF & rf[ri.rt]) << 24);
         stats.numIType++;
         stats.numMemWrites++;
         stats.numRegReads += 2; // from the OP_SB loading and address calc
         break;
      case OP_LBU:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         rf.write(ri.rt, dmem[addr] >> 24);
         stats.numIType++;
         stats.numMemReads++;
         stats.numRegReads++; // from address calc
         stats.numRegWrites++;
         break;
      case OP_LB:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         rf.write(ri.rt, signExtend8to32ui(dmem[addr] >> 24));
         stats.numIType++;
         stats.numMemReads++;
         stats.numRegReads++; // from address calc
         stats.numRegWrites++;
         break;
      case OP_SLTI:
         rf.write(ri.rt, (rf[ri.rs] < signExtend16to32ui(ri.imm)) ? 1 : 0);
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         break;
      case OP_SLTIU:
         rf.write(ri.rt, (rf[ri.rs] < zeroExtend16to32ui(ri.imm)) ? 1 : 0);
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         break;
      case OP_BNE:
         if (rf[ri.rs] != rf[ri.rt]) {
            pc = pc + (ri.imm << 2);
         }
         stats.numIType++;
         stats.numRegReads += 2;
         break;
      case OP_BEQ:
         if (rf[ri.rs] == rf[ri.rt]) {
            pc = pc + (ri.imm << 2);
         }
         stats.numIType++;
         stats.numRegReads += 2;
         break;
      case OP_BLEZ:
         if (rf[ri.rs] <= 0) {
            pc = pc + (ri.imm << 2);
         }
         stats.numRegReads++;
         stats.numIType++;
         break;
      case OP_LUI:
         rf.write(ri.rt, (ri.imm << 16));
         stats.numIType++;
         stats.numRegWrites++;
         break;
      case OP_JAL:
         rf.write(31, pc + 4);
         pc.write((pc & 0xf0000000) | (rj.target << 2));
         stats.numJType++; 
         stats.numRegReads++;
         stats.numRegWrites++;
         break;
      case OP_J:
         pc.write((pc & 0xf0000000) | (rj.target << 2));
         stats.numJType++;
         stats.numRegReads++;
         break;
   // Our modifications end here
      case OP_SW:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         dmem.write(addr, rf[ri.rt]);
         stats.numIType++;
         stats.numMemWrites++;
         stats.numRegReads += 2; // from address calc and mem write
         break;
      case OP_LW:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         rf.write(ri.rt, dmem[addr]);
         stats.numIType++;
         stats.numMemReads++;
         stats.numRegReads++;
         stats.numRegWrites++;
         break;
      default:
         cout << "Unsupported instruction: ";
         instr.printI(instr);
         exit(1);
         break;
   }
}
