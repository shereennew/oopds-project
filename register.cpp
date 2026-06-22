#include <iostream>
#include <fstream>
#include <sstream> 
#include <string> 
#include <cstdlib>
using namespace std;

// custom vector class 
// template created by Eryne 
template<typename T>
class MyVector {
  private: 
    T* data;
    int cap; // capacity
    int sz; // size

    // creates a larger arr if overflowed
    void grow(){
      int newCapacity = cap *2;
      T* newData = new T[newCapacity];

      // copy from data (old) to newData (new)
      for (int i = 0; i< sz; i++){
        newData[i] = data[i];
      }
      
      delete[] data; //delete old data
      data = newData; //point to new array
      cap = newCapacity; //update capacity
    }
  
  public:
    // Constructor for a brand new empty vector
    MyVector() {
      sz = 0; // no elements yet
      cap = 4; // allocates memory for 4 elemeents
      data = new T[cap]; //points to the allocated memory
    }

    // copy constructor for creating a vector as a copy for existing vector
    MyVector(const MyVector& other){
      sz = other.sz;
      cap = other.cap;
      data = new T[cap];
      for (int i = 0; i < sz; i++){
        data[i] = other.data[i];
      }
    }

    // assignment operator to replace array
    MyVector& operator=(const MyVector& other){
      if (this == &other) return *this;
      delete[] data;
      sz = other.sz;
      cap = other.cap;
      data = new T[cap];
      for (int i = 0; i < sz; i++){
        data[i] = other.data[i];
      }
      return *this;
    }
    
    // Destructor if Myvector out of scope
    ~MyVector() {
      delete[] data;
    }

    //adds new element to the end of the vector
    void pushback(const T& value){
      if (sz == cap){
        grow(); //called when full to transfer data from old arr to new arr
      }
      data[sz] = value; // places value in user-defined place
      sz++;
    }

    // removes last element from vector
    void popback(){
      if (sz > 0){
        sz--;
      }
    }

    // allows using square brackets
    const T& operator[](int index){
      return data[index];
    }

    // get size
    int size() const {
      return sz;
    }

    // get capacity
    int capacity() const{
      return cap;
    }

    // returns if size = 0
    bool empty() const {
      return sz == 0;
    }
};

// custom stack class
// template created by Eryne
template<typename T>
class MyStack {
  private:
    MyVector<T> elements; // uses the MyVector template

  public:
    MyStack() {}

    //add element to top
    void push(const T& value){

      if (elements.size() >= 8) {
        cout << "Error: Stack Overflow (Maximum capacity of 8 bytes reached)" << endl;
        exit(1);
      }

      elements.pushback(value);
    }

    // remove top element
    T pop() {
      if (isEmpty()){ // error handling for empty stack
        cout << "Error: Cannot pop from empty stack" << endl;
        exit(1);
      }
      T value = elements[elements.size() -1 ]; // get top value
      elements.popback(); // remove it
      return value; // return the value
    }

    // return top element without removing
    T& top() {
      if (isEmpty()){ // error handling for empty stack
        cout << "Error: Cannot return top element from empty stack" << endl;
        exit(1);
      }
      return elements[elements.size() -1];
    }

    // check if empty
    bool isEmpty() {
      return elements.empty();
    }

    //get size
    int size() {
      return elements.size();
    }
};

// custom queue class
// template created by Eryne
template<typename T>
class MyQueue {
  private:
    T* data;
    int frontIndex;
    int rearIndex;
    int sz;
    int cap;

    int next(int index){
      return (index + 1) % cap;
    }

    void grow(){
      int oldCapacity = cap;
      int newCapacity = cap * 2;
      T* newData = new T[newCapacity];

      // copy elements in order (from front to rear)
      for (int i = 0; i < sz; i++){
        int oldIndex = (frontIndex + i) % oldCapacity;
        newData[i] = data[oldIndex];
      }

      // delete old array
      delete[] data;

      //point to new array
      data = newData;

      //reset indices
      frontIndex = 0;
      rearIndex = sz-1;

      //update capacity
      cap = newCapacity;
    }

  public:
    MyQueue() {
      sz = 0;
      cap = 4;
      frontIndex = 0;
      rearIndex = sz -1;
      data = new T[cap];
    }

    ~MyQueue() {
      delete[] data;
    }

    void enqueue(const T& value){
      if (sz == cap){ // calls grow to create a bigger arr if capacity is full
        grow();
      }
      rearIndex = next(rearIndex); // move rear forward 
      data[rearIndex] = value; // store value 
      sz++;
    }

    void dequeue(){
      if (isEmpty()){
        cout << "Error: Cannot dequeue from empty queue" << endl;
        exit(1);
      }
      frontIndex = next(frontIndex);
      sz--;
    }

   const T& front() const {
      if (isEmpty()){
        cout << "Error: Cannot return first data from empty queue" << endl;
        exit(1);
      }
      return data[frontIndex];
    }

    bool isEmpty() const {
      return sz == 0;
    }

    int size() const {
      return sz;
    }
};

// class created by Eryne
class Memory {
  private:
    signed char memory[64]; //64 bytes

  public:
    Memory() {
      // assigned every element in memory to 0
      for (int i = 0; i < 64; i++){
        memory[i] = 0;
      }
    }

    // to get address
    signed char load(int address){
      if (isValidAddress(address)){
        return memory[address];
      }else{
        cout << "Error: Address not found" << endl;
        return 0;
      }
    }

    // to store value at address
    void store(int address, signed char value){
      if (isValidAddress(address)){
        memory[address] = value;
      }else{
        cout << "Error: Invalid memory address " << address << endl;
      }
    }

    bool isValidAddress(int address){
      if (address >= 0 && address <=63){
        return true;
      }
      return false;
    }
  };

class BaseRegister {
public:
    virtual signed char getValue() = 0;
    virtual void setValue(signed char v) = 0;
    virtual ~BaseRegister() {}
};

class GeneralRegister : public BaseRegister {
    private:
        signed char value;  // 1 Byte， -128 to 127
        
    public:
        GeneralRegister() { value = 0; }
        
        signed char getValue() override { return value; }   
        void setValue(signed char v) override { value = v; }
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

      void resetOF()
      {
          OF = false;
      }

      void resetUF()
      {
          UF = false;
      }

      void resetZF()
      {
          ZF = false;
      }

      void resetCF()
      {
          CF = false;
      }

      
      bool getOF() const { return OF; }
      bool getUF() const { return UF; }
      bool getZF() const { return ZF; }
      bool getCF() const { return CF; }
};

class CPU
{
  private:
    BaseRegister* R[8]; // R0-R7, R=register
    FlagRegister flags; // CPU flags
    signed char SI = 0; // stack index register, added by Eryne
    Memory memory; // memory object, added by Eryne
    MyStack<signed char> stack; // for push and pop classes, added by Eryne

  public:
    CPU() {
        for(int i = 0; i < 8; i++) {
            R[i] = new GeneralRegister(); 
        }
    }

    ~CPU() {
        for(int i = 0; i < 8; i++) {
            delete R[i]; 
        }
    }
   
    signed char getRegister(int i) // get value from  selected register
    {
       if (i < 0 || i > 7) {
            cout << "Error: Invalid register access." << endl;
            exit(1); 
        }
        return R[i]->getValue();
    }

    void setRegister(int i, int result) // store result into selected register
    {
        if (i < 0 || i > 7) {
            cout << "Error: Invalid register access." << endl;
            exit(1);
        }
        flags.update(result); // check if the result was OF/UF/ZF/CF
        R[i]->setValue((signed char)result);  // make the result back into 1 byte
        
    }

    FlagRegister& getFlags() 
    {
        return flags;
    }

    // function created by Eryne
    signed char getSI() {
      return SI;
    }

    // function created by Eryne
    void setSI(signed char value){
      if (value > 127 ){
        cout << "Error: Stack overflow, SI exceeds 127" << endl;
        return;
      }
      if (value < -128) {
        cout << "Error: Stack overflow, SI below -128" << endl;
        return;
      }
      SI = value;
    }

    // function created by Eryne
    Memory& getMemory() {
      return memory;
    }

    // function created by Eryne
    MyStack<signed char>& getStack() {
      return stack;
    }
};


class Instruction{ 
    public:
       virtual void execute( CPU& cpu) = 0; //every child class must create execute
       virtual ~Instruction(){}
};


//======== ADD ============
class ADD : public Instruction
{
    private:
      int dest;  // dest = destination
      int src;   // src = source 
      bool isImm;  //imm = immediate    

    public:
      ADD(int d, int s, bool imm = false) : dest(d), src(s), isImm(imm) {}
      
      void execute( CPU& cpu) override {
        int val2 = isImm ? src : cpu.getRegister(src); 
        int result = cpu.getRegister(dest) + val2; 
        cpu.setRegister(dest,result); 
      }
};

class SUB : public Instruction
{
    private:
      int dest;
      int src;
      bool isImm;

    public:
      SUB(int d,int s, bool imm = false) : dest(d), src(s), isImm(imm) {}

      void execute ( CPU& cpu) override {
        int val2 = isImm ? src : cpu.getRegister(src);
        int result = cpu.getRegister(dest) - val2;
        cpu.setRegister(dest,result);
      }
};

class MUL : public Instruction
{
    private:
      int dest;
      int src;
      bool isImm;

    public:
      MUL(int d,int s, bool imm = false) : dest(d), src(s), isImm(imm) {}

      void execute ( CPU& cpu) override {
        int val2 = isImm ? src : cpu.getRegister(src);
        int result = cpu.getRegister(dest) * val2;
        cpu.setRegister(dest,result);
      }
};

class DIV : public Instruction
{
    private:
      int dest;
      int src;
      bool isImm;

    public:
      DIV(int d,int s, bool imm = false) : dest(d), src(s), isImm(imm) {}

      void execute ( CPU& cpu) override {
        int val2 = isImm ? src : cpu.getRegister(src);
        if (val2 != 0) {
          int result = cpu.getRegister(dest) / val2;
          cpu.setRegister(dest,result);
        } else {
          cout << "Math Error: cannot be divide by 0" << endl;
          exit(1);
        }
      }

        
};

// MOV_DIRECT 
class MOV_Direct : public Instruction {
  private:
    int dest; // destination register
    int src; // source register

  public:
    MOV_Direct(int d, int s) : dest(d), src(s) {}

    void execute(CPU& cpu) override {
        int value = cpu.getRegister(src);
        cpu.setRegister(dest, value);
    }
};

// MOV_IMMEDIATE
class MOV_Immediate : public Instruction {
  private:
    int dest; // destination register
    int value; // immediate value

  public:
    MOV_Immediate(int d, int v) : dest(d), value(v) {}

    void execute(CPU& cpu) override {
        cpu.setRegister(dest, value);
    }
};

class MOV_FromMemory : public Instruction {
  private:
    int dest;
    int address;
  public:
    MOV_FromMemory(int d, int addr) : dest(d), address(addr) {}
    
    void execute(CPU& cpu) override {
        // Load from memory
        signed char value = cpu.getMemory().load(address);
        // Store to register
        cpu.setRegister(dest, value);
    }
};

class MOV_ToMemory : public Instruction {
  private:
    int address;  // memory address FIRST
    int src;      // source register SECOND
  public:
    MOV_ToMemory(int addr, int s) : address(addr), src(s) {}
    
    void execute(CPU& cpu) override {
        signed char value = cpu.getRegister(src);
        cpu.getMemory().store(address, value);
    }
};

// MOV R3, [R1]
class MOV_Indirect : public Instruction {
  private:
    int dest;  
    int srcAddr; 
  public:
    MOV_Indirect(int d, int sAddr) : dest(d), srcAddr(sAddr) {}
    
    void execute(CPU& cpu) override {
        // 1. take address from R1
        int address = cpu.getRegister(srcAddr);
        // 2. take value
        signed char value = cpu.getMemory().load(address);
        // 3. save in R3
        cpu.setRegister(dest, value);
    }
};

// SHL (Shift Left)
class SHL : public Instruction {
  private:
    int dest;    // register to shift
    int amount;  // how many positions to shift
    
  public:
    SHL(int d, int a) : dest(d), amount(a) {}
    
    void execute(CPU& cpu) {
        // Get current value
        signed char value = cpu.getRegister(dest);
        
        // Shift left using << operator
        // Example: value=5 (binary 00000101), amount=2
        // 5 << 2 = 20 (binary 00010100)
        int result = value << amount;
        
        // Store result (flags update automatically if overflow)
        cpu.setRegister(dest, result);
    }
};

// SHR (Shift Right)
class SHR : public Instruction {
  private:
    int dest;    // register to shift
    int amount;  // how many positions to shift
    
  public:
    SHR(int d, int a) : dest(d), amount(a) {}
    
    void execute(CPU& cpu) {
        // Get current value
        signed char value = cpu.getRegister(dest);
        
        // Need to treat as unsigned for right shift to avoid sign issues
        // Example: value=20 (binary 00010100), amount=2
        // 20 >> 2 = 5 (binary 00000101)
        unsigned char uvalue = (unsigned char)value;
        
        // Shift right
        int result = (signed char)(uvalue >> amount);
        
        // Store result
        cpu.setRegister(dest, result);
    }
};


//ROL (Rotate Left)
class ROL : public Instruction {
  private:
    int dest;
    int amount;
  public:
    ROL(int d, int a) : dest(d), amount(a) {}
    
    void execute(CPU& cpu) override {
        unsigned char value = (unsigned char)cpu.getRegister(dest);
        int shift = amount % 8;
        
        // Simple rotation
        unsigned char result = (value << shift) | (value >> (8 - shift));
        
        cpu.setRegister(dest, (signed char)result);
    }
};

//ROR (Rotate Right)
class ROR : public Instruction {
  private:
    int dest;
    int amount;
  public:
    ROR(int d, int a) : dest(d), amount(a) {}
    
    void execute(CPU& cpu) override {
        unsigned char value = (unsigned char)cpu.getRegister(dest);
        int shift = amount % 8;
        
        // Simple rotation
        unsigned char result = (value >> shift) | (value << (8 - shift));
        
        cpu.setRegister(dest, (signed char)result);
    }
};

//INC (Increment)
class INC : public Instruction {
  private:
    int dest;  // which register to increment
    
  public:
    INC(int d) : dest(d) {}  // constructor stores the register number
    
    void execute(CPU& cpu) {
        // Get current value from register
        int currentValue = cpu.getRegister(dest);
        
        // Add 1 to it
        int result = currentValue + 1;
        
        // Store back to same register (this also updates flags)
        cpu.setRegister(dest, result);
    }
};

//DEC (Decrement)
class DEC : public Instruction {
  private:
    int dest;  // which register to decrement
    
  public:
    DEC(int d) : dest(d) {}
    
    void execute(CPU& cpu) {
        // Get current value
        int currentValue = cpu.getRegister(dest);
        
        // Subtract 1
        int result = currentValue - 1;
        
        // Store back (updates flags)
        cpu.setRegister(dest, result);
    }
};

class INPUT : public Instruction {
private:
    int dest;

public:
    INPUT(int d)
    {
        dest = d;
    }

    void execute(CPU& cpu) override {
        int inputVal;
        cout << "? ";
        cin >> inputVal;
        cpu.setRegister(dest, inputVal); 
    }
};

class DISPLAY : public Instruction {
private:
    int src;

public:
    DISPLAY(int s)
    {
        src = s;
    }

    void execute(CPU& cpu) override
    {
        cout << (int)cpu.getRegister(src) << endl;
    }
};

class RESET : public Instruction {
private:
    string flagName;

public:

    RESET(string flag) {
        flagName = flag;
    }

    void execute(CPU& cpu) override {

        if(flagName == "OF")
        {
            cpu.getFlags().resetOF();
        }
        else if(flagName == "UF")
        {
            cpu.getFlags().resetUF();
        }
        else if(flagName == "ZF")
        {
            cpu.getFlags().resetZF();
        }
        else if(flagName == "CF")
        {
            cpu.getFlags().resetCF();
        }
    }
};

// class created by Eryne 
// for LOAD <DestinationRegister>, <address>
class LOAD_Direct : public Instruction {
  private:
    int destReg; // destination register(R1)
    int address; // memory address (20)
  public:
    // store destReg and memory address
    LOAD_Direct(int dest, int addr) : destReg(dest), address(addr) {} 

    void execute(CPU& cpu) override {
      // get value from memory at 'address'
      signed char value = cpu.getMemory().load(address);
      // store that value into register 'destReg'
      cpu.setRegister(destReg, value);
    }
};

// class created by Eryne
// for LOAD <DestinationRegister>, <[SourceRegister]>
class LOAD_Indirect : public Instruction {
  private:
    int destReg; // destination register example: [R1]
    int srcReg; // source register that holds address example: [R2]
  public:
    // store destReg and sourceReg
    LOAD_Indirect(int dest, int src) : destReg(dest), srcReg(src){}

    void execute(CPU& cpu) override {
      // get address from source register
      int address = cpu.getRegister(srcReg);
      // get value from memory at that address
      signed char value = cpu.getMemory().load(address);
      // store value into destination register
      cpu.setRegister(destReg, value);
    }
};

// class created by Eryne
// for STORE <Destination Register>, <memoryAddress>
class STORE_Direct : public Instruction {
  private:
    int srcReg; // source register example: [R1]
    int address; // memory address example: 20
  public:
    // stores source register and memory address
    STORE_Direct(int src, int addr) : srcReg(src), address(addr) {}

    void execute (CPU& cpu) override {
      // get value from register
      signed char value = cpu.getRegister(srcReg);
      // store value to memory at address
      cpu.getMemory().store(address, value);
    }
};

// class created by Eryne
// for STORE <[DestinationRegister]> , <SourceRegister>
class STORE_Indirect : public Instruction{
  private:
    int srcReg; // source register example: [r1]
    int addressReg; // register holding address example: r2
  public:
    // stores address register and source register
    STORE_Indirect(int src, int addrReg) : srcReg(src), addressReg(addrReg) {}

    void execute(CPU& cpu) override {
      // get address from addressReg
      int address = cpu.getRegister(addressReg);
      // get value from srcReg
      signed char value = cpu.getRegister(srcReg);
      // store value to memory at that address
      cpu.getMemory().store(address, value);
    }
};

// class created by Eryne
// for PUSH <REGISTER>
class PUSH : public Instruction {
  private:
    int srcReg;
  public:
    //stores source register
    PUSH(int src) : srcReg(src) {}

    void execute (CPU& cpu) override {
      // get value from srcReg
      signed char value = cpu.getRegister(srcReg);
      // push onto stack
      cpu.getStack().push(value);
      // increase SI
      cpu.setSI(cpu.getSI() + 1);
    }
};

// class created by Eryne
// for POP <REGISTER>
class POP : public Instruction {
  private:
    int destReg;
  public:
    // stores destination register
    POP (int dest) : destReg(dest) {}

    void execute(CPU& cpu) override {
      // pop from stack
      signed char value = cpu.getStack().pop();
      // store into destReg
      cpu.setRegister(destReg, value);
      // decrease SI
      cpu.setSI(cpu.getSI() - 1);
    }
};

class Runner {
private:
    CPU cpu;
    unsigned char pc;                         // program counter
    MyQueue<Instruction*> program; 

    void print4Digit(ostream& out, int value) {
        if(value < 0) {
            out << "-";
            value = -value;
            if(value < 10) out << "00" << value;
            else if(value < 100) out << "0" << value;
            else out << value;
        } else {
            if(value < 10) out << "000" << value;
            else if(value < 100) out << "00" << value;
            else if(value < 1000) out << "0" << value;
            else out << value;
        }
    }

    // parsing instructions
    int parseRegister(string regStr) {
        if (!regStr.empty() && regStr.back() == ',') {
            regStr.pop_back(); // remove ","
        }
        if (regStr.length() >= 2 && regStr[0] == 'R') {
            return regStr[1] - '0';
        }
        return -1;
    }
    
    void handleMov(const string& arg1, const string& arg2, int r1, int r2) {
      // Clean strings (remove trailing commas)  
        string a1 = arg1; 
        string a2 = arg2;
        if (!a1.empty() && a1.back() == ',') a1.pop_back();
        if (!a2.empty() && a2.back() == ',') a2.pop_back();
        
        // handle MOV [R1], R2 or MOV [20], R1
        if (a1[0] == '[' && a1.back() == ']') {
            string inner = a1.substr(1, a1.length() - 2);
            if (inner[0] == 'R') {
                int destAddrReg = inner[1] - '0';
                program.enqueue(new STORE_Indirect(r2, destAddrReg));
            } else {
                int addr = stoi(inner);
                program.enqueue(new MOV_ToMemory(addr, r2));
            }
        } 
        // handle MOV R3, [R1] or MOV R1, [20]
        else if (a2[0] == '[' && a2.back() == ']') {
            string inner = a2.substr(1, a2.length() - 2);
            if (inner[0] == 'R') {
                int srcAddrReg = inner[1] - '0';
                program.enqueue(new MOV_Indirect(r1, srcAddrReg));
            } else {
                int addr = stoi(inner);
                program.enqueue(new MOV_FromMemory(r1, addr));
            }
        } 
        // handle MOV R1, R2
        else if (a2[0] == 'R') {
            program.enqueue(new MOV_Direct(r1, r2));
        }
        // handle MOV R1, 5 or MOV R1, #5
        else {
            string valStr = a2;
            if (valStr[0] == '#') valStr = valStr.substr(1);
            int immValue = stoi(valStr);
            program.enqueue(new MOV_Immediate(r1, immValue));
        }
    }

    void handleMath(const string& op, int r1, const string& arg2, int r2) {
        string a2 = arg2; 
        if (!a2.empty() && a2.back() == ',') a2.pop_back(); // clear ","
        
        bool isImm = (r2 == -1); // if parseRegister cannot parse R，then is integer
        int val2 = 0;
        
        if (isImm) {
            // delete # if there is
            if (a2[0] == '#') a2 = a2.substr(1);
            val2 = stoi(a2);
        } else {
            val2 = r2; 
        }

        if (op == "ADD") program.enqueue(new ADD(r1, val2, isImm));
        else if (op == "SUB") program.enqueue(new SUB(r1, val2, isImm));
        else if (op == "MUL") program.enqueue(new MUL(r1, val2, isImm));
        else if (op == "DIV") program.enqueue(new DIV(r1, val2, isImm));
    }
    
    // SHL, SHR, ROL, ROR - NEED TO GET THE AMOUNT VALUE
    void handleShiftRotate(const string& op, const string& arg2, int r1) {
        // Check if second argument is a number (like #2 or just 2)
        string amountStr = arg2;
        if (amountStr[0] == '#') amountStr = amountStr.substr(1);
        int amount = stoi(amountStr);
        
        if (op == "SHL") program.enqueue(new SHL(r1, amount)); 
        else if (op == "SHR") program.enqueue(new SHR(r1, amount));
        else if (op == "ROL") program.enqueue(new ROL(r1, amount));
        else if (op == "ROR") program.enqueue(new ROR(r1, amount));
    }

    void handleLoadStore(const string& op, const string& arg2, int r1) {
        if (op == "LOAD") {
          // LOAD R1, 20 (direct - number without #)
            if (arg2[0] != '[') {
                program.enqueue(new LOAD_Direct(r1, stoi(arg2)));
            } 
            // LOAD R1, [R2] (indirect - register in brackets)
            else if (arg2[0] == '[' && arg2.back() == ']') {
                int srcReg = parseRegister(arg2.substr(1, arg2.length() - 2));
                program.enqueue(new LOAD_Indirect(r1, srcReg));
            }
        } else if (op == "STORE") {
          // STORE R1, 20 (direct)
            if (arg2[0] != '[') {
                program.enqueue(new STORE_Direct(r1, stoi(arg2)));
            } 
            // STORE R1, [R2] (indirect)
            else if (arg2[0] == '[' && arg2.back() == ']') {
                int destReg = parseRegister(arg2.substr(1, arg2.length() - 2));
                program.enqueue(new STORE_Indirect(destReg, r1));
            }
        }
    }


    void buildInstruction(const string& op, const string& arg1, const string& arg2) {
        int r1 = parseRegister(arg1);
        int r2 = parseRegister(arg2);

        if (op == "ADD" || op == "SUB" || op == "MUL" || op == "DIV") handleMath(op, r1, arg2, r2);
        else if (op == "INPUT") program.enqueue(new INPUT(r1));
        else if (op == "DISPLAY") program.enqueue(new DISPLAY(r1));
        else if (op == "RESET") program.enqueue(new RESET(arg1));
        else if (op == "MOV") handleMov(arg1, arg2, r1, r2);
        else if (op == "SHL" || op == "SHR" || op == "ROL" || op == "ROR") handleShiftRotate(op, arg2, r1);
        else if (op == "INC") program.enqueue(new INC(r1));
        else if (op == "DEC") program.enqueue(new DEC(r1));
        else if (op == "LOAD" || op == "STORE") handleLoadStore(op, arg2, r1);
        else if (op == "PUSH") program.enqueue(new PUSH(r1));
        else if (op == "POP") program.enqueue(new POP(r1));
        else {
            cout << "Error: Unknown instruction " << op << endl;
            exit(1);
        }
    }

public:
    Runner() { pc = 0; }

    ~Runner() { // destructor (releases memory dynamically allocated to instruction objects)
        while (!program.isEmpty()) {
            delete program.front();
            program.dequeue();
        }
    }

    // file reading(.asm)
    void loadFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            size_t commentPos = line.find(';'); // filter comments
            if (commentPos != string::npos) line = line.substr(0, commentPos);

            stringstream ss(line);
            string op, arg1, arg2;
            if(ss >> op)
            {
                ss >> arg1 >> arg2;

                string extra;

                if(ss >> extra)
                {
                    cout << "Error: Multiple instructions on one line" << endl;
                    exit(1);
                }

                buildInstruction(op,arg1,arg2);
            }
        }
        file.close();
    }

    // pc updates
    // initialised to 0 when loading a new program and is updated after the execution of any statement
    void run() {
        pc = 0;
        while (!program.isEmpty()) {
            Instruction* currentInst = program.front();
            program.dequeue();
            currentInst->execute(cpu);
            pc++; 
  
            delete currentInst;
        }
        printOutput();
    }

    void printRegistersAndFlags(ostream& out) {
        out << "#Registers#";
        for(int i = 0; i < 8; i++) {
            print4Digit(out, (int)cpu.getRegister(i));
            out << "#";
        }
        out << endl << "#Flags#";
        out << "OF#" << cpu.getFlags().getOF() << "#"
            << "UF#" << cpu.getFlags().getUF() << "#"
            << "CF#" << cpu.getFlags().getCF() << "#"
            << "ZF#" << cpu.getFlags().getZF() << "#" << endl;
    }

    void printMemoryDump(ostream& out) {
        out << "#Memory#" << endl;
        for(int i = 0; i < 64; i++) {
            if(i % 8 == 0) out << "#";
            print4Digit(out, (int)cpu.getMemory().load(i));
            out << "#";
            if((i+1) % 8 == 0) out << endl;
        }
    }

    void printOutput() {
        cout << "#Begin#" << endl;
        printRegistersAndFlags(cout);
        cout << "#PC#";
        print4Digit(cout, pc);
        cout << "#" << endl;
        printMemoryDump(cout);
        cout << "#End#" << endl;

        // output.txt
        ofstream outFile("output.txt");
        if(outFile.is_open()) {
            outFile << "#Begin#" << endl;
            printRegistersAndFlags(outFile);
            outFile << "#PC#";
            print4Digit(outFile, pc);
            outFile << "#" << endl;
            printMemoryDump(outFile);
            outFile << "#End#" << endl;
            outFile.close();
            cout << "\n[System] Execution finished. Results have been saved to 'output.txt'." << endl;
        } else {
            cout << "\n[Error] Unable to create 'output.txt' file." << endl;
        }
    }
};

int main() {
    Runner vm;
    
    vm.loadFile("test.asm"); 
    vm.run(); 

    return 0;
}