/// CIS22C-HM2B : This single file will contain all the code for Homework 2. Program execution begins and ends here (in main).
//


using namespace std;
#include <iostream>
#include <fstream>

/*
  The following code file is divided into 4 sections

	1. The interface and code for Class Student  (supplied)
	2. The interface and code for class StudentEsa  (insert your HM1 code here)
	3. The interface and code for class StudentDQI  (The interface is supplied. HM2 is writing the code to implement this interface)
	4. The HM2 test program code (supplied)
*/


// 1.  ************************ class Student code included here  ***************************

class Student
{   // A VERY simple Student consisting only of the student's ID and Name
    // Both the interface and the code will be located here.
   
private:
    int sid; // Student ID
    string sname; // Full Name (Ex: KleinmanRon)

public:
    Student() { // Default constructor
        sid = 0; sname.clear();
    };
    Student(const Student& os) { // Copy constructor - overwrite internal variables
         sid = os.sid;  sname = os.sname;
    };
    Student(int id, string name) { // Initializer Constructor - set internal variables
        sid = id; sname = name;
    };
    ~Student() { // Default Destructor - clear string
        sname.clear();
    };
  

    //Getters 
    string getName() { return (sname); };
    int getId() { return (sid); };
};

//      ********************** End class Student ***************************************


// 2.   ********************** Insert "class StudentEsa" code from your homework 1 assignment here





//    ********************** End class StudentEsa ******************************


// 3. *************************** Homework 2.  insert the code for the StudentDQI into the StudentDQI interface below ***************


// class "StudentDQI   <Homework #2 - wraps (embeds) Extended Student Array (ESA) so it is invisible to external users of this class

class StudentDQI {
private:
    StudentEsa* soa;  // Allocated Extended Student Array 
          // These might be useful if your solution is for extra credit and positions the DQ in the MIDDLE of the Extended Array
    unsigned int top; // Index value 1 above highest OA element used
    unsigned int btm; // Index value 1 below lowest OA element used
public:
    StudentDQI(unsigned int); // Create a DQ with this initial size 
    StudentDQI(StudentDQI&); // Equate this to an existing DQ (can use private parts directly)
    ~StudentDQI(); // Destruct the DQI (free OA space)

    int getSize();  // Gets # elements (Student *) in the DQ
    bool isEmpty(); // True if no elements held (“pop” will fail)

    int pushFront(Student*); // Prepend a new element to the front
    Student* popFront();      // Remove the first element and return it
    Student* lookFront();      // Return the first element but do not remove it

    int pushBack(Student*); // Append a new element to the back
    Student* popBack();     // Remove the last element and return it
    Student* lookBack();     // Return the last element but do not remove it
};


// **************************** End class StudentDQI ******************************


// 4.  ***********************  Start of StudentDQI Test Program Code  ************

int main()
{ // Redirect Input
    string infileName; // Use if Input redirected
    string outfileName; // Use if output redirected 
    FILE** input = NULL;  // Recovering Cin

    // Command File Record entries
    int ssize; // Size of extended array
    int nops; // # operations to perform

    char command; // Command (G,Z   F,G,H   B,C,D)
            // Not all of the following are present in each command (Default given)
    int num;  // Student ID Number (-1 default)
    string name;  // Student Name (XXXX default)

    StudentDQI* dqi = NULL;   // Pointer to DeQue
    Student sc; // A class to collect Students is generated

    int x = 0; // Useful variables

    cout << "Use input file:  ";
    cin >> infileName; // Get name of file containing input data
    cout << "Using input file " << infileName << endl << endl;

    // Create an input file stream to read supplied file
    std::ifstream inp;
    inp.open(infileName.c_str());
    if (!inp) {
        cerr << "Error: file " << infileName.c_str() << "  could not be opened" << endl;
        exit(1);
    }

    // First line is array size and # commands to add, every subsequent line is one of:
    // 
    // GetSize:      S / -1 / -1
    // isEmpty:      Z / -1 / -1
    // 
    //  PushFront:   F / Student ID / Student Name
    //  PopFront:    G / -1 / -1
    //  LookFront :  H / -1 / -1
    //
    //  PushBack:    B / Student ID / Student Name
    //  PopBack:     C / -1 / -1
    //  LookBack :   D / -1 / -1

    // Get Size of Extended Array and # of commands
    // ssize is size of extended array, nops is # commands

    inp >> ssize >> nops;
    cout << "Read Array size " << ssize << "  Read # commands " << nops << endl;

    Student* stud;    // Array to hold pointer of created student.
    dqi = new StudentDQI(ssize);  // Create Dequeue of specified size.


    for (int i = 0; i < nops; i++) {  // Process Commands 
        //**************************************************************
        inp >> command;
        inp >> num;
        inp >> name;
        cout << "Command: " << command << "  " << num << "  " << name << endl;

        // Process each command
        switch (command)
        { // Convert to command for Extended Array
        case 'S':  // Get Size
            cout << "Size:  " << dqi->getSize() << endl;
            break;

        case 'Z':  // Check if Empty
            cout << "Empty : " << dqi->isEmpty() << endl;
            break;

        case 'F':  // Push Front
            stud = new Student(num, name);
            (void)dqi->pushFront(stud);
            cout << "Pushed Front " << num << "  " << name << endl;
            break;

        case 'G': // Pop Front
            stud = dqi->popFront();
            if (stud) { // Success
                cout << "Pop Front " << stud->getId() << "  " << stud->getName() << endl;
                delete (stud);
            }
            break;

        case 'H':  // Look Front
            stud = dqi->lookFront();
            if (stud) { // Success ... don't delete Student
                cout << "Look Front " << stud->getId() << "  " << stud->getName() << endl;
            }
            break;

        case 'B':  // Push Back
            stud = new Student(num, name);
            (void)dqi->pushBack(stud);
            cout << "Pushed Back " << num << "  " << name << endl;
            break;

        case 'C':  // Pop Back
            stud = dqi->popBack();
            if (stud) { // Success
                cout << "Pop Back " << stud->getId() << "  " << stud->getName() << endl;
                delete (stud);
            }
	    break;

        case 'D':  // Look Back
            stud = dqi->lookBack();
            if (stud) { // Success ... don't delete Student
                cout << "Look Back " << stud->getId() << "  " << stud->getName() << endl;
            }
	    break;

        default:
            cout << "Illegal Command:  " << command << endl;
        }
    }
    // Print out Current contents of extended array
    x = dqi->getSize(); // Get number of array elements
    cout << "------------------" << endl << "Start Popping from bottom  " << x << "  Elements queued" << endl << endl;

    while (stud = dqi->popBack())
    {
            cout << "Student: ID = " << stud->getId() << "  Name = " << stud->getName() << endl;
    }
    return (0);
};


// **********************************  End of test code  *************************************