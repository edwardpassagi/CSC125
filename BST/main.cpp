/* to use this, 
     - write a form that calls this program with 'action=' in the <form> tag
     - call getPostData() 
     - use getField(string) to access form information 

*/
#include <iostream>
#include "htmlform.h"
#include <stdlib.h>
#include "BST.h"

void printProgram(string);   /// print the program in HTML

using namespace std;

int main()
{
  /// complete the http header
  cout << "Content-type: text/html\n\n";

  /// build a form object
  HTMLform steps;
  steps.getPostData();

  /// Show the debugging
  cout << "Queue Parser Lab startup" << endl;
  steps.debug();

  

  /// the entire programs
  string program = steps.getField("program");
  
  printProgram(program);
  
  //The next line is for you to complete
  //parseProgram(program);

  return 0;
}

void printProgram(string program)
{
  /// a single line
  string line;
  BST story;
  /// for counting the lines
  int count = 0;
  /// where the newline is (for peeling off a line)
  int pos;
  string numstr, strContent;
  int strID;
  program = program+(" \n");
  vector <string> SS, parser;
  while ( string::npos != (pos = program.find("\n") ) )
    {
      line = program.substr(0, pos);    /// before the newline
      program = program.substr(pos+1);  /// after the newline
      /// there might newline characters at the end of line
      if (line[pos] < '0') line.erase(pos-1);
      
      /// here's where you need to process 'line'
      /// this routine just prints it.
      //cout << line.substr(0, line.find("\n"))<< "<br />" << endl; 
      SS.push_back(line.substr(0, line.find("\n")));
      parser.push_back(line.substr(0, line.find(",")));
    }

  for(int i=0 ; i< SS.size()-1 ; i++){
    //cout << parser[i] << "<br />" << endl;
      if (parser[i].size() == 9){
        numstr= parser[i].substr(7,2);
        strID = atoi(numstr.c_str());
        strContent = SS[i].substr(11, line.find("\n"));
      }
      else if ( parser[i].size() == 8){
        numstr= parser[i].substr(7,1);
        strID = atoi(numstr.c_str());
        strContent = SS[i].substr(10, line.find("\n"));
      }
      else{
        cout << "length is more than 2 digits long"<< endl;
        
    }
    story.Insert(strID, strContent);
  }

  if( SS[SS.size()-1] == "INORDER"){
  cout << "<table border='1'>";
  story.inorderPrint();
  cout << "</table>";
  }
  else if( SS[SS.size()-1] == "POSTORDER"){
  cout << "<table border='1'>";
  story.postorderPrint();
  cout << "</table>";
  }
  else if( SS[SS.size()-1] == "PREORDER"){
  cout << "<table border='1'>";
  story.preorderPrint();
  cout << "</table>";
  }
  else{
    cout << "Invalid command: '"<< SS[SS.size()-1]<< "' !"<< " <br/>" << endl;
    cout << "Valid commands are : INORDER, PREORDER, POSTORDER (case sensitive)" << endl;
  }
}
