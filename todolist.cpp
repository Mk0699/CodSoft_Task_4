#include <iostream>
#include <string>
using namespace std;
typedef struct Task{
    string taskName;
    string status;
    struct Task* link;
}task;
task *listHead = NULL;
task *lastTask = NULL;
task* createTask(string name){
    task* newTask = new task;
    if(!newTask){
        cout << "\nMemory not allocated\n";
        exit(1);
    }
    newTask->taskName = name;
    newTask->status = "pending";
    newTask->link = NULL;
    return newTask;
}
void addTask(string name){
    task* n = createTask(name);
    if(!listHead){
        listHead = n;
        lastTask = n;
        return;
    }
    lastTask->link = n;
    lastTask = n;
}
task* findTask(int n){
    task* temp = listHead;
    while(n>1 && temp){
        temp = temp->link;
        n--;
    }
    if(!temp || n<=0){
        return NULL;
    }
    return temp;
}
void displayList(){
    task* temp = listHead;
    if(!temp){
        cout <<"\nTo do list has no tasks \n";
        return;
    }
    cout <<"\n----------- TO DO LIST -------------\n";
    cout <<"No | Task Name                             |   status\n";
    int x = 1;
    while(temp){
        cout<<"\n "<<x<<") "<<temp->taskName<<"         status="<<temp->status;
        temp=temp->link;
        x++;
    }
    cout<<endl<<endl;
    return;
}
void deleteTask(int n){
    if(!listHead){
        cout <<"\nThe TO DO list is empty\n";
        return;
    }
    task* temp = listHead;
    if(n==1){
        temp = listHead;
        listHead = listHead->link;
        free(temp);
        return;
    }
    task* temp2;
    while(n>2 && temp){
        temp = temp->link;
        n--;
    }
    if(!temp || temp == lastTask || n<=0){
        cout <<"\nGiven task does not exist in to do list\n";
    }
    if(temp->link == lastTask){
        lastTask = temp;
    }
    temp2 = temp->link;
    temp->link = temp2->link;
    free(temp2);
    return;
}
int main(){
    int x = 0,y;
    string name;
    task* temp;
    while(x!=5){
        cout <<"\n---To do list operations----\n1.Add task\n2.display to do list\n3.mark task status\n4.delete task\n5.exit\n\n";
        cin>>x;
        switch(x)
        {
            case 1:
                cout <<"\nEnter task : ";
                cin.ignore();
                getline(cin,name);
                addTask(name);
                break;
            case 2:
                displayList();
                break;
            case 3:
                cout<<"\nPlease Enter the task number you want to update : ";
                cin>>y;
                temp=findTask(y);
                if(!temp){
                    cout <<"\nThere is no such task number in the to do list \nPlease select appropriate task !\n";
                    break;
                }
                cout << "\nWhat do you want your task status ?\n1.Completed\n2.pending\n";
                cin>>y;
                if(y!=1 && y!=2){
                    cout <<"\nPlease select either 1 or 2 \n";
                    break;
                }
                if(y==1){
                    temp->status = "Completed";
                }else if(y==2){
                    temp->status = "pending";
                }
                break;
            case 4:
                cout<<"\nEnter task number you want to delete : ";
                cin>>y; 
                deleteTask(y);
                break;
            case 5:
                exit(1);
                break;
            default:
                cout <<"\nPlease select a valid operation\n";
                break;
        }
    }
}