
template <class T>
class Array {
 private:
   T* data;
   unsigned int size;

 public:
   Array();
   void add(T& item);
   T& operator [] (unsigned int index);
};

//Constructor
template <class T>
Array<T>::Array() {
  size = 0;
};

//Array insertion
template <class T>
void Array<T>::add(T& item) {
  //Increment internal counter
  size++;

  //If it's the first item, allocate memory
  if(size == 1) {
    data = (T*)malloc(data, sizeof(T) * size);
  }

  //Otherwise, reallocate memory
  else {
    data = (T*)realloc(data, sizeof(T) * size);
  }

  //Insert the result
  data[size-1] = item;
}

//Array access operator
template <class T>
T& Array<T>::operator [] (unsigned int index) {
  return data[index];
}
