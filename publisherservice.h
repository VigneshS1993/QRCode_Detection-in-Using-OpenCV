#ifndef PUBLISHERSERVICE_H
#define PUBLISHERSERVICE_H

#include <thread>
#include <memory>
#include <vector>
#include <chrono>

class PublisherService
{
public:
    enum State {
        Publishing,
        SingleTransmission,
        Idle
    };

    explicit PublisherService(int id, unsigned int period = 100);
    virtual ~PublisherService();

    inline int id() {
        return _id;
    }

    void setState(State state);

    inline State state() {
        return _state;
    }

    inline void setPeriod(unsigned int period) {
        _period = period;
    }

    inline unsigned int period() {
        return _period;
    }

    virtual void publish() = 0;

private:
    int _id;
    State _state;
    unsigned int _period;
    std::unique_ptr<std::thread> _pubThread;
};

#endif // PUBLISHERSERVICE_H
