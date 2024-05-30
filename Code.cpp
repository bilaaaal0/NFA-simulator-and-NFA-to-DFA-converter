#include<iostream>
#include <conio.h>
#include<bits/stdc++.h>

using namespace std;

bool al=false;//for indicating if alphabet symbol used or numeric symbol used in making of NFA 
bool NFANULL=false;
class AdjNode
{
	public:
		int path;
		int state;
		string label;
		AdjNode *next;
		AdjNode()
		{
			path = 0;
			state = 0;
			label = " ";
			next = NULL;
		}
		AdjNode(int c, int k, string lab)
		{
			path = c;
			state = k;
			label = lab;
			next = NULL;
			
		}
	
};
class Vertex
{
	public:
		int state;
		string label;
		AdjNode *head;
		Vertex()
		{
			head = NULL;
		}
		Vertex(int k, string lab)
		{
			state = k;
			label = lab;
			head = NULL;
		}
};



class AdjList
{
	public:

		Vertex** arr;
		int size;
		int *input_var;
		int *final_states;
		int size_final;
		int size_input;
		bool dead; // to identify while converting nfa to dfa, is there dead state or not
		bool set; // if there is dead state then it is set or not
		vector <int> path;
		AdjList()
		{
			size = 2;
		}
		AdjList(int s,int *ain, int *fin ,int in, int fs)
		{
			size = s;
			arr = new Vertex*[size];
			for(int i=0;i<size;++i)
			{
				arr[i] = NULL;
			}
			dead = false;
			set = false;    
			size_input = in;
			input_var = new int[in];
			for(int i=0;i<in;++i)
			{
				input_var[i] = ain[i];
			}
			final_states = new int[fs];
			size_final = fs;
			for(int i=0;i<fs;++i)
			{
				final_states[i] = fin[i];
			}
		}
	
		void AddVertex(int k, string lab)
		{
			Vertex *v = new Vertex(k,lab);
			if(arr[k]==NULL)
			{
				arr[k] = v;
 			}
		}
		void AddEdge(int src, int des, int var,string des_lab)
		{
			
		    if (arr[src] != NULL )
		    {	
		        AdjNode *n = new AdjNode(var, des, des_lab);
		        if (arr[src]->head == NULL)
		        {
		            arr[src]->head = n;
		        }
		        else
		        {
		            AdjNode *temp = arr[src]->head;
		            while (temp->next != NULL)
		            {
		                temp = temp->next;
		            }
		            temp->next = n;
		        }
		    }
		}
		
		
		bool dfs(int node, int counter, const string& str) 
		{
		    
		    for (int i = 0; i < size_final; ++i) 
		    {
		        if (final_states[i] == node) 
		        {
		            if (!check_Halt(node))
		            {
		            cout<<"q"<<node<<"is a halt and final state\n";
		                return true;
						}  // Current node is a final state and has no possible tranisitons left we will accept it
		        }
		    }
		
		    //if we have done more non epsilon tranisitions then string size we will backtrack to previous state
		    if (counter > str.size()) 
		    {
		        cout << "Exceeded string length at node: " << node << ", reverting to previous state..." << endl;
		        return false;
		    }
		
		    //if we have consumed the last input and we are at the final state we accept
		    if (counter == str.size()) 
		    {
		        for (int i = 0; i < size_final; ++i) 
		        {
		            if (final_states[i] == node) 
		            {
		                cout << "String accepted at final state: " << node << "." << endl;
		                return true;  // String ends at a final state
		            }
		        }
		    }
		
		    // Explore all possible transitions from the current state
		    AdjNode* temp = arr[node]->head;
		
		    while (temp != NULL) 
		    {
		        if (temp->path == -1) //epsilon tranisitons
		        {  
		             cout << "\t\t" << "epsilon" << endl;
		            cout << "q" << node << " -------------------------------------------> " << "q" << temp->state << endl << endl;
		            cout << "Transition from q" << node << " to q" << temp->state << " via epsilon.\n\n" << endl << endl;
		            if (dfs(temp->state, counter, str)) //recrusive case
		            {
		                return true;
		            }
		        } 
		        else if (counter < str.size() && temp->path == str[counter] - '0') 
		        {  
		            if (al == true)
		            {
		                cout << "\t\t" << char(temp->path + 97) << endl; //for printing a,b,c is symbols are letters
		                cout << "q" << node << " -------------------------------------------> " << "q" << temp->state << endl << endl;
		            cout << "Transition from q" << node << " to q" << temp->state << " on reading " << char(str[counter]+49) << ".\n\n" << endl << endl;
		            }
		            else
		            {
		                cout << "\t\t" << temp->path << endl;
		                cout << "q" << node << " -------------------------------------------> " << "q" << temp->state << endl << endl;
		            cout << "Transition from q" << node << " to q" << temp->state << " on reading " << str[counter] << ".\n\n" << endl << endl;
		            }
		            
		            if (dfs(temp->state, counter + 1, str)) //recrusive case
		            {
		                return true;
		            }
		        }
		        
		        temp = temp->next;
		    }
		    AdjNode* temp2 = arr[node]->head;
		    bool flag=false;
		
		    while(temp2!=NULL)        //checking if we have backtracked to a state and if there still tranistions possible from it with current input symbol read we will make flag ==true
		    {
		    	
		    	if((str[counter]-'0')==temp2->path)
		    	{
		    		
		    		flag=true;
				}
				temp2=temp2->next;
			}
		    
		    if(flag==false) //if flag false means there are no possible tranisitions then we check if it is a final state so accept 
		    {
			
		    for (int i = 0; i < size_final; ++i) 
		    {
		        if (final_states[i] == node) 
		        {
		        	cout<<endl<<"q"<<node<<" is a halt and final state\n";
		            return true;  // Final state reached again
		        }
		    }
		}
		
		    // If no valid transitions found, we move back to previous state and try from that
		    cout << "No valid transitions from state" << node << ", reverting to previous decision point." << endl;
		    return false;
		}

        bool check_Halt(int state)
		{
			AdjNode *temp = arr[state]->head;
			
			return temp;
		}
		void update_size(int s)
		{
			size = s;
		}


		bool NFA(string str)
		{
		    int q0 = 0;
		    path.push_back(q0);
		    return dfs(q0, 0, str); 
		}
		string sort(string str) 
		{
			int k = str.length();
	    	k/=2;
	    	int arr[k];
	    	int a = 0;
	    	for(int j=1;str[j]!='\0';j+=2)
	    	{
	    		arr[a] = str[j] - 48;
	    		a++;
			}
		    int i, j, temp;
		    for (i = 0; i < k-1; i++) 
			{
		       
		        for (j = 0; j < k-i-1; j++) 
				{
		            if (arr[j] > arr[j+1]) 
					{
		                temp = arr[j];
		                arr[j] = arr[j+1];
		                arr[j+1] = temp;
		            }
		        }
		    }
		    string t;
		    for(int i=0;i<k;++i)
		    {
		    	t+="q";
		    	t+=arr[i] + 48;
			}
			return t;
		}
		void NFAToDFA()
		{
			int s = pow(2,size);// maximum state in dfa 
			AdjList dfa(s,input_var,final_states,size_input,size_final);//Dfa intialize
			dfa.AddVertex(0,"q0");//q0 state is added
			int u = 1;
			
			string new_states[size_input];//temporary string array created 
			AdjNode *temp;
		    for(int i=0;i<u;++i) // loop on all veretx in dfa
		    {
		    	for(int j=0;j<size_input;++j)
		    	{
		    		new_states[j].clear(); // array of string clear 
				}
		    	string str = dfa.arr[i]->label;//vertex label in dfa is copied in str
		    	int k = str.length();
		    	k/=2;
		    	int array[k];
		    	int a = 0;
		    	for(int j=1;str[j]!='\0';j+=2) // loop on even idices of str to convert it into integer and store in an array. eg q0q1q2 0,1,2 will be extracted and stored in the array
		    	{
		    		array[a] = str[j] - 48;
		    		a++;
				}
				for(int j=0;j<k;++j) //loop on array
				{
					int b = array[j];
					
					temp = arr[b]->head; 
			
					while (temp != NULL)//loop on adjlist of nfa 
					{
					    string newState = temp->label;
				        if (new_states[temp->path].find(newState) == string::npos)
				        {
				            new_states[temp->path] += newState;
				        }
					    temp = temp->next;
					}
				}	
				for (int m = 0; m < size_input; ++m)
			    {
			    	string t;
			    	if(new_states[m].length()>2)
			    	t =	sort(new_states[m]);//new_states string is sorted based on state number
			    	
			        bool found = false;
			        bool d = false;
					if(t.length() == 0)
					{
						d = true; // to identify dead state
					}
				
			        if(!d)
			        {
			        	for (int f = 0; f < u; ++f)
				        {
				            if (t == dfa.arr[f]->label)
				            {
				                found = true; 
				                break;
				            }
				        }
				        int l = i;
				        while(dfa.arr[l]!=NULL)
				        {
				        	l++;
						}
				        
				        if(!found)
				        {
				            dfa.AddVertex(l, t); // vertex added if it is new
				            dfa.AddEdge(i, u, m, t); // edge added
				            ++u;
				            
				        }
				        else
				        {
				        	dfa.AddEdge(i, u, m, t); // edge added
						}
					}
					else
					{
						dfa.dead = true;
						if(!dfa.set)
						{
							dfa.AddVertex(-1,"DEAD"); // if dead state found, vertex added with label "DEAD"
						}
						dfa.AddEdge(i,-1,m,"DEAD");// edge added to dead state
						dfa.set = true;	
					}
			    }
			}
			if(dfa.dead && dfa.set)
			{
				++u;
				dfa.AddVertex(u,"DEAD"); //last state number assigned to dead state
				for(int m=0;m<size_input;++m)
				{
					dfa.AddEdge(u,u,m,"DEAD"); // self loop of all input added to dead state
				}
			}
			dfa.update_size(u+1);
			dfa.Print();		
		}
		bool checkFinal(string str)
		{
			int k = str.length();
			k/=2;
			int array[k];
			int a = 0;
			for(int j=1;str[j]!='\0';j+=2)
			{
				array[a] = (str[j] - 48);
				a++;
		
			}
			bool found = false;
			for(int j=0;j<k;++j)
			{
				for(int l=0;l<size_final;++l)
				{
					if(array[j] == final_states[l])
					{
					
						found = true;
						break;
					}
				}
			}
			return found;
		}

        void Print2()
		{

			cout<<"States with F are final states\n\n";
			for (int i = 0; i < size; i++) 
			{
			
	        	if (arr[i] != NULL) 
				{
				
	        		
	        		AdjNode *temp = arr[i]->head;
	        		
	        		while(temp != NULL) 
					{
						bool a =false;
						bool b =false;
						if(checkFinal(arr[i]->label))
						{
							a = true;
						}
						if(checkFinal(temp->label))
						{
							b = true;
						}
						if(al==true)
		                {
		                	if(temp->path==-1)
		                	{
		                	cout<<"\t\t"<<"epsilon"<<endl;
							}
							else
							{
								char y = temp->path+'a';
								cout <<"\t\t"<<y<<endl;
							}
		                	
						}
		                else
		                {
		                	if(temp->path==-1)
		                	{
		                		cout <<  ("epsilon");
							}
							else
		                    cout <<"\t\t"<< (temp->path)<<endl;
		                
						}
					
						cout<<arr[i]->label;
						if(a)
						cout<<"F";
						cout<<" ----------------------> ";
						cout<<temp->label;
						if(b)
						cout<<"F";
	        			
	        			cout<<endl;
	        			temp = temp->next;
					}
					cout<<endl;
				}
	    	}
		}

void Print() 
{
    cout << "States with F are final states\n\n";


    cout << "+--------------+----------+--------------+\n";
    cout << "| Current      | Symbol   | Next         |\n";
    cout << "+--------------+----------+--------------+\n";

    for (int i = 0; i < size; i++) {
        if (arr[i] != NULL) 
		{
            AdjNode *temp = arr[i]->head;

            while (temp != NULL) 
			{
                bool isCurrentFinal = false;
                bool isNextFinal = false;
                if (checkFinal(arr[i]->label)) 
				{
                    isCurrentFinal = true;
                }
                if (checkFinal(temp->label)) 
				{
                    isNextFinal = true;
                }

                cout << "| " << left <<setw(12) << arr[i]->label + (isCurrentFinal ? "F" : "");
                if(al==true)
                {
                	if(temp->path==-1)
                	{
                		cout << "| " << left << setw(8) << ("epsilon");
					}
					else
                	cout << "| " << left << setw(8) << char(temp->path+97);
				}
                else
                {
                	if(temp->path==-1)
                	{
                		cout << "| " << left <<setw(8) << ("epsilon");
					}
					else

                	cout << "| " << left << setw(8) << (temp->path);
				}
                cout << "| " << left << setw(12) << temp->label + (isNextFinal ? "F" : "");
                cout << "|\n";

                temp = temp->next;
            }
       
            cout << "+--------------+----------+--------------+\n";
        }
    }
    cout << endl;
}

		void Display() 
		{
			for (int i = 0; i < size; i++) 
			{
	        	if (arr[i] != NULL) 
				{
				
	        		cout << "Source state : " << arr[i]->label <<"  "<<arr[i]->state<< endl;
	        		AdjNode *temp = arr[i]->head;
	        		
	        		while(temp != NULL) 
					{
	        			cout<<"state : " << temp->label << " path : " << temp->path << "\t";
	        			temp = temp->next;
					}
					cout<<endl;
				}
	    	}
		}
};


void dis() 
{
    const int width = 80;
    cout << setw(width) << setfill('=') << "" << endl;
    cout << setfill(' ');
    cout << "=========================================================\n";
    cout << "|                   NFA Menu                             |\n";
    cout << "---------------------------------------------------------\n";
    cout << "| Options:                                               |\n";
    cout << "|          1 - Use a prebuilt NFA                        |\n";
    cout << "|          2 - Make a NFA yourself                       |\n";
    cout << "|          3 - Exit                                      |\n";
    cout << "---------------------------------------------------------\n";
    cout << "| Enter your choice (1-3):                               |\n";
    cout << "=========================================================\n";
}

void display_welcome_message() {
    const int box_width = 70; 
    const int screen_width = 80; 
    const int left_padding = (screen_width - box_width) / 2; 
    cout << "\n\n"; 
    cout << setw(left_padding) << "" << setw(box_width) << setfill('*') << "" << endl; 
    cout << setfill(' '); 
    cout << setw(left_padding) << "\t" << "* Welcome to the TOA project.    \t" << endl << endl << endl << endl;
    cout << setw(left_padding) << "\t\t" << "* Conversion of Nfa to Dfa     \t" << endl << endl << endl << endl;
    cout << setw(left_padding) << "\t\t" << "* Recognizing NFA NULL     \t" << endl << endl << endl << endl;

    cout << setw(left_padding) << "" << setw(box_width) << setfill('*') << "" << endl;
    cout << setfill(' '); 
    cout << endl << endl;
    cout<<"Press 1 to Proceed , Press 0 to exit \n";
}


int main()
{
	int k;
    system("color 70");
    display_welcome_message();
    cin>>k;
    if(k==0)
    {
    	return 0;
	}
    for( ; ; )
    {
    	m2:
    	al = false;
      system("CLS");
    	int choice;
    	dis();
    	cin >> choice;
    	if( choice == 1 )
    	{
    		int l;
    		cout << "=========================================================\n";
        	cout << "|                    Option Menu                        |\n";
        	cout << "---------------------------------------------------------\n";
        	cout << "| Options:                                              |\n";
        	cout << "|          1. NFA with epsilon                           |\n";
        	cout << "|          2. NFA without epsilon                        |\n";
        	cout << "|          3. NFA with Epsilon                           |\n";
        	cout << "|          4. NFA without epsilon                        |\n";
        	cout << "|          5. NFA without epsilon                        |\n";
        	cout << "|          6. NFA without epsilon                        |\n";
        	cout << "|          7. Go back                                    |\n";
        	cout << "---------------------------------------------------------\n";
        	cout << "| Enter your choice (1-7):                              |\n";
        	cout << "=========================================================\n";
    		cin>>l;
    		if(l==1)
	    	{
				int input = 3;
	    		int* input_arr = new int[input];
	    		input_arr[0] = 0;
	    		input_arr[1] = 1;
	    		int states = 8;
				int final_states = 3;
				int* final_states_array = new int[final_states];
				final_states_array[0] = 5; // q5 is a final state
				final_states_array[1] = 7; // q7 is a final state
				final_states_array[2] = 0;
	    		AdjList nfa(states, input_arr, final_states_array, input, final_states);
	    		nfa.AddVertex(0, "q0");
				nfa.AddVertex(1, "q1");
				nfa.AddVertex(2, "q2");
				nfa.AddVertex(3, "q3");
				nfa.AddVertex(4, "q4");
				nfa.AddVertex(5, "q5");
				nfa.AddVertex(6, "q6");
				nfa.AddVertex(7, "q7");
				// Adding edges based on transitions shown in the diagram
				nfa.AddEdge(0, 1, -1, "q1"); // epsilon transition from q0 to q1
				nfa.AddEdge(1, 2, -1, "q2"); // epsilon transition from q1 to q2
				nfa.AddEdge(2, 3, 0, "q3"); // transition from q2 to q3 on 'a'
				nfa.AddEdge(3, 4, -1, "q4"); // transition from q3 to q4 on 'b'
				nfa.AddEdge(4, 5, 1, "q5"); // epsilon transition from q4 to q5
				nfa.AddEdge(1, 6, -1, "q6"); // epsilon transition from q2 to q6
				nfa.AddEdge(6, 7, 0, "q7"); // transition from q6 to q7 on 'a'
				nfa.AddEdge(5, 1, -1, "q1"); // epsilon transition from q5 back to q0 (loop back for *)
				nfa.AddEdge(7, 1, -1, "q1"); // epsilon transition from q7 back to q0 (loop back for *)
			k1:
				nfa.Print();
			
			int c;
			
			while(1)
			{
				
				
				cout << "=========================================================\n";
    			cout << "|                NFA to DFA Converter                   |\n";
    			cout << "=========================================================\n";
    			cout << "|                    Main Menu                          |\n";
    			cout << "---------------------------------------------------------\n";
    			cout << "| Options:                                              |\n";
    			cout << "|                                                       |\n";
   				cout << "|          1. Perform NFA null recognition              |\n";
    			cout << "|          2. Exit                                      |\n";
    			cout << "---------------------------------------------------------\n";
    			cout << "| Enter your choice (1-2):                              |\n";
    			cout << "=========================================================\n";
				cin>>c;
				if(c==2)
				{
					goto m2;
				}
				
      			 if(c==1)
      			{
      				string userInput;
      				fflush(stdin);
    					cout << "Please enter something: ";
    					getline(cin, userInput);	
    					if(nfa.NFA(userInput))
    					{
    						cout<<"accpeted\n";
					}
					else
					{
						cout<<"rejected\n";
					}
    					cout<<"\n---------------------------------------------\n";
      			}
      			else
				{
      				cout<<"Wrong input \n";
      				goto k1;
      			}
      		}
			}
			 //2nd nfa
			if(l==2)
			{
				int input2 = 2; // Different input size
				int* input_arr2 = new int[input2];
				input_arr2[0] = 0;
				input_arr2[1] = 1;
				
				int states2 = 8;
				int final_states2 = 3;
				int* final_states_array2 = new int[final_states2];
				final_states_array2[0] = 5;
				final_states_array2[1] = 7;
				final_states_array2[2] = 0;
				
				AdjList nfa2(states2, input_arr2, final_states_array2, input2, final_states2);
				nfa2.AddVertex(0, "q0");
				nfa2.AddVertex(1, "q1");
				nfa2.AddVertex(2, "q2");
				nfa2.AddVertex(3, "q3");
				nfa2.AddVertex(4, "q4");
				nfa2.AddVertex(5, "q5");
				nfa2.AddVertex(6, "q6");
				nfa2.AddVertex(7, "q7");
				// Adding edges based on transitions
				nfa2.AddEdge(0, 1, 1, "q1"); // Transition from q0 to q1 on 'a'
				nfa2.AddEdge(1, 2, 1, "q2"); // Transition from q1 to q2 on 'b'
				nfa2.AddEdge(2, 3, 1, "q3"); // Transition from q2 to q3 on 'a'
				nfa2.AddEdge(3, 4, 1, "q4"); // Transition from q3 to q4 on 'b'
				nfa2.AddEdge(4, 5, 0, "q5"); // Transition from q4 to q5 on 'a'
				nfa2.AddEdge(5, 6, 1, "q6"); // Transition from q5 to q6 on 'b'
				nfa2.AddEdge(6, 7, 0, "q7"); // Transition from q6 to q7 on 'a'
				nfa2.AddEdge(7, 0, 1, "q0"); // Transition from q7 back to q0 on 'b'
				k2:
				nfa2.Print();
			
			int c;
			
			while(1)
			{
				
				cout << "=========================================================\n";
    			cout << "|                NFA to DFA Converter                   |\n";
    			cout << "=========================================================\n";
    			cout << "|                    Main Menu                          |\n";
    			cout << "---------------------------------------------------------\n";
    			cout << "| Options:                                              |\n";
    			cout << "|          1. Construct and convert NFA to DFA          |\n";
   				cout << "|          2. Perform NFA null recognition              |\n";
    			cout << "|          3. Exit                                      |\n";
    			cout << "---------------------------------------------------------\n";
    			cout << "| Enter your choice (1-3):                              |\n";
    			cout << "=========================================================\n";
				cin>>c;
				if(c==3)
				{
					goto m2;
				}
				if(c==1)
      			{
      			nfa2.NFAToDFA();
      			}
      			else if(c==2)
      			{
      				string userInput;
      				fflush(stdin);
    					cout << "Please enter something: ";
    					getline(cin, userInput);	
    					if(nfa2.NFA(userInput))
    					{
    						cout<<"accpeted\n";
					}
					else
					{
						cout<<"rejected\n";
					}
    					cout<<"\n---------------------------------------------\n";
      			}
      			else
				{
      				cout<<"Wrong input \n";
      				goto k2;
      			}
      		}
			}
		
			//nfa 3
			if (l == 3) 
			{
		    	int input3 = 2; // Different input size
		    	int* input_arr3 = new int[input3];
		    	input_arr3[0] = 0; // Representing 0
		    	input_arr3[1] = 1; // Representing 1
				
				int states3 = 8;
				int final_states3 = 3;
				int* final_states_array3 = new int[final_states3];
				final_states_array3[0] = 5;
				final_states_array3[1] = 7;
				final_states_array3[2] = 0;
				
				AdjList nfa3(states3, input_arr3, final_states_array3, input3, final_states3);
				nfa3.AddVertex(0, "q0");
				nfa3.AddVertex(1, "q1");
				nfa3.AddVertex(2, "q2");
				nfa3.AddVertex(3, "q3");
			    nfa3.AddVertex(4, "q4");
			    nfa3.AddVertex(5, "q5");
			    nfa3.AddVertex(6, "q6");
			    nfa3.AddVertex(7, "q7");
			
			    // Adding edges based on transitions
			    nfa3.AddEdge(0, 1, 0, "q1"); // Transition from q0 to q1 with input '0'
			    nfa3.AddEdge(1, 2, 1, "q2"); // Transition from q1 to q2 with input '1'
			    nfa3.AddEdge(2, 3, 0, "q3"); // Transition from q2 to q3 with input '0'
			    nfa3.AddEdge(3, 4, -1, "q4"); // Transition from q3 to q4 with input '1'
			    nfa3.AddEdge(4, 5, 0, "q5"); // Transition from q4 to q5 with input '0'
			    nfa3.AddEdge(5, 6, -1, "q6"); // Transition from q5 to q6 with input '1'
			    nfa3.AddEdge(6, 7, 0, "q7"); // Transition from q6 to q7 with input '0'
			    nfa3.AddEdge(7, 0, -1, "q0"); // Transition from q7 back to q0 with input '1'
			  k3:
			    nfa3.Print();
			
			    int c;
			
			    while (true) 
				{
			        
					cout << "=========================================================\n";
    				cout << "|                NFA to DFA Converter                   |\n";
    				cout << "=========================================================\n";
    				cout << "|                    Main Menu                          |\n";
    				cout << "---------------------------------------------------------\n";
    				cout << "| Options:                                              |\n";
    				cout << "|                                                       |\n";
   					cout << "|          1. Perform NFA null recognition              |\n";
    				cout << "|          2. Exit                                      |\n";
    				cout << "---------------------------------------------------------\n";
    				cout << "| Enter your choice (1-2):                              |\n";
    				cout << "=========================================================\n";
			        cin >> c;
			        if (c == 2) 
					{
			            goto m2;
			        }
			        if (c == 1) 
					{
			            string userInput;
			            fflush(stdin);
			            cout << "Please enter something: ";
			            getline(cin, userInput);
			            if (nfa3.NFA(userInput)) {
			            	cout<<"\nResult\n";
			                cout << "accepted\n";
			            } 
						else 
						{
							cout<<"\nResult\n";
			                cout << "rejected\n";
			            }
			            cout << "\n---------------------------------------------\n";
			        } 
					else 
					{
			            cout << "Wrong input \n";
			            goto k3;
			        }
			    }
			}
		     if (l == 4) 
			 {
				int input4 = 2; // Different input size
				int* input_arr4 = new int[input4];
				input_arr4[0] = 0; // Representing 'a'
				input_arr4[1] = 1; // Representing 'b'
				
				al = true;
				
				int states4 = 8;
				int final_states4 = 3;
				int* final_states_array4 = new int[final_states4];
				final_states_array4[0] = 5;
			    final_states_array4[1] = 7;
			    final_states_array4[2] = 0;
				
			    AdjList nfa4(states4, input_arr4, final_states_array4, input4, final_states4);
			    nfa4.AddVertex(0, "q0");
			    nfa4.AddVertex(1, "q1");
			    nfa4.AddVertex(2, "q2");
				nfa4.AddVertex(3, "q3");
				nfa4.AddVertex(4, "q4");
				nfa4.AddVertex(5, "q5");
				nfa4.AddVertex(6, "q6");
				nfa4.AddVertex(7, "q7");
				
				    // Adding edges based on transitions
				nfa4.AddEdge(0, 1, 0, "q1"); // Transition from q0 to q1 with input 'a'
				nfa4.AddEdge(1, 2, 1, "q2"); // Transition from q1 to q2 with input 'b'
				nfa4.AddEdge(2, 3, 0, "q3"); // Transition from q2 to q3 with input 'a'
				nfa4.AddEdge(3, 4, 1, "q4"); // Transition from q3 to q4 with input 'b'
				nfa4.AddEdge(4, 5, 0, "q5"); // Transition from q4 to q5 with input 'a'
				nfa4.AddEdge(5, 6, 1, "q6"); // Transition from q5 to q6 with input 'b'
				nfa4.AddEdge(6, 7, 1, "q7"); // Transition from q6 to q7 with input 'a'
				nfa4.AddEdge(7, 0, 1, "q0"); // Transition from q7 back to q0 with input 'b'
				k7:
				nfa4.Print();
				
				int c;
				
				    while (true) 
					{
				        cout << "=========================================================\n";
    					cout << "|                NFA to DFA Converter                   |\n";
    					cout << "=========================================================\n";
    					cout << "|                    Main Menu                          |\n";
    					cout << "---------------------------------------------------------\n";
    					cout << "| Options:                                              |\n";
    					cout << "|          1. Construct and convert NFA to DFA          |\n";
   						cout << "|          2. Perform NFA null recognition              |\n";
    					cout << "|          3. Exit                                      |\n";
    					cout << "---------------------------------------------------------\n";
    					cout << "| Enter your choice (1-3):                              |\n";
    					cout << "=========================================================\n";
				        cin >> c;
				        if (c == 3) 
						{
							al = false;
				            goto m2;
				        }
				        if (c == 1) 
						{
				            nfa4.NFAToDFA();
				        } 
						else if (c == 2) 
						{
				            string userInput;
				            fflush(stdin);
				            cout << "Please enter something: ";
				             getline(cin, userInput);
				            string processedInput;
    						 for (int i = 0; i < userInput.length(); i++) {
                			char c = userInput[i];
               			 if (c >= 'a' && c <= 'e') { 
                  			processedInput += to_string(c - 'a');
              					  }
						}
				           
				            if (nfa4.NFA(processedInput)) 
							{
								cout<<"\nResult\n";
				                cout << "accepted\n";
				            } 
							else 
							{
								cout<<"\nResult\n";
				                cout << "rejected\n";
				            }
				            cout << "\n---------------------------------------------\n";
				        } 
						else 
						{
				            cout << "Wrong input \n";
				            goto k7;
				        }
				    }
				    
				}
				 if (l == 5) 
				 {
						int input5 = 2; // Different input size
						int* input_arr5 = new int[input5];
						input_arr5[0] = 0; // Representing 'a'
						input_arr5[1] = 1; // Representing 'b'
						al = true;
						
						
						int states5 = 4;
						int final_states5 = 2;
						int* final_states_array5 = new int[final_states5];
						final_states_array5[0] = 2;
					    final_states_array5[1] = 3;
						
					    AdjList nfa5(states5, input_arr5, final_states_array5, input5, final_states5);
					    nfa5.AddVertex(0, "q0");
					    nfa5.AddVertex(1, "q1");
					    nfa5.AddVertex(2, "q2");
						nfa5.AddVertex(3, "q3");
						
						//Source Destination Inputvariable DestinationLabel
						nfa5.AddEdge(0,0,0,"q0"); 
						nfa5.AddEdge(0,0,1,"q0");
						nfa5.AddEdge(0,1,0,"q1");
						nfa5.AddEdge(1,2,0,"q2");
						nfa5.AddEdge(1,1,1,"q1");
						nfa5.AddEdge(2,3,1,"q3");
						nfa5.AddEdge(3,2,1,"q2");
						k9:
						nfa5.Print();
						cout<<endl;
						nfa5.Print2();
						
						int c;
						
						    while (true) 
							{
						        cout << "=========================================================\n";
		    					cout << "|                NFA to DFA Converter                   |\n";
		    					cout << "=========================================================\n";
		    					cout << "|                    Main Menu                          |\n";
		    					cout << "---------------------------------------------------------\n";
		    					cout << "| Options:                                              |\n";
		    					cout << "|          1. Construct and convert NFA to DFA          |\n";
		   						cout << "|          2. Perform NFA null recognition              |\n";
		    					cout << "|          3. Exit                                      |\n";
		    					cout << "---------------------------------------------------------\n";
		    					cout << "| Enter your choice (1-3):                              |\n";
		    					cout << "=========================================================\n";
						        cin >> c;
						        if (c == 3) 
								{
									al = false;
						            goto m2;
						        }
						        if (c == 1) 
								{
						            nfa5.NFAToDFA();
						        } 
								else if (c == 2) 
								{
						            string userInput;
				            fflush(stdin);
				            cout << "Please enter something: ";
				             getline(cin, userInput);
				            string processedInput;
    						 for (int i = 0; i < userInput.length(); i++) {
                			char c = userInput[i];
               			 if (c >= 'a' && c <= 'e') { 
                  			processedInput += to_string(c - 'a');
              					  }
						}
						            if (nfa5.NFA(processedInput))
									{
										cout<<"\nResult\n";
						                cout << "accepted\n";
						            } 
									else 
									{
										cout<<"\nResult\n";
						                cout << "rejected\n";
						            }
						            cout << "\n---------------------------------------------\n";
						        } 
								else 
								{
						            cout << "Wrong input \n";
						            goto k9;
						        }
						    }
				}
				if (l == 6) 
				 {
						int input6 = 2; // Different input size
						int* input_arr6 = new int[input6];
						input_arr6[0] = 0; // Representing 'a'
						input_arr6[1] = 1; // Representing 'b'
						al = true;
						int states6 = 4;
						int final_states6 = 1;
						int* final_states_array6 = new int[final_states6];
						final_states_array6[0] = 1;
						
					    AdjList nfa6(states6, input_arr6, final_states_array6, input6, final_states6);
					    nfa6.AddVertex(0, "q0");
					    nfa6.AddVertex(1, "q1");
					    nfa6.AddVertex(2, "q2");
						nfa6.AddVertex(3, "q3");
						
						//Source Destination Inputvariable DestinationLabel
						nfa6.AddEdge(0,1,0,"q1"); 
						nfa6.AddEdge(0,2,0,"q2");
						nfa6.AddEdge(1,1,0,"q1");
						nfa6.AddEdge(1,2,0,"q2");
						nfa6.AddEdge(2,1,1,"q1");
						nfa6.AddEdge(2,3,1,"q3");
						nfa6.AddEdge(3,2,0,"q2");
						nfa6.AddEdge(3,1,0,"q1");
						k11:
						nfa6.Print();
						cout<<endl;
						nfa6.Print2();

						int c;
						
						    while (true) 
							{
						        cout << "=========================================================\n";
		    					cout << "|                NFA to DFA Converter                   |\n";
		    					cout << "=========================================================\n";
		    					cout << "|                    Main Menu                          |\n";
		    					cout << "---------------------------------------------------------\n";
		    					cout << "| Options:                                              |\n";
		    					cout << "|          1. Construct and convert NFA to DFA          |\n";
		   						cout << "|          2. Perform NFA null recognition              |\n";
		    					cout << "|          3. Exit                                      |\n";
		    					cout << "---------------------------------------------------------\n";
		    					cout << "| Enter your choice (1-3):                              |\n";
		    					cout << "=========================================================\n";
						        cin >> c;
						        if (c == 3) 
								{
									al = false;
						            goto m2;
						        }
						        if (c == 1) 
								{
						            nfa6.NFAToDFA();
						        } 
								else if (c == 2) 
								{
						           
						            fflush(stdin);
						            string userInput;
				            fflush(stdin);
				            cout << "Please enter something: ";
				             getline(cin, userInput);
				            string processedInput;
    						 for (int i = 0; i < userInput.length(); i++) {
                			char c = userInput[i];
               			 if (c >= 'a' && c <= 'e') { 
                  			processedInput += to_string(c - 'a');
              					  }
						}
						            cout << "Please enter something: ";
						            
						            if (nfa6.NFA(processedInput))
									{
										cout<<"\nResult\n";
						                cout << "accepted\n";
						            } 
									else 
									{
											cout<<"\nResult\n";
						                cout << "rejected\n";
						            }
						            cout << "\n---------------------------------------------\n";
						        } 
								else 
								{
						            cout << "Wrong input \n";
						            goto k11;
						        }
						    }
				}
    	
    	}
    	if( choice == 2 )
    	{
    		al=0;
    		NFANULL=false;
    		int input,opt,ele,states,final_states,fin,nu;
    		string verinp,stat;
    		l4:
    		cout<<"How many input symbols are there ?";
    		cin>>input;
    		if(input<=0)
    		{
    			cout<<"It has to be more than zero/n";
    			goto l4;
    		}
    		cout<<"Enter 0: Numeric Symbols(0,1,2 etc) \n";
    		cout<<"Enter 1: Alphabet Symbols(a,b,c etc)\n";
    		fflush(stdin);
    		cin>>nu;
    		if(nu==1)
    		{
    			al=true;
    		}
    		else
			{
    			al=false;
    		}
    		
    		int* input_arr = new int[input];
    		cout<<"List down input symbols\n";
      	 
      		input_arr = new int[input];
      		char e;
      		for(int i=0;i<input;i++)
      		{
      			cout<<"Enter Input Symbol "<<i+1<<endl;
      			fo1:
      			if(al==true)
      			{
      				fflush(stdin);
      				cin>>e;
      				if(e<97&&e!='E')
      				{
      					cout<<"No capital letters allowed as input\n";
      					goto fo1;
      				}
      				if(e=='E')
      				{
      					input_arr[i]=-1;
					}
					else
					{
      				input_arr[i]=e-97;
      				}
      			}
      			else
      			{
      				cin>>ele;
					input_arr[i]=ele;	
				}	
			}
     	fflush(stdin);
      	cout<<"\nEnter the number of states in NFA\n";
      	cin>>states;
      	string sp[states];
      	for(int i = 0 ; i < states; i++)
      	{
      		string o=to_string(i);
      		sp[i]="q"+o;
      	}
      
      	l2:
      	cout<<"\nHow many final states are there in NFA\n";
      	cin>>final_states;
      	
      	if(final_states>states||final_states<1)
      	{
      		cout<<"Invalid\n";
      		goto l2;
      	}	
      
     	 	int* final_states_array = new int[final_states];

      	for(int i=0;i<final_states;i++)
      	{
      		f1:
      		cout<<"\nSelect the final states from the following \n\n";
            for(int i = 0 ; i < states; i++)
      		{
      			cout<<i<<"."<<sp[i]<<endl;
      		}
      		cin>>fin;
      		if(fin>=states)
      		{
      			cout<<"Wrong input\n";
      			goto f1;
      		}
      		final_states_array[i]=fin;
      	}
      	AdjList nfa(states,input_arr, final_states_array, input, final_states);
		for(int i=0;i<states;i++)
      	{
      		nfa.AddVertex( i , sp[i] );
      	}
      
      	for( int i = 0 ; i < states ; i++ )
      	{
      		int numed,des,d,inp;
      		string deslab;
      		cout << "\nHow many edges do you want for State "<< i << endl;
      		cin >> numed;
      		for( int k = 0 ; k < numed ; k++ )
      		{	
      			f2:
      			if(numed>0)
      		    {
      				cout<<"Select destination from following list\n";
      				for(int t = 0 ; t < states; t++)
                  	{
      					cout<<t<<"."<<sp[t]<<endl;
      	      		}
      			}
      			cin >> des;
      			if(des>states)
      			{
      				cout<<"destination state number not valid\n";
      				goto f2;
      			}
      			h1:
      			cout << "\nEnter the input symbol for this transition ? \n";
      			cout<<"For making NFA with Null, Enter -1 or E to represent Epsilon Transition \n";
      			if(al==1)
      			{
      				char e;
      				cin>>e;
      				if(e=='E')
      				{
      					NFANULL=true;
					  }
      				if(des==i&&e=='E')
      				{
      					continue;
					}
					if(e=='E')
					{
						inp=-1;
					}
					else
					{
						bool l;
						l=false;
						for(int i=0;i<input;i++)
						{
							if(input_arr[i]==e-97)
							{
								inp=e-97;
								l=true;
								break;
							}
						}
		                if(l==false)
		                {
		                	cout<<"Wrong Input, enter again\n\n";
		                	goto h1;
						}
      				}
      			}
      			else
				{
      				cin >> inp;
      				if(inp==-1)
      				{
      					NFANULL=true;
					  }
      				if(des==i&&inp==-1)
      				{
      					continue;
					}
					else
					{
						bool l;
						l=false;
						for(int i=0;i<input;i++)
						{
							if(input_arr[i]==inp)
							{
								l=true;
								break;
							}
						}
			            if(l==false)
			            {
			                cout<<"Wrong Input, enter again\n\n";
			                goto h1;
						}
					}
      		    }
				nfa.AddEdge(i,des,inp,sp[des]);    
				cout<<endl<<endl; 
				nfa.Print2(); 
			}
      	}
      		nfa.Print();
      
			int c;
			
			while(1)
			
			{
				 k5:
				cout<<"\nPress any key to continue....\n";
				getch();
				system("CLS");
				
				nfa.Print();
				if(NFANULL==false)
				{
				
				cout << "=========================================================\n";
    			cout << "|                NFA to DFA Converter                   |\n";
    			cout << "=========================================================\n";
    			cout << "|                    Main Menu                          |\n";
    			cout << "---------------------------------------------------------\n";
    			cout << "| Options:                                              |\n";
    			cout << "|          1. Construct and convert NFA to DFA          |\n";
   				cout << "|          2. Perform NFA null recognition              |\n";
    			cout << "|          3. Exit                                      |\n";
    			cout << "---------------------------------------------------------\n";
    			cout << "| Enter your choice (1-3):                              |\n";
    			cout << "=========================================================\n";
    		}
    		else if(NFANULL==true)
    		{
    			cout<<"\nPress any key to continue....\n";
    			getch();
				system("CLS");
				
				nfa.Print();
    			cout << "=========================================================\n";
    			cout << "|                NFA to DFA Converter                   |\n";
    			cout << "=========================================================\n";
    			cout << "|                    Main Menu                          |\n";
    			cout << "---------------------------------------------------------\n";
    			cout << "| Options:                                              |\n";
   				cout << "|          1. Perform NFA null recognition              |\n";
    			cout << "|          2. Exit                                      |\n";
    			cout << "---------------------------------------------------------\n";
    			cout << "| Enter your choice (1-2):                              |\n";
    			cout << "=========================================================\n";
    			
			}
				cin>>c;
				if(c==3 &&NFANULL==false )
				{
					goto m2;
				}
				if(c==2 && NFANULL==true)
				{
					goto m2;
				}
				if(c==1&&NFANULL==false)
      			{
      				nfa.NFAToDFA();
      			}
      			else if((c==2 && NFANULL==false) || (c==1 && NFANULL==true))
      			{
      				string userInput;
      				fflush(stdin);
    					cout << "\nPlease enter something\n: ";
    				
    					getline(cin, userInput);
							cout<<"\n\nSimulation\n\n";	
    					if(al==1)
    					{
    						string processedInput;
    						 for (int i = 0; i < userInput.length(); i++) {
                			char c = userInput[i];
               			 if (c >= 'a' && c <= 'e') { 
                  			processedInput += to_string(c - 'a');
              					  }
						}
						
						if(nfa.NFA(processedInput))
    					{
    					
							cout<<"Result:\n";
    						cout<<"accpeted\n";
					}
					else
					{
							
						cout<<"rejected\n";
					}
    					cout<<"\n---------------------------------------------\n";
					}
					else{
			
    					if(nfa.NFA(userInput))
    					{
    								cout<<"Result:\n";
    						cout<<"accpeted\n";
					}
					else
					
					{
						
						cout<<"rejected\n";
					}
    					cout<<"\n---------------------------------------------\n";
    				}
      			}
      			else
				{
      				cout<<"Wrong input \n";
      				goto k5;
      			}
      		}
	}
	if( choice == 3 ){
		
		cout<<" \nExiting Program ...\n";
		return 0;
		
	}
	
     


}

}
