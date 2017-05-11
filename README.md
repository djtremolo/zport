# Overview of the *zport* protocol
## Background
The *zport* module works as OSI L4 Transport protocol for embedded systems. It provides user message fragmentation and re-ordering of fragments at the receiving end. The *zport* library is intentionally kept as minimal as possible, mostly because of memory footprint and CPU load issues on smaller systems.

Typically, the *zport* layer is used as bi-directional session between two endpoints. By using *zport* together with *zchannel* module, multi-node networks can be supported by allowing multiple, separately buffered messaging channels to share one *zport* instance.

## Concept
The *zport* can be seen loosely combining the idea of partial message transfers used in various p2p networks with the typical behaviour of simple file transfer protocols based on the sliding window principle. In *zport*, the message parts (known as *fragments*) can be sent in any order, and missing some parts does not cause resending of the parts that are correctly received earlier.

The protocol uses 8-bit bytes and does not use any special transcoding of transferred bytes. It is based on pre-defined message frame structure that can be transparently used with any kind of user payload. 

The nodes communicating with each other must be cofigured similarly. For example, the maximum length for user message of the sender instance cannot exceed the receivers capability. At first stage, this configuration is made hard-coded, but will be negotiated in the conection set-up phase in the further protocol versions. 

## Interfaces
The *zport* instance fetches the upper layer message frames from the *session* layer (OSI L5) using the provided target adaptation interface. The protocol uses *network* layer (OSI L3) for sending/receiving protocol messages (containing fragments of the user messages with some protocol status information).

# User Interface
## zportCreate
This function creates a new *zport* instance. The instances are stored in a fixed-size pool so no dynamic memory allocation is done. Returns the handle to the created *zport* instance. The handle can then be used by calling its member functions.
```c
#include "zport.h"

void foo()
{
    zport_t* const zp = zportCreate(0);

    if(zp != NULL)
    {
        uint8_t* msg;
        uint16_t maxLen;
        const zportZeroCopyHandle_t zcHnd = nodeA->zcReserve(nodeA, &msg, &maxLen);

        if(zcHnd != NULL)
        {
            /*TODO: fill in the message payload in msg, as much as maxLen bytes*/
            /* ... */

            /*send message*/
            nodeA->zcSend(nodeA, zcHnd);
        }
    }
}
```

## zcReserve
This method reserves a message slot from the internal pool and returns the handle to it. The handle must then be used when sending or releasing the message for reusing. The message payload pointer and maximum payload size is returned via the parameters.

## zportPutMessage


# Functionality
The *zport* protocol uses just one symmetrical message frame for transferring data between the endpoints. Neither one of them is master or slave. The message acknowledgments are sent using the same message type (if there is no user data to be sent, the payload is left empty).

On TX side, the *zport* runs the following process:
* fetches a message from the user side (`zportReserveMessage`)
    * the user side must consider this message being locked until the `zportReleaseMessage` is called. 
* determines how many fragments are needed to send this message over
* marks all fragments with a *dirty* flag
* send first *dirty* fragment with the header that provides the following information:
    * current fragment id
    * total number of fragments
    * *dirty* fragment bitmask for the another endpoint
* after none of the fragments are not dirty anymore, the message is considered done
    * the *zport* calls the `zportReleaseMessage` function to allow the buffer to be reused by the user

On the RX side, the following process is run for each incoming message:
* update own *dirty* fragment bitmask with the information coming from the another endpoint (acknowledgement)
* if the incoming message contains a payload
    * push the fragment into a receiving buffer
    * update dirty *flags* for another endpoint


# Use cases
