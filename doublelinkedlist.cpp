#include <iostream>
using namespace std;

// membuat struktur untuk object double linkedlist
struct Node
{
    // deklarasi noMhs dan name untuk menampung data
    int noMhs;
    string name;
    // deklarasi pointer next dan pref untuk penunjukkan data sebelum dan sesudah
    Node *next;
    Node *prev;
};

// deklarasi pointer START dan pemberian nilai
Node *START = NULL;

// deklarasi prosedur addNode
void addNode()
{
    // pembuatan node dan pemberian value untuk data noMhs dan name
    Node *newNode = new Node(); // step 1 Buat node baru
    cout << "\nEnter the roll number of the student: ";
    cin >> newNode->noMhs; // assign value to theh data field of the new node
    cout << "\nEnter the name of the student: ";
    cin >> newNode->name; // assign value to theh data field of the new node

    // Insert the new node in the list 
    //kondisi jika star == null atau noMhs node baru <= noMhs start
    if (START == NULL || newNode->noMhs <= START->noMhs)
    {
        //step 2: insert new node at the beginning
        // kondisi jika start tidak kosong dan noMhs node baru sma dengan noMhs
        if (START != NULL && newNode->noMhs == START->noMhs)
        {
            cout << "\033[31mDuplicate roll numbers not allowed\033[0m" << endl;
            return;
        }
        //if the list is empaty, make the new node the START
        //jika list kosong, maka node text nya adalah START
        newNode->next = START; // step3; make the new node point to the fisrt node
        // kondisi jika START tidak memiliki nilai atau tidak kosong 
        if (START != NULL)
        {
            START->prev = newNode; // step 4; make the first node point to the new node 
        }
        //memberi nilai prev = null dan start = node baru 
        newNode ->prev = NULL; // step 5: make the new node point to NULL
        START = newNode; // step 6: make the new node the first node 
    }
    //kondisi jika semua kondisi if tidak terpenuhi
    else
    {

        //insert the new node in the middle or at the end
        //set nilai current = start dan nilai previous = null
        Node *current = START; // step1.a: start from the first node
        Node *previous = NULL; //step 1.b: previous node is Null intially

        //Looping selama current != null dan noMhs dari current lebih kecil dari noMhs node baru
        while (current !=NULL && current->noMhs < newNode->noMhs)
        {                           //step 1.c: traverse the list to find the correct position
            previous = current;     // step 1.d: move the previous to the current node
            current = current->next; //step1.e: move the current to the next  node 
        }

        // set nilai next node baru = current dan prev node baru = previous 
        newNode->next = current;  //step 4: make the next field of the new node 
        newNode ->prev = previous; // step 5: make the previos field of teh new node

        //kondisi jika current tidak sama dengan null
        if (current != NULL)
        {
            current->prev = newNode; //step 6: make the previoud field of the current node point to the new node    
        }
        
        //kondisijika previous tidak sama dengan null
        if (previous != NULL)
        {
            previous->next = newNode; //step 7: make the next field of the previos node point to the new node 
        }
        // kondisi jika if previous sama dengan NULL
        else
        {
            // if previous is still NULL, it means newNode is now the first node
            START = newNode;
        }
    }
}

//pembuatan functional search untuk mencari data
bool search(int rollNo, Node **previous, Node **current)
{
    *previous = NULL;
    *current = START;
    while (*current != NULL && (*current)->noMhs != rollNo)
    {
        *previous = *current;
        *current = (*current)->next;
    }
    return (*current != NULL);
}

//pembuatan prosedur delete untuk menghapus data
void deleteNode()
{
  Node *previous, *current;
  int rollNo;
  
  cout << "\nEnter the roll number of the student whose record is to be delete:";
  cin >> rollNo; // step 3: get the roll number number to the deleted

  if (START == NULL)
  {
    cout << "List is empaty" << endl;
    return;
  }

current = START; // step 1: start from the fisrt node
previous = NULL;

//Located the node to be delate
while (current != NULL && current->noMhs != rollNo)
{
    previous = current;
    current = current->next;
}

if (current == NULL)
{
    cout << "\033[31mThe record with roll number "
    << rollNo << " not found\033[0m" << endl;
    return;
}

// node to be deleted in the first node
if (current = START)
{
    START = START->next; // step 2 : update the START pointer 
    if (START != NULL)
    {
        START->prev = NULL;
    }
}
else
{   // node to be deleted is not the first node 
    previous->next = current->next;
    if  (current->next != NULL)
    {   //if there's a successor, update  its prev pointer 
        current->next->prev = previous;
    }
}
    // release the memory of the node marked as current
    delete current;
    cout << "\x1b[32mRecord with roll number " << rollNo << "deleted\x1b[0m" <<endl;
}

// method untuk mengecek apakah list kosong
bool listEmpaty()
{
    return (START == NULL);
}

// prosedur traverse untuk menampilkan data secara urut
void traverse()
{
    if (listEmpaty())
    {
        cout << "\nList is empty" << endl;
    }
    else
    {
        cout << "\nRecords in ascending order of roll number are: " << endl;
        Node *currentNode = START;
        while (currentNode != NULL)
        {
            cout << currentNode->noMhs << endl;
            currentNode = currentNode->next;
        }
        cout << endl;
    }
}
// prosedure untuk menampilkan data secara urutan terbalik
void revtraverse()
{
    if (listEmpaty())
        cout << "\nList is empaty" << endl;
    else
    {
        cout << "\nRecords in descending order  of roll number are: " <<endl;
        Node *currentNode = START;
        while(currentNode->next != NULL )
            currentNode = currentNode->next;

        while (currentNode != NULL)
        {
            cout << currentNode->noMhs << " " << currentNode->name << endl;
            currentNode = currentNode->prev;
        }
    }
}

//prosedure untuk mencari data dan menampilkan data yang dicari jika ada 
void searchData()
{
    if (listEmpaty() == true )
    {
        cout << "\nList is empaty" << endl;
    }
    Node *prev, *curr;
    prev = curr = NULL;
    cout << "\nEnter the roll number of the student whoose record you want to search: ";
    int num;
    cin >>num;
    if (search(num, &prev, &curr) == false)
        cout << "\nRecord not found: " << endl;
    else
    {
        cout << "\nRecord found" <<endl;
        cout << "\nRoll Number: " << curr->noMhs << endl;
        cout << "\nName: " << curr->name << endl;
    }

}

int main()
{
    // perulangan selama bernilai benar untuk program utama double lineked list
    while (true)
    {
        try 
        {
            cout << "\nMenu" << endl;
            cout << "1. add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. view all records in the asscending order of roll number" << endl;
            cout << "4. view all records in the descending order of roll number" << endl;
            cout << "5. Search for a record in the list" << endl;
            cout << "6. Exit" << endl;
            cout << "\nEnter your choice (1-6): ";
            char ch;
            cin >> ch;

            
            switch (ch)
            {
                case '1':
                    addNode();
                    break;
                case '2':
                    deleteNode();
                    break;
                case '3':
                    traverse();
                    break;
                case '4':
                    revtraverse();
                    break;
                case '5':
                    searchData();
                    break;
                case '6':
                    return 0;
                default:
                    cout << "\nInvalid optional" <<endl;
                    break;
            
            }
        }
        catch (exception &e)
        {
            cout << " check for the values entered. " << endl;
        }
    }
}

