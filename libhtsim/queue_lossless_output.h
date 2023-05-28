// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-        
#ifndef _LOSSLESS_OUTPUT_QUEUE_H
#define _LOSSLESS_OUTPUT_QUEUE_H
/*
 * A FIFO queue that supports PAUSE frames and lossless operation
 */

#include <list>
#include "queue.h"
#include "config.h"
#include "eventlist.h"
#include "network.h"
#include "loggertypes.h"
#include "eth_pause_packet.h"
#include "ecn.h"

class LosslessOutputQueue : public Queue {
 public:
    LosslessOutputQueue(linkspeed_bps bitrate, mem_b maxsize, EventList &eventlist, QueueLogger* logger, int ECN=0, int K=0);

    void receivePacket(Packet& pkt);
    void receivePacket(Packet& pkt,VirtualQueue* q);

    void beginService();
    void completeService();

    enum {PAUSED,READY,PAUSE_RECEIVED};

 private:
    list<VirtualQueue*> _vq;

    int _state_send;
    int _sending;

    int _ecn_enabled;
    int _K;
};

#endif
