#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <iostream>
#include <string>

using namespace std;

class Role;

class Object
{
public:
	Object();

	Object(char, int, int);

	//(y, x)
	void setPos(int, int);

	//(y, x)
	pair<int, int> getPos();

	char getIcon();
	string getTag();
  
  //virtual void startActive() = 0; //tell game need to display choose screen
  //virtual void active(Role* role) = 0;
  //virtual void chooseActiveUP() = 0; 
  //virtual void chooseActiveDown() = 0;
  //virtual vector<string> getAllChoose() = 0; // return all choose's name, you can use it to display

protected:
	char icon;
	string tag;

	int y;
	int x;
};

#endif // _OBJECT_H_
