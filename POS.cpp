#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<cstdlib>

using namespace std;

class products
{
private:
    char P_ID[50];
    char P_name[50];
    float Price;
friend void searchproduct();
friend void newbill();
friend void delproduct();
friend void editproduct();
public:
    void accept(){
    cout<<endl<<"Enter Product ID -  ";
    cin>>P_ID;
    cout<<endl<<"Enter Product Name -  ";
    cin>>P_name;
    cout<<endl<<"Enter Price -  ";
    cin>>Price;

    }

    void display(){
    cout<<endl<<setw(21)<<P_ID<<setw(28)<<P_name<<setw(20)<<Price;

    }

};
products obj;

class bill
{
public:
    int billno;
    char date[20];
    char itemcode[50];
    char itemname[50];
    float BPrice;
    int qty;
    float total;
    void display()
    {
        cout<<endl<<setw(21)<<itemcode<<setw(28)<<itemname<<setw(10)<<qty<<setw(12)<<BPrice<<setw(12)<<total;

    }

};
bill obj2;



void addproduct()
{   char ch='y';
    while(ch=='y')
    {
        fstream wr;
    wr.open("D:\\C++\\myproducts.txt",ios::app);
    obj.accept();
    wr.write((char*)&obj,sizeof(obj));
    cout<<"\n Product added successfully...";
    cout<<"\n\n Want to add more? ( 'y' for YES, 'n' for NO ):  ";
    cin>>ch;
    }
}

void readproducts()
{
    fstream rd;
    rd.open("D:\\C++\\myproducts.txt",ios::in);
    rd.seekg(0,ios::end);
    int n= rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    cout<<endl<<setw(21)<<"Barcode"<<setw(28)<<"Product Name"<<setw(20)<<"Price";
    cout<<"\n__________________________________________________________________________";
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        obj.display();
    }
    cout<<endl<<"_______________________________________________________________________";
}

 void searchproduct()
{
    char ch='y';
    while(ch=='y')
    {
        fstream rd;
    rd.open("D:\\C++\\myproducts.txt",ios::in);
    char nm[50];
    cout<<endl<<"Enter the Product ID :  ";
    cin>>nm;
    rd.seekg(0,ios::end);
    int n= rd.tellg()/sizeof(obj);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj,sizeof(obj));
        if(strcmp(nm,obj.P_ID)==0)
        {
            obj.display();
        }
    }

    cout<<"\n\n Want to search for more entries?  ( 'y' for YES, 'n' for NO ):  ";
    cin>>ch;


    }
}

void newbill()
{
    int bid;
    char dte[50];
    cout<<"\n Enter Bill Number :  ";
    cin>>bid;
    cout<<"\n Enter Date (dd/mm/yyyy):  ";
    cin>>dte;
    int e=0;
    while(e!=1)
    {
        char barcode[50];
        cout<<"\n Enter Product's Bar Code :  ";
        cin>>barcode;
        if(strcmp(barcode,"0")==0)
        {
            e=1;
        }
        else
        {
            fstream rd;
            rd.open("D:\\C++\\myproducts.txt",ios::in);
            rd.seekg(0,ios::end);
            int n=rd.tellg()/sizeof(obj);
            rd.seekg(0,ios::beg);
            for(int i=1;i<=n;i++)
            {
                rd.read((char*)&obj,sizeof(obj));
                if(strcmp(barcode,obj.P_ID)==0)
                {
                    obj2.billno=bid;
                    strcpy(obj2.date,dte);
                    strcpy(obj2.itemcode,obj.P_ID);
                    strcpy(obj2.itemname,obj.P_name);
                    obj2.BPrice=obj.Price;
                    obj2.qty=1;
                    obj2.total=obj2.qty*obj2.BPrice;
                    fstream wr;
                    wr.open("D:\\C++\\bill.txt",ios::app);
                    wr.write((char*)&obj2,sizeof(obj2));
                    wr.close();

                }
            }



        }
    }
    fstream rd2;
    rd2.open("D:\\C++\\bill.txt",ios::in);
    rd2.seekg(0,ios::end);
    int m=rd2.tellg()/sizeof(obj2);
    rd2.seekg(0,ios::beg);
    cout<<"\n\n\n\n\n__________________________* WELCOME TO MY SUPER STORE *__________________________";
    float mybill=0;
    for(int j=1;j<=m;j++)
    {
        rd2.read((char*)&obj2,sizeof(obj2));
        if(obj2.billno==bid && strcmp(obj2.date,dte)==0)
        {
            obj2.display();
            mybill = mybill+obj2.total;
        }
    }
    cout<<endl<<"\n\n*******************************************************************";
    cout<<"\nPlease Pay -"<<mybill<<endl;
    cout<<"*******************************************************************";



}

void dupbill()
{   int sbill;
    char dt[20];
    cout<<"\n Enter the bill number :  ";
    cin>>sbill;
    fstream rd;
    bill ob;
    rd.open("D:\\C++\\bill.txt",ios::in);
    rd.seekg(0,ios::end);
    int n= rd.tellg()/sizeof(ob);
    rd.seekg(0,ios::beg);
     cout<<"\n\n\n\n\n__________________________* WELCOME TO MY SUPER STORE *__________________________";
    float mybill=0;
    cout<<"\n*duplicate bill*";
    cout<<"\n_________________________________________________________________________________\n";

    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&ob,sizeof(ob));
        if(ob.billno==sbill)
        {
            ob.display();
            mybill = mybill+ob.total;
        }
    }
    cout<<endl<<"\n\n*******************************************************************";
    cout<<"\nPlease Pay -"<<mybill<<endl;
    cout<<"*******************************************************************";

}

void delproduct()
{    char ch='y';
     while(ch=='y')
     {
         fstream rd,wr;
     products ob;
    rd.open("D:\\C++\\myproducts.txt",ios::in);
    wr.open("D:\\C++\\temp.txt",ios::out);
    char nm[50];
    cout<<endl<<"Enter the Product ID :  ";
    cin>>nm;
    rd.seekg(0,ios::end);
    int n= rd.tellg()/sizeof(ob);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&ob,sizeof(ob));
        if(strcmp(nm,ob.P_ID)==0)
        {
            ob.display();
            cout<<"\n\n ABOVE FILE HAS BEEN DELETED";
        }
        else{

            wr.write((char*)&ob,sizeof(ob));
        }

    }rd.close();
    wr.close();
    remove("D:\\C++\\myproducts.txt");
    rename("D:\\C++\\temp.txt","D:\\C++\\myproducts.txt");

    cout<<"\n\nWant to Delete more? ( 'y' for YES, 'n' for NO):  ";
    cin>>ch;


     }


}

void editproduct()
{
    products ob;
    fstream rd,wr;
    rd.open("D:\\C++\\myproducts.txt",ios::in);
    wr.open("D:\\C++\\temp.txt",ios::out);
    char id[50];
    cout<<endl<<"Enter the Product ID :  ";
    cin>>id;
    rd.seekg(0,ios::end);
    int n= rd.tellg()/sizeof(ob);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&ob,sizeof(ob));
        if(strcmp(id,ob.P_ID)==0)
        {   int ch;
            ob.display();
            cout<<"\n\nwhat do you want to change...?\n\t1. Product ID\n\t2. Product Name\n\t3. Product's Price\n: ";
            cin>>ch;
            switch(ch)
            {

                case 1:char id[50];
                        cout<<"\n Enter new ID for the product- ";
                        cin>>id;
                        strcpy(ob.P_ID,id);
                        wr.write((char*)&ob,sizeof(ob));
                        cout<<"\nProduct ID successfully changed...";
                        break;

                case 2: char name[50];
                        cout<<"\n Enter new name- ";
                        cin>>name;
                        strcpy(ob.P_name,name);
                        wr.write((char*)&ob,sizeof(ob));
                        cout<<"\nName successfully changed...";
                        break;
                case 3: float nprice;
                        cout<<"\n Enter new price- ";
                        cin>>nprice;
                        ob.Price=nprice;
                        wr.write((char*)&ob,sizeof(ob));
                        cout<<"\nPrice successfully changed...";
                        break;

            }
        }
        else{

            wr.write((char*)&ob,sizeof(ob));
        }

    }rd.close();
    wr.close();
    remove("D:\\C++\\myproducts.txt");
    rename("D:\\C++\\temp.txt","D:\\C++\\myproducts.txt");



}
float caltotal(int bno,char dat[])
{   float tot=0;
    bill ob;
    fstream rd2;
    rd2.open("D:\\C++\\bill.txt",ios::in);
    rd2.seekg(0,ios::end);
    int n=rd2.tellg()/sizeof(ob);
    rd2.seekg(0,ios::beg);
    for(int j=1;j<=n;j++)
            {
                rd2.read((char*)&ob,sizeof(ob));
                if(strcmp(ob.date,dat)==0 && ob.billno==bno)
                {
                    tot=tot+ob.total;
                }
            }
    rd2.close();
    return tot;
}
void sales()
{
    char dat[20];
    int billno;
    int temp=0;
    float tot=0;
    cout<<"\nEnter Date for the day you want to view the sales (dd/mm/yyyy): ";
    cin>>dat;
    cout<<"\n\n___________________________________________________";
    cout<<"\nSales for Date "<<dat<<" are:  ";
    cout<<endl<<endl<<setw(20)<<"Bill Number"<<setw(22)<<"Total bill\n";
    fstream rd;
    float total=0;
    rd.open("D:\\C++\\bill.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(obj2);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=n;i++)
    {
        rd.read((char*)&obj2,sizeof(obj2));
        if(strcmp(obj2.date,dat)==0)
        {   total=total+obj2.BPrice;
            billno=obj2.billno;
            if(billno!=temp)
            {
                tot=0;
                temp=billno;
                tot=caltotal(billno,dat);

            cout<<endl<<setw(20)<<billno<<setw(20)<<tot;
            }

        }
    }
    cout<<"\n___________________________________________________";
    cout<<"\nTotal Sale: "<<total;
    cout<<"\n___________________________________________________";



}

main()
{
  char e='y';
  int ch;
  while(e=='y')
  {
    cout<<"\n_________________________ M E N U ___________________";
    cout<<"\n\n\t1. To Create New Bill...";
    cout<<"\n\t2. To view Bill...";
    cout<<"\n\t3. To Add Product...";
    cout<<"\n\t4. To View Products...";
    cout<<"\n\t5. To Search Product...";
    cout<<"\n\t6. To Delete Product...";
    cout<<"\n\t7. To Edit Product...";
    cout<<"\n\t8. To view Sales...";
    cout<<"\n\t9. To Exit...";
    cout<<"\n_______________________________________________________";
    cout<<"\n\n\tEnter the CHOICE:  ";
    cin>>ch;

    switch(ch)
    {
        case 1:newbill();
                break;
        case 2:dupbill();
                break;
        case 3:addproduct();
                break;
        case 4:readproducts();
                break;
        case 5:searchproduct();
                break;
        case 6:delproduct();
                break;
        case 7:editproduct();
                break;
        case 8:sales();
                break;
        case 9:cout<<"\nyou pressed EXIT.....";
                exit(0);


    }
    cout<<"\n\n* Go back to Main Menu ? _(y/n)_ * -  ";
    cin>>e;

    system("cls");


  }
}
