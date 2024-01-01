#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

struct AhoCorasickNode {
    map<char, AhoCorasickNode*> edges;
    vector<bool> *patternsMatched;
    AhoCorasickNode *failNode = nullptr;
    bool isRoot;
    
    AhoCorasickNode(int numPatterns, bool root = false) {
        patternsMatched = new vector<bool>(numPatterns, false);
        isRoot = root;
    }
};

class AhoCorasickTrie {
    AhoCorasickNode *root;
    vector<string> myPatterns;
    
    public:
        AhoCorasickTrie(vector<string> patterns) {
            myPatterns = patterns;
            root = new AhoCorasickNode(patterns.size(), true);
            AhoCorasickNode *currentNode;
            for (int i = 0; i < patterns.size(); ++i) {
                currentNode = root;
                for (int j = 0; j < patterns[i].length(); ++j) {
                    if (currentNode->edges.find(patterns[i][j]) == currentNode->edges.end()) {
                        currentNode->edges[patterns[i][j]] = new AhoCorasickNode(patterns.size());
                    }
                    currentNode = currentNode->edges[patterns[i][j]];
                }
                (*currentNode->patternsMatched)[i] = true;
            }
            queue<AhoCorasickNode*> BFSQueue;
            for (auto iter = root->edges.begin(); iter != root->edges.end(); ++iter) {
                BFSQueue.push(root->edges[iter->first]);
                root->edges[iter->first]->failNode = root;
            }
            while (BFSQueue.size() > 0) {
                currentNode = BFSQueue.pop();
                for (auto iter = currentNode->edges.begin();
                    iter != currentNode->edges.end(); ++iter) {
                        AhoCorasickNode *failNode = currentNode->failNode;
                        while (failNode->edges.find(iter->first) == failNode->edges.end()) {
                            failNode = failNode->failNode;
                        }
                        failNode = failNode->edges[iter->first];
                        currentNode->edges[iter->first]->failNode = failNode;
                        for (int i = 0; i < patterns.size(); ++i) {
                            currentNode->edges[(*iter->first]->patternsMatched)[i]
                                = (*currentNode->edges[iter->first]->patternsMatched)[i]
                                    || (*failNode->patternsMatched)[i];
                        }
                        BFSQueue.push(currentNode->edges[iter->first]);
                }
            }
        }
};

int main() {
    vector<string> patterns = { "he", "she", "his", "hers" };
    AhoCorasickTrie ahoCorasickTrie(patterns);
    
    return 0;
}