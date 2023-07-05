# include <iostream>
# include <fstream>
# include <bits/stdc++.h>
# include <string.h>

# define MAX 10
using namespace std;
int k=0;
ofstream Dictionary;

string cols[MAX][2];
void create(string q);
void insert_record(string q);
void update_record_with_where(string q);
void update_record(string q);
void delete_record(string q);
void describe(string q);
void truncate(string q, bool del);
void drop(string q);
void select(string q);
void select_with_where(string q);
int checktable(string t);
bool checkDataType(string data, string dataType);
void help();

int main() {

    string query = "", temp;
    int i = 0;


    do {
        i = 0;
        temp = "";

        cout << "\n Query > " ;
        getline(cin, query);

        transform(query.begin(), query.end(), query.begin(), ::tolower);
        //cout << query << endl;

        if(query[i] == 'h') {
            while(query[i] != ';') {
               temp += query[i];
               i++;
            }
        }
        else {
            while(query[i] != 32) {
               temp += query[i];
               i++;
            }
        }
        //cout << temp << endl;
        string q1 = query.substr(i, query.length());

        if(temp == "create") {
            create(q1);
        }
        else if(temp == "insert") 
        {
            insert_record(q1);
        }
        else if(temp == "update") 
        {
            int pos = 0;
            if(q1.find("where", pos) != string::npos) 
            {
                update_record_with_where(q1);
            }
            else
            {
                update_record(q1);
            }
        }
        else if(temp == "delete") {
            int pos = 0;
            if(q1.find("where", pos) != string::npos) 
            {    
                delete_record(q1);
            }
            else
            {
                string str = "";
                
                for (int i = q1.size() - 1; q1[i] != ' '; i--)
                    str = q1[i]+ str;
                truncate("table "+str, true);
            }
        }
        else if(temp == "desc" || temp == "describe") {

            describe(q1);
        }
        else if(temp=="trunc" || temp=="truncate")
        {
            truncate(q1, false);
        }
        else if(temp=="drop")
        {
            drop(q1);
        }
        else if(temp=="select")
        {
            int pos = 0;
            if(q1.find("where", pos) != string::npos) 
            {    
                select_with_where(q1);
            }
            else
            {
                select(q1);
            }
        }
        else if(temp == "help")
        {
            help();
        }
        else if(temp == "exit") {
            exit(0);
        }
        else {
            cout << "\n ERR: Please enter valid statement..! " ;
        }

    } while(1);

    return 0;
}

void help()
{
    string command;

    do {
        cout << "\n Command : " ;
        cin >> command;
        cout << endl << "    " ;
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        if(command == "create")
        {
            cout << "CREATE TABLE table_name (column1 datatype, column2 datatype, column3 datatype, ....);"<<endl;
        }
        else if(command == "truncate" || command == "trunc")
        {
            cout << "TRUNCATE TABLE table_name;"<<endl;
        }
        else if(command == "drop")
        {
             cout << "DROP TABLE table_name;"<<endl;
        }
        else if(command == "delete")
        {
             cout << "DELETE FROM table_name WHERE condition;"<<endl;
        }
        else if(command == "update")
        {
             cout << "UPDATE table_name SET column1 = value1, column2 = value2, ... WHERE condition;"<<endl;
        }
        else if(command == "describe" || command == "desc")
        {
             cout << "DESCRIBE table_name;"<<endl;
        }
        else if(command == "insert")
        {
             cout << "INSERT INTO table_name (column1, column2, column3, ...) VALUES (value1, value2, value3, ...);"<<endl;
        }
        else if(command == "select")
        {
           cout << "" << endl ;
        }
        else if(command == "help")
        {
            cout << "YOU ARE IN HELP COMMAND EXECUTION iTSELF.." << endl ;
        }
        else if(command == "exit") {
            break;
        }
        else {
            cout << " Please enter valid command.. " << endl ;
        }

    }while(1);
}

void select(string q1)
{
    ifstream infile;
    int i=1;
    char data[100];
    string tableName="";

    cout << endl ;
    //* from 
    if(q1[i]=='*')
    {
        i+=2;

        while(q1[i]!=' ')
        {
           i++;
        }
        i++;

        // while(q1[i]!=' ')
        // {
        //    i++;
        // }
        // i++;
        while(q1[i]!=';')
        {
           tableName+=q1[i];
           i++;
        }
        
        if(checktable(tableName))
        {
            infile.open(tableName + ".txt", ios::in);

        while(!infile.eof())
            {
                infile.getline(data,100);
                for(int i=0;data[i]!='\0';i++)
                {
                    if(data[i]=='|')
                    {
                        cout<<"\t";
                    }
                    else
                    {
                        cout<<data[i];
                    }
                }
            cout<<endl;
    
                    //cout << data <<endl ;
                
            }
            infile.close();
        }
        else
        {
            cout<<"\n Table does not exists..! "<<endl;
        }
    }
}

void select_with_where(string q1)
{
    string tableName="";
    vector<vector<string>> tableData;

    char data[100];
    fstream tableFileToRead;
    int i = 1;
    if(q1[i]=='*')
    {
        i++;

        while(q1[i]!=' ')
        {
           i++;
        }
        i++;

        while(q1[i]!=' ')
        {
           i++;
        }
        i++;

        while(q1[i]!=' ')
        {
           tableName+=q1[i];
           i++;
        }
        i++;

        while(q1[i] != ' ')
        {
            i++;
        }
        i++;
        
        string colName = "";
        string val = "";

        while(q1[i]!='=')
        {
            colName+=q1[i];
            i++;
        }
        i+=2;
        while (q1[i] != '"')
        {
            val+=q1[i];
            i++;
        }
        
        tableFileToRead.open(tableName+".txt", ios_base::in);

        string tmpString = "";
        vector<string> row;
        while(!tableFileToRead.eof())
        {
            tableFileToRead.getline(data, 100);

            for(int itr=0;data[itr]!='\0';itr++)
            {
            	if(data[itr]=='|')
            	{
                    row.push_back(tmpString);
                    tmpString="";
				}
				else
				{
					tmpString+=data[itr];
				}
			}
            tableData.push_back(row);
            row.clear();
        }
        int colFlag = -1;
        for(int tbItr = 0; tbItr < tableData[0].size(); tbItr++)
        {
            if(tableData[0][tbItr] == colName)
            {
                colFlag = tbItr;
                break;
            }
        }

        if(colFlag == -1)
        {
            cout<<"Column does not exist..."<<endl;
            return;
        }
        for(int tbItr = 0; tbItr < tableData[0].size(); tbItr++)
        {
            cout<<tableData[0][tbItr]<<"\t";
        }
        cout<<endl;
        for(int tbItr = 1; tbItr < tableData.size() - 1; tbItr++)
        {
            if(tableData[tbItr][colFlag] == val)
            {
                for(int j =0; j < tableData[0].size(); j++)
                {
                    cout<<tableData[tbItr][j]<<"\t";
                }
                cout<<endl;
            }    
        }
        
        tableFileToRead.close();
    }
}
void describe(string q1)
{
    int i=1;
    int flag=0;
    char data[100];
    ifstream infile;
    string tableName;

    while(q1[i]!=';')
    {
        tableName+=q1[i];
        i++;

    }

    if(checktable(tableName))
     {
        //cout<<tableName;
        string temp="Dict";
        char ch;
        string tb_nm, col_nm, col_type;
        infile.open(temp + ".txt", ios::in);
        int i1,k,j,m;

        while(!infile.eof())
        {
            infile.getline(data,100);

            for( i1=0; data[i1]!=35 ;i1++)
            {
                tb_nm+=data[i1];
            }
            i1++;

            if(tb_nm == tableName)
            {
                //cout << "\n " << data << endl ;
                
                cout<<"Table Name: ";
			    for(int i = 0; data[i] != ';'; i++)
			    {
			        if(data[i] == '#')
			        {
			            cout<<"\n"<<"Column Name\t\t"<< "Data Type"<<endl;
			        }
			        else if( data[i] == '|')
			            cout<<endl;
			        else if( data[i] == '-')
			            cout<<"\t\t\t";
			        else
			            cout<<data[i];
			    }
            }
            tb_nm = "";
        }
        infile.close();
    }
    else{
        cout<<"\n Table does not exists..! "<<endl;
   }
}
void drop(string q)
{
  int i=1;
  string tableName;

    while(q[i] != 32) {
       i++;
       //cout << i << endl;
    }
    i++;

    //cout << i ;
    while(q[i] != ';') {
       tableName += q[i];
       i++;
    }
    i++;

    string temp1 = tableName + ".txt";

    int n = temp1.length();

    // declaring character array
    char char_array[n + 1];

    strcpy(char_array, temp1.c_str());

    int result = remove(char_array);

    if (result == 0)
    {
        ifstream infile;
        ofstream outfile;
        string temp = "temp1";
        char data[100];

        infile.open("Dict.txt", ios::in);
        outfile.open(temp + ".txt", ios::out);

        while(!infile.eof()) {

            memset(data, 0, sizeof(data));
            infile.getline(data,100);
           // cout << data << endl;
            string t;
            int i = 0 ;

            while(data[i] != 35) {
               t += data[i];
               i++;
            }
          //  cout << t << endl ;
            if(tableName != t) {
                outfile << data ;
            }
        }
        outfile.close();
        infile.close();

        infile.open(temp + ".txt", ios::in);
        outfile.open("Dict.txt", ios::out);

        while(!infile.eof()) {

            memset(data, 0, sizeof(data));
            infile.getline(data,100);
            outfile << data ;
        }
        outfile.close();
        infile.close();

        cout << "\n Table drop Successfully..! "<< endl;
    }
}

void truncate(string q , bool del)
{
    int i=1;
    char data[100];
    ofstream outfile;
    ifstream infile;
    string temp, tableName,temp2;
    temp2="temp";


    while(q[i] != 32) {
       i++;
       //cout << i << endl;
    }
    i++;

    //cout << i ;
    while(q[i] != ';') {
       tableName += q[i];
       i++;

    }
    i++;

    if(checktable(tableName))
    {

        infile.open(tableName + ".txt",ios::in);
        outfile.open(temp2 + ".txt",ios::out);

        infile.getline(data,100);
        outfile<<data;

        outfile.close();
        infile.close();
        infile.open(temp2 + ".txt",ios::in);
        outfile.open(tableName + ".txt",ios::out);
        infile.getline(data,100);
        outfile<<data<<endl;


        del ? cout<<"\n Deleted records successfully..! " << endl : cout<<"\n Truncated successfully..! " << endl;

    }
    else
    {
        cout<<"\n Table does not exists..! " <<endl;
    }
}

int checktable(string tblName)
{
    ifstream f;

    char data[100];
    int flag=0;

    f.open("Dict.txt", ios::in);
    int cnt = 1;
     while(!f.eof())
     {
        memset(data, 0, sizeof(data));
        f.getline(data, 100);
        string tableName;
        int i = 0 ;

        while(data[i] != 35) {
           tableName += data[i];
           i++;
        }

         if(tblName == tableName)
         {

             flag=1;
             break;
         }
         cnt++;
     }
     if(flag==0)
     {
         return 0;
     }
     else{
        return cnt;
     }

}

void create(string q)
{
    /*
    create table student(id int, name varchar)
    create table employee(id int, mob int, name varchar)
    */
    int i = 1, k = 0;
    string temp, tableName, columnName, dataType;

    string file = "Dict";

    while(q[i] != 32) {
       i++;
       //cout << i << endl;
    }
    i++;
    //cout << i ;
    while(q[i] != 40) {
       tableName += q[i];
       i++;
    }
    i++;

    //Exception - Check whether already table exist or not with similar name..
    //cout << "\n Table Name - " << tableName << endl;

    while(q[i] != 41) {
        columnName = "";
        dataType = "";

        while(q[i] != 32) {
            columnName += q[i];
            i++;
        }
        i++;
        cols[k][0] = columnName;

        while(q[i] != 44) {
            if(q[i] == 41) {
                break;
            }
            dataType += q[i];
            i++;
        }
        cols[k][1] = dataType;
        //cout << " col = " << cols[k][0] << " "<< cols[k][1] << endl ;
        k++;

        if((q[i] != 41)) {
            i += 2;
        }
        else {
            break;
        }
    }

    int flag=0;
    ofstream outfile;
    char data[100];

    ifstream dict;
    dict.open(file + ".txt", ios::out);

    while(!dict.eof())
    {
         dict.getline(data,100);

        string temp = "";
        int ii = 0;

        while(data[ii] != 35) {

            temp += data[ii];
            //cout << " \n temp - " << temp << endl ;
            ii++;
        }

         if(tableName == temp)
         {
             cout << "\n Table is already exists..! " << endl;
             flag=1;
             break;
         }
    }
    dict.close();

    Dictionary.open(file + ".txt", ios::app);

    if(flag==0)
    {
        outfile.open(tableName + ".txt");

        Dictionary << tableName << "#" ;

        for(i=0;i<k;i++)
        {
            Dictionary<<cols[i][0]<<"-";
            Dictionary<<cols[i][1]<<"|";
        }
        Dictionary << ";" << "\n" ;
        Dictionary.close();

        for( i = 0 ; i < k ; i++) {
            outfile << cols[i][0] << "|";
        }

        outfile << "\n" ;

        cout << "\n " << tableName<<" : Table Created Successfully..! " << endl;
     }

    outfile.close();
}

void insert_record(string q)
{
    /*
    -- insert into stud values(111, ABC, 1234567890);
    */
    int i = 1;
    string temp, tableName, id, temp2;
    char data[100];
    int ids[100], no, no1, flag = 0;

    while(q[i] != 32) {
       i++;
    }
    i++;

    while(q[i] != 32) {
       tableName += q[i];
       i++;
    }
    i++;


    while(q[i] != 40) {
        //To skip 'values'
       i++;
    }
    i++;
    int cnt = checktable(tableName);
    // cout<<cnt<<endl;
    if(cnt > 0)
    {
        fstream dictFileToRead;
        dictFileToRead.open("Dict.txt", ios_base::in);

        while(cnt>0)
        {
            cnt--;
            dictFileToRead.getline(data, 100);
        }
        // cout<<cnt<<endl;
    
        string tbStructure = data;
        int j = i, k = 0;
        // cout<<"TB structure " << data;
        while(q[j] != ')' && q[j] != ';')
        {
            string dType = "";
            string val = "";

            //extract data type from var tbStructure
            
            while(tbStructure[k] != '-' && tbStructure[k] != ';')
            {
                // cout<<"working 1"<< dType << " " << k<<endl;
                k++;
            }
            tbStructure[k] == ';' ? k : k++;

            while(tbStructure[k] != '|' && tbStructure[k] != ';')
            {
                // cout<<"working 2"<< dType << " " << k<<endl;
                dType+=tbStructure[k];
                k++;
            }
            k++;
            // tbStructure[k] == ';' ? k : k++;

            while(q[j] != ',' && q[j] != ')' && q[j] != ';')
            {
                
                // cout<<"working 3 "<<val<<endl;
                val+=q[j];
                j++;
            }
            
            // cout<<val << " "<<dType<<endl;
            if(!checkDataType(val, dType))
            {
                cout<<"Incorrect data type for value: " << val << endl << "Expected Data type: "<< dType<<endl;
                return;
            }
            j++;
        }
        
        dictFileToRead.close();
        ofstream outfile;
        outfile.open(tableName + ".txt", ios::app);
        

        /* while(q[i] != 41) {
        temp+=q[i];
        i++;
        } */

        /*int t = i;

        while(q[t] != 44) {
            id += q[t];
            t++;
        }
        t++;

        no = stoi(id);

        //cout << "\n id = " << no << endl ;
        int k = 0;

        ifstream ifs;
        ifs.open(tableName + ".txt", ios::in);
        ifs.getline(data,100);

        while(!ifs.eof())
        {
            ifs.getline(data,100);

            int j = 0;
            temp2 = "";

            while(data[j] != 124) {
                temp2 += data[j];
                j++;
            }
            //cout << endl << temp2 << endl ;

            no1 = stoi(temp2);
            ids[k] = no1;
            //cout << " | " << ids[k] << " = " << k ;
            k++;
        }

        ifs.close();

        for(int n = 0 ; n < k ; n++) {
            if(no == ids[n]) {
                flag = 1;
                break;
            }
        }

        if(flag == 1) {
            cout << "\n Primary Key Constraint Violated..! " << endl ;
        }
        else {*/
            while(q[i] != 41) {

                while(q[i] != 44) {

                    if(q[i] == 41) {
                        break;
                    }
                        temp += q[i];
                        i++;
                    }

                    outfile << temp << "|" ;
                    temp="";

                    if((q[i] != 41)) {
                        i += 2;
                    }
                    else {
                        break;
                    }
            }

            outfile<<temp;
            outfile << "\n" ;
            cout << tableName << " : Record inserted succesfully..!" << endl;
            outfile.close();
        //}
    }
    else
    {
        cout << "\n Table is not exists..! " << endl;
    }
}
void update_record(string q)
{
    
    string  tableName, colName, value, t = "";
    
    int i=1;
    ofstream outfile;
    ifstream infile;
    
    char data[100];
    
    string temp2;
    temp2="temp";

    while(q[i] != ' ') {
       tableName += q[i];
       i++;
    }
    i++;

    
    if(checktable(tableName))
    {
        while(q[i] != ' ') {

           i++;
        }
        i++;

        while(q[i] != '=') {

          colName += q[i];
          i++;
        }
        i += 2;

        while(q[i] != 34) {  // check for "

          value += q[i];
          i++;
        }
    }
    else
    {
        cout<<"\n Table does not exists..! "<<endl;
        return;
    }

    ifstream is;
    string temp;

    memset(data, 0, sizeof(data));

    is.open(tableName + ".txt", ios::in);
    is.getline(data, 100);
    int ii = 0, flag = 0, colPosition = 0;

    while(data[ii] != '\0') { //check if column is there or not
        temp = "" ;
        
        while(data[ii] != '|') {
            temp += data[ii];
            ii++;
        }

        colPosition++;
        ii++;

        if(temp == colName) {
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        cout << "\n Column name specified doesn't exist..! " << endl ;
        return;
    }

    flag = 0;
    ii = 0;

    ofstream tempFileToAppend;
    tempFileToAppend.open("temp.txt", ios_base::out);
    tempFileToAppend.close();
    tempFileToAppend.open("temp.txt", ios_base::app);

    fstream tableFileToRead;
    tableFileToRead.open(tableName+".txt", ios_base::in);

    tableFileToRead.getline(data, 100);

    string tempData = "";
    tempData+=data;
    tempFileToAppend << tempData<<endl;
    while (!tableFileToRead.eof()) 
    {
        tempData = "";
        i = 0;
        memset(data, 0, sizeof(data));
        
        tableFileToRead.getline(data, 100);
        int itr = 0;
        bool flag = false;
        while(data[i] != '\0')
        {
            if(data[i] == '|') itr++;
            tempFileToAppend<<data[i];

            if(itr == colPosition - 1 && !flag)
            {
                flag = true;
                tempFileToAppend<<value<<"|";
                i++;
                while (data[i]!='|')
                {
                    i++;
                }
            }
            i++;
        }
        tempFileToAppend<<endl;
	}
    tempFileToAppend.close();
    tableFileToRead.close();

    
    fstream tempFileToRead;
    ofstream tableFileToWrite;

    tempFileToRead.open("temp.txt", ios_base::in);
    tableFileToWrite.open(tableName+".txt", ios_base::out);
    char c;
    while (tempFileToRead.get(c))
    {
        tableFileToWrite << c;
    }

    tempFileToRead.close();
    tableFileToWrite.close();

    cout << "\n Record Successfully Updated..! " << endl ;
    //     is.clear();
    //     is.seekg(0);
    //     memset(data, 0, sizeof(data));
    //     is.getline(data,100);
        
    //     ofstream ofs;
    //     ofs.open("temp.txt", ios::out);

    //     string tempUpdate = "";
    //     tempUpdate+=data;
    //     while(!is.eof()) 
    //     {
    //         memset(data, 0, sizeof(data));
    //         is.getline(data,100);
    //         int iterateForColPosition = 0;
    //         int itr = 0;

    //         while (iterateForColPosition != colPosition)
    //         {
    //             tempUpdate+= data[itr];
    //             itr++;
    //             if(data[itr] == '|')
    //             {
    //                 iterateForColPosition++;
    //             }
    //         }
    //         tempUpdate+=value;
    //         while(data[itr] != '|')
    //             itr++;
    //         tempUpdate+='|';
    //         itr++;
    //         while(data[itr] != '|')
    //         {
    //             tempUpdate+=data[itr];
    //             itr++;
    //         }
    //         tempUpdate+='|';
    //         tempUpdate+="\n";
    //     }
    //     ofs << tempUpdate;
    //     ofs.close();
    //     is.close();

    //     // Getting back data
    //     is.open("temp.txt", ios::in);
    //     ofs.open(tableName + ".txt", ios::out);

    //     char c;
    //     while (is.get(c))
    //     {
    //         ofs << c;
    //     }
    //     ofs.close();
    //     is.close();

    //     cout << "\n Record Successfully Updated..! " << endl ;
    //     return;
    // }
}

void update_record_with_where(string q)
{

    string  tableName, colName, value, newColName, newValue, t = "";
    int i=1;
    ofstream outfile;
    ifstream infile;
    char data[100];
    string temp2;
    temp2="temp";
    bool whereClause = false;
    //cout << "Query - " << q << endl ;
    //update stud set phone_no="784526390" where name="GARUAV";
    //update stud set name="Nehali" where id="333";
    //update stud set name="GAURAV" where id="222";

    while(q[i] != 32) {
       tableName += q[i];
       i++;
    }
    i++;

 //   cout << "\n " <<  tableName << endl ;

    if(checktable(tableName))
    {
        while(q[i] != ' ') {

           i++;
        }
        i++;

        while(q[i] != '=') {

          newColName += q[i];
          i++;
        }
        i += 2;

        while(q[i] != 34) {  // check for "

          newValue += q[i];
          i++;
        }
        i++;
        cout<< q[i] << whereClause<<endl;

        i += 2;
        while(q[i] != ' ') {

           i++;
        }
        i++;

     //   cout << "\n " << newColName << endl ;
     //   cout << " " <<  newValue << endl ;

        while(q[i] != '=') { //get column name

          colName += q[i];
          i++;
        }
        i += 2;

        while(q[i] != 34) { // get value

          value += q[i];
          i++;
        }
        i++;

      //  cout << "\n " << colName << endl ;
      //  cout << " " <<  value << endl ;
    }
    else
    {
        cout<<"\n Table does not exists..! "<<endl;
        return;
    }

    ifstream is;
    int line_no = 1, count1 = 0, count2 = 0, ii = 0, flag = 0;
    string temp;

    memset(data, 0, sizeof(data));

    is.open(tableName + ".txt", ios::in);
    is.getline(data, 100);

    /*for(int n = 0 ; n < 3 ; n++) {
        cout << data[n] << " | ";
    }*/
    int colPosition = 0;
    while(data[ii] != '\0') { //check if column is there or not
        temp = "" ;
        
        while(data[ii] != '|') {
            temp += data[ii];
            //cout << " \n temp - " << temp << endl ;
            ii++;
            colPosition++;
        }
        ii++;
        count1++;

        //cout << " \n temp - " << temp << endl ;

        if(temp == newColName) {
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        cout << "\n Column name specified doesn't exist..! " << endl ;
        return;
    }

   // cout << "\n Count1 - " << count1 << endl ;
    
    flag = 0;
    ii = 0;
    memset(data, 0, sizeof(data));
    is.clear();
    is.seekg(0);
    is.getline(data, 100);

    /*for(int n = 0 ; n < 3 ; n++) {
        cout << data[n] << " | ";
    }*/

    while(data[ii] != '\0') { // for where clause
        temp = "" ;

        while(data[ii] != 124) {
            temp += data[ii];
            //cout << " \n temp - " << temp << endl ;
            ii++;
        }
        ii++;
        count2++;

        //cout << " \n temp - " << temp << endl ;

        if(temp == newColName) {
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        cout << "\n Column name specified doesn't exist..! " << endl ;
    }

   // cout << "\n Count2 - " << count2 << endl ;

    while(!is.eof()) {

        memset(data, 0, sizeof(data));
        is.getline(data,100);

        for(int n = 0 ; n < 3 ; n++) {
     //       cout << data[n] << " | ";
        }

        temp = "";
        line_no++;
        ii = 0;

        for(int k = 0 ; k < count1 ; k++) {
            temp = "" ;
            while(data[ii] != 124) {
                temp += data[ii];
                ii++;
            }
            ii++;
            //cout << " \n temp - " << temp << endl ;
        }
        if(temp == value) {
            break;
        }
    }

   // cout << "\n Line - " << line_no << endl ;

    is.clear();
    is.seekg(0);
    ofstream ofs;
    ofs.open("temp.txt", ios::out);

    // Copying content to temporary file Except Line to be deleted
    char c;
    int n = 0, tt = 1;
    char arr[100];
    ii = 0;

    while (!is.eof())
    {
        memset(data, 0, sizeof(data));
        is.getline(data, 100);
        n++;

        if (n != line_no)
            ofs << data;
        else {
            while(tt < count2) {
                while(data[ii] != 124) {
                    arr[ii] = data[ii];
                    ii++;
                }

                arr[ii] = '|';
                ii++;

                tt++;
            }

            int j = 0, k = ii;

            while(newValue[j] != '\0') {
                arr[k] = newValue[j];
                k++;
                j++;
            }
            arr[k] = '|';
            k++;

            while(data[ii] != 124) {
                ii++;
            }
            ii++;

            while (data[ii] != '\0') {
                arr[k] = data[ii];
                k++;
                ii++;
            }

            arr[k] = '\0';

            for(int n = 0 ; arr[n] != '\0' ; n++) {
             //   cout << arr[n] << " | ";
            }

            ofs << arr;
        }
        ofs << '\n' ;
    }

    ofs.close();
    is.close();

    // Getting back data
    is.open("temp.txt", ios::in);
    ofs.open(tableName + ".txt", ios::out);

    while (is.get(c))
    {
        ofs << c;
    }
    ofs.close();
    is.close();

    cout << "\n Record Successfully Updated..! " << endl ;
}

void delete_record(string q)
{
    string  tableName, colName, value, t = "";
    int i=1;
    ofstream outfile;
    ifstream infile;
    char data[100];
    string temp2;
    temp2="temp";

    //cout << "Query - " << q << endl ;
    //delete from stud where name="RAJ";

    while(q[i] != 32) {
       t += q[i];
       i++;
    }
    i++;

    //cout << "\n t = " << t << endl;

    if(t == "*") {
        while(q[i] != 32) {
           i++;
        }
        i++;

        while(q[i] != ';') {
           tableName += q[i];
           i++;
        }
        i++;

        //cout << "\n " <<  tableName << endl ;

        if(checktable(tableName))
        {
            infile.open(tableName + ".txt",ios::in);
            outfile.open(temp2 + ".txt",ios::out);

            infile.getline(data,100);
            outfile<<data;

            outfile.close();
            infile.close();
            infile.open(temp2 + ".txt",ios::in);
            outfile.open(tableName + ".txt",ios::out);
            infile.getline(data,100);
            outfile<<data;
        }
        else
        {
            cout<<"\n Table does not exists..! "<<endl;
        }
    }
    else {
        while(q[i] != 32) {
           tableName += q[i];
           i++;
        }
        i++;

        //cout << "\n " <<  tableName << endl ;

        if(checktable(tableName))
        {
            while(q[i] != 32) {

               i++;
            }
            i++;

            while(q[i] != 61) {

              colName += q[i];
              i++;
            }
            i += 2;

            while(q[i] != 34) {

              value += q[i];
              i++;
            }
            i++;

            //cout << "\n " << colName << endl ;
            //cout << "\n " <<  value << endl ;
        }
        else
        {
            cout<<"\n Table does not exists..! "<<endl;
        }

        ifstream is;
        int line_no = 1, count = 0, ii = 0, flag = 0;
        char data[100];
        string temp;

        memset(data, 0, sizeof(data));

        is.open(tableName + ".txt", ios::in);
        is.getline(data, 100);

        /*for(int n = 0 ; n < 3 ; n++) {
            cout << data[n] << " | ";
        }*/

        while(data[ii] != '\0') {
            temp = "" ;

            while(data[ii] != 124) {
                temp += data[ii];
                //cout << " \n temp - " << temp << endl ;
                ii++;
            }
            ii++;
            count++;

            //cout << " \n temp - " << temp << endl ;

            if(temp == colName) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            cout << "\n Column name specified doesn't exist..! " << endl ;
        }

        //cout << "\n Count - " << count << endl ;

        while(!is.eof()) {

            memset(data, 0, sizeof(data));
            is.getline(data,100);
            /*for(int n = 0 ; n < 3 ; n++) {
                cout << data[n] << " | ";
            }*/

            temp = "";
            line_no++;
            ii = 0;

            for(int k = 0 ; k < count ; k++) {
                temp = "" ;
                while(data[ii] != 124) {
                    temp += data[ii];
                    ii++;
                }
                ii++;
                //cout << " \n temp - " << temp << endl ;
            }
            if(temp == value) {
                break;
            }
        }

        //cout << "\n Line - " << line_no << endl ;

        is.clear();
        is.seekg(0);
        ofstream ofs;
        ofs.open("temp.txt", ios::out);

        // Copying content to temporary file Except Line to be deleted
        char c;
        int n = 1;

        while (is.get(c))
        {
            if (c == '\n')
                n++;

            if (n != line_no)
                ofs << c;
        }

        ofs.close();
        is.close();

        // Getting back data
        is.open("temp.txt", ios::in);
        ofs.open(tableName + ".txt", ios::out);

        while (is.get(c))
        {
            ofs << c;
        }
        ofs.close();
        is.close();
    }

    cout << "\n Record Successfully Deleted..! " << endl ;
}

bool checkDataType(string data, string dataType)
{
    if(dataType == "int")
    {
        for (char const &c : data) 
        {
            if (std::isdigit(c) == 0) return false;
        }
    }
    return true;
}
/*
create table stud(id int, name varchar, phone_no varchar);
insert into stud values(111, ABHISHEK, 0987654321);
insert into stud values(222, NEHALI, 9594046574);
insert into stud values(333, GAURAV, 1234567890);
insert into stud values(444, RAJ, 8855224400);
truncate table stud;
drop table stud;
desc stud;
select * from stud;
id|name|phone_no|
111|ABHISHEK|0987654321|
222|NEHALI|9594046574|drop
333|GAURAV|1234567890|
111|RAJ|8855224400|

update stud set phone_no="784526390" where name="GARUAV";
update stud set name="Nehali" where id="333";
update stud set name="GAURAV" where id="222";

delete * from stud;
delete from stud where name="GAURAV";
delete from stud where id="333";

update tablename set columnane=value where condition
delete from tablename where columname=value
*/
