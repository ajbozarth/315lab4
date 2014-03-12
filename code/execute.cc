#include "mipsim.hpp"
#include <stdio.h>

Stats stats;
Caches caches(0);

static unsigned int rd1;
static unsigned int rd2;

unsigned int signExtend16to32ui(short i) {
   return static_cast<unsigned int>(static_cast<int>(i));
}

unsigned int zeroExtend16to32ui(unsigned short i) {
   return static_cast<unsigned int>(i);
}

unsigned int signExtend8to32ui(unsigned int i) {
   return static_cast<unsigned int>(static_cast<int>(static_cast<char>(i)));
}

void setForwardEx(unsigned int rg) {
   if (rg && rd1 && rg == rd1) {
      stats.numExForwards++;
   }
   if (rg && rd2 && rg == rd2) {
      stats.numMemForwards++;
   }
}

void setForwardEx(unsigned int rg1, unsigned int rg2) {
   setForwardEx(rg1);
   setForwardEx(rg2);
}

void setRd(unsigned int rd) {
   rd2 = rd1;
   rd1 = rd;
}

void execute() {
   Data32 instr = imem[pc];
   Data32 memVal = imem[pc]; // init with junk val
   GenericType rg(instr);
   RType rt(instr);
   IType ri(instr);
   JType rj(instr);
   unsigned int addr;
   unsigned int pctarget = pc + 4;
   stats.instrs++;
   stats.cycles++; // my added for testing

   static unsigned int next_pc;
   static bool isJump;
   static bool isBranch;

   if (isJump) {
      imem[pc].data_uint() == 0 ? stats.hasUselessJumpDelaySlot++
                                : stats.hasUsefulJumpDelaySlot++;
      pc = next_pc;
      isJump = false;
   } else if (isBranch) {
      pc = next_pc;
      isBranch = false;
   } else {
      pc = pctarget;
   }

   setForwardEx(instr);

   switch(rg.op) {
      case OP_SPECIAL:
         switch(rg.func) {
            case SP_ADDU:
               rf.write(rt.rd, rf[rt.rs] + rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_SLL:
               // noop check.
               if(instr.data_uint() == 0) {
                  stats.instrs--;
                  stats.numRType--;
               } else {
                  setForwardEx(rt.rt);
                  setRd(rt.rd);
               }
               rf.write(rt.rd, rf[rt.rt] << rt.sa);
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
               break;
            case SP_SLT:
               // checking casting as int in case it's a sign issue
               rf.write(rt.rd, rf[rt.rs] < rf[rt.rt] ? 1 : 0);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_JR:
               next_pc = rf[rt.rs].data_uint();
               isJump = true;
               stats.numRType++;
               stats.numRegReads++;
               setForwardEx(rt.rs);
               setRd(0);
               break;
            case SP_SRL:
               rf.write(rt.rd, rf[rt.rt].data_uint() >> rt.sa);
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
               setForwardEx(rt.rt);
               setRd(rt.rd);
               break;
            case SP_SRA:
               rf.write(rt.rd, rf[rt.rt].data_int() >> rt.sa);
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
               setForwardEx(rt.rt);
               setRd(rt.rd);
               break;
            case SP_ADD:
               rf.write(rt.rd, rf[rt.rs] + rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_SUB:
               rf.write(rt.rd, rf[rt.rs] - rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_SUBU:
               rf.write(rt.rd, rf[rt.rs] - rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_AND:
               rf.write(rt.rd, rf[rt.rs] & rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_OR:
               rf.write(rt.rd, rf[rt.rs] | rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_XOR:
               rf.write(rt.rd, rf[rt.rs] ^ rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_NOR:
               rf.write(rt.rd, !(rf[rt.rs] | rf[rt.rt]));
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               setForwardEx(rt.rs, rt.rt);
               setRd(rt.rd);
               break;
            case SP_JALR:
               rf.write(rt.rd, pc + 4);
               next_pc = rf[rt.rs].data_uint();
               isJump = true;
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
               setForwardEx(rt.rs);
               setRd(rt.rd);
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
         setForwardEx(rt.rs);
         setRd(rt.rt);
         break;
   // Our modifications start here
      case OP_ORI:
         rf.write(ri.rt, rf[ri.rs] | zeroExtend16to32ui(ri.imm));
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         setForwardEx(rt.rs);
         setRd(rt.rt);
         break;
      case OP_SB:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         memVal = dmem[addr];
         memVal.set_data_ubyte4(0, rf[ri.rt].data_ubyte4(3));
         dmem.write(addr, memVal);
         stats.numIType++;
         stats.numMemWrites++;
         stats.numRegReads += 2; // from the OP_SB loading and address calc
         setForwardEx(rt.rs, rt.rt);
         setRd(0);
        break;
      case OP_LBU:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         rf.write(ri.rt, (unsigned int)(dmem[addr].data_ubyte4(0)));
         stats.numIType++;
         stats.numMemReads++;
         stats.numRegReads++;
         stats.numRegWrites++;
         if(imem[pc].data_uint() == 0) {
            stats.loadHasLoadUseStall++;
         }
         stats.loadHasNoLoadUseHazard++;
         setForwardEx(rt.rs);
         setRd(ri.rt);
         break;
      case OP_LB:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         rf.write(ri.rt, signExtend8to32ui(dmem[addr].data_ubyte4(0)));
         stats.numIType++;
         stats.numMemReads++;
         stats.numRegReads++;
         stats.numRegWrites++;
         if(imem[pc].data_uint() == 0) {
            stats.loadHasLoadUseStall++;
         }
         stats.loadHasNoLoadUseHazard++;
         setForwardEx(rt.rs);
         setRd(ri.rt);
         break;
      case OP_SLTI:
         rf.write(ri.rt, (rf[ri.rs] < signExtend16to32ui(ri.imm)) ? 1 : 0);
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         setForwardEx(rt.rs);
         setRd(rt.rt);
         break;
      case OP_SLTIU:
         rf.write(ri.rt, (rf[ri.rs] < zeroExtend16to32ui(ri.imm)) ? 1 : 0);
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         setForwardEx(rt.rs);
         setRd(rt.rt);
         break;
      case OP_BNE:
         next_pc = pc + (signExtend16to32ui(ri.imm) << 2);
         imem[pc].data_uint() == 0 ? stats.hasUselessBranchDelaySlot++
                                   : stats.hasUsefulBranchDelaySlot++;
         if (rf[ri.rs] != rf[ri.rt]) {
            (pc < next_pc) ? stats.numForwardBranchesTaken++
                           : stats.numBackwardBranchesTaken++;
            isBranch = true;
         }
         else {
            (pc < next_pc) ? stats.numForwardBranchesNotTaken++
                           : stats.numBackwardBranchesNotTaken++;
         }
         stats.numIType++;
         stats.numRegReads += 2;
         setForwardEx(rt.rs, rt.rt);
         setRd(0);
         break;
      case OP_BEQ:
         next_pc = pc + (signExtend16to32ui(ri.imm) << 2);
         imem[pc].data_uint() == 0 ? stats.hasUselessBranchDelaySlot++
                                   : stats.hasUsefulBranchDelaySlot++;
         if (rf[ri.rs] == rf[ri.rt]) {
            (pc < next_pc) ? stats.numForwardBranchesTaken++
                           : stats.numBackwardBranchesTaken++;
            isBranch = true;
         }
         else {
            (pc < next_pc) ? stats.numForwardBranchesNotTaken++
                           : stats.numBackwardBranchesNotTaken++;
         }
         stats.numIType++;
         stats.numRegReads += 2;
         setForwardEx(rt.rs, rt.rt);
         setRd(0);
         break;
      case OP_BLEZ:
         next_pc = pc + (signExtend16to32ui(ri.imm) << 2);
         imem[pc].data_uint() == 0 ? stats.hasUselessBranchDelaySlot++
                                   : stats.hasUsefulBranchDelaySlot++;
         if (rf[ri.rs] <= 0) {
            (pc < next_pc) ? stats.numForwardBranchesTaken++
                           : stats.numBackwardBranchesTaken++;
            isBranch = true;
         }
         else {
            (pc < next_pc) ? stats.numForwardBranchesNotTaken++
                           : stats.numBackwardBranchesNotTaken++;
         }
         stats.numIType++;
         stats.numRegReads += 2;
         setForwardEx(rt.rs);
         setRd(0);
         break;
      case OP_LUI:
         rf.write(ri.rt, (ri.imm << 16));
         stats.numIType++;
         stats.numRegWrites++;
         setRd(ri.rt);
         break;
      case OP_JAL:
         rf.write(31, pc + 4);
         next_pc = (pc & 0xf0000000) | (rj.target << 2);
         isJump = true;
         stats.numJType++; 
         stats.numRegWrites++;
         setRd(31);
         break;
      case OP_J:
         next_pc = (pc & 0xf0000000) | (rj.target << 2);
         isJump = true;
         stats.numJType++;
         setRd(0);
         break;
   // Our modifications end here
      case OP_SW:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         dmem.write(addr, rf[ri.rt]);
         stats.numIType++;
         stats.numMemWrites++;
         stats.numRegReads += 2; // from address calc and mem write
         setForwardEx(rt.rs, ri.rt);
         setRd(0);
         break;
      case OP_LW:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         rf.write(ri.rt, dmem[addr]);
         stats.numIType++;
         stats.numMemReads++;
         stats.numRegReads++;
         stats.numRegWrites++;
         if(imem[pc].data_uint() == 0) {
            stats.loadHasLoadUseStall++;
         }
         stats.loadHasNoLoadUseHazard++;
         setForwardEx(rt.rs);
         setRd(ri.rt);
         break;
      default:
         cout << "Unsupported instruction: ";
         instr.printI(instr);
         exit(1);
         break;
   }
}
