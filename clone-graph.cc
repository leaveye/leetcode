/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
    typedef unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> cache_map;
    UndirectedGraphNode *doCloneGraph(cache_map &out, UndirectedGraphNode *node) {
        if (node != NULL && out.find(node) == out.end()) {
            UndirectedGraphNode *o = out[node] = new UndirectedGraphNode(node->label);
            for (auto &child : node->neighbors)
                o->neighbors.push_back(doCloneGraph(out, child));
        }
        return out[node];
    }
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        cache_map node_map;
        node_map[NULL] = NULL;
        return doCloneGraph(node_map, node);
    }
};
