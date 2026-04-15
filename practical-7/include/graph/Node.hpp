#ifndef NODE_H
#define NODE_H

namespace graph
{
    template <typename RecordType>
    struct Node
    {
        /** @todo I can probably add some metadata here so that it's not just an unncessary wrapper **/
        const RecordType *record;
    };

}

#endif