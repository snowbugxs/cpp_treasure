/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mtrie.h
 * Author: kcy
 *
 * Created on 2016年11月14日, 上午8:43
 */

#ifndef MTRIE_H
#define MTRIE_H
#include <stddef.h>
#include <set>
#include <string.h>
#include <stdint.h>


template<class OBJ>
class mtrie_t {
public:
    mtrie_t();
    virtual ~mtrie_t();
    
    // Add key to the trie. Returns true if it's a new subscription.
    bool add(unsigned char *prefix_, size_t size_, OBJ *object_ = NULL);

    //Remove all subscription
    void rm(OBJ *object_, 
            void (*func_) (unsigned char *data_, size_t size, void *arg_),
            void *arg_);
    bool rm(unsigned char *prefix_, size_t size_, OBJ *object = NULL);
    
    // Signal all the matching objects.
    void match(unsigned char *data_, size_t size,
            void (*func_) (OBJ *object_, void *arg_),
            void *arg_);
    
    bool check(unsigned char* data_, size_t size_);
protected:
    bool add_helper(unsigned char *prefix_, size_t size_, OBJ *object_);
    
    void rm_helper(OBJ *object_, unsigned char **buff_, size_t buffsize_, size_t maxbuffsize_,
                    void (*func_) (unsigned char *data_, size_t size_, void *arg_),
                    void *arg_);
    
    bool rm_helper(unsigned char *prefix_, size_t size_, OBJ *object_);
    bool is_redundant() const;
    
private:
    typedef std::set<OBJ*> objects_t;
    objects_t *objects;

    
    uint32_t refcnt;
    unsigned char min;
    unsigned short count;
    unsigned short live_nodes;
    union {
        class mtrie_t *node;
        class mtrie_t **table;
    }next;
};

#include "mtrie_imp.h"

template<class OBJ>
class trie_map : public mtrie_t<OBJ> {
public:
    bool add(unsigned char *key_,  OBJ *object_ = NULL) {
        return add_helper(key_, strlen((const char*)key_), object_);
    }
    bool add(const char *key_, OBJ *object_ = NULL) {
        return add_helper((unsigned char*)key_, strlen(key_), object_);
    }
    
    bool check(const char* key_) {
        return mtrie_t<OBJ>::check((unsigned char*)key_, strlen(key_));
    }
};

template<typename key_type, class OBJ>
class value_map : public mtrie_t<OBJ> {
public:
    bool add(key_type key_value_, OBJ *object_ = NULL) {
        return add_helper((unsigned char*)&key_value_, sizeof(key_type), object_);
    }
    
    bool check(key_type key_value_) {
        return mtrie_t<OBJ>::check((unsigned char*)&key_value_, sizeof(key_type));
    }
};

#endif /* MTRIE_H */

