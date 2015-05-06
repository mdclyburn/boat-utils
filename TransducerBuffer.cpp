#include "TransducerBuffer.h"

TransducerBuffer::TransducerBuffer() : max_size(5)
{
}

TransducerBuffer::TransducerBuffer(const unsigned int max_size) : max_size(max_size)
{
}

TransducerBuffer::~TransducerBuffer()
{
}

void TransducerBuffer::set_max_size(const unsigned int max_size)
{
    this->max_size = max_size;
    return;
}

void TransducerBuffer::add_depth_reading(const unsigned int depth)
{
    // remove element if necessary
    if(depth_buffer.size() == max_size)
	depth_buffer.pop();
    depth_buffer.push(depth);

    return;
}

void TransducerBuffer::add_temp_reading(const unsigned int temp)
{
    // remove element if necessary
    if(temp_buffer.size() == max_size)
	temp_buffer.pop();
    temp_buffer.push(temp);

    return;
}

unsigned int TransducerBuffer::get_max_size() const
{
    return max_size;
}

unsigned int TransducerBuffer::get_depth_reading()
{
    const unsigned int depth = depth_buffer.front();
    depth_buffer.pop();

    return depth;
}

unsigned int TransducerBuffer::get_temp_reading()
{
    const unsigned int temp = temp_buffer.front();
    temp_buffer.pop();

    return temp;
}

unsigned int TransducerBuffer::get_depth_buffer_size() const
{
    return depth_buffer.size();
}

unsigned int TransducerBuffer::get_temp_buffer_size() const
{
    return temp_buffer.size();
}
