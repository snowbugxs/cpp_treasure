/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.c
 * Author: kcy
 *
 * Created on 2016年12月26日, 下午3:23
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "mtrie.h"

/*
 * Simple C++ Test Suite
 */

class object {
    public:
    int i ;
};

int main(int argc, char** argv) {
    object ob;
    ob.i = 100;
    mtrie_t<object> trie;
    trie_map<object> trie_m;
    bool b = trie_m.add("test",&ob);
    bool c = trie_m.check("test");
    object *pob = new object();
    bool d = trie.add((unsigned char*)"test",4,pob);
    d = trie.rm((unsigned char*)"test",4,pob);
    int i = 12536789;
    //trie.add((unsigned char*)&i,sizeof(i),&ob);
    //trie.add(12536789,&ob);
    
    unsigned char *p = (unsigned char*)&i;
    
    unsigned char o = i;
    int size = sizeof(i);
    for(int c = 0; c < size; c++,p++)
    {
        printf("%d \n",*p);
        printf("%d \n",o);
        o = (i >> (4 + c*4)) & 0b00001111;
    }
    

    return (EXIT_SUCCESS);
}

