#ifndef Mod_Node_h
#define Mod_Node_h

/// <summary>
/// A node in the map that the player traverse. Each node contains a list of nodes that this node leads to.
/// </summary>
class Mod_Node {
	public:
		enum Node_Type {
			NotNode = -1,
			MonsterNode = 0,
			EliteNode = 1,
			RestNode = 2,
			ShopNode = 3
		};
		Node_Type type;
};
#endif
