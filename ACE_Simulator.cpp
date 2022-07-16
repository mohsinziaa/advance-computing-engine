#include<string>
#include<conio.h>
#include<windows.h>
#include<iomanip>
#include<iostream>

using namespace std;

void gotoxy(int x, int y) 
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct node
{
	string ins;
	int address;
	int i;
	node *next;
	int p;
};

int ram[64], ac = 0, e = 0, dr = 0, tr = 0;
string aC, dR, tR, ones;
node *pc;

char flip(char c)
{
	return (c == '0') ? '1' : '0';
}

// function to convert decimal to binary
string DecimalToBinary(unsigned int dec)
{
	char binary[19] = {0};
	int i = 0;
	int ix = 20; // subscript of current character
	do
	{
		binary[--ix] = '0' + dec % 2;
		dec /= 2;
		i++;
	} while (i < 20);

	return (binary + ix); // ix is offset into char array where answer begins
}

int BinaryToDecimal(string binary)
{
	int power = 1048576;
	int sum = 0;
	//    assert(strlen(binary) == 20);

	for (int i = 0; i < 20; ++i)
	{
		if (i == 0 && binary[i] != '0')
		{
			sum = -1048576;
		}
		else
		{
			sum += (binary[i] - '0') * power;
		}
		power /= 2;
	}
	return sum;
}

void displayMemory()
{
	int x = 85;
	int y = 1;
	
	gotoxy(x, y);
	cout<<"   MEMORY   ";
	
	y = 2;
	for (int i = 0; i < 64; i++)
	{
		if(i % 4 == 0)
		{
			y++;
			x = 80;
		}
		
		gotoxy(x, y);
	
		if (ram[i] != -9999)
		{
			cout << ram[i];
		}
		else
		{
			cout << "_\t";
		}
			
		x += 7;
		
	}
}

void displayRegisters()
{
	aC = DecimalToBinary(ac);
	dR = DecimalToBinary(dr);
	tR = DecimalToBinary(tr);
	
	gotoxy(80, 21);
	cout<<"Registers";

	gotoxy(80, 23);
	cout<<"AC: "<<aC<<" : "<<ac;
	
	gotoxy(80, 24);
	cout<<"DR: "<<dR<<" : "<<dr;
	
	gotoxy(80, 25);
	cout<<"TR: "<<tR<<" : "<<tr;

}

void insert(node *head)
{
	node *ptr = head;
	
	while(ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = new node;
	ptr = ptr->next;
	cout << "\n\n\tEnter Instruction: ";
	cin >> ptr->ins;
	
	if (ptr->ins == "STR")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		
		if(ptr->i == 00)
		{
			ram[ptr->address] = ac;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			ram[ptr->address] = ac;
		}
		
		
	}
		
	if (ptr->ins == "LOD")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		
		if(ptr->i == 00)
		{
			ac = ram[ptr->address];
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			ac = ram[ptr->address];
		}
		else if(ptr->i == 10)
		{
			ac = ptr->address;
		}
		
	}
	else if (ptr->ins == "ADD")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		
		if(ptr->i == 00)
		{
			dr = ram[ptr->address];
			ac += ram[ptr->address];
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			dr = ram[ptr->address];
			ac += ram[ptr->address];
		}
		else if(ptr->i == 10)
		{
			dr = ptr->address;
			ac += ptr->address;
		}
		
	}
	else if (ptr->ins == "MUL")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;

		if(ptr->i == 00)
		{
			dr = ram[ptr->address];
			ac *= ram[ptr->address];
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			dr = ram[ptr->address];
			ac *= ram[ptr->address];
		}
		else if(ptr->i == 10)
		{
			dr = ptr->address;
			ac *= ptr->address;
		}
	}
	else if (ptr->ins == "DIF")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;

		if(ptr->i == 00)
		{
			dr = ram[ptr->address];
			ac -= ram[ptr->address];
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			dr = ram[ptr->address];
			ac -= ram[ptr->address];
		}
		else if(ptr->i == 10)
		{
			dr = ptr->address;
			ac -= ptr->address;
		}
	}

	else if (ptr->ins == "INC")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		if(ptr->i == 00)
		{
			dr = ram[ptr->address];
			ac = ram[ptr->address];
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			dr = ram[ptr->address];
			ac = ram[ptr->address];
		}
		else if(ptr->i == 10)
		{
			dr = ptr->address;
			ac = ptr->address;
		}
		ac++;
	}
	else if (ptr->ins == "DEC")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		if(ptr->i == 00)
		{
			dr = ram[ptr->address];
			ac = ram[ptr->address];
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			dr = ram[ptr->address];
			ac = ram[ptr->address];
		}
		else if(ptr->i == 10)
		{
			dr = ptr->address;
			ac = ptr->address;
		}
		ac--;
	}
	else if (ptr->ins == "SWP")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		if(ptr->i == 00)
		{
			tr = ac;
			ac = ram[ptr->address];
			ram[ptr->address] = tr;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			tr = ac;
			ac = ram[ptr->address];
			ram[ptr->address] = tr;
		}
		else if(ptr->i == 10)
		{
			tr = ac;
			ac = ptr->address;
			ptr->address = tr;
		}
	}
	else if (ptr->ins == "NOT")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		
		if(ptr->i == 00)
		{
			tr = (~ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			tr = (~ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 10)
		{
			tr = (~(ptr->address));
			ac = tr;
		}		
		
	}
	else if (ptr->ins == "OR")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		
		if(ptr->i == 00)
		{
			tr = (ac | ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			tr = (ac | ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 10)
		{
			tr = (ac | (ptr->address));
			ac = tr;
		}	
		
	}
	else if (ptr->ins == "NOR")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		if(ptr->i == 00)
		{
			tr = ~(ac | ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			tr = ~(ac | ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 10)
		{
			tr = ~(ac | (ptr->address));
			ac = tr;
		}	
	}
	else if (ptr->ins == "AND")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		if(ptr->i == 00)
		{
			tr = (ac & ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			tr = (ac & ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 10)
		{
			tr = (ac & (ptr->address));
			ac = tr;
		}	
	}
	else if (ptr->ins == "NAND")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		if(ptr->i == 00)
		{
			tr = ~(ac & ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			tr = ~(ac & ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 10)
		{
			tr = ~(ac & (ptr->address));
			ac = tr;
		}	
	}
	else if (ptr->ins == "XOR")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		if(ptr->i == 00)
		{
			tr = (ac ^ ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			tr = (ac ^ ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 10)
		{
			tr = (ac ^ (ptr->address));
			ac = tr;
		}	
	}
	else if (ptr->ins == "XNOR")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		cout << "\tI1 I0 (00/01/10): ";
		cin >> ptr->i;
		if(ptr->i == 00)
		{
			tr = ~(ac ^ ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 01)
		{
			ptr->address = ram[ptr->address];
			tr = ~(ac ^ ram[ptr->address]);
			ac = tr;
		}
		else if(ptr->i == 10)
		{
			tr = ~(ac ^ (ptr->address));
			ac = tr;
		}	
	}
	else if (ptr->ins == "GTR")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		if (ram[ptr->address] > ac)
		{
			ac = ram[ptr->address];
		}
	}
	else if (ptr->ins == "LES")
	{
		cout << "\tEnter Address: ";
		cin >> ptr->address;
		if (ram[ptr->address] < ac)
		{
			ac = ram[ptr->address];
		}
	}
	else if (ptr->ins == "CLA")
	{
		ac = 0;
	}
	else if (ptr->ins == "CMA")
	{
		ac = ~ac;
	}
	else if (ptr->ins == "TCA")
	{
		ac = ~ac;
		ac++;
	}
	else if (ptr->ins == "SHL")
	{
		ac = (ac << 1);
	}
	else if (ptr->ins == "SHR")
	{
		ac = (ac >> 1);
	}

	ptr->next = NULL;
}

void ramValInit(int address, int value)
{

	ram[address] = value;
}

void clearRam()
{
	for (int i = 0; i < 64; i++)
	{
		ram[i] = 0;
	}
}

int main()
{
	node *head = new node;
	head->next = NULL;

	char opt = 'y';
	int choice = 0;

	for (int i = 0; i < 64; i++)
	{
		ram[i] = -9999;
	}
	
	ram[4] = 20;
	ram[5] = -4;
	ram[6] = 123;
	ram[7] = 64;
		
	while(choice != 4)
	{
		system("CLS");

		gotoxy(20, 0);
		cout<<"Advance Computing Engine (ACE)";
		
		displayMemory();
		displayRegisters();
		
		gotoxy(0, 2);
		cout<<"1. Write a Program"<<endl
			<<"2. Enter A Value in RAM"<<endl
			<<"3. Clear RAM"<<endl
			<<"4. Exit"<<endl;
			
			cout<<"\nEnter Choice: ";
			cin>>choice;
			
		if (choice == 1)
		{
			opt = 'y';
			while (opt != 'n')
			{
				insert(head);
				cout << "\n\tDo you want to write more instructions(y/n)? ";
				cin >> opt;
			}
			system("cls");
		}
		else if (choice == 2)
		{
			int value, address;
			cout << "Enter the address at which you want to store value: ";
			cin >> address;
			cout << "Enter the value: ";
			cin >> value;
			ramValInit(address, value);
		}
		else if (choice == 3)
		{
			clearRam();
		}
		
		else if (choice == 4)
		{
			
			return 0;
		}
		
	}
}
