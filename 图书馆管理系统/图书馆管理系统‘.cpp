#include<cstdio>
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int BookBase_nummax=100000;  //图书库容纳图书的最大数量
const int Reader_nummax=1000;  //图书库科容纳的最大读者数量
const int Reader_book=3;   //读者可借图书的最大数量
const int Reader_time=60;   //读者借阅时间的最大日期 60天


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
int book_no;//书号
string book_name;//书名
string author;//作者名
string press;//出版社名


public:
Book(int x,string y,string z,string b,int t):book_no(x),book_name(y),author(z),press(b),state(t){}
Book(){};


void setbook_no(int x){book_no=x;}      //图书信息的录入
void setbook_name(string x){book_name=x;}        //图书信息的录入
void setauthor(string x){author=x;}
void settime(Time x){t1=x;}
void setstate(bool x){state=x;}      //图书信息的录入
void setpress(string x){press=x;}   //图书信息的录入


int getbook_no(){return book_no;}        //图书信息的返回
string getbook_name(){return book_name;} //图书信息的返回
bool getstate(){return state;}
Time gettime(){return t1;}
string getauthor(){return author;} //图书信息的返回
string getpress(){return press;}   //图书信息的返回

void changebook_no(int x){book_no=x;}      //图书信息的修改
void changebook_name(string x){book_name=x;} //图书信息的修改
void changeauthor(string x){author=x;} //图书信息的修改
void changepress(string x){press;}   //图书信息的修改
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
    output<<"书号："<<A.book_no<<endl;
    output<<"书名："<<A.book_name<<endl;
    output<<"作者姓名："<<A.author<<endl;
    output<<"出版社："<<A.press<<endl;
    if(A.state==0)output<<"本书未借出"<<endl<<endl;
    else
    {
        output<<"书已经被借出！"<<endl;
        output<<"借出时间：" <<A.t1.getyear()<<"/"<<A.t1.getmonth()<<"/"<<A.t1.getday()<<endl;
        output<<" "<<endl;
    }
    return output;
}

class BookBase
{
    vector<Book>v;
    vector<Book>::iterator it;
    multimap<int,int>m1 ;              //按照书号查找
    multimap<int,int>::iterator mit1;
    multimap<string,int>m2;               //按照书名查找
    multimap<string,int>::iterator mit2;
    multimap<string,int>m3;              //按照作者姓名查找
    multimap<string,int>::iterator mit3;
    multimap<string,int>m4 ;                   //按照出版社查找
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
   void add(Book A);         //放一本书到库中
   void add();             //放许多本书到库中
   void load();              //读取文件中的数据
   void save();             //把向量中的数据写到文件
   int search1(int x);     //按书号查找书
   int search2(string x);   //按书的名字找书
   int search3(string x);    //按照书的作者找书
   int search4(string x);    //根据出版社的名找书 目前的方法只能找一本该出版社的书，另作修正。
   void delebook(int x);   //根据书号删除某一本书
   void display();     //将所有库中的数据显示出来
   void borrow(int x);  //将书号为x的书从库中借阅出去
   void giveback(int x);// 将书号为x的书返回到库中
};
void BookBase::add(Book A)
{
    v.push_back(A);
    int i=v.size();
    if(i>=BookBase_nummax-1) {cout<<"图书数量已达到图书库所能容纳的最大数量"<<endl;}
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
    if(i>=BookBase_nummax-1) {cout<<"图书数量已达到图书库所能容纳的最大数量"<<endl;break;}
    m1.insert(make_pair(r.getbook_no(),i-1));     //make_pair 成对
    m2.insert(make_pair(r.getbook_name(),i-1));
    m3.insert(make_pair(r.getauthor(),i-1));
    m4.insert(make_pair(r.getpress(),i-1));

    }
}
int BookBase::search1(int x)
{
    mit1=m1.find(x);  //find 找key 返回第一个key所在的位置，否则返回end。
    if(mit1!=m1.end())
    {
    return mit1->second;
    }
    else
    return 0;
}
int BookBase::search2(string x)
{
    mit2=m2.find(x);  //find 找key 返回第一个key所在的位置，否则返回end。
    if(mit2!=m2.end())
    {
    return mit2->second;
    }
    else
    return 0;
}
int BookBase::search3(string x)
{
    mit3=m3.find(x);  //find 找key 返回第一个key所在的位置，否则返回end。
    if(mit3!=m3.end())
    {
    return mit3->second;  //multimap 的second 即使第二个元素  value
    }
    else
    return 0;
}
int BookBase::search4(string x)
{
    mit4=m4.find(x);   //find 找key 返回第一个key所在的位置，否则返回end。
    if(mit4!=m4.end())
    {
    return mit4->second;
    }
    else
    return 0;
}

void BookBase::delebook(int x)
{
    v.erase(v.begin()+x-1);   //消除第x个位置的Book

}

void BookBase::display()
{
    for(it=v.begin();it!=v.end();it++)
    cout<<*it;         //迭代器是特殊的空间指针
}

void BookBase::load()
{
    Book r;
    int i;
   ifstream infile;
   infile.open("E:\\测试数据1.txt",ios::in);
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
    ofstream outfile("E:\\c++的题\\图书馆管理系统的测试数据\\输出数据1.txt",ios::out);
    if(!outfile)
    return ;

    for(it=v.begin();it!=v.end();it++)
    outfile<<*it;

    outfile.close();

}


class Reader  //读者的信息： 姓名，学号，借阅的书，
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
     m1.insert(make_pair(A.getbook_no(),i-1)); //书号放入m1中

 }
void Reader::giveback(int x)
{
   mit2=m1.find(x);
   if(mit2!=m1.end())
   old_r.push_back(r[mit2->second]);  //放入历史记录中
   r.erase(r.begin()+mit2->second);    //从现有记录中清除
}
void Reader::display()
{
    cout<<"学号:"<<no<<endl;
    cout<<"姓名:"<<name<<endl;
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











