/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pipe.h
 * Author: kcy
 *
 * Created on 2016年10月14日, 上午10:16
 */

#ifndef PIPE_H
#define PIPE_H

#include "ypipe_base.h"
#include <stdint.h>
#include "array.h"
#include "blob.h"


class object_t;
class pipe_t;

int pipepair(object_t* parents_[2],pipe_t* pipes_[2], int hwms_ [2], bool conflate_[2]);

struct i_pipe_events
{
    virtual ~i_pipe_events(){}
    
    virtual void read_activated(pipe_t *pipe_) = 0;
    virtual void write_activated(pipe_t *pipe_) = 0;
    virtual void hiccuped(pipe_t *pipe_) = 0;
    virtual void pipe_terminated(pipe_t *pipe_) = 0;
};

class pipe_t : public array_item_t<1>, public array_item_t<2>, public array_item_t<3>

{

    friend int pipepair(object_t* parents_[2],pipe_t* pipes_[2], int hwms_ [2], bool conflate_[2]);
public:
    

    
    void set_event_sink(i_pipe_events *sink_);
    
    void set_identity(const blob_t &identity_);
    blob_t get_identity();
    
    bool check_read();
    
    bool read(blob_t);
    
    bool check_write();
    
    bool write(blob_t);
    
    void rollback();
    
    void flush();
    
    void hiccup();
    
    void set_nodelay();
    
    void terminate(bool delay_);
    
    void set_hwms(int inhwm_, int outhwm_);
    
private:
    
    typedef ypipe_base_t<blob_t,256> upipe_t;
    
    //Command handlers;
    void process_activate_read();
    
    
    
    void process_delimiter();
    
    pipe_t(object_t *parent_, upipe_t *inpipe_, upipe_t *outpipe_,
            int inhwm_, int outhwm_, bool conflate_);
    
    void set_peer(pipe_t *pipe_);

    ~pipe_t();
    
    
    //Can the pipe be read from / written to?
    bool in_active;
    bool out_active;
    
    //High watermark for the outbound pipe.
    int hwn;
    //Low watermark for ...
    int lwm;
    
    //Number of messages read and written so far.
    uint64_t msgs_read;
    uint64_t msgs_written;
    
    uint64_t peers_msgs_read;
    
    //The pipe object on the other side of the pipepair.
    pipe_t *peer;
    
    //Sink to send events to.
    i_pipe_events *sink;
    
    enum {
        active,
        delimiter_received,
        waiting_for_delimiter,
        term_ack_sent,
        term_req_sent1,
        term_req_set2
    }state;

    
    bool delay;
    
    blob_t identity;
    
    static bool is_delimiter(blob_t &msg_);
    static int compute_lwm(int hwm_);
    bool conflate;
    
};

#endif /* PIPE_H */

