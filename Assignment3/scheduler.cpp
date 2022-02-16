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



int main(int argc, char* argv[])
{
    ifstream input_file(argv[1]);

    Queue start_queue;
    start_queue.init();

    //int first_process_priority;
    //int compiling_time = 0;
    //int cumulative_late = 0;

    while(!input_file.eof()){
        string p_name;
        int p_priority;
        int p_arrival_time;
        int p_task_count;
        string subtask_name;
        int subtask_duration;

        input_file >> p_name >> p_priority;
        if(input_file.eof()) break;
        input_file >> p_arrival_time >> p_task_count;
        if(p_task_count > 0){
            Process* to_add = new Process;
            to_add->next = NULL;
            to_add->name = p_name;
            to_add->arrival_time = p_arrival_time;
            to_add->deadline = p_arrival_time;
            to_add->task_count = 0;
            to_add->priority = p_priority;
            to_add->task_stack.init();
            for(int i = 0; i < p_task_count; i++){
                to_add->task_count++;
                input_file >> subtask_name >> subtask_duration;
                to_add->deadline += subtask_duration;
                Subtask* to_add_stack = new Subtask;
                to_add_stack->next = NULL;
                to_add_stack->name = subtask_name;
                to_add_stack->duration = subtask_duration;
                to_add->task_stack.push(to_add_stack);
            }
            start_queue.queue(to_add);
        }
    }

    MultiQueue multiq;
    multiq.init();
    int time = 0;
    Process* to_see1 = NULL;
    Process* to_see2 = NULL;
    Process* to_see3 = NULL;
    int two_count = 0;
    bool special_condition = false;
    int cumulative_late = 0;

    while(!start_queue.isEmpty()){
        while(start_queue.front() != NULL && start_queue.front()->arrival_time <= time ){
            //ADD TO MULTIQUEUE
            //cout << "Time: " << time << endl;
            Process* to_add_multiq = start_queue.dequeue();
            to_add_multiq->next = NULL;
            //cout << "ENTERED: " << to_add_multiq->name << endl;
            multiq.queues[to_add_multiq->priority-1].queue(to_add_multiq);
            
        }

         if(two_count == 2 ){
            //if(!multiq.queues[0].isEmpty() || to_see1 != NULL) special_condition = false;
            if(multiq.queues[2].isEmpty() && to_see3 == NULL){
                special_condition = false;
                two_count = 0;
            }
            else special_condition = true;
        }

        //if(special_condition) cout << "ACTIVE" << endl;

        if(!multiq.queues[0].isEmpty() || to_see1 != NULL){
            if(to_see1 == NULL) to_see1 = multiq.queues[0].dequeue();

            Subtask* to_see_stack = to_see1->task_stack.pop();
            cout << to_see1->name << " " << to_see_stack->name << endl;
            time += to_see_stack->duration;
            if(to_see1->task_stack.isEmpty()){
                cumulative_late += (time - to_see1->deadline);
                delete to_see1;
                to_see1 = NULL;
            }
            delete to_see_stack;
        }
        
        else if((!multiq.queues[1].isEmpty() || to_see2 != NULL)&&!special_condition){
            if(to_see2 == NULL) to_see2 = multiq.queues[1].dequeue();

            Subtask* to_see_stack = to_see2->task_stack.pop();
            cout << to_see2->name <<" " << to_see_stack->name << endl;
            time += to_see_stack->duration;
            if(to_see2->task_stack.isEmpty()){
                cumulative_late += (time - to_see2->deadline);
                delete to_see2;
                to_see2 = NULL;
            }
            delete to_see_stack;
            two_count++;
        }
        else if(!multiq.queues[2].isEmpty() || to_see3 != NULL){
            
            if(to_see3 == NULL) to_see3 = multiq.queues[2].dequeue();
            
            two_count = 0;
            special_condition = false;

            Subtask* to_see_stack = to_see3->task_stack.pop();
            cout << to_see3->name <<" " << to_see_stack->name  << endl;
            time += to_see_stack->duration;
            if(to_see3->task_stack.isEmpty()){
                cumulative_late += (time - to_see3->deadline);
                delete to_see3;
                to_see3 = NULL;
            }
            delete to_see_stack;
        }
        else time++;
    }

    //NOW THE STARTING QUEUE IS EMPTY
    start_queue.close();

    //IF THERE ARE PROCESSES WAITING IN MULTIQUEUE
    while(!multiq.isEmpty() || to_see1 != NULL || to_see2 != NULL || to_see3 != NULL){
        
        if(two_count == 2 ){
            if(multiq.queues[2].isEmpty() && to_see3 == NULL) special_condition = false;
            else special_condition = true;
        }

        //if(special_condition) cout << "ACTIVE" << endl;

        if(!multiq.queues[0].isEmpty() || to_see1 != NULL){
            if(to_see1 == NULL) to_see1 = multiq.queues[0].dequeue();

            Subtask* to_see_stack = to_see1->task_stack.pop();
            cout << to_see1->name <<" " << to_see_stack->name << endl;
            time += to_see_stack->duration;
            if(to_see1->task_stack.isEmpty()){
                cumulative_late += (time - to_see1->deadline);
                delete to_see1;
                to_see1 = NULL;
            }
            delete to_see_stack;
        }
        
        else if((!multiq.queues[1].isEmpty() || to_see2 != NULL)&&!special_condition){
            if(to_see2 == NULL) to_see2 = multiq.queues[1].dequeue();

            Subtask* to_see_stack = to_see2->task_stack.pop();
            cout << to_see2->name << " " << to_see_stack->name << endl;
            time += to_see_stack->duration;
            if(to_see2->task_stack.isEmpty()){
                cumulative_late += (time - to_see2->deadline);
                delete to_see2;
                to_see2 = NULL;
            }
            delete to_see_stack;
            two_count++;
        }
        else if(!multiq.queues[2].isEmpty() || to_see3 != NULL){
            
            if(to_see3 == NULL) to_see3 = multiq.queues[2].dequeue();

            two_count = 0;
            special_condition = false;

            Subtask* to_see_stack = to_see3->task_stack.pop();
            cout << to_see3->name <<" " << to_see_stack->name  << endl;
            time += to_see_stack->duration;
            if(to_see3->task_stack.isEmpty()){
                cumulative_late += (time - to_see3->deadline);
                delete to_see3;
                to_see3 = NULL;
            }
            delete to_see_stack;
        }
        else time++;
    }

    cout << "Cumulative Lateness: " << cumulative_late << endl;

    multiq.close();
   
    input_file.close();
    return EXIT_SUCCESS;
    
}