#include <iostream>
#include <queue>
/**
/*实现优先级调度算法和轮转时间片调度算法
/*author：灯光也暗了丶
**/
using namespace std;
struct process{
    int pid;//进程编号，由输入时顺序决定、
    string statu;//进程目前状态
    int rotation;//已占用CPU时间
    int priority;//优先级
    int occupy_num;//轮转时间上限
    int need_cpu;//进程目前还需CPU时间片数
    process* next;
    bool operator<(process p)const{
        return priority < p.priority;
    }
};

priority_queue<process>readyqueue_priority;//优先级调度算法就绪队列
queue<process>readyqueue_roation;//轮转调度算法队列

/*优先级调度算法就绪队列输出*/
void outPriority(priority_queue<process>q,process cur){
    cout<<"----------------"<<"process: "<<cur.pid<<"------------------"<<endl;
    cout<<"statue: "<<cur.statu<<endl;
    cout<<"Needing CPU: "<<cur.need_cpu<<endl;
    cout<<"Priority: "<<cur.priority<<endl;
    while(!q.empty()){
        cur = q.top();
        q.pop();
        cout<<"----------------"<<"process: "<<cur.pid<<"------------------"<<endl;
        cout<<"statue: "<<cur.statu<<endl;
        cout<<"Needing CPU: "<<cur.need_cpu<<endl;
        cout<<"Priority: "<<cur.priority<<endl;
    }
    cout<<"\none clock pass"<<endl;
}

/*轮转调度算法就绪队列输出*/
void outRotation(queue<process>q,process cur){
    cout<<"----------------"<<"process: "<<cur.pid<<"------------------"<<endl;
    cout<<"statue: "<<cur.statu<<endl;
    cout<<"Needing CPU: "<<cur.need_cpu<<endl;
    cout<<"The limit of occupying CPU: "<<cur.occupy_num<<endl;
    cout<<"Had occupied CPU: "<<cur.rotation<<endl;
    while(!q.empty()){
        cur = q.front();
        q.pop();
        cout<<"----------------"<<"process: "<<cur.pid<<"------------------"<<endl;
        cout<<"statue: "<<cur.statu<<endl;
        cout<<"Needing CPU: "<<cur.need_cpu<<endl;
        cout<<"The limit of occupying CPU: "<<cur.occupy_num<<endl;
        cout<<"Had occupied CPU: "<<cur.rotation<<endl;
    }
    cout<<"\none clock pass"<<endl;
}

/*优先级调度算法实现*/
void priority_ctrl(){
    while(!readyqueue_priority.empty()){
        process cur_p = readyqueue_priority.top();//链首进程
        readyqueue_priority.pop();
        cur_p.statu = "Run";
        process top_pro = readyqueue_priority.top();
        while(cur_p.priority>=top_pro.priority)
        {
            outPriority(readyqueue_priority,cur_p);//判断优先数是否大于链首进程
            cur_p.priority-=3;
            cur_p.need_cpu--;
            if(cur_p.need_cpu==0){
                cur_p.statu = "Finish";
                cout<<"\n\nFinish: "<<cur_p.pid<<endl;
                break;
            }
        }
        if(cur_p.statu!="Finish"){
            cur_p.statu = "Ready";
            readyqueue_priority.push(cur_p);
        }
    }
    cout<<endl;
}

/*轮转调度算法实现*/
void rotation_ctrl(){
    while(!readyqueue_roation.empty()){
        process cur_p = readyqueue_roation.front();

        readyqueue_roation.pop();
        cur_p.statu = "Run";/*置当前进程状态为运行*/
        while(cur_p.rotation<cur_p.occupy_num)//判断占用CPU时间是否达到轮转
        {
            outRotation(readyqueue_roation,cur_p);
            cur_p.rotation++;
            cur_p.need_cpu--;
            if(cur_p.need_cpu==0){
                cur_p.statu = "Finish";
                cout<<"\n\nFinish: "<<cur_p.pid<<endl;
                break;
            }
        }
        if(cur_p.statu!="Finish"){
            cur_p.statu = "Ready";
            cur_p.rotation = 0;
            readyqueue_roation.push(cur_p);
        }
    }
    cout<<endl;
}
int main()
{
    int n;
    cout<<"Input total process: "<<endl;
    cin>>n;
    cout<<"Choose process control way:"<<endl<<"1:Priority"<<endl<<"2:Rotation"<<endl;
    int choose;
    cin>>choose;
    process p;
    if(choose==1){
        cout<<"Input "<<n<<" pairs of "<<"need_CPU and priority: (separate with SPACE)"<<endl;
        p.statu = "Ready";
        p.occupy_num = 1;
        p.rotation = 1;
        p.next = NULL;
        for(int i=1;i<=n;i++){
            p.pid = i;
            cin>>p.need_cpu>>p.priority;
            readyqueue_priority.push(p);
        }
        priority_ctrl();

    }
    else{
        cout<<"Input "<<n<<" pairs of "<<"need_CPU and occupy_TIME: (separate with SPACE)"<<endl;
        p.statu = "Ready";
        p.priority = 1;
        p.rotation = 0;
        p.next = NULL;
        for(int i=1;i<=n;i++){
            p.pid = i;
            cin>>p.need_cpu>>p.occupy_num;
            readyqueue_roation.push(p);
        }
        rotation_ctrl();

    }
    return 0;
}

