#include <iostream>
#include <queue>
/**
/*ʵ�����ȼ������㷨����תʱ��Ƭ�����㷨
/*author���ƹ�Ҳ����ؼ
**/
using namespace std;
struct process{
    int pid;//���̱�ţ�������ʱ˳�������
    string statu;//����Ŀǰ״̬
    int rotation;//��ռ��CPUʱ��
    int priority;//���ȼ�
    int occupy_num;//��תʱ������
    int need_cpu;//����Ŀǰ����CPUʱ��Ƭ��
    process* next;
    bool operator<(process p)const{
        return priority < p.priority;
    }
};

priority_queue<process>readyqueue_priority;//���ȼ������㷨��������
queue<process>readyqueue_roation;//��ת�����㷨����

/*���ȼ������㷨�����������*/
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

/*��ת�����㷨�����������*/
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

/*���ȼ������㷨ʵ��*/
void priority_ctrl(){
    while(!readyqueue_priority.empty()){
        process cur_p = readyqueue_priority.top();//���׽���
        readyqueue_priority.pop();
        cur_p.statu = "Run";
        process top_pro = readyqueue_priority.top();
        while(cur_p.priority>=top_pro.priority)
        {
            outPriority(readyqueue_priority,cur_p);//�ж��������Ƿ�������׽���
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

/*��ת�����㷨ʵ��*/
void rotation_ctrl(){
    while(!readyqueue_roation.empty()){
        process cur_p = readyqueue_roation.front();

        readyqueue_roation.pop();
        cur_p.statu = "Run";/*�õ�ǰ����״̬Ϊ����*/
        while(cur_p.rotation<cur_p.occupy_num)//�ж�ռ��CPUʱ���Ƿ�ﵽ��ת
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

