#include "Mod_Map.h"
#pragma hdrstop

Mod_Map::Mod_Map() {
}
Mod_Map::~Mod_Map() {
    delete nodes;
}

void Mod_Map::GenerateMap()
{
    //  Chooses the 6 starting points for node generation
    int indexes[6];
    for (int i = 0; i < 6;i++)
    {
        indexes[i] = gameLocal.random.RandomInt(7);

        //  Consistency Improvement - the first two nodes cannot be the same
        while(i == 1 && indexes[0] == indexes[1])
            indexes[1] = gameLocal.random.RandomInt(7);
    }

    //	Pick a random node on the first floor
    for (int i = 0; i < 6; i++)
    {
        int x = indexes[i];

        //  Generate connections to next floor
        for (int y = 0; y < 15; y++)
        {
            //  The last connection to the highest floor always connects to 
            //  (x,14)->(3,15)
            if (y == 14)
            {
                struct ConnectionPair conn;
                conn.fromx = x;
                conn.fromy = y;
                conn.tox = 3;
                conn.toy = 15;

                //  Checks if a connection already exists;
                if (!ContainsConnection(conn))
                {
                    AddConnection(conn);
                }
                break;
            }


            vectorClass<int> possibleConnections;
            possibleConnections.push(x - 1);
            possibleConnections.push(x);
            possibleConnections.push(x + 1);

            //  Check for any rule conflicts

            //  1. Can't be out of bounds (x < 0 || x > 6)
            for (int i = 0; i < possibleConnections.size(); i++)
            {
                if (possibleConnections.get(i) < 0 || possibleConnections.get(i) > 6)
                {
                    possibleConnections.removeAt(i);
                    i--;
                }
            }

            //  2. Can't be cross with another connection
            //  connection from (x,y) to (x,y+1) will never be crossed
            for (int i = 0; i < possibleConnections.size(); i++)
            {
                if (possibleConnections.get(i) == x)
                    continue;
                if (possibleConnections.get(i) < x)
                {
                    /*
                    * For this      Can't have
                        .   .       .   .
                          \           /
                        .   .       .   .

                    */
                    if (ContainsConnection(x - 1, y, x, y+1))
                    {
                        possibleConnections.removeAt(i);
                        i--;
                        continue;
                    }
                }
                if (possibleConnections.get(i) > x)
                {
                    /*
                     * For this      Can't have
                         .   .       .   .
                           /           \
                         .   .       .   .

                     */
                    if (ContainsConnection(x + 1, y, x, y + 1))
                    {
                        possibleConnections.removeAt(i);
                        i--;
                        continue;
                    }
                }
            }

            //  Pick a possibleConnection
            int connection = possibleConnections.get(gameLocal.random.RandomInt(possibleConnections.size()));
            struct ConnectionPair connectionpair;
            connectionpair.fromx = x;
            connectionpair.fromy = y;
            connectionpair.tox = connection;
            connectionpair.toy = y + 1;


            //  Checks if a connection already exists;
            if (!ContainsConnection(connectionpair))
            {

                gameLocal.Printf("[(%d %d)->(%d %d)]\n", connectionpair.fromx,
                    connectionpair.fromy, connectionpair.tox, connectionpair.toy);
                AddConnection(connectionpair);
            }
            x = connection;
        }
    }
    //  Afterwards, get rid of any excess connections from the 1st floor that map to the same 2nd floor
    //  This prevents early node convergence
    for (int i = 0; i < connections.size(); i++)
    {
        for (int j = i + 1; j < connections.size(); j++)
        {
            if (connections.get(i).toy == 1 && connections.get(j).toy == 1 &&
                connections.get(i).tox == connections.get(j).tox)
            {
                RemoveAt(j);
                j--;
            }
        }
    }

    //  Initializing Nodes
    for (int x = 0; x < 7; x++)
        for (int y = 0; y < 15; y++)
            nodes[x][y].type = Mod_Node::NotNode;

    //  Node pass
    for (int i = 0; i < connections.size(); i++)
    {
        struct ConnectionPair conn = connections.get(i);
        if (nodes[conn.fromx][conn.fromy].type != Mod_Node::NotNode)
            continue;
        //  1st floor is all monsters
        if (conn.fromy == 0)
            nodes[conn.fromx][conn.fromy].type = Mod_Node::MonsterNode;
        //  15th floor is all rest sites
        else if (conn.fromy == 14)
            nodes[conn.fromx][conn.fromy].type = Mod_Node::RestNode;
        //  (NVM) Floor 5 and below
        /*
        else if (conn.fromy <= 5)
        {
            float random = gameLocal.random.RandomFloat();
            if(random < .20)
                nodes[conn.fromx][conn.fromy].type = Mod_Node::ShopNode;
            else if (random < .27)
                nodes[conn.fromx][conn.fromy].type = Mod_Node::RestNode;
        }
        */
        else
        {
            float random = gameLocal.random.RandomFloat();
            if (random < .1)
                nodes[conn.fromx][conn.fromy].type = Mod_Node::ShopNode;
            else if (random < .3)
                nodes[conn.fromx][conn.fromy].type = Mod_Node::RestNode;
            else if (random < .4)
                nodes[conn.fromx][conn.fromy].type = Mod_Node::EliteNode;
            else
                nodes[conn.fromx][conn.fromy].type = Mod_Node::MonsterNode;
        }
    }
}
void Mod_Map::AddConnection(struct ConnectionPair connection)
{
    connections.push(connection);
}
void Mod_Map::RemoveAt(int index)
{
    connections.removeAt(index);
}
bool Mod_Map::ContainsConnection(struct ConnectionPair connection)
{
    for (int i = 0; i < connections.size(); i++)
    {
        if (ConnectionCompare(connections.get(i), connection))
            return true;
    }
    return false;
}
bool Mod_Map::ContainsConnection(int fromx, int fromy, int tox, int toy)
{
    struct ConnectionPair connection;
    connection.fromx = fromx;
    connection.fromy = fromy;
    connection.tox = tox;
    connection.toy = toy;
    return ContainsConnection(connection);
}
bool Mod_Map::HasConnectionTo(int x, int y)
{
    for (int i = 0; i < connections.size(); i++)
    {
        if (connections.get(i).tox == x && connections.get(i).toy == y)
            return true;
    }
    return false;
}
bool Mod_Map::HasConnectionFrom(int x, int y)
{
    for (int i = 0; i < connections.size(); i++)
    {
        if (connections.get(i).fromx == x && connections.get(i).fromy == y)
            return true;
    }
    return false;
}
bool Mod_Map::ConnectionCompare(struct ConnectionPair conn1, struct ConnectionPair conn2)
{
    return conn1.fromx == conn2.fromx &&
        conn1.fromy == conn2.fromy &&
        conn1.tox == conn2.tox &&
        conn1.toy == conn2.toy;
}
