/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mtrie.cpp
 * Author: kcy
 * 
 * Created on 2016年11月14日, 上午8:43
 */

#include "mtrie.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

template<typename OBJ>
mtrie_t() 
:objects(NULL)
,refcnt(0)
,min(0)
,count(0)
,live_nodes(0)
{
}

template<typename OBJ>
~mtrie_t() {
    if(objects)
    {
        delete objects;
        objects = NULL;
    }
    
    
}

template<typename OBJ>
bool add(unsigned char* prefix_, size_t size_, OBJ* object_)
{
    return add_helper(prefix_, size_, object_);
}

bool mtrie_t::add(int prefix_, OBJ* object_)
{
    return add_helper((unsigned char*)&prefix_, sizeof(prefix_), object_);
}

bool mtrie_t::add_helper(unsigned char* prefix_, size_t size_, OBJ* object_)
{
    // We are at the node corresponding to the prefix. We are done.
    if(!size_)
    {
        bool result = !objects;
        if(!objects)
        {
            objects = new (std::nothrow) objects_t;
            assert(objects);
        }
        if(object_)
            objects->insert(object_);
        ++refcnt;
        return result;
    }
    
    unsigned char c = *prefix_;
    if(c < min || c >= min + count)
    {
        //字符超出数组范围，需要扩展
        if(!count)
        {
            min = c;
            count = 1;
            next.node = NULL;
        } else if(count == 1)
        {
            unsigned char oldc = min;
            mtrie_t *oldp = next.node;
            count = (min < c ? c - min : min -c) + 1;
            next.table = (mtrie_t**) malloc (sizeof(mtrie_t*) * count);
            assert(next.table);
            for(unsigned short i = 0; i != count; ++i)
            {
                next.table[i] = 0;
            }
            min = std::min(min,c);
            next.table[oldc - min] = oldp;
            
        } else if(min < c)
        {
            unsigned short old_count = count;
            count = c - min + 1;
            next.table = (mtrie_t**) realloc (next.table, sizeof(mtrie_t*) * count);
            assert(next.table);
            for(unsigned short i = old_count; i != count; i++)
            {
                next.table[i] = NULL;
            }
            
        } else
        {
            unsigned short old_count = count;
            count = (min + old_count) - c;
            next.table = (mtrie_t**) realloc(next.table, sizeof(mtrie_t*) * count);
            assert(next.table);
            memmove(next.table + min - c, next.table, old_count * sizeof(mtrie_t*));
            for(unsigned short i = 0; i != min - c; i ++)
            {
                next.table[i] = NULL;
            }
            min = c;
        }
    }
    
    //创建下一个node 如果存在
    if(count == 1)
    {
        if(!next.node)
        {
            next.node = new (std::nothrow) mtrie_t;
            assert(next.node);
            ++live_nodes;
        }
        return next.node->add_helper(prefix_ + 1, size_ -1, object_);
    } else
    {
        if(!next.table[c - min])
        {
            next.table[c - min] = new (std::nothrow) mtrie_t;
            assert(next.table[c - min]);
            ++live_nodes;
        }
        return next.table[c - min]->add_helper(prefix_ + 1, size_ - 1, object_);
    }
}

void mtrie_t::match(unsigned char* data_, size_t size, void(*func_)(object*,void*), void* arg_)
{
    
}

bool mtrie_t::check(unsigned char* data_, size_t size_)
{
    mtrie_t *current = this;
    while(true)
    {
        if(current->refcnt)
            return true;
        if(!size_)
            return false;
        
        unsigned char c = *data_;
        if(c < current->min || c >= current->min + current->count)
            return false;
        
        if(current->count == 1)
            current = current->next.node;
        else
        {
            current = current->next.table[c - current->min];
            if(!current)
                return false;
        }
        data_++;
        size_--;
    }
}