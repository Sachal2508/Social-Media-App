#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
//----------------------------Compile time error handle------------------------------------------------------------------------
class Page;
class User;
class Comment;
class Activity;
class Helper;
class SharedMemory;

class Base
{
private:
    char* ID;
public:
    Base() :ID(0)
    {

    }

    ~Base()
    {
        if (ID != 0)
        {
            delete[] ID;
        }
    }
    //              Virtual Functions

    virtual int GetTotalFriend() const
    {
        return 0;
    }
    virtual User** GetFriendList() const
    {
        return nullptr;
    }

    virtual void SharedMemories(const char* ID, const char* Description)
    {

    }
    virtual SharedMemory* SeeMemories()
    {
        return 0;
    }
    virtual void PrintFriendList()
    {

    }
    virtual void PrintLikedPages()
    {

    }
    virtual void SetFriendList(int a)
    {

    }
    virtual void SetLikedPages(int a)
    {

    }
    virtual void AddFriend(User* array)
    {

    }
    virtual void AddLikedPages(Page* array)
    {

    }
    virtual void PrintID()
    {
        cout << ID;
    }
    virtual void PrintName()
    {

    }
    virtual void PrintTimeLine(int, int, int)
    {

    }

    void SetID(char* ID)
    {
        this->ID = new char[strlen(ID) + 1];
        strcpy_s(this->ID, strlen(ID) + 1, ID);
    }

    bool compareId(const char* arr)
    {
        return strcmp(ID, arr) == 0;
    }
};
//-----------------------------Post--------------------------------------------------------------------------------------------
class Post
{
private:
    char* ID;
    char* Discription;
    int TotalLiked;
    int totalcomment;
    Base* sharedBy;
    Base** likedBy;
    Comment** commentBy;
    Activity* active;
protected:
    int day;
    int month;
    int year;
public:
    Post()
    {
        ID = nullptr;
        Discription = nullptr;
        day = 0;
        month = 0;
        year = 0;
        TotalLiked = 0;
        totalcomment = 0;
        likedBy = new Base * [10];        // Allocating space of 10 Post
        commentBy = new Comment * [10];   // Allocating space of 10 Comments 
        sharedBy = nullptr;
        active = nullptr;
    }

    // Getters

    int GetTotalComments() {
        return totalcomment;
    }

    Comment** GetComments() {
        return commentBy;
    }

    void ReadDataFromFile(istream& fin)
    {
        char Buffer[100];
        fin >> Buffer;
        ID = new char[strlen(Buffer) + 1];
        strcpy_s(ID, strlen(Buffer) + 1, Buffer);
        fin >> day >> month >> year;
        fin.ignore();
        fin.getline(Buffer, 99);
        Discription = new char[strlen(Buffer) + 1];
        strcpy_s(Discription, strlen(Buffer) + 1, Buffer);

    }
    void AddSharedBy(Base* obj)
    {
        sharedBy = obj;
    }
    void AddLikedBy(Base* obj)
    {
        if (TotalLiked < 10)
        {
            likedBy[TotalLiked] = obj;
            TotalLiked++;
        }
    }

    virtual void PrintTimeLine(int, int, int);
    void PrintComment(int, int, int);

    // It Print The Memories Era
    void MemoriesTimePrinter(int systemDay, int systemMonth, int systemYear)
    {
        if (systemDay == day && systemMonth == month && systemYear == year)
        {
            cout << "On This Day" << endl;
        }
        else if (systemYear != year)
        {
            cout << (systemYear - year) << " Years Ago" << endl;
        }
        else if (systemMonth != month)
        {
            cout << (systemMonth - month) << " Months Ago" << endl;
        }
        else if (systemDay != day)
        {
            cout << (systemDay - day) << " Days Ago" << endl;
        }
    }
    bool compareId(const char* arr)
    {
        return strcmp(ID, arr) == 0;
    }
    void PrintLikedBy()
    {
        for (int i = 0; i < TotalLiked; i++)
        {
            likedBy[i]->PrintID();
            cout << "-";
            likedBy[i]->PrintName();
            cout << endl;
        }
    }

    //              Adding Things
    void AddComments(Comment*& comment)
    {

        if (totalcomment < 11) {
            commentBy[totalcomment] = comment;
            totalcomment++;
        }
    }

    void TimePrinter(int systemDay, int systemMonth, int systemYear)
    {
        if (day > 0 && month > 0 && year > 0)
        {
            if (systemDay == day && systemMonth == month && systemYear == year)
            {
                cout << " (1h):" << endl;
            }
            else
            {
                cout << " (" << day << "/" << month << "/" << year << "):" << endl;
            }
        }
    }
    void AddActivities(Activity* activity)
    {
        active = activity;
    }
    void AddNewPostData(const char* POSTID, const char* DESCRIPTION)
    {
        if (ID != 0)
        {
            delete[] ID;
        }
        ID = new char[strlen(POSTID) + 1];
        strcpy_s(ID, strlen(POSTID) + 1, POSTID);

        if (Discription != 0)
        {
            delete[] Discription;

        }
        Discription = new char[strlen(DESCRIPTION) + 1];
        strcpy_s(Discription, strlen(DESCRIPTION) + 1, DESCRIPTION);
    }
    //              Virtual Destructor 
    virtual ~Post()
    {
        if (ID != 0)
        {
            delete[] ID;
        }
        if (Discription != 0)
        {
            delete[] Discription;
        }

        if (likedBy != 0)
        {
            delete[] likedBy;
        }

        if (commentBy != 0)
        {
            for (int i = 0; i < totalcomment; i++)
            {
                delete commentBy[i];
            }
            delete[] commentBy;
        }

        if (active != 0)
        {
            delete active;
        }
    }

};
//-----------------------------Memory------------------------------------------------------------------------------------------
class SharedMemory : public Post
{
private:
    Post** sharedmemory;
    int totalsharedmemories;

public:
    SharedMemory()
    {
        sharedmemory = nullptr;
        totalsharedmemories = 0;
    }
    void CombineMemories(Post**& memory, const int totalmemory)
    {
        sharedmemory = new Post * [totalmemory];
        for (int i = 0; i < totalmemory; i++)
        {
            sharedmemory[i] = memory[i];
        }
        totalsharedmemories = totalmemory;
    }

    void PrintTimeLine(int systemDay, int systemMonth, int systemYear)
    {
        cout << "\nWe hope you enjoy looking back and sharing your memories on Facebook,";
        cout << " from the most recent to those long ago.\n\n\n" << endl;
        for (int i = 0; i < totalsharedmemories; i++)
        {
            sharedmemory[i]->MemoriesTimePrinter(systemDay, systemMonth, systemYear);
            sharedmemory[i]->PrintTimeLine(systemDay, systemMonth, systemYear);
        }
    }


    //              Destructor Called
    ~SharedMemory()
    {
        if (sharedmemory != 0)
        {
            delete[] sharedmemory;
        }
    }
};

//-----------------------------Page-------------------------------------------------------------------------------------------
class Page : public Base
{
private:
    char* Title;
    int TotalTimeline;
    Post** Timeline;
    SharedMemory* memories;

public:
    Page()
    {
        Title = nullptr;
        TotalTimeline = 0;
        memories = nullptr;
        Timeline = new Post * [10];
    }

    void AddTimeLine(Post* obj)
    {
        if (TotalTimeline < 10)
        {
            Timeline[TotalTimeline] = obj;
            TotalTimeline++;
        }
    }
    void ReadDataFromFile(istream& fin)
    {
        //               Initializing ID
        char Buffer[100];
        fin >> Buffer;
        SetID(Buffer);

        //               Initializing Page Name
        int position = fin.tellg();
        fin.seekg(position + 1);
        fin.getline(Buffer, 99);
        Title = new char[strlen(Buffer) + 1];
        strcpy_s(Title, strlen(Buffer) + 1, Buffer);
    }
    void PrintName()
    {
        cout << Title;
    }
    void PrintTimeLine(int systemDay, int systemMonth, int systemYear)
    {
        for (int i = 0; i < TotalTimeline; i++)
        {
            Timeline[i]->PrintTimeLine(systemDay, systemMonth, systemYear);
        }
    }
    void SharedMemories(const char* POSTID, const char* DESCRIPTION)
    {
        if (memories != 0)
        {
            delete memories;
        }
        SeeMemories();
        AddTimeLine(memories);
        memories->AddNewPostData(POSTID, DESCRIPTION);
        memories->AddSharedBy(this);
        memories = 0;
    }

    SharedMemory* SeeMemories()
    {
        memories = new SharedMemory;
        memories->CombineMemories(Timeline, TotalTimeline);

        return memories;
    }

    //              Destructor Called
    ~Page()
    {
        if (Title != 0)
        {
            delete[] Title;
        }
        if (Timeline != 0)
        {
            for (int i = 0; i < TotalTimeline; i++)
            {
                delete Timeline[i];
            }
            delete[] Timeline;
        }
    }
};

//-----------------------------User--------------------------------------------------------------------------------------------
class User : public Base
{
private:
    char* Fname;
    char* Lname;
    int TotalFriend;
    int TotalLikedPages;
    int numberOfFriends;
    int numberOfPages;
    int TotalTimeline;
    User** FriendList; // null or 10 pointers max
    Page** LikedPages; // null or 10 pointers max
    Post** Timeline;
    SharedMemory* memories;

public:

    User()
    {
        Fname = nullptr;
        Lname = NULL;
        TotalFriend = 0;
        TotalLikedPages = 0;
        numberOfFriends = 0;
        numberOfPages = 0;
        TotalTimeline = 0;
        memories = nullptr;
        LikedPages = nullptr;
        FriendList = nullptr;
        Timeline = new Post * [10];

    }
    //                          Getters
    char* GetFname() {
        return Fname;
    }
    char* GetLname() {
        return Lname;
    }
    int GetTotalFriend() const override
    {
        return TotalFriend;
    }
    User** GetFriendList() const override
    {
        return FriendList;
    }


    void ReadDataFromFile(ifstream& fin)
    {
        //                  Initializing ID
        char Buffer[100];
        fin >> Buffer;
        SetID(Buffer);

        //                  Initializing First name
        fin >> Buffer;
        Fname = new char[strlen(Buffer) + 1];
        strcpy_s(Fname, strlen(Buffer) + 1, Buffer);

        //                  Initializing Last Name
        fin >> Buffer;
        Lname = new char[strlen(Buffer) + 1];
        strcpy_s(Lname, strlen(Buffer) + 1, Buffer);
    }

    //              Setting things 
    void SetFriendList(int num)
    {
        TotalFriend = num;
        FriendList = new User * [num];
    }
    void AddFriend(User* Array)
    {
        if (numberOfFriends < TotalFriend)
        {
            FriendList[numberOfFriends] = Array;
            numberOfFriends++;
        }
    }
    void SetLikedPages(int num)
    {
        TotalLikedPages = num;
        LikedPages = new Page * [num];
    }
    void AddLikedPages(Page* array)
    {
        if (numberOfPages < TotalLikedPages)
        {
            LikedPages[numberOfPages] = array;
            numberOfPages++;
        }
    }
    void AddTimeLine(Post* obj)
    {
        if (TotalTimeline < 10)
        {
            Timeline[TotalTimeline] = obj;
            TotalTimeline++;
        }
    }

    //              Printing Functions
    void PrintName()
    {
        cout << Fname << " " << Lname;
    }
    void PrintLikedPages()
    {
        for (int i = 0; i < TotalLikedPages; i++)
        {
            LikedPages[i]->PrintID();
            cout << " - ";
            LikedPages[i]->PrintName();
            cout << endl;
        }
    }
    void PrintFriendList()
    {
        for (int i = 0; i < TotalFriend; i++)
        {
            FriendList[i]->PrintID();
            cout << " -  ";
            FriendList[i]->PrintName();
            cout << endl;
        }
    }
    void PrintTimeLine(int systemDay, int systemMonth, int systemYear)
    {
        for (int i = 0; i < TotalTimeline; i++)
        {
            Timeline[i]->PrintTimeLine(systemDay, systemMonth, systemYear);
        }
    }

    SharedMemory* SeeMemories()
    {
        memories = new SharedMemory;
        memories->CombineMemories(Timeline, TotalTimeline);
        return memories;
    }
    void SharedMemories(const char* POSTID, const char* DESCRIPTION)
    {
        if (memories != 0)
        {
            delete memories;
        }
        SeeMemories();
        AddTimeLine(memories);
        memories->AddNewPostData(POSTID, DESCRIPTION);
        memories->AddSharedBy(this);
        memories = 0;
    }



    //          Destructor Called
    ~User()
    {
        if (Fname != 0)
        {
            delete[] Fname;
        }

        if (Lname != 0)
        {
            delete[] Lname;
        }

        if (FriendList != 0)
        {
            delete[] FriendList;
        }

        if (LikedPages != 0)
        {
            delete[] LikedPages;
        }

        if (Timeline != 0)
        {
            for (int i = 0; i < TotalTimeline; i++)
            {
                delete Timeline[i];
            }
            delete[] Timeline;
        }

    }
};
//-----------------------------Comment-----------------------------------------------------------------------------------------
class Comment
{
    char* description;
    Base* commentby;
public:
    //Getters
    char* GetDescription() {
        return description;
    }
    Base* GetCommentedBy() {
        return commentby;
    }

    void Readfromfile(ifstream& fin)
    {
        char Buffer[100];
        fin.getline(Buffer, 99);
        description = new char[strlen(Buffer) + 1];
        strcpy_s(description, strlen(Buffer) + 1, Buffer);
    }

    void addcommentby(Base* ptr)
    {
        commentby = ptr;
    }

    void AddComment(const char* arr) {
        char b[80];
        description = new char[strlen(arr) + 1];
        strcpy_s(description, strlen(arr) + 1, arr);
    }

    void READFROMFILE(ifstream& fin)
    {
        char buffer[80];
        //              To find Position os Pointer in file 
        int position = fin.tellg();
        fin.seekg(position + 1);
        fin.getline(buffer, 99);
        description = new char[strlen(buffer) + 1];
        strcpy_s(description, strlen(buffer) + 1, buffer);
    }
    void print() {
        cout << "\t\t";
        commentby->PrintName();
        cout << ": ";
        cout << description << endl;
    }

    //          Destructor Called
    ~Comment()
    {
        if (description != 0)
        {
            delete[] description;
        }
    }
};
//-----------------------------Helper------------------------------------------------------------------------------------------
class Helper
{
public:
    static char* Concatenate(char* arrayy, const char* Expression)
    {
        int s1 = strlen(arrayy);
        int s2 = strlen(Expression);

        char* concatenatedString = new char[s1 + s2 + 1];
        concatenatedString[s1 + s2] = '\0';

        int j = 0;
        for (int i = 0; concatenatedString[i] != '\0'; i++)
        {
            if (i < s2)
            {
                concatenatedString[i] = Expression[i];
            }
            else
            {
                concatenatedString[i] = arrayy[j];
                j++;
            }
        }

        if (arrayy != 0)
        {
            delete[] arrayy;
        }
        return concatenatedString;
    }
};

//----------------------------Activities--------------------------------------------------------------------------------------
class Activity
{
    int expression;
    char* Array;

public:

    void readfromfile(ifstream& fin)
    {
        char buffer[80];
        fin >> expression;

        fin.getline(buffer, 99);
        Array = new char[strlen(buffer) + 1];
        strcpy_s(Array, strlen(buffer) + 1, buffer);

        if (expression == 1)
        {
            Array = Helper::Concatenate(Array, " is Feeling");
        }
        else if (expression == 2)
        {
            Array = Helper::Concatenate(Array, " is Thinking about");
        }
        else if (expression == 3)
        {
            Array = Helper::Concatenate(Array, " is Making");
        }
        else
        {
            Array = Helper::Concatenate(Array, " is Celebrating");
        }
    }
    void print()
    {
        cout << Array;
    }

    //          Destructor Called
    ~Activity()
    {
        if (Array != 0)
        {
            delete[] Array;
        }
    }
};

//-----------------------------Controller------------------------------------------------------------------------------------
class Controller :public User
{
    static int totalUser;
    static int totalPage;
    static int totalPost;
    int day;
    int month;
    int year;
    int totalcomments;
    int totalactivities;
    Base* currentUser;
    User** AllUsers;
    Page** AllPages;
    Post** AllPost;

public:

    //                          Functions Use in Constructor

    //          Searching Functions
    User* SearchUserByID(const char* ID)
    {
        for (int i = 0; i < totalUser; i++)
        {
            if (AllUsers[i]->compareId(ID))
            {
                return AllUsers[i];
            }
        }
        return nullptr;
    }
    Page* SearchPageByID(const char* ID)
    {
        for (int i = 0; i < totalPage; i++)
        {
            if (AllPages[i]->compareId(ID))
            {
                return AllPages[i];
            }
        }
        return nullptr;
    }
    Post* SearchPostByID(const char* Array)
    {
        for (int i = 0; i < totalPost; i++)
        {
            if (AllPost[i]->compareId(Array))
            {
                return AllPost[i];
            }
        }
        return nullptr;
    }

    //             Function to show the added Comment
    void DisplayCommentsOnPost(const char* postID) {
        Post* post = SearchPostByID(postID);

        if (post) {
            cout << "Comments on Post " << postID << ":" << endl;
            Comment** comments = post->GetComments();
            int totalComments = post->GetTotalComments();

            for (int i = 0; i < totalComments; ++i) {
                cout << "Comment " << (i + 1) << ": " << comments[i]->GetDescription() << endl;
                cout << "By: ";
                comments[i]->GetCommentedBy()->PrintName();
                cout << endl;
            }
        }
        else {
            cout << "Post not found." << endl;
        }
    }

    //          Loading Functions 
    void LoadAllUser()
    {
        ifstream fin("User.txt");
        fin >> totalUser;
        AllUsers = new User * [totalUser + 1];
        for (int i = 0; i < totalUser; i++)
        {
            AllUsers[i] = new User();
            AllUsers[i]->ReadDataFromFile(fin);
        }

    }
    void LoadAllPage()
    {
        ifstream fin("Pages.txt");
        fin >> totalPage;
        AllPages = new Page * [totalPage];
        for (int i = 0; i < totalPage; i++)
        {
            AllPages[i] = new Page;
            AllPages[i]->ReadDataFromFile(fin);
        }

    }
    void LinkUsersAndPages()
    {
        ifstream fin("Like.txt");

        char Buffer[10];

        int count = 0;
        int countForFriend = 0;
        int countForPage = 0;
        while (!fin.eof())
        {
            fin >> Buffer;
            currentUser = SearchUserByID(Buffer);
            count = 0;
            countForFriend = 0;
            countForPage = 0;
            for (int i = 0; count != 2; i++)
            {
                if (count == 0)
                {
                    fin >> Buffer;
                    if (Buffer[0] == 'u')
                    {
                        countForFriend++;
                    }
                    else if (Buffer[0] == '-')
                    {

                        count++;
                    }
                }
                else if (count == 1)
                {
                    fin >> Buffer;
                    if (Buffer[0] == 'p')
                    {
                        countForPage++;
                    }
                    else if (Buffer[0] == '-')
                    {
                        count++;
                    }
                }
            }
            currentUser->SetFriendList(countForFriend);
            currentUser->SetLikedPages(countForPage);
        }
        fin.close();

        ifstream in("Like.txt");
        count = 0;
        countForFriend = 0;
        countForPage = 0;
        while (!in.eof())
        {
            in >> Buffer;
            currentUser = SearchUserByID(Buffer);
            count = 0;
            countForFriend = 0;
            countForPage = 0;
            for (int i = 0; count != 2; i++)
            {
                if (count == 0)
                {
                    in >> Buffer;
                    if (Buffer[0] == 'u')
                    {
                        currentUser->AddFriend(SearchUserByID(Buffer));
                    }
                    else if (Buffer[0] == '-')
                    {

                        count++;
                    }
                }
                else if (count == 1)
                {
                    in >> Buffer;
                    if (Buffer[0] == 'p')
                    {
                        currentUser->AddLikedPages(SearchPageByID(Buffer));
                    }
                    else if (Buffer[0] == '-')
                    {
                        count++;
                    }
                }
            }
        }
    }
    void LoadAllPost()
    {
        char Buffer[100];
        ifstream fin("Post.txt");
        fin >> totalPost;
        AllPost = new Post * [totalPost];
        for (int i = 0; i < totalPost; i++)
        {
            AllPost[i] = new Post;
            AllPost[i]->ReadDataFromFile(fin);
            fin >> Buffer;
            if (Buffer[0] == 'u')
            {
                AllPost[i]->AddSharedBy(SearchUserByID(Buffer));
                SearchUserByID(Buffer)->AddTimeLine(AllPost[i]);
            }
            else if (Buffer[0] == 'p')
            {
                AllPost[i]->AddSharedBy(SearchPageByID(Buffer));
                SearchPageByID(Buffer)->AddTimeLine(AllPost[i]);
            }
            while (Buffer[0] != '-')
            {
                fin >> Buffer;
                if (Buffer[0] == 'u')
                {
                    AllPost[i]->AddLikedBy(SearchUserByID(Buffer));

                }
                else if (Buffer[0] == 'p')
                {
                    AllPost[i]->AddLikedBy(SearchPageByID(Buffer));

                }
            }
        }

    }
    void LoadAllcommets()
    {
        char buffer[100];
        ifstream fin("Comments.txt");

        Comment* temp = 0;

        fin >> totalcomments;
        for (int i = 0; i < totalcomments; i++)
        {
            temp = new Comment;
            fin >> buffer;

            SearchPostByID(buffer)->AddComments(temp);

            fin >> buffer;
            if (buffer[0] == 'u')
            {
                temp->addcommentby(SearchUserByID(buffer));
            }
            else if (buffer[0] == 'p')
            {
                temp->addcommentby(SearchPageByID(buffer));
            }
            temp->READFROMFILE(fin);
            temp = 0;
        }

        fin.close();
    }
    void LoadALLActivities()
    {
        char buffer[100];
        ifstream fin("Activities.txt");

        Activity* temp = 0;

        fin >> totalactivities;
        for (int i = 0; i < totalactivities; i++)
        {
            temp = new Activity;
            fin >> buffer;
            SearchPostByID(buffer)->AddActivities(temp);

            temp->readfromfile(fin);

            temp = 0;
        }

        fin.close();
    }

    Controller()
    {
        LoadAllUser(); //Keep it easily configurable
        LoadAllPage(); //Keep it easily configurable
        LinkUsersAndPages();
        LoadAllPost();
        LoadAllcommets();
        LoadALLActivities();
    }
    //          Printing 
    void SetCommandUser()
    {

        //           Login Page
        string name, option, password, p, name1, password1;
        char* user = new char[100];
        cout << "-----------------------------------------------------------------------------------------\n";
        cout << "www.Facebook.com" << endl;
        cout << "-----------------------------------------------------------------------------------------\n\n\n\n";
        cout << "\n\t\t\t\t\t\tFacebook\t\t\t\t\t\n\n\n";
    here:
        cout << "\nDo you want to sign up(yes/no)?\n";
        cin >> option;
        if (option == "yes") {
            cout << "\n Enter user id(like u1,u2,u3 etc): ";
            cin >> user;
        again:
            cout << "\n Enter password: ";
            cin >> password;
            cout << "\nConfirm password: ";
            cin >> p;
            if (password == p) {
                cout << "\nLoading............Please have some patience\n";
                for (int i = 0, count = 0; i < 10000000000000000000; i++) {
                    if (count == 1000000000) {
                        cout << "Wait a little longer while we gather all your junk.";
                    }
                    count++;
                }
                currentUser = SearchUserByID(user);
                cout << "\n\nCongratulations! Account successfully created\n";
                cout << "\n\n\nWelcome to Facebook ";  currentUser->PrintName(); cout << "\n\n\n";

            }
            else {
                cout << "\nPassword did not match. Please enter password again.\n";
                goto again;
            }
        }
        else {
            cout << "\nYou are supposed to write yes";
            goto here;
        }
        //                      Menu
        int choice = 0;
        while (choice != 11) {
            cout << "\nEnter the number of the task you wish to perform:\n";
            cout << "\n\t\t\t----------------Menu--------------------";
            cout << "\n\t\t\t|      1. Set Current Date              |";
            cout << "\n\t\t\t|      2. Set Current User              |";
            cout << "\n\t\t\t|      3. View Friend List              |";
            cout << "\n\t\t\t|      4. View Homepage                 |";
            cout << "\n\t\t\t|      5. View Liked Pages              |";
            cout << "\n\t\t\t|      6. Like a Post                   |";
            cout << "\n\t\t\t|      7. Add a Comment                 |";
            cout << "\n\t\t\t|      8. View Timeline                 |";
            cout << "\n\t\t\t|      9. Share a Memory                |";
            cout << "\n\t\t\t|     10. View a Page                   |";
            cout << "\n\t\t\t|     11. View Profile                  |";
            cout << "\n\t\t\t|     12. Exit                          |";
            cout << "\n\t\t\t----------------------------------------";
            cout << endl;
            cin >> choice;


            //                      Current Date
            if (choice == 1) {
                cout << "\n\n";
                cout << "\t\tCommand: Set system current Date \n\n";
                cout << "\nEnter Date: ";
                cin >> day;
                cout << "\nEnter Month: ";
                cin >> month;
                cout << "\nEnter Year: ";
                cin >> year;
                cout << "\nSystem Date: " << day << "/" << month << "/" << year << "\n\n";
            }

            //                      Current User
            if (choice == 2) {
                const char* id = user;
                cout << "\n\t\tCommand:Set current user \n\n";
                currentUser = SearchUserByID(id);
                currentUser->PrintName();
                cout << " Successfully set as Current user\n";
            }

            //                      View Friend List
            if (choice == 3) {
                cout << "\n\n\t\tCommand:\t\t- View Friend List\n";
                cout << "-----------------------------------------------------------------------------------------------------------\n";
                currentUser->PrintName();
                cout << " - Friend List\n";
                currentUser->PrintFriendList();
            }

            //                      View Homepage
            if (choice == 4) {
                cout << "\n\n\t\tCommand:\t- View Home Page\n";
                cout << "---------------------------------------------------\n";
                cout << "Home Page of ";
                currentUser->PrintName();
                cout << endl;
                cout << "---------------------------------------------------\n";
                int totalFriend = currentUser->GetTotalFriend();
                User** friendList = currentUser->GetFriendList();
                for (int i = 0; i < totalFriend; i++) {
                    cout << "---------------------------------------------------\n";
                    friendList[i]->PrintTimeLine(day, month, year);
                    cout << "---------------------------------------------------\n";
                }
            }


            //                      View Profile
            if (choice == 11) {
                cout << "\n\n\t\tCommand:\t- View Profile\n";
                cout << "User Name: \n";
                const char* id = user;
                currentUser = SearchUserByID(id);
                currentUser->PrintName();
                cout << endl << endl << endl;
                User u1;
                currentUser->PrintTimeLine(day, month, year);
            }

            //                          Add Comment 
            if (choice == 7) {
                char* arr = new char[100];
                Post p1;
                Comment* temp = new Comment;
                char* id = new char[100];
                cout << "Enter id of post you wish to add comment on: (like post1, post2 etc)\n";
                cin >> id;
                cout << "Write your comment on the " << id << " and hit enter to add the comment: \n";
                cin >> arr;
                User* User = SearchUserByID(user);
                Post* post = SearchPostByID(id);

                if (user && post) {
                    Comment* newComment = new Comment;
                    newComment->AddComment(arr);
                    newComment->addcommentby(User);
                    post->AddComments(newComment);
                    cout << "Comment added successfully." << endl;
                    DisplayCommentsOnPost(id);
                }
                else {
                    cout << "User or Post not found." << endl;
                }

            }


            //                      View Like Pages
            if (choice == 5) {
                cout << "\n\n\t\tCommand:\t- View Liked Pages\n";
                cout << "------------------------------------------------------------------------------------------------------------\n";
                currentUser->PrintName();
                cout << " - Liked Pages\n";
                currentUser->PrintLikedPages();
            }

            //                      View TimeLine
            if (choice == 8) {
                cout << "\n\n\t\tCommand:\t- View Time Line:\n";
                cout << "---------------------------------------------------\n";
                currentUser->PrintName();
                cout << " - TimeLine\n\n\n";
                currentUser->PrintTimeLine(day, month, year);
            }

            //                      View Liked List
            if (choice == 6) {
                char* po = new char[100];
                cout << "\n\n\t\tCommand:\t- View Liked List:\n";
                cout << "---------------------------------------------------\n";
                cout << "\nWhich post do you want to like \n";
                cin >> po;
                const char* arr = po;
                cout << arr << " - TimeLine\n\n\n";
                SearchPostByID(arr)->PrintLikedBy();


                //                      View Liked Post
                cout << "\n\n\t\tCommand:\t LikedPost\n";
                cout << "\nDo you want to like post (yes/no)?\n";
                cin >> option;
                if (option == "yes")
                    SearchPostByID(arr)->AddLikedBy(currentUser);
                SearchPostByID(arr)->PrintLikedBy();
            }

            //                      View Page 
            if (choice == 10) {
                cout << "\n\n\t\tCommand:\t- View Page:\n";
                cout << "---------------------------------------------------\n";
                cout << "\nEnter id of page you wish to view (like p1,p2,p3 etc): ";
                cin >> user;
                const char* ID = user;
                SearchPageByID(ID)->PrintTimeLine(day, month, year);
                cout << "-------------------------------------------------------------------------------------------------------------" << endl;
            }

            //                      View Shared Memory
            if (choice == 9) {
                cout << "Command:\tShareMemory(post10,  Never thought I will be specialist in this field  )\n\n\n" << endl;
                currentUser->SharedMemories("post10", "Never thought I will be specialist in this field ");

                //                      View TimeLine
                cout << "Command:\tView TimeLine" << endl;
                currentUser->PrintName();
                cout << " - Time Line\n\n\n" << endl;
                currentUser->PrintTimeLine(day, month, year);
                cout << "-------------------------------------------------------------------------------------------------------------" << endl;
            }

        }
        cout << "\n\n\nHave a good day !\n";
        cout << "Signing you out\n";
    }
    //               Destructor Called
    ~Controller()
    {
        for (int i = 0; i < totalUser; i++)
        {
            delete AllUsers[i];
        }
        delete[] AllUsers;

        delete[] AllPost;

        for (int i = 0; i < totalPage; i++)
        {
            delete AllPages[i];
        }
        delete[] AllPages;
    }
};

//-----------------------------Static Allocation------------------------------------------------------------------------------
int Controller::totalUser = 0;
int Controller::totalPage = 0;
int Controller::totalPost = 0;

//------------------------------Main---------------------------------------------------------------------------------------
int main()
{
    system("color 17");
    Controller mainApp;
    mainApp.SetCommandUser();
    return 0;
}
void Post::PrintTimeLine(int day, int month, int year)
{
    sharedBy->PrintName();

    if (active != 0)
    {
        active->print();
    }
    TimePrinter(day, month, year);
    cout << Discription << "\n\n";
    if (commentBy != 0)
    {
        for (int i = 0; i < totalcomment; i++)
        {
            commentBy[i]->print();
        }
    }
}