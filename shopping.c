/* \    / | ''T''    /\   |    |      /\  /\     /\   |\ ''T''
    \  /  |   |     /--\  |    |     /  \/  \   /--\  |/   |
     \/   |   |    /    \ |___ |___ /        \ /    \ |\   | */
#include <stdio.h>
#include <string.h>
struct item
{
	int id;
	char name[20];
	int price;
	int qty;
	struct item *next;
}*shopList = NULL;

void shopInsert()
{
	struct item *newnode;
	newnode = (struct item*) malloc (sizeof(struct item));
	printf("Enter name: ");
	scanf("%s", newnode->name);
	printf("Enter cost: ");
	scanf("%d", &newnode->price);
	printf("Enter quantity: ");
	scanf("%d", &newnode->qty);
	if(shopList == NULL)
	{
		newnode->next = NULL;
		newnode->id = 10000;
	}
	else
	{
		newnode->id = shopList->id + 1;
		newnode->next = shopList;
	}
	shopList = newnode;
}

int shopRemove(int id)
{
	int flag = 0;
	struct item *t1 = shopList, *t2;
	while(t1->id != id)
	{
		if(t1->next == NULL)
		{
			flag = 1;
			break;
		}
		t2 = t1;
		t1 = t1->next;
	}
	if(flag == 1)
	{
		printf("ID #%d is not in the list\n", id);
	}
	else
	{
		if(t1 == shopList)
			shopList = shopList->next;
		else
			t2->next = t1->next;
		free(t1);
		return 1;
	}
	return 0;
}

void shopDisplay()
{
	if(shopList == NULL)
		printf("Shop is empty\n");
	else
	{
		printf("ID\tNAME\tPRICE\tQUANTITY\n");
		struct item *t = shopList;
		while(t != NULL)
		{
			printf("#%d\t", t->id);
			printf("%s\t", t->name);
			printf("%d\t", t->price);
			printf("%d\n", t->qty);
			t = t->next;
		}
	}
}

void shopModify()
{
	int id;
	printf("Enter ID of item you want to modify: ");
	scanf("%d", &id);
	int flag = 0;
	struct item *t = shopList;
	while(t->id != id)
	{
		if(t == NULL)
		{
			flag = 1;
			break;
		}
		t = t->next;
	}
	if(flag == 1)
	{
		printf("ID #%d is not in the list\n", id);
	}
	else
	{
		printf("Enter name: ");
		scanf("%s", t->name);
		printf("Enter cost: ");
		scanf("%d", &t->price);
		printf("Enter quantity: ");
		scanf("%d", &t->qty);
	}
}

void owner()
{
	int ch, id;
	do
	{
		printf("\n1. Add item\n2. Remove item\n3. Display all items\n4. Modify an item\n5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: shopInsert();
					break;
			case 2: printf("Enter the ID: ");
					scanf("%d", &id);
					if(shopRemove(id) == 1)
						printf("Item with ID #%d has been removed\n", id);
					else
						printf("ID #%d is not in the list\n", id);
					break;
			case 3: shopDisplay();
					break;
			case 4: shopModify();
					break;
			case 5: printf("Thank you\n");
					break;
			default:printf("Invalid choice\n");
		}
	}while(ch != 5);
}

struct item *cartList = NULL;

void cartInsert()
{
	struct item *newnode;
	newnode = (struct item*) malloc (sizeof(struct item));
	printf("Enter id of the product you want: ");
	int id, flag = 0;
	scanf("%d", &id);
	struct item *t = shopList;
	while(t != NULL)
	{
		if(t->id == id)
		{
			flag = 1;
			int cartflag = 0;
			struct item *temp = cartList;
			while(temp != NULL)
			{
				if(temp->id == id)
				{
					cartflag = 1;
					break;
				}
				temp = temp->next;
			}
			if(cartflag == 0)
			{
				newnode->id = id;
				strcpy(newnode->name, t->name);
				newnode->price = t->price;
				int qty;
				while(1)
				{
					printf("Enter the quantity: ");
					scanf("%d", &qty);
					if(qty <= t->qty)
					{
						newnode->qty = qty;
						break;
					}
					else
						printf("Enter valid quantity\n");
				}
				t->qty = t->qty - qty;
				if(t->qty == 0)
					shopRemove(id);
				if(cartList == NULL)
				{
					newnode->next = NULL;
				}
				else
				{
					newnode->next = cartList;
				}
				cartList = newnode;
			}
			else
			{
				t->qty += temp->qty;
				int qty;
				while(1)
				{
					printf("Enter the quantity: ");
					scanf("%d", &qty);
					if(qty <= t->qty)
					{
						newnode->qty = qty;
						break;
					}
					else
						printf("Enter valid quantity\n");
				}
				t->qty = t->qty - qty;
				if(t->qty == 0)
					shopRemove(id);
			}
			break;
		}
		t = t->next;
	}
	if(flag == 0)
		printf("ID #%d is invalid\n", id);
}

void cartRemove()
{
	int id;
	printf("Enter the ID of the element to be removed: ");
	scanf("%d", &id);
	int flag = 0;
	struct item *t1 = cartList, *t2;
	while(t1->id != id)
	{
		if(t1->next == NULL)
		{
			flag = 1;
			break;
		}
		t2 = t1;
		t1 = t1->next;
	}
	if(flag == 1)
	{
		printf("ID #%d is not in the list\n", id);
	}
	else
	{
		printf("The following has been removed:\n");
		printf("ID: #%d\n", t1->id);
		printf("Item Name: %s\n", t1->name);
		struct item *t = shopList;
		while(t != NULL)
		{
			if(t->id == id)
			{
				t->qty = t->qty + t1->qty;
				break;
			}
			t = t->next;
		}
		if(t1 == cartList)
			cartList = cartList->next;
		else
			t2->next = t1->next;
		free(t1);
	}
}

void cartModify()
{
	printf("Enter the id of the item whose quantity you want to change: ");
	int id;
	scanf("%d", &id);
	struct item *cart_t = cartList;
	struct item *shop_t = shopList;
	int flag = 0;
	while(cart_t->id != id)
	{
		if(cart_t == NULL)
		{
			flag = 1;
			break;
		}
		cart_t = cart_t->next;
	}
	if(flag == 1)
	{
		printf("Item with ID #%d is not in the list!\n", id);
	}
	else
	{
		int qty;
		while(shop_t->id != id)
		{
			shop_t = shop_t->next;
		}
		shop_t->qty += cart_t->qty;
		cart_t->qty = 0;
		while(1)
		{
			printf("Enter the quantity: ");
			scanf("%d", &qty);
			if(qty <= shop_t->qty)
			{
				cart_t->qty = qty;
				break;
			}
			else
				printf("Enter valid quantity\n");
		}
		shop_t->qty -= qty;
		if(shop_t->qty == 0)
			shopRemove(id);
	}
}

void cartDisplay()
{
	if(cartList == NULL)
		printf("item is empty\n");
	else
	{
		int total = 0;
		printf("ID\tName\tPrice\tQuantity\tTotal Price\n");
		struct item *t = cartList;
		while(t != NULL)
		{
			printf("#%d\t", t->id);
			printf("%s\t", t->name);
			printf("%d\t", t->price);
			printf("%d\t", t->qty);
			printf("\t%d\n", (t->price)*(t->qty));
			total += (t->price)*(t->qty);
			t = t->next;
		}
		printf("Net Cost = %d\n", total);
	}
}

void checkOut(char name[], char phno[])
{
	if(cartList != NULL)
	{
		printf("---------------------------------------------------------------------------------------------------\n");
		printf("___________________________________________________________________________________________________\n");
		printf("\t\t\t\t\tVIT ALL-MART\n");
		printf("___________________________________________________________________________________________________\n");
		printf("---------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t\tBILL\n\n");
		printf("Customer Name: %s\nContact Number: %s\n\n", name, phno);
		printf("ID\tNAME\tPRICE\tQUANTITY\tTOTAL PRICE\n");
		printf("---------------------------------------------------------------------------------------------------\n");
		int total = 0;
		struct item *t = cartList;
		while(t != NULL)
		{
			printf("#%d\t", t->id);
			printf("%s\t", t->name);
			printf("%d\t", t->price);
			printf("%d\t", t->qty);
			printf("\t%d\n", (t->price)*(t->qty));
			total += (t->price)*(t->qty);
			t = t->next;
		}
		printf("\nNET COST = %d\n", total);
		printf("---------------------------------------------------------------------------------------------------\n");
		printf("\n\t\t\t\tTHANK YOU! PLEASE VISIT AGAIN!\n");
		if(total >= 1000)
		{
			printf("Your total expenditure is over 1000. Do you want to avail of free home delivery? (Y/N)\n");
		}
		else
		{
			printf("Do you want to avail of home delivery (Y/N)? Delivery charges are 10% of your total cost.\n");
		}
		char homeDelivery;
		scanf("%c", &homeDelivery);
		while(cartList != NULL)
		{
			struct item *t = cartList;
			cartList = cartList->next;
			free(t);
		}
	}
	else
		printf("THANK YOU! PLEASE VISIT AGAIN!\n");

}

void customer()
{
	if(shopList != NULL)
	{
		printf("\n\t\t\t\t\t\tWELCOME!\n");
		char name[20], phno[11];
		printf("Enter your name: ");
		scanf("%s", name);
		printf("Enter your number: ");
		scanf("%s", phno);
		int ch;
		do
		{
			printf("\n1. See all items in the shop\n2. Add an item to item\n3. Remove an item from item\n4. Modify quantity\n5. See your item\n6. Check Out\n");
			printf("Enter your choice: ");
			scanf("%d", &ch);
			switch(ch)
			{
				case 1: shopDisplay();
						break;
				case 2: cartInsert();
						break;
				case 3: cartRemove();
						break;
				case 4: cartModify();
						break;
				case 5: cartDisplay();
						break;
				case 6: checkOut(name, phno);
						break;
				default:printf("Invalid choice\n");
			}
		}while(ch != 6);
	}
	else
		printf("Shop is closed. Please come back later!\n");
}

void main()
{
	int ch;
	char password[20] = "DSAProject";
	do
	{
		char pwd[20];
		printf("\nEnter 1 if you are the admin, 2 if you are a user. Enter 3 to exit.\n");
		printf("Enter your choice: ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: printf("Enter the password: ");
					scanf("%s", pwd);
					if(strcmp(password, pwd) == 0)
						owner();
					else
						printf("Incorrect Password!\n");
					break;
			case 2: customer();
					break;
			case 3: printf("Thank you\n");
					break;
			default:printf("Invalid choice\n");
					break;
		}
	}while(ch != 3);
}
