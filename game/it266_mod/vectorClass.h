#ifndef Vector_Class_h
#define Vector_Class_h

template <typename T> class vectorClass {

    // arr is the class pointer
    // which stores the address of our vector
    T* arr;

    // capacity is the total storage
    // capacity of the vector
    int capacity;

    // current is the number of elements
    // currently present in the vector
    int current;
public:
    // Default constructor to initialise
    // an initial capacity of 1 element and
    // allocating storage using dynamic allocation
    vectorClass()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }
    //destructor to deallocate storage allocated by dynamic allocation
    //to prevent memory leak
    ~vectorClass()
    {
        delete[] arr;
    }

    // Function to add an element at the last
    void push(T data)
    {

        // if the number of elements is equal to the
        // capacity, that means we don't have space to
        // accommodate more elements. We need to double the
        // capacity
        if (current == capacity) {
            T* temp = new T[2 * capacity];

            // copying old array elements to new array
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }

            // deleting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }

        // Inserting data
        arr[current] = data;
        current++;
    }

    // function to replace any element at an index
    void replace(T data, int index)
    {
        if (index < 0 || index >= size)
            return;
        else
            arr[index] = data;
    }

    // function to extract element at any index
    T get(int index)
    {

        // if index is within the range
        if (index < current)
            return arr[index];
    }

    // function to delete last element
    T pop() 
    {
        current--; 
        return arr[current];
    }

    // function to remove element at index
    T removeAt(int index)
    {
        T item = arr[index];
        for (int i = index; i < size() - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        current--;
        return item;
    }
    int indexOf(T item)
    {
        for (int i = 0; i < size(); i++)
        {
            if (arr[i] == item)
                return i;
        }
        return -1;
    }
    //  Insertion Sort
    void sort()
    {
        for (int i = 1; i < size(); i++)
        {
            T item = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > item)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = item;
        }
    }
    // function to get size of the vector
    int size() { return current; }

    // function to get capacity of the vector
    int getcapacity() { return capacity; }
};
#endif // !Vector_Class_h