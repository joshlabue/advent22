#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>    

const int maxSize = 100000;

enum FSNodeType {
    File, Folder
};

/*
File System Node
    name: The relative name of the node
    type: The type that the node is, either File or Folder
    size: The size of the file, or size of the folder's child nodes
    contents: List of child File/Folder nodes
    parent: Pointer to the node's parent node
*/
struct FSNode {
    std::string name = "/";
    FSNodeType type = Folder;
    int size = 0;
    std::vector<FSNode> contents;
    FSNode* parent = nullptr;
};

/*
Search a Folder node for a child with a given name.
Returns a pointer to said child if it is found.
*/
FSNode* searchDir(FSNode* workingDir, std::string name) {
    for(int i = 0; i < workingDir->contents.size(); i++) {
        if(workingDir->contents.at(i).name == name) return &workingDir->contents.at(i);
    }

    return nullptr;
}

/*
Recurse through the tree of nodes, calculating the size of each folder.
*/
void computeNodeSize(FSNode* node) {
    if(node->type == Folder) {
        for(int i = 0; i < node->contents.size(); i++) {
            computeNodeSize(&node->contents.at(i));
        }

        if(node->parent != nullptr) node->parent->size += node->size;
    }
    else if(node->type == File) {
        node->parent->size += node->size;
    }

    return;
}

/*
Recursively step through the tree of nodes, adding the size of each Folder that is smaller than a given amount.
*/
int sumFilteredFolders(FSNode* node, int size) {
    int output = 0;
    if(node->type == Folder) {
        for(int i = 0; i < node->contents.size(); i++) {
            output += sumFilteredFolders(&node->contents.at(i), size);

            if(node->contents.at(i).size < size && node->contents.at(i).type == Folder) {
                output += node->contents.at(i).size;
            }
        }
    }
    return output;
}

int main() {
    std::ifstream input("input.txt");
    std::string terminal;

    /*
    Top level node of the Filesystem tree.
    All subsequence nodes are children of this one.
    */
    FSNode root;

    /*
    Pointer to current folder node.
    */
    FSNode* workingDir = &root;

    while(!input.eof()) {
        input >> terminal;
        
        /*
        Parse the line of text.
        First determine if it is a command, or a directory listing.
        */
        if(terminal == "$") {
            input >> terminal;
            // If it is just an ls command, move to the next line since that's where the information is.
            if(terminal == "ls") {
                continue;
            }
            // If it is a cd command, change the working directory to the target location
            else if(terminal == "cd") {
                input >> terminal;

                if(terminal == "/") workingDir = &root;
                // If the directory is .. then move up a directory to the node's parent.
                else if(terminal == "..") workingDir = workingDir->parent;
                // Otherwise, search the node's children for a node with the name given
                else workingDir = searchDir(workingDir, terminal);
            }
        }
        /*
        If the line contains a size, it must be a file.
        Create a file node and add it to the current node's children.
        */
        else if(atoi(terminal.c_str()) > 0) {
            FSNode file = {
                .type = File,
                .size = atoi(terminal.c_str()),
                .parent = workingDir
            };

            input >> terminal;

            file.name = terminal;

            workingDir->contents.push_back(file);
        }
        /*
        If the line starts with "dir", it is a folder.
        Create a folder node and add it to the current node's children.
        */
        else if(terminal == "dir") {
            input >> terminal;
            FSNode folder = {
                .name = terminal,
                .type = Folder,
                .parent = workingDir
            };

            workingDir->contents.push_back(folder);
        }
    }

    /*
    Once the file structure has been generated, go back through the fs and calculate the size of each folder
    */
    computeNodeSize(&root);

    /*
    Take the sum of the sizes of all folders with size < 1000
    */
    int output = sumFilteredFolders(&root, maxSize);
    printf("%d\n", output);

    return 0;
}