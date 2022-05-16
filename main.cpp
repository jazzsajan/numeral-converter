//jazz sajan
//MERGE SORT 87-153, CALL LINE 374
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

struct Node {
  int arabic;
  string roman;
  Node * next = nullptr;
};

Node *sorted(Node *first, Node* second, int sortchoice);
void split(Node *main,Node **firstptr, Node **secondptr);

int searchfxn(Node *head, string numsearch){
    Node *temp=head;
    if(isdigit(numsearch[0])){
        int arabicsearch=stoi(numsearch); //convert the arabic string to an int
         while(temp!=nullptr){ //search for arabic
             //cout << temp->arabic;
             if(temp->arabic==arabicsearch){
                 cout << numsearch << " found" << endl;
                 break;
             }
             else if(temp->next == nullptr) {
                 cout << numsearch << " not found" << endl;
             }
             temp=temp->next;
         }
    }
    else{
        string romansearch=numsearch;

        while(temp!=nullptr){ //search for roman
            if(temp->roman.compare(romansearch)==0){
                cout << numsearch << " found" << endl;
                break;
            }
            else if(temp->next == nullptr) {
                cout << numsearch << " not found" << endl;
            }
            temp=temp->next;
        }
    }
    return 0;
}

void printfxn(Node *head, ofstream &outfile){
      if (head==nullptr){
          return;
      }else{
        outfile << setw(16) << left << head->roman << right << head->arabic <<endl;
        printfxn(head->next, outfile);
        }
}

void printfxnConsole(Node *head){
      if (head==nullptr){
          return;
      }else{
        cout << setw(16) << left << head->roman << right << head->arabic <<endl;
        printfxnConsole(head->next);
        }
}

void printA(Node *head){
    if(head==nullptr){
    return;
  }
  cout << head->arabic << '\n';
  printA(head->next);
}

void printR(Node *head){
    if(head==nullptr){
    return;
  }
  cout << head->roman << '\n';
  printR(head->next);
}

void mergesort(Node**headptr, int sortchoice){
    Node *head=*headptr;
    Node *first;
    Node *second;
    
    if ((head == nullptr || head->next == nullptr)){ //base case, empty linked list or one element linked list
        return;
    }
    
    split(head, &first, &second); //split in half
    mergesort(&first,sortchoice); //sort first half
    mergesort(&second,sortchoice); //sort second half
    
    *headptr=sorted(first,second,sortchoice);
}

Node* sorted(Node *first, Node *second, int sortchoice){
    Node *temp=nullptr;
    
    if(first==nullptr){
        return second;
    } else if(second==nullptr) {
        return first;
    }
    
    if(sortchoice==1){ //roman sort
        if(first->roman <= second->roman){
            temp=first;
            temp->next=sorted(first->next, second,sortchoice);
        }else{
            temp=second;
            temp->next=sorted(first, second->next,sortchoice);
        }
        return temp;
    }
    
    if(sortchoice==2){ //arabic sort
        if(first->arabic <= second->arabic){
            temp=first;
            temp->next=sorted(first->next, second,sortchoice);
        }else{
            temp=second;
            temp->next=sorted(first, second->next,sortchoice);
        }
        return temp;
    }
    return temp;
}

void split(Node *main, Node **frontptr, Node **backptr){ //finding middle
    Node *fast;
    Node *slow;
    
    slow=main;
    fast=main->next;
    
    while(fast!=nullptr){
        fast=fast->next;
        if(fast!=nullptr){
            slow=slow->next;
            fast=fast->next;
        }
    }
    *frontptr=main;
    *backptr=slow->next;
    slow->next=nullptr;
}

int romanToArabic(string line){
  int arabic_numeral = 0;

  for (int k = 0; k < static_cast<int>(line.length()); k++) {

    char roman_numeral = line[k];
    char roman_numeralNext = line[k + 1];

    if (roman_numeral == 'M') {
      arabic_numeral += 1000;
    }
    if (roman_numeral == 'D') {
      arabic_numeral += 500;

    }
    if ((roman_numeral == 'C' && roman_numeralNext == 'D') || (roman_numeral == 'C' && roman_numeralNext == 'M')) {

      arabic_numeral -= 100;
 
    } else if (roman_numeral == 'C') {
      arabic_numeral += 100;
    }
    if (roman_numeral == 'L') {
      arabic_numeral += 50;
    } else if ((roman_numeral == 'X' && roman_numeralNext == 'L') || (roman_numeral == 'X' && roman_numeralNext == 'C')) {
      arabic_numeral -= 10;
    } else if (roman_numeral == 'X') {
      arabic_numeral += 10;
    }
    if (roman_numeral == 'V') {
      arabic_numeral += 5;
    }
    if ((roman_numeral == 'I' && roman_numeralNext == 'X') || (roman_numeral == 'I' && roman_numeralNext == 'V')) {
      arabic_numeral -= 1;
    } else if (roman_numeral == 'I') {
      arabic_numeral += 1;
    }
  }
  return arabic_numeral;
}

string
arabicToRoman(int num){
  int thous = num / 1000;
  int hund = num % 1000 / 100;
  int tens = num % 1000 % 100 / 10;
  int ones = num % 1000 % 100 % 10;

  string converted = "";

  for (int i = 0; i < thous; i++) {
    converted.push_back('M');
  }

  if (hund < 4) {
    for (int i = 0; i < hund; i++)
      converted.push_back('C');
  } else if (hund == 4) {
    converted.push_back('C');
    converted.push_back('D');
  } else if (hund == 5) {
    converted.push_back('D');
  } else if (hund > 5 && hund < 9) {
    converted.push_back('D');

    for (int i = 0; i < hund - 5; i++)
      converted.push_back('C');
  } else if (hund == 9) {
    converted.push_back('C');
    converted.push_back('M');
  }

  if (tens < 4) {
    for (int i = 0; i < tens; i++)
      converted.push_back('X');
  } else if (tens == 4) {
    converted.push_back('X');
    converted.push_back('L');
  } else if (tens == 5) {
    converted.push_back('L');
  } else if (tens > 5 && tens < 9) {
    converted.push_back('L');

    for (int i = 0; i < tens - 5; i++)
      converted.push_back('X');
  } else if (tens == 9) {
    converted.push_back('X');
    converted.push_back('C');
  }

  if (ones < 4) {
    for (int i = 0; i < ones; i++)
      converted.push_back('I');
  } else if (ones == 4) {
    converted.push_back('I');
    converted.push_back('V');
  } else if (ones == 5) {
    converted.push_back('V');
  } else if (ones > 5 && ones < 9) {
    converted.push_back('V');
    for (int i = 0; i < ones - 5; i++) {
      converted.push_back('I');
    }
  } else if (ones == 9) {
    converted.push_back('I');
    converted.push_back('X');
  }

  return converted;

}

bool validRoman(string str){
  for (int i = 0; i < static_cast<int>(str.length()); i++) { //check through each element for the length of the string
    if (str.at(i) == 'M' || str.at(i) == 'D' || str.at(i) == 'C' || str.at(i) == 'L' || str.at(i) == 'X' || str.at(i) == 'V' || str.at(i) == 'I') { //seperate?
      continue; //if each i element is one of the letters, str is valid roman
    } else {
      return false; //str is not a valid roman numeral
    }

  }
  return true; //after for loop/checking every char
}

bool validArabic(string str){
  for (int j = 0; j < static_cast<int> (str.length()); j++) { //check for each digit cycling through each element of the length
    if (!isdigit(str[j])) { //if the element is not a digit, then it is not valid
      return false;
    }
//      if(stoi(str)>=4999){
//          return false;
//      }
  }
  return true; //element is a digit, it is valid, all elements are arabic
}

int main(){
  ifstream type;
  string filename;
  //int useroption;
  string search;
  int sortchoice;
    
  cout << "Enter file name: ";
cin >> filename;
   

  type.open(filename.c_str(), ios:: in | ios::out | ios::binary);
  string line;
  int counter = 0; //keeps track of line number
  Node * head = nullptr;
  if (!(type)) {
    return 0;
  } else {
    while (!type.eof()) {
        
      counter++; //each time loop, increase line number

      char ch = type.peek();

      Node* newNode = new Node; //create new node
        
      if (ch == ' ') { //space means the line has arabic numerals
        string tmp; // create string to put the arabic numerals into a string
        type >> tmp; //replaces getline (type, tmp); gets the numeral

        if (validArabic(tmp)) {
          int itemp = stoi(tmp); //convert the arabic string to an int
          string r = arabicToRoman(itemp);
//          if(itemp>4999){
//              break;
//          }
            if(!(itemp>4999)){
          newNode -> roman = r;
          newNode -> arabic = itemp;
            }
      }
      }
      else { //when ch is not a space
        string line;
        type >> line; //read string aka getline
        
        if (validRoman(line)) {
            int j = romanToArabic(line);
//            if(j>4999){
//                break;
//            }
            if(!(j>4999)){
            newNode -> roman = line;
            newNode -> arabic = j;
            }
        }
      }
      getline(type, line);
      
      //linking nodes
      if(counter== 1) { // first Node;
          head = newNode;
      } else if(newNode->arabic>0){
          newNode -> next = head;
          head = newNode;
      }
    }
      
      int useroption=0;
      while(useroption != 3) {
          cout << "1. Search\n2. Sort\n3. Exit" << endl;
          cin >> useroption;
          
          if(useroption==1){
              cout<<"Enter numeral to search for: ";
              cin>>search;
              searchfxn(head, search);
          }

          if(useroption==2){
              cout << "1. Sort by Roman numeral\n2. Sort by Arabic numeral"<<endl;
              cin>>sortchoice;

              mergesort(&head,sortchoice);
              if(sortchoice==1){
                  printR(head);
              }
              if(sortchoice==2){
                  printA(head);
              }
              
          }

      }
      if (useroption==3){
          printfxnConsole(head);
      }
  }
    ofstream outfile("numbers.txt");
    printfxn(head, outfile);
    type.close();
}

