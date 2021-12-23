#include <iostream>

using namespace std;

class TrieNode;

class Node;

void Print(Node *head);

/// linked list
class Node {
public:
    Node *nextNode;
    TrieNode *value;

    Node(TrieNode *curr) {
        value = curr;
    }

    Node() {
        nextNode = nullptr;
        value = nullptr;
    }
};


/// tree
class TrieNode {
public:
    int id;
    char next;
    Node *head;
    Node *tail;

    TrieNode() {
        id = -1;
        next = 0;
        head = nullptr;
        tail = nullptr;
    }

    TrieNode(int i, char nxt) {
        id = i;
        next = nxt;

    }

    Node *insertLast(Node *newNode) {
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->nextNode = newNode;
            tail = newNode;
            tail->nextNode = nullptr;
        }
        return tail;
    }

    void print() {
        Print(this->head);
    }
};


class SuffixTrie {
public:
    SuffixTrie(char *word) {
        int r;
        for (r = 0; word[r]; r++);
        root = new TrieNode();
        Suffix(0, r, word);
    }

    void Suffix(int l, int r, char *word) {
        if (l != r) {
            TrieNode *level = root;
            Node *curr = root->head;
            for (int i = l; i < r; i++) {

                bool found = 0;

                while (true) {
                    if (curr == nullptr)
                        break;

                    if (curr->value != nullptr && curr->value->next == word[i]) {
                        level = curr->value;
                        curr = level->head;
                        found = 1;
                        break;
                    }

                    if (curr->nextNode != nullptr)
                        curr = curr->nextNode;
                    else
                        break;
                }

                if (!found) {
                    curr = level->insertLast(new Node(new TrieNode((l + 1) * (i == r - 1) - 1, word[i])));
                    level = curr->value;
                }

            }
            Suffix(l + 1, r, word);
        }
    }

    void Search(char *word) {
        search(0, word, root, root->head);
        cout << '\n';
    }

    void search(int l, char *word, TrieNode *level, Node *curr) {
        while (true) {
            if (curr->value != nullptr && curr->value->next == word[l]) {
                if (word[l + 1]) {
                    level = curr->value;
                    curr = level->head;
                    search(l + 1, word, level, curr);
                } else {
                    level = curr->value;
                    level->print();
                }
                return;
            }
            if (curr->nextNode != nullptr)
                curr = curr->nextNode;
            else
                return;
        }
    }

    TrieNode *root;
};

void Print(Node *head) {
    if (head != nullptr) {
        Node *ptr = head;
        while (true) {
            ptr->value->print();
            if (ptr->nextNode != nullptr)
                ptr = ptr->nextNode;
            else {
                if (ptr->value->id != -1)
                    cout << ptr->value->id << ' ';
                return;
            }
        }
    }
}

int main() {
    // Construct a suffix trie containing all suffixes of "bananabanaba$"

    //            0123456789012
    SuffixTrie t("bananabanaba$");

    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8

    return 0;
}