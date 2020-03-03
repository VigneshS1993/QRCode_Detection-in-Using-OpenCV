#ifndef PUBLISHINGNODE_H
#define PUBLISHINGNODE_H

#include <vector>
#include <memory>
#include <algorithm>

#include "publisherservice.h"

class PublishingNode
{
public:
    explicit PublishingNode() = default;
    void setPublisherState(int id, PublisherService::State state, unsigned int period = 0);
    void addPublisher(std::unique_ptr<PublisherService> service);
private:
    std::vector< std::unique_ptr<PublisherService> > _services;
};

#endif // PUBLISHINGNODE_H
