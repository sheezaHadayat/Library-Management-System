#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class book
{
    public:
    string title;
    string author;
    string publisher;
    int year;
    string isbn;
    book* next;
    book(string, string, string, int, string, book*);
};

book::book(string tempTitle, string tempAuthor, string tempPublisher, int tempYear, string tempIsbn, book* tempNext)
{
    title=tempTitle;
    author=tempAuthor;
    publisher=tempPublisher;
    year=tempYear;
    isbn=tempIsbn;
    next=tempNext;
}

typedef book* bookPtr;

void getline(istream &stream, string &str, char delimiter)
{    char temp[500];

    stream.get(temp, 500, delimiter);
    stream.ignore(500, delimiter);
    str = temp;
}

void getline(istream &stream, int &num, char delimiter)
{    int temp;

    stream >> temp;
    stream.ignore(500, delimiter);
    num= temp;
}

void readFile(bookPtr &root);
void insert (bookPtr &root);
void delTitle(bookPtr &root);
bookPtr locateNode(bookPtr temp, string titl);
void Check();
void delIsbn(bookPtr &root);
bookPtr locateNodeIsbn(bookPtr temp, string isb);
void searchIsbn(bookPtr temp);
void printList(bookPtr temp);
void printAuthor(bookPtr temp);
void saveFile(bookPtr temp);
int countNodes(bookPtr temp);


void  readFile(bookPtr &root)
{
	Check();
    int numBooks, yea;
    string titl, aut, pub, isb;
    ifstream infile ("books.txt", ios::in);
    infile >> numBooks;
    infile.ignore(500,'\n');
    for (int count = 0; count < numBooks; count++)
    {
        getline(infile, titl, '\n');
        getline(infile, aut, '\n');
        getline(infile, pub, '\n');
        getline(infile,yea, '\n');
        getline(infile, isb, '\n');

        root = new book (titl, aut, pub, yea, isb, root);
    }
}

void  Check()
{
	ifstream infile;

	infile.open("books.txt");
	if (!infile.is_open())
	{
		cout<<"Error file is not open!\n";
	}
	else
	{
		cout <<"file is open successfully ; \n";
	} 
	
}

//add  a book 

void insert (bookPtr &root)
{
    string titl, aut, pub, isb;
    int yea;

    cout << "Title:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, titl, '\n');
    cout << "Author:\t\t\t";
    getline(cin, aut, '\n');
    cout << "Publisher:\t\t";
    getline(cin,pub, '\n');
    cout << "Year:\t\t\t";
    getline(cin,yea, '\n');
    cout << "ISBN:\t\t\t";
    getline(cin, isb, '\n');

    root = new book (titl, aut, pub, yea, isb, root);
}
//delete book by title 
void delTitle(bookPtr &root)
{
    string titl;

    cout << "Book Title:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, titl, '\n');

    bookPtr p = locateNode(root, titl);

    if (p == NULL)
        cout << "\nDeletion cannot be done.\n\n";
    else if (root == p)
        root = p->next;
    else
    {
        bookPtr q = root;
        while (q->next != p)
            q = q->next;
        q->next = p->next;
    }
    delete p;
}

// locate node /position where want to del

bookPtr locateNode(bookPtr temp, string titl)
{
    while (temp != NULL)
    {
        if (temp->title == titl)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// del book by isbn

void delIsbn(bookPtr &root)
{
    string isb;

    cout << "Book ISBN:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, isb, '\n');

    bookPtr p = locateNodeIsbn(root, isb);

    if (p == NULL)
        cout << "\nDeletion cannot be done.\n\n";
    else if (root == p)
        root = p->next;
    else
    {
        bookPtr q = root;
        while (q->next != p)
            q = q->next;
        q->next = p->next;
    }
    delete p;
}
// locate isbn position /node  for del

bookPtr locateNodeIsbn(bookPtr temp, string isb)
{
    while (temp != NULL)
    {
        if (temp->isbn == isb)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
//search  book by isbn

void searchIsbn(bookPtr temp)
{
    string isb;

    cout << "Book ISBN:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, isb, '\n');

    while (temp != NULL)
    {
        if (isb == temp->isbn)
        {
            cout << temp->title << "\n";
            cout << temp->author << "\n";
            cout << temp->publisher << "\n";
            cout << temp->year << "\n";
            cout << temp->isbn << "\n\n";
        }
        temp = temp->next;
    }
   // cout << "Not found\n";
}
// print all books
void printList(bookPtr temp)
{
    while (temp != NULL)
    {
        cout << temp->title << "\n";
        cout << temp->author << "\n";
        cout << temp->publisher << "\n";
        cout << temp->year << "\n";
        cout << temp->isbn << "\n\n";
        temp = temp->next;
    }
    cout << "\n";
}
//print all books by auther 

void printAuthor(bookPtr temp)
{
    string aut;

    cout << "Author name:\t\t\t";
    cin.ignore(500,'\n');
    getline(cin, aut, '\n');

    while (temp != NULL)
    {
        if (temp->author == aut)
        {
            cout << temp->title << "\n";
            cout << temp->author << "\n";
            cout << temp->publisher << "\n";
            cout << temp->year << "\n";
            cout << temp->isbn << "\n\n";
        }
        temp = temp->next;
    }
    cout << "\n";
}
//save book data

void saveFile(bookPtr temp)
{
    int count = countNodes(temp);

    ofstream outFile("books.txt",ios::out);

    outFile << count << "\n";
    while (temp != NULL)
    {
        outFile << temp->title << "\n";
        outFile << temp->author << "\n";
        outFile << temp->publisher << "\n";
        outFile << temp->year << "\n";
        outFile << temp->isbn << "\n";
        temp = temp->next;
    }
    cout << "\n";
}

// count node of books
int countNodes(bookPtr temp)
{
    int countB = 0;
    while (temp != NULL)
    {
        countB++;
        temp = temp->next;
    }
    return countB;
}




//read lines for student data

int count_lines(const char *filename)
{
	ifstream infile("saved.txt");
	string name;
	int count =0;

	while(getline(infile,name))
	{
		++count;
	}
	return count ;

}
//save student data

void savedata(bookPtr temp,string name,string dept,string session)
{
        ofstream outFile;
        outFile.open("saved.txt",ios::app);
		
	ifstream infile("saved.txt",ios::in);
	string title,bs,namee,iss,na;
	string deptt,sessionn;
	int totall;

	const char filename[]="saved.txt";
	int count=count_lines("saved.txt");

	for(int i=0;i<count-2;i++)

	{
		getline(infile,na);
	}
	

	for(int i=0;i<2;i++)
	
	{	
		infile>>bs;
		infile>>iss;
		infile>>namee;
		infile>>sessionn;
		infile>>deptt;
		infile>>totall;

    	if(namee==name &&deptt==dept && sessionn==session )
		{
			if(totall<5)
			{
     		goto g;
			}
			else
			{
				cout<<"\tSORRY We Cannot issue anymore Book\n";
				cout<<"\tYou Already Have ISsued 5 Books\n";
				goto k;
			}
		}
		else
		{
		
		}
	
	}

	
 	
    	cout<<"New Qamr\n";
		outFile << temp->title<<"\t\t";
		outFile << temp->isbn << "\t";
        outFile << name << "\t\t";
		outFile << session << "\t";
		outFile << dept << "\t\t";
		outFile<< "1";
		outFile<<endl;
		
	    goto k;




g:		cout<<"Already Issue Boosks=\t"<<totall;
		outFile << temp->title<<"\t\t";
		outFile << temp->isbn << "\t";
        outFile << name << "\t\t";
		outFile << session << "\t";
		outFile << dept << "\t\t";
		outFile<<totall+1;
		outFile<<endl;
		cout<<"\nTotal Issue -->"<<totall+1;
	
    k:

	infile.close();
	outFile.close();
		
}

// issue book to student

int issueBook(bookPtr temp)
{
	string nameofbook,name,dept,session;
	cout<<"\nEnter NAme of Book YOu Want\n";
	cin>>nameofbook;
	 
    while (temp != NULL)
    {
		if (nameofbook == temp->title)
        {
        cout<<"Successfully Found\n";
		
  		cout<<"First Enter Name:-->";
		cin>>name;
		
		cout<<"Enter Department:--> ";
		cin>>dept;
		
		cout<<"Enter Session:-->";
		cin>>session;
	    savedata(temp,name,dept,session);
		temp = temp->next;
		return 2;

		}
        temp = temp->next;
    }

	return 1;
}









int main()
{
    int choice,j,n;
    bookPtr root = NULL;
    readFile(root);
	system("color f1");

	cout<<"Please Login First TO Access the Menu \n";
	a:  cout<<"Username-->";
	string username;
	string  password;

	cin>>username;
    cout<<"\npassword-->";
	cin>>password;
	if(username=="Sheeza" && password=="123")
	{
		goto j;
	}
	else
	{ 
	 cout<<"Please Enter Correct Information\n";	
	 goto a;

	}
	
j:	do
    {
        cout << "\t\t<<=========================>>";
        cout << "\n\t\t>>LIBRARY MANAGEMENT SYSTEM<<";
        cout << "\n\t\t<<=========================>>";
        cout << "\n\nMenu: Select your option\n\n";
        cout << "(1) Add a book to the list\n";
        cout << "(2) Delete a book based on Title\n";
        cout << "(3) Delete a book based on ISBN\n";
        cout << "(4) Search for a book by ISBN.\n";
        cout << "(5) List all books.\n";
        cout << "(6) Issue Books.\n";
		cout << "(7) Quit.\n\n";
        cout << "Enter your choice ---> ";
		cin >> choice;

        if (1 <= choice && choice <= 6)
        {
            switch (choice)
            {
            case 1:
                insert(root);
                break;
            case 2:
                delTitle(root);
                break;
            case 3:
                delIsbn(root);
                break;
            case 4:
                searchIsbn(root);
                break;
            case 5:
                printList(root);
                break;
            case 6:
             n=issueBook(root);
			  if(n==2)
			  {    cout <<endl;}
			  else
			  { 
				  cout << "\tNot Found\n";
			  }//  printAuthor(root);
                break;
            default:
                cout << "Invalid choice.  Enter again.\n\n";
                break;
            }
        }
    }
    while (choice != 7);
	
	saveFile(root);
	//save(root);
    return 0;
}



