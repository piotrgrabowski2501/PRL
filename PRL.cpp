//Piotr Grabowski
#include <iostream>
enum Group{
	child,
	pregnant_women,
	worker,
	without_group
};

extern double limit_child[];
extern double limit_pregnant_women[];
extern double limit_worker[];

static unsigned int people=0;

struct RationStamp
{
	double meat;
	double chocolate;
};

struct Citizen
{
	int NIP;
	Group group;
	RationStamp rationStamp;
	Citizen()
	{
		NIP=0;
		group=without_group;
		rationStamp.chocolate=0.0;
		rationStamp.meat=0.0;
	}
	Citizen(int g)
	{
		this->NIP = people + 1;
		people++;
		this->group=(Group)g;
		if(g==0)
		{
			rationStamp.meat=*(limit_child);
			rationStamp.chocolate=*(limit_child+1);
		}

		if(g==1)
		{
			rationStamp.meat=*(limit_pregnant_women);
			rationStamp.chocolate=*(limit_pregnant_women+1);
		}

		if(g==2)
		{
			rationStamp.meat=*(limit_worker);
			rationStamp.chocolate=*(limit_worker+1);
		}
	}
};

struct Node
{
	Node* prev=nullptr;
	Node* next=nullptr;
	Citizen* citizen;
};
struct List
{
	Node* head = nullptr;
	Node* tail = nullptr;
};


class Shop
{
private:

	double get_commodity_citizen(Citizen* m) //C-CHOCO M-MEAT
	{
		if(this->symbol=='C') return m->rationStamp.chocolate;
		else return m->rationStamp.meat;
	}

	void set_commodity_citizen(Citizen* s, double subtraction)
	{
		if(this->symbol=='C') s->rationStamp.chocolate -= subtraction;
		else s->rationStamp.meat -= subtraction;
	}

	double minimum(double x, double y, double z)
	{
		double min_min=x;
		if(min_min > y) min_min = y;
		if(min_min > z) min_min = z;
		return min_min;
	}
public:
	List* queue=new List;
	char symbol;
	double commodity;

	Shop(){}

	Shop(char s, double x): symbol(s), commodity(x){}

	void delivery(double x) { commodity += x; }

	void setClientInTheQueue(int g) //end
	{
		auto new_node = new Node;
		auto new_client = new Citizen(g);
		new_node->citizen=new_client;

		if(queue->tail!=nullptr)
		{
			queue->tail->next=new_node;
			new_node->prev=queue->tail;
		}

		queue->tail=new_node;

		if(queue->head==nullptr)
			queue->head=new_node;
	}

    void setClientToTheFrontOfQueue(int g)
    {
    	auto new_node = new Node;
		auto new_client = new Citizen(g);
		new_node->citizen=new_client;

		if(queue->head==nullptr)
		{
			queue->head=new_node;
			queue->tail=new_node;
		}
		else
		{
			queue->head->prev=new_node;
			new_node->next=queue->head;
			queue->head=new_node;
		}
    }

    void setBehindClientRight(int k, int g)
    {
		auto new_node = new Node;
		auto new_client = new Citizen(g);
		new_node->citizen=new_client;
		Node* old_node;
		old_node=queue->head;
		if(queue->head==nullptr)
		{
			queue->head=new_node;
			queue->tail=new_node;
		}
		else
		{
			int i;
			for(i=1; i<=k; i++)
			{
				if(i==k)
				{
					if(old_node->next==nullptr)
					{
						queue->tail->next=new_node;
						new_node->prev=queue->tail;
						queue->tail=new_node;
					}
					else
					{
						new_node->next=old_node->next;
						old_node->next->prev=new_node;
						old_node->next=new_node;
						new_node->prev=old_node;
					}
				}
				old_node=old_node->next;
			}
		}
    }

    void deleteClient(int n)
    {
		Node* temp=queue->head;
		while(temp!=nullptr)
		{
			if(temp->citizen->NIP==n)
			{
				if(temp->prev==nullptr && temp->next==nullptr)
				{
					queue->head=nullptr;
					queue->tail=nullptr;
					delete temp;
					people--;
					break;
				}
				if(temp->prev==nullptr && temp->next!=nullptr)
				{
					temp->next->prev=nullptr;
					queue->head=temp->next;
					delete temp;
					people--;
					break;
				}
				if(temp->prev!=nullptr && temp->next==nullptr)
				{
					temp->prev->next=nullptr;
					queue->tail=temp->prev;
					delete temp;
					people--;
					break;
				}
				if(temp->prev!=nullptr && temp->next!=nullptr)
				{
					temp->next->prev=temp->prev;
					temp->prev->next=temp->next;
					delete temp;
					people--;
					break;
				}
			}

			temp = temp->next;
		}
    }

	bool commodityDelivered(double x, Citizen* o)
	{
		if(x <= 0) return false;
		x = minimum(x,this->commodity,get_commodity_citizen(o));
		this->commodity -= x;
		set_commodity_citizen(o,x);
		return true;
	}

    void sale(double x)
    {
    	while(queue->head!=nullptr && this->commodity>0)
		{
			if(commodityDelivered(x,queue->head->citizen))
					deleteClient(queue->head->citizen->NIP);
			else return;
		}
    }
    void turnSequenceAround()
    {
		Node* temp_old_head=queue->head;
		if(queue->head!=queue->tail)
		{
			Node* temp1=queue->tail->prev;
			queue->head=queue->tail;
			queue->head->prev=nullptr;
			queue->head->next=temp1;


			while(temp1!=temp_old_head)
			{
				Node* pom_pom=temp1->prev;
				temp1->prev=temp1->next;
				temp1->next=pom_pom;
				temp1=pom_pom;
			}
			temp_old_head->prev=temp_old_head->next;
			temp_old_head->next=nullptr;
		}
    }

    void sort_()
    {
		Node* temp=queue->head;
		while(temp)
		{
			if(temp->citizen->group==0)
			{
				Node*temp1=temp;
				if(temp->next!=nullptr && temp!=queue->head)
				{
					temp=temp->next;
					temp1->prev->next=temp1->next;
					temp1->next->prev=temp1->prev;
					queue->head->prev=temp1;
					temp1->next=queue->head;
					temp1->prev=nullptr;
					queue->head=temp1;
				}
				else if(temp->next==nullptr && temp!=queue->head)
				{
					temp->prev->next=nullptr;
					queue->tail=temp->prev;
					queue->head->prev=temp;
					temp->next=queue->head;
					temp->prev=nullptr;
					queue->head=temp;
					break;
				}
				else temp=temp->next;
			}
			else temp=temp->next;
		}

		temp=queue->head;
		while(temp)
		{
			if(temp->citizen->group==1)
			{
				Node*temp1=temp;
				if(temp->next!=nullptr && temp!=queue->head)
				{
					temp=temp->next;
					temp1->prev->next=temp1->next;
					temp1->next->prev=temp1->prev;
					queue->head->prev=temp1;
					temp1->next=queue->head;
					temp1->prev=nullptr;
					queue->head=temp1;
				}
				else if(temp->next==nullptr && temp!=queue->head)
				{
					temp->prev->next=nullptr;
					queue->tail=temp->prev;
					queue->head->prev=temp;
					temp->next=queue->head;
					temp->prev=nullptr;
					queue->head=temp;
					break;
				}
				else temp=temp->next;
			}
			else temp=temp->next;
		}
		temp=queue->head;
		while(temp)
		{
			if(temp->citizen->group==2)
			{
				Node*temp1=temp;
				if(temp->next!=nullptr && temp!=queue->head)
				{
					temp=temp->next;
					temp1->prev->next=temp1->next;
					temp1->next->prev=temp1->prev;
					queue->head->prev=temp1;
					temp1->next=queue->head;
					temp1->prev=nullptr;
					queue->head=temp1;
				}
				else if(temp->next==nullptr && temp!=queue->head)
				{
					temp->prev->next=nullptr;
					queue->tail=temp->prev;
					queue->head->prev=temp;
					temp->next=queue->head;
					temp->prev=nullptr;
					queue->head=temp;
					break;
				}
				else temp=temp->next;
			}
			else temp=temp->next;
		}
		Node* temp_old_head=queue->head;
		if(queue->head!=queue->tail)
		{
			Node* temp1=queue->tail->prev;
			queue->head=queue->tail;
			queue->head->prev=nullptr;
			queue->head->next=temp1;

			while(temp1!=temp_old_head)
			{
				Node* pom_pom=temp1->prev;
				temp1->prev=temp1->next;
				temp1->next=pom_pom;
				temp1=pom_pom;
			}
			temp_old_head->prev=temp_old_head->next;
			temp_old_head->next=nullptr;
		}
    }

    int checkPresence()
    {
		Node* temp=queue->head;
		int sizeOfQueue=0;
		while(temp!=nullptr)
		{
			std::cout << temp->citizen->NIP << " "
				<< temp->citizen->group << " "
				<< temp->citizen->rationStamp.meat << " "
				<< temp->citizen->rationStamp.chocolate << std::endl;
			sizeOfQueue++;
			temp = temp->next;
		}
		return sizeOfQueue;
    }

    void addQueue(Shop &shop2)
    {
    	if(shop2.symbol!=this->symbol) return;
		else
		{	shop2.turnSequenceAround();
			this->queue->tail->next=shop2.queue->head;
		}
    }
    ~Shop()
    {
    	Node* temp=queue->head;
		while(temp)
		{
			deleteClient(temp->citizen->NIP);
			delete temp->citizen;
			temp=temp->next;
		}
		delete this->queue;
    }
};
