#include <iostream>
using namespace std;

class BaseRegister{
    private:
      signed char value; // 1 Byte， -128 to 127

    public:
      BaseRegister()  
      {
         value = 0; // initialize  value to 0 when register created
      }

      signed char getValue() // return current value stored in register
      {
          return value;
      }

      void setValue(signed char v)  // store new value into register
      {
          value = v;
      }
};

class FlagRegister{
    private :
      bool OF ;  // Overflow 
      bool UF ;  // Underflow 
      bool ZF ;  // Zero
      bool CF ;  // Carry

    public:
      FlagRegister()
      {
        OF = UF = ZF = CF = false; // start all flags to false
      }

      void update(int v) // check result and update flag 
      {
        OF = (v > 127);
        UF = (v < -128);
        ZF = (v == 0);
        CF = (v > 127 || v < -128);

          if (OF)
           {      
            cout << "Overflow Flag Activated" << endl;
           }
          
          if (UF)
           {      
            cout << "Underflow Flag Activated" << endl;
           }
         if (ZF)
           {      
            cout << "Zero Flag Activated" << endl;
           }

         if (CF)
           {      
            cout << "Carry Flag Activated" << endl;
           }
      }

      void reset()
      {
        OF = false;
        UF = false;
        ZF = false;
        CF = false;
      }
};



class CPU
{
  private:
    BaseRegister R[8]; // R0-R7, R=register
    FlagRegister flags; // CPU flags

  public:
    signed char getRegister(int i) // get value from  selected register
    {
       return R[i].getValue();
    }

    void setRegister(int i, int result) // store result into selected register
    {
        flags.update(result); // check if the result was OF/UF/ZF/CF
        R[i].setValue((signed char)result);  // make the result back into 1 byte
        
    }

    FlagRegister& getFlags() 
    {
        return flags;
    }
};


class Instruction{ 
    public:
       virtual void execute( CPU& cpu) = 0; //every child class must create execute

};


//======== ADD ============
class ADD : public Instruction
{
    private:
      int dest;  // dest = destination
      int src;   // src = source     

    public:
      ADD(int d, int s)
      {
        dest = d;
        src = s;
      }

      void execute( CPU& cpu)
      {
        int result = cpu.getRegister(dest) + cpu.getRegister(src); // get values form register, then add 
        cpu.setRegister(dest,result); // store result into destination register
      }

};

class SUB : public Instruction
{
    private:
      int dest;
      int src;

    public:
      SUB(int d,int s)
      {
        dest = d;
        src = s;
      }

      void execute ( CPU& cpu)
      {
        int result = cpu.getRegister(dest) - cpu.getRegister(src);
        cpu.setRegister(dest,result);
      }
};


class MUL : public Instruction
{
    private:
      int dest;
      int src;

    public:
      MUL(int d,int s)
      {
        dest = d;
        src = s;
      }

      void execute ( CPU& cpu)
      {
        int result = cpu.getRegister(dest) * cpu.getRegister(src);
        cpu.setRegister(dest,result);
      }
};


class DIV : public Instruction
{
    private:
      int dest;
      int src;

    public:
      DIV(int d,int s)
      {
        dest = d;
        src = s;
      }

      void execute ( CPU& cpu)
      {
        int division = cpu.getRegister(src);

        if (division != 0)
        {
        int result = cpu.getRegister(dest) / cpu.getRegister(src);
        cpu.setRegister(dest,result);
        }

        else
        {
          cout << "Math Error: cannot be divide by 0" << endl;
        }


        
      }
};

int main()  // checking purpose
{
    CPU cpu;

    cpu.setRegister(0,1000);
    cpu.setRegister(1,5);

    ADD add(0,1);

    add.execute(cpu);

    cout << "R0 = "
         << (int)cpu.getRegister(0)
         << endl;

    return 0;
}