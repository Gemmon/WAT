//============================================================================
// Zadanie 3_1  jezyk C++
//  Sito Erastotenesa
//  WCY22IY1S1  Chrapowicz Krzysztof
//============================================================================
#include <iostream>
#include <cstdlib>
using namespace std;

struct Node
{
    int value;
    Node* next;
};

void erastotenes(int n)
{
    Node* head = NULL;
    Node* tail = NULL;

    // Wypelnienie listy liczbami
    for(int i = 2; i <= n; ++i)
	{
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->value = i;
        new_node->next = NULL;

        if(head == NULL)
		{
            head = new_node;
            tail = new_node;
        }
		else
		{
            tail->next = new_node;
            tail = new_node;
        }
    }

    int p = 2;
    while (p * p <= n)
	{
        Node* current = head;
        Node* prev = NULL;
        while(current != NULL)
		{
        
		int num = current->value;
        
		if(num == p)
		{
                prev = current;
                current = current->next;
        }
        //sprawdzenie czy liczba mimo nie bycia rownej p jest powiedzielna przez nia, i usuniecie jej gdy jest
		else if(num % p == 0) 
		{
                if(prev != NULL)
				{

                    prev->next = current->next;
        }
        else
        {
                    head = current->next;
                }
                free(current);
                current = prev->next;
        }
		else
		{
                prev = current;
                current = current->next;   
        }
        }
        p += 1;
    }

    //zwolnienie pammieci    
    Node* current = head;
    while(current != NULL)
    {
        cout << current->value << " ";
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    int n;
    cout << "Podaj n: ";
    cin >> n;

    cout << "Liczby pierwsze:  ";
    erastotenes(n);

    return 0;
}
