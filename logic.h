// logic.h -- May 9, 2009
//    by geohot
// part of "The Embedded Disassembler"
//  released under GPLv3,

#ifndef EDA_LOGIC_H_
#define EDA_LOGIC_H_

#include "data_memory.h"

namespace eda {

class MemoryManager {

};

// This is an abstract class to be extended by the different arches
// If I thought this through right, no other class needs to be
// This also kills the ARM/Thumb problem
// EDA plugins are extensions to this
class InstructionFactory {
public:
  // Sets up the addresses of the registers
  virtual void InitRegisters(Memory *m) = 0;

  // Parses an instruction
  // instruction should be null when passed in
  // Returns the address after the end of this instruction
  virtual Address* Process(Address* start) = 0;

  virtual void StateToXML(std::ostringstream& out) = 0;

  // This is the instruction that is currently running
  uint32_t GetProgramCounter() {
    uint32_t ret;
    program_counter_->get32(0, &ret);
    return TranslateProgramCounter(ret);
  }

  uint32_t GetStackPointer() {
    uint32_t ret;
    stack_pointer_->get32(0, &ret);
    return ret;
  }

  // This is extended for different archs to get the real program counter
  virtual uint32_t TranslateProgramCounter(uint32_t in) {
    return in;
  }

  Address* program_counter_;
  Address* link_register_;
  Address* stack_pointer_;
  vector<pair<std::string, Address*> > registers_;
private:

};

// This creates changelists
// Currently, theres two ways
class ChangelistFactory {
// out should be null when passed in to all
public:
  ChangelistFactory();
  // Used for loading from files or straight web data
  Changelist* CreateFromInput(Address* owner, const string& data, Address* start);
  // Used by the Core
  Changelist* CreateFromStatelessChangelist(Address* owner, StatelessChangelist& in,
                                     Memory* state);
  inline int get_current_changelist_number() {
    return current_changelist_number_;
  }
private:
  // This is incremented every time a changelist is created
  // It starts out at zero
  int current_changelist_number_;
};

class Core {

};

}

#endif

