    #include <iostream>
    #include <string>
    #include <fstream>
    using namespace std;
        struct Questions_Answers
        {
            int Form_I_D = 0;
            int To_I_D = 0;
            bool Answer_True = false;
            string Question;
            string Answer;
        };
        struct Account
        {
            string Name, EMail, Password;
            bool Allow_Anonymous_Questions;
        };
        Account Array_OF_Accounts[int(1e4)];
        Questions_Answers S_Array[int(1e5)];    
        int My_ID;
        int Number_OF_Users;
        int Number_OF_Questions;
    void PreProccessor()
        {
            ifstream Read;
                Read.open("Users_Data.txt");
                if (Read.is_open())
                {
                    Number_OF_Users = 1;
                    while (Read >> Array_OF_Accounts[Number_OF_Users].Name >> Array_OF_Accounts[Number_OF_Users].Password >> Array_OF_Accounts[Number_OF_Users].EMail >> Array_OF_Accounts[Number_OF_Users].Allow_Anonymous_Questions)
                    {
                        Number_OF_Users++;
                    }
                }
                else
                {
                    cout << "Unable to open Users File\n";
                }
                Read.close();
        }
    void Questions_Update()
    {
            ifstream Read("Questions.txt");
            int To, From;
            if (Read.is_open())
            {
                Number_OF_Questions = 1;
                while (Read >> S_Array[Number_OF_Questions].Form_I_D >> S_Array[Number_OF_Questions].To_I_D)
                {
                    Read.ignore();
                    getline(Read, S_Array[Number_OF_Questions].Question);
                    Number_OF_Questions++;
                }
            }
            else
            {
                cout << "Unable to open Users File\n";
            }
    }
    void Answers_Update()
    {
            ifstream Read("Answers.txt");
            int Q_ID = -1;
            if (Read.is_open())
            {
                while (Read >> Q_ID)
                {
                    Read.ignore();
                    getline(Read, S_Array[Q_ID].Answer);
                    S_Array[Q_ID].Answer_True = true;
                }
            }
            else
            {
                cout << "Unable to open Users File\n";
            }
    }
    void Answers_Upload()
    {
        ofstream Write("Answers.txt", ios::trunc);
        for (int a = 1; a < Number_OF_Questions; a++)
        {
            if (S_Array[a].Answer_True)
            {
                Write << a << '\n' << S_Array[a].Answer << '\n';
            }
        }
    }
    class Users_Acc
    {
    private:    
        Account A1;
    public:
        Users_Acc()
        {
            A1.Name = '0';
            A1.EMail = '0';
            A1.Password = '0';
            A1.Allow_Anonymous_Questions = true;
        }
        friend istream& operator >> (istream&Input, Users_Acc&User)
        {
            cout << "Enter Your Name ";
            getline(Input, User.A1.Name);
            while (!User.Valid_Name())
            {
                cout << "Enter Another Name ";
                getline(Input, User.A1.Name);
            }
            cout << "Enter you EMail ";
            getline(Input, User.A1.EMail);
            while (!User.Valid_EMail())
            {
                cout << "Enter Another Email ";
                getline(Input, User.A1.EMail);
            }
            cout << "Enter your Password ";
            getline(Input, User.A1.Password);
            cout << "Do You Allow Anonymous Questions(1 To Allow, 0 To NoT Allow)? ";
            cin >> User.A1.Allow_Anonymous_Questions;
            return Input;
        }
        friend ostream& operator << (ostream&output, Users_Acc&User)
        {
            output << "Name : " << User.A1.Name << '\n';
            output << "Email : " << User.A1.EMail << '\n';
            output << "Password : " << User.A1.Password << '\n';
            output << "Allow Anonymous Questions : " << boolalpha << User.A1.Allow_Anonymous_Questions << '\n';
            return output;
        }
        void SignUp()
        {
            cin >> (*this);
            ofstream File_Output("Users_Data.txt", ios::app);
            cout << "Your ID is " << Number_OF_Users << '\n';
            cout << "Welcome to Askfm System!\n";
            File_Output << A1.Name << '\n' << A1.Password << '\n' << A1.EMail << '\n' << A1.Allow_Anonymous_Questions << '\n';
            File_Output.close();
            PreProccessor();
        }
        bool Login()
        {
            ifstream File_Input;
            bool Yes = false;
            cout << "Enter Your Name : "; cin >> A1.Name;
            cout << "Enter Your password : "; cin >> A1.Password;
            for (int j = 1; j <= Number_OF_Users; j++)
            {
                if (Array_OF_Accounts[j].Name == A1.Name)
                {
                    if (A1.Password == Array_OF_Accounts[j].Password)
                    {
                        My_ID = j;
                        cout << "Your ID is : " << My_ID << '\n';
                        Yes = true;
                    }
                }
            }
            if (Yes)
            {
                cout << A1.Name << ", Welcome to Our System\n";
            }
            else
            {
                cout << "Your Name or Password is Wrong\n";
            }
            return Yes;
        }
        bool Valid_Name()
        {
            for (int g = 1; g <= Number_OF_Users; g++)
            {
                if (A1.Name == Array_OF_Accounts[g].Name)
                {
                    cout << "This Name has been used\n";
                    return false;
                    break;
                }
            }
            return true;
        }
        bool Valid_EMail()
        {
            for (int g = 1; g <= Number_OF_Users; g++)
            {
                if (A1.EMail == Array_OF_Accounts[g].EMail)
                {
                    cout << "This Email has been used\n";
                    return false;
                    break;
                }
            }
            return true;
        }
    };
    class User : public Users_Acc {
    public:
        User()
        {
            PreProccessor();
            Questions_Update();
            Answers_Update();
        }
        void Ask_Question()
        {
            int Send_To; string Q; char ch = 'N';
            Here:
            cout << "Press 0 to Back\nEnter User ID : "; cin >> Send_To;
            if (Send_To < 0 || Send_To > Number_OF_Users)
            {
                cout << "This User Dosen't Exist...!\n";
                goto Here;
            }
            if (!Send_To)
            {
                return;
            }
            if (Send_To == My_ID)
            {
                cout << "You Can't Ask Yourself!\n";
                goto Here;
            }
            cin.ignore();
            if (Array_OF_Accounts[Send_To].Allow_Anonymous_Questions)
            {
                cout << "Do you want Anonymous Question(y/n)?!"; cin >> ch;
            }
            else
            {
                int Num;
                cout << "Note : " << Array_OF_Accounts[Send_To].Name << " Doesn't Allow Anonymous Questions Press -1 To Cancel or 1 to Continue : ";
                cin >> Num;
                if (Num == -1)
                {
                    return;
                }
            }
            cin.ignore();
            cout << "Your Question : "; getline(cin, Q);
            ofstream Write("Questions.txt", ios::app);
            if (ch == 'y' || ch == 'Y')
            {
                Write << (-My_ID) << ' ' << Send_To << '\n' << Q << '\n';
            }
            else
            {
                Write << My_ID << ' ' << Send_To << '\n' << Q << '\n';
            }
            Questions_Update();
        }
        void Answer_Question()
        {
            ofstream Write("Answers.txt", ios::app); int Q_ID;
            here:
            cout << "Press 0 to Back\nEnter Question ID  : ";
            cin >> Q_ID;
            if (Q_ID < 0 || Q_ID > Number_OF_Questions)
            {
                cout << "This Question Dosen't Exist\n";
                goto here;
            }
            if (!Q_ID)
            {
                return;
            }
            if (S_Array[Q_ID].Question == "~ Deleted Question")
            {
                cout << "Your Can't Answer Deleted Question.\n";
                return;
            }
            cin.ignore();
            if (S_Array[Q_ID].To_I_D == My_ID && S_Array[Q_ID].Answer_True == true)
            {
                char C;
                cout << "Warning: This Question Has Been Answered Before, Do You Want Update The Answer(y/n) ?! "; cin >> C;
                if (C == 'Y' || C == 'y')
                {
                    cout << "Write Your New Answer : ";
                    cin.ignore();
                    getline(cin, S_Array[Q_ID].Answer);
                    Answers_Upload();
                }
            }
            else if (S_Array[Q_ID].To_I_D == My_ID)
            {
                cout << "Write Your Answer : ";
                getline(cin, S_Array[Q_ID].Answer);
                S_Array[Q_ID].Answer_True = true;
                Write << Q_ID << '\n' << S_Array[Q_ID].Answer << '\n';
            }
            else
            {
                cout << "You can't Answer This Question...!\n";
            }
            Answers_Update();
        }
        void Print_Questions_TO_ME()
        {
            Questions_Update();
            Answers_Upload();
            Answers_Update();
            ifstream Input("Questions.txt");
            if (Input.is_open())
            {
                for (int a = 1; a < Number_OF_Questions; a++)
                {
                    if (S_Array[a].To_I_D == My_ID)
                    {
                        if (S_Array[a].Form_I_D < 0)
                        {
                            cout << "Question ID(" << a << ") From Anonymous User To You : " << S_Array[a].Question << '\n';
                        }
                        if (S_Array[a].Form_I_D > 0)
                        {
                            cout << "Question ID(" << a << ") From " << Array_OF_Accounts[S_Array[a].Form_I_D].Name << " To You : " << S_Array[a].Question << '\n';
                        }
                        if (S_Array[a].Answer_True && S_Array[a].Question != "~ Deleted Question")
                        {
                            cout << "\tAnswer : " << S_Array[a].Answer << '\n';
                        }
                        else if (S_Array[a].Question == "~ Deleted Question")
                        {
                            S_Array[a].Answer = "The Question And Answer Have Been Deleted.\n";
                            cout << S_Array[a].Answer;
                        }
                        else
                        {
                            cout << "This Question Hasn't Been Answered Yet.\n";
                        }
                    }
                }
            }
            else
            {
                cout << "Unable to open Questions File\n";
            }
        }
        void Print_Questions_From_ME()
        {
            Questions_Update();
            Answers_Update();
            ifstream Input("Questions.txt");
            if (Input.is_open())
            {
                for (int a = 1; a < Number_OF_Questions; a++)
                {
                    if (S_Array[a].Form_I_D == My_ID)
                    {
                        cout << "Question ID (" << a << ") From You To " << Array_OF_Accounts[S_Array[a].To_I_D].Name << " : "<< S_Array[a].Question << '\n';
                        if (S_Array[a].Answer_True && S_Array[a].Question != "~ Deleted Question")
                        {
                            cout << "\tAnswer : " << S_Array[a].Answer << '\n';
                        }
                        else if (S_Array[a].Question == "~ Deleted Question")
                        {
                            S_Array[a].Answer = "The Question And Answer Have Been Deleted By " + Array_OF_Accounts[S_Array[a].Form_I_D].Name + ".!\n";
                            cout << S_Array[a].Answer;
                        }
                        else
                        {
                            cout << "This Question Hasn't Been Answered Yet.\n";
                        }
                    }
                    if (S_Array[a].Form_I_D == (-My_ID))
                    {
                        cout << "Anonymous Question ID (" << a << ") From You To " << Array_OF_Accounts[S_Array[a].To_I_D].Name << " : "<< S_Array[a].Question << '\n';
                        if (S_Array[a].Answer_True && S_Array[a].Question != "~ Deleted Question")
                        {
                            cout << "\tAnswer : " << S_Array[a].Answer << '\n';
                        }
                        else if (S_Array[a].Question == "~ Deleted Question")
                        {
                            S_Array[a].Answer = "The Question And Answer Have Been Deleted By " + Array_OF_Accounts[S_Array[a].Form_I_D].Name + '\n';
                            cout << S_Array[a].Answer;
                        }
                        else
                        {
                            cout << "This Question Hasn't Been Answered Yet.\n";
                        }
                    }
                }
            }
            else
            {
                cout << "Unable to open Questions File\n";
            }
        }
        void Delete_Question()
        {
            Questions_Update();
            Answers_Update();
            ifstream Input("Questions.txt");
            if (Input.is_open())
            {
                int a, Q_ID, To, From;
                cout << "Press 0 to Back\nEnter Question ID You Want to be Deleted : ";
                cin >> a;
                cin.ignore();
                if (!a)
                {
                    return;
                }
                    if (S_Array[a].Form_I_D == My_ID || S_Array[a].Form_I_D == (-My_ID))
                    {
                        string line;
                        while (Input >> From >> To)
                        {
                            Input.ignore();
                            getline(Input, line);
                                if (line == S_Array[a].Question)
                                {
                                    S_Array[a].Question = "~ Deleted Question\n";
                                    cout << "Question ID (" << a << ") Has Been Deleted\n";
                                }
                        }
                        Input.close();
                        ofstream Write("Questions.txt");
                        for (int u = 1; u < Number_OF_Questions; u++)
                        {
                            Write << S_Array[u].Form_I_D << ' ' << S_Array[u].To_I_D << '\n' << S_Array[u].Question << '\n';
                        }
                        Write.close();
                        Input.open("Answers.txt");
                        while (Input >> Q_ID)
                        {
                            getline(Input, line);
                            if (Q_ID = a)
                            {
                                S_Array[a].Answer_True = false;
                            }
                        }
                        Input.close();
                        Write.open("Answers.txt");
                        for (int u = 1; u < Number_OF_Questions; u++)
                        {
                            if (S_Array[u].Answer_True)
                            {
                                Write << u << '\n' << S_Array[u].Answer << '\n';
                            }  
                        }
                        Write.close();
                    }
                    else
                        {
                            cout << "You Can't Delete This Question\n";
                        }
            }
            else
            {
                cout << "Unable to open Questions or Answers File\n";
            }
        }
        void Users_List()
        {
            ifstream Read; int Counter;
                Read.open("Users_Data.txt");
                if (Read.is_open())
                {
                    for (int j = 1; j < Number_OF_Users; j++)
                    {
                        cout << "Name : " << Array_OF_Accounts[j].Name
                        << "\tEmail : " << Array_OF_Accounts[j].EMail
                        << "\nID : " << j << "\t\tAllowing anonymous questions : " 
                        << boolalpha << Array_OF_Accounts[j].Allow_Anonymous_Questions << '\n' << '\n';
                    }
                }
                else
                {
                    cout << "Unable to open Users File\n";
                }
                Read.close();
        }
        void Feed()
        {
            Questions_Update();
            Answers_Update();
            ifstream Input("Questions.txt");
            if (Input.is_open())
            {
                for (int a = 1; a < Number_OF_Questions; a++)
                {
                    if (S_Array[a].Answer_True && S_Array[a].Question != "~ Deleted Question" && S_Array[a].Answer != "This Question Hasn't Been Answered Yet.")
                    {
                        if (S_Array[a].Form_I_D < 0)
                        {
                            cout << "Question ID (" << a << ") From Anonymous User To " << Array_OF_Accounts[S_Array[a].To_I_D].Name << " : " << S_Array[a].Question << '\n';
                        }
                        else
                        {
                            cout << "Question ID (" << a << ") From " << Array_OF_Accounts[S_Array[a].Form_I_D].Name << " To "  << Array_OF_Accounts[S_Array[a].To_I_D].Name << " : " << S_Array[a].Question << '\n';
                        }
                        cout << "\tAnswer : " << S_Array[a].Answer << '\n';
                    }
                }
            }
            else
            {
                cout << "Unable to open Questions File\n";
            }
        }
        void Delete_Answer()
        {
                int Q_ID;
                Try:
                cout << "Press 0 to Back\nEnter Question ID You Want to Delete His Answer : ";
                cin >> Q_ID;
                cin.ignore();
                if (!Q_ID)
                {
                    return;
                }
                if (Q_ID < 0 || Q_ID > Number_OF_Questions)
                {
                    cout << "This Question Dosen't Exist\n";
                    goto Try;
                }
                    if (S_Array[Q_ID].To_I_D == My_ID)
                    {
                        if (S_Array[Q_ID].Question == "~ Deleted Question")
                        {
                            cout << "This is Already Deleted Question\n";
                            return;
                        }
                        ofstream Write("Answers.txt", ios::trunc);
                        for (int u = 1; u < Number_OF_Questions; u++)
                        {   
                            if ((S_Array[u].Question == S_Array[Q_ID].Question && S_Array[u].Answer == S_Array[Q_ID].Answer))
                            {
                                cout << "Answer OF Question ID (" << Q_ID << ") Has Been Deleted\n";
                                S_Array[u].Answer = "This Question Hasn't Been Answered Yet.\n";
                            }
                        }
                        Write.close();
                        Answers_Upload();
                        Answers_Update();
                    }
                    else
                    {
                        cout << "You Can't Delete This Answer\n";
                    }
        }
        ~User()
        {
            cout << "See You Later...!\n";
        }
    };
    int main()
    {
        cout << "-------------------- Askfm System --------------------\n";
        User U;
        int Number;
            Invalid:
            cout << "For Login Press 1, And For Sign Up Press 2 : "; cin >> Number;
            switch (Number)
            {
            case 1:
            if (!U.Login())
            {
                goto Invalid;
            }
                break;
            case 2:
                cin.ignore();
                U.SignUp();
                U.Login();
                break;
            default:
                cout << "Invalid Number, Please Try Again..\n";
                break;
            }
            bool Logout = false;
                Cancel:
            while (!Logout)
            {
                cout << "\nMenu:-\n-----------------------------------------------------------------------------------------------\n";
                cout <<
                "1: Print Questions To Me\n" <<
                "2: Print Questions From Me\n" <<
                "3: Ask Question\n" <<
                "4: Answer Question or Edit Answer\n" <<
                "5: Delete Question\n" <<
                "6: Delete Answer\n"<<
                "7: System Users List\n" <<
                "8: Feed\n" <<
                "9: Logout\nEnter Number in Range 1 - 9 : ";
                int Operation;
                cin >> Operation;
                switch (Operation)
                {
                case 1:
                    U.Print_Questions_TO_ME();
                    break;
                case 2:
                    U.Print_Questions_From_ME();
                    break;
                case 3:
                    U.Ask_Question();
                    break;
                case 4:
                    U.Answer_Question();
                    break;
                case 5:
                    U.Delete_Question();
                    break;
                case 6:
                    U.Delete_Answer();
                    break;
                case 7:
                    U.Users_List();
                    break;
                case 8:
                    U.Feed();
                    break;
                case 9:
                    Logout = true;
                    break;
                default:
                    "Invalid Number, Please Try Again..\n";
                    break;
                }
            }
    }