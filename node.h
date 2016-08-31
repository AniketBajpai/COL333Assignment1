//
// Created by root on 31/8/16.
//

#ifndef COL333ASSIGNMENT1_NODE_H
#define COL333ASSIGNMENT1_NODE_H

#define max 10000
struct node // bid node structure
{
    int cid; //company
    double price;
    int norc;  // no. of regions in one bid
    int region[max];
};

#endif //COL333ASSIGNMENT1_NODE_H
