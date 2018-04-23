#include <iostream> 
#include <cstdlib> 
#include <fstream> 
#include <cmath>


using namespace std;

/*Logic of Code:
Reads a csv file that is organized by title
Reads title, creates a linked list with all of the authors of the publication
each link includes all the information relating to the author (department, race, gender, etc)
Calculates the homophily index using formula from Harvard paper 
	summation[(#ofAuthorsInRaceGroup/TotalAuthors)^2]
Once reads a new title, it will delete this linked list (to free up memory) and creates a new list
*/


//Declare and Initialize Global variables
/*	These are the ethnicity categories, you can add/delete
	You can also change these to work for gender or department
	just make sure you update rest of code accordingly
*/
	int WH = 0;
	int* WHptr = &WH;

	int AS = 0;
	int* ASptr = &AS;

	int BL = 0;
	int* BLptr = &BL;

	int HI = 0;
	int* HIptr = &HI;

	int _2X = 0;
	int* _2Xptr = &_2X;

	int Other = 0;
	int* Otherptr = &Other;


	string title;
	string ID;
	string ethnicity;
	string gender;
	string department;
	string citations;
	string numAuthors;
	int numberAuthors;


	//this is for reading in from a file and outputing to a file
	ifstream ifs;
	ofstream ofs;




//This is the info included in each link of the list
struct Authors {
	string title;
	string ID;
	string ethnicity;
	string gender;
	string department;
	string citations; 
	int numberAuthors;

	Authors *next;
};

//This function adds a link with the author info to the list
// as long as the title is the same as the previous one
void addLink(Authors* head){
		//Checks to see if its the end of the file
		if(ifs.eof()){
			return;
		}
		//reads first observation (should be title)
		getline(ifs, title, ',');

		//checks to see if title matches title of passed in linked list 
		if(title != head->title){

			return;
		}

		else{

		//creates new link
		Authors* p = new Authors;

		//reads vital info
		getline(ifs, ID, ',');
		getline(ifs, ethnicity, ',');
		getline(ifs, gender, ',');
		getline(ifs, department, ',');
		getline(ifs, citations, ',');
		getline(ifs, numAuthors);
		numberAuthors = stoi(numAuthors);

		//puts info into a link
		p->ID = ID; //intialize head of list with data
		p->ethnicity = ethnicity;
		p->gender = gender;
		p->department = department;
		p->title = title;
		p->citations = citations;
		p->numberAuthors = numberAuthors;
		p->next = NULL;

		//connects this link to the rest of the linked list that was passed in (head)
		head->next = p;

		//this is a recursive function so it will keep going until it reaches an 
		//observation with a new title that doesnt match with the rest of the linked list
		addLink(p);
		//not sure if i should delete p here, but i will figure out soon :P
		}

}


void initializeEthnicities(){
	*WHptr = 0;
	*ASptr = 0; 
	*BLptr = 0;
	*HIptr = 0;
	*_2Xptr = 0;
	*Otherptr = 0;
}

//finds the index
double findHomophilyIndex(Authors* head){
	
	//need to initialize all the enthincity categories back to 0 for every new linked list
	//this allows us to reuse variables and not waste memory space
	initializeEthnicities();
	cout<<"title is: "<<head->title<<endl;


	Authors* after = head->next;
	Authors* prev = head;
	//basically we have variable of the enthinicties that are intialized to 0
	//this do loop will iterate through the linked list (that was passed in) 
		//just reminder, each link in the list represents an author
		//each list contains all the authors of one publication
	//adds 1 to the appropriate ethnicity group
	//example: looks at the ethnicity of first link (first author) and reads "WH", 
		// it adds 1 to variable representing total number of WH

	//this is a little confusing just cuz you kinda need to know about linked lists and pointers sorry :(

	do{
		if(prev->ethnicity == "WH"){
			*WHptr = *WHptr +1;
	
		}
			else if(prev->ethnicity == "AS"){ 
				*ASptr = *ASptr +1;

			}
			else if(prev->ethnicity == "BL"){ 
				*BLptr = *BLptr +1;
	
			}
			else if(prev->ethnicity == "HI"){ 
				*HIptr = *HIptr +1;
			}
			else if(prev->ethnicity == "2X"){ 
				*_2Xptr = *_2Xptr+1;
			}
				else { 
					*Otherptr = *Otherptr+1; }

		prev=after;
		if(after==NULL){
			after = after;
		}
		else{
		after = after->next;}
		
	}while(prev!=NULL);

	

	double index = 0;
	//creates an array of all the ethnicties, each group represents total number of that race in the linked list

	int races[5] = {WH, AS, BL, HI, _2X};

	//calculates index
	//formula: summary of summation(#ofAuthorsWithRaceN/TotalAuthorsOfPublication)^2
	for (int i = 0; i<5; i++) 
	{
		double r = static_cast<double>(races[i]);
		double a= static_cast<double>(head->numberAuthors);
		double x = r/a;

		index = index + pow(x, 2.0);
	}

	return index;

}

void outputOntoFile (string outfile, Authors* head, double index){

	Authors* after = head->next;
	Authors* current = head;
	
	//opens file to write on, does not overwrite previously written work
	ofs.open(outfile, ofs.out | ofs.app);

	//iterates through passed in linked list and outputs each title, ID, and corresponding homophily index
 	while(current!=NULL){

		ofs<<current->title<<","<<current->ID<<","<<index<<endl;

		current=after;
		if(after==NULL){
			after = after;
		}
		else{
			after = after->next;}
		
	}

	//closes output file
	ofs.close();
}


int main(int argc, char *argv[]){ 
	//infile is second argument, reading in info from this file
	string infile = argv[1];

	//outfile is third argument, outputting data onto this file
		//make sure it is a new blank file, it does not overwrite previously work on file
	string outfile = argv[2];
	
	//opens file
	ifs.open(infile);

	//reads first line
	getline(ifs, title, ','); //first data must be title
	
	//while loop, continues as long as it hasnt reached end of file
	while(!ifs.eof()){ 

		//creates new list for each new title
		Authors* head = new Authors;

		//reads in the info for the first author and creates first head link of linked list
		getline(ifs, ID, ',');
		getline(ifs, ethnicity, ',');
		getline(ifs, gender, ',');
		getline(ifs, department, ',');
		getline(ifs, citations, ',');
		getline(ifs, numAuthors);
		numberAuthors = stoi(numAuthors);

		//inputs info it just read into a link
		head->ID = ID;
		head->ethnicity = ethnicity;
		head->gender = gender;
		head->department = department;
		head->title = title;
		head->citations = citations;
		head->numberAuthors = numberAuthors;
		head->next = NULL;

		//keeps reading in lines and adding a new link for each author until reads a new title (aka a new publication)
		addLink(head);

		//finds the homphily index for this publication (this linked list)
		double i = findHomophilyIndex(head);
		//prints out index of this publicaiton
		cout<<"index is: "<<i<<endl;

		//code to output the index onto a file
		outputOntoFile (outfile, head, i);

		//free up memory space
		delete head;
	}

	//close input file
	ifs.close();
	
	return 0;
}



