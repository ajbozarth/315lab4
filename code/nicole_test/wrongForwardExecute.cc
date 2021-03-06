#include "mipsim.hpp"
#include <stdio.h>

Stats stats;
Caches caches(0);

void checkForwardMem(Data32 i);

unsigned int signExtend16to32ui(short i) {
   return static_cast<unsigned int>(static_cast<int>(i));
}

unsigned int zeroExtend16to32ui(unsigned short i) {
   return static_cast<unsigned int>(i);
}

unsigned int signExtend8to32ui(unsigned int i) {
   return static_cast<unsigned int>(static_cast<int>(static_cast<char>(i)));
}

// stall check function
// basically if there is a LW or LB to a register and the next instruction needs to load from
// that register, then a stall needs to happen.
void checkForwardEx(Data32 i) {
   // Checks 2 instructions later
   Data32 pcInstr = imem[pc];
   GenericType rp(pcInstr);
   RType pcrt(pcInstr);
   IType pcit(pcInstr);
   Type pciType = Data32::classifyType(pcInstr);
   
   Data32 nextInstr = imem[pc + 4];
   GenericType rg(nextInstr);
   RType rt(nextInstr);
   IType ri(nextInstr);
   Type iType = Data32::classifyType(nextInstr);
   switch(pciType) {
      case R_TYPE:
         if(pcrt.rt == i || pcrt.rs == i || pcrt.rd == i) {
            if(iType == R_TYPE && (rt.rt == i || rt.rs == i)) {
               stats.numExForwards++;
            }
            else if(iType == I_TYPE && (ri.rt == i || rt.rs == i)) {
               stats.numExForwards++;
            }
            else if (pcrt.rt == i || pcrt.rs == i) {
               stats.numMemForwards++;
            }
         }
         break;
      case I_TYPE:
         if(pcit.rt == i || pcit.rs == i || pcrt.rd == i) {
            if(iType == R_TYPE && (rt.rt == i || rt.rs == i)) {
               stats.numExForwards++;
            }   
            else if(iType == I_TYPE && (ri.rt == i || rt.rs == i)) {
               stats.numExForwards++;
            }   
            else if(pcrt.rt == i || pcrt.rs == i) {
               stats.numMemForwards++;
            }  
         }   
         break;
      default:
         break;
   }
}

void execute() {
   Data32 instr = imem[pc];
   Data32 memVal = imem[pc]; // init with junk val
   GenericType rg(instr);
   RType rt(instr);
   IType ri(instr);
   JType rj(instr);
   unsigned int pctarget = pc + 4;
   unsigned int addr;
   stats.instrs++;
   stats.cycles++; // my added for testing
   pc = pctarget;
   switch(rg.op) {
      case OP_SPECIAL:
         switch(rg.func) {
            case SP_ADDU:
               rf.write(rt.rd, rf[rt.rs] + rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_SLL:
               // noop check.
               if(instr.data_uint() == 0) {
                  stats.instrs--;
                  stats.numRType--;
               }
               rf.write(rt.rd, rf[rt.rt] << rt.sa);
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_SLT:
               // checking casting as int in case it's a sign issue
               rf.write(rt.rd, rf[rt.rs] < rf[rt.rt] ? 1 : 0);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_JR:
               // For jump delay slot checks.
               imem[pc].data_uint() == 0 ? stats.hasUselessJumpDelaySlot++
                                         : stats.hasUsefulJumpDelaySlot++;

               pc.write(rf[rt.rs]);
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
               break;
            case SP_SRL:
               rf.write(rt.rd, rf[rt.rt].data_uint() >> rt.sa);
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_SRA:
               rf.write(rt.rd, rf[rt.rt].data_int() >> rt.sa);
               stats.numRType++;
               stats.numRegReads++;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_ADD:
               rf.write(rt.rd, rf[rt.rs] + rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_SUB:
               rf.write(rt.rd, rf[rt.rs] - rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_SUBU:
               rf.write(rt.rd, rf[rt.rs] - rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_AND:
               rf.write(rt.rd, rf[rt.rs] & rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_OR:
               rf.write(rt.rd, rf[rt.rs] | rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_XOR:
               rf.write(rt.rd, rf[rt.rs] ^ rf[rt.rt]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_NOR:
               rf.write(rt.rd, !(rf[rt.rs] | rf[rt.rt]));
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites++;
               checkForwardEx(rt.rd);
               break;
            case SP_JALR:
               //Jump delay slot
               imem[pc].data_uint() == 0 ? stats.hasUselessJumpDelaySlot++
                                         : stats.hasUsefulJumpDelaySlot++;

               rf.write(rt.rd, pc + 4);
               pc.write(rf[rt.rs]);
               stats.numRType++;
               stats.numRegReads += 2;
               stats.numRegWrites += 2;
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
         checkForwardEx(ri.rt);
         break;
   // Our modifications start here
      case OP_ORI:
         rf.write(ri.rt, rf[ri.rs] | zeroExtend16to32ui(ri.imm));
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         checkForwardEx(ri.rt);
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
         checkForwardEx(ri.rt);
         break;
      case OP_LBU:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         rf.write(ri.rt, dmem[addr].data_ubyte4(0));
         stats.numIType++;
         stats.numMemReads++;
         stats.numRegReads++;
         stats.numRegWrites++;
         if(imem[pc].data_uint() == 0) {
            stats.loadHasLoadUseStall++;
         }
         stats.loadHasNoLoadUseHazard++;
         checkForwardEx(ri.rt);
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
         checkForwardEx(ri.rt);
         break;
      case OP_SLTI:
         rf.write(ri.rt, (rf[ri.rs] < signExtend16to32ui(ri.imm)) ? 1 : 0);
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         checkForwardEx(ri.rt);
         break;
      case OP_SLTIU:
         rf.write(ri.rt, (rf[ri.rs] < zeroExtend16to32ui(ri.imm)) ? 1 : 0);
         stats.numIType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         checkForwardEx(ri.rt);
         break;
      case OP_BNE:
         // Branch delay slot check
         imem[pc].data_uint() == 0 ? stats.hasUselessBranchDelaySlot++
                                   : stats.hasUsefulBranchDelaySlot++;

         if (rf[ri.rs] != rf[ri.rt]) {
            (pc < (pc + (ri.imm << 2))) ? stats.numForwardBranchesTaken++
                                        : stats.numBackwardBranchesTaken++;
            pc.write(pc + (signExtend16to32ui(ri.imm) << 2));
            stats.numRegReads++;
            stats.numRegWrites++;
         }
         else {
            (pc < (pc + (ri.imm << 2))) ? stats.numForwardBranchesNotTaken++
                                        : stats.numBackwardBranchesNotTaken++;
         }
         stats.numIType++;
         stats.numRegReads += 2;
         checkForwardEx(ri.rt);
         break;
      case OP_BEQ:
         // Branch delay slot check
         imem[pc].data_uint() == 0 ? stats.hasUselessBranchDelaySlot++
                                   : stats.hasUsefulBranchDelaySlot++;
         
         if (rf[ri.rs] == rf[ri.rt]) {
            (pc < (pc + (ri.imm << 2))) ? stats.numForwardBranchesTaken++
                                        : stats.numBackwardBranchesTaken++;
            pc.write(pc + (signExtend16to32ui(ri.imm) << 2));
            stats.numRegReads++;
            stats.numRegWrites++;
         }
         else {
            (pc < (pc + (ri.imm << 2))) ? stats.numForwardBranchesNotTaken++
                                        : stats.numBackwardBranchesNotTaken++;
         }
         stats.numIType++;
         stats.numRegReads += 2;
         checkForwardEx(ri.rt);
         break;
      case OP_BLEZ:
         // Branch delay slot check
         imem[pc].data_uint() == 0 ? stats.hasUselessBranchDelaySlot++
                                   : stats.hasUsefulBranchDelaySlot++;
         
         if (rf[ri.rs] <= 0) {
            (pc < (pc + (ri.imm << 2))) ? stats.numForwardBranchesTaken++
                                        : stats.numBackwardBranchesTaken++;
            pc.write(pc + (signExtend16to32ui(ri.imm) << 2));
            stats.numRegReads++;
            stats.numRegWrites++;
         }
         else {
            (pc < (pc + (ri.imm << 2))) ? stats.numForwardBranchesNotTaken++
                                        : stats.numBackwardBranchesNotTaken++;
         }
         stats.numIType++;
         stats.numRegReads++;
         checkForwardEx(ri.rt);
         break;
      case OP_LUI:
         rf.write(ri.rt, (ri.imm << 16));
         stats.numIType++;
         stats.numRegWrites++;
         checkForwardEx(ri.rt);
         break;
      case OP_JAL:
         // Jump delay slot check
         imem[pc].data_uint() == 0 ? stats.hasUselessJumpDelaySlot++
                                   : stats.hasUsefulJumpDelaySlot++;

         rf.write(31, pc + 4);
         pc.write((pc & 0xf0000000) | (rj.target << 2));
         stats.numJType++; 
         stats.numRegReads += 2;
         stats.numRegWrites += 2;
         break;
      case OP_J:
         // Jump delay slot check
         imem[pc].data_uint() == 0 ? stats.hasUselessJumpDelaySlot++
                                   : stats.hasUsefulJumpDelaySlot++;

         pc.write((pc & 0xf0000000) | (rj.target << 2));
         stats.numJType++;
         stats.numRegReads++;
         stats.numRegWrites++;
         break;
   // Our modifications end here
      case OP_SW:
         addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
         caches.access(addr);
         dmem.write(addr, rf[ri.rt]);
         stats.numIType++;
         stats.numMemWrites++;
         stats.numRegReads += 2; // from address calc and mem write
         checkForwardEx(ri.rt);
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
         checkForwardEx(ri.rt);
         break;
      default:
         cout << "Unsupported instruction: ";
         instr.printI(instr);
         exit(1);
         break;
   }
}
