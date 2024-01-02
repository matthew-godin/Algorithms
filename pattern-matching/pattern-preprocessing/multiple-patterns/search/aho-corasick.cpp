#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

struct AhoCorasickNode {
    map<char, AhoCorasickNode*> edges;
    vector<bool>* patternsMatched;
    AhoCorasickNode* failNode = nullptr;
    bool isRoot;

    AhoCorasickNode(int numPatterns, bool root = false) {
        patternsMatched = new vector<bool>(numPatterns, false);
        isRoot = root;
    }
};

class AhoCorasickTrie {
    AhoCorasickNode* root;
    vector<string> myPatterns;

    void clearRecursion(AhoCorasickNode* currentNode) {
        for (auto iter = currentNode->edges.begin();
            iter != currentNode->edges.end(); ++iter) {
            clearRecursion(currentNode->edges[iter->first]);
        }
        delete currentNode;
    }

public:
    AhoCorasickTrie(vector<string> patterns) {
        myPatterns = patterns;
        root = new AhoCorasickNode(patterns.size(), true);
        AhoCorasickNode* currentNode;
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
            currentNode = BFSQueue.front();
            BFSQueue.pop();
            for (auto iter = currentNode->edges.begin();
                iter != currentNode->edges.end(); ++iter) {
                AhoCorasickNode* failNode = currentNode->failNode;
                while (failNode->edges.find(iter->first) == failNode->edges.end()) {
                    if (failNode->isRoot) {
                        currentNode->edges[iter->first]->failNode = root;
                        BFSQueue.push(currentNode->edges[iter->first]);
                        goto AhoCorasickTrieL1;
                    }
                    failNode = failNode->failNode;
                }
                failNode = failNode->edges[iter->first];
                currentNode->edges[iter->first]->failNode = failNode;
                for (int i = 0; i < patterns.size(); ++i) {
                    (*currentNode->edges[iter->first]->patternsMatched)[i]
                        = (*currentNode->edges[iter->first]->patternsMatched)[i]
                        || (*failNode->patternsMatched)[i];
                }
                BFSQueue.push(currentNode->edges[iter->first]);
                AhoCorasickTrieL1: ;
            }
        }
    }

    void search(string text) {
        AhoCorasickNode* currentNode = root;
        for (int i = 0; i < text.length(); ++i) {
            while (currentNode->edges.find(text[i]) == currentNode->edges.end()) {
                if (currentNode->isRoot) {
                    goto searchL1;
                }
                currentNode = currentNode->failNode;
            }
            cout << text[i] << " " << (*currentNode->patternsMatched)[0]
                << " " << (*currentNode->patternsMatched)[1]
                << " " << (*currentNode->patternsMatched)[2]
                << " " << (*currentNode->patternsMatched)[3] << endl;
            for (int j = 0; j < currentNode->patternsMatched->size(); ++j) {
                if ((*currentNode->patternsMatched)[j]) {
                    cout << "Found " << myPatterns[j] << endl;
                }
            }
            currentNode = currentNode->edges[text[i]];
            searchL1: ;
        }
    }

    void clear() {
        clearRecursion(root);
    }
};

int main() {
    vector<string> patterns = { "he", "she", "his", "hers" };
    AhoCorasickTrie ahoCorasickTrie(patterns);
    
    //ahoCorasickTrie.search("ahishers");
    ahoCorasickTrie.clear();

    return 0;
}