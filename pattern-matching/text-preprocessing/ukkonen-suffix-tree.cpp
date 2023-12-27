#include <iostream>
#include <climits>
using namespace std;

struct SuffixTreeNode {
    SuffixTreeNode *children[CHAR_MAX];
    SuffixTreeNode *suffixLink;
    int start;
    int *end;
    int suffixIndex;
    
    SuffixTreeNode(int startGiven, int *endGiven, SuffixTreeNode *root) {
        for (char i = 0; i < CHAR_MAX; ++i) {
            children[i] = nullptr;
        }
        suffixLink = root;
        start = startGiven;
        end = endGiven;
        suffixIndex = -1;
    }
};

int edgeLength(SuffixTreeNode *node) {
    return *(node->end) - node->start + 1;
}

bool walkdown(SuffixTreeNode *currNode, int *activeLength, char *activeEdge,
    SuffixTreeNode **activeNode, const string & text) {
    if (*activeLength >= edgeLength(currNode)) {
        *activeEdge = text[*activeEdge + edgeLength(currNode)] - ' ';
        *activeLength -= edgeLength(currNode);
        *activeNode = currNode;
        return true;
    }
    return false;
}

void extendSuffixTree(int i, int *remainingSuffixCount, int *activeLength, char *activeEdge,
    SuffixTreeNode **activeNode, SuffixTreeNode *root, SuffixTreeNode **lastNewNode,
    int **splitEnd, int *leafEnd, const string &text) {
    *leafEnd = i;
    ++*remainingSuffixCount;
    while (*remainingSuffixCount > 0) {
        if (*activeLength == 0) {
            *activeEdge = text[i] - ' ';
        }
        if ((*activeNode)->children[*activeEdge] == nullptr) {
            (*activeNode)->children[*activeEdge] = new SuffixTreeNode(i, leafEnd, root);
            if (*lastNewNode != nullptr) {
                (*lastNewNode)->suffixLink = *activeNode;
                *lastNewNode = nullptr;
            }
        } else {
            SuffixTreeNode *next = (*activeNode)->children[*activeEdge];
            if (walkdown(next, activeLength, activeEdge, lastNewNode, text)) {
                continue;
            }
            if (text[next->start + *activeLength] == text[i]) {
                if (*lastNewNode != nullptr && *activeNode != root) {
                    (*lastNewNode)->suffixLink = *activeNode;
                    *lastNewNode = nullptr;
                }
                ++*activeLength;
                break;
            }
            *splitEnd = new int(next->start + *activeLength - 1);
            SuffixTreeNode *split = new SuffixTreeNode(next->start, *splitEnd, root);
            (*activeNode)->children[*activeEdge] = split;
            split->children[text[i] - ' '] = new SuffixTreeNode(i, leafEnd, root);
            next->start += *activeLength;
            split->children[*activeEdge] = next;
            if (*lastNewNode != nullptr) {
                (*lastNewNode)->suffixLink = split;
            }
            *lastNewNode = split;
        }
        --*remainingSuffixCount;
        if (*activeNode == root && *activeLength > 0) {
            --*activeLength;
            *activeEdge = text[i - *remainingSuffixCount + 1] - ' ';
        } else if (*activeNode != root) {
            *activeNode = (*activeNode)->suffixLink;
        }
    }
}

void setSuffixIndexByDFS(SuffixTreeNode *node, int labelHeight, const string &text) {
    if (node == nullptr) {
        return;
    }
    int leaf = 1;
    for (char i = 0; i < CHAR_MAX; ++i) {
        if (node->children[i] != nullptr) {
            leaf = 0;
            setSuffixIndexByDFS(node->children[i], labelHeight + edgeLength(node->children[i]),
                text);
        }
    }
    if (leaf == 1) {
        node->suffixIndex = text.length() - labelHeight;
    }
}

void freeSuffixTreeByPostOrder(SuffixTreeNode *node) {
    if (node == nullptr) {
        return;
    }
    for (char i = 0; i < CHAR_MAX; ++i) {
        if (node->children[i] != nullptr) {
            freeSuffixTreeByPostOrder(node->children[i]);
        }
    }
    if (node->suffixIndex == -1) {
        delete node->end;
    }
    delete node;
}

int traverseEdge(const string &pattern, int i, int start, int end) {
    for (int j = start; j <= end && i < pattern.length(); ++j, ++i) {
        if (pattern[j] != pattern[i]) {
            return -1;
        }
    }
    if (i == pattern.length()) {
        return 1;
    }
    return 0;
}

bool searchSuffixTree(SuffixTreeNode *node, const string &pattern, int i = 0) {
    if (node == nullptr) {
        return false;
    }
    if (node->start != -1) {
        int res = traverseEdge(pattern, i, node->start, *node->end);
        if (res == -1) {
            return false;
        }
        if (res == 1) {
            return true;
        }
    }
    i += edgeLength(node);
    if (node->children[pattern[i]] != nullptr) {
        return searchSuffixTree(node->children[pattern[i]], pattern, i);
    } else {
        return false;
    }
}

void buildSuffixTree(const string &text, SuffixTreeNode **root) {
    int *rootEnd = new int(-1);
    *root = new SuffixTreeNode(-1, rootEnd, nullptr);
    int remainingSuffixCount = 0;
    SuffixTreeNode *activeNode = *root;
    SuffixTreeNode *lastNewNode = nullptr;
    int count = 0;
    char activeEdge = -1;
    int activeLength = 0;
    int *splitEnd = nullptr;
    int leafEnd = 0;
    for (int i = 0; i < text.length(); ++i) {
        extendSuffixTree(i, &remainingSuffixCount, &activeLength, &activeEdge,
            &activeNode, *root, &lastNewNode, &splitEnd, &leafEnd, text);
    }
    setSuffixIndexByDFS(*root, 0, text);
}

int main() {
    string text = "ASFAINASFPINASFDPSAIBFPISABFB";
    string pattern = "SFPI";
    SuffixTreeNode *root;
    buildSuffixTree(text, &root);
    cout << searchSuffixTree(root, pattern) << endl;
    freeSuffixTreeByPostOrder(root);
    return 0;
}