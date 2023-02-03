#include "../../idlib/precompiled.h"
#ifndef Mod_Map_h
#define Mod_Map_h

#include "Mod_Node.h"

/// <summary>
/// The map of nodes that the player can traverse.
/// </summary>
class Mod_Map {
	public:
		/// <summary>
		/// A list of the immediate nodes that the player can access. They can point to a list of more nodes.
		/// </summary>
		idList<Mod_Node> nodes;

		/// <summary>
		/// Generates the list of nodes that the player can traverse from.
		/// </summary>
		void GenerateMap();

		/// <summary>
		/// Constructor
		/// </summary>
		Mod_Map();

		/// <summary>
		/// Frees memory from the list
		/// </summary>
		~Mod_Map();
};
#endif