#include "../../idlib/precompiled.h"
#ifndef Mod_Map_h
#define Mod_Map_h

#include "Mod_Node.h"
#include "vectorClass.h"
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