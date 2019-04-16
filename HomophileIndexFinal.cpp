/* 
	This code was used in a team where everyone was familiar with coding, but not C++
	My comments try to explain my work to someone unfamilar with C++
*/


#include <iostream> 
#include <cstdlib> 
#include <fstream> 
#include <cmath>


using namespace std;
/*Logic of Code:
Reads a csv file that is organized/sorted by title
Reads title, creates a linked list with all of the authors of the publication
each link includes all the information relating to the author (department, race, gender, etc)
Calculates the homophily index using formula from Harvard paper 
	summation[(#ofAuthorsInRaceGroup/TotalAuthors)^2]
Once reads a new title, it will delete this linked list (to free up memory) and creates a new list
*/
	//ethnicities
	int CHN = 0;
	int* CHNptr = &CHN;

	int KOR = 0;
	int* KORptr = &KOR;

	int JAP = 0;
	int* JAPptr = &JAP;

	int VNM = 0;
	int* VNMptr = &VNM;

	int AFR = 0;
	int* AFRptr = &AFR;

	int ENG = 0;
	int* ENGptr = &ENG;

	int HIS = 0;
	int* HISptr = &HIS;

	int RUS = 0;
	int* RUSptr = &RUS;

	int EUR = 0;
	int* EURptr = &EUR;

	int IND = 0;
	int* INDptr = &IND;

	int Other = 0;
	int* Otherptr = &Other;
	
	//genders
	int M = 0;
	int* Mptr = &M;

	int F = 0;
	int* Fptr = &F;

	int GOther = 0;
	int* GOtherptr = &GOther;



	string title;
	string author;
	string dept;
	string numAuthorPublications;
	string ID;
	string school;
	string country;
	string city;
	string gender;
	string publisher;
	string paperCitations;
	string yearPublished;
	string ethnicity;
	string numAuthors;

	//this is for reading in from a file and outputing to a file
	ifstream ifs;
	ofstream ofs;



//This is the info included in each link of the list
struct Authors {

	string title;
	string author;
	string dept;
	string numAuthorPublications;
	string ID;
	string school;
	string country;
	string city;
	string gender;
	string publisher;
	string paperCitations;
	string yearPublished;
	string ethnicity;
	string numAuthors;

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
		
		Authors* p;

		//checks to see if title matches title of passed in linked list 
		if(title != head->title){
			return;
		}

		else{
		//creates new link
		//variable p is reused (by having it point to a new struct Authors) so this saves memory space
		p = new Authors;

		//reads info
		getline(ifs, author, ',');
		getline(ifs, dept, ',');
		getline(ifs, numAuthorPublications, ',');
		getline(ifs, ID, ',');
		getline(ifs, school, ',');
		getline(ifs, country, ',');
		getline(ifs, city, ',');
		getline(ifs, gender, ',');
		getline(ifs, ethnicity,',');
		getline(ifs, publisher, ',');
		getline(ifs, paperCitations, ',');
		getline(ifs, yearPublished, ',');
		getline(ifs, numAuthors);

		
		//puts info into a link
		p->title = title;
		p->author = author;
		p->dept = dept;
		p->numAuthorPublications = numAuthorPublications;
		p->ID = ID;
		p->school = school;
		p->country = country;
		p->city = city;
		p->gender = gender;
		p->publisher = publisher;
		p->paperCitations = paperCitations;
		p->yearPublished = yearPublished;
		p->numAuthors = numAuthors;
		p->ethnicity = ethnicity; 
		p->next = NULL;

		//connects this link to the rest of the linked list that was passed in (head)
		head->next = p;

		//this is a recursive function so it will keep going until it reaches an 
		//observation with a new title that doesnt match with the rest of the linked list
		addLink(p);
		}

}


void initializeEthnicities(){
	*CHNptr = 0;
	*KORptr = 0; 
	*JAPptr = 0;
	*VNMptr = 0;
	*AFRptr = 0;
	*ENGptr = 0;
	*HISptr = 0;
	*RUSptr = 0;
	*EURptr = 0;
	*INDptr = 0;
	*Otherptr = 0;
}

//finds the index for Race
double findHomophilyRaceIndex(Authors* head){
	
	//need to initialize all the enthnicity categories back to 0 for every new linked list
	//this allows us to reuse variables and not waste memory space
	initializeEthnicities();

	Authors* after = head->next;
	Authors* prev = head;
	//basically we have variable of the enthnicities that are intialized to 0
	//this do loop will iterate through the linked list (that was passed in) 
		//reminder, each list is a publication
		//each link in the list represents an author
		//each list contains all the authors of one publication
	
	//adds 1 to the appropriate ethnicity group
	//example: looks at the ethnicity of first link (first author) and reads "WH", 
		// it adds 1 to variable representing total number of WH

	//Sorry this part is a little confusing if you are unfamiliar with linked lists and pointers :(

	do{
		if(prev->ethnicity == "CHN"){
			*CHNptr = *CHNptr +1;
		}

			else if(prev->ethnicity == "KOR"){ 
				*KORptr = *KORptr+1;
			}

			else if(prev->ethnicity == "JAP"){ 
				*JAPptr = *JAPptr +1;
			}

			else if(prev->ethnicity == "VNM"){ 
				*VNMptr = *VNMptr +1;
			}

			else if(prev->ethnicity == "AFR"){ 
				*AFRptr = *AFRptr+1;
			}

			else if(prev->ethnicity == "ENG"){ 
				*ENGptr = *ENGptr+1;
			}

			else if(prev->ethnicity == "HIS"){ 
				*HISptr = *HISptr+1;
			}

			else if(prev->ethnicity == "RUS"){ 
				*RUSptr = *RUSptr+1;
			}

			else if(prev->ethnicity == "EUR"){ 
				*EURptr = *EURptr+1;
			}
			
			else if(prev->ethnicity == "IND"){ 
				*INDptr = *INDptr+1;
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
	//creates an array of all the ethnicities, each group represents total number of that race in the linked list

	int races[11] = {CHN, KOR, JAP, VNM, AFR, ENG, HIS, RUS, EUR, IND, Other};


	//calculates index
	//formula: summary of summation(#ofAuthorsWithRaceN/TotalAuthorsOfPublication)^2

	for (int i = 0; i<10; i++) 
	{
		double r = static_cast<double>(races[i]);

		int n = CHN+ KOR+ JAP+ VNM+ AFR+ENG+ HIS+ RUS+ EUR+ IND+ Other;
		double a = static_cast<double>(n);

		double x = r/a;


		index = index + pow(x, 2.0);
	}

	return index;

}



void initializeGenders(){
	*Mptr = 0;
	*Fptr = 0; 
	*GOtherptr = 0;
}

double findHomophilyGenderIndex(Authors* head){
	
	//need to initialize genders back to 0 for every new linked list
	//this allows us to reuse variables and not waste memory space
	initializeGenders();


	Authors* after = head->next;
	Authors* prev = head;
	//basically we have variable of the enthinicties that are intialized to 0
	//this do loop will iterate through the linked list (that was passed in) 
		//just reminder, each link in the list represents an author
		//each list contains all the authors of one publication
	//adds 1 to the appropriate gender group
	//example: looks at the gender of first link (first author) and reads "male", 
		// it adds 1 to variable representing total number of males

	do{
		if(prev->gender == "male"){
			*Mptr = *Mptr +1;
		}
		else if(prev->gender == "female"){
			*Fptr = *Fptr+1; 
		}
			else{
				*GOtherptr = *GOtherptr+1;
			}

		prev=after;
		if(after==NULL){
			after = after;
		}
		else{
		after = after->next;}
		
	}while(prev!=NULL);


	double index = 0;
	//creates an array of all the ethnicties, each group represents total number of that race in the linked list

	int genders[3] = {M,F, GOther};

	//calculates index
	//formula: summary of summation(#ofAuthorsWithRaceN/TotalAuthorsOfPublication)^2
	for (int i = 0; i<3; i++) 
	{
		double g = static_cast<double>(genders[i]);
		int n = M+F+GOther;
		double a = static_cast<double>(n);
		double x = g/a;
		index = index + pow(x, 2.0);
	}

	return index;

}




void outputOntoFile (string outfile, Authors* head, double RaceIndex, double GenderIndex){

	Authors* after = head->next;
	Authors* current = head;
	
	//opens file to write on, does not overwrite previously written work
	ofs.open(outfile, ofs.out | ofs.app);
	
	//iterates through passed in linked list and outputs each title, ID, and corresponding homophily index
 	while(current!=NULL){

		ofs<<current->title<<","<<RaceIndex<<","<<GenderIndex<<endl;

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

void deleteList(Authors* head)
{
	  Authors* next;

  for (Authors* curr=head; curr->next!=NULL; curr=next) {
    next = curr->next;
    delete curr;
  }

}
int main(int argc, char *argv[]){ 
	//infile is second argument, reading in info from this file
	string infile = argv[1];

	//outfile is third argument, outputting data onto this file
		//make sure it is a new blank file, it does not overwrite previously work on file
	string outfile = argv[2];
	
	//opens file
	ifs.open(infile);

	//reads first line of obs
	getline(ifs, title, ','); //first data must be title
	
	//while loop, continues as long as it hasnt reached end of file
	while(!ifs.eof()){ 

		//creates new list for each new title
		Authors* head = new Authors;

		//reads info
		getline(ifs, author, ',');
		getline(ifs, dept, ',');
		getline(ifs, numAuthorPublications, ',');
		getline(ifs, ID, ',');
		getline(ifs, school, ',');
		getline(ifs, country, ',');
		getline(ifs, city, ',');
		getline(ifs, gender, ',');
		getline(ifs, ethnicity, ',');
		getline(ifs, publisher, ',');
		getline(ifs, paperCitations, ',');
		getline(ifs, yearPublished, ',');
		getline(ifs, numAuthors);

		
		//puts info into a link
		head->title = title;
		head->author = author;
		head->dept = dept;
		head->numAuthorPublications = numAuthorPublications;
		head->ID = ID;
		head->school = school;
		head->country = country;
		head->city = city;
		head->gender = gender;
		head->publisher = publisher;
		head->paperCitations = paperCitations;
		head->yearPublished = yearPublished;
		head->numAuthors = numAuthors;
		head->ethnicity = ethnicity; 
		head->next = NULL;

		//keeps reading in lines and adding a new link for each author until reads a new title (aka a new publication)
		addLink(head);

		//finds the homphily index for this publication (this linked list)
		double RaceIndex = findHomophilyRaceIndex(head);
		double GenderIndex = findHomophilyGenderIndex(head);

		//code to output the index onto a file
		outputOntoFile (outfile, head, RaceIndex, GenderIndex);

		//free up memory space
		deleteList(head);


	}

	//close input file
	ifs.close();
	
	return 0;
}



