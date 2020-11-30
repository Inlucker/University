#ifndef MASQUEUE_H
#define MASQUEUE_H

#define my_type int

struct masqueue
{
    my_type* ptr;
    my_type* ptr_in;
    my_type* ptr_out;
    int size;
};

#endif // MASQUEUE_H
