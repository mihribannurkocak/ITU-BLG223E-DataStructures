/* @Author
Student Name: Mihriban Nur Kocak
Student ID : 150180090
Date: 13.01.2021 */

#include "data_structs.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

//STACK OPERATIONS
void Stack::init()
{
    head = NULL;
}

void Stack::close()
{
    Subtask* p;
    while(head)
    {
        p = head;
        head = head->next;
        delete p;
    }
}

void Stack::push(Subtask* in)
{
    //MALLOC IN BEFORE PASSING TO FUNCTION
    in->next = head;
    head = in;
}

Subtask* Stack::pop()
{
    Subtask* popped;
    popped = head;
    head = head->next;
    return popped;
}

bool Stack::isEmpty()
{
    if(head == NULL) return true;
    else return false;
}

//QUEUE OPERATIONS

void Queue::init()
{
    head = NULL;
    tail = NULL;
}
void Queue::close()
{
    Process* p;
    while(head)
    {
        p = head;
        head = head->next;
        p->task_stack.close();
        delete p;
    }
}
void Queue::queue(Process* in)
{
    //BEFORE PASSING TO FUNCTION SET IN'S NEXT AS NULL
    if(isEmpty()){
        //FIRST ELEMENT
        in->next = NULL;
        head = in;
        tail = in;
    }
    else{
        
        tail->next = in;
        tail = in;
        tail->next = NULL;
    }
}

Process* Queue::dequeue()
{
    Process* deqd;
    if(head==tail){
        //JUST ONE ELEMENT
        deqd = head;
        head = NULL;
        tail = NULL;
    }
    else{
        deqd = head;
        head = head->next;
    }
    return deqd;
}

bool Queue::isEmpty()
{
    if(head == NULL && tail == NULL) return true;
    else return false;
}

Process* Queue::front()
{
    Process* fronted = head;
    return fronted;    
}

void MultiQueue::init()
{
    queues[0].init();
    queues[1].init();
    queues[2].init();
}

void MultiQueue::close()
{
    queues[0].close();
    queues[1].close();
    queues[2].close();
}

void MultiQueue::queue(Process* in)
{
    if(in->priority == 1) queues[0].queue(in);
    else if(in->priority == 2) queues[1].queue(in);
    else if(in->priority == 3) queues[2].queue(in);
}

Process* MultiQueue::dequeue(int priority)
{
    Process* deqd = queues[priority-1].dequeue();
    return deqd;
}

bool MultiQueue::isEmpty()
{
    if(queues[0].isEmpty() && queues[1].isEmpty() && queues[2].isEmpty()) return true;
    else return false;
}

Process* MultiQueue::front(int priority)
{
    Process* fronted = queues[priority-1].front();
    return fronted;
}