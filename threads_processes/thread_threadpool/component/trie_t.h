/* 
 * File:   trie_t.h
 * Author: kcy
 *
 * Created on 2016年4月21日, 上午9:47
 */

#ifndef TRIE_T_H
#define	TRIE_T_H
#include <stdint.h>
#include <stddef.h>

//一个简单高效用于实现“订阅”功能的树型结构
class trie_t {
public:
    trie_t();
    virtual ~trie_t();
    
    bool add(unsigned char *prefix_, size_t size_);
    //bool rm(unsigned char *prefix_, size_t size_);
    bool check(unsigned char*data_, size_t size_);
    //void apply(void(*func)(unsigned char *data_,size_t size_, void *arg_), void *arg_  );
    
private:
    
    //void apply_helper(
    //        unsigned char **buff_, size_t buffsize_, size_t maxbuffsize_, 
    //        void(*func_)(unsigned char *data_,size_t size_, void *arg_),
    //        void *arg_);
    //bool is_redundant() const;
    
    uint32_t refcnt;
    unsigned char min;
    unsigned short count;
    unsigned short live_nodes;
    union {
        class trie_t *node;
        class trie_t **table;
    } next;

};

#endif	/* TRIE_T_H */

