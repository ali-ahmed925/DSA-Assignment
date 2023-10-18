#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "Sequence.h"
using namespace std;
using namespace chrono;

class LinkedList : Sequence{
	public:
		class Node{
			public:  	
		        int data;
				Node * next;
				Node(int data) : data(data){
					next = NULL;	 	   	
				}  	  	
		};
	    Node * head;
		LinkedList(){
			head = NULL;		 	
		}
		 
		void fillrandom(int n){
			for(int i=0; i<n; i++){
				insert(rand()%100);
			}
		}
		 
		void insert(int data) override{
			Node * newnode = new Node(data);
			static Node * temp = NULL;
	        if(head == NULL){
	        	head = newnode;
	        	temp = head;
			}else{
				temp->next = newnode;
				temp = newnode;   	
			}
		}
	
		void insert(int index, int data) override{
			Node * temp = head;
			int count = 0;
			while(count != index){
				if(temp->next == NULL){
					cout<<"Wrong index entered"<<endl;
					exit(0);		  	 	
				}else{
					temp = temp->next;
					count++;  	   	
				}				
			}
			Node * temp2 = temp->next; 
			Node * newnode = new Node(data);
			temp->next = newnode;
			newnode->next = temp2;	
		}
	
		void insertFirst(int data) override{
			Node * newnode = new Node(data);
			if(head == NULL){
				head = newnode;		
			}else{
				newnode->next = head;
				head = newnode;  	
			}	   			   
		}
	
	    void remove(int data) override{
			Node * temp = head;
		    if(temp->data == data){
			    head = head->next;	
			}else{
				while(temp->next != NULL && temp->next->data != data){	   	  	
					temp = temp->next;				   	  	
				} 	
				if(temp->next != NULL){
					temp->next = temp->next->next; 	   	
				}						   
				else{
					cout<<"Wrong value entered"<<endl; 					   	
				}
			}
		}
		
		void remove(int index, int data2) override{
			int count = 0;
			Node * temp = head;
			if(index == 0 && data2 == head->data){
				head = head->next;	 	
			}	 
			while(temp != NULL && count != index - 1){
				temp = temp->next;   
				count++;	   	
			}
			if(temp != NULL && temp->next->data == data2){
				temp->next = temp->next->next;		
			}else if(temp->next->data != data2){
	            cout<<"Wrong data provided"<<endl; 	
			}else{
				cout<<"Wrong index provided"<<endl;  	
			}	
		}
		
		void removeFirst() override{
			if(head->next != NULL){
				head = head->next;		  	
			}
		}
		
		void sort(){
			
		}
	
		void sortBubble(){
			int sorted = 0;
			swaps = 0; 
			n_compare = 0;
			Node * curr = head;
			Node * next;
			while(sorted == 0){
				sorted = 1;
				next = curr->next;
				while(next != NULL){
					if(next->data < curr->data){
						swap(next, curr);
						n_compare++;		  					
					}
					next = next->next;	
					sorted = 0;   	  	
				}
				curr = curr->next;	   	
			}	
		}
		
		void sortSelection() {
	        int swaps = 0;
	        int n_compare = 0;
	        Node* current = head;
	        while (current) {
	            Node* minNode = current;
	            Node* temp = current->next;
	            while (temp) {
	                n_compare++; 
	                if (temp->data < minNode->data) {
	                    minNode = temp;
	                }
	                temp = temp->next;
	            }
	            if (minNode != current) {
	                int tempData = current->data;
	                current->data = minNode->data;
	                minNode->data = tempData;
	                swaps++; 
	            }
	            current = current->next;
	        }
	    }
	    Node * sortInsertion(){
	    	swaps = 0;
	    	n_compare = 0;
	    	Node * dummy = new Node(0);
	    	while(head){
	    		Node * next = head->next;
		        Node * temp = dummy;
		        while(temp->next && temp->next->data < head->data){
	        	    temp = temp->next;
					n_compare++; 
				}
				head->next = temp->next;
				temp->next = head;
				head = next;
				swaps++;	
			}
			return dummy->next; 
		}
		
		void benchmarkBubble(LinkedList& s, int iterations) {
		    for (int i = 0; i < iterations; ++i) {
		        LinkedList tmp = s;
		        Print(tmp.head);
		        auto start = std::chrono::system_clock::now();
		        tmp.sortBubble();
				Print(tmp.head); 
		        auto end = std::chrono::system_clock::now();
		
		        std::cout << "Iteration " << i + 1 << " - Bubble Sort - Time taken: " 
		                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms, "
		                  << "Comparisons: " << tmp.getn_compare() << ", "
		                  << "Swaps: " << tmp.getSwaps() << "\n";
						                 
				s.fillrandom(10);   
		    }
		}
		
		void benchmarkSelection(LinkedList& s, int iterations) {
		    for (int i = 0; i < iterations; ++i) {
		        LinkedList tmp = s;
		        Print(tmp.head);
		        auto start = std::chrono::system_clock::now();
		        tmp.sortSelection();
				Print(tmp.head); 
		        auto end = std::chrono::system_clock::now();
		
		        std::cout << "Iteration " << i + 1 << " - Selection - Time taken: " 
		                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms, "
		                  << "Comparisons: " << tmp.getn_compare() << ", "
		                  << "Swaps: " << tmp.getSwaps() << "\n";
						                 
				s.fillrandom(10);   
		    }
		}
			
		void benchmarkInsertion(LinkedList& s, int iterations) {
		    for (int i = 0; i < iterations; ++i) {
		        LinkedList tmp = s;
		        Print(tmp.head);
		        auto start = std::chrono::system_clock::now();
		        tmp.sortInsertion();
				Print(tmp.head); 
		        auto end = std::chrono::system_clock::now();
		
		        std::cout << "Iteration " << i + 1 << " - Insertion Sort - Time taken: " 
		                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms, "
		                  << "Comparisons: " << tmp.getn_compare() << ", "
		                  << "Swaps: " << tmp.getSwaps() << "\n";
						                 
				s.fillrandom(10);   
		    }	
		}
		    
		void Print(Node * a){
			Node * temp = a;
		    while(temp != NULL){
			    cout<<temp->data<<" --> ";
				temp = temp->next;	
			}
			cout<<"null"<<endl; 
		}
		
		int getSwaps(){
			return swaps;
		}
		
		int getn_compare(){
			return n_compare;
		}
	private:
	    int swaps = 0;
	    int n_compare = 0;
        void deleteList(){
        	Node * curr = head;
            while(head != NULL) {
                Node * curr= head;
                head = head->next;
                delete curr;
            }
	    }
	    void swap(Node *a, Node *b){
            swaps++;
	        a->data = a->data ^ b->data;
	        b->data = a->data ^ b->data;
	        a->data = a->data ^ b->data;
	    }
		    
};
int main(){
	int index;
	int n_data;
	int val;
	LinkedList l;
	
	l.insert(3);
	l.insert(5);
	l.insert(4);      // insertion
	l.insert(7);
	l.insert(8);
	
	/*l.insertFirst(3);
	l.insertFirst(5);
	l.insertFirst(4);      // insert first
	l.insertFirst(7);
	l.insertFirst(8);*/
	
	//l.Print(l.head);
	
	/*cout<<"Enter index after which node will be inserted:"<<endl;
	cin>>index;
	cout<<"Enter new node value:"<<endl;     // insertion
	cin>>n_data;
	l.insert(index, n_data);*/
	
	/*cout<<"Enter value to be removed:"<<endl;
	cin>>val;                                      // removal
	l.remove(val);*/
	
	/*cout<<"Enter index and value to be removed:"<<endl;
	cin>>index;
	cin>>val;										// removal	
	l.remove(index, val);*/
	
	//l.Print(l.head);
	
	/*l.sortBubble();
	l.Print(l.head);
	cout<<l.getSwaps()<<endl;                     // sorting
	cout<<l.getn_compare()<<endl;*/
	
	/*l.sortSelection();
	l.Print(l.head);                             // sorting
	cout<<l.getSwaps()<<endl;
	cout<<l.getn_compare()<<endl;*/
	
	/*LinkedList::Node * node = l.sortInsertion();
	l.Print(node);
	cout<<l.getSwaps()<<endl;                    // sorting
	cout<<l.getn_compare()<<endl;*/
	
	LinkedList random;
	random.fillrandom(10);
	random.benchmarkBubble(random, 2);
	cout<<endl;
	random.benchmarkSelection(random, 2);
	cout<<endl;
	random.benchmarkInsertion(random, 2);
	cout<<endl;
}