#include<iostream>
#include<string>
#include<unordered_map>
#include <bits/stdc++.h>
using namespace std;

/*Well, this problem is known as 'serializing structured data' - basically it's the opposite of parsing. The thing is that you can't just 
dump the raw binary data of your in-memory data structure to a file - it won't be meaningful upon the next launch of your program when 
addresses change. You have to come up with a format that is able to describe your data structure and write that to the file. Then, of course, 
you'll also have to write a parser for that format if you want to recover the data structure from the file later.*/

class Details
{	public:
		string number;
		string email;
	public: 
		Details(string number, string email)
		{	
		
			this->number=number;
			this->email=email;
		}
};

class Trie
{
	public:
		unordered_map<char, Trie*> map;
		bool isWord;
		Details* details;

	 
		/*Trie()
		{
			//Trie* head=new Trie();

		}*/


	void setDetails(Trie* node, string number, string email)
	{
		if (node->isWord==true)
		{
			node->details=new Details(number, email);
			cout<<"\nIn setDetails()"<<endl;
			cout<<"node->number - "<<node->details->number<<endl;
			cout<<"node->email - "<<node->details->email<<endl;
		}
	}

	Trie* NewTrieNode()
	{
		Trie* node=new Trie();
		node->isWord=false;
		
		return node;	
	}

	void insert(Trie*& head, char* str, string number, string email)
	{

		if (head==NULL)
		{
			head=NewTrieNode();
		}

		Trie* current=head;
		while(*str)
		{
			if(current->map.find(*str)==current->map.end())
				current->map[*str]=NewTrieNode();

			current=current->map[*str];
			str++;
		}
		current->isWord=true;
		cout<<"\nin insert() - going to setDetails()"<<endl;
		setDetails(current, number, email);


	}

	void displayContactsSuggestions(Trie* currNode, string prefix)
	{
		//cout<<"\n\nin DCS() - prefix - "<<prefix<<endl;
		if (currNode->isWord)
		{
			cout<<endl;
			cout<<"*************************************************************************"<<endl;
			cout<<"* Name - "<<prefix<<"                                                    "<<endl;
			cout<<"* Number - "<<currNode->details->number<<"                               "<<endl;
			cout<<"* Email - "<<currNode->details->email<<"                                 "<<endl;
			cout<<"*************************************************************************"<<endl;
			
		}
		//cout<<"\n\n\n\n\n\nin DCS() - currNode - "<<currNode<<endl;
		string alpha="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		//for(char i='a';i<='z';i++)
		for(auto i:alpha)
		{
			
			Trie* nextNode=currNode->map[i];
			if(nextNode!=NULL)
				displayContactsSuggestions(nextNode, prefix+char(i));
		}
	}

	void displayContacts(Trie*& head, string str)
	{
		Trie* prevNode=head;
		string prefix="";
		

		for (int i = 0; i < str.length(); i++)
		{
			//cout<<"\nin DisplayContact()before prefix statement - prefix - "<<prefix<<" i - "<<i<<endl;
			prefix+=str[i];
			//cout<<"\nin DisplayContact()after prefix statement - prefix - "<<prefix<<" i - "<<i<<endl;

			char lastChar=prefix[i];

			//cout<<"\n\n\n\n\nprevNode - "<<prevNode<<"\n\n\n\n\n";


			Trie* currNode=prevNode->map[lastChar];
			//sTrie* currentNode=currNode; //after displaying the word, when it exits back to this loop the address in currNode becomes 0
			//cout<<"\n\n\n\n\n - currentNode"<<currentNode<<"\n\n\n\n\n";

			if (currNode==NULL)
			{
				cout<<"\nNo results found for "<<"\""<<prefix<<"\"\n";
				i++;
				//break;

			}
			else
			{

			
				cout<<"\nSuggestions based on "<<prefix<<" are.....\n";
				displayContactsSuggestions(currNode, prefix);
				prevNode=prevNode->map[lastChar];
				/*cout<<"i - "<<i<<endl;
				cout<<"map[lastChar] - "<<map[lastChar]<<endl;
				
				cout<<prevNode;*/
			}
		}
	}

	int modifyContacts(Trie*& head, char* str, string name, string number, string email)
	{
		try
		{

		
			//cout<<"Reached 1"<<endl;
			if(head==NULL)
			{
				//cout<<"Reached 2"<<endl;
				cout<<"Contats empty";
				//cout<<"Reached 3"<<endl;
				return 0;
			}
			//cout<<"Reached 4"<<endl;

			Trie* current=head;
			//cout<<"Reached 5"<<endl;
				while(*str)
				{
					//cout<<"Reached 6"<<endl;
					if(current->map.find(*str)==current->map.end() && current->isWord==false)
					{
						//cout<<"Reached 7"<<endl;
						//current->map[*str]=NewTrieNode();
						cout<<"No contacts found for "<<name;
						//cout<<"Reached 8"<<endl;
						return 0;
					}
					//cout<<"Reached 9"<<endl;
					

					current=current->map[*str];
					//cout<<"Reached 10"<<endl;
					str++;
					//cout<<"Reached 11"<<endl;
				}
				//cout<<"Reached 12"<<endl;
				if(current->isWord==true)
				{
					//cout<<"Reached 13"<<endl;
					if(current->details==NULL)
					{
						//cout<<"Reached 14"<<endl;
						current->details=new Details(number, email);
						//cout<<"Reached 15"<<endl;
						return 0;
					}
					//cout<<"Reached 16"<<endl;
					else
					{
						//cout<<"Reached 17"<<endl;
						current->details->number=number;
						//cout<<"Reached 18"<<endl;
						current->details->email=email;
						//cout<<"Reached 19"<<endl;
						return 0;
					}
					//cout<<"Reached 20"<<endl;
				}
				else
				{
					cout<<"\nNo contact named "<<name<<" found."<<endl;
				}
				//cout<<"Reached 21"<<endl;
			//cout<<"Reached 22"<<endl;
		}
		catch(...)
		{
			cout<<"\nNo contact named "<<name<<" found.";
		}
	}

	int deleteContacts(Trie*& head, char* str, string name)
	{	//cout<<"Reached 1"<<endl;
		if(head==NULL)
		{
			//cout<<"Reached 2"<<endl;
			cout<<"Contats empty";
			//cout<<"Reached 3"<<endl;
			return 0;
		}
		//cout<<"Reached 4"<<endl;

		Trie* current=head;
		//cout<<"Reached 5"<<endl;
			while(*str)
			{
				//cout<<"Reached 6"<<endl;
				if(current->map.find(*str)==current->map.end() && current->isWord==false)
				{
					//cout<<"Reached 7"<<endl;
					current->map[*str]=NewTrieNode();
					cout<<"No contacts found for "<<name;
					//cout<<"Reached 8"<<endl;
					return 0;
				}
				//cout<<"Reached 9"<<endl;
				

				current=current->map[*str];
				//cout<<"Reached 10"<<endl;
				str++;
				//cout<<"Reached 11"<<endl;
			}
			//cout<<"Reached 12"<<endl;
			if(current->isWord==true)
			{
				current->isWord=false;
				free(current->details);
				current->details=NULL;
				//cout<<"Reached 13"<<endl;
				//cout<<"Reached 20"<<endl;
			}
			else
			{
				cout<<"\nNo contact named "<<name<<" found to delete."<<endl;
			}
			//cout<<"Reached 21"<<endl;
		//cout<<"Reached 22"<<endl;
	}

};






	/*Trie* prevNode=head;
	string prefix="";

	if(currNode->isWord==true)
	{
		if(currNode->details!=NULL)
		{
			currNode->details->number=number;
			currNode->details->email=email;
			return 0;

		}
	}


	Trie* currNode, nextNode;
	currNode=prevNode->prevNode->map[name[0]];
	for(int i=0;i<name.length();i++)
	{
		nextNode=currNode->map[name[i]];
		if(nextNode!=NULL)
		{
			modifyContacts(nextNode, )
		}

	}*/





int main()
{

	Trie* t;
	
	

	t=NULL;

	
	/*t->insert(t, "Madhu", "6379659187", "madhu2000u@gmail.com");
	t->insert(t, "Madhusudhanan", "9894063625", "madhusudh2000u@gmail.com");
	t->insert(t, "Kishore", "4654678987", "madhu2000ukishore2003u@gmail.com");
	t->insert(t, "Krishna", "1081081081", "krsna@goloka.com");
	t->insert(t, "Kripasindhu", "8493849102", "Kripasindhu@gmail.com");
	t->insert(t, "Geeksfogeeks", "8493845671", "geeks@gmail.com");
	t->insert(t, "gforgeeks", "8493845671", "geeks@gmail.com");
	t->insert(t, "geeksquiz", "8493845671", "geeks@gmail.com");*/
	string ch="y";
	while(ch=="y")
	{
		cout<<"********************************************************************************************************"<<endl;
		cout<<"*                                     1 - Add Contacts                                                 *"<<endl;
		cout<<"*                                     2 - Search Contacts                                              *"<<endl;
		cout<<"*                                     3 - Modify Contacts                                              *"<<endl;
		cout<<"*                                     4 - Delete Contacts                                              *"<<endl;
		cout<<"*                                     5 - Exit                                                         *"<<endl;
		cout<<"********************************************************************************************************"<<endl;
		int choice;
		cout<<"\nEnter your Choice - ";
		cin>>choice;cout<<endl;
		if(choice==1)
		{
			string number, email;
			string name;

			cout<<"		Enter name - ";cin>>name;cout<<endl;
			char* n=&name[0];
			//cout<<"\n&name - "<<*n<<endl;
			cout<<"     Enter mobile number - ";cin>>number;cout<<endl;
			cout<<"     Enter email - ";cin>>email;cout<<endl;
			t->insert(t, n, number, email);

		}
		else if(choice==2)
		{
			string name;
			//if(t==NUll) cout<<"Contacts is empty";
			//else
			//{
			cout<<"\nEnter the contact name to be searched - ";cin>>name;
			t->displayContacts(t, name);
			//}

		}
		else if(choice==3)
		{
			string name,number,email;
			cout<<"\nEnter the contact name that you want to modify - ";cin>>name;
			cout<<"\nEnter the new number - ";cin>>number;
			cout<<"\nEtner the new email - ";cin>>email;
			char*n= &name[0];
			t->modifyContacts(t, n, name, number, email);
		}
		else if(choice==4)
		{
			string name;
			cout<<"\nEnter the contact name that you want to delete - ";cin>>name;
			char* n=&name[0];
			t->deleteContacts(t, n, name);
		}
		else if(choice==5) exit(0);

		cout<<"\nWoudl you like to continuer?[y/n] - ";
		cin>>ch;
	}

	//cout<<"\n\nDisplaying Contacts\n\n";
	//t->displayContacts(t,"Krip");
}
