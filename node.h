//
// Created by root on 31/8/16.
//

#define maxR 10000
#ifndef COL333ASSIGNMENT1_NODE_H
#define COL333ASSIGNMENT1_NODE_H

struct node // bid node structure
{
    int cid; //company
    double price;
    int norc;  // no. of regions in one bid
    int region[maxR];
};

#endif //COL333ASSIGNMENT1_NODE_H
