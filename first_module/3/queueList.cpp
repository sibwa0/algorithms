#include<cassert>
#include<iostream>
#include<sstream>

template<class T>
class Queue {
public:
	Queue() = default;
	Queue( const Queue& ) = delete;
	~Queue();

	Queue& operator = ( const Queue& ) = delete;

	void PushBack( const T& value );
	T PopFront();
	int Size() const { return size; }
	bool IsEmpty() const { return size == 0; }

private:
	struct Node {
		T Value;
		Node* Next;

		explicit Node( const T& value, Node* next = nullptr ) : Value( value ), Next( next ) {}
	};
	Node* head = nullptr;
	Node* tail = nullptr;
	int size = 0;
};

template<class T>
Queue<T>::~Queue()
{
	while( head != nullptr ) {
		Node* tmpNode = head;
		head = head->Next;
		delete tmpNode;
	}
}

template<class T>
void Queue<T>::PushBack( const T& value )
{
	Node* newNode = new Node( value );
	if( IsEmpty() ) {
		head = tail = newNode;
	} else {
		tail->Next = newNode;
		tail = newNode;
	}
	++size;
}

template<class T>
T Queue<T>::PopFront()
{
	assert( !IsEmpty() );
	Node* tmpNode = head;
	T tmpValue = head->Value;
	head = head->Next;
	delete tmpNode;
	if( head == nullptr ) {
		tail = nullptr;
	}
	--size;
	return tmpValue;
}

int run( std::istream& input, std::ostream& output )
{
	Queue<int> queue;
	int n = 0;
	input >> n;
	bool result = true;
	for( int i = 0; i < n; ++i ) {
		int command = 0;
		int value = 0;
		input >> command >> value;
		switch( command ) {
		case 2:
			if( !queue.IsEmpty() ) {
				result = result && queue.PopFront() == value;
			} else {
				result = result && value == -1;
			}
			break;
		case 3:
			queue.PushBack( value );
			break;
		default:
			assert( false );
		}
	}
	output << ( result ? "YES" : "NO");
	return 0;
}

void testQueue()
{
	{
		std::stringstream input;
		std::stringstream output;
		input << "3 3 44 3 50 2 44";
		run( input, output );
		assert( output.str() == "YES" );
	}
	{
		std::stringstream input;
		std::stringstream output;
		input << "2 3 44 2 66";
		run( input, output );
		assert( output.str() == "NO" );
	}
}

int main()
{
	testQueue();
	// run( std::cin, std::cout );
	return 0;
}