/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mtrie_imp.h
 * Author: kcy
 *
 * Created on 2016年12月27日, 下午2:24
 */

#ifndef MTRIE_IMP_H
#define MTRIE_IMP_H
#include "mtrie.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>




template<class OBJ>
mtrie_t<OBJ>::mtrie_t() 
:objects(NULL)
,refcnt(0)
,min(0)
,count(0)
,live_nodes(0)
{
}

template<class OBJ>
mtrie_t<OBJ>::~mtrie_t() {
    if(objects)
    {
        delete objects;
        objects = NULL;
    }
    
    
}

template<class OBJ>
bool mtrie_t<OBJ>::add(unsigned char* prefix_, size_t size_, OBJ* object_)
{
    return add_helper(prefix_, size_, object_);
}

//template<class OBJ>
//bool mtrie_t<OBJ>::add(int prefix_, OBJ* object_)
//{
//    return add_helper((unsigned char*)&prefix_, sizeof(prefix_), object_);
//}

template<class OBJ>
bool mtrie_t<OBJ>::add_helper(unsigned char* prefix_, size_t size_, OBJ* object_)
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

template<class OBJ>
void mtrie_t<OBJ>::match(unsigned char* data_, size_t size, void(*func_)(OBJ*,void*), void* arg_)
{
    
}

template<class OBJ>
bool mtrie_t<OBJ>::check(unsigned char* data_, size_t size_)
{
    mtrie_t *current = this;
    while(true)
    {
        if(current->refcnt && !size_)
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

template<class OBJ>
bool mtrie_t<OBJ>::rm(unsigned char* prefix_, size_t size_, OBJ* object)
{
    return rm_helper(prefix_,size_,object);
}

template<class OBJ>
bool mtrie_t<OBJ>::rm_helper(unsigned char* prefix_, size_t size_, OBJ* object_)
{
    if(!size_)
    {
        if(objects)
        {
            //int erased = objects->erase(object_);
            //assert(erased == 1);
            objects->clear();
            if(objects->empty()) {
                delete objects;
                objects = 0;
            }
        }
        return !objects;
    }
    unsigned char c = *prefix_;
    if (!count || c < min || c >= min + count)
        return false;

    mtrie_t *next_node =
        count == 1 ? next.node : next.table [c - min];

    if (!next_node)
        return false;

    bool ret = next_node->rm_helper (prefix_ + 1, size_ - 1, object_);

    if (next_node->is_redundant ()) {
        delete next_node;
        assert (count > 0);

        if (count == 1) {
            next.node = 0;
            count = 0;
            --live_nodes;
            assert (live_nodes == 0);
        }
        else {
            next.table [c - min] = 0;
            assert (live_nodes > 1);
            --live_nodes;

            //  Compact the table if possible
            if (live_nodes == 1) {
                //  If there's only one live node in the table we can
                //  switch to using the more compact single-node
                //  representation
                unsigned short i;
                for (i = 0; i < count; ++i)
                    if (next.table [i])
                        break;

                assert (i < count);
                min += i;
                count = 1;
                mtrie_t *oldp = next.table [i];
                free (next.table);
                next.node = oldp;
            }
            else
            if (c == min) {
                //  We can compact the table "from the left"
                unsigned short i;
                for (i = 1; i < count; ++i)
                    if (next.table [i])
                        break;

                assert (i < count);
                min += i;
                count -= i;
                mtrie_t **old_table = next.table;
                next.table = (mtrie_t**) malloc (sizeof (mtrie_t*) * count);
                assert (next.table);
                memmove (next.table, old_table + i, sizeof (mtrie_t*) * count);
                free (old_table);
            }
            else
            if (c == min + count - 1) {
                //  We can compact the table "from the right"
                unsigned short i;
                for (i = 1; i < count; ++i)
                    if (next.table [count - 1 - i])
                        break;

                assert (i < count);
                count -= i;
                mtrie_t **old_table = next.table;
                next.table = (mtrie_t**) malloc (sizeof (mtrie_t*) * count);
                assert (next.table);
                memmove (next.table, old_table, sizeof (mtrie_t*) * count);
                free (old_table);
            }
        }
    }

    return ret;
}


template<class OBJ>
bool mtrie_t<OBJ>::is_redundant() const
{
    return !objects && live_nodes == 0;
}

#endif /* MTRIE_IMP_H */

