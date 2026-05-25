#include <iostream>
#include <fstream>
#include <sstream> 
#include <string> 
#include <cstdlib>
using namespace std;

// Custom Vector class for dynamic array
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

// Custom Stack class
template<typename T>
class MyStack {
  private:
    MyVector<T> elements; // uses the MyVector template

  public:
    MyStack() {}

    //add element to top
    void push(const T& value){
      elements.pushback(value);
    }

    // remove top element
    void pop() {
      if (isEmpty()){ // error handling for empty stack
        cout << "Error: Cannot pop from empty stack" << endl;
        exit(1);
      }
      elements.popback();
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

      bool getOF() const { return OF; }
      bool getUF() const { return UF; }
      bool getZF() const { return ZF; }
      bool getCF() const { return CF; }
};

class CPU
{
  private:
    BaseRegister R[8]; // R0-R7, R=register
    FlagRegister flags; // CPU flags
    signed char SI = 0; // stack index register
    Memory memory; // memory object

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

    signed char getSI() {
      return SI;
    }

    void setSI(signed char value){
      SI = value;
    }

    Memory& getMemory() {
      return memory;
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

class INPUT : public Instruction {
private:
    int dest;
public:
    INPUT(int d) { dest = d; }
    void execute(CPU& cpu) override {
        int inputVal;
        cout << "INPUT - Enter an integer for R" << dest << " (-128 to 127): ";
        cin >> inputVal;
        cpu.setRegister(dest, inputVal);
    }
};

class DISPLAY : public Instruction {
private:
    int src;
public:
    DISPLAY(int s) { src = s; }
    void execute(CPU& cpu) override {
        cout << "DISPLAY -> R" << src << " = " << (int)cpu.getRegister(src) << endl;
    }
};

class RESET : public Instruction {
public:
    void execute(CPU& cpu) override {
        cpu.getFlags().reset();
        cout << "SYSTEM RESET - Flags have been cleared." << endl;
    }
};

class Runner {
private:
    CPU cpu;
    int pc;                         // program counter
    MyVector<Instruction*> program; 

    // parsing instructions
    // 1. parse register text (exp: convert "R0," or "R5" to the integer 0 or 5).
    int parseRegister(string regStr) {
        if (!regStr.empty() && regStr.back() == ',') {
            regStr.pop_back(); // remove ","
        }
        if (regStr.length() >= 2 && regStr[0] == 'R') {
            return regStr[1] - '0';
        }
        return -1;
    }

    // 2. constructs the corresponding derived instruction object based on the identified opcode
    void buildInstruction(const string& op, const string& arg1, const string& arg2) {
        int r1 = parseRegister(arg1);
        int r2 = parseRegister(arg2);

        if (op == "ADD") program.pushback(new ADD(r1, r2));
        else if (op == "SUB") program.pushback(new SUB(r1, r2));
        else if (op == "MUL") program.pushback(new MUL(r1, r2));
        else if (op == "DIV") program.pushback(new DIV(r1, r2));
        else if (op == "INPUT") program.pushback(new INPUT(r1));
        else if (op == "DISPLAY") program.pushback(new DISPLAY(r1));
        else if (op == "RESET") program.pushback(new RESET());
    }

public:
    Runner() { pc = 0; }

    ~Runner() { // destructor (releases memory dynamically allocated to instruction objects)
        for (int i = 0; i < program.size(); i++) {
            delete program[i];
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
            if (ss >> op) {
                ss >> arg1 >> arg2;
                buildInstruction(op, arg1, arg2);
            }
        }
        file.close();
    }

    // pc updates
    // initialised to 0 when loading a new program and is updated after the execution of any statement
    void run() {
        pc = 0;
        while (pc < program.size()) {
            Instruction* currentInst = program[pc];
            pc++; 
            currentInst->execute(cpu); // instruction execution flow
        }
        printOutput();
    }

    // output formatting
    void printOutput() {
        cout << "\n#Begin#" << endl;
        cout << "#Registers#" << endl;
        for (int i = 0; i < 8; i++) {
            cout << "R" << i << " " << (int)cpu.getRegister(i) << endl;
        }
        cout << "#Flags#" << endl;
        cout << "OF " << cpu.getFlags().getOF() << endl;
        cout << "UF " << cpu.getFlags().getUF() << endl;
        cout << "ZF " << cpu.getFlags().getZF() << endl;
        cout << "CF " << cpu.getFlags().getCF() << endl;
        cout << "PC " << pc << endl;
        cout << "#End#" << endl;
    }
};

int main()  // checking purpose
{
    Runner vm;

    cout << "--- Virtual Machine System Booting ---" << endl;
    
    vm.loadFile("test.asm"); 

    return 0;
}