#include<cstdio>
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int BookBase_nummax=100000;  //ͼ�������ͼ����������
const int Reader_nummax=1000;  //ͼ�������ɵ�����������
const int Reader_book=3;   //���߿ɽ�ͼ����������
const int Reader_time=60;   //���߽���ʱ���������� 60��


class Time
{

   int year,month,day;


   public:
   Time(int x,int y,int z)
   {
       year=x;
       month=y;
       day=z;
   }
   Time(){};

   void setyear(int x){year=x;}
   void setmonth(int x){month=x;}
   void setday(int x){day=x;}

   int getday(){return day;}
   int getmonth(){return month;}
   int getyear(){return year;}

};

class Book
{

Time t1;
bool state;
int book_no;//���
string book_name;//����
string author;//������
string press;//��������


public:
Book(int x,string y,string z,string b,int t):book_no(x),book_name(y),author(z),press(b),state(t){}
Book(){};


void setbook_no(int x){book_no=x;}      //ͼ����Ϣ��¼��
void setbook_name(string x){book_name=x;}        //ͼ����Ϣ��¼��
void setauthor(string x){author=x;}
void settime(Time x){t1=x;}
void setstate(bool x){state=x;}      //ͼ����Ϣ��¼��
void setpress(string x){press=x;}   //ͼ����Ϣ��¼��


int getbook_no(){return book_no;}        //ͼ����Ϣ�ķ���
string getbook_name(){return book_name;} //ͼ����Ϣ�ķ���
bool getstate(){return state;}
Time gettime(){return t1;}
string getauthor(){return author;} //ͼ����Ϣ�ķ���
string getpress(){return press;}   //ͼ����Ϣ�ķ���

void changebook_no(int x){book_no=x;}      //ͼ����Ϣ���޸�
void changebook_name(string x){book_name=x;} //ͼ����Ϣ���޸�
void changeauthor(string x){author=x;} //ͼ����Ϣ���޸�
void changepress(string x){press;}   //ͼ����Ϣ���޸�
void changetime(Time t){t1=t;}

friend istream & operator>>(istream &,Book &);
friend ostream & operator<<(ostream &, Book &);
Book(const Book & A)
{
    book_no=A.book_no;
    book_name=A.book_name;
    author=A.author;
    press=A.press;
    state=A.state;
}
};

istream & operator>>(istream & input,Book & A)
{
    input>>A.book_no>>A.book_name>>A.author>>A.press>>A.state;
    return input;
}
ostream & operator<<(ostream & output,Book & A)
{
    output<<"��ţ�"<<A.book_no<<endl;
    output<<"������"<<A.book_name<<endl;
    output<<"����������"<<A.author<<endl;
    output<<"�����磺"<<A.press<<endl;
    if(A.state==0)output<<"����δ���"<<endl<<endl;
    else
    {
        output<<"���Ѿ��������"<<endl;
        output<<"���ʱ�䣺" <<A.t1.getyear()<<"/"<<A.t1.getmonth()<<"/"<<A.t1.getday()<<endl;
        output<<" "<<endl;
    }
    return output;
}

class BookBase
{
    vector<Book>v;
    vector<Book>::iterator it;
    multimap<int,int>m1 ;              //������Ų���
    multimap<int,int>::iterator mit1;
    multimap<string,int>m2;               //������������
    multimap<string,int>::iterator mit2;
    multimap<string,int>m3;              //����������������
    multimap<string,int>::iterator mit3;
    multimap<string,int>m4 ;                   //���ճ��������
    multimap<string,int>::iterator mit4;

    public:
    BookBase(){load();}
    ~BookBase(){save();}
   void searchbook(int x)
   {    int y=search1(x)  ;
       it=v.begin()+y;
       cout<<*it;
    }
    void searchbook2(string x)
   {    int y=search2(x)  ;
       it=v.begin()+y;
       cout<<*it;
    }
    void searchbook3(string x)
   {    int y=search3(x)  ;
       it=v.begin()+y;
       cout<<*it;
    }
    void searchbook4(string x)
   {    int y=search4(x)  ;
       it=v.begin()+y;
       cout<<*it;
    }
   void add(Book A);         //��һ���鵽����
   void add();             //����౾�鵽����
   void load();              //��ȡ�ļ��е�����
   void save();             //�������е�����д���ļ�
   int search1(int x);     //����Ų�����
   int search2(string x);   //�������������
   int search3(string x);    //���������������
   int search4(string x);    //���ݳ������������ Ŀǰ�ķ���ֻ����һ���ó�������飬����������
   void delebook(int x);   //�������ɾ��ĳһ����
   void display();     //�����п��е�������ʾ����
   void borrow(int x);  //�����Ϊx����ӿ��н��ĳ�ȥ
   void giveback(int x);// �����Ϊx���鷵�ص�����
};
void BookBase::add(Book A)
{
    v.push_back(A);
    int i=v.size();
    if(i>=BookBase_nummax-1) {cout<<"ͼ�������Ѵﵽͼ����������ɵ��������"<<endl;}
    else
    {
    m1.insert(make_pair(A.getbook_no(),i-1));
    m2.insert(make_pair(A.getbook_name(),i-1));
    m3.insert(make_pair(A.getauthor(),i-1));
    m4.insert(make_pair(A.getpress(),i-1));
    }
}
void BookBase::add()
{
    Book r;

    while(1)
    {
    cin>>r;
    if(r.getbook_no()==-1) break;
    v.push_back(r);
    int i=v.size();
    if(i>=BookBase_nummax-1) {cout<<"ͼ�������Ѵﵽͼ����������ɵ��������"<<endl;break;}
    m1.insert(make_pair(r.getbook_no(),i-1));     //make_pair �ɶ�
    m2.insert(make_pair(r.getbook_name(),i-1));
    m3.insert(make_pair(r.getauthor(),i-1));
    m4.insert(make_pair(r.getpress(),i-1));

    }
}
int BookBase::search1(int x)
{
    mit1=m1.find(x);  //find ��key ���ص�һ��key���ڵ�λ�ã����򷵻�end��
    if(mit1!=m1.end())
    {
    return mit1->second;
    }
    else
    return 0;
}
int BookBase::search2(string x)
{
    mit2=m2.find(x);  //find ��key ���ص�һ��key���ڵ�λ�ã����򷵻�end��
    if(mit2!=m2.end())
    {
    return mit2->second;
    }
    else
    return 0;
}
int BookBase::search3(string x)
{
    mit3=m3.find(x);  //find ��key ���ص�һ��key���ڵ�λ�ã����򷵻�end��
    if(mit3!=m3.end())
    {
    return mit3->second;  //multimap ��second ��ʹ�ڶ���Ԫ��  value
    }
    else
    return 0;
}
int BookBase::search4(string x)
{
    mit4=m4.find(x);   //find ��key ���ص�һ��key���ڵ�λ�ã����򷵻�end��
    if(mit4!=m4.end())
    {
    return mit4->second;
    }
    else
    return 0;
}

void BookBase::delebook(int x)
{
    v.erase(v.begin()+x-1);   //������x��λ�õ�Book

}

void BookBase::display()
{
    for(it=v.begin();it!=v.end();it++)
    cout<<*it;         //������������Ŀռ�ָ��
}

void BookBase::load()
{
    Book r;
    int i;
   ifstream infile;
   infile.open("E:\\��������1.txt",ios::in);
    if(!infile)
    return ;
    v.clear();
    m1.clear();
    m2.clear();
    m3.clear();
    m4.clear();
    i=0;
    while(infile>>r)
    {
    v.push_back(r);
    m1.insert(make_pair(r.getbook_no(),i));
    m2.insert(make_pair(r.getbook_name(),i));
    m3.insert(make_pair(r.getauthor(),i));
    m4.insert(make_pair(r.getpress(),i));
    i++;

    }
    infile.close();
}

void BookBase::save()
{
    ofstream outfile("E:\\c++����\\ͼ��ݹ���ϵͳ�Ĳ�������\\�������1.txt",ios::out);
    if(!outfile)
    return ;

    for(it=v.begin();it!=v.end();it++)
    outfile<<*it;

    outfile.close();

}


class Reader  //���ߵ���Ϣ�� ������ѧ�ţ����ĵ��飬
{
    string name;
    int no;
    vector<Book>r;
    vector<Book>::iterator it;
    multimap<int,int>m1;
    multimap<int,int>::iterator mit2;
    vector<Book>old_r;
    public:
    Reader(string name,int no):no(no),name(name){};
    Reader(){};


    void add(Book A);
    void giveback(int x);
    void display();
};
 void Reader::add(Book A)
 {    cout<<A.getstate()<<endl;
    r.push_back(A);
     int i=r.size();
     m1.insert(make_pair(A.getbook_no(),i-1)); //��ŷ���m1��

 }
void Reader::giveback(int x)
{
   mit2=m1.find(x);
   if(mit2!=m1.end())
   old_r.push_back(r[mit2->second]);  //������ʷ��¼��
   r.erase(r.begin()+mit2->second);    //�����м�¼�����
}
void Reader::display()
{
    cout<<"ѧ��:"<<no<<endl;
    cout<<"����:"<<name<<endl;
    for(it=r.begin();it!=r.end();it++)
    cout<<*it;
}
int main()
{
int x,y;
string z;
Book a,b;

cin>>y>>z;
cin>>a>>b;

Time t(2018,5,24);
a.settime(t);
b.settime(t);
Reader u(z,y);
cout<<b;
cout<<a.getstate()<<endl;
cout<<b.getstate()<<endl;
u.add(a);
u.add(b);
cin>>x;
u.giveback(x);
u.display();

}











