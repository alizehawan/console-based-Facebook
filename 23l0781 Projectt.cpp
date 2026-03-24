#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;


template<typename T>
void Destructor(T**& array, int length)
{
	if (array) {
		for (int i = 0; i < length; i++)
		{
			if (array[i])
				delete[] array[i];
		}
		delete[] array;
	}
}

class Date;
class Helper;
class object;
class Post;
class User;
class Page;
class Facebook;
class Memory;
class Activity;
class Comments;

class Date {
	int day;
	int Month;
	int Year;

public:
	static Date currentDate;

	Date(int _Day = 0, int _Month = 0, int _Year = 0) {
		day = _Day;
		Month = _Month;
		Year = _Year;
	}

	static void SetCurrentDate(int d, int m, int y) {
		currentDate.day = d;
		currentDate.Month = m;
		currentDate.Year = y;
	}

	void ReadDate(ifstream& input) {
		input >> day >> Month >> Year;
	}

	int getMonth() const {
		return Month;
	}

	void PrintCurrentDate() {
		cout << currentDate.day << "/" << currentDate.Month << "/" << currentDate.Year;
	}

	void PrintUserDate() {
		cout << "...(" << day << "/" << Month << "/ " << Year << ")" << endl;
	}

	bool CheckTime() {
		if ((currentDate.day == day || currentDate.day - 1 == day) && currentDate.Month == Month && currentDate.Year == Year)
			return true;
		else
			return false;
	}

	bool IsOneDayBeforeCurrentDate() {
		Date oneDayBeforeCurrentDate = currentDate;
		if (oneDayBeforeCurrentDate.day == 1) {
			if (oneDayBeforeCurrentDate.Month == 1) {
				oneDayBeforeCurrentDate.day = 31;
				oneDayBeforeCurrentDate.Month = 12;
				oneDayBeforeCurrentDate.Year--;
			}
			else {
				oneDayBeforeCurrentDate.day = 31; // Assuming all months have 31 days for simplicity
				oneDayBeforeCurrentDate.Month--;
			}
		}
		else {
			oneDayBeforeCurrentDate.day--;
		}
		return (day == oneDayBeforeCurrentDate.day && Month == oneDayBeforeCurrentDate.Month && Year == oneDayBeforeCurrentDate.Year);
	}

	int getYear() const {
		return Year;
	}
	int getDay() const {
		return day;
	}

	int getDate() const {
		return day;
	}
	static Date getcurrentdate() {
		return currentDate;
	}
};

Date Date::currentDate;

class Helper   //to avoid shallow copy of character arrays
{
public:

	static int StringLenght(char* string) //Used to find the string length 
	{
		int stringLen = 0;
		for (char* temp = string; *temp != '\0'; temp++)
			stringLen++;
		return stringLen;
	}

	static char* GetStringFromBuffer(char* str) //Takes input of the string without taking extra space
	{
		int strLen = StringLenght(str);
		char* GetString = 0;

		if (strLen > 0)
		{
			GetString = new char[strLen + 1];
			int i = 0;
			for (; str[i] != '\0'; i++)
				GetString[i] = str[i];

			GetString[i] = '\0';
		}
		return GetString;
	}

	static bool CompareStrings(char* a)
	{
		if (StringLenght(a) == 2)
		{
			if (a[0] == '-' && a[1] == '1')
				return true;
			else
				return false;
		}
		else
			return false;
	}

	static bool CompareStrings(char* a, char* b)
	{
		int count = 0;
		if (StringLenght(a) != StringLenght(b))
			return false;
		else
		{
			for (int i = 0; i < StringLenght(a); i++)
			{
				if (a[i] == b[i]) count++;
			}
			if (count == StringLenght(a))
				return true;
			else
				return false;
		}
	}

	static char* Concatenate(char* str1, char* str2)
	{
		int len1 = StringLenght(str1);
		int len2 = StringLenght(str2);
		int len3 = len1 + len2;
		char* string3 = new char[len3 + 1];
		int index3 = 0;

		for (int i = 0; i < len1; i++, index3++)
			string3[index3] = str1[i];

		string3[index3] = ' ';
		index3++;

		for (int i = 0; i < len2; i++, index3++)
			string3[index3] = str2[i];

		string3[index3] = '\0';
		string3 = GetStringFromBuffer(string3);

		return string3;
		delete[] string3;
		string3 = 0;
	}


};

//base class
class object
{
	char* ID;

public:

	virtual void PrintName()
	{

	}

	virtual void SetTimeline(Post*& temp)
	{

	}

	virtual char* GetID()
	{
		return ID;
	}

	virtual void ViewPageForPost()
	{

	}

	virtual void PrintNameAndID()
	{

	}

};


class Comments
{
	object* Author;
	char* Text;
	char* ID;
	static int TotalComments;

public:
	Comments()
	{
		Author = 0;
		ID = 0;
		Text = 0;
		TotalComments++;
	}

	Comments(char* _ID, char* _Text)
	{
		ID = Helper::GetStringFromBuffer(_ID);
		Text = Helper::GetStringFromBuffer(_Text);
	}

	~Comments()
	{

		if (Text)
		{
			delete[] Text;
			Text = 0;
		}

		if (ID)
		{
			delete[] ID;

		}

	}

	void SetCommentInfo(char*& a, object*& b, char*& c)
	{
		ID = Helper::GetStringFromBuffer(a);
		Author = b;
		Text = Helper::GetStringFromBuffer(c);
	}

	void PrintText()
	{
		cout << " wrote '" << Text << "'" << endl;
	}

	void PrintAuthor()
	{
		Author->PrintName();
	}

	void Print()
	{
		Author->PrintName();
		cout << " wrote: ";
		cout << "'" << Text << "' " << endl;
	}

	void SetNewComment(object* author, char*& temptext, char*& tempIDofComment)
	{
		Author = author;
		Author->PrintName();
		Text = Helper::GetStringFromBuffer(temptext);
		ID = Helper::GetStringFromBuffer(tempIDofComment);
	}
};

int Comments::TotalComments = 0;

class Post  //parent class of memory
{
	object** LikedBy; // Array of pointers to objects representing users who liked the post
	Comments** Allcomments;
	char* ID;
	Comments* comments = new Comments[10];        //aggregation
	//Date postdate;
	object* sharedby;  //aggregation
	int activity;
	Activity* Activityy;
	char* PostIDForComment;
	int noc = 0;
	int TotalComments;
	int TotalLikes;
	//object* sharedby;
		//Date getdate();


protected:
	Date PostedOn;
	object* Author; //association
	Date postdate;
	int pt;
	char* Text;
	char* ID_ofPost;

public:

	Post()
	{
		PostedOn = 0;
		ID = 0;
		Text = 0;
		ID_ofPost = 0;
		PostIDForComment = 0;
		Allcomments = 0;
		TotalComments = 0;
		TotalLikes = 0;
		Author = 0;
		LikedBy = 0;
		activity = 0;

	}

	virtual ~Post()
	{

		if (Allcomments)
		{
			for (int i = 0; i < TotalComments; i++)
			{
				delete Allcomments[i];
			}
			delete[] Allcomments;
		}

		if (ID)
		{
			delete[] ID;
			ID = 0;
		}

		if (Text)
		{
			delete[] Text;
			Text = 0;
		}

		if (LikedBy)
		{
			delete[] LikedBy;
		}
	}

	char* GetText()
	{
		return Text;
	}

	Date getdate() const {
		return postdate;
	}
	virtual void PrintSearchResults()
	{

		cout << ID_ofPost << "-";
		PrintName();
		cout << " shared ";
		cout << "'" << Text << "'" << endl;
	}
	void printcomments()
	{
		if (comments != nullptr)
			for (int i = 0; i < noc; i++)
				comments[i].Print();
	}
	virtual void viewpost() {
		if (pt == 2) {
			// Handle Activity post separately
			cout << "Activity post: ";
			// Print details of the activity post
			cout << Text << "    ";
			postdate.PrintCurrentDate();
			cout << endl;
		}
		else {
			// Handle regular post
			cout << "Regular post: ";
			// Print details of the regular post
			cout << Text << "    ";
			postdate.PrintCurrentDate();
			cout << endl;
		}
		// Print comments for all types of posts
		this->printcomments();
	}

	void print()
	{
		cout << ID << " " << Text << endl;
	}

	void ViewPageForPost()
	{
		PrintName();
		cout << Text;
		PrintAllComments();
	}
	object* getsharedby()
	{
		if (this != nullptr)
			return sharedby;
	}

	void InitializingLikedBy()
	{
		LikedBy = new object * [10];

		for (int i = 0; i < 10; i++)
		{
			LikedBy[i] = new object;
			LikedBy[i] = 0;
		}
	}

	void AddLikedBy(object* obj)
	{
		SetLikes(obj);
	}

	void PrintLikes()
	{
		cout << endl << "Post Liked By:" << endl;
		for (int i = 0; i < TotalLikes; i++)
		{
			LikedBy[i]->PrintNameAndID();
		}
		cout << endl;
	}

	void PrintAllComments()
	{
		for (int i = 0; i < TotalComments; i++)
		{
			Allcomments[i]->Print();
		}
	}

	virtual void PrintLatestFreindsPosts()
	{
		if (PostedOn.CheckTime() || PostedOn.IsOneDayBeforeCurrentDate())
		{
			PrintName();
			cout << " shared ";
			cout << "'" << Text << "'" << endl;;
			PrintAllComments();
			cout << endl;
		}
	}

	virtual void PrintLatestPagesPost()
	{
		if (PostedOn.CheckTime())
		{
			PrintName();
			cout << " shared ";
			cout << "'" << Text << "'" << endl;;
			PrintAllComments();
			cout << endl;
		}
	}

	virtual void PrintInfo()
	{
		PrintName();
		cout << " shared ";
		cout << "'" << Text << "'";
		PostedOn.PrintUserDate();
		PrintAllComments();
		cout << endl;
	}

	void SetLikes(object*& temp)
	{
		if (!TotalLikes)
			LikedBy = new object * [10];
		LikedBy[TotalLikes] = temp;
		TotalLikes++;
	}

	object* SetAuthor(object*& obj)
	{
		Author = obj;
		return Author;
	}

	virtual void Print()
	{
		cout << "'" << Text << "'" << endl;
	}

	void ReadID(ifstream& input)
	{
		int NoOfLikes = 0;
		char* Buffer = new char[80];
		input >> Buffer;
		ID = Helper::GetStringFromBuffer(Buffer);
	}

	void InitializingComments()
	{
		Allcomments = new Comments * [10];
		for (int i = 0; i < 10; i++)
		{
			Allcomments[i] = 0;
		}
	}

	void SaveComment(Comments*& temp)
	{
		if (!TotalComments)
			Allcomments = new Comments * [10];
		Allcomments[TotalComments] = temp;
		TotalComments++;
	}

	char* GetID()
	{
		return ID;
	}

	char* GetID_ofPost()
	{
		return ID_ofPost;
	}

	virtual void PrintName()
	{
		Author->PrintName();
		char* temp = Author->GetID();
	}

	virtual void LoadFromFile(ifstream& input)
	{
		char* tempBuffer = new char[80];
		int tempDay, tempMonth, tempYear;

		input >> tempBuffer;
		ID_ofPost = Helper::GetStringFromBuffer(tempBuffer);
		PostedOn.ReadDate(input);
		input.ignore();
		input.getline(tempBuffer, 80);
		Text = Helper::GetStringFromBuffer(tempBuffer);
	}
};

//Inheritance
class Page :public object
{
private:
	char* ID;
	char* Title;
	Post** Timeline;  //Aggregation 
	int totalPosts;

public:

	Page() :object()
	{
		ID = 0;
		Title = 0;
		totalPosts = 0;
		Timeline = 0;
	}

	~Page()
	{
		if (Timeline)
			Destructor(Timeline, totalPosts);
		if (Title)
			delete[] Title;
		if (ID)
			delete[] ID;
	}

	void PrintNameAndID()
	{
		cout << ID << "-" << Title << endl;;
	}

	void InitializingTimeLine()
	{
		Timeline = new Post * [10];

		for (int i = 0; i < 10; i++)
		{
			Timeline[i] = new Post;
			Timeline[i] = 0;
		}
	}

	void PrintSearchResults()
	{
		cout << ID << "-" << Title << endl;
	}

	char* GetID()
	{
		return ID;
	}

	char* Get_Title()
	{
		return Title;
	}

	void ViewPageForPost()
	{
		for (int i = 0; i < totalPosts; i++)
		{
			Timeline[i]->PrintInfo();
		}
	}

	void PrintLatestPagesPost()
	{
		for (int i = 0; i < totalPosts; i++)
		{
			Timeline[i]->PrintLatestPagesPost();
		}
	}

	void LoadDataFromPages(ifstream& IN)
	{
		char* buffer = new char[80];

		IN >> buffer;
		ID = Helper::GetStringFromBuffer(buffer);
		IN.ignore();
		IN.getline(buffer, 80);
		Title = Helper::GetStringFromBuffer(buffer);
		delete[] buffer;
	}

	int GetTotalPosts()
	{
		return totalPosts;
	}

	void PrintName()
	{
		cout << Title;
	}


	void SetTimeline(Post*& Add)
	{
		if (!totalPosts)
			Timeline = new Post * [10];

		Timeline[totalPosts] = Add;
		totalPosts++;
	}
};


class User :public object  //inheritance  User inherits from object
{

private:
	char* ID;
	char* FirstName;
	char* LastName;
	User** FriendList;	//Aggregation as User aggregates multiple User objects as friends
	Page** LikedPages; //Aggregation as User aggregates multiple Page objects as liked pages
	int noOfFriends;
	int noOfPages;
	Post** Timeline; //Aggregation as User aggregates multiple Post objects in their timeline
	int totalPosts;

public:

	User() :object()
	{
		ID = NULL;
		FirstName = LastName = NULL;
		FriendList = NULL;
		LikedPages = NULL;
		noOfFriends = NULL;
		noOfPages = NULL;
		Timeline = NULL;
		totalPosts = NULL;
	}

	~User()
	{

		if (FirstName)
			delete[] FirstName;
		if (LastName)
			delete[] LastName;
		if (FriendList)
			delete[] FriendList;
		if (LikedPages)
			delete[] LikedPages;
		if (Timeline)
		{
			Destructor(Timeline, totalPosts);
		}

		if (ID)
			delete[] ID;
	}

	void PrintNameAndID()
	{
		cout << ID << "-" << FirstName << " " << LastName << endl;;
	}

	User(const User& rhs)
	{
		ID = rhs.ID;
		FirstName = Helper::GetStringFromBuffer(rhs.FirstName);
		LastName = Helper::GetStringFromBuffer(rhs.LastName);

		for (int i = 0; i < totalPosts; i++)
			Timeline[i] = rhs.Timeline[i];

		for (int i = 0; i < noOfFriends; i++)
			FriendList[i] = rhs.FriendList[i];

		for (int i = 0; i < noOfPages; i++)
			LikedPages[i] = rhs.LikedPages[i];

		noOfFriends = rhs.noOfFriends;
		noOfPages = rhs.noOfPages;
		totalPosts = rhs.totalPosts;
	}

	void PrintSearchResults()
	{
		cout << ID << "-" << FirstName << " " << LastName << endl;
	}


	void ViewPageForPost()
	{
		for (int i = 0; i < totalPosts; i++)
		{
			Timeline[i]->PrintInfo();
		}
	}

	// Member function to set the timeline (add posts) for the page (Association)
	void SetTimeline(Post*& temp)
	{
		if (!totalPosts)
			Timeline = new Post * [10];
		Timeline[totalPosts] = temp;
		totalPosts++;
	}



	void ViewTimeline()
	{
		cout << FirstName << " " << LastName << " ***Timeline*** " << endl << endl;
		for (int i = 0; i < totalPosts; i++)
		{
			Timeline[i]->PrintInfo();
		}
	}


	char* Get_FirstName()
	{
		return FirstName;
	}

	char* Get_LastName()
	{
		return LastName;
	}

	void LoadUsers(ifstream& fin)
	{
		char* buffer = new char[80];

		fin >> buffer;
		ID = Helper::GetStringFromBuffer(buffer);

		fin >> buffer;
		FirstName = Helper::GetStringFromBuffer(buffer);

		fin >> buffer;
		LastName = Helper::GetStringFromBuffer(buffer);

	}

	char* GetID()
	{
		return ID;
	}

	void SetColumns(int count)
	{
		noOfFriends = count;
		SetFriends(noOfFriends);
		FriendList = new User * [count];
		for (int i = 0; i < noOfFriends; i++)
			FriendList[i] = 0;
	}
	//void sharememory(Post* ptr, char* text)
	//{
	//	Post* tempptr = new Memory(ptr, text, this);
	//	this->SetTimeline(tempptr);
	//}



	void viewmemories() {
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n\n";
		cout << "------On this Day-----" << endl;
		cout << "4 years ago" << endl;
		for (int i = 0; i < totalPosts; i++) {
			Post* currentpost = Timeline[i];
			Date PostDate = currentpost->getdate();
			if (PostDate.getDay() == Date::getcurrentdate().getDay() &&
				PostDate.getMonth() == Date::getcurrentdate().getMonth()) {
				cout << Date::getcurrentdate().getYear() - PostDate.getYear() << " Year Ago\n";
				PrintName();
				Timeline[i]->viewpost();
				cout << endl;
			}
		}
	}






	void SetColumns_Pages(int count)
	{
		noOfPages = count;

		LikedPages = new Page * [count];
		for (int i = 0; i < noOfPages; i++)
			LikedPages[i] = 0;
	}

	void AddPages(Page* Pages, int index)
	{
		if (LikedPages[index] == 0)
			LikedPages[index] = Pages;
	}

	void AddFriend(User* Friends, int index)
	{
		if (FriendList[index] == 0)
			FriendList[index] = Friends;
	}

	int SetFriends(int total)
	{
		noOfFriends = total;
		return noOfFriends;
	}

	void PrintFriends()
	{
		cout << endl;

		for (int i = 0; i < noOfFriends; i++)
		{
			cout << FriendList[i]->GetID() << "\t  " << FriendList[i]->Get_FirstName() << " " << FriendList[i]->Get_LastName();
			cout << endl;
		}
	}

	void PrintHomePage()
	{

		for (int i = 0; i < noOfFriends; i++)
		{
			for (int j = 0; j < FriendList[i]->totalPosts; j++)
			{
				FriendList[i]->Timeline[j]->PrintLatestFreindsPosts();
			}
		}

		for (int i = 0; i < noOfPages; i++)
		{
			LikedPages[i]->PrintLatestPagesPost();
		}
	}

	void PrintPages()
	{
		cout << endl;
		for (int i = 0; i < noOfPages; i++)
		{
			cout << LikedPages[i]->GetID() << "\t  " << LikedPages[i]->Get_Title();
			cout << endl;
		}
	}

	void Allocate()
	{
		FriendList = new User * [10];
	}

	void FixColumn_forPages(int cols)
	{
		LikedPages = new Page * [20];
	}

	void FixColumns_forUsers(int cols)
	{
		FriendList = new User * [20];
	}

	void PrintName()
	{
		cout << FirstName << " " << LastName << " ";

	}
};

//Inheritance
class Memory : public Post {
	Post* SharedPost; //Aggregation
	Date SharedDate; //composition

public:
	Memory(Post* ptr, char* Text, object* CurrentUser) {
		SharedPost = ptr;
		SharedDate = SharedPost->getdate();
	}

	void viewpost() {

		Post::getsharedby()->PrintName();
		cout << " --------shared a memory--------------";

		cout << "...";
		SharedDate.PrintUserDate();
		//cout << "\n\"" << gettext() << "\"\n";
		cout << "\t\t(" << Date::currentDate.getYear() - SharedDate.getYear() << " Years Ago)\n";

		//SharedPost->viewpost();

		cout << endl << endl;
	}
};


class Activity :public Post //inheritance
{
	int Type;
	char* Value;

public:

	Activity() :Post()
	{
		Type = 0;
		Value = 0;
	}

	~Activity()
	{
		if (Value)
			delete[] Value;
	}

	void PrintLatestFreindsPosts()
	{
		Author->PrintName();
		if (Type == 1) cout << " is feeling ";
		if (Type == 2) cout << " is thinking about ";
		if (Type == 3) cout << " is making ";
		if (Type == 4) cout << " is celebrating ";

		cout << Value << endl;
		cout << "'" << Text << "'" << endl;;
		PrintAllComments();
		cout << endl;

	}

	void PrintLatestPagesPost()
	{
		if (Post::PostedOn.CheckTime())
		{
			Author->PrintName();
			if (Type == 1) cout << " is feeling ";
			if (Type == 2) cout << " is thinking about ";
			if (Type == 3) cout << " is making ";
			if (Type == 4) cout << " is celebrating ";

			cout << Value << endl;
			cout << "'" << Text << "'" << endl;;
			PrintAllComments();
			cout << endl;
		}
	}

	void LoadFromFile(ifstream& input)
	{
		Post::LoadFromFile(input);
		char* temp = new char[80];

		input >> Type;
		input.getline(temp, 80, '\n');
		Value = Helper::GetStringFromBuffer(temp);
	}

	void Print()
	{
		if (Type == 1) cout << " is feeling";
		if (Type == 2) cout << " is thinking about";
		if (Type == 3) cout << " is making";
		if (Type == 4) cout << " is celebrating";
		cout << Value << endl;
		Post::Print();
	}

	void PrintInfo()
	{
		Author->PrintName();
		if (Type == 1) cout << " is feeling ";
		if (Type == 2) cout << " is thinking about ";
		if (Type == 3) cout << " is making ";
		if (Type == 4) cout << " is celebrating ";

		cout << Value << endl;
		cout << "'" << Text << "'";
		PostedOn.PrintUserDate();
		PrintAllComments();
		cout << endl;
	}

	void PrintSearchResults()
	{

		cout << ID_ofPost << "-";
		Author->PrintName();
		if (Type == 1) cout << " is feeling ";
		if (Type == 2) cout << " is thinking about ";
		if (Type == 3) cout << " is making ";
		if (Type == 4) cout << " is celebrating ";

		cout << Value << endl;
		cout << "'" << Text << "'" << endl;;
	}
};

class Facebook
{
private:
	User* CurrentUser; // Aggregation: Facebook has a relationship with User.
	User** UsersList; // Aggregation: Facebook has a list of User objects.
	Page** PageList; // Aggregation: Facebook has a list of Page objects.
	Post** AllPosts; // Aggregation: Facebook manages a list of Post objects.
	int TotalPosts;
	int TotalComments;
	int activity;
	int total_users;
	int total_pages;


public:

	Facebook()
	{
		CurrentUser = 0;
		UsersList = NULL;
		PageList = 0;
		TotalPosts = 0;
		activity = 0;
		TotalComments = 0;
		total_pages = 0;
		total_users = 0;
		AllPosts = 0;
	}

	~Facebook()
	{

		if (UsersList)
		{
			for (int i = 0; i < total_users; i++)
			{
				delete UsersList[i];
			}
			delete[] UsersList;
		}

		if (PageList)
		{
			for (int i = 0; i < total_pages; i++)
			{
				delete[] PageList[i];
			}
			delete[] PageList;
		}

		if (AllPosts)
		{

			delete[] AllPosts;
		}
	}

	//Association
	Page* SearchString_fromPage(char* temp)
	{
		for (int i = 0; i < 12; i++)
		{
			if (Helper::CompareStrings(PageList[i]->GetID(), temp))
				return  PageList[i];
		}
		return 0;
	}

	void ViewPage(char* temp)
	{
		object* post = GetAuthorFromID(temp);
		post->ViewPageForPost();
	}

	void ViewPost(char* post)
	{
		Post* _post = GetPostFromID(post);
		_post->PrintInfo();

	}

	void PostComment(char* tempPost, char* temptext)
	{
		Comments* AddNewComment = new Comments;
		Post* Post = GetPostFromID(tempPost);

		char tempstring[10];

		_itoa_s(++TotalComments, tempstring, 10);
		char* tempIDofComment = Helper::Concatenate((char*)"c", tempstring);
		AddNewComment->SetNewComment(CurrentUser, temptext, tempIDofComment);
		Post->SaveComment(AddNewComment);

	}

	//Association
	Post* GetPostFromID(char* temp)
	{
		for (int i = 0; i < TotalPosts; i++)
		{
			if (Helper::CompareStrings(AllPosts[i]->GetID_ofPost(), temp))
			{
				return AllPosts[i];
			}
		}
		return NULL;
	}

	void LikePost(char* temp)
	{
		Post* P = GetPostFromID(temp);
		P->AddLikedBy(CurrentUser);
	}

	void LikedList(char* temp)
	{
		Post* P = GetPostFromID(temp);
		P->PrintLikes();
	}


	User* SearchString(char* temp) //Assocciation
	{
		for (int i = 0; i < 20; i++)
		{
			if (Helper::CompareStrings(UsersList[i]->GetID(), temp))
				return  UsersList[i];
		}
		return 0;
	}

	void Friends_Association(char***& tempUser)
	{
		int count = 0;
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				int check = Helper::CompareStrings(tempUser[i][j]);
				if (check == 1) break;
				count++;
			}
			UsersList[i]->SetColumns(count);

			count = 0;
			int temp = 0;
			for (int j = 0; j < 20; j++)
			{
				int check = Helper::CompareStrings(tempUser[i][j]);
				User* U = SearchString(tempUser[i][j]);

				if (check == 1) break;

				if (U != 0)
					UsersList[i]->AddFriend(U, temp);

				temp++;
			}
		}
	}

	void Pages_Association(char***& tempUser)
	{
		int count = 0;
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				int check = Helper::CompareStrings(tempUser[i][j]);
				if (check == 1) break;
				count++;
			}

			UsersList[i]->SetColumns_Pages(count);

			int temp = 0;
			for (int j = 0; j < count; j++)
			{
				int check = Helper::CompareStrings(tempUser[i][j]);
				Page* _page = SearchString_fromPage(tempUser[i][j]);

				if (check == 1) break;

				if (_page != 0)
				{
					UsersList[i]->AddPages(_page, temp);
				}
				temp++;
			}
			count = 0;
		}
	}

	User* SetCurrentUser(char* temp)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (Helper::CompareStrings(temp, UsersList[i]->GetID()))
				{
					CurrentUser = UsersList[i];

					CurrentUser->PrintName();
					cout << " successfully set as a current user. " << endl;
					break;
				}
			}
		}

		cout << "---------------------------------------------------------------------------------" << endl << endl;
		cout << "Command:\t\tView FriendList" << endl;
		cout << "---------------------------------------------------------------------------------" << endl << endl;

		CurrentUser->PrintName();
		cout << " - FriendList " << endl;
		CurrentUser->PrintFriends();
		cout << endl;
		cout << "---------------------------------------------------------------------------------" << endl << endl;
		cout << "Command:\t\tView Liked Pages" << endl;
		cout << "---------------------------------------------------------------------------------" << endl << endl;
		CurrentUser->PrintName();
		cout << " - Liked Pages " << endl;
		CurrentUser->PrintPages();
		cout << endl;

		return CurrentUser;
	}

	void LoadData(ifstream& IN, ifstream& fin, ifstream& linksin)
	{
		fin >> total_users;
		IN >> total_pages;
		bool check = 0;

		char*** tempUser = new char** [total_users];
		char*** tempPages = new char** [total_users];

		for (int i = 0; i < total_users; i++)
		{
			tempUser[i] = new char* [10];
			tempPages[i] = new char* [10];
		}

		int count = 0;
		char* temp;
		UsersList = new User * [total_users];
		for (int i = 0; i < total_users; i++)
		{
			UsersList[i] = new User;
			UsersList[i]->LoadUsers(fin);
		}

		for (int i = 0; i < total_users; i++)
		{
			count = 0;
			for (int j = 0; j < 10; j++)
			{
				char* buffer = new char[80];
				linksin >> buffer;
				check = Helper::CompareStrings(buffer);
				temp = Helper::GetStringFromBuffer(buffer);
				tempUser[i][j] = temp;

				if (check == 1) break;
				count++;
			}

			for (int j = 0; j < 10; j++)
			{
				char* buffer = new char[80];
				linksin >> buffer;
				check = Helper::CompareStrings(buffer);
				count++;
				temp = Helper::GetStringFromBuffer(buffer);
				tempPages[i][j] = temp;

				if (check == 1) break;
			}
		}

		count = 0;
		Friends_Association(tempUser);

		PageList = new Page * [total_pages];
		for (int i = 0; i < total_pages; i++)
		{
			PageList[i] = new Page[1];
			PageList[i]->LoadDataFromPages(IN);
		}
		Pages_Association(tempPages);
	}

	// Association
	object* GetAuthorFromID(char* ID)
	{
		char* tempBuffer = new char[80];
		for (int i = 0; i < TotalPosts; i++)
		{
			if (ID[0] == 'u')
			{
				for (int j = 0; j < 20; j++)
				{
					if (Helper::CompareStrings(UsersList[j]->GetID(), ID))
					{
						return UsersList[j];
					}
				}
			}

			else
			{
				for (int j = 0; j < 12; j++)
				{
					if (Helper::CompareStrings(PageList[j]->GetID(), ID))
					{
						return PageList[j];
					}
				}
			}
		}
	}

	void LoadAllPosts(ifstream& input)
	{

		int  temp = 0, NoOfLikes = 0;
		input >> TotalPosts;

		AllPosts = new Post * [TotalPosts];

		for (int i = 0; i < TotalPosts; i++)
		{
			NoOfLikes = 0;
			int activity;
			input >> activity;
			if (activity == 1)
				AllPosts[i] = new Post;

			else
				AllPosts[i] = new Activity;

			object* Author;

			AllPosts[i]->LoadFromFile(input);
			char* temp = new char[80];
			char* tempID;
			input >> temp;
			tempID = Helper::GetStringFromBuffer(temp);

			Author = GetAuthorFromID(tempID);

			AllPosts[i]->SetAuthor(Author);
			Author->SetTimeline(AllPosts[i]);

			char* tempLikedID = new char[10];
			int j = 0;
			while (j < 10)
			{
				input >> tempLikedID;

				if (tempLikedID[0] == '-')
				{
					break;
				}
				j++;
				Author = GetAuthorFromID(tempLikedID);
				AllPosts[i]->SetLikes(Author);
			}
		}
	}

	// Association:
	Post* SearchPostFromID(char* temp)
	{
		for (int i = 0; i < TotalPosts; i++)
		{
			if (Helper::CompareStrings(temp, AllPosts[i]->GetID_ofPost()))
			{
				return AllPosts[i];
			}
		}
	}
	void LoadActivitiessFromFile(ifstream& inputA) {
		char* tempID = nullptr;
		char* tempText = nullptr;
		int tempType;

		while (inputA >> tempID >> tempType) {
			inputA.ignore(); // Ignore the space
			tempText = new char[80];
			inputA.getline(tempText, 80);

			// Create an instance of Activity
			Activity* newActivity = new Activity();

			// Set the ID and text
			//newActivity->GetID_ofPost(tempID);
			//newActivity->SetValue(tempText);

			// Set the type
			//newActivity->SetType(tempType);

			// Add the activity to the timeline or wherever it should be added
			// For example, if Timeline is a member variable, you can add it like this:
			//SetTimeline(newActivity);
		}
	}


	void LoadAllComments(ifstream& FIN)
	{
		char* tempID_ofComment = 0;
		char* tempID_ofPost = 0;
		char* CommentBy = 0;
		char* Temptext = 0;
		char* buffer = new char[80];

		FIN >> TotalComments;
		Comments** AllComments = new Comments * [TotalComments];

		for (int i = 0; i < TotalComments; i++)
		{
			AllComments[i] = new Comments;

			FIN >> buffer;
			tempID_ofComment = Helper::GetStringFromBuffer(buffer);
			FIN >> buffer;
			tempID_ofPost = Helper::GetStringFromBuffer(buffer);
			FIN >> buffer;
			CommentBy = Helper::GetStringFromBuffer(buffer);
			FIN.ignore();
			FIN.getline(buffer, 80);
			Temptext = Helper::GetStringFromBuffer(buffer);

			object* OBJ = GetAuthorFromID(CommentBy);
			AllComments[i]->SetCommentInfo(tempID_ofComment, OBJ, Temptext);

			Post* _post = SearchPostFromID(tempID_ofPost);

			_post->SaveComment(AllComments[i]);
		}
	}
};

//Association:
//The function Run takes an instance of the Facebook class (fb)as its first parameter.
//Aggregation:
//The function takes a pointer to a User object(CurrentUser) as its second parameter.

void Controller(Facebook& fb, User* CurrentUser, ifstream& input, ifstream& FIN) {
	cout << "---------------------------------------------------------------------------------" << endl << endl;
	cout << "Command:\tSet Current System Date 17 04 2024" << endl;
	cout << "---------------------------------------------------------------------------------" << endl << endl;
	cout << "System Date:\t";
	Date::SetCurrentDate(17, 04, 2024);
	Date::currentDate.PrintCurrentDate();
	cout << endl << endl;

	cout << "Command:\tSetCurrentUser 'u7' " << endl << endl;
	CurrentUser = fb.SetCurrentUser((char*)"u7");
	cout << "---------------------------------------------------------------------------------------" << endl << endl;

	cout << "Command:\tView Timeline" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	CurrentUser->ViewTimeline();
	cout << "---------------------------------------------------------------------------------------" << endl << endl;

	cout << "Command:\tView LikedList(post5)" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	fb.LikedList((char*)"post5");
	cout << "---------------------------------------------------------------------------------------" << endl << endl;

	cout << "Command:\tView Likedpost(post5)" << endl;
	cout << "Command:\tView LikedList(post5)" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	fb.LikedList((char*)"post5");
	fb.LikePost((char*)"post5");
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	cout << "Command:\t\t View Page" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	fb.ViewPage((char*)"p1");
	cout << endl;
	fb.ViewPage((char*)"p11");
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	cout << "Command:\tView HomePage" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	CurrentUser->PrintHomePage();

	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	cout << "Command:\tPost Comment" << endl;
	cout << "Command:\tView Post" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	fb.PostComment((char*)"post4", (char*)"Good Luck for your Result");
	fb.ViewPost((char*)"post4");
	fb.PostComment((char*)"post8", (char*)"Thanks for the wishes");
	fb.ViewPost((char*)"post8");
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	cout << "Command:     See Your Memories\n";
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	CurrentUser->viewmemories();
	fb.ViewPost((char*)"post10");

	cout << endl << endl;
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	cout << "Command:     Share Memory\n";
	cout << "Command:     View timeline \n";
	cout << "---------------------------------------------------------------------------------------" << endl << endl;
	cout << "u7" << "--------Shared a memory--------" << endl;
	CurrentUser->viewmemories();
	fb.PostComment((char*)"post10", (char*)"Never Thought i will be a speacialist in tis field!");
	cout << endl;
	CurrentUser->ViewTimeline();
	cout << "---------------------------------------------------------------------------------" << endl << endl;
	cout << "Command:\tSetCurrentUser 'u11' " << endl << endl;
	cout << "---------------------------------------------------------------------------------" << endl << endl;
	fb.SetCurrentUser((char*)"u11");
	cout << "---------------------------------------------------------------------------------" << endl << endl;
}

int main() {
	ifstream IN("Pages.txt");
	ifstream fin("Users.txt");
	ifstream linksinput("Links.txt");
	ifstream input("SocialNetworkPosts.txt");
	ifstream FIN("SocialNetworkComments.txt");
	ifstream inputA("SocialnetworkActivities.txt");
	Facebook fb;

	fb.LoadData(IN, fin, linksinput);

	fb.LoadAllPosts(input);
	fb.LoadAllComments(FIN);

	// Call the Controller function for passing necessary data
	Controller(fb, nullptr, input, FIN);
	system("pause");
	return 0;
}
