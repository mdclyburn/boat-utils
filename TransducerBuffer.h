#ifndef TRANSDUCERBUFFER_H
#define TRANSDUCERBUFFER_H

#include <queue>

class TransducerBuffer
{
public:
    TransducerBuffer();
    TransducerBuffer(const unsigned int max_size);
    ~TransducerBuffer();

    void set_max_size(const unsigned int max_size);
    void add_depth_reading(const unsigned int depth);
    void add_temp_reading(const unsigned int temp);

    unsigned int get_max_size() const;
    unsigned int get_depth_reading();
    unsigned int get_temp_reading();
    unsigned int get_depth_buffer_size() const;
    unsigned int get_temp_buffer_size() const;

private:
    unsigned int max_size;
    std::queue<unsigned int> depth_buffer;
    std::queue<unsigned int> temp_buffer;
};

#endif
