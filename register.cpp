#include <iostream>
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
    int front;
    int rear;
    int sz;
    int cap;

    int next(int index){
      return (index + 1) % cap;
    }

    void grow(){

    }

  public:
    MyQueue() {
      sz = 0;
      cap = 4;
      front = 0;
      rear = -1;
      data = new T[cap];
    }

    ~MyQueue() {
      delete[] data;
    }

    void enqueue(const T& value){
      if (sz == cap){ // calls grow to create a bigger arr if capacity is full
        grow();
      }
      rear.next(); // move rear forward 
      data[rear] = value; // store value 
      sz++;
    }

    void dequeue(){
      if (isEmpty()){
        cout << "Error: Cannot dequeue from empty stack" << endl;
        exit(1);
      }
      front.next();
      sz--;
    }

    T& front() {
      if (isEmpty()){
        cout << "Error: Cannot return first data from empty stack" << endl;
        exit(1);
      }
      return data[front];
    }

    bool isEmpty(){
      return sz == 0;
    }

    int size() {
      return sz;
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