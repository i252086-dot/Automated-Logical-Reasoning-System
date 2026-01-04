#include<iostream>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;
//for infix to postfix
char stack[100]; 
int top = -1;
//for expression evaluator
int stackValue[100];
int valueTop=-1;
bool And(bool a,bool b)
{
	return a&&b;
}
bool Or(bool a,bool b)
{
	return a||b;
}
bool Not(bool a)
{
	return !a;
}
bool Implication(bool a,bool b)
{
	return !a || b;
}
bool biconditional(bool a,bool b)
{
	return a == b;
}
//for precedence of operator
int Precedence(char opr)
{
	if(opr=='!') return 4;
	else if(opr=='&') return 3;
	else if(opr=='|') return 2;
	else if(opr=='>') return 1;
	else if(opr=='=') return 1;
	return 0;
}
//Checking character is operator
bool Operator(char a) 
{
    return (a == '&' || a == '|' || a == '!' || a == '>' || a == '=');
}
//Checking character is variable
bool Variable(char a) 
{
    return (a >= 'A' && a <= 'Z');
}
int tokenization(char input[],char token[])
{
	
int count=0;
for(int i=0;input[i]!='\0';i++)
{
char a = input[i];
//skipping space
if(input[i]==' ')
	continue;
//If valid character add to token array
	if(Variable(a)||Operator(a)||a=='('||a==')')
	{
		token[count]=a;
     	count++;
	}
	else
	{
		cout<<"invalid character"<<a<<"Enter valid one."<<endl;
		return -1;
	}

}
    token[count]='\0';
    return count;	
}
//Helpers of Infix to postfix stack function
char pop()
{
  return stack[top--];
}
char peak()
{
  return stack[top];	
}
void pushTop(char a)
{
  stack[++top]=a;	
}
void infixToPostfix(char token[],char postfix[])
{
top=-1;
int j=0;
  for(int i=0;token[i]!='\0';i++)
    {
	    char a=token[i];
//if variable
	if(Variable(a))
	{
		postfix[j]=a;
		j++;
	}
//If its  '(' 
    else if(a=='(')
    {
        pushTop(a);	
    }
    else if(a==')')
    {
	    while(top!=-1&&peak()!='(')
	    {
		    postfix[j]=pop();
		    j++;
	    }
//stops when we found the '('.
	    pop();
//throwing away as we dont need '(' in output
    }
    else if(Operator(a))
    {
	while(top!=-1&&Precedence(peak()) >= Precedence(a))
        {
	    if (peak() == '(') 
	    break; 
	    postfix[j] = pop();
	    j++;
        }
    pushTop(a);
    }
    else 
    {
    	;
	}
}
    while(top!=-1)
    {
        postfix[j]=pop();
	    j++;	   
	}
//Adding null pointer to make it valid string
postfix[j] = '\0';	
}
//Helpers of  Evaluater
// Helper  1 to Add number to stack
void pushValue(int x)
{
 valueTop++;
 stackValue[valueTop]=x;	
}
// Helper 2 to Remove number from stack
int popValue()
{
int x=stackValue[valueTop];	
valueTop--;
return x;
}
bool Evaluator(char postfix[], char var[], int values[], int varCount)
{
for (int i = 0; postfix[i] != '\0'; i++)
{
        char ch = postfix[i];
//if it is variable find value (0 or 1)
    if (Variable(ch))
    {
        for(int k = 0; k < varCount; k++)
        {
            if(var[k] == ch)
            {
                pushValue(values[k]);
                break; 
            }
        }
    }
// 2. If it is an Operator, do the math
    else if (Operator(ch))
    {
// NOT (!) uses 1 number
    if (ch == '!') 
    {
    int a = popValue();
    pushValue(Not(a));
    }
// Others uses 2 numbers
    else 
    {
    int b = popValue(); 
    int a = popValue(); 
        if (ch == '&')     
		pushValue(And(a, b));
        else if (ch == '|') 
		pushValue(Or(a, b));
        else if (ch == '>')  
		pushValue(Implication(a, b));
        else if (ch == '=')  
		pushValue(biconditional(a, b));
    }
    }
}
// Final answer will be on top of stack
return popValue();
}
void saveResult(char text[]) 
{
    ofstream file;
    file.open("results.txt", ios::app);
    if(file.is_open()) 
	{
    file <<text<< endl;
    file.close();
    cout << "[Saved to results.txt]\n";
    }
}
//helper to save reult
void save(char* res) 
{
    cout << "Do you want to save results? (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') 
	{
    saveResult(res);
    }
}
int main()
{
	int choice;
    char exp[100];
    cout << "===========================================\n";
    cout << "  Automated Logical Reasoning System (ALRS)\n";
    cout << "===========================================\n";
    cout << "\nOperators supported:\n";
    cout << "  & = AND\n";
    cout << "  | = OR\n";
    cout << "  ! = NOT\n";
    cout << "  > = IMPLIES\n";
    cout << "  = = EQUIVALENT\n";
    cout << "===========================================\n";
do 
{
    cout << "\n--- MENU ---\n";
    cout << "1. Input and Parse Expression (Truth Table)\n";
    cout << "2. Validate Argument\n";
    cout << "3. Check Equivalence\n";
    cout << "4. Reasoning Chain\n";
    cout << "5. View Previous Saved Results\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    if(choice==1)
    {
    char clean[100],postfix[100];
	cout << "\n--- Truth Table Generator ---\n";
    cout << "Enter Expression: ";
    cin.getline(exp, 100);
//tokenizing 
    int countToken=tokenization(exp,clean);
    if(countToken==-1)
    continue;
//parsing the expression
    infixToPostfix(clean,postfix);
    cout<<"postfix form is: "<<postfix;
//Finding unique variables
    char variable[5];
    int variableCount=0;
    bool seen[100]={false};
    for(int i=0;clean[i]!='\0';i++)
    {
    	char c=clean[i];
    	if(Variable(c)&&seen[c]==false)
    	{
    		variable[variableCount]=c;
    		variableCount++;
    		seen[c] = true;
		}
	}
//generating truth table
    int tRows=pow(2,variableCount);
    int currentValues[5];
//Always shows truth table
	cout << "\nTruth Table:\n";
//for printing table headers
    for(int i = 0; i < variableCount; i++) 
		cout << variable[i] << " | ";
    cout << "Result";
    cout <<"\n----------------------------"<<endl;
    for(int i=0;i<tRows;i++)
	{
		int temp=i;
	    for(int j=variableCount-1;j>=0;j--)
	    {
	    currentValues[j]=temp%2;
	    temp/=2;
	    }
	    for(int k = 0; k < variableCount; k++) 
		{
        cout << currentValues[k] << " | ";
		}
//calling Evaluator
	bool result=Evaluator(postfix, variable, currentValues, variableCount);
//printing Result
    cout << "  " << result << endl;	
	}  	
    cout <<"\n----------------------------"<<endl;	 
//open the file in truth table
    cout <<"Do you want to save results? (Y/N): ";
	char choiceS;
	cin >> choiceS;
	if(choiceS== 'Y' || choiceS== 'y')
	{
    ofstream file("results.txt", ios::app); 
    if(file.is_open())
    {
    file<< "\nTruth Table:\n";
//for printing table headers
    for(int i = 0; i <variableCount; i++) 
		file<< variable[i] << " | ";
		
    file<< "Result";
    file<<"\n----------------------------"<<endl;
    for(int i=0;i<tRows;i++)
	{
		int temp=i;
	    for(int j=variableCount-1;j>=0;j--)
	    {
	    currentValues[j]=temp%2;
	    temp/=2;
	    }
	    for(int k = 0; k < variableCount; k++) 
		{
        file << currentValues[k] << " | ";
		}
//calling Evaluator
	bool result=Evaluator(postfix, variable, currentValues, variableCount);
//printing Result
file << "  " << result << endl;	
	}  	
    file << "----------------------------\n";
    file.close();
    cout<< "Full Table is saved to results.txt"<<endl;
    }
    }
    }
	else if(choice==2)
	{
//Validating argument
    cout << "\n--- Argument Validator ---\n";
    char premises[5][100];
	char conclusion[100];
	char postConclusion[100];
	char clean[100];
	char variable[5];
	int variableCount = 0;
	bool seen[100] = {false};
	int count;
	int tRows=pow(2,variableCount);
    int currentValues[5];
    bool valid=true;
	cout << "Number of Premises: ";
	cin >> count;
	cin.ignore();
//input premises
	for(int i = 0; i < count; i++)
	{
	 cout<<"premise:"<<i+1<<endl;
	 char rawP[100];
	 cout<<"input";
    cin.getline(rawP, 100);
	 tokenization(rawP, clean);
	 infixToPostfix(clean, premises[i]);
// Finding variables
    for(int j=0;clean[j]!='\0';j++)
    {
    	char c=clean[j];
    	if(Variable(c)&&seen[c]==false)
    	{
    		variable[variableCount]=c;
    		variableCount++;
    		seen[c] = true;
		}
	}
	}
//input conclusion
	cout<<"Conclusion:"<<endl;
	char rawC[100];
	cout<<"input";
    cin.getline(rawC, 100);
	tokenization(rawC, clean);
	infixToPostfix(clean, postConclusion);
// Finding variables
    for(int k=0;clean[k]!='\0';k++)
    {
    	char c=clean[k];
    	if(Variable(c)&&seen[c]==false)
    	{
    		variable[variableCount]=c;
    		variableCount++;
    		seen[c] = true;
		}
	}
//validating loop
    cout << "\nChecking...\n";
    for(int i=0;i<tRows;i++)
	{
		int temp=i;
	    for(int j=variableCount-1;j>=0;j--)
	    {
	    currentValues[j]=temp%2;
	    temp/=2;
	    }
	
//checking premises
	bool allPremises=true;
    for(int k=0;k<count;k++)
    {
    if(Evaluator(premises[k], variable, currentValues, variableCount) == 0) 
	{
	allPremises= false;
	break; 
	}
	}
//Checking conclusion
if(allPremises==true)
{
if(Evaluator(postConclusion, variable, currentValues, variableCount) == 0) 
	{
	valid= false;
	cout << "Invalid at row " << i << endl;
	break; 
	}	
}
    }
    if(valid)
    {
    cout<<"Result:Valid Argument"<<endl;
    save((char*)"Argument Validator: Valid");
	}
    else
    {
    cout<<"Result:Invalid Argument"<<endl;
	save((char*)"Argument Validator: Invalid");
	}	
	}
	else if(choice==3)
	{
//checking Equivalence
    cout << "\n--- Equivalence Checker ---\n";
    char exp1[100], exp2[100];
    char clean1[100], post1[100];
    char clean2[100], post2[100];
//Expression 1
    cout << "Enter Expression 1: ";
    cin.getline(exp1, 100);
    tokenization(exp1, clean1);
    infixToPostfix(clean1, post1);
//Expression 2
	cout << "Enter Expression 2: ";
    cin.getline(exp2, 100);
    tokenization(exp2, clean2);
    infixToPostfix(clean2, post2);	
    bool equivalent=true;
    char variable[5];
    int variableCount=0;
    bool seen[100]={false};
    int rows = pow(2, variableCount);
    int currentValues[5];
//Scanning First Expression
for(int i=0;clean1[i]!='\0';i++)
    {
    	char c=clean1[i];
    	if(Variable(c)&&seen[c]==false)
    	{
    		variable[variableCount]=c;
    		variableCount++;
    		seen[c] = true;
		}
	}
//Scanning Second Expression
for(int i=0;clean2[i]!='\0';i++)
    {
    	char c=clean2[i];
    	if(Variable(c)&&seen[c]==false)
    	{
    		variable[variableCount]=c;
    		variableCount++;
    		seen[c] = true;
		}
	}
//comparing both Expressions
    for(int i=0;i<rows;i++)
    {
		int temp=i;
	    for(int j=variableCount-1;j>=0;j--)
	    {
	    currentValues[j]=temp%2;
	    temp/=2;
	    }

	    if(Evaluator(post1, variable, currentValues, variableCount) != Evaluator(post2,variable,currentValues,variableCount))
	    {
	    equivalent=false;
	    cout<<"Rows are mismatching at location"<<i<<endl;
		}
	}
//result
    if(equivalent)
    {
    cout<<"Result:Equivalent!Identical logic."<<endl;
    save((char*)"Equivalence Check: Equivalent");
	}
    else
    {
    cout<<"Result:Not Equivalent"<<endl;
    save((char*)"Equivalence Check: Not Equivalent");	
	}
	}
	
	else if(choice==4)
	{
//reasoning chain
        cout << "\n--- Reasoning Chain ---\n";
		cout << "Checks if premise to Result is valid logic.";
		char P[50], Q[50];
		cout << "Enter Premise Variable: ";
		cin.getline(P, 50);
		cout << "Enter Result Variable: ";
		cin.getline(Q, 50);	
// logic is for((P>Q)&P)>Q
		char logic[200] = "((";
		strcat(logic, P); 
		strcat(logic, ">"); 
		strcat(logic, Q); 
// (P>Q)
		strcat(logic, ")&");
		strcat(logic, P); 
// & P
		strcat(logic, ")>");
		strcat(logic, Q); 
// > Q
	    cout << "Validating Chain: " << logic << endl;
//validating loop
    char clean[100], post[100];
	tokenization(logic, clean);
	infixToPostfix(clean, post);
	char variable[5];
	int variableCount = 0;
	bool seen[100] = {false};
// Finding variables
    for(int j=0;clean[j]!='\0';j++)
    {
    	char c=clean[j];
    	if(Variable(c)&&seen[c]==false)
    	{
    		variable[variableCount]=c;
    		variableCount++;
    		seen[c] = true;
		}
	}
//checking validity now
    int tRows=pow(2,variableCount);
    int currentValues[5];
    bool valid=true;
    for(int i=0;i<tRows;i++)
	{
		int temp=i;
	    for(int j=variableCount-1;j>=0;j--)
	    {
	    currentValues[j]=temp%2;
	    temp/=2;
	    }
//checking chain
	    if(Evaluator(post, variable, currentValues, variableCount) == 0) 
	   {
	    valid= false;
	    break; 
	   }
    }
    if(valid)
    {
    cout<<"Result:Valid Reasoning Chain!"<<endl;
    save((char*)"Reasoning Chain: Valid");
	}
    else
    {
    cout<<"Result:Invalid Reasoning Chain!"<<endl;
    save((char*)"Reasoning Chain: Invalid");	
	}
    }
	else if(choice==5)
	{
//viewing previous saved results
    cout << "\n--- Saved Results ---\n";
// Tries to open the file
    ifstream file("results.txt");
//checks if file is actually open or not?
    if(file.is_open()) 
	{
        char line[100];
        while(file.getline(line, 100)) 
	    {
        cout <<line<< endl;
        }
    file.close();
    } 
	else 
	{
     cout << "No saved file found.\n";
    }
    }	
	else if(choice==6)
	{
//exit	
    cout << "Exiting...\n";
	}
	else
	{
	cout << "\nInvalid choice! Please try again." << endl;
	}
}
while(choice!=6);
	return 0;
}
