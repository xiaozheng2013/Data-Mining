#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<fstream>
#include<math.h>
using namespace std;

class Item{
public:
	int value;
	double MIS;
	Item();
	Item(int,double);
	Item(const Item& a);
	void display();

};

class Itemset{
public:
	int length;
	vector<Item> value;

	Itemset();
	Itemset(const Itemset& a);
	//~Itemset();
	void add(Item a);//used the default copy constructor
	double contain(int a);
	int contain(Item& a);
	Item& operator[](const int i);
	void remove(int i);
	int contain(Itemset& a);
	void proj(Itemset& a);
	void display();

};

class Sequence{
public:
	int length;
	vector<Itemset> transactions;
	Sequence();
	Sequence(const Sequence& a);
	//~Sequence();
	void add(Itemset a);
	void add(Item a);
	int contain(Item& a);
	Itemset& operator[](const int i);
	void remove(int i);
	void remove(int i, int j);
	int contain(Sequence& a); 

	void proj(Sequence& a);
	int size();
	void inc_in(Item a);
	void inc_out(Item a);
	void display();
	friend ostream& operator<<(ostream& os, const Sequence& a); 

};

class Sequenceset{
public:
	int length;
	vector<Sequence> patterns;
	Sequenceset();
	Sequenceset(const Sequenceset& a);
	void add(Sequence a);
	void add(Item a);
	Sequence& operator[](const int i);
	void remove(int i);
	void remove(int i,int j,int k);
	int freq(Item a);
	int freq(Sequence a);
	void display();
	void resize(int i);
};


class Sequenceset_set{
public:
        int length;
        vector<Sequenceset> level_result;
        Sequenceset_set();
	Sequenceset_set(int i);
        Sequenceset& operator[](const int i);
	friend ostream& operator<<(ostream& os, const Sequenceset_set& a); 
	void resize(int i);
};

Sequenceset_set::Sequenceset_set()
{       length = 0;     };

Sequenceset_set::Sequenceset_set(int i)
{
	length = i;
	level_result.resize(i);	

};
	
Sequenceset& Sequenceset_set::operator[](const int i)
{
        return level_result[i];

};

ostream& operator<<(ostream& os, const Sequenceset_set& a) 
{
	for(int i=0;i<a.length;i++)
	{
	   os<<"The number of length "<<i+1<<" sequential patters is "
		<<a.level_result[i].length<<endl;
	   int L1 = a.level_result[i].length;	
	   for(int j=0;j<L1;j++)
	   {
		os<<"<";
		int L2 = a.level_result[i].patterns[j].length;
		for(int k=0;k<L2;k++)
		{
		   os<<"{";
		   int L3 = a.level_result[i].patterns[j].transactions[k].length;
		   for(int l=0;l<L3;l++)
		   {
			os<<a.level_result[i].patterns[j].transactions[k].value[l].value;
			if(l != L3-1) os<<",";
		   }
		   os<<"}";
		}
		os<<">"<<endl;


	   }
	   os<<endl;


	}

}

ostream& operator<<(ostream& os, const Sequence& a)
{
	os<<"<";
	for(int i=0;i<a.length;i++)
	{
	   int L1 = a.transactions[i].length;
	   os<<"{";
	   for(int j=0;j<L1;j++)
	   {
		os<<a.transactions[i].value[j].value;
		if(j != L1 - 1) os<<",";
	   }
	   os<<"}";
	}
	os<<">";
} 

void Sequenceset_set::resize(int i)
{
	length = i;
	level_result.resize(i);

};


void seq_proj(Sequence s, Sequenceset& b)
{
	//cout<<"Problem!"<<endl;
	for(int i=0;i<b.length;i++)
        {
           if(b[i].contain(s) == 1) 
	   {
		//cout<<"i = "<<i<<endl;
		//b[i].display();
		//s.display();
		b[i].proj(s);
	   }

           else { b.remove(i); i--;}

        }

};

Item::Item()
{

};

Item::Item(int a, double b)
{	value = a; MIS = b; }

Item::Item(const Item& a)
{
	value = a.value;
	MIS = a.MIS;
}

void Item::display()
{
	cout<<value;
}

void Itemset::add(Item a)
{	value.push_back(a);
	length += 1;	}

Itemset::Itemset()
{	length = 0;	}

Itemset::Itemset(const Itemset& a)
{
	length = a.length;
	for(int i=0;i<length;i++)
	{
	   Item *temp = new Item;
	   temp->value = a.value[i].value;
	   temp->MIS = a.value[i].MIS;
	   value.push_back(*temp);

	}

}

double Itemset::contain(int a)
{
	for(int i=0;i<length;i++)
	if(value[i].value == a) return value[i].MIS;
	return 0.0;
}

int Itemset::contain(Item& a)
{
	for(int i=0;i<length;i++)
	if(value[i].value == a.value) return 1;
	return 0;
}

Item& Itemset::operator[](const int i)
{
	return value[i];

};

void Itemset::remove(int i)
{
	if(i>-1 && i<length)
	{
		value.erase(value.begin() + i);	
		length--;
	}

};

int Itemset::contain(Itemset& a)
{
	//cout<<"Problem here2"<<endl;
	//this->display();
	//a.display();
	if(length >= a.length)
	{
	   int i=0,j=0;

	   while(i<length && j<a.length)
	   {
		if(value[i].value == a[j].value)
		{
		   if(j == a.length - 1) return 1;
		   j++;
		}		
		i++;

	   }
	   return 0;

	}
	else return 0;

};

void Itemset::proj(Itemset& a)
{
	int i=0,j=0;
	while(j<a.length)
	{
	   if(value[i].value == a[j].value)
	   {
		if(i != j) cout<<"error occurred!"<<endl;
		if(j == a.length - 1) return;
		else if(j < a.length - 1)
		{
		   i++; j++;

		}

	   }
	   else if(value[i].value != a[j].value)
	   {
		value.erase(value.begin() + i);
		length--;

	   }


	}	

};

void Itemset::display()
{
	cout<<"{";
	for(int i=0;i<length;i++)
	{
	   value[i].display();
	   if(i != length - 1) cout<<",";

	}
	cout<<"}";

};

Sequence::Sequence()
{	length = 0;	}

Sequence::Sequence(const Sequence& a)
{
	length = a.length;
	for(int i=0;i<length;i++)
	{
	   Itemset *temp = new Itemset(a.transactions[i]);
	   //temp(a[i]);
	   transactions.push_back(*temp);

	}

};

void Sequence::add(Itemset a)
{	transactions.push_back(a);
	length += 1;	}

void Sequence::add(Item a)
{
	Itemset *p;
	p = new Itemset;
	p->add(a);
	transactions.push_back(*p);
	length += 1;

}

int Sequence::contain(Item& a)
{
	for(int i=0;i<length;i++)
	{
	   //cout<<"a.value = "<<a.value<<endl;
	   if(transactions[i].contain(a) == 1)
		return 1;
	}
	return 0;
};

Itemset& Sequence::operator[](const int i)
{
	return transactions[i];

};

void Sequence::remove(int i)
{
	if(i>-1 && i<length)
	{
		transactions.erase(transactions.begin() + i);
		length--;
	}

};

void Sequence::remove(int i,int j)
{
	if(i>-1 && i<length)
	{
	   transactions[i].remove(j);

	   if(transactions[i].length == 0)
	   {
		transactions.erase(transactions.begin() + i);
		length--;
	   }

	}

};

int Sequence::contain(Sequence& a)
{
	if(length >= a.length)
	{
	   int i=0,j=0;
	   while(i<length)
	   {

		if(transactions[i].contain(a[j]) == 1)
		{
		   if(j==a.length-1) return 1;
		   j++;
		}
		i++;
	   }

	   return 0;
	}
	else return 0;

}; 

void Sequence::proj(Sequence& a)
{
	int i=0,j=0;
	while(j<a.length && i<length)
	{
	   if(transactions[i].contain(a[j])==1)
	   {
		if(i != j) cout<<"error occurred 1"<<endl;
		if(j!=a.length - 1)
		{
		   transactions.erase(transactions.begin() + i);
		   transactions.insert(transactions.begin() + i, a[j]);

		}

		else if(j == a.length - 1)
		{

		   transactions[i].proj(a[j]);
		   return;


		}
		i++; j++;

	   }

	   else if(transactions[i].contain(a[j]) == 0)
	   {
		transactions.erase(transactions.begin() + i);
		length--;

	   }
	   

	}	


};

int Sequence::size()
{
	int s=0;
	for(int i=0;i<length;i++)
	{
	   s += transactions[i].length;
	}
	return s;

};

void Sequence::inc_in(Item a)
{
		
	transactions[length - 1].add(a);

};

void Sequence::inc_out(Item a)
{
	Itemset *temp = new Itemset;
	temp->add(a);
	transactions.push_back(*temp);

};

void Sequence::display()
{
	cout<<"<";
	for(int i=0;i<length;i++)
	{
	   transactions[i].display();

	}
	cout<<">"<<endl;

}

Sequenceset::Sequenceset()
{	length = 0;	}

Sequenceset::Sequenceset(const Sequenceset& a)
{
	length = a.length;
	for(int i=0;i<length;i++)
	{
	
	   Sequence *temp = new Sequence(a.patterns[i]);
	   patterns.push_back(*temp);

	}


}

void Sequenceset::add(Sequence a)
{	patterns.push_back(a);
	length += 1;	}

void Sequenceset::add(Item a)
{
	Sequence *p;
	p = new Sequence;
	p->add(a);
	patterns.push_back(*p);
	length += 1;

}

Sequence& Sequenceset::operator[](const int i)
{
	return patterns[i];

};

void Sequenceset::remove(int i)
{
	if(i>-1 && i<length)
	{
		patterns.erase(patterns.begin() + i);
		length--;
	}
	else cout<<"error!, remove a indice out of the class range"<<endl;


};

void Sequenceset::remove(int i,int j,int k)
{
	if(i>-1 && i<length)
	{
	   patterns[i].remove(j,k);

	   if(patterns[i].length == 0)
	   {
		patterns.erase(patterns.begin() + i);
		length--;

	   }

	}
};

int Sequenceset::freq(Item a)
{
	int i=0;
	for(int j=0;j<length;j++)
	{
	   if(patterns[j].contain(a) == 1) i++;

	}
	return i;

};

int Sequenceset::freq(Sequence a)
{
	int i=0;
	for(int j=0;j<length;j++)
	{
	   if(patterns[j].contain(a) == 1) i++;

	}
	return i;


};

void Sequenceset::display()
{
	for(int i=0;i<length;i++)
		patterns[i].display();
	cout<<endl;

};

void Sequenceset::resize(int i)
{
	length = i;
	patterns.resize(i);

};

int max_sd(Sequence& s, map<int,int>& sup)
{
	int min,max;
	min = max =0;
	for(int i =0 ;i<s.length;i++)
	   for(int j=0;j<s[i].length;j++)
	   {
		if(i==0&&j==0) min = max = sup[s[i][j].value];
		else if(sup[s[i][j].value] < min) min = sup[s[i][j].value];
		else if(sup[s[i][j].value] > max) max = sup[s[i][j].value];


	   }

	return max - min;

};

void r_prefix(Item& a, Sequence& s, Sequenceset& b, Sequenceset_set& Result, map<int, int>& SUP,double SDC)
{




        if(b.length >= a.MIS)
{

        Sequenceset b_proj(b);
        seq_proj(s,b_proj);

        for(int i=0;i<b_proj.length;i++)
        {
           if(b_proj[i].contain(a) == 0)
           {
                b_proj.remove(i);
                i--;
		
           }
        }

	if(b_proj.length < a.MIS) return;	
        int d1,d2;
        d1 = s.length;
        d2 = s[d1-1].length;

        Itemset *temp1 = new Itemset;
        Itemset *temp2 = new Itemset;
        for(int i = 0; i<b_proj.length; i++)
        {
           for(int j = d1 - 1; j<b_proj[i].length; j++)
           {
		if(j == d1-1 && b_proj[i][j].length > d2)
		{

                   for(int k = d2; k<b_proj[i][j].length; k++)
                   {
                        /*if(temp1->contain(b_proj[i][j][k]) == 0)
                        {
			   if(s.size() == 1) { 
				if(s[0][0].value == a.value)
					temp1->add(b_proj[i][j][k]);
				else if(b_proj[i][j][k].value == a.value)
					{temp1->add(b_proj[i][j][k]); break;}	

			   } 
                           else temp1->add(b_proj[i][j][k]);

                        }*/
			if(temp1->contain(b_proj[i][j][k]) == 0) temp1->add(b_proj[i][j][k]);
                   }

                }
                else if(j > d1 -1 )
                {
		   for(int k = 0;k<b_proj[i][j].length;k++)
		   {
                        /*if(temp2->contain(b_proj[i][j][k]) == 0)
                        {
			   if(s.size() == 1) { 
				if(s[0][0].value == a.value)
					temp2->add(b_proj[i][j][k]);
				else if(b_proj[i][j][k].value == a.value)
				{temp2->add(b_proj[i][j][k]); break;}	

			   } 
                           else temp2->add(b_proj[i][j][k]);

                        }*/
			if(temp2->contain(b_proj[i][j][k]) == 0) temp2->add(b_proj[i][j][k]);

		   }
		}

           }

        }

        int SIZE = s.size();
        Sequenceset pool;
        if(temp1->length != 0)
        {
           for(int i=0;i<temp1->length;i++)
           {

                //Sequence s1(s);
		Sequence *s1 = new Sequence(s);
                s1->inc_in((*temp1)[i]);
		
                if(b.freq(*s1) >= a.MIS)
                {
                   pool.add(*s1);
		   if(s1->contain(a) == 1 && max_sd(*s1,SUP) <= SDC)
                   Result[SIZE].add(*s1);
                }



           }
        }

        if(temp2->length != 0)
        {
           for(int i=0;i<temp2->length;i++)
           {
                Sequence* s2= new Sequence(s);
		Itemset *s2_l = new Itemset;
		s2_l->add((*temp2)[i]);
		s2->add(*s2_l);	
		
                if(b.freq(*s2) >= a.MIS)
                {
			
                   pool.add(*s2);
		   if(s2->contain(a) == 1 && max_sd(*s2,SUP) <= SDC)
                   Result[SIZE].add(*s2);

                }

           }
        }

        for(int i=0;i<pool.length;i++)
        {
             r_prefix(a,pool[i],b_proj,Result,SUP,SDC);

        }




}
	return;
};



void r_MSPS(Item& a, Sequenceset& b, Sequenceset_set& Result, map<int,int>& SUP,double SDC)
{
//find length one frequent sequence (frequency larger than MIS(a)), the do prefix_span for each sequence
        Itemset c;
        for(int i=0;i<b.length;i++)
        {
           for(int j=0;j<b[i].length;j++)
           {
                for(int k=0;k<b[i][j].length;k++)
                {
                   if(c.contain(b[i][j][k]) == 0) c.add(b[i][j][k]);

                }
           }

        }
        int COUNT = 0;
        for(int i=0;i<c.length - COUNT;i++)
        {

           if(b.freq(c[i]) < c[i].MIS) c.remove(i);
           i--;
           COUNT++;

        }
        Sequenceset temp;

        for(int i=0;i<c.length;i++)
        {
           Sequence temp2;
           temp2.add(c[i]);
           temp.add(temp2);
           if(c[i].value == a.value)
	   {
		Result[0].add(temp2);
	   }
        }
        for(int i=0;i<temp.length;i++)
        {

           r_prefix(a, temp[i], b,Result,SUP,SDC);      //a- the main item, temp[i] the patter as prefix
                                                //b- the pattern database, Result- the final result

        }



};

int main()
{
	ifstream f1("para2-1.txt");
	Itemset Para;
	char a;
	int b;
	double c;
	double SDC;

	Sequenceset Main;
	Sequence *S = new Sequence; 
	Itemset *I = new Itemset;
	int light = 0;
	
	vector<int> para;
	map<int,double> M;
	if(!f1)
	{
	   cout<<"file can not open"<<endl;
	   return 0;
	}
	while(!f1.eof())
	{
	   if(light == 0)
	   {
		f1>>a;
		if(a == '(') light = 1;
		if(a == 'C') b = 0;
		if(a == '='&&b != 0) light = 2;
		if(a == '='&&b == 0) light = 5;
	   }	
	   else if(light == 1)
	   {
		f1>>b; light = 0; 
	   }
	   else if(light == 2)
	   {
		f1>>c;
		//Para.add(Item(b,c));	
		para.push_back(b);
		M[b] = c;
	//	cout<<"b = "<<b<<" and M[b] = "<<M[b]<<" and c= "<<c<<endl;
		light = 0;
	   }
	   else if(light == 5)
	   {
		f1>>SDC;

	   }
	   
	}
	f1.close();

	sort(para.begin(),para.end());
	

	for(vector<int>::size_type i=0; i<para.size();i++)
	{
	//   cout<<"para["<<i<<"] = "<<para[i]<<endl;
	   Para.add(Item(para[i],M[para[i]]));
	//	cout<<"Para[i] value and MIS are: "<<Para[i].value<<" "<<Para[i].MIS<<endl;	
	   Para.value[i].MIS *= 1200;
	   
	}

	light = 0;
	f1.open("data2.txt");
	if(!f1)
	{
		printf("file can not open");
		return 0;
	}
	
	while(!f1.eof())
	{
	   if( light == 0 ) 
	   {
		f1>>a;
	   	if(a == '<') { delete S; S = new Sequence; }
	   	if(a == '{') { delete I; I = new Itemset; light = 1; }
	   	if(a == '}') S->add(*I);
	   	if(a == '>') Main.add(*S);
	   	if(a == ',') { light = 1; }
	   }
	   else if ( light == 1)
	   {
	   	f1>>b;
		double temp = Para.contain(b);	
	   	I->add(Item(b,temp)); 
		light = 0;
	   }
	} 
	f1.close();

	Main.resize(Main.length - 1);
cout<<"the number of sequences is "<<Main.length<<endl;

	SDC = SDC*Main.length;
	//finding all freqent items;
	//vector<int> SUP;

	map<int,int> SUP;
	Sequenceset_set Result(10);
	Itemset F_items;
	for(int i=0;i<Para.length;i++)
	{
	   int count = 0;
	   for(int j=0;j<Main.length;j++)
	   {
		if(Main[j].contain(Para[i]) == 1)
		count ++;
	   }
	   //SUP.push_back(count);
	   SUP[Para[i].value] = count;
	   if(count >= Para[i].MIS) 
	   {
		F_items.add(Para[i]);
	   }

	}

 cout<<"here we test whether <{2,13}{5}> is a frequent pattern or not"<<endl;
 cout<<"the MIS value and SUP value for 2 is"<<M[2]*1200<<" "<<SUP[22]<<endl;
 cout<<"for 13 is "<<M[13]*1200<<" "<<SUP[13]<<endl;
 cout<<"for 5 is "<<M[5]*1200<<" "<<SUP[5]<<endl;
cout<<"SDC = "<<SDC<<endl;

/*
 Itemset t1,t2;
 Sequence test;
 t1.add(Para[1]);t1.add(Para[12]);t2.add(Para[6]);
 test.add(t1);test.add(t2);
 cout<<"the sequence is";test.display();
 cout<<"the frequency of this pattern is "<<Main.freq(test); 
cout<<"SDC = "<<SDC<<endl;
cout<<"the MIS value and SUP value for 22 is "<<M[22]*1200<<" "<<SUP[22]<<endl;
cout<<" for 13 is "<<M[13]*1200<<" "<<SUP[13]<<endl;
cout<<" for 3 is "<<M[3]*1200<<" "<<SUP[3]<<endl;
*/

	
	//for each frequent item, mining all patterns that contains it, while with a minimum support as it's minimum support
	for(int i=0;i<F_items.length;i++)
	{


////////if(F_items[i].value == 4){
	   Sequenceset temp;
	   for(int j=0;j<Main.length;j++)
	   {
		if(Main[j].contain(F_items[i]) == 1) 
		   temp.add(Main[j]);
		
	   }

	   //cout<<"temp.length = "<<temp.length<<endl;

	   for(int j=0;j<temp.length;j++)
	   {
		for(int k=0;k<temp[j].length;k++)
		{
		   if(k == -1) {
			j--; break;}
		   for(int l=0;l<temp[j][k].length;l++)
		   {
			if(fabs(SUP[temp[j][k][l].value] - SUP[F_items[i].value])>SDC 
			   || temp[j][k][l].MIS < F_items[i].MIS
			   || temp[j][k][l].MIS == F_items[i].MIS 
				&& temp[j][k][l].value < F_items[i].value)
			   //||temp[j][k][l].value < F_items[i].value)
			{
				temp.remove(j,k,l);
				if(l==0) 
				{ 
				   k--; 
				   if(k==-1) k=-2;
				   break;
					
				
				}
				
				else if(l>0) l--;
			}

		   }
		}
	   }
	   r_MSPS(F_items[i],temp,Result,SUP,SDC);	

	}

	Result.resize(7);
	ofstream data;
	data.open("result2-1.txt");
	//data<<Result;
	data<<"total number of sequences is "<<Main.length<<endl;
	data<<endl;
	for(int i=0;i<Result.length;i++)
	{
	    data<<"the number of length "<<i+1<<" sequential patterns is "<<Result[i].length<<endl;
	    for(int j =0;j<Result[i].length;j++)
	    {
		data<<"Pattern: ";
		data<<Result[i][j];
		//Result[i][j].display();
		data<<" Count: "<<Main.freq(Result[i][j])<<endl;


	    }
	    data<<endl;


	}



	
	return 0;
}

