#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

/* ---- Token Type ---- */

typedef enum
{
    SEMICOLON,
    IF,
    THEN,
    END,
    REPEAT,
    UNTIL,
    IDENTIFIER,
    ASSIGN,
    READ,
    WRITE,
    LESSTHAN,
    EQUAL,
    PLUS,
    MINUS,
    MULT,
    DIV,
    OPENBRACKET,
    CLOSEDBRACKET,
    NUMBER
}TokenType;

/* ---- DFA of Tiny Scanner ---- */

typedef enum{
    START, INCOMMENT ,INNUM , INID, INASSIGN, DONE
}State;


/* ---- Token Struct ---- */

typedef struct {
    TokenType type;
    string tokenvalue;
    string s;
}Token;

 //string line="";


/* ---- Functions Prototypes ---- */

TokenType getToken (string input);
string assignToken (string token,State state);
string readFile(string fileName);
void writeFile(string filename, string tokens);









int main()
{
    string s;
    cout << "Please Enter Input file name \n";
    cin >> s;
    string input =readFile(s);
    getToken (input);
    getch();
    return 0;
}


/* ---- Function to Assign values to tokens Struct ---- */

string assignToken (string token, State state){
    Token T1;
    string line="";
    T1.tokenvalue = token;
    if (token==";"){
        T1.type=SEMICOLON;
        T1.s="SEMICOLON";
    }
    else if (token=="if"){
        T1.type=IF;
        T1.s="IF";
    }
    else if (token=="then"){
        T1.type=THEN;
        T1.s="THEN";
    }
    else if (token=="end"){
        T1.type=END;
        T1.s="END";
    }
    else if (token=="repeat"){
        T1.type=REPEAT;
        T1.s="REPEAT";
    }
    else if (token=="until"){
        T1.type=UNTIL;
        T1.s="UNTIL";
    }
    else if (token==":="){
        T1.type=ASSIGN;
        T1.s="ASSIGN";
    }
    else if (token=="read"){
        T1.type=READ;
        T1.s="READ";
    }
    else if (token=="write"){
        T1.type=WRITE;
        T1.s="WRITE";
    }
    else if (token=="<"){
        T1.type=LESSTHAN;
        T1.s="LESSTHAN";
    }
    else if (token=="="){
        T1.type=EQUAL;
        T1.s="EQUAL";
    }
    else if (token=="+"){
        T1.type=PLUS;
        T1.s="PLUS";
    }
    else if (token=="-"){
        T1.type=MINUS;
        T1.s="MINUS";
    }
    else if (token=="*"){
        T1.type=MULT;
        T1.s="MULT";
    }
    else if (token=="/"){
        T1.type=DIV;
        T1.s="DIV";
    }
    else if (token=="("){
        T1.type=OPENBRACKET;
        T1.s="OPENBRACKET";
    }
    else if (token==")"){
        T1.type=CLOSEDBRACKET;
        T1.s="CLOSEDBRACKET";
    }
    else if (state==INID){
        T1.type=IDENTIFIER;
        T1.s="IDENTIFIER";
    }
    else if (state==INNUM){
        T1.type=NUMBER;
        T1.s="NUMBER";
    }
    line+=token + " , " + T1.s + "\n";
    return line;
}


/* ---- Function to get Token , Will be used by Parser ---- */

TokenType getToken (string input){
    State returnstate ;
    string line="";
    TokenType t;
    int i =0 ;
    while(i<input.size()){
            string token="";
            State state= START;

            /* ---- Ignoring Whitespaces ---- */

            if (input[i]== ' ' || input[i]=='\n' || input[i]=='\r' ){
                state= START;
                i++;
                continue;
            }

            /* ---- Ignoring Comments ---- */

            else if (input[i]=='{'){
                state = INCOMMENT;
                while (state==INCOMMENT){
                            if(input[i]=='}'){
                                    state=START;
                            }
                            i++;
                }
                continue;

            }

             /* ---- get SPECIAL SYMBOLS Tokens ---- */

            else if ( input[i] == ';' || input[i] == '+' || input[i] == '-' ||input[i] == '*' || input[i] == '/' || input[i] == '=' || input[i] ==  '<' || input[i] == '(' || input[i] == ')'){
                state=DONE;
                token+=input[i];
            }

             /* ---- get ASSIGN tokens  ---- */

            else if (input[i]==':'){
                            token+=input[i];
                            state=INASSIGN;
                            if(input[i+1]=='='){
                                token+=input[i+1];
                                state=DONE;
                            }
                            i++;
                        }


            else{

             /* ---- get NUMBERS tokens ---- */

                    if (input[i] >= '0' && input[i] <= '9'){
                        state=INNUM;
                          while (state== INNUM){
                                token += input[i];
                                i++;

                                if (!(input[i] >= '0' && input[i] <= '9')){
                                    i--;
                                    break;
                                    }
                                }
                    }

                    else {

                /* ---- get IDENTIFIER tokens ---- */

                        state=INID;
                        while (state== INID){
                                token += input[i];
                                i++;

                                if (!((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))){

                                    i--;
                                    break;
                                    }
                        }

                    }
            }

            /* ---- String concatenating all Tokens ---- */

            line += assignToken(token,state);
            i++;
        }
        writeFile("output.txt",line);
}


/* ----Read File Function ---- */

string readFile(string fileName) {
    ifstream newfile;
    string out;
    string tp;
    newfile.open(fileName, ios::binary);

    if (newfile.is_open())
    {
        while (getline(newfile, tp))
        {
            out += tp + "\n";
        }
        newfile.close();
    }
    return out;
}

/* ----Write File Function ---- */

void writeFile(string filename, string tokens)
{
    ofstream file;
    file.open(filename, ios::binary);
    file << tokens << endl;
    file.close();

}



