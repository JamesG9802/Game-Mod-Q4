#include "../../idlib/precompiled.h"
#ifndef Mod_Map_h
#define Mod_Map_h

#include "Mod_Node.h"
template <typename T> class vectorClass {

    // arr is the integer pointer
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

    // function to add element at any index
    void push(T data, int index)
    {

        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity)
            push(data);
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
    void pop() { current--; }

    void removeAt(int index)
    {
        for (int i = index; i < size() - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        current--;
    }
    // function to get size of the vector
    int size() { return current; }

    // function to get capacity of the vector
    int getcapacity() { return capacity; }
};
struct ConnectionPair {
	int fromx, fromy, tox, toy;
};
/// <summary>
/// The map of nodes that the player can traverse.
/// </summary>
class Mod_Map {
	public:
		/// <summary>
		/// An array of nodes representing the map
		/// </summary>
		Mod_Node nodes[7][16];
	
		/// <summary>
		/// Maps node (x,y) to its connection node (x,y)
		/// </summary>
		vectorClass<ConnectionPair> connections;

		/// <summary>
		/// Generates the list of nodes that the player can traverse from.
		/// </summary>
		void GenerateMap();

		/// <summary>
		/// Constructor
		/// </summary>
		Mod_Map();

		/// <summary>
		/// Destructor
		/// </summary>
		~Mod_Map();

		/// <summary>
		/// Adds a connection to the connection list
		/// </summary>
		void AddConnection(struct ConnectionPair connection);

		/// <summary>
		/// Removes a connection at the index.
		/// </summary>
		/// <param name="index"></param>
		void RemoveAt(int index);

		/// <summary>
		/// Returns true if there is a matching connection in connections
		/// </summary>
		/// <param name="connection"></param>
		/// <returns></returns>
		bool ContainsConnection(struct ConnectionPair connection);

		/// <summary>
		/// Returns true if there is a matching connection in connections
		/// </summary>
		/// <param name="connection"></param>
		/// <returns></returns>
		bool ContainsConnection(int fromx, int fromy, int tox, int toy);

		/// <summary>
		/// Returns true if there is a connection to a node
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		bool HasConnectionTo(int x, int y);

		/// <summary>
		/// Returns true if there is a connection from a node
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		bool HasConnectionFrom(int x, int y);

	private:
		/// <summary>
		/// Returns true if both connections are identical
		/// </summary>
		/// <param name="conn1"></param>
		/// <param name="conn2"></param>
		/// <returns></returns>
		bool ConnectionCompare(struct ConnectionPair conn1, struct ConnectionPair conn2);
};


#endif