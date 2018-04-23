#include <iostream> 
#include <cstdlib> 
#include <fstream> 
#include <cmath>


using namespace std;

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
	string citations; //will figure out how to change string to int later
	string numAuthors;
	int numberAuthors;

	ifstream ifs;



struct Authors {
	string title;
	string ID;
	string ethnicity;
	string gender;
	string department;
	string citations; //will figure out how to change string to int later
	int numberAuthors;

	Authors *next;
};

void addLink(Authors* head){

		if(ifs.eof()){
			return;
		}

		getline(ifs, title, ',');

		if(title != head->title){

			return;
		}

		else{

		Authors* p = new Authors;

		getline(ifs, ID, ',');
		getline(ifs, ethnicity, ',');
		getline(ifs, gender, ',');
		getline(ifs, department, ',');
		getline(ifs, citations, ',');
		getline(ifs, numAuthors);
		numberAuthors = stoi(numAuthors);

		p->ID = ID; //intialize head of list with data
		p->ethnicity = ethnicity;
		p->gender = gender;
		p->department = department;
		p->title = title;
		p->citations = citations;
		p->numberAuthors = numberAuthors;
		p->next = NULL;

		head->next = p;
		addLink(p);
		//delete p?
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

double findHomophilyIndex(Authors* head){
	
	initializeEthnicities();
	cout<<"title is: "<<head->title<<endl;


	Authors* after = head->next;
	Authors* prev = head;

	do{
		if(prev->ethnicity == "WH"){ //retrieve raceOfAuthor from file
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
	int races[5] = {WH, AS, BL, HI, _2X};

	for (int i = 0; i<5; i++) 
	{
		double r = static_cast<double>(races[i]);
		double a= static_cast<double>(head->numberAuthors);
		double x = r/a;

		index = index + pow(x, 2.0);
	}

	return index;

}


int main(int argc, char *argv[]){ 
	
	string file = argv[1];
	
	ofstream ofs;

	ifs.open(file);

	getline(ifs, title, ','); //first data must be title
	
	while(!ifs.eof()){ 

	Authors* head = new Authors;

	getline(ifs, ID, ',');
	getline(ifs, ethnicity, ',');
	getline(ifs, gender, ',');
	getline(ifs, department, ',');
	getline(ifs, citations, ',');
	getline(ifs, numAuthors);
	numberAuthors = stoi(numAuthors);

	head->ID = ID; //intialize head of list with data
	head->ethnicity = ethnicity;
	head->gender = gender;
	head->department = department;
	head->title = title;
	head->citations = citations;
	head->numberAuthors = numberAuthors;
	head->next = NULL;

	addLink(head);

	double i = findHomophilyIndex(head);
	cout<<"index is: "<<i<<endl;

	//code to output the index onto a file
	delete head;
	}
	

	return 0;
}



